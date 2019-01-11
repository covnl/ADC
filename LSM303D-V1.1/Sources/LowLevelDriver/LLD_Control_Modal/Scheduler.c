#include "typedefs.h"


/* -- Global Variables --------------------------------------------------------*/

UINT8 PowerDown_Counter_Flg;//�µ��ʼ��ʱ��־����Ϊ1��������API��ʱ����ʼ��ʱ
UINT8 PowerDown_Ms;
UINT16 PowerDown_Second;
UINT8 AfterRun_Flg;
UINT16  loop_timer_10ms;
UINT8  T_1ms;
UINT8  T_5ms;
UINT8  T_10ms;
UINT8  T_20ms;
UINT8  T_50ms;
UINT8  T_100ms;
UINT8  T_200ms;
UINT8  T_1000ms;
UINT8  T_Syn;    
UINT8 Counter_1_MS;
UINT8 Syn_Minute=0;
UINT16 Syn_Ms=0;
UINT8 Start_Syn_Counter=0;     
//=====����Ӧ�ó����Ƿ�ִ��====================
UINT8 Task_Enable;
UINT8 IsECUCrack; //�Ƿ�Ϊ�����ECU
UINT8 B_StepEnabled;
UINT8 StepMovedOneStep;
UINT8 LKT4200_Successful;
UINT16 LKT4200_ResetCounter;
INT8 CopyRight_Buf[24];
UINT8 AutoSend100msData;
UINT8 B_WriteNVMEnd;
UINT8 B_PwrOnOneSecond;
UINT32 RAM_VAL_ECU_Passwd;


extern UINT8 LKT4200_Successful;
extern UINT16 StepPosDsr_WB;
extern UINT16 RAM_Write_tEngOff_Flag;
extern UINT16 NVM_tEngOff_Ptr;
extern UINT8 u8IGNSW_Filtered;



#ifdef DZ_001 //====Rotax 582�ͻ����ư�������кţ�������Bootloaderһһ��Ӧ�ſ���ʹ��

UINT16 DZ001_SoftwareID[4] = 
{
 0x0804,0x0303,0x0102,0x0103
};

#endif


/*******************************************************************************/
/**
* \brief    Scheduler - Periodic Interrup Timer Initialization
* \author   Engineer
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Init(void)
{   
     /* RTI��ʼ�� */
    RTI_RTDEC = RTI_DecSelect ;/* 1:ʮ���Ʒ�Ƶֵ  0�������Ʒ�Ƶֵ   */
    RTI_RTR  = RTI_Prescaler;/* ��IRCCLK��Ƶ�ķ�Ƶ���� 1MHz/(2000)=500Hz(2ms) */
    RTI_RTIOSCSEL = IRCCLK; /* RTI clock sourse is IRCCLK */
    RTI_RTIF = ENABLED;/* Clear RTI interrupt flag  */
    RTI_RTIE = ENABLED;/* Enable RTI interrupt  */

    /* API��ʼ�� */
    API_APIFE  = FALSE;/* ���뽫��λ����ſɶԺ���ļĴ������в��� */
    API_APICLK = Internal_Clock;//0:ѡ���ڲ�APIʱ�� 1:ѡ������ʱ�� 
                         //��������ⲿ����˴�ѡ1����������ڲ�RC�������˴�ѡ0
    API_APIES  = FALSE;
    API_APIEA  = FALSE;
    API_APIE   = ENABLED;//���ж�
    API_APIF   = ENABLED;//���API�����־���������жϺ���������λ�ſ��Լ���һ���µĶ�ʱ���� 
    API_APIR = API_Prescaler;    //��ѡ���ڲ�ʱ��ʱ��0--0.2ms   1--0.4ms  2--0.6ms  3--0.8ms  4--1.0ms 
                        //ѡ���ⲿʱ��ʱ��  0--2*Fbusclk  1--4*Fbusclk 2--6*Fbusclk 3--8*Fbus 4--10*Fbusclk                   
    API_APIFE  = ENABLED;  //Ҫʹ�������ж϶�ʱ�������뽫��λ����Ϊ1  
    
    Scheduler_Flg_Clear();
    //=========================================
    IsECUCrack = FALSE;
    Task_Enable = TRUE;
    LKT4200_Successful = TRUE;
    B_StepEnabled = FALSE;
    StepMovedOneStep = 0;
    
    if(HLS_CV_APP & 128) //====2013-3-11 �ڰ�λ
    {
        AutoSend100msData = TRUE;
    }
    else
    {
        AutoSend100msData = FALSE;
    }
    
    //=====================
    if(HLS_VAL_ECU_Passwd !=0xFFFFFFFF)
    {
        RAM_VAL_ECU_Passwd = HLS_VAL_ECU_Passwd;
    }
    else
    {
        RAM_VAL_ECU_Passwd = 847215;//Ĭ������ 
    }
}

