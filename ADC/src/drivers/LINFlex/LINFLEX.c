/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       LINFLEX.c$
* @file             LINFLEX.c
*
* $Date:            Jul-24-2014$
* @date             Jul-24-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      LINFLEX driver source file
* @brief            LINFLEX driver source file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage LINFLEX driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains LINFLEX driver for MPC5744P allowing to 
*	initialize and configure LINFLEX module for LIN or UART transfers.
*
*  The key features of this package are the following:
*  - Initialize/configure LINFLEX module for LIN transfers
*  - Initialize/configure LINFLEX module for UART transfers
*  - Send/receive basic LIN frames
*  - Send/receive basic UART frames
*  For more information about the functions and configuration items see these documents: 
*
*******************************************************************************
*
* @attention 
*            
*******************************************************************************/
/*==================================================================================================
*   Project              : PowerSBC
*   Platform             : MPC5744P
*   Dependencies         : MPC5744P - Basic SW drivers.
*   All Rights Reserved.
==================================================================================================*/

/*==================================================================================================
Revision History:
                             Modification     Function
Author (core ID)              Date D/M/Y       Name		  Description of Changes
B35993		 				  24/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#include "Defines.h"
#include "EXTGLOBALS.h"
#include <math.h>
#include "LINFLEX.h"
#include "SIUL.h"

volatile struct LINFlexD_tag *LINFLEX[2] = {&LINFlexD_0, &LINFlexD_1};

/***************************************************************************//*!
*   @brief The function LINFLEX_ChangeBaudRate changes a baud rate to the 
*			desired one (if the value is in the specified range).
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function computes settings of LINIBRR and LINFBRR registers 
*					for a specified LINFlex module (nbLINFlex) with respect to 
*					a system clock (sysClk) and desired baud rate (baudRate).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] sysClk
*					System clock frequency [Hz].
*	@param[in] baudRate
*					Desired baud rate [b/s]. Maximal and minimal baud rate 
*						depend on the actual system clock frequency and on the 
*						limits of LINIBRR and LINFBRR registers. *						
*	@remarks 	If an internal RC oscillator is used as a system clock, then its 
*				calibration is recommended before use of LINFlex module (see 
*				calibrateRC function for details). Value obtained from the 
*				calibration should be directly added in the floating point format
*				as a parameter to the LINFLEX_InitUART function. If the calibration 
*				will not be done, bus timing with RC oscillator should not be exact 
*				and communication shall generate errors. LINFlex module should be 
*				activated before use of this function (see LINFLEX_InitUART function 
*				for details).
*	@par Code sample1
*			LINFLEX_ChangeBaudRate(1, 40000000.0, 600);
*			- Command changes content of the LINFlex1 registers (LINIBRR, LINFBRR) 
*			to set up baud rate 600 b/s with respect to the 40 MHz clock frequency. 
*			In this case an XTAL oscillator is used.
*	@par Code sample2		
*			LINFLEX_ChangeBaudRate(1, RCfrequency, 19200);
*			- Command changes content of the LINFlex1 registers (LINIBRR, LINFBRR) 
*			to set up baud rate 19200 b/s with respect to the real frequency of 
*			RC oscillator. RCfrequency parameter is a real frequency of RC 
*			oscillator obtained from its previous calibration.
********************************************************************************/
void LINFLEX_ChangeBaudRate(vuint8_t nbLINFlex, double sysClk, uint32_t baudRate){
	double LFDIVvalue = 0;
	double fractionalPart = 0;
	uint32_t integerPart = 0;
	uint32_t fractionalPartRounded = 0;
	
	LFDIVvalue = sysClk/(16.0*baudRate);
	
	
	integerPart = floor(LFDIVvalue);										//to get the integer part
	fractionalPart = LFDIVvalue - floor(LFDIVvalue);		//to get only the fractional part
	fractionalPart*=16;
	fractionalPartRounded = round(fractionalPart);
	
	LINFLEX[nbLINFlex]->LINFBRR.R = fractionalPartRounded;
	LINFLEX[nbLINFlex]->LINIBRR.R = integerPart;
	
}

/***************************************************************************//*!
*   @brief The function LINFLEX_ConfigurePads configures the I/O pads used for 
*			communication.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function is used by the init function to configure LINFLex 
*					I/O pins (Rx and Tx). Default pin mapping is used, but can 
*					be changed directly in the function.			
*					Default pin mapping:
*					- LINFLEX0 TxD = PB2 / RxD = PB7
*					- LINFLEX1 TxD = PD9 / RxD = PB13
*	@param[in] nbLINFlex
*				Number of LINFlex module (0 or 1).
*	@remarks 	This function is used only once by the initialization function 
*				(LINFLEX_InitUART) so in standard operation user does not 
*				need to use it directly. LINFlex module should be activated 
*				before use of this function (see LINFLEX_InitUART function for 
*				details).
*	@par Code sample
*			LINFLEX_ConfigurePads(0);
*			- Command configures I/O pads as Rx/Tx for LINFLex0.
********************************************************************************/
void LINFLEX_ConfigurePads(vuint8_t nbLINFlex)
{

	if(nbLINFlex == 0)							//LINFLEX_0					
	{
			SIUL_DigitalOutput(SIUL_PB2, SIUL_ALT1);                   			 	// Tx
            SIUL_DigitalInput(SIUL_PB3, SIUL_IN_PB3, 0, SIUL_ALT1);     			// Rx	

	}else{										//LINFLEX_1
			SIUL_DigitalOutput(SIUL_PD9, SIUL_ALT2);								//Tx 
	 		SIUL_DigitalInput(SIUL_PD12, SIUL_IN_PD12, 0, SIUL_ALT2);				//Rx			
	}
}


