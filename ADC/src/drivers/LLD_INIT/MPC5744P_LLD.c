/* * MPC5744P_LLD.C
 *
 *  Created on: Jul 27, 2016
 *      Author: B55903
 */

#include "MPC5744P_LLD.h"




extern void MC_MODE_INIT(void);
extern void INTC_Init(void);

void BSP_LowLevelInit(void)
{
    DISABLE_IRQ();

	/* Init MODE ENTRY module */
	MC_MODE_INIT();

	/* Init interrupt controller */
	INTC_Init();

	/* Enable all PBridge Masters for Reads, Writes, and Master Privilege Mode. */
	AIPS_0.MPRA.R = 0x77777777;
	AIPS_1.MPRA.R = 0x77777777;


	/*****************Init LINFLEX1 for UART communication****************/
	SIUL_DigitalOutput(SIUL_PD9, SIUL_ALT2);								//Tx
 	SIUL_DigitalInput(SIUL_PD12, SIUL_IN_PD12, 0, SIUL_ALT2);				//Rx

	LINFLEX_InitUART(LINFLEX_UART_NB, LINFLEX_CLK, LINFLEX_UART_BR);
	LINFLEX_InitRxBuffer(LINFLEX_UART_NB,LINFLEX_UART_RX_BUFFER_SIZE);	//set Rx buffer size to the actual message (frame size)/2



	/****************Init IOs for eEVB test********/
/*
	SIUL_DigitalInputSimple(SIUL_PA5,0);		//SW1
	SIUL_DigitalInputSimple(SIUL_PA6,0);		//SW2
	SIUL_DigitalInputSimple(SIUL_PA7,0);		//SW3
	SIUL_DigitalInputSimple(SIUL_PA8,0);		//SW4
*/
 	SIUL_DigitalIO(SIUL_PD4,0);		//LED1
 	SIUL_DigitalIO(SIUL_PD5,0);		//LED2
 	SIUL_DigitalIO(SIUL_PD6,0);		//LED3
 	SIUL_DigitalIO(SIUL_PD7,0);		//LED4


	/*******Init PIT module**********/
	PIT_Init();
	PIT_Setup(0, 50000000, 0.001);  //PIT CLK=50MHz, interval=1ms
	PIT_EnableInt(0);
	PIT_EnableChannel(0);



	//__init_uart_console();

}
