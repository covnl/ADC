/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     ctu.h
*
* @author   b15651
* 
* @version  1.0.1.0
* 
* @date     Aug-29-2013
* 
* @brief    CTU - Cross Triggering Units for MPC5744P
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of MPC5744P CTU
* peripheral modules.
*
******************************************************************************/
#ifndef _CTU_H_
#define _CTU_H_



/******************************************************************************
* Global CTU variables definition
******************************************************************************/

/******************************************************************************
* CTU MACRO definitions
******************************************************************************/

/******************************************************************************
* CTU registers bit definition
******************************************************************************/

/******************************************************************************
* Exported functions
*******************************************************************************/
extern void ctu0_init(void);
extern void ctu1_init(void);

void CTU0_Init_v1(void);
/*
CTU0 registers configuration
--------------------------------------
*/
#define CTU0_TGSISR			            0x00000001   ///enable FlexPWM Master Reload signal trigger CTU
#define CTU0_TGSCR                      0x0100       //Trigger generator subunit control register
                                                     //ET_TM=1,enable toggle mode for external trigger
#define CTU0_T0CR                       0x00A0       //Trigger compare register
#define CTU0_T1CR                       0x1000		 //Trigger compare register
#define CTU0_T2CR                       0x1080		 //Trigger compare register
#define CTU0_TGSCCR                     0x4000

#define CTU0_CLCR1                      0x00000000   //commands list control register 1

#define CTU0_THCR1                      0x00444461   //Trigger handler control register 1
                                                     //trigger 2 eTimer2_TRG output enable,
                                                     //trigger 1 eTimer2_TRG output enable
                                                     //trigger 0 external trigger output enable
                                                     //trigger 0 ADC command output enable


#define CTU0_COTR                       0x0064
#define CTU0_CTU0CR                     0x0003   //General reload enable, TGS input selection register reload enable

#define CTU0_CLR0                       0xA104   //CMS=1,ST0=0->dual conversion mode,
                                                 //ENABLE comman execution interrupt request(CTU0_ADC_I_ISR)
                                                 ///ADC port B channel 8,port A channel 4

#define CTU0_CLR1                       0x61CD   //ADC PORT B channel 14, port A channel 13
#define CTU0_CLR2                       0x2000
#define CTU0_CLR3                       0x202F
#define CTU0_CLR4                       0x204E


/*
CTU1 registers configuration
--------------------------------------
*/
#define CTU1_TGSISR						0x00000001
#define CTU1_TGSCR                      0x0100
#define CTU1_T0CR                       0x00A0
#define CTU1_T1CR                       0x1450		//0x1B00
#define CTU1_T2CR                       0x3390		//0x3A40
#define CTU1_TGSCCR                     0x3E80
#define CTU1_CLCR1                      0x00000000

// UNI3 - Trig0 (ADC) - EN, Resolver #2 excitation by ET2_CH3
// UNI3 - CTU_1 -> eTimer0_TRG (T1E) for Aux_0 of eTimer2
#define CTU1_THCR1                      0x00424261

#define CTU1_COTR                       0x0064
#define CTU1_CTU1CR                     0x0003
#define CTU1_CLR0                       0x6080
#define CTU1_CLR1                       0x20A1
#define CTU1_CLR2                       0xA062
#define CTU1_CLR3                       0x602F

#endif /* _CTU_H_ */
