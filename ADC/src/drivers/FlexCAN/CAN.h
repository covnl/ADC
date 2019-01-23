/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       CAN.c$
* @file             CAN.c
*
* $Date:            Jul-23-2014$
* @date             Jul-23-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description      CAN driver header file
* @brief           CAN driver header file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage CAN driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains CAN driver allowing to configure/initialize CAN module
*	and transmit CAN frames.

*  The key features of this package are the following:
*  - Initializate CAN module 
*  - Send CAN frames
*  - Disable CAN module
*
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
B35993		 				  23/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#ifndef _CAN_H_
#define _CAN_H_

/*==================================================================================================
*   NON - configurable parameters
*	User should not modify configuration in this section.
==================================================================================================*/

#define CAN_MODULE_0 0
#define CAN_MODULE_1 1

/*==================================================================================================
*   Function prototypes
==================================================================================================*/

void CAN_ConfigurePads(uint8_t);
void CAN_Init(uint8_t);
void CAN_Send (uint8_t, uint8_t, uint64_t, uint32_t);
//void CAN_Receive(uint8_t nbModule,uint8_t nbBuffer,uint64_t message, uint32_t id);
void CAN_Receive(uint8_t nbModule,uint8_t nbBuffer,uint64_t* message, uint32_t* id);
void CAN_Stop(uint8_t, uint8_t);

#endif 
