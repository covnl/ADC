/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     swg.c
*
* @author   b15651
* 
* @version  1.0.1.0
* 
* @date     Sep-24-2013
* 
* @brief    SWG - Sine Wave Generator for MPC5744P
*
*******************************************************************************
*
* This file includes initial setting function of MPC5744P SWG peripheral module.
*
******************************************************************************/
#include "SWG.h"

/******************************************************************************
* SWG variables definition
******************************************************************************/
// Pointer to SWG structure
volatile struct SGEN_tag *pSWG;

/******************************************************************************
* SWG timer functions
*****************************************************************************/

/***************************************************************************//*!
@brief          Sine Wave Generator init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the SWG
                module.

@note           

@warning        
******************************************************************************/
void sgen_init(void)
{
    // initialization of peripheral base address
    pSWG                            = &SGEN_0;

    // wait for load I/O frequency
    pSWG->CTRL.B.LDOS				= 0x0;

    /*-------------------------------------------------------------------------
     * SWG CTRL registers
    --------------------------------------------------------------------------*/
    #ifdef SWG_CTRL                  /* SGEN_CRTL register */
        pSWG->CTRL.R				= SWG_CTRL;

        pSWG->CTRL.B.IOFREQ			= SWG_TRIG_IOFREQ;
		pSWG->CTRL.B.IOAMPL			= SWG_TRIG_IOAMPL;
		pSWG->CTRL.B.TRIG_EN		= SWG_TRIG_EN;
		pSWG->CTRL.B.TRIG_SEL		= SWG_TRIG_SEL;
    #endif
		 // SGEN TRIG0 src - ETIMER1_TRG - CTU_0
		 // SGEN TRIG1 src - ETIMER0_TRG - CTU_1

    // load I/O frequency
    pSWG->CTRL.B.LDOS				= 0x1;

    pSWG->CTRL.B.PDS		= 0x1;
}


void SGEN_EnableTrigger(void)
{
    // initialization of peripheral base address
    pSWG                            = &SGEN_0;

    // wait for load I/O frequency
    pSWG->CTRL.B.LDOS			= 0x0;

    pSWG->CTRL.B.TRIG_EN		= 0x1;

    // load I/O frequency
    pSWG->CTRL.B.LDOS			= 0x1;

}


void SGEN_EnableOutput(void)
{
    // initialization of peripheral base address
    pSWG                            = &SGEN_0;

    pSWG->CTRL.B.PDS		= 0x0;
}

void SGEN_DisableOutput(void)
{
    // initialization of peripheral base address
    pSWG                            = &SGEN_0;
    pSWG->CTRL.B.PDS		= 0x1;
}
