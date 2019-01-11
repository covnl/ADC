#include "typedefs.h"


/* -- Global Variables --------------------------------------------------------*/

UINT8 PowerDown_Counter_Flg;//下电后开始计时标志，若为1，则利用API定时器开始定时
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
//=====控制应用程序是否执行====================
UINT8 Task_Enable;
UINT8 IsECUCrack; //是否为抄板的ECU
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



#ifdef DZ_001 //====Rotax 582客户定制版软件序列号，必须与Bootloader一一对应才可以使用

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
     /* RTI初始化 */
    RTI_RTDEC = RTI_DecSelect ;/* 1:十进制分频值  0：二进制分频值   */
    RTI_RTR  = RTI_Prescaler;/* 对IRCCLK分频的分频因子 1MHz/(2000)=500Hz(2ms) */
    RTI_RTIOSCSEL = IRCCLK; /* RTI clock sourse is IRCCLK */
    RTI_RTIF = ENABLED;/* Clear RTI interrupt flag  */
    RTI_RTIE = ENABLED;/* Enable RTI interrupt  */

    /* API初始化 */
    API_APIFE  = FALSE;/* 必须将此位清零才可对后面的寄存器进行操作 */
    API_APICLK = Internal_Clock;//0:选择内部API时钟 1:选择总线时钟 
                         //如果启用外部晶振此处选1，如果启用内部RC振荡器，此处选0
    API_APIES  = FALSE;
    API_APIEA  = FALSE;
    API_APIE   = ENABLED;//开中断
    API_APIF   = ENABLED;//清楚API溢出标志，当产生中断后必须清楚此位才可以继续一个新的定时周期 
    API_APIR = API_Prescaler;    //当选用内部时钟时：0--0.2ms   1--0.4ms  2--0.6ms  3--0.8ms  4--1.0ms 
                        //选用外部时钟时：  0--2*Fbusclk  1--4*Fbusclk 2--6*Fbusclk 3--8*Fbus 4--10*Fbusclk                   
    API_APIFE  = ENABLED;  //要使能周期中断定时器，必须将此位设置为1  
    
    Scheduler_Flg_Clear();
    //=========================================
    IsECUCrack = FALSE;
    Task_Enable = TRUE;
    LKT4200_Successful = TRUE;
    B_StepEnabled = FALSE;
    StepMovedOneStep = 0;
    
    if(HLS_CV_APP & 128) //====2013-3-11 第八位
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
        RAM_VAL_ECU_Passwd = 847215;//默认密码 
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
     PowerDown_Counter_Flg = 0; //为0则不计时
     PowerDown_Ms = 0;
     PowerDown_Second = 0;
     AfterRun_Flg = 0;//下电后5S此标志置1，然后进入省电模式
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
   //====执行1ms任务函数======================================
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
   //====执行5ms任务函数======================================
   
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
 
   //====执行20ms任务函数======================================
   if(T_10ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_10MS_TASKS();//执行20ms任务
           #endif  
       }
       LLD_EXECUTE_r10ms();
       
       T_10ms = FALSE;
   }
   
   
   //====执行20ms任务函数======================================
   if(T_20ms)
   {
       if(Task_Enable)
       {
           #ifdef Enable_Application_Software
             EXECUTE_20MS_TASKS();//执行20ms任务
           #endif  
       }
       LLD_EXECUTE_r20ms();
       
       T_20ms=FALSE;
   }
   //====执行50ms任务函数======================================
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
   //====执行100ms任务函数======================================
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
   //====执行200ms任务函数======================================
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
   //====执行1000ms任务函数======================================
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
**检测加密字节
**
*****************************************/
void  Check_Security(void)
{}

/*****************************************
**记录复位次数，然后存储到NVM中
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
** 当钥匙又打开后开将记录得到时间写到NVM中存储起来
**
*****************************************************************/
void KeyOn_Again(void) 
{
                 
     Write_Flag(&tEngOff,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS,0x1F); //把tEngoff存储的NVM中，因为在初始化时RAM会全部被清零
     if(*(UINT16*)NVM_tEngOff_Ptr != tEngOff) //如果写下电时间失败
     {
         RAM_Write_tEngOff_Flag = 1;  //相当于NVM_tEngOff_Error_Flg 
         Write_Flag(&RAM_Write_tEngOff_Flag,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS+2,0x1F);//写错误标志
     } 
     else
     {
         RAM_Write_tEngOff_Flag = 0;
         Write_Flag(&RAM_Write_tEngOff_Flag,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS+2,0x1F);
     }
     //=========================
     
     Disable_All_Interrupts();
     
     #ifdef Bootloader_V54
        __asm   //使用这种方法的话下电计时的时间参数无法传递给应用程序
       {
           JMP $F000;//程序计数器PC跳转到程序复位后的地址处
       }
     #else
        __asm   //使用这种方法的话下电计时的时间参数无法传递给应用程序
       {
           JMP $C000;//程序计数器PC跳转到程序复位后的地址处
       }
     #endif
     

}

/****************************************************************
**
**
*****************************************************************/

