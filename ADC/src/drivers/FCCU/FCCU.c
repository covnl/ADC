/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       FCCU.c$
* @file             FCCU.c
*
* $Date:            Jul-25-2014$
* @date             Jul-25-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      FCCU driver source file
* @brief            FCCU driver source file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage FCCU driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains FCCU driver for MPC5744P allowing to clear fault 
*	flags and to generate fake faults for test purposes.
*  The key features of this package are the following:
*  - Clear critical and non-critical error flags
*  - Generate critical and non-critical fake faults

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
B35993		 				  25/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#include "Defines.h"
#include "ME.h" 
#include "FCCU.h"

/***************************************************************************//*!
*   @brief The function FCCU_SetProtocol sets protocol for the FCCU's safety output pins.
*	@par Include 
*					FCCU.h
* 	@par Description 
*					This function sets protocol that will be used to signal actual 
*					state of the FCCU via FCCU_F0 and FCCU_F1 pins.
*	@param[in] protocol
*					Protocol that will be used by the FCCU_F pins.
*					Predefined values:
*					- FCCU_RAIL	0b000
*					- FCCU_TIME_SWITCHING 0b001
*					- FCCU_BI_STABLE	0b010
*					- FCCU_TEST0	0b101
*					- FCCU_TEST1	0b110
*					- FCCU_TEST2	0b111
*	@remarks 	Execution of this function should not be interrupt by any event 
*				(e.g. break point). Function must be executed in the real time 
*				in one sequence, otherwise time delays for using access keys will 
*				be applied and protocol will not be changed.
*	@par Code sample
*			FCCU_SetProtocol(FCCU_BI_STABLE);
*			- Command sets bistable protocol for the FCCU_Fx pins.
********************************************************************************/
void FCCU_SetProtocol(uint32_t protocol){
    // Enter FCCU Configuration Mode
    FCCU.TRANS_LOCK.R = 0xBC;    
    FCCU.CTRLK.R = FCCU_CTRLK_OP1;
    FCCU.CTRL.R = FCCU_OPR_SET_CONFIG;
    while(FCCU.CTRL.B.OPS != FCCU_OPS_SUCCESS);
    
    // Disable all faults
    FCCU.NCF_E[0].R = 0x00000000;	
    FCCU.NCF_E[1].R = 0x00000000;
    FCCU.NCF_E[2].R = 0x00000000;
	//SW reaction
    FCCU.NCF_CFG[0].R = 0xFFFFFFFF; 	
    FCCU.NCF_CFG[1].R = 0xFFFFFFFF;
    FCCU.NCF_CFG[2].R = 0xFFFFFFFF;

    FCCU.CFG.R = 0x01000000;
    FCCU.CFG.B.FOM = protocol;
    
    // Exit FCCU Configuration Mode
    FCCU.CTRLK.R = FCCU_KEY_NORMAL ;
    FCCU.CTRL.R = FCCU_OPR_SET_NORMAL;
    while(FCCU.CTRL.B.OPS != FCCU_OPS_SUCCESS);

}