void Scheduler_Flg_Clear(void)
{
    //=========================================
     loop_timer_10ms = 0;
     Counter_1_MS = 0;
     T_1ms = 0;
     T_5ms = 0;
     T_10ms = 0;
     T_20ms = 0;
     T_50ms = 0;
     T_100ms = 0;
     T_200ms = 0;
     T_1000ms =0;
     T_Syn = 0;
     //=========================================
     PowerDown_Counter_Flg = 0; //Ϊ0�򲻼�ʱ
     PowerDown_Ms = 0;
     PowerDown_Second = 0;
     AfterRun_Flg = 0;//�µ��5S�˱�־��1��Ȼ�����ʡ��ģʽ
     B_WriteNVMEnd = TRUE;
     B_PwrOnOneSecond = FALSE;
}


/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            "gu8Scheduler_Thread_ID". This variable is modified by          \n
            ISR "Scheduler_PIT0_Isr"                                        \n
            List of tasks shall be defined @ "tasks.h" file
* \author   Engineer
* \param    void
* \return   void
* \todo     
*/


void vfnTask_Scheduler(void)
{
   //====ִ��1ms������======================================
   if(T_1ms)
   {
       //=======================================
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_1MS_TASKS();
           #endif  
       }
       LLD_EXECUTE_r1ms();
       
       T_1ms = FALSE;
   }
   //====ִ��5ms������======================================
   
   if(T_5ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_5MS_TASKS();
           #endif  
       }
       LLD_EXECUTE_r5ms();
       T_5ms = FALSE;
   }
 
   //====ִ��20ms������======================================
   if(T_10ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_10MS_TASKS();//ִ��20ms����
           #endif  
       }
       LLD_EXECUTE_r10ms();
       
       T_10ms = FALSE;
   }
   
   
   //====ִ��20ms������======================================
   if(T_20ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_20MS_TASKS();//ִ��20ms����
           #endif  
       }
       LLD_EXECUTE_r20ms();
       
       T_20ms=FALSE;
   }
   //====ִ��50ms������======================================
   if(T_50ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_50MS_TASKS();
           #endif  
       }
       LLD_EXECUTE_r50ms();
       T_50ms=FALSE;  
   }
   //====ִ��100ms������======================================
   if(T_100ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_100MS_TASKS();   
           #endif  
       }
       LLD_EXECUTE_r100ms();
       
       T_100ms=FALSE;   
   }
   //====ִ��200ms������======================================
   if(T_200ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_200MS_TASKS();
           #endif  
       }

       T_200ms=FALSE;          
   }
   //====ִ��1000ms������======================================
   if(T_1000ms)
   {       
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_1000MS_TASKS();
           #endif  
       }
       LLD_EXECUTE_r1000ms();   
       
       T_1000ms=FALSE;      
   }
}

/*****************************************
**�������ֽ�
**
*****************************************/
void  Check_Security(void)
{}

/*****************************************
**��¼��λ������Ȼ��洢��NVM��
**
*****************************************/
void Increase_Reset_Counter(void)
{}



void Disable_All_Interrupts(void)
{
    DISABLE_INTERRUPTS();
    //===================RTI interrupt
    RTI_RTIF = TRUE;
    RTI_RTIE = FALSE;
    
    //===================API interrupt
    API_APIF = TRUE;
    API_APIE = FALSE;
    
    //===================Timer interrupt
    TIE = FALSE;
    TSCR2_TOI = FALSE;
    //===================ADC interrupt
    ADC_INTERRUPT(DISABLED);
    
    //===================PORTJ interrupt
    #ifdef LLD_4T1CCD_TR
       /** HALL_F , Port J, Channel 0*/
       PIEJ_PIEJ0 = FALSE;//Enable interrupt
       /** HALL_A , Port J, Channel 1*/
       PIEJ_PIEJ1 = FALSE;//Enable interrupt
    #endif
    
    #ifdef LLD_4T1CTH_TR2_0M
        /** HALL_F , Port J, Channel 0*/
       PIEJ_PIEJ0 = FALSE;//Enable interrupt
       /** HALL_A , Port J, Channel 1*/
       PIEJ_PIEJ1 = FALSE;//Enable interrupt
    #endif
}

