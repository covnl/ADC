/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       LINFLEX.h$
* @file             LINFLEX.h
*
* $Date:            Jul-24-2014$
* @date             Jul-24-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      LINFLEX driver header file
* @brief            LINFLEX driver header file
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

#ifndef _LINFLEX_H_
#define _LINFLEX_H_

#define MASTER	1
#define SLAVE 	0

void LINFLEX_ChangeBaudRate(vuint8_t, double, uint32_t);
void LINFLEX_ConfigurePads(vuint8_t);
void LINFLEX_Sleep(vuint8_t);
void LINFLEX_WakeUp(vuint8_t);
void LINFLEX_DisableTxUART(vuint8_t);
void LINFLEX_DisableRxUART(vuint8_t);
void LINFLEX_EnableTxUART(vuint8_t);
void LINFLEX_EnableRxUART(vuint8_t);

void LINFLEX_EnableInt(vuint8_t);
void LINFLEX_InitUART(vuint8_t, double, uint32_t);
void LINFLEX_InitRxBuffer (vuint8_t, int8_t);

void LINFLEX_SendUART (vuint8_t, uint8_t*, uint8_t);
void LINFLEX_ReadUART (vuint8_t, int8_t, uint8_t*);

uint32_t LINFLEX_GetReceiveFlagUART(vuint8_t);
void LINFLEX_ClearReceiveFlagUART(vuint8_t);
void LINFLEX_EnableDRFint(vuint8_t);
uint32_t LINFLEX_GetParityErrorUART(vuint8_t);
void LINFLEX_ClearParityError(vuint8_t);
uint32_t LINFLEX_IsIdle(vuint8_t);

//pure LIN functions
void LINFLEX_InitLIN(vuint8_t, double, uint32_t, uint8_t);
void LINFLEX_SendFrameLIN(vuint8_t, uint8_t*, uint8_t, uint8_t);
void LINFLEX_SendHeaderLIN(vuint8_t, uint8_t, uint8_t);
void LINFLEX_ReadLIN(vuint8_t, int8_t, uint8_t*);
uint32_t LINFLEX_GetReceiveFlagLIN(vuint8_t);
void LINFLEX_ClearReceiveFlagLIN(vuint8_t);
uint32_t LINFLEX_GetHeaderFlagLIN(vuint8_t);
void LINFLEX_ClearHeaderFlagLIN(vuint8_t);
uint32_t LINFLEX_ReadLINid(vuint8_t);
void LINFLEX_SetReceptionParamLIN(vuint8_t, uint8_t);
void LINFLEX_SendWordUART(vuint8_t nbLINFlex, uint8_t* p_string, uint8_t length);


#endif
