                                         /*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       ADC.c
\brief      Analog to Digital Converter Interface functions
\author     COMPANY_XXX
\author     Application Lab
\author     Luis Olea
\version    0.2
\date       November/ 2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "typedefs.h"
/*******************************************************************************/
/* Global ADC status */
UINT8 u8ADC_Status;

/* Analog channels data array */
//sAnalogDatachannel_t au16AnalogSamples[ADC_CHANNELS_TO_SAMPLE];
/* ADC conversion result average */
//UINT16 au16AnalogAverage[ADC_CHANNELS_TO_SAMPLE];
extern  UINT8 signals_array[];
extern  UINT8 signals_pointer;
/*******************************************************************************/
/**
* \brief    ADC initialization
* \author   Engineer
* \param    void
* \return   void
*/
void vfnADC_Init(void)
{

    ATDCTL1_SRES = 0x02; 
          
    /* Discharge capacitor before sampling */
    ATDCTL1_SMP_DIS = 1;       
    
    /* A read access to the result register will cause the associated CCF[n] flag to clear automatically. */
    ATDCTL2_AFFC = 1;      
    
    /* Disable external triggering */
    ATDCTL2_ETRIGE = 0;    
    /* Conversion result right justified */
    ATDCTL3_DJM = 1;       
    /* 1 conversions per sequence  */
    ATDCTL3_S8C = 0;       
    ATDCTL3_S4C = 0;
    ATDCTL3_S2C = 0;
    ATDCTL3_S1C = 1;
    
    
    ATDCTL4_PRS = ADC_PRESCALER_VALUE;
    ATDCTL4_SMP = 0;
    ATDSTAT0_SCF = 1;
    
    /* 切记在写ATDCTL5寄存器之前将初始化工作完成，因为只要写ATDCTL5寄存器就会开始一个新的AD转换序列 */
    ATDCTL5_SCAN = 0;      /* Single conversion sequence */
    ATDCTL5_MULT = 0;      /* Sample one channel */ 
    ATDCTL5_SC   = 0;      /* Special channal conversion enable */
    /* Enable ADC freeze in debug mode = finish current conversion, then freeze */
    //ATDCTL3_FRZ = 0;
  

    ADC_INTERRUPT(ENABLED);  
    vfnADC_Start_Conversions();
}

void ADC_Disabled(void)
{
   ATDCTL1 = 0x2F;
   ATDCTL2 = 0;
   ATDCTL3 = 0x20;
   ATDCTL4 = 0x05;
   ATDCTL5 = 0;
   ADC_INTERRUPT(DISABLED); 
}

/********************************************
**
**强制进行MAP信号采集
********************************************/
void Force_ConvertADC_Map()
{
    ATDCTL5_Cx = signals_array[2];
    signals_pointer = 2;   
}

/*******************************************************************************/