/***************************************************************************//*!
*   @brief The function LINFLEX_Sleep requests the sleep mode for the LINFlex module.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function requests Sleep mode by setting SLEEP bit in the 
*					LINCR1 register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	Sleep mode should be activated when LINFlex module is not 
*				currently in use to decrease consumption. LINFlex module should 
*				be activated before use of this function (see LINFLEX_InitUART 
*				function for details).
*	@par Code sample
*		LINFLEX_Sleep(1);
*		- Requests Sleep mode for LINFlex1.
********************************************************************************/
void LINFLEX_Sleep(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->LINCR1.B.SLEEP = 1; // Request sleep mode 
}

/***************************************************************************//*!
*   @brief The function LINFLEX_WakeUp wakes-up the LINFlex module from the 
*			Sleep mode.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function wakes up specified LINFlex module from Sleep mode 
					by clearing SLEEP bit in LINCR1 register.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_WakeUp(0);
*			- Wakes up LINFlex0 from Sleep mode.
********************************************************************************/
void LINFLEX_WakeUp(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->LINCR1.B.SLEEP = 0;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_DisableTxUART disables UART's transmitter.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function disables UART transmitter for specified LINFlex 
*					module by clearing TXEN bit in UARTCR register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_DisableTxUART(1);
*			- Command disables UART transmitter of LINFlex1.
********************************************************************************/
void LINFLEX_DisableTxUART(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->UARTCR.B.TxEn = 0;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_DisableRxUART disables UART's receiver.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function disables UART receiver for specified LINFlex module
*					by clearing RXEN bit in UARTCR register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_DisableRxUART(0);
*			- Command disables UART receiver of LINFlex0.
********************************************************************************/
void LINFLEX_DisableRxUART(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->UARTCR.B.RxEn = 0;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_EnableTxUART enables UART's transmitter.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function enables UART transmitter for specified LINFlex 
*					module by setting TXEN bit in UARTCR register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_EnableTxUART(1);
*			- Command enables UART transmitter of LINFlex1.
********************************************************************************/
void LINFLEX_EnableTxUART(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->UARTCR.B.TxEn = 1;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_EnableRxUART enables UART's receiver.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function enables UART receiver for specified LINFlex module 
*					by setting RXEN bit in UARTCR register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_EnableRxUART(0);
*			- Command enables UART receiver of LINFlex0.
********************************************************************************/
void LINFLEX_EnableRxUART(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->UARTCR.B.RxEn = 1;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_EnableInt enables LINFlex interruptions.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function enables all interrupt flags (in the LINIER register) 
*					associated with the specified LINFlex module.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*			LINFLEX_EnableInt(1);
*			- Command enables all interrupts for LINFlex1.
********************************************************************************/
void LINFLEX_EnableInt(vuint8_t nbLINFlex)
{
	//LINFLEX[nbLINFlex]->LINIER.B.DTIE = 1; 	//Enable data transmission interrupt 
	LINFLEX[nbLINFlex]->LINIER.B.DRIE = 1; 		//Enable data reception interrupt 
	LINFLEX[nbLINFlex]->LINIER.B.SZIE = 1;		//Stuck at Zero Interrupt Enable
	LINFLEX[nbLINFlex]->LINIER.B.OCIE = 1;		//Output Compare Interrupt Enable
	LINFLEX[nbLINFlex]->LINIER.B.FEIE = 1;		//Framing Error Interrupt Enable
	LINFLEX[nbLINFlex]->LINIER.B.BOIE = 1;		//Framing Error Interrupt Enable
}


/***************************************************************************//*!
*   @brief The function LINFLEX_InitUART initializes the UART module.
*	@par Include 
*					DSPI.h
* 	@par Description 
* 		This function initializes the LINFlex module specified by the index 
*		(nbLINFlex) for UART communication. On the beginning, the input and output pins 
*		are initialized (using configurePadsLINFlex function), then the main 
*		LINFlex registers are configured, the baud rate is computed and set 
*		(using changeBaudRateLINFlex function), and the input (receiver) buffer 
*		is initialized to the size of four bytes. Communication has the 
*		following parameters by default: no parity, one stop bit, and 8-bit data 
*		word. 
*	@param[in] nbLINFlex 
*					Number of LINFlex module (0 or 1).
*	@param[in] sysClk
*					System clock sysClk [Hz].
*	@param[in] baudRate
*					Desired baud rate [b/s]. Maximal and minimal baud 
*							rate depends on the actual system clock sysClk and 
*							on the limits of the LINIBRR and LINFBRR registers 
*							(for additional information see 
*							LINFlex_ChangeBaudRate function).
*	@remarks 	Calibration is recommended if an internal RC oscillator is used 
*				as a system clock.
*	@par Code sample1
*			LINFLEX_UART_Init(1, 40000000.0, 600);
*			- Command initializes UART module no. 1 with respect to the 40 MHz 
*			system clock sysClk and the desired baud rate 600 b/s.
*	@par Code sample2
*			LINFLEX_UART_Init(0, 40000000.0, 115200);
*			- Command initializes UART module no. 0 with respect to the 40 MHz 
*			system clock sysClk and the desired baud rate 115 200 b/s.		
********************************************************************************/
void LINFLEX_InitUART(vuint8_t nbLINFlex, double sysClk, uint32_t baudRate)
{

	LINFLEX_ConfigurePads(nbLINFlex);
	
	LINFLEX_WakeUp(nbLINFlex);

	LINFLEX[nbLINFlex]->LINCR1.B.INIT = 1; // enter initialization mode 

	LINFLEX_EnableInt(nbLINFlex);


	LINFLEX[nbLINFlex]->UARTCR.B.UART = 1;		//0=LIN 	 1=UART
	LINFLEX[nbLINFlex]->UARTCR.B.PCE = 0;			//0 = parity disabled, 1 = parity enabled
	LINFLEX[nbLINFlex]->UARTCR.B.PC0 = 0;			//0 = even parity, 1 = odd parity
	LINFLEX[nbLINFlex]->UARTCR.B.WL0 = 1;			//0 7-bit data + parity bit *** 1 8-bit data (or 9-bit if PCE is set).

	LINFLEX[nbLINFlex]->UARTCR.B.TxEn = 1;
	LINFLEX[nbLINFlex]->UARTCR.B.RxEn = 1;

	LINFLEX_ChangeBaudRate(nbLINFlex, sysClk, baudRate);
	
	LINFLEX_InitRxBuffer(nbLINFlex,4);


	LINFLEX[nbLINFlex]->UARTSR.B.DRFRFE = 1; // clear DRF flag (Data Reception Complete Flag)
	LINFLEX[nbLINFlex]->UARTSR.B.DTFTFF = 1; // clear DTF flag (Data Transmission Complete Flag)
	LINFLEX[nbLINFlex]->LINCR1.B.INIT = 0; // enter normal mode 

}

/***************************************************************************//*!
*   @brief The function LINFLEX_InitRxBuffer initializes and changes size of 
*			the input buffer.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function initializes size of the input (reception) buffer. 
*					By default this function is used during init phase, where the 
*					buffer is initialized to a size of 4 Bytes (32 bits).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] nbBytes
*					Preferred size of reception buffer in Bytes. In UART 
*					mode minimal size of the buffer is 1, maximal 4 Bytes.
* 	@remarks The size of the input buffer affirms when a Data Reception 
*				Completed Flag (DRF) sets. The flag sets only when the input buffer is 
*				full (received data is equal to its size). The LINFlex module should be 
*				activated before using this function (see LINFLEX_InitUART function for 
*				details). 
*	@par Code sample
*			LINFLEX_InitRxBuffer(0, 4);	
*			- Size of input buffer of the LINFlex0 module will be set to 4 Bytes.
********************************************************************************/
void LINFLEX_InitRxBuffer (vuint8_t nbLINFlex, int8_t nbBytes)
{
	LINFLEX[nbLINFlex]->UARTCR.B.RDFL_RFC = nbBytes-1; 	//can be programmed only once UART bit is set 
}

/***************************************************************************//*!
*   @brief The function LINFLEX_SendUART sends a data packet through the UART.
*	@par Include 
*					DSPI.h
* 	@par Description 
* 			This function sends n data Bytes through the specified LINFLex UART 
*			module. It sets the output buffer size, reads the data from the location 
*			specified by a pointer (p_tx), and then waits for the end of 
*			transmission (indicated by a DTF - Data Transmission Completed Flag). 
*			The DTF flag is cleared to prepare for the next operation. 
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] p_tx
*					Pointer to the data to be sent. 
*	@param[in] nbBytes
*					Defines how many Bytes of data are given to be sent. 
*	@remarks 	Data should be organized e.g. in an array of Bytes and p_tx 
*				should contain address of the first item. Data Bytes will be 
*				sent in the same order as they are stocked in the memory. LINFlex 
*				module should be activated before use of this function (see 
*				LINFLEX_InitUART function for details).
*	@par Code sample	 
*				</para>
*			uint8_t data[4];						</para>
*			data[0] = 'E';							</para> 
*			data[1] = 'a';							</para>
*			data[2] = 's';							</para>
*			data[3] = 'y';							</para>
*			LINFLEX_InitUART(1, 40000000.0, 600);	</para>
*			LINFLEX_SendUART (1, &data[0], 4);		</para>
*			- This sample of code will send a word ("Easy") via LINFlex1 UART. 
*			Data bytes will be sent in the same order as they are in the memory 
*			(first sent will be letter "E").
********************************************************************************/
void LINFLEX_SendUART (vuint8_t nbLINFlex, uint8_t* p_tx, uint8_t nbBytes)
{	

	uint32_t responseL=0;

	while((LINFLEX[nbLINFlex]->LINSR.B.LINS != 2) && (LINFLEX[nbLINFlex]->LINSR.B.LINS != 0)){ };		//waiting for IDLE or SLEEP mode

	LINFLEX[nbLINFlex]->UARTCR.B.TDFL_TFC = nbBytes-1;

	if (nbBytes == 1)
	{
		responseL = p_tx[0];
	}
	else if (nbBytes == 2)
	{
		responseL = p_tx[0] | (p_tx[1] << 8);
	}
	else if (nbBytes == 3)
	{
		responseL = p_tx[0] | (p_tx[1] << 8) | (p_tx[2] << 16);		
	}
	else if (nbBytes == 4)
	{
		responseL = p_tx[0] | (p_tx[1] << 8) | (p_tx[2] << 16) | (p_tx[3] << 24);
	}

	LINFLEX[nbLINFlex]->BDRL.R = responseL;
	while(LINFLEX[nbLINFlex]->UARTSR.B.DTFTFF!=1){}
	LINFLEX[nbLINFlex]->UARTSR.B.DTFTFF=1;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_ReadUART reads the received data from the 
*			UART buffer.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function reads specified length of received data from input 
*					buffer and stores them in memory allocated by a user. Memory 
*					must be accessible using a pointer (response).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] nbBytes
*					Length of data to be read from input buffer.
*	@param[out] response
*					Pointer to the beginning of data block, where received 
*							data will be stored. Data block must be allocated 
*							before (e.g. Byte array should be used).
*	@remarks 	Function should be used when the data is available e.g. in an 
*				interruption routine or just simply by testing a flag as shown 
*				in the example below. Data will be stored in the memory in the 
*				same order as they arrived. LINFlex module should be activated 
*				before use of this function (see LINFLEX_InitUART function for 
*				details).
*	@par Code sample
*			</param>
*		uint8_t data[4];								</param>	
*		LINFLEX_InitUART(1, 40000000.0, 600);			</param>									
*		while(LINFLEX_GetReceiveFlagUART(1)==0);  		</param>
*		LINFLEX_ReadUART (1, 4, &data[0]);				</param>
*		LINFLEX_ClearReceiveFlagUART(1);				</param>
*		- This sample of code will wait for input data (4 Bytes). When data 
*		arrives (indicated by Data Reception Completed Flag - DRF), data will 
*		be read, stored in data array and receive flag will be cleared.
********************************************************************************/
void LINFLEX_ReadUART (vuint8_t nbLINFlex, int8_t nbBytes, uint8_t* response)
{
	uint32_t responseL = 0;
	uint32_t responseM = 0;
	int8_t index;

	responseL = LINFLEX[nbLINFlex]->BDRL.R;
	responseM = LINFLEX[nbLINFlex]->BDRM.R;

	for (index=0;index<nbBytes;index++)															
	{
		if(index<4) *(response+index) = (int8_t) ( responseM >> (8*index) );
		else *(response+index) = (int8_t) ( responseL  >> (8*(index-4)));
	}
}

/***************************************************************************//*!
*   @brief The function LINFLEX_GetReceiveFlagUART returns the UART's reception flag.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function returns DRF - Data Reception Completed Flag from 
*					UARTSR register. This should be e.g. used simply in while 
*					cycle to wait for available data.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@return Function returns DRF - Data Reception Completed Flag.
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitUART function for details).
*	@par Code sample
*		while(LINFLEX_GetReceiveFlagUART(1)==0);  
*		- Command simply waits for received data on LINFlex1. If the data 
*		arrives program will continue in its execution.
********************************************************************************/
uint32_t LINFLEX_GetReceiveFlagUART(vuint8_t nbLINFlex)
{
	return LINFLEX[nbLINFlex]->UARTSR.B.DRFRFE;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_ClearReceiveFlagUART clears the UART's reception flag.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function clears DRF (Data Reception Completed Flag) and 
*					RMB (Release Message Buffer) in UARTSR register.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	Function should be used everytime after data read (after 
*				LINFLEX_GetReceiveFlagUART function) to clear input buffer 
*				and to prepare receiver for new data. LINFlex module should be 
*				activated before use of this function (see LINFLEX_InitUART 
*				function for details).
*	@par Code sample
*		LINFLEX_ClearReceiveFlagUART(0);
*		- Command clears DRF and RMB flag bits for LINFlex0.
********************************************************************************/
void LINFLEX_ClearReceiveFlagUART(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->UARTSR.B.DRFRFE = 1;
	LINFLEX[nbLINFlex]->UARTSR.B.RMB = 1;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_EnableDRFint enables an interrupt activated 
*			when the data is received.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function enables interrupt on the reception 
*					(DRIE - Data Reception Complete Interrupt Enable).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
*	@par Code sample
*			LINFLEX_EnableDRFint(0);
*			- Command enables interrupt on the reception for the LINFLEX no. 0.
********************************************************************************/
void LINFLEX_EnableDRFint(vuint8_t nbLINFlex){
		LINFLEX[nbLINFlex]->LINIER.B.DRIE = 1; 				// enable data reception interrupt 
}

/***************************************************************************//*!
*   @brief The function LINFLEX_GetParityErrorUART checks if an error in the 
*			parity has been detected.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function returns PE - Parity Error Flags Rx.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@return 	Function returns four parity error flags in one register.
*	@remarks 	All four Parity Error flags PE3, PE2, PE1, PE0 are returned in 
*				one register. PE0 is placed on the least significant bit.
*	@par Code sample
*			error = LINFLEX_GetParityErrorUART(1);
*			- Command returns state of parity bits for all received Bytes in 
*			the LINFLEX module no. 1 and stores it in the error variable.
********************************************************************************/
uint32_t LINFLEX_GetParityErrorUART(vuint8_t nbLINFlex){						//check parity errors in all receiver bytes	
	return (LINFLEX[nbLINFlex]->UARTSR.B.PE);									//if PE == 0 -> NO error, if PE > 0 -> error
}

/***************************************************************************//*!
*   @brief The function LINFLEX_ClearParityError clears the parity error flag.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function clears all PE - Parity Error Flags.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@remarks 	All four Parity Error flags PE0, PE1, PE2, PE3 are cleared in 
*				the same time.
*	@par Code sample
*			LINFLEX_ClearParityError(0);
*			- Command clears all parity flags in the PE register for module no.0.	
********************************************************************************/
void LINFLEX_ClearParityError(vuint8_t nbLINFlex){
	LINFLEX[nbLINFlex]->UARTSR.B.PE = 0xFF;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_IsIdle checks whether module is in the IDLE 
*			state or not.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function checks if the LINFlex module is in IDLE state.
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@return Returns 1 if the LINFlex module is id IDLE state, otherwise 0.
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
*	@par Code sample
*			LINFLEX_IsIdle(1);
*			- Command returns 1 if the UART of the LINFLEX1 is in the IDLE state. 
********************************************************************************/
uint32_t LINFLEX_IsIdle(vuint8_t nbLINFlex){			//function returns 1 if UART is in IDLE state (NOT transmitting/receiving)
	if(LINFLEX[nbLINFlex]->LINSR.B.LINS == 2){				
		return (1);																	//in IDLE state
	}
	else{
		return(0);																	//NOT in IDLE state
	}
	
}


/***************************************************************************//*!
*   @brief The function LINFLEX_InitLIN initializes the LIN module.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function initializes LINFlex module specified by index 
*					(nbLINFlex) for LIN communication. On the beginning input 
*					and output pins are initialized (using LINFLEX_ConfigurePads 
*					function), then main LINFlex registers are configured, baud 
*					rate is computed and set (using LINFLEX_ChangeBaudRate function). 
*					Module will be set into a Master or Slave mode (mode parameter).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] sysClk
*					System clock sysClk [Hz].
*	@param[in] baudRate
*					Desired baud rate [b/s]. Maximal and minimal baud rate 
*					depends on the actual system clock sysClk and on the 
*					limits of the LINIBRR and LINFBRR registers (for 
*					additional information see LINFlex_ChangeBaudRate 
*					function).
*	@param[in] mode
*				Desired mode - Master or Slave.
*				Predefined values:
*				- "MASTER" - LIN will be a Master	
*				- "SLAVE" - LIN will be a Slave	
*	@remarks 	If internal RC oscillator is used as a system clock, then its 
*				calibration is recommended (see calibrateRC function for details). 
*				Then the value obtained from the calibration should be directly 
*				added in the floating point format as a parameter of the 
*				LINFLEX_UART_Init function. This will allow init function to 
*				compute baud rate registers more precisely.
*	@par Code sample1
*			LINFLEX_InitLIN(1, 40000000.0, 600, MASTER);	
*			Command initializes LIN module no. 1 as a Master with respect to 
*			the 40 MHz system clock sysClk and the desired baud rate 600 b/s. 	
*	@par Code sample2
*			LINFLEX_InitLIN(0, 40000000.0, 115200, SLAVE);	
*			Command initializes LIN module no. 0 as a Slave with respect to 
*			the 40 MHz system clock sysClk and the desired baud rate 115
*			200 b/s.	
********************************************************************************/
void LINFLEX_InitLIN(vuint8_t nbLINFlex, double sysClk, uint32_t baudRate, uint8_t mode)
{

	LINFLEX_ConfigurePads(nbLINFlex);
	
	LINFLEX_WakeUp(nbLINFlex);

	LINFLEX[nbLINFlex]->LINCR1.B.INIT = 1; // enter initialization mode 
	LINFLEX[nbLINFlex]->LINCR1.B.MBL = 3;	//Master break length set to 13-bit
	LINFLEX[nbLINFlex]->LINCR1.B.BF = 0;	//Bypass filter -> no interrupt if ID does not match any filter
	LINFLEX[nbLINFlex]->LINCR1.B.MME = mode;	//1 -> Master, 0 -> Slave
	LINFLEX[nbLINFlex]->LINTCSR.B.IOT = 0;	//LIN state machine does not reset to Idle on timeout event
	
	LINFLEX_EnableInt(nbLINFlex);

	LINFLEX[nbLINFlex]->LINCR1.B.BF = 1;
	LINFLEX[nbLINFlex]->LINCR2.B.IOBE = 0;
	LINFLEX[nbLINFlex]->LINCR2.B.IOPE = 0;
	LINFLEX[nbLINFlex]->LINCR1.B.CCD = 0;
	LINFLEX[nbLINFlex]->LINCR1.B.CFD = 0;

	LINFLEX[nbLINFlex]->UARTCR.B.UART = 0;	//0=Lin
	
	LINFLEX_ChangeBaudRate(nbLINFlex, sysClk, baudRate);

	LINFLEX[nbLINFlex]->LINCR1.B.INIT = 0; // enter normal mode 

}

/***************************************************************************//*!
*   @brief The function LINFLEX_SendFrameLIN sends a full LIN frame (header + data).
*	@par Include 
*					DSPI.h
* 	@par Description 
*			LINFLEX_SendFrameLIN sends a full LIN frame (header + data) via the LIN 
*			if configured as a Master. Two associated registers (BDRL and BDRM) are 
*			fed from the memory (beginning specified by p_tx pointer). The ID is 
*			modified with the data length (coded on two bits as shown below) and BIDR register is set. Next, the frame is 
*			sent by setting the HTRQ bit in the LINCR2 register (up to 8 data Bytes 
*			should be sent in a one frame). The function waits for the end of data 
*			transmission (DTF flag in LINSR register), then clears the flag and 
*			returns. Depending on bit2 and 3, the data frame length is defined as 
*			follows: 
*					- "00" - 1 Byte
*					- "01" - 2 Bytes
*					- "10" - 4 Bytes
*					- "11" - 8 Bytes
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] p_tx
*					Pointer to the data to be sent. 
*	@param[in] nbBytes
*					Defines how many Bytes of data are given to be sent. 
*	@param[in] ID
*					Header frame identifier (from 0 up to 15). Header frame 
*					is normally coded on 6 bits, which means 64 possible 
*					combinations divided into 4 classes. Then 4 bits mean 
*					identifier number and 2 bits number of data Bytes (see 
*					the image above). Exceptional are identifiers from 0x3C 
*					till 0x3F (see LIN specification for details).
*	@remarks 	Data should be organized e.g. in an array of Bytes and p_tx 
*				should contain address of the first item. Data Bytes will be
*				sent in the same order as they are stocked in the memory. 
*				Sending a full frame is possible only if LINFlex module is 
*				configured as a Master. LINFlex module should be activated 
*				before use of this function (see LINFLEX_InitLIN function for 
*				details).
*	@par Code sample
*				</para>
*			uint8_t p_array[8];											</para>
*			p_array[0] = 'H';											</para>
*			p_array[1] = 'e';											</para>					
*			p_array[2] = 'l';											</para>
*			p_array[3] = 'l';											</para>
*			p_array[4] = 'o';											</para>
*			p_array[5] = '!';											</para>
*			p_array[6] = '!';											</para>
*			p_array[7] = '!';											</para>
*			LINFLEX_InitLIN(0,40000000,19200,MASTER);					</para>
*			LINFLEX_SendFrameLIN (0, (uint8_t*)&p_array, 0x08, 0x02);	</para>
*			This sample of code will send a word ("Hello!!!") via LIN bus 
*			connected to LINFlex0 module. Data bytes will be sent in the same 
*			order as they are in the memory (first sent will be letter "H").	
********************************************************************************/
void LINFLEX_SendFrameLIN (vuint8_t nbLINFlex, uint8_t* p_tx, uint8_t nbBytes, uint8_t ID)
{	
//sends complete LIN frame on Master => header + data
	uint32_t responseL=0;
	uint32_t responseH=0;

	if (nbBytes == 1)
	{
		responseL = p_tx[0];
	}
	else if (nbBytes == 2)
	{
		responseL = p_tx[0] | (p_tx[1] << 8);
	}
	else if (nbBytes == 3)
	{
		responseL = p_tx[0] | (p_tx[1] << 8) | (p_tx[2] << 16);//(uint32_t) p_tx[0] + ( ((uint32_t)p_tx[1]) * 256) + ( ((uint32_t)p_tx[2]) * 65536);
	}
	else if (nbBytes >= 4)
	{
		responseL = p_tx[0] | (p_tx[1] << 8) | (p_tx[2] << 16) | (p_tx[3] << 24);
	}	
	if (nbBytes == 5)
	{
		responseH = p_tx[4];
	}
	else if (nbBytes == 6)
	{
		responseH = p_tx[4] | (p_tx[5] << 8);
	}
	else if (nbBytes == 7)
	{
		responseH = p_tx[4] | (p_tx[5] << 8) | (p_tx[6] << 16);//(uint32_t) p_tx[0] + ( ((uint32_t)p_tx[1]) * 256) + ( ((uint32_t)p_tx[2]) * 65536);
	}
	else if (nbBytes == 8)
	{
		responseH = p_tx[4] | (p_tx[5] << 8) | (p_tx[6] << 16) | (p_tx[7] << 24);
	}
	

	LINFLEX[nbLINFlex]->BDRL.R = responseL;
	LINFLEX[nbLINFlex]->BDRM.R = responseH;
	
	switch(nbBytes){												//number of data Bytes will be included into the IDentifier
		case 2 : ID = 0x20 | ID; break; //0b10_0000 | ID; break;
		case 4 : ID = 0x10 | ID; break; //0b01_0000 | ID; break;
		case 8 : ID = 0x30 | ID; break; //0b11_0000 | ID; break;	
	}
	

	LINFLEX[nbLINFlex]->BIDR.R = ((nbBytes - 1) << 10) | (1 << 9)  | (0 << 8) | ID;			//DIR - transmit, CCS - enhanced checksum
	
	LINFLEX[nbLINFlex]->LINCR2.B.HTRQ = 1;    // TEST PROC posilz i DATA a ne jenom HEADER??????????????????????????????????????????????????????????????

    	while(LINFLEX[nbLINFlex]->LINSR.B.DTF!=1){}
	LINFLEX[nbLINFlex]->LINSR.B.DTF=1;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_SendHeaderLIN sends a LIN header.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function sends LIN frame header if configured as a Master. 
*					At first ID is modified to take into account number of data 
*					Bytes that will follow in the frame (coded on two bits, see 
*					the previous LINFLEX_SendFrameLIN function for details). Then 
*					BIDR register is fed up with the transfer parameters/ID and 
*					Header Transmission is requested (HTRQ bit in LINCR2 register).
*	@param[in] nbLINFlex
*					Number of LINFlex module (0 or 1).
*	@param[in] nbBytes
*					Defines how many Bytes of data are given to be sent. 
*	@param[in] ID
*					Header frame identifier (from 0 up to 15). Header frame is 
*					normally coded on 6 bits, which means 64 possible combinations 
*					divided into 4 classes. Then 4 bits mean identifier number 
*					and 2 bits number of data Bytes (see the image above). 
*					Exceptional are identifiers from 0x3C till 0x3F (see LIN 
*					specification for details).
*	@remarks 	Sending a full frame is possible only if LINFlex module is 
*				configured as a Master. LINFlex module should be activated 
*				before use of this function (see LINFLEX_InitLIN function for 
*				details).
*	@par Code sample
*				</param>
*			LINFLEX_InitLIN(0,40000000,19200,MASTER);	</param>	
*			LINFLEX_SendHeaderLIN(0, 0x08, 0x02);		</param>
*			- This sample of code will send a header with ID 0x02 via the 
*			LINFlex0 module.	
********************************************************************************/
void LINFLEX_SendHeaderLIN (vuint8_t nbLINFlex, uint8_t nbBytes, uint8_t ID)
{	
	//sends only LIN header on Master
		switch(nbBytes){												//number of data Bytes will be included into the IDentifier
		case 2 : ID = 0x20 | ID; break; //0b10_0000 | ID; break;
		case 4 : ID = 0x10 | ID; break; //0b01_0000 | ID; break;
		case 8 : ID = 0x30 | ID; break; //0b11_0000 | ID; break;	
	}
	
	LINFLEX[nbLINFlex]->BIDR.R = (1 << 9) | ID;		//DIR - transmit, CCS - enhanced checksum
	
	LINFLEX[nbLINFlex]->LINCR2.B.HTRQ = 1;    //requests LIN header transmit
}

/***************************************************************************//*!
*   @brief The function LINFLEX_SendWordUART sends a word via UART.
*	@par Include: 
*					LINFLEX.h
* 	@par Description: 
*					This function sends a word consisted of several Bytes via UART.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@param[in] p_string -  Pointer to the array of Bytes to be sent.
*	@param[in] length -  Number of Bytes to be sent.
*	@remarks 	Function blocks UART as a resource, this could block execution 
*				of the main routines if longer frames are sent.
********************************************************************************/
void LINFLEX_SendWordUART(vuint8_t nbLINFlex, uint8_t* p_string, uint8_t length){
	int i = 0;
	unsigned char data[4];
	uint32_t stockPriority = 0;
	stockPriority = INTC_0.CPR0.B.PRI;		//save current priority
	INTC_0.CPR0.B.PRI = INT_CEIL_UART_PRIORITY;	//block UART resource
	
	for(i=0;i<length;i+=4){
		data[0] = p_string[i];
		if(length > (i+1)){
			data[1] = p_string[i+1];
			if(length > (i+2)){
				data[2] = p_string[i+2];
					if(length > (i+3)){
						data[3] = p_string[i+3];
						LINFLEX_SendUART(nbLINFlex,data,4);
					}else
					{
						LINFLEX_SendUART(nbLINFlex,data,3);	
					}
					
			}else
			{
				LINFLEX_SendUART(nbLINFlex,data,2);
			}
			
		}else
		{
			LINFLEX_SendUART(nbLINFlex,data,1);
		}
			
	}
	
	INTC_0.CPR0.B.PRI = stockPriority;			//release UART resource
}



/***************************************************************************//*!
*   @brief The function LINFLEX_ReadLIN reads data previously received via LIN.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function reads data previously received via LIN.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@param[in] nbBytes - Defines how many Bytes of data are given to be read.
*	@param[out] response -  Pointer to data memory, where the result will be 
*							stored. Data memory has to be allocated before 
*							use of this function.
*	@remarks 	Function should be used only if data is available in the 
*				input buffer (see LINFLEX_GetReceiveFlagLIN function). 
*				LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
********************************************************************************/
void LINFLEX_ReadLIN (vuint8_t nbLINFlex, int8_t nbBytes, uint8_t* response)
{
	uint32_t responseL = 0;
	uint32_t responseM = 0;
	int8_t index;

	responseL = LINFLEX[nbLINFlex]->BDRL.R;
	responseM = LINFLEX[nbLINFlex]->BDRM.R;

	for (index=0;index<nbBytes;index++)							
	{
		if(index<4) *(response+index) = (int8_t) ( responseL >> (8*index) );
		else *(response+index) = (int8_t) ( responseM  >> (8*(index-4)));
	}
}

/***************************************************************************//*!
*   @brief The function LINFLEX_GetReceiveFlagLIN returns the DRF flag.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function returns theDRF - Data Reception Completed Flag 
*					from the LINSR register. This should be e.g. used simply in 
*					while cycle to wait for available data if configured as a Master 
*					or a Slave.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@return Function returns DRF - Data Reception Completed Flag.
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
********************************************************************************/
uint32_t LINFLEX_GetReceiveFlagLIN(vuint8_t nbLINFlex)
{
	return LINFLEX[nbLINFlex]->LINSR.B.DRF;
}

/***************************************************************************//*!
*   @brief The function clears the DRF flag.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function clears DRF (Data Reception Completed Flag) 
*					in LINSR register.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@remarks 	Function should be used everytime after data read (after 
*				LINFLEX_GetReceiveFlagLIN function) to clear input buffer 
*				and to prepare receiver for new data. LINFlex module should 
*				be activated before use of this function (see LINFLEX_InitLIN 
*				function for details).
********************************************************************************/
void LINFLEX_ClearReceiveFlagLIN(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->LINSR.B.DRF = 1;
}

/***************************************************************************//*!
*   @brief The function returns the HRF flag.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function returns HRF - Header Reception Flag from LINSR 
*					register. Function should be used if configured as a Slave 
*					to wait for a header.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@return Function returns HRF - Header Reception Flag.
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
********************************************************************************/
uint32_t LINFLEX_GetHeaderFlagLIN(vuint8_t nbLINFlex)
{
	return LINFLEX[nbLINFlex]->LINSR.B.HRF;
}

/***************************************************************************//*!
*   @brief The function clears the HRF flag.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function clears HRF (Header Reception Flag) in LINSR register.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@remarks 	Function should be used everytime when a header has been received 
*				and processed (LINFLEX_ReadLINid and LINFLEX_SetReceptionParamLIN 
*				functions). In the case when Slave  task works as a publisher 
*				(will send data Bytes), flag should be cleared after the whole 
*				frame (see LIN code examples for details). LINFlex module should 
*				be activated before use of this function (see LINFLEX_InitLIN 
*				function for details).
********************************************************************************/
void LINFLEX_ClearHeaderFlagLIN(vuint8_t nbLINFlex)
{
	LINFLEX[nbLINFlex]->LINSR.B.HRF = 1;
}

/***************************************************************************//*!
*   @brief The function reads the received LIN identifier.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function reads identifier (ID) of the received LIN frame.
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@return Returns identifier (ID) of the received frame.
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
********************************************************************************/
uint32_t LINFLEX_ReadLINid(vuint8_t nbLINFlex){
	return LINFLEX[nbLINFlex]->BIDR.B.ID;
}

/***************************************************************************//*!
*   @brief The function LINFLEX_SetReceptionParamLIN sets parameters of 
*			the LINFlex module.
*	@par Include: 
*					DSPI.h
* 	@par Description: 
*					This function sets parameters for the LIN receiver as follows:
*						- Enhanced checksum	CCS = 0
*						- Direction - receive	DIR = 0
*						- Data bytes	DFL = nbBytes
*	@param[in] nbLINFlex -  Number of LINFlex module (0 or 1).
*	@param[in] nbBytes - 	Number of data bytes in the LIN frame. Number from 1 
*							till 8 with respect to the LIN specification 2.0).
*	@remarks 	LINFlex module should be activated before use of this function 
*				(see LINFLEX_InitLIN function for details).
********************************************************************************/
void LINFLEX_SetReceptionParamLIN(vuint8_t nbLINFlex, uint8_t nbBytes){
	LINFLEX[nbLINFlex]->BIDR.B.DFL = nbBytes - 1;			//set parameters for data Bytes
	LINFLEX[nbLINFlex]->BIDR.B.CCS = 0;			//0 = enhanced CHSUM		1 = classic CHSUM
	LINFLEX[nbLINFlex]->BIDR.B.DIR = 0;			//direction -> receive
}

