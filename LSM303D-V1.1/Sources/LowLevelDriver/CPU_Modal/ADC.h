                                                                               /*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       ADC.h
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

#ifndef __ADC_H        /*prevent duplicated includes*/
#define __ADC_H

/*-- Includes ----------------------------------------------------------------*/


/*------s12xs micros---------------------------------------------------------------*/









/*-- Defines -----------------------------------------------------------------*/
/* ADC channels to sample */
#define     ADC_CHANNELS_TO_SAMPLE  8
/* ADC Sample buffer depth per channel */
#define     ADC_SAMPLE_BUFFER_SIZE  16
/*Global ADC engine definitions*/
#define     ADC_CLOCK_FREQ          4000000

/*-- Types Definitions -------------------------------------------------------*/

typedef struct
{
    /* ADC conversion result buffer */
    UINT16 u16Sample[ADC_SAMPLE_BUFFER_SIZE];
}sAnalogDatachannel_t;

extern UINT8 signals_array[];
/*-- Macros ------------------------------------------------------------------*/
#define     ADC_PRESCALER_VALUE     ((BUS_FREQ)/(2*ADC_CLOCK_FREQ)-1)

#define vfn_convertADC_Channel(arg) ATDCTL5_Cx = arg

#define vfnADC_Start_Conversions()   ATDCTL5_Cx = signals_array[0]


#define ADC_INTERRUPT(SELECTOR)  ATDCTL2_ASCIE = SELECTOR

/*-- Function Prototypes -----------------------------------------------------*/

/** ADC Initalization */
void vfnADC_Init(void);

void ADC_Disabled(void);

/*******************************************************************************/

#endif /* __ADC_H */