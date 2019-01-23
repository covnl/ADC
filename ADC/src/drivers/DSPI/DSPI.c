/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       DSPI.c$
* @file             DSPI.c
*
* $Date:            Jul-28-2014$
* @date             Jul-28-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      DSPI driver source file
* @brief            DSPI driver source file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage DSPI driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains DSPI driver for MPC5744P allowing to 
*	initialize/configure DSPI module and process SPI communication.
*
*  The key features of this package are the following:
*  - Initialize DSPI module with the desired parameters
*  - Configure DSPI parameters
*  - Process SPI communication (reading/writing)
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
B35993		 				  28/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/


#include "Defines.h"
#include "MPC5744P.h"
#include "SIUL.h"
#include "DSPI.h"
#include "math.h"
//#include "IntcInterrupts.h"

#define DSPI_SECURE_COUNTER 50000

/***************************************************************************//*!
*   @brief The function DSPI_Init computes register contents and initializes the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function initializes the DSPIx in specified mode (Master or Slave), 
*					computes register configuration to achieve the desired baud rate 
*					(if possible) and sets interruption mask. By default, data is changed 
*					on a leading edge of DSPI clock and captured on a falling edge (CPHA=1). 
*					Inactive state of DSPI clock is set to low by default (CPOL=0). Both 
*					parameters are changeable after the init phase using other functions 
*					(see setPhaseSPIx and setPolaritySPIx functions for additional information). 
* 	@param[in] DspiNumber - Number of DSPI module (0 or 1 or 2).
*	@param[in] mode - DSPIx mode configuration (Master or Slave).
*					Predefined values:
*					- MASTER	DSPIx will handle communication as a Master.
*					- SLAVE	DSPIx will listen to the incoming commands as a Slave.
*	@param[in] sysClk
*					System clock frequency [Hz].
*	@param[in] baudRate
*					Desired baud rate [b/s]. Maximal and minimal Baud rate depends on 
*						the actual system clock frequency and on the limits of the PBR and 
*						BR registers. Maximal and minimal values for fsys = 16 MHz are shown 
*						in the table below, for other frequencies see the external excel file.
*						Predefined values:
*						- min baudRate = 70 b/s for fsys = 16 MHz
*						- max baudRate = 4 000 000 b/s for fsys = 16MHz
*	@param[in] intMask
*					32-bit mask allowing us to choose which interruption we want to activate. 
*						If no interruption is necessary, please add simply 0 instead of the whole 
*						mask. Predefined iterruption masks can be combined arbitrarily using 
*						logical OR (|) operator.
*						Predefined value:
*						- TCFRE - Transmission Complete Request Enable flag mask
*						- EOQFRE - Finished Request Enable flag mask
*						- TFUFRE - Transmit FIFO Underflow Request Enable flag mask
*						- TFFFRE - Transmit FIFO Fill Request Enable flag mask
*						- RFOFRE - Receive FIFO Overflow Request Enable flag mask
*						- RFDFRE - Receive FIFO Drain Request Enable flag mask
*	@remarks 	System clock frequency should be added in multiples of the basic units 
*				(e.g. in kHz, MHz), with respect to the units of a baud rate.
*	@par Code sample1
*			DSPI_Init(0, MASTER, 16000000, 4000000, TCFRE);
*			- Command initializes DSPI no. 0 in Master mode with desired baud rate     
*			4 Mbit/s (more exactly 3.81Mbit/s, because 1 Mb/s = 1 048 576 b/s) and 
*			activated interruption when transmission is completed. System clock 
*			frequency is 16 MHz.
*	@par Code sample2
*			DSPI_Init(2, SLAVE, 16, 4, TCFRE | EOQFRE);
*			- Command initializes DSPI no. 2 in Slave mode with desired baud rate         
*			4 Mb/s and activated interruption when transmission is completed and 
*			when request is finished.
********************************************************************************/
void DSPI_Init(uint8_t DspiNumber,uint8_t mode, uint32_t sysClk, uint32_t baudRate, uint32_t intMask)		
{
    volatile struct SPI_tag *p_DSPI;			//base pointer 

    uint32_t p1 = sysClk/baudRate;				//basic parameter
    uint32_t realBR;
    uint32_t realBR1;
    uint32_t realBR2;
    uint32_t realBR3;
    uint32_t realBR4;

    int16_t errorBR = 32767;							//undesirable value of error
    int16_t errorBR1;
    int16_t errorBR2;
    int16_t errorBR3;
    int16_t errorBR4;

    uint8_t binaryPBR; 
    uint8_t binaryBR;

    if(mode == MASTER)
    {						
        //prescaler PBR = 00
        if(p1>=RATIO_MIN1 && p1<=RATIO_MAX1)
        {						
            realBR1 = p1*(1/PBR_VALUE1);
            realBR1 = DSPI_RoundBaudRate(realBR1);
            errorBR1 = baudRate - (sysClk/(PBR_VALUE1*realBR1));
            errorBR1 = (int16_t)fabs(errorBR1);
            if(errorBR1<errorBR)
            {
                errorBR = errorBR1;
                realBR = realBR1;	
                binaryPBR = PBR1;		
            }
        }		

        //prescaler PBR = 01
        if(p1>=RATIO_MIN2 && p1<=RATIO_MAX2)
        {
            realBR2 = p1*(1/PBR_VALUE2);	
            realBR2 = DSPI_RoundBaudRate(realBR2);
            errorBR2 = baudRate - (sysClk/(PBR_VALUE2*realBR2));
            errorBR2 = (int16_t)fabs(errorBR2);
            if(errorBR2<errorBR)
            {
                errorBR = errorBR2;
                realBR = realBR2;	
                binaryPBR = PBR2;		
            }
        }

        //prescaler PBR = 10
        if(p1>=RATIO_MIN3 && p1<=RATIO_MAX3)
        {
            realBR3 = p1*(1/PBR_VALUE3);
            realBR3 = DSPI_RoundBaudRate(realBR3);
            errorBR3 = baudRate - (sysClk/(PBR_VALUE3*realBR3));
            errorBR3 = (int16_t)fabs(errorBR3);
            if(errorBR3<errorBR)
            {
                errorBR = errorBR3;
                realBR = realBR3;
                binaryPBR = PBR3;			
            }
        }

        //prescaler PBR = 11
        if(p1>=RATIO_MIN4 && p1<=RATIO_MAX4)
        {
            realBR4 = p1*(1/PBR_VALUE4);
            realBR4 = DSPI_RoundBaudRate(realBR4);
            errorBR4 = baudRate - (sysClk/(PBR_VALUE4*realBR4));
            errorBR4 = (int16_t)fabs(errorBR4);
            if(errorBR4<errorBR)
            {
                errorBR = errorBR4;
                realBR = realBR4;	
                binaryPBR = PBR4;		
            }
        }

        //choose the BR value
        if(p1<RATIO_MIN1 || p1>RATIO_MAX4)
        {
        //out of bounds
            if(p1<RATIO_MIN1)
            {							
                binaryBR = BR1;										//lower than minimum
                binaryPBR = PBR1;
            }
            else
            {
                binaryBR = BR16;									//greater than maximum
                binaryPBR = PBR4;
            }
        }
        else
        {																	//in the bounds			
            switch(realBR)
            {          
                case BR_VALUE1	: binaryBR = BR1;	break;
                case BR_VALUE2  : binaryBR = BR2;	break;
                case BR_VALUE3  : binaryBR = BR3;	break;	
                case BR_VALUE4  : binaryBR = BR4;	break;
                case BR_VALUE5  : binaryBR = BR5;	break;
                case BR_VALUE6  : binaryBR = BR6;	break;
                case BR_VALUE7  : binaryBR = BR7;	break;
                case BR_VALUE8  : binaryBR = BR8;	break;
                case BR_VALUE9  : binaryBR = BR9;	break;
                case BR_VALUE10	: binaryBR = BR10;	break;
                case BR_VALUE11	: binaryBR = BR11;	break;
                case BR_VALUE12	: binaryBR = BR12;	break;
                case BR_VALUE13	: binaryBR = BR13;	break;
                case BR_VALUE14	: binaryBR = BR14;	break;
                case BR_VALUE15	: binaryBR = BR15;	break;
                case BR_VALUE16	: binaryBR = BR16;	break;
            }		
        }
    }

    //DSPI setting
    //pointer setting
    switch(DspiNumber)
    {											//choose base DSPI address
        case 0 : p_DSPI = &SPI_0; break;
        case 1 : p_DSPI = &SPI_1; break;
        case 2 : p_DSPI = &SPI_2; break;
		case 3 : p_DSPI = &SPI_3; break;
        default: p_DSPI = &SPI_0; break;
    }

    p_DSPI->MCR.B.MSTR = mode;		// Set DSPIx in mode Slave-0 or Master-1
    p_DSPI->MCR.B.MDIS=0;    			// Enable clock
    p_DSPI->MCR.B.HALT=0;					// Allow transfer

    p_DSPI->MCR.B.PCSIS=0x3F;		// CS0-5 active Low		

    //FIFOs
    p_DSPI->MCR.B.DIS_TXF=1;		//FIFOs
    p_DSPI->MCR.B.DIS_RXF=1;

    p_DSPI->RSER.R = intMask;	//interrupt mask						  

    p_DSPI->MCR.B.FRZ = 0;

    //Configuration of ports	
    switch(DspiNumber)
    {
		case 0 :
	if(mode)
            {   // as a Master
                SIUL_DigitalInput(SIUL_PC7, SIUL_IN_PC7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_0 	->IN
                SIUL_DigitalOutput(SIUL_PC6, SIUL_ALT1);                    // SOUT_0	->OUT
                SIUL_DigitalOutput(SIUL_PC5, SIUL_ALT1);                    // SCK_0	->OUT
                SIUL_DigitalOutput(SIUL_PC4, SIUL_ALT1);                    // CS0_0	->OUT
            }
            else
            {	//as a Slave
                SIUL_DigitalInput(SIUL_PC7, SIUL_IN_PC7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_0	->IN
                SIUL_DigitalOutput(SIUL_PC6, SIUL_ALT1);                    // SOUT_0	->OUT
                SIUL_DigitalInputSimple(SIUL_PC5, SIUL_PULL_UP | SIUL_SLEW_ENB);      // SCK_0	->IN
                SIUL_DigitalInputSimple(SIUL_PC4, SIUL_PULL_UP | SIUL_SLEW_ENB);      // CS0_0	->IN
            }
		break;
	
        case 1 	:
            if(mode)
            {	//as a Master
                SIUL_DigitalInput(SIUL_PA8, SIUL_IN_PA8, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_1 	->IN
                SIUL_DigitalOutput(SIUL_PA7, SIUL_ALT1);                    // SOUT_1	->OUT
                SIUL_DigitalOutput(SIUL_PA6, SIUL_ALT1);                    // SCK_1	->OUT
                SIUL_DigitalOutput(SIUL_PA5, SIUL_ALT1);                    // CS0_1	->OUT
            }
            else
            {	//as a Slave
                SIUL_DigitalInput(SIUL_PA8, SIUL_IN_PA8, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_1 	->IN		
                SIUL_DigitalOutput(SIUL_PA7, SIUL_ALT1);                    // SOUT_1	->OUT
                SIUL_DigitalInputSimple(SIUL_PA6, SIUL_PULL_UP | SIUL_SLEW_ENB);      // SCK_1	->IN
                SIUL_DigitalInputSimple(SIUL_PA5, SIUL_PULL_UP | SIUL_SLEW_ENB);      // CS0_1	->IN
            }
            break;
        case 2 	:
            if(mode)
            {		//as a Master
                SIUL_DigitalInput(SIUL_PA2, SIUL_IN_PA2, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT2);      // SIN_2 	->IN
                SIUL_DigitalOutput(SIUL_PA1, SIUL_ALT2);                    // SOUT_2	->OUT
                SIUL_DigitalOutput(SIUL_PA0, SIUL_ALT2);                    // SCK_2	->OUT
                SIUL_DigitalOutput(SIUL_PA3, SIUL_ALT2);                    // CS0_2	->OUT
            }
            else
            {				//as a Slave
                SIUL_DigitalInput(SIUL_PA2, SIUL_IN_PA2, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT2);      // SIN_2 	->IN
                SIUL_DigitalOutput(SIUL_PA1, SIUL_ALT2);                    // SOUT_2	->OUT
                SIUL_DigitalInput(SIUL_PA0, SIUL_IN_PA0_DSPI2 , SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SCK_2	->IN
                SIUL_DigitalInput(SIUL_PA3, SIUL_IN_PA3, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // CS0_2	->IN
            }
            break;	
		case 3 :
			if(mode)
            {		//as a Master
                SIUL_DigitalInput(SIUL_PD7, SIUL_IN_PD7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT2);      // SIN_2 	->IN
                SIUL_DigitalOutput(SIUL_PD5, SIUL_ALT4);                    // SOUT_2	->OUT
                SIUL_DigitalOutput(SIUL_PD6, SIUL_ALT4);                    // SCK_2	->OUT
                SIUL_DigitalOutput(SIUL_PC11, SIUL_ALT4);                    // CS0_3	->OUT
            }
            else
            {				//as a Slave
                SIUL_DigitalInput(SIUL_PD7, SIUL_IN_PD7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT2);      // SIN_2 	->IN
                SIUL_DigitalOutput(SIUL_PD5, SIUL_ALT4);                    // SOUT_2	->OUT
                SIUL_DigitalInput(SIUL_PD6, SIUL_IN_PD6, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SCK_2	->IN
                SIUL_DigitalInput(SIUL_PC11, SIUL_IN_PC11, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // CS0_3	->IN
            }
            break;	
		 
        default : 
	if(mode)
            {   // as a Master
                SIUL_DigitalInput(SIUL_PC7, SIUL_IN_PC7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_0 	->IN
                SIUL_DigitalOutput(SIUL_PC6, SIUL_ALT1);                    // SOUT_0	->OUT
                SIUL_DigitalOutput(SIUL_PC5, SIUL_ALT1);                    // SCK_0	->OUT
                SIUL_DigitalOutput(SIUL_PC4, SIUL_ALT1);                    // CS0_0	->OUT
            }
            else
            {	//as a Slave
                SIUL_DigitalInput(SIUL_PC7, SIUL_IN_PC7, SIUL_PULL_UP | SIUL_SLEW_ENB, SIUL_ALT1);      // SIN_0	->IN
                SIUL_DigitalOutput(SIUL_PC6, SIUL_ALT1);                    // SOUT_0	->OUT
                SIUL_DigitalInputSimple(SIUL_PC5, SIUL_PULL_UP | SIUL_SLEW_ENB);      // SCK_0	->IN
                SIUL_DigitalInputSimple(SIUL_PC4, SIUL_PULL_UP | SIUL_SLEW_ENB);      // CS0_0	->IN
            }
		break;
	
    }

    p_DSPI->MODE.CTAR[0].B.DBR=0; 	// double baud rate
    p_DSPI->MODE.CTAR[0].B.FMSZ=15; 	// Frame size (value+1)
    p_DSPI->MODE.CTAR[0].B.CPOL=0; 	// Polarity CPOL=0=>sck is valid @1
    p_DSPI->MODE.CTAR[0].B.CPHA=1; 	// Phase CPHA=0=>data captured on leading edge 
    p_DSPI->MODE.CTAR[0].B.LSBFE=0; 	// MSB first if 0

    if(mode == MASTER)
    {
        p_DSPI->MODE.CTAR[0].B.PBR=binaryPBR;					//Baud rate
        p_DSPI->MODE.CTAR[0].B.BR=binaryBR;
    }

    p_DSPI->MODE.CTAR[0].B.PCSSCK = PRESC_VAL1;		//tcsc
    p_DSPI->MODE.CTAR[0].B.CSSCK = SCALER3;

    p_DSPI->MODE.CTAR[0].B.PDT = PRESC_VAL3;			//tdt
    p_DSPI->MODE.CTAR[0].B.DT = SCALER4;

    p_DSPI->MODE.CTAR[0].B.PASC = PRESC_VAL1;			//tasc
    p_DSPI->MODE.CTAR[0].B.ASC = SCALER3;					
}

/***************************************************************************//*!
*   @brief The function DSPI_Send sends a 16-bit word through the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function sends a Word (16-bit) via DSPIx (DspiNumber) to the device/devices 
*					specified by a chip select (CSmask). 
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] CSmask
*					Chip Select mask allows us to send a data word only to the specified devices. 
*						If a corresponding bit is set, the affected chip select will be used and data 
*						will be send to the device activated by this chip select. For details see img. 
*						Number of available chip selects differs by module (see table below for details).
*						- DSPI0 can use 6 different chip selects (from PCS0 till PCS5)
*						- DSPI1 can use 5 different chip selects (from PCS0 till PCS4)
*						- DSPI2 can use 4 different chip selects (from PCS0 till PCS3)
*	@param[in] Word
*					6bit data word to be send via DSPI.
*	@remarks 	In Slave mode chip select mask has no effect. DSPI in a Slave mode listens everytime to the 
*				Chip Select no. 0 (communication is controlled by a Master). Function waits until the end of 
*				transmission and then clears the Transfer Complete Flag (TCF). DSPI module must be previously 
*				initialized (see DSPI_Init function for details).
*	@par Code sample1
*			DSPI_Send(0, 0b111111, 0xABBA);
*			- Command sends 16-bit word (0xABBA) via DSPI0 (must be previously configured as a Master) 
*			to the Slaves connected on the 6 Chip Selects (no. 0 - 5).
*	@par Code sample2
*			DSPI_Send(1, 0, 0xABBA);
*			- Command sends 16-bit word (0xABBA) via DSPI no. 1 (must be previously configured as 
*			a Slave).
********************************************************************************/
void DSPI_Send(uint8_t DspiNumber,uint8_t CSmask,uint16_t Word)
{
    uint32_t secure_counter = 0;
    uint32_t toSend = 0;
    uint32_t wordToSend = 0;
    
		//pointer setting
		volatile struct SPI_tag *p_DSPI;				//base pointer
	switch(DspiNumber){											//choose base DSPI address
        case 0 : p_DSPI = &SPI_0; break;
        case 1 : p_DSPI = &SPI_1; break;
        case 2 : p_DSPI = &SPI_2; break;
		case 3 : p_DSPI = &SPI_3; break;
        default: p_DSPI = &SPI_0; break;
    }
    
    toSend = (CSmask << 16);
    toSend = toSend & 0x00FF0000;

    wordToSend = (uint32_t)(Word);
    wordToSend = wordToSend & 0x0000FFFF;
    toSend = toSend | wordToSend;

//add CS in function parameter
	    //p_DSPI->PUSHR.PUSHR.R=((CSmask)<<16)|Word;
    p_DSPI->PUSHR.PUSHR.R = toSend;
    if(p_DSPI->MCR.B.MSTR==MASTER){
	    	while((p_DSPI->SR.B.TCF!=1) && (secure_counter < DSPI_SECURE_COUNTER)){
			secure_counter++;
		}; 			// Wait end of transfert if MASTER
	    	p_DSPI->SR.B.TCF=1;									// Clear Transfert Flag	
	    }    
}

/***************************************************************************//*!
*   @brief The function DSPI_Read reads the incoming 16-bit word from the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function waits for incoming data on a specified DSPI (DspiNumber), then clears Receive 
*					FIFO Drain Flag (RFDF), Transfer Complete Flag (TCF) and returns received data.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@return 32-bit received data.
*	@remarks 	This function waits in a loop until data arrives (indicated by the RFDF flag). The DSPI 
*				module must be previously initialized (see DSPI_Init function for details).
*	@par Code sample
*			DSPI_Read(2);
*			- Command reads and returns incoming data from DSPI2, when they are ready.
********************************************************************************/
uint32_t DSPI_Read(uint8_t DspiNumber){
		volatile struct SPI_tag *p_DSPI;				//base pointer
    uint32_t secure_counter = 0; 
		uint32_t recData = 0;
		//pointer setting
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}

		while((p_DSPI->SR.B.RFDF != 1) && (secure_counter < DSPI_SECURE_COUNTER)){
		    secure_counter++;
		};	//wait for RX data
		recData = p_DSPI->POPR.R;					//get received data
		p_DSPI->SR.B.RFDF = 1;						//clear receive flag
		p_DSPI->SR.B.TCF = 1;							//clear transfer complete flag
		return recData;
}

/***************************************************************************//*!
*   @brief The function DSPI_RoundBaudRate is used by the DSPIx Init during 
*			the baud rate setting.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function rounds baud rate.
* 	@param[in] pureBR
*					Baud rate to be rounded.
*	@return Rounded baud rate.
*	@remarks 	This function is used during DSPI initialization (DSPI_Init) 
*				to compute register setting for the desired baud rate.
*	@par Code sample
*			roundedBR= DSPI_RoundBaudRate(pureBR);
*			- Command rounds baud rate that is given through the variable pureBR and returns 
*			the new value through the roundedBR variable.
********************************************************************************/
uint32_t DSPI_RoundBaudRate(uint32_t pureBR){					//IN - computed baud rate  OUT - baud rate from a list
    uint32_t BR = 0;
	if(pureBR>=2 			&& pureBR<3) 			BR = 2;
	if(pureBR>=3 			&& pureBR<5) 			BR = 4;
	if(pureBR>=5 			&& pureBR<7) 			BR = 6;
	if(pureBR>=7 			&& pureBR<12) 		BR = 8;
	if(pureBR>=12 		&& pureBR<24)			BR = 16;
	if(pureBR>=24 		&& pureBR<48) 		BR = 32;
	if(pureBR>=48 		&& pureBR<96) 		BR = 64;
	if(pureBR>=96 		&& pureBR<192) 		BR = 128;
	if(pureBR>=192 		&& pureBR<384) 		BR = 256;
	if(pureBR>=384 		&& pureBR<768) 		BR = 512;
	if(pureBR>=768 		&& pureBR<1536) 	BR = 1024;
	if(pureBR>=1536 	&& pureBR<3072) 	BR = 2048;
	if(pureBR>=3072 	&& pureBR<6144) 	BR = 4096;
	if(pureBR>=6144	 	&& pureBR<12288) 	BR = 8192;
	if(pureBR>=12288 	&& pureBR<24576) 	BR = 16384;
	if(pureBR>=24576 	&& pureBR<32768) 	BR = 32768;

	return BR;
}

/***************************************************************************//*!
*   @brief The function DSPI_Enable enables transfers in the DSPIx module.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function starts transfers (HALT bit equals to 0) of the specified DSPI module.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Transfers are enabled by default. DSPI module must be previously initialized 
*				(see DSPI_Init function for details). 
*	@par Code sample
*			DSPI_Enable(2);
*			- Command starts transfers of DSPI2.
********************************************************************************/
void DSPI_Enable(uint8_t DspiNumber){
		//pointer setting
		volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}

	p_DSPI->MCR.B.HALT=0; 	// Allow transfer						
}

/***************************************************************************//*!
*   @brief The function disables the DSPIx transfer.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function stops transfers (HALT bit equals to 1) of the specified DSPI module.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Transfers are enabled by default. DSPI module must be previously initialized 
*				(see DSPI_Init function for details).
*	@par Code sample
*			DSPI_Disable(0);
*			- Command stops transfers of DSPI0.
********************************************************************************/
void DSPI_Disable(uint8_t DspiNumber){
		//pointer setting
		volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}

			p_DSPI->MCR.B.HALT=1;// Disable transfert
}

/***************************************************************************//*!
*   @brief The function DSPI_ChangeBaudRateType changes type of the baud rate 
*			for the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function changes Double Baud Rate (DBR) parameter setting for the DSPIx.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] typeBR
*					Setting for the DBR bit: 
*						- "0" - The baud rate is computed normally with a 50/50 duty cycle. 
*						- "1" - The baud rate is doubled with the duty cycle depending on the Baud Rate Prescaler.
*	@remarks 	DSPI module must be previously initialized (see DSPI_Init function for details). 
*	@par Code sample
*			DSPI_ChangeBaudRateType(0, 1);
*			- Baud rate of the DSPI0 will be doubled with the duty cycle depending 
*			on the baud rate prescaler.
********************************************************************************/
void DSPI_ChangeBaudRateType(uint8_t DspiNumber, uint8_t typeBR){
	 	//pointer setting
		volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
		
		DSPI_Disable(DspiNumber);
		p_DSPI->MODE.CTAR[0].B.DBR=typeBR; 
		DSPI_Enable(DspiNumber);
}

/***************************************************************************//*!
*   @brief the function DSPI_ChangeFrameSize changes a frame size for the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function changes frame size for the DSPIx.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] frameSize
*					Desired frame size in bits (min. 4, max. 16). 
*	@remarks 	DSPI module must be previously initialized (see DSPI_Init function for details). 
*	@par Code sample
*			DSPI_ChangeFrameSize(1, 16);
*			- Changes frame size for DSPI1 module to 16 bits.
********************************************************************************/
void DSPI_ChangeFrameSize(uint8_t DspiNumber, uint8_t frameSize){
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
		
	if(frameSize<4){								//frameSize out of bounds - lower
		frameSize = 3;
	}
	else{
		if(frameSize>16){							//frameSize out of bounds - higher
			frameSize = 15;
		}
		else{
			frameSize = frameSize - 1;	//frameSize from table
		}
	}
	
	DSPI_Disable(DspiNumber);
	p_DSPI->MODE.CTAR[0].B.FMSZ=frameSize;
	DSPI_Enable(DspiNumber);
}

/***************************************************************************//*!
*   @brief The function DSPI_SetPhase changes phase of the DSPIx clock.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function changes clock phase for the DSPI module (DspiNumber).
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] phase
*					Number to be written to the CPHA (Clock Phase) bit.
*					Predefined values:
*					- CAPTURE_RISING - data will be captured on a rising edge and 
*					changed on a falling edge of the DSPI clock
*					- CAPTURE_FALLING - data will be captured on a falling edge and 
*					captured on a rising edge of the DSPI clock
*	@remarks 	DSPI is configured by default with the following parameters: data is changed on a rising edge and captured on a falling edge 
*				(CPHA=1) of the DSPI clock .
*	@par Code sample
*			DSPI_SetPhase(0, CAPTURE_RISING);
*			- Command sets CPHA bit to 0 for DSPI0 (data will be captured on a rising edge 
*			and changed on a falling edge of the DSPI0 clock).
********************************************************************************/
void DSPI_SetPhase(uint8_t DspiNumber, uint8_t phase){				//CPHA
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	
	DSPI_Disable(DspiNumber);
	p_DSPI->MODE.CTAR[0].B.CPHA=phase;
	DSPI_Enable(DspiNumber);
}

/***************************************************************************//*!
*   @brief The function DSPI_SetPolarity changes polarity of the DSPIx clock.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function changes clock polarity for the DSPI module (DspiNumber).
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] polarity
*					Number to be written to the CPOL (Clock Polarity) bit.
*					Predefined values:
*					- DSPI_SetPhase(0, CAPTURE_RISING);
*					- Command sets CPHA bit to 0 for DSPI0 (data will be captured on 
*					a rising edge and changed on a falling edge of the DSPI0 clock).
*	@remarks 	Inactive state of the DSPI clock is set to low by default (CPOL=0). 
*				Phase and clock polarity must be set in the same way in both Master 
*				and Slave devices. DSPI module must be previously initialized 
*				(see DSPI_Init function for details). 
*	@par Code sample
*			DSPI_SetPolarity(1, HIGH_SCK);
*			- Command sets CPOL bit to 1 (inactive state of SCK will be high).
********************************************************************************/
void DSPI_SetPolarity(uint8_t DspiNumber, uint8_t polarity){	//CPOL
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	
	DSPI_Disable(DspiNumber);
	p_DSPI->MODE.CTAR[0].B.CPOL=polarity;
	DSPI_Enable(DspiNumber);
}

/***************************************************************************//*!
*   @brief The function DSPI_EnableTxFIFO enables FIFO for the transmitter 
*			of the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function changes clock polarity for the DSPI module (DspiNumber).
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Tx FIFO is disabled by default. DSPI module must be previously 
*				initialized (see DSPI_Init function for details).
*	@par Code sample
*			DSPI_EnableTxFIFO(1);
*			- Command enables FIFO for the transmitter of DSPI1.
********************************************************************************/
void DSPI_EnableTxFIFO(uint8_t DspiNumber){
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	p_DSPI->MCR.B.DIS_TXF=0;		// Enable TxFIFO			
}

/***************************************************************************//*!
*   @brief The function DSPI_DisableTxFIFO disables FIFO for the DSPIx 
*			transmitter.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function disables FIFO for transmitter of the specified DSPI module.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Tx FIFO is disabled by default. DSPI module must be previously initialized 
*				(see DSPI_Init function for details).
*	@par Code sample
*			DSPI_DisableTxFIFO(2);
*			 - Command disables FIFO for the transmitter of DSPI2.
********************************************************************************/
void DSPI_DisableTxFIFO(uint8_t DspiNumber){
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	p_DSPI->MCR.B.DIS_TXF=1;				// Disable TxFIFO
			
}

/***************************************************************************//*!
*   @brief The function DSPI_EnableRxFIFO enables FIFO for the DSPIx receiver.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function enables FIFO for receiver of the specified 
*						DSPI module.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Rx FIFO is disabled by default. DSPI module must be previously initialized 
*				(see DSPI_Init function for details).
*	@par Code sample
*			DSPI_EnableRxFIFO(0);
*			- Command enables FIFO for the receiver of DSPI0.
********************************************************************************/
void DSPI_EnableRxFIFO(uint8_t DspiNumber){
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	p_DSPI->MCR.B.DIS_RXF=0; 				// Enable RxFIFO 
				
}

/***************************************************************************//*!
*   @brief The function DSPI_DisableRxFIFO disables FIFO for the DSPIx receiver.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function disables FIFO for receiver of the specified DSPI module.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@remarks 	Rx FIFO is disabled by default. DSPI module must be previously initialized 
*				(see DSPI_Init function for details).
*	@par Code sample
*			DSPI_EnableRxFIFO(0);
*			- Command enables FIFO for the receiver of DSPI0.
********************************************************************************/
void DSPI_DisableRxFIFO(uint8_t DspiNumber){
	//pointer setting
	volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	p_DSPI->MCR.B.DIS_RXF=1;				// Disable RxFIFO
		
}

/**
* 19072011 new functions added -> NOT tested_______________________________________________________________________________
*/

/***************************************************************************//*!
*   @brief The function DSPI_SendWithInt sends a 16-bit word through the DSPIx 
*			(used with interrupt service routine).
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function sends a Word (16-bit) via DSPIx (DspiNumber) to the device/devices 
*					specified by a chip select (CSmask). Function shall be used when an interrupt 
*					service routine launched by the Transfer Complete Flag (TCF) is configured.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@param[in] CSmask
*					Chip Select mask allows us to send a data word only to the specified devices. 
*						If a corresponding bit is set, the affected chip select will be used and data 
*						will be send to the device activated by this chip select. For details see img. 
*						Number of available chip selects differs by module (see table below for details).
*						- DSPI0 can use 6 different chip selects (from PCS0 till PCS5)
*						- DSPI1 can use 5 different chip selects (from PCS0 till PCS4)
*						- DSPI2 can use 4 different chip selects (from PCS0 till PCS3)
*	@param[in] Word
*					16bit data word to be send via DSPI.
*	@remarks 	In the Slave mode, the chip select mask has no effect. DSPI in a Slave mode listens
*				to the Chip Select no. 0 (communication is controlled by a Master). Function does not 
*				wait for the end of transmission -> the TCF flag should be cleared in its interrupt 
*				service routine. DSPI module must be previously initialized (see DSPI_Init function for 
*				details).
*				(see DSPI_Init function for details).
*	@par Code sample1
*			DSPI_SendWithInt(0, 0b111111, 0xABBA);
*			- Command sends 16-bit word (0xABBA) via DSPI0 (must be previously configured as a Master) 
*			to the Slaves connected on the 6 Chip Selects (no. 0 - 5).
*	@par Code sample2
*			DSPI_SendWithInt(1, 0, 0xABBA);
*			- Command sends 16-bit word (0xABBA) via DSPI no. 1 (must be previously configured as a Slave).
********************************************************************************/
void DSPI_SendWithInt(uint8_t DspiNumber,uint8_t CSmask,uint16_t Word)
{
		//pointer setting
		volatile struct SPI_tag *p_DSPI;				//base pointer
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
			//add CS in function parameter
	    p_DSPI->PUSHR.PUSHR.R=((CSmask)<<16)|Word;
}

/***************************************************************************//*!
*   @brief The function DSPI_ReadWithInt reads the incoming 16-bit word from DSPI 
*			(used with interrupt service routine).
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function waits for incoming data on a specified DSPI (DspiNumber), then clears 
*					Transfer Complete Flag (TCF) and returns received data. Function does not clear 
*					Receive FIFO Drain Flag (RFDF). This function shall be used in the RFDF interrupt 
*					service routine.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@return 32-bit received data.
*	@remarks 	Function waits at first for the data (RFDF flag), so the function will be waiting in a loop 
*				until the data will arrive. DSPI module must be previously initialized (see DSPI_Init function 
*				for details).
*	@par Code sample
*			DSPI_ReadWithInt(2);
*			- Command reads and return incoming data from DSPI2, when they are ready.
********************************************************************************/
uint32_t DSPI_ReadWithInt(uint8_t DspiNumber){
		volatile struct SPI_tag *p_DSPI;				//base pointer
		uint32_t recData = 0;
		//pointer setting
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}

		while(p_DSPI->SR.B.RFDF != 1){};	//wait for RX data
		recData = p_DSPI->POPR.R;					//get received data
		p_DSPI->SR.B.TCF = 1;							//clear transfer complete flag
		return recData;
}

/***************************************************************************//*!
*   @brief The function DSPI_ClearRFDF clears RFDF flag of the DSPIx.
*	@par Include 
*					DSPI.h
* 	@par Description 
*					This function clears Receive FIFO Drain Flag (RFDF). This 
*					function should be used in the end of the RFDF interrupt routine.
* 	@param[in] DspiNumber
*					Number of DSPI module (0 or 1 or 2).
*	@return 32-bit received data.
*	@remarks 	DSPI module must be previously initialized (see DSPI_Init function for details). 
*	@par Code sample
*			DSPI_ClearRFDF(0);
*			- Command clears RFDF flag in the DSPI0 module.
********************************************************************************/
void DSPI_ClearRFDF(uint8_t DspiNumber){
		volatile struct SPI_tag *p_DSPI;				//base pointer
		//pointer setting
		switch(DspiNumber){											//choose base DSPI address
			case 0 : p_DSPI = &SPI_0; break;
			case 1 : p_DSPI = &SPI_1; break;
			case 2 : p_DSPI = &SPI_2; break;
			case 3 : p_DSPI = &SPI_3; break;
			default: p_DSPI = &SPI_0; break;
		}
	p_DSPI->SR.B.RFDF = 1;						//clear receive flag
}

