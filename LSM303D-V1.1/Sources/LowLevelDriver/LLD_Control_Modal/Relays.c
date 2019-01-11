/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Relays.c
\brief      Relays control functions
\author     COMPANY_XXX
\author     Application Lab
\ThirdParty engieer/engieer (lab)
\version    0.1
\date       Jun/ 2008
*/
/*******************************************************************************/

#include "typedefs.h"



UINT8 FuelPumpOnCtr=0;

//=================================================
//
//
//=================================================
void FuelPump_Relay_r20ms(void)
{
    if(HLS_B_PWPumpExist == FALSE)
    {
        ROUT = (HLS_B_Pmp || HLS_Nraw);
    }
}

//=================================================
//
//
//=================================================
void FuelPump_PWM_r1ms(void)
{
 /*   if(HLS_B_PWPumpExist == TRUE)
    {
        FuelPumpOnCtr ++;
        
        if(HLS_tOnPWPump == 0)
        {
            PWMOUT_MOTO = OFF;
        }
        else
        {           
            if(FuelPumpOnCtr >= HLS_tPerPWPump)
            {
                FuelPumpOnCtr = 0;
                PWMOUT_MOTO = ON;
            }
            else if(FuelPumpOnCtr >= HLS_tOnPWPump)
            {
                PWMOUT_MOTO = OFF;
            }
        }           
    }
    */
}   



//=================================================
//
//
//=================================================
void OilPump1_PWM_1ms(void)
{
    static UINT16 Inc_Counter=0;
    UINT16 Local_Freq,Local_Duty;

    Local_Freq = HLS_tOilCyc/10;
    Local_Duty = HLS_tOilOn/50;
    
    if(Local_Freq < Local_Duty || Local_Duty==0)
    {
        OIL_PUMP3 = OFF;
        return;
    }
    //===========================
    Inc_Counter ++;
    if(Inc_Counter >= Local_Freq)
    {
        Inc_Counter = 0;
        OIL_PUMP3 = ON;
        HLS_OilPmpOpenCnt ++;
    }
    else if(Inc_Counter > Local_Duty)
    {
        OIL_PUMP3 = OFF;
    }
}

void OilPump2_PWM_1ms(void)
{
    static UINT16 Inc_Counter=0;
    UINT16 Local_Freq,Local_Duty;

    Local_Freq = HLS_tOilCyc2/10;
    Local_Duty = HLS_tOilOn2/50;
    
    if(Local_Freq < Local_Duty || Local_Duty==0)
    {
        OIL_PUMP4 = OFF;
        return;
    }
    //===========================
    Inc_Counter ++;
    if(Inc_Counter > Local_Freq)
    {
        Inc_Counter = 0;
        OIL_PUMP4 = ON;
        HLS_OilPmpOpenCnt2 ++;
    }
    else if(Inc_Counter >= Local_Duty)
    {
        OIL_PUMP4 = OFF;
    }
}  

//=================================================
//
//舵机控制输出模块
//=================================================
void LLD_ServoCtl_r10ms(void)
{
    if(HLS_VAL_ServoCtlOut_En == FALSE) return;
    SET_PWM_DTY(1,HLS_OnTime_ServoCtlOutPWM);    
}

//=================================================
//
//舵机控制输出模块
//=================================================
void LLD_GearPmpCtl_r20ms(void)
{
  UINT16 freq,duty;
  
  freq = HLS_GearPmpOut_freq;
  duty = HLS_GearPmpOut_duty;
  #ifdef LLD_V10_3W_HK
    SET_PWM_DTY(3,duty);
    SET_PWM_Freq(3,freq);
  #else  
    SET_PWM_DTY(5,duty);
    SET_PWM_Freq(5,freq); 
  #endif     
}