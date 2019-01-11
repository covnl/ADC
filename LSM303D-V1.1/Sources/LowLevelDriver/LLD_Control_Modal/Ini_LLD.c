
#include "typedefs.h"


UINT16 NVM_tEngOff_Ptr;
UINT16 NVM_tEngOff_Flg_Ptr;
UINT16 NVM_WriteError_Flg_Ptr;
UINT16 NVM_StartErase_Flg_Ptr;
UINT16 NVM_ECUFirstRuning_Ptr;
UINT8 AutoTuning_B_Pwf;

extern UINT16 RAM_Write_Successful_Flag;
extern UINT8 PowerDown_Counter_Flg;
extern UINT8 Task_Enable;




/*******************************************************************************/
/**
* \brief    Copy NVM data to RAM.
* \author   Engineer
* \param    void
* \return   void
*/
void Copy_WO2LearnData_To_Ram()
{
    UINT16 S_Address,D_Address;
    UINT16 i;
     
    if(AutoTuning_B_Pwf)
    {
        SelfLearningTabInit(AutoTuning_B_Pwf);
    }
    else
    {
        Convert_fVe_To_Ld();
    }
    
}

void Copy_WriteBackData_To_Ram()
{
    UINT16 S_Address,D_Address;
    UINT16 i;
 
    S_Address = DFLASH_BLOCK1_WRITEBACK_LOCALADDRESS;
    D_Address = RAM_WriteBack_Data;
    
    if(!HLS_B_Pwf)
    {
        for(i=0;i<Writeback_Data_Length;i++)
        {
            *(UINT8 *)D_Address++ = *(UINT8 *)S_Address++;
        }
    }    
    
    /*S_Address = DFLASH_BLOCK4_DTC_LOCALADDRESS;
    D_Address = RAM_DTC;
    for(i=0;i<DTC_Length;i++)
    {
        *(UINT8 *)D_Address++ = *(UINT8 *)S_Address++;
    }
    */
}

void Erase_DFLASH_Sector_2_256_Byte_After_KeyOn(void)  //ÿ�θ�λ֮��Ҫ�Ƚ����еı�־��0����Ĭ��Ϊʧ��״̬���µ��Ὣ�ɹ��ı�־д��ȥ
{
   Erase_D_Flash(1,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS);  
}

/*******************************************************************************/
/**
* \brief    LLD initialization
* \author   Engineer
* \param    void
* \return   void
*/
void vfnIni_LLD()
{
    HLS_B_KeyOn = TRUE;
    
    /* ��һ����д����ʱ�Ͳ������������Ʋ����ˣ���ΪDFLASH���ǿյģ���DFLASH�д������ݺ���ʹ���������ĸ��Ʋ��� */
    //====2015-3-10Copy_WO2LearnData_To_Ram();
    Calc_Ini();//2012-3-2  ��PFLASH�ı궨����д��RAM��
    Copy_WriteBackData_To_Ram();
    /* Perform SCI Initialization */
    SCI_Init();
    /* Perform I/O configuration and Initialization */
    vfnInputs_Outputs_Init();
    /* Starts all low level interrupts related to acquiring and 
    synchronizing to the crankshaft and camshaft. */
    asc0_KWP2000_ProtocolInit_FLASH();
    /* Perform initialization of Multi-thread round robin Task Scheduler */
    vfnScheduler_Init();
    
    #ifdef STEP_MOTOR_CONTROL_ENABLE_LLD
      Idle_Speed_Controller_Init();
    #endif
    
    
}


/*******************************************************************************/
/** 
* \brief    Power up interface
* \author   Engineer
* \param    void
* \return   void
*/
void Powerup_Interface(void)
{    
    Pre_Start_AD(); //�ϵ���Ƚ���ADת��
    Check_B_Pwf_LastTime();
    vfnIni_LLD();
    
    //====2015-3-10SLM_init();  
    UAV_CAN_Protocol_Init();
    //----------------------------
    SPI_Init(0x32,0); //32��Ƶ��1M�����ʣ�8bit
    PWM_Init();
    CANBUS_Init();
    SAE_J1939Brodcast_Init();
    LSM303_Initial();
    IMU_Init();

  
}
/*******************************************************************************/
/**
* \brief    Power down interface
* \author   Engineer
* \param    void
* \return   void
*/
void Powerdown_Interface(void)
{
    PowerDown_Counter_Flg = TRUE;//�µ��ʼ��ʱ��־������1����ʼ��ʱ�������㣬��ֹͣ��ʱ 
    Write_Successful_Test();
    vfnDisable_LLD();    
}

/****************************************************************
** ��ֹ���ֵײ���ж�
**
*****************************************************************/

void vfnDisable_LLD(void)
{
     Clock_Disabled();
     SCI_Disabled();
     TimerModule_Disabled();
     vfnInputs_Outputs_Disabled();
}

/*************************************************************
**
**/
void Pre_Start_AD(void)
{
    /* PLL initialization, Bus Clock @ 32MHz */
    vfnClock_Init(); 
    /* Other CPU initalization parameters */
    vfnCpu_init(); 
    vfnADC_Init();  //ADģ���ʼ��
    ENABLE_INTERRUPTS();//ʹ��ȫ���ж�

}

void Check_B_Pwf_LastTime(void)
{}