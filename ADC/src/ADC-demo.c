#include "derivative.h"   /* include peripheral declarations */
#include "MPC5744P_LLD.h"


#define DISABLE_IRQ()               asm("wrteei 0")
#define ENABLE_IRQ()                asm("wrteei 1")


void delay(void);


uint32_t ADC_VALUE0 = 0;
uint32_t ADC_VALUE1 = 1;
uint64_t CAN_Message =0x0;
uint32_t CAN_ID =0x0;
uint16_t u32ADC_Result;                 // ADC Conversion Result
uint16_t u16ADC_Result;

uint32_t count=0;

__attribute__ ((section(".text")))
int main(void)
{

	DISABLE_IRQ();

	/* Init MODE ENTRY module */
	MC_MODE_INIT();

	/* Init interrupt controller */
	INTC_Init();

	/* Enable all PBridge Masters for Reads, Writes, and Master Privilege Mode. */
	AIPS_0.MPRA.R = 0x77777777;
	AIPS_1.MPRA.R = 0x77777777;

	/****************Init IOs for eEVB test********/
	SIUL_DigitalInputSimple(SIUL_PA5,0);		//SW1
	SIUL_DigitalInputSimple(SIUL_PA6,0);		//SW2
	SIUL_DigitalInputSimple(SIUL_PA7,0);		//SW3
	SIUL_DigitalInputSimple(SIUL_PA8,0);		//SW4
 	SIUL_DigitalIO(SIUL_PD4,0);		//LED1
 	SIUL_DigitalIO(SIUL_PD5,0);		//LED2
 	SIUL_DigitalIO(SIUL_PD6,0);		//LED3
 	SIUL_DigitalIO(SIUL_PD7,0);		//LED4


 	/*****************Init ADC0******************/
	ADC_Init(0, ADC_MASK, 0, ONE_SHOT);
	ADC_SetInt(0, EOC_FLAG, ADC_MASK);		//Enable EOC interrupt

 	/*****************Init ADC1 for eEVB test*************/
	ADC_Init(1, 0, CH0Smask, DEFAULT_ADC);

 	ENABLE_IRQ();



	for(;;) {

		SIUL_ToggleIO(SIUL_PD4);


	 /*****************Start Conversion of ADC1******************/
		ADC_StartNormalConversion(1, CH0Smask);
		u32ADC_Result = ADC_GetChannelValue(1, 0);

     /*****************Start Conversion of ADC0******************/
		ADC_StartNormalConversion(0, ADC_MASK);


		delay();


	}

	return 0;
}

/***********delay function*******************/
void delay(void) {
	    unsigned long counter = 0;
	    for(counter=0;counter<1000000;counter++){}
	 	for(counter=0;counter<1000000;counter++){}
	 	for(counter=0;counter<1000000;counter++){}

}


/************following are interrupts*********************/



/************EOC Of ADC0 Interrupt********************/
void ISR496_ADC0_EOC(void) {


	ADC_VALUE0=ADC_GetChannelValue(ADC_NB, 0);
	ADC_VALUE1=ADC_GetChannelValue(ADC_NB, 1);

	ADC_ClearAllEOCflags(0);

}