/****************************************************************
** ��Կ���ִ򿪺󿪽���¼�õ�ʱ��д��NVM�д洢����
**
*****************************************************************/
void KeyOn_Again(void) 
{
                 
     Write_Flag(&tEngOff,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS,0x1F); //��tEngoff�洢��NVM�У���Ϊ�ڳ�ʼ��ʱRAM��ȫ��������
     if(*(UINT16*)NVM_tEngOff_Ptr != tEngOff) //���д�µ�ʱ��ʧ��
     {
         RAM_Write_tEngOff_Flag = 1;  //�൱��NVM_tEngOff_Error_Flg 
         Write_Flag(&RAM_Write_tEngOff_Flag,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS+2,0x1F);//д�����־
     } 
     else
     {
         RAM_Write_tEngOff_Flag = 0;
         Write_Flag(&RAM_Write_tEngOff_Flag,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS+2,0x1F);
     }
     //=========================
     
     Disable_All_Interrupts();
     
     #ifdef Bootloader_V54
        __asm   //ʹ�����ַ����Ļ��µ��ʱ��ʱ������޷����ݸ�Ӧ�ó���
       {
           JMP $F000;//���������PC��ת������λ��ĵ�ַ��
       }
     #else
        __asm   //ʹ�����ַ����Ļ��µ��ʱ��ʱ������޷����ݸ�Ӧ�ó���
       {
           JMP $C000;//���������PC��ת������λ��ĵ�ַ��
       }
     #endif
     

}

/****************************************************************
**
**
*****************************************************************/

void EngOff_Timer(void) //�µ��ӳټ�������
{
    if(!HLS_B_Syn) //���ʧȥͬ�����߷�����ֹͣת��
    {
        if(PowerDown_Ms>=TwentyMs_Per_Second) //1���ʱʱ�䵽
        {
              PowerDown_Ms=0;
              if(HLS_tEngOff+1)
              {
                   HLS_tEngOff++;//ÿ��1��tEngOff�ͼ�1
              }
              if(PowerDown_Second>=(HLS_VAL_tEngOffMx - HLS_tAfrApp)) //
              {    
                   POWEROFF = LOW;  
              }
              else
              {
                 PowerDown_Second++;
              }
        }
        else
        {
           PowerDown_Ms++; //ÿ20ms��1 
        }
    }

}
/****************************************************************
**
**
*****************************************************************/

void Syn_Counter(void) //ʱ�������
{
    if(Start_Syn_Counter)
    {
         Syn_Ms++;
         if(Syn_Ms>59999)//1 minute=60000ms
         {
             Syn_Ms=0;
             Syn_Minute++;
             if(Syn_Minute>239)  //4 hour
             {
                 Syn_Minute=0;
             }
         }
    }
    else 
    {
         Syn_Minute=0;
         Syn_Ms=0;
    }
}

/****************************************************************
**������Ϩ���Ҫ������д����
**������Ϩ����жϱ�׼��1.N < 100  2.B_StaEnd�½���
*****************************************************************/

