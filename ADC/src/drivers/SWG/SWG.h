/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     swg.h
*
* @author   b15651
* 
* @version  1.0.1.0
* 
* @date     Nov-15-2010
* 
* @brief    SWG - Sine Wave Generator module for MPC5744P
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of MPC5744P SWG
* peripheral module.
*
******************************************************************************/
#ifndef _SWG_H_
#define _SWG_H_

#include "MPC5744P.h"

/*
SWG registers configuration
--------------------------------------
*/
#define SWG_CTRL                 	   0x00000000UL

/******************************************************************************
* Global SWG variables definition
******************************************************************************/
// Pointer to SWG structure
extern volatile struct SGEN_tag *pSWG;

/******************************************************************************
* SWG MACRO definitions
******************************************************************************/
/*
SWG registers configuration
--------------------------------------
*/
#define SWG_CTRL                 	   0x00000000UL
#define SWG_TRIG_EN                        0	// 0 - Dis, 1-EN
#define SWG_TRIG_SEL                       0    // First trigger input will used for aligning the sine wave output
#define SWG_TRIG_IOAMPL			   15   // 1.136 Sine wave amplitude (V)
#define SWG_TRIG_IOFREQ			   512  // IOFREQ(dec) = freq*1048576/InFreq = 9.765625KHz*1048576/20MHz = 512
                                                // BW freq. recalc: freal = 9994.5Hz

/******************************************************************************
* SWG registers bit definition
******************************************************************************/

/******************************************************************************
* Exported functions
*******************************************************************************/
extern void sgen_init(void);
extern void SGEN_EnableTrigger(void);
extern void SGEN_EnableOutput(void);
extern void SGEN_DisableOutput(void);

#endif /* _SWG_H_ */
