/*******************************************************************************/
/**
Copyright (c) 
COMPANY_Confidential_Proprietary
\file       Application Definitions.h
\brief      Single header file for the whole application
\author     Guochao
\author     Application Lab
\author     engineer
\version    1.0
\date       2011-8-1
*/

/*******************************************************************************/

//===Idle speed control ========================
//#define Step_ABDC  //�������岽�����������˳��



//====BootLoader Version======================
//#define Bootloader_V40
//#define Bootloader_V51
//#define Bootloader_V54

//====Hardware Version===========================
//#define  LLD_V10_5_2
//#define  LLD_4T1CCD_IA
//#define  LLD_4T2CCD
//#define  LLD_4T2CTH
//#define  LLD_4T2C2IG
//#define  LLD_4T2C1IG
//#define  LLD_4T1CCD_TR
//#define  LLD_4T1CTH_1_1
#define  LLD_4T1CTH_IA_1_2
//#define  LLD_4T1CCD_IA_M1
//#define LLD_4T1CTH_TR2_0M
//#define  LLD_DF4T2C_IA
//#define  LLD_V10_3W_HK
//#define LLD_4T2CCDB_1_1M
//#define LLD_4T2CCDA_1_1M
//#define LLD_4T2CCDA_C_1_0M

#ifdef LLD_4T1CCD_TR
    #define B_AsrEn_True
#endif

#ifdef LLD_4T1CTH_TR2_0M
    #define B_AsrEn_True
#endif



//======���ư汾=======================

//#define NoBatterySystem  //�������ϵͳ
#define CAN_MODULE_ENABLE


//============����Ӧ������Ƿ�ʹ��==========
//#define Enable_Application_Software

//============����Crank�ײ��Ƿ�ʹ��=========
//#define Enable_CrankLLD

//===========ʹ�ܻ��ͱÿ���================
//#define EnableLampControlOilPumpPWM
//===============���ͱö˿�Ԥ����==========
//#define OilPmpPort_Custom1 //====PT4-CH1  PP2-CH2


#define DTC_FlashingCode_En

//#define GuangYinFuelPumpDriverEnable
//#define IdleSolenoidValveDriverEnable

//#define EGT_Enabled //====����EGTģ������

//#define DZ_001//====�ͻ����ư汾  DZ001�������ͻ����ӡRotax 582���������

#define PowDownDelay_Disabled





/*******************************************************************************/
