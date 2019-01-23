/*
  * PIT_IRQ.c
 *
 *  Created on: Jul 27, 2016
 *      Author: B55903
 */

#include "derivative.h"
#include "PIT_IRQ.h"
#include "PIT.h"
#include "Defines.h"
#include "PwSBC.h"
#include "SIUL.h"

unsigned int count_c1=0;
unsigned int count_c2=0;


void ISR226_PIT_CH0(void) {

	SIUL_ToggleIO(SIUL_PD5);

	PIT_ClearFlag(PIT_WD_CH);

}



void ISR36_STM0_CH0(void)
{

    SIUL_ToggleIO(SIUL_PD6);

	//STM_0.CR.R = 0x0000C700;
	STM_0.CHANNEL[0].CMP.R += u32Stm0Ch0PeriodTicks;	//set comparator for next event
	STM_0.CHANNEL[0].CIR.R = 1;		//clear STM1_CH0 flag;
	//STM_0.CR.R = 0x0000C701;
}
