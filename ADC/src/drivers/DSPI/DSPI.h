/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       DSPI.h$
* @file             DSPI.h
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

#ifndef _DSPI_H_
#define _DSPI_H_

///DSPI basic defines
#define MASTER 1
#define SLAVE  0

#define PBR_VALUE1	2.
#define PBR_VALUE2	3.
#define PBR_VALUE3	5.
#define PBR_VALUE4	7.

#define PBR1	0x0		
#define PBR2	0x1
#define PBR3	0x2
#define PBR4	0x3

#define BR_VALUE1		2
#define BR_VALUE2		4
#define BR_VALUE3		6
#define BR_VALUE4		8
#define BR_VALUE5		16
#define BR_VALUE6		32
#define BR_VALUE7		64
#define BR_VALUE8		128
#define BR_VALUE9		256
#define BR_VALUE10      512
#define BR_VALUE11      1024
#define BR_VALUE12      2048
#define BR_VALUE13      4096
#define BR_VALUE14      8192
#define BR_VALUE15      16384
#define BR_VALUE16      32768

#define BR1             0x0 
#define BR2             0x1 
#define BR3             0x2 
#define BR4             0x3 
#define BR5             0x4 
#define BR6             0x5 
#define BR7             0x6 
#define BR8             0x7 
#define BR9             0x8 
#define BR10            0x9 
#define BR11            0xA 
#define BR12            0xB 
#define BR13            0xC 
#define BR14            0xD 
#define BR15            0xE 
#define BR16            0xF 

///Minimal values of the ratio (fsys/SCKbr) with different PBR setting
#define RATIO_MIN1	4				
#define RATIO_MIN2	6				
#define RATIO_MIN3	10				
#define RATIO_MIN4	14				
///Maximal values of the ratio (fsys/SCKbr) with different PBR setting
#define RATIO_MAX1	65536			
#define RATIO_MAX2	98304			
#define RATIO_MAX3	163840			
#define RATIO_MAX4	229376			

///CTAR defines
#define LOW_SCK						0						//CPOL
#define HIGH_SCK					1
#define CAPTURE_RISING		0						//CPHA
#define CAPTURE_FALLING     1				
#define NORMAL_BR					0						//DBR
#define DOUBLED_BR				1
///CTAR Prescalers
#define PRESC_VAL1		0	
#define PRESC_VAL3		1
#define PRESC_VAL5		2
#define PRESC_VAL7		3
///CTAR Scalers
#define SCALER1		    0x0
#define SCALER2		    0x1
#define SCALER3		    0x2
#define SCALER4		    0x3
#define SCALER5		    0x4
#define SCALER6		    0x5
#define SCALER7		    0x6
#define SCALER8		    0x7
#define SCALER9         0x8
#define SCALER10        0x9
#define SCALER11		0xA
#define SCALER12		0xB
#define SCALER13		0xC
#define SCALER14		0xD
#define SCALER15		0xE
#define SCALER16		0xF

///Interrupts
#define TCFRE		0x80000000
#define EOQFRE	0x10000000
#define TFUFRE	0x08000000
#define TFFFRE	0x02000000
#define RFOFRE	0x00080000
#define RFDFRE	0x00020000

///Offset definitions
#define CTAR0_OFF	0x000C	//till CTAR5 by 4 Bytes each
#define TXFR0_OFF	0x003C	//till TXFR3 by 4 Bytes each
#define RXFR0_OFF	0x007C	//till RXFR3 by 4 Bytes each


void DSPI_Init(uint8_t,uint8_t, uint32_t, uint32_t, uint32_t);
void DSPI_Send(uint8_t,uint8_t,uint16_t);
uint32_t DSPI_Read(uint8_t);
uint32_t DSPI_RoundBaudRate(uint32_t);
void DSPI_SetPhase(uint8_t, uint8_t);
void DSPI_SetPolarity(uint8_t, uint8_t);
void DSPI_Enable(uint8_t);
void DSPI_Disable(uint8_t);

void DSPI_ChangeBaudRateType(uint8_t DspiNumber, uint8_t typeBR);
void DSPI_ChangeFrameSize(uint8_t DspiNumber, uint8_t frameSize);

void DSPI_EnableTxFIFO(uint8_t);
void DSPI_DisableTxFIFO(uint8_t);
void DSPI_EnableRxFIFO(uint8_t);
void DSPI_DisableRxFIFO(uint8_t);
void DSPI_SendWithInt(uint8_t,uint8_t,uint16_t);
uint32_t DSPI_ReadWithInt(uint8_t);
void DSPI_ClearRFDF(uint8_t);


#endif