void LLD_WriteBackNVM_r10ms(void)
{
    if(HLS_B_StaEnd)
    {
        B_WriteNVMEnd = FALSE;
    }
    else
    {
        if(B_WriteNVMEnd == FALSE)
        {
            Write_Successful_Test(); 
            B_WriteNVMEnd = TRUE;
        }    
    }
       
}
/****************************************************************
**
**
*****************************************************************/
void LLD_EXECUTE_r1ms(void)
{
    //======���Կ�׿��غ���=================
    vfnIGNSW_Filter(); 

    #ifdef LLD_4T1CCD_TR
     #ifdef B_AsrEn_True
       HLS_B_AsrEn = TRUE; 
     #else
       TRACT_EN_Monitoring();
     #endif  
    #endif

    //=======================================
    #ifdef LLD_4T1CTH_TR2_0M
     #ifdef B_AsrEn_True
       HLS_B_AsrEn = TRUE; 
     #else
       TRACT_EN_Monitoring();
     #endif 
    #endif
    
    //=======================================
    CAN_RxDataProcess_r1ms();
    CAN_Tx_Process_r1ms();
    SAE_J1939Brodcast_1ms();
    IMU_Get_Pitch_Roll_Acc_r10ms();
}
/****************************************************************
**
**
*****************************************************************/
void LLD_EXECUTE_r5ms(void)
{
    #ifdef STEP_MOTOR_CONTROL_ENABLE_LLD 
      if(HLS_CV_APP & 32) 
      {
          if(HLS_B_IdlRdy)
          {
             vfnSet_ISM_Position(StepPosDsr + StepMovedOneStep); 
          }
          else
          {
             vfnSet_ISM_Position(StepPosDsr); 
          }
      }
      else
      {
          if(HLS_B_IdlRdy && B_StepEnabled)    
          {
             vfnSet_ISM_Position(StepPosDsr_WB + StepMovedOneStep);
          }
          else 
          {
             StepPosDsr_WB = HLS_StepPosDsr;
             vfnSet_ISM_Position(HLS_StepPosDsr);   
             if(HLS_B_StepLrn == FALSE)
             {
                  B_StepEnabled = ((HLS_StepPos == HLS_StepPosDsr)&&(HLS_StepPosDsr!=0));
             }
             else
             {
                  B_StepEnabled = FALSE;
             }
          }  
      }

      vfn_ISM_TASK();//Idle speed control
    #endif 
    
    LLD_Task_Syn();//2014-12-19   
}
/****************************************************************
**
**
*****************************************************************/
void LLD_EXECUTE_r10ms(void)
{
    //=====Ϩ��ʱ��дNVM==================
    #ifdef NoBatterySystem
        LLD_WriteBackNVM_r10ms();
    #endif    
    //=====����ͨѶ��⺯��===============
    asc0_KWP2000_FLASH_10ms();
    LLD_ServoCtl_r10ms();
    
    UAVCAN_MessageCollection_r10ms();
    //IMU_Get_Pitch_Roll_Acc_r10ms();
}
/****************************************************************
**
**
*****************************************************************/
void LLD_EXECUTE_r20ms(void)
{
    #ifdef Enable_CrankLLD
      TASK_20MS_FOR_INTERFACE;
    #endif  
    //=========�Զ��궨������=======================
    //====2015-3-10SLM_20ms(); 
    //====�궨����ʱ10ms�Ķ�ʱ���񣬽����ڴ��ȡ�����ݴ�� 
    if(KWP2000_Task10ms_PeriodicGetData())
    {
        KWP2000_Task10ms_PeriodicTransmission();
    }
    //=======CCP 20ms DAQ============================
    CCP_vDAQTransmit_20ms();
    //=======�ͱü̵����������������ȵײ�����========
    LLD_O2H_Control_r20ms();              
    FuelPump_Relay_r20ms();  
    LLD_GearPmpCtl_r20ms();
}

/****************************************************************
**
**
*****************************************************************/


void LLD_EXECUTE_r50ms(void)
{
    //===================2011-11-8
    if(HLS_B_StaEnd) //�����������Ժ�Ҫ����Щ������0
    {
       HLS_tEngOff = 0;
       PowerDown_Ms=0;
       PowerDown_Second = 0;
    } 
    //===================2012-4-6
    if(StepMovedOneStep == 0)
    {
       StepMovedOneStep = 1;
    }
    else
    {
       StepMovedOneStep = 0;
    }

}
/****************************************************************
**
**
*****************************************************************/
void LLD_EXECUTE_r100ms(void)
{
    //====================
    //====2015-3-10SLM_100ms();
    if(KWP2000_Task100ms_PeriodicGetData())//�궨ʱ100ms��ʱ���񣬽����ڴ��ȡ�����ݴ�� 
    {
       KWP2000_Task100ms_PeriodicTransmission();
    }
    //======CCP 100ms DAQ===============
    CCP_vDAQTransmit_100ms();

    Fault_Code_Indication_100ms();//���ڹ��ϵ�ָʾ
    DSM_ClearHealBit_r100ms();
}
/****************************************************************
**
**
*****************************************************************/ 
void LLD_EXECUTE_r1000ms(void)
{
    HLS_B_Pwf = 0;
    
    B_PwrOnOneSecond = TRUE;
    if(AutoSend100msData == FALSE)SCI_WriteWhenStartup(CopyRight_Buf,24);
    //===================================================== 
    #ifndef NoBatterySystem  
       if(AfterRun_Flg) //�ӳ�5S��Ȼ��ִ���µ����,��⵽Key_Off��AfterRun_FlgΪ��
       {
           if(AfterRun_Flg>=HLS_tAfrApp)
           {
              // AfterRun_Flg = DISABLED;
               DISABLE_INTERRUPTS();//�ڲ�дFLASH��ʱ��һ��Ҫ��ֹ����һ���жϷ���
               Powerdown_Interface();
               ENABLE_INTERRUPTS(); 
           }
           else
           {
               AfterRun_Flg++;
           }
       }
    #endif  
}

