/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       IGNSW.c
\brief      Ignition Switch Monitoring.
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\ThirdParty engieer/engieer (lab)
\version    0.2
\date       Aug/ 2008
*/
/*******************************************************************************/

#include "typedefs.h"


static UINT8 u8IGNSW_Collection_Rate_Counter = 0;
static UINT8 u8IGNSW_Buffer_Counter = 0;
UINT8  au8IGNSW_Data_Buffer=0;
UINT8 au8IGNSW_Data_BufferOld=0;
UINT8 u8IGNSW_Counter = 0;
UINT8 u8IGNSW_Filtered = 0;


/** Buffer used to collect Ignition Switch data */

  


extern UINT8 AfterRun_Flg;

extern UINT8 PowerDown_Counter_Flg;
UINT8 Battery_Shortage_Delay=0;

UINT16 uIGNSW;//开关钥匙检测
UINT8 Filter_Counter_Low;
UINT8 Filter_Counter_High;

extern UINT16 u16Current_ISM_Position; 
extern UINT8 B_StepEnabled;
 


static UINT8 TRACT_EN_Collection_Rate_Counter = 0;
static UINT8 TRACT_EN_Buffer_Counter = 0;
UINT8  TRACT_EN_Data_Buffer=0;
UINT8 TRACT_EN_Data_BufferOld=0;
UINT8 TRACT_EN_Counter = 0;
UINT8 TRACT_EN_Filtered = 0;
/*******************************************************************************/
/**
* \brief    Initializations for Ignition Switch Buffer
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnIGNSW_Init(void)
{ 
   /** Initialization of Buffer used to collect Ignition Switch data */
   au8IGNSW_Data_Buffer=0;
   au8IGNSW_Data_BufferOld=0;
   u8IGNSW_Counter=0; 
   u8IGNSW_Filtered=0;
   Filter_Counter_Low=0;
   Filter_Counter_High=0;
   uIGNSW =0; 
}

/*******************************************************************************/
/**
* \brief    Ignition Switch Monitoring periodic rate check and buffer data collection
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnIGNSW_Monitoring(void)
{}

/*******************************************************************************/
/**
* \brief    Filter algorithm of the Ignition Switch data buffer. Updates IGNSW_Filter var.
* \author   OH
* \param    Void
* \return   Void
*/
void vfnIGNSW_Filter(void)
{  
    //========================================
    if(uIGNSW < IGNSW_LOW)//检测钥匙开关是否关闭
    {
        Filter_Counter_Low++;
        Filter_Counter_High = 0;
    }
    else
    {
        Filter_Counter_High++;
        Filter_Counter_Low = 0;
    }

    //=========================================
    if(Filter_Counter_Low >=  DEBOUNCE_TIME)//如果连续检测到钥匙电压低于正常电压，则说明用户关闭钥匙
    {            
        u8IGNSW_Filtered = OFF;
       
    }
    else if(Filter_Counter_High >= DEBOUNCE_TIME)
    {
        u8IGNSW_Filtered = ON;
        //=========================================
        HLS_B_KeyOn= u8IGNSW_Filtered;//应用软件中用到
    }

    if(Filter_Counter_Low >= DEBOUNCE_TIME||Filter_Counter_High >= DEBOUNCE_TIME)
    {             
        Filter_Counter_Low=0;
        Filter_Counter_High =0;
        
        #ifdef PowDownDelay_Disabled
            if(u8IGNSW_Filtered == OFF)//====熄火开关关闭
            {
                //=========要做的事情  第1，断油断火
            }
            else
            {
                //=========要做的事情  第2，恢复供油和点火
            }
        #else
            if(u8IGNSW_Filtered==OFF)//点火开关关闭    
            {               
                if(AfterRun_Flg==OFF)//使能AfterRun()函数，通过将AfterRun_Flg置1完成
                {             
                    //当连续1s检测到电池缺电且点火开关关闭，那么就不是启动过程造成的电池短暂掉电
                    if(HLS_BatteryVol > BATTERY_DIGITAL_6V)
                    {
                         //SCI_Disabled();//禁止SCI模块 2010-11-12
                         AfterRun_Flg = ENABLED;
                         Battery_Shortage_Delay=0;
                         //========================================= 2012-4-20
                         HLS_B_KeyOn= u8IGNSW_Filtered;//应用软件中用到

                         B_StepEnabled = FALSE;

                     }
                     else//电池亏电
                     {
                         Battery_Shortage_Delay++; 
                         if(Battery_Shortage_Delay>=250)//检测到电池电压持续1S钟在8V以下
                         {
                             POWEROFF = LOW;
                         }
                     }
                 }
            }
            else if((AfterRun_Flg>0) && (PowerDown_Counter_Flg==OFF)) 
            {
                AfterRun_Flg = DISABLED;
                Powerdown_Interface();
                KeyOn_Again();//在5S计时内发生Key_Cycle，只需要回写DFLASH数据，不用写tEngOff了，
            }
        #endif    
    }   
} 

//=======================================================
// Check Battery :compare with 11V  >=11V retrun True
//                                  <11V  retrurn False
//=======================================================
UINT8 CompareUbAdcWith11V(void)
{
    return TRUE;
    if(UbAdc >= BATTERY_DIGITAL_11V) return TRUE;
    else return FALSE;   
}

void TRACT_EN_Monitoring(void)
{  

    TRACT_EN_Data_BufferOld = TRACT_EN_Data_Buffer;
    TRACT_EN_Data_Buffer = (UINT8)(TRACT_EN);
  
    if(TRACT_EN_Data_Buffer == TRACT_EN_Data_BufferOld )
    {
        TRACT_EN_Buffer_Counter++;  
    } 
    else
    {
        TRACT_EN_Buffer_Counter = 0;         
    } 

    if(TRACT_EN_Buffer_Counter >= DEBOUNCE_TIME) // #define DEBOUNCE_TIME 4
    {
          TRACT_EN_Buffer_Counter = 0;
          if(TRACT_EN_Data_Buffer)
          {
              B_AsrEn = FALSE;   //反逻辑
          }
          else
          {
              B_AsrEn = TRUE;
          }
    }
         
}


/*******************************************************************************/