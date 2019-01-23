/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       PIT.h$
* @file             PIT.h
*
* $Date:            Jul-29-2014$
* @date             Jul-29-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      PIT driver header file
* @brief            PIT driver header file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage PIT driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains PIT driver for MPC5744P allowing to 
*	initialize and configure PIT module.
*
*  The key features of this package are the following:
*  - Initialize PIT for the desired time period
*  - Launch and stop PIT for specified channel
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
B35993		 				  29/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#ifndef _H_PIT
#define _H_PIT

//offset definitions
#define PITCH0_OFF			0x100
#define PITCH1_OFF			0x110
#define PITCH2_OFF			0x120
#define PITCH3_OFF			0x130


void PIT_Init(void);
void PIT_Setup(int8_t Channel, uint32_t Clock_Freq, double ExpectedTimeBase);
void PIT_EnableInt(int8_t Channel);
void PIT_EnableChannel(int8_t Channel);
void PIT_Disable(int8_t Channel);
int8_t PIT_GetFlag(int8_t Channel);
void PIT_ClearFlag(int8_t Channel);

void PIT_DisableChannel(int8_t Channel);
uint32_t PIT_IsChannelEnabled(int8_t Channel);

/////STM
void STM0TimerInit(uint32_t nTimerSel, uint32_t u32Ticks);
void STM0_Init(void);

#endif