/****************************************************************
**
**
*****************************************************************/
void LLD_Task_Syn(void)
{
    if(T_Syn == TRUE)
    {
        T_Syn = FALSE;
        //========================================
        if(KWP2000_Tasksyn_PeriodicGetData(Syn_Ms))
        {
            KWP2000_Tasksyn_PeriodicTransmission();
        }
        //=========================================
        UAVCAN_MessageCollection_Syn();
        
    }
}




#pragma CODE_SEG __NEAR_SEG NON_BANKED

/*********************************************************************************
** APIҲ����1ms��ʱ�����ڲ���10ms,20ms,50ms,100ms,200ms,1000ms���񣬻�����ͬ�Ķ�ʱ��
**  ����Ҫ��˳��ִ�У����������ͬһʱ��ִ��������ͬ����������
*********************************************************************************/
void interrupt Task_10ms(void)
{   
    API_APIF   = TRUE;   //�����ſ����¿�ʼ��һ�ּ�ʱ
    
    API_INTERRUPT(DISABLED); // ��ֹ�����ж� 
    ENABLE_INTERRUPTS(); //Clear I bit interrupt nest    
   
    if(!PowerDown_Counter_Flg)//ִ��PowerDown_Interface()������˱�־�ã��ٴν����жϺ�����Ͳ���ִ��������Ⱥ�����
    {
        loop_timer_10ms++;//��������1
        T_10ms=TRUE;
        
        ////////////////////////////20ms����ִ��ʱ�䵽/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 2==0)
        {
            T_20ms=TRUE;
        }
        ////////////////////////////50ms����ִ��ʱ�䵽/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 5==0)
        {
            T_50ms=TRUE;
        }
        ///////////////////////////100ms����ִ��ʱ�䵽/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 10==0)
        {
            T_100ms=TRUE;
        }
        ////////////////////////////200ms����ִ��ʱ�䵽////////////////////////////////////////////////////////
        if(loop_timer_10ms % 20==0)
        {
            T_200ms=TRUE;
        }
        /////////////////////////////1000ms����ִ��ʱ�䵽///////////////////////////////////////////////////////
        if(loop_timer_10ms % 100==0)
        {
            //==��λ����=================================
            loop_timer_10ms=0;
            T_1000ms=TRUE;
        }          
    }
    else//���5���ʱ������ִ�������µ纯�� 
    {
        EngOff_Timer();
        if(u8IGNSW_Filtered&& (AfterRun_Flg>=HLS_tAfrApp))//��𿪹��ִ�
        {
            KeyOn_Again(); 
        }   
    }
   
    API_INTERRUPT(ENABLED);// �������ж� 
}

#pragma CODE_SEG  DEFAULT
  




#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Task_1ms(void)
{
    CPMUFLG_RTIF = 1;   //һ��Ҫ��chu�����־�������һֱ���жϣ����1΢���һ�� 

    vfnADC_Start_Conversions(); // ���ȼ���ADת��ģ�飬ÿ��������һ�� 
    #ifdef Enable_CrankLLD     
      TASK_1MS_FOR_INTERFACE; //====Crank �ײ��ṩ
    #endif
    Counter_1_MS++;
    T_1ms = TRUE;
    if(Counter_1_MS >= 5)
    {
        Counter_1_MS = 0;
        T_5ms = TRUE;
    }

    //==��׼��ʱ��===============
    Syn_Counter(); 
    //=====���ͱÿ���============ 
    #ifdef EnableLampControlOilPumpPWM
        OilPump1_PWM_1ms();
        OilPump2_PWM_1ms();
    #endif
}

#pragma CODE_SEG  DEFAULT






















