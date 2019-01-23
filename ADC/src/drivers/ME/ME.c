/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2012 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       ME.c$
* @file             ME.c
*
* $Date:            Jul-31-2014$
* @date             Jul-31-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      ME driver source file
* @brief            ME driver source file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage ME driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains ME driver for MPC5744P allowing to 
*	initialize and configure ME module.
*
*  The key features of this package are the following:
*  - Initialize ME module
*  - Change actual mode
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
B35993		 				  31/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#include "Defines.h"
#include "ME.h"
#include "FCCU.h"

/***************************************************************************//*!
*   @brief The function MC_MODE_INIT initializes Mode Entry Module (ME).
*	@par Include: 
*					ME.h
* 	@par Description: 
*					This function makes a basic initialization of oscillators 
*					and peripherals. After the necessary initialization, the MCU 
*					goes into the DRUN mode.
*	@remarks 	
********************************************************************************/
void MC_MODE_INIT(void)
{
    /* Enable All Modes */
    //MC_ME.ME.R = 0x000005E2;
	//MC_ME.ME.R = 0x000005FF;

    /* Peripheral ON in every run mode */
    MC_ME.RUN_PC[0].R = 0x000000FE; 
    
    /******************** Configure XOSC for DRUN **********************/    
    /* Enable EXT OSC First */
    XOSC.CTL.B.OSCM = 0x1;                          /* Change OSC mode to LCP (Loop Controlled Pierce Mode) */
    XOSC.CTL.B.EOCV = 0x80;                         /* Set the End of Count Value for when to check stabilization. */
   
    /* Enable XOSC in DRUN mode and select as SYS_CLK */
    MC_ME.DRUN_MC.R = 0x00130031;                  
    
    /* RE enter the DRUN mode, to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;                      /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                      /* Mode & Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1);                /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);        /* Check DRUN mode has been entered */
    while(!MC_ME.GS.B.S_XOSC);                      /* Wait for clock to stabilise */
    
    /******************** PLL0, PLL1 **********************/
  
    /* Route XOSC to PLL1 */
    MC_CGM.AC4_SC.B.SELCTL = 1;
    
    /* Route XOSC PLL0 */
    MC_CGM.AC3_SC.B.SELCTL = 1;
    
    /*
        Configure PLL0 Dividers for 160 MHz
        fPLL0_VCO = (fPLL0_ref x PLL0DV[MFD] x 2)/PLL0DV[PREDIV]
                  = 40MHz x 8 x 2 / 1 =  640 MHz    
                  
        fPLL0_PHI  = fPLL0_ref x PLL0DV[MFD] / (PLL0DV[PREDIV] x PLL0DV[RFDPHI]
                   = 40MHz x 8 / (1 x 2) = 160 MHz

        fPLL0_PHI1 = fPLL0_ref x PLL0DV[MFD] / (PLL0DV[PREDIV] x PLL0DV[RFDPHI1])
                   = 40MHz x 8 / (1 x 8) = 40 MHz                   
    */
    PLLDIG.PLL0DV.B.RFDPHI1 = 8; 
    PLLDIG.PLL0DV.B.RFDPHI = 2;
    PLLDIG.PLL0DV.B.PREDIV = 1;
    PLLDIG.PLL0DV.B.MFD = 8;

    /*
        Configure PLL1 Dividers for 200 MHz
        fPLL1_VCO = fPLL1_REF x (PLL1DV[MFD] + PLL1FD[FRCDIV]/2^12)
                  = 40MHz x 20 + 0 = 800 MHz
                  
        fPLL1_PHI = fPLL1_REF * ( (PLL1DV[MFD] + PLL1FD[FRCDIV]/2^12) / (2 x PLL1DV[RFDPHI]) )
                  = 40MHz x (20 + 0) / (2 x 2) = 200 MHz
                  

    */    
    PLLDIG.PLL1DV.B.RFDPHI = 2;                     
    PLLDIG.PLL1DV.B.MFD = 20;    
        
    /* Enable PLL0/PLL1 in DRUN mode and set PLL1 as SYS_CLK */
    MC_ME.DRUN_MC.R = 0x001300F4;
        
    /******************** Configure Clock Dividers **********************/  
   
    SIUL2.MSCR[22].R = 0x22800001;                  /* Configure CLK_OUT (B6) */
    //MC_CGM.AC6_SC.B.SELCTL = 0;                   /* source AC6 is internal RCOSC */
    //MC_CGM.AC6_SC.B.SELCTL = 2;                   /* source AC6 is PLL0 PHI */
    //MC_CGM.AC6_SC.B.SELCTL = 1;                   /* source AC6 is XOSC */
    MC_CGM.AC6_SC.B.SELCTL = 4;                     /* source AC6 is PLL1 PHI */    
    MC_CGM.AC6_DC0.R = 0x80090000;                  /* Aux clock select 6 divider 0 --> div by 10 (CLK_OUT) */    
    
    MC_CGM.AC0_SC.B.SELCTL = 2;                     /* source AC0 is PLL0 PHI */
    MC_CGM.AC0_DC0.R = 0x80000000;                  /* Aux clock select 0 divider 0 --> div by 1 (MOTC_CLK) */
    MC_CGM.AC0_DC1.R = 0x80070000;                  /* Aux clock select 0 divider 1 --> div by 8 (SWG_CLK) */
    MC_CGM.AC0_DC2.R = 0x80010000;                  /* Aux clock select 0 divider 2 --> div by 2 (ADC_CLK) */

    MC_CGM.AC1_DC0.R = 0x80010000;                  /* Aux clock select 1 divider 0 --> div by 2 (FRAY_PLL_CLK) */
    MC_CGM.AC1_DC1.R = 0x80030000;                  /* Aux clock select 1 divider 1 --> div by 4 (SENT_CLK) */

    MC_CGM.AC2_DC0.R = 0x80030000;                  /* Aux clock select 2 divider 0 --> div by 4 (CAN_PLL_CLK) */
    
    MC_CGM.SC_DC0.R = 0x80030000;                   /* Sys clock select divider 0 --> div by 4 (PBRIDGEx_CLK) -> DSPI clock = 50MHz, PIT clock = 50 MHz */

    /******************** Start the core **********************/
    /* Main and checker cores running in RUN3:0, DRUN, SAFE, TEST modes */
    MC_ME.CCTL0.R = 0x00FE;

     /* Set PRAM controller WS to 1 since running SYS_CLK as PLL1 (200 MHz) */
    PRAMC.PRCR1.B.FT_DIS = 1;
    
    /******************** Perform mode change **********************/    
    /* Mode change re-enter the DRUN mode, to start cores, clock tree & PLL1 */
    MC_ME.MCTL.R = 0x30005AF0;                  /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                  /* Mode & Key inverted */
  
    while(MC_ME.GS.B.S_MTRANS == 1);            /* Wait for mode entry complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);    /* Check DRUN mode entered */

}