void EngOff_Timer(void) //下电延迟计数函数
{
    if(!HLS_B_Syn) //如果失去同步或者发动机停止转动
    {
        if(PowerDown_Ms>=TwentyMs_Per_Second) //1秒计时时间到
        {
              PowerDown_Ms=0;
              if(HLS_tEngOff+1)
              {
                   HLS_tEngOff++;//每过1秒tEngOff就加1
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
           PowerDown_Ms++; //每20ms加1 
        }
    }

}
/****************************************************************
**
**
*****************************************************************/

void Syn_Counter(void) //时间计数器
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
**发动机熄火后要立即回写数据
**发动机熄火的判断标准：1.N < 100  2.B_StaEnd下降沿
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
    //======检测钥匙开关函数=================
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
    //=====熄火时回写NVM==================
    #ifdef NoBatterySystem
        LLD_WriteBackNVM_r10ms();
    #endif    
    //=====串行通讯检测函数===============
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
    //=========自动标定函数，=======================
    //====2015-3-10SLM_20ms(); 
    //====标定数据时10ms的定时任务，进行内存读取和数据打包 
    if(KWP2000_Task10ms_PeriodicGetData())
    {
        KWP2000_Task10ms_PeriodicTransmission();
    }
    //=======CCP 20ms DAQ============================
    CCP_vDAQTransmit_20ms();
    //=======油泵继电器和氧传感器加热底层驱动========
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
    if(HLS_B_StaEnd) //启动发动机以后要将这些数据清0
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
    if(KWP2000_Task100ms_PeriodicGetData())//标定时100ms定时任务，进行内存读取和数据打包 
    {
       KWP2000_Task100ms_PeriodicTransmission();
    }
    //======CCP 100ms DAQ===============
    CCP_vDAQTransmit_100ms();

    Fault_Code_Indication_100ms();//用于故障灯指示
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
       if(AfterRun_Flg) //延迟5S，然后执行下电操作,检测到Key_Off，AfterRun_Flg为真
       {
           if(AfterRun_Flg>=HLS_tAfrApp)
           {
              // AfterRun_Flg = DISABLED;
               DISABLE_INTERRUPTS();//在擦写FLASH的时候一定要禁止其他一切中断发生
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
** API也产生1ms定时，用于产生10ms,20ms,50ms,100ms,200ms,1000ms任务，基于相同的定时器
**  而且要按顺序执行，即不会出现同一时刻执行两个不同的任务的情况
*********************************************************************************/
void interrupt Task_10ms(void)
{   
    API_APIF   = TRUE;   //清除后才可重新开始下一轮计时
    
    API_INTERRUPT(DISABLED); // 禁止自身中断 
    ENABLE_INTERRUPTS(); //Clear I bit interrupt nest    
   
    if(!PowerDown_Counter_Flg)//执行PowerDown_Interface()函数后此标志置，再次进入中断函数后就不会执行任务调度函数了
    {
        loop_timer_10ms++;//计数器加1
        T_10ms=TRUE;
        
        ////////////////////////////20ms任务执行时间到/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 2==0)
        {
            T_20ms=TRUE;
        }
        ////////////////////////////50ms任务执行时间到/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 5==0)
        {
            T_50ms=TRUE;
        }
        ///////////////////////////100ms任务执行时间到/////////////////////////////////////////////////////////
        if(loop_timer_10ms % 10==0)
        {
            T_100ms=TRUE;
        }
        ////////////////////////////200ms任务执行时间到////////////////////////////////////////////////////////
        if(loop_timer_10ms % 20==0)
        {
            T_200ms=TRUE;
        }
        /////////////////////////////1000ms任务执行时间到///////////////////////////////////////////////////////
        if(loop_timer_10ms % 100==0)
        {
            //==复位操作=================================
            loop_timer_10ms=0;
            T_1000ms=TRUE;
        }          
    }
    else//如果5秒计时到，且执行完了下电函数 
    {
        EngOff_Timer();
        if(u8IGNSW_Filtered&& (AfterRun_Flg>=HLS_tAfrApp))//点火开关又打开
        {
            KeyOn_Again(); 
        }   
    }
   
    API_INTERRUPT(ENABLED);// 打开自身中断 
}

#pragma CODE_SEG  DEFAULT
  




#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Task_1ms(void)
{
    CPMUFLG_RTIF = 1;   //一定要清chu这个标志，否则会一直进中断，大概1微秒进一次 

    vfnADC_Start_Conversions(); // 首先激活AD转换模块，每毫秒启动一次 
    #ifdef Enable_CrankLLD     
      TASK_1MS_FOR_INTERFACE; //====Crank 底层提供
    #endif
    Counter_1_MS++;
    T_1ms = TRUE;
    if(Counter_1_MS >= 5)
    {
        Counter_1_MS = 0;
        T_5ms = TRUE;
    }

    //==基准定时器===============
    Syn_Counter(); 
    //=====机油泵控制============ 
    #ifdef EnableLampControlOilPumpPWM
        OilPump1_PWM_1ms();
        OilPump2_PWM_1ms();
    #endif
}

#pragma CODE_SEG  DEFAULT






















