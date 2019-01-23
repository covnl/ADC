/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     flexpwm.h
*
* @author   b15651
*
* @version  1.0.1.0
*
* @date     Aug-30-2013
*
* @brief    flexPWM - flexPWM module on MPC5744P
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of MPC5744P flexPWM
* peripheral module.
*
******************************************************************************/
#ifndef _FLEXPWM_H_
#define _FLEXPWM_H_



/******************************************************************************
* Global flexPWM variables definition
******************************************************************************/
// Pointer to flexPWM structure
extern volatile struct FlexPWM_tag *pPWM0;
extern volatile struct FlexPWM_tag *pPWM1;

//typedef struct{
//    uint16_t    s16A;
//    uint16_t    s16B;
//    uint16_t    s16C;
//}FLEXPWM_VAL_COMPL;

/******************************************************************************
* flexPWM MACRO definitions
******************************************************************************/
#define SUB_0                                   0x0     // Sub module 0
#define SUB_1                                   0x1     // Sub module 1
#define SUB_2                                   0x2     // Sub module 2
#define SUB_3                                   0x3     // Sub module 3

#define RUN_SUB0                                0x0100
#define RUN_SUB1                                0x0200
#define RUN_SUB2                                0x0400
#define RUN_SUB3                                0x0800

#define LDOK_SUB0                               0x0001
#define LDOK_SUB1                               0x0002
#define LDOK_SUB2                               0x0004
#define LDOK_SUB3                               0x0008


/*
FlexPWM0 registers configuration
--------------------------------------
*/
#define FlexPWM0_OUTEN                 0x0FF0 /* enable sub0,1,2,3 */
#define FlexPWM0_MASK                  0x0FF0
#define FlexPWM0_MCTRL                 0x0700
#define FlexPWM0_FCTRL                 0xF0F0
#define FlexPWM0_FFILT                 0x0001

#define FlexPWM0_INIT_sub0             0xF000
#define FlexPWM0_CTRL2_sub0            0x0000/* 0xC0A0: force init disabled for SWG sync */
#define FlexPWM0_CTRL1_sub0            0x1400
#define FlexPWM0_VAL1_sub0             0x0FFF
#define FlexPWM0_VAL2_sub0             0xF830
#define FlexPWM0_VAL3_sub0             0x07D0
#define FlexPWM0_OCTRL_sub0            0x0410
#define FlexPWM0_INTEN_sub0            0x1000
#define FlexPWM0_DTCNT0_sub0           0x005A
#define FlexPWM0_DTCNT1_sub0           0x005A

#define FlexPWM0_INIT_sub1             0xF000
#define FlexPWM0_CTRL2_sub1            0xC2AE
#define FlexPWM0_CTRL1_sub1            0x1400
#define FlexPWM0_VAL1_sub1             0x0FFF
#define FlexPWM0_VAL2_sub1             0xF830
#define FlexPWM0_VAL3_sub1             0x07D0
#define FlexPWM0_OCTRL_sub1            0x0410
#define FlexPWM0_DTCNT0_sub1           0x005A
#define FlexPWM0_DTCNT1_sub1           0x005A

#define FlexPWM0_INIT_sub2             0xF000
#define FlexPWM0_CTRL2_sub2            0xC2AE
#define FlexPWM0_CTRL1_sub2            0x1400
#define FlexPWM0_VAL1_sub2             0x0FFF
#define FlexPWM0_VAL2_sub2             0xF830
#define FlexPWM0_VAL3_sub2             0x07D0
#define FlexPWM0_OCTRL_sub2            0x0410
#define FlexPWM0_DTCNT0_sub2           0x005A
#define FlexPWM0_DTCNT1_sub2           0x005A

#define FlexPWM0_INIT_sub3             0xF000
#define FlexPWM0_CTRL2_sub3            0xC2AE
#define FlexPWM0_CTRL1_sub3            0x1400
#define FlexPWM0_VAL1_sub3             0x0FFF
#define FlexPWM0_VAL2_sub3             0xF830
#define FlexPWM0_VAL3_sub3             0x07D0
#define FlexPWM0_OCTRL_sub3            0x0410
#define FlexPWM0_DTCNT0_sub3           0x005A
#define FlexPWM0_DTCNT1_sub3           0x005A


/******************************************************************************
* Exported functions
*******************************************************************************/
extern void flexpwm0_init(void);
extern void flexpwm1_init(void);

extern void FlexPWM0_Init_v1(void);
extern void FlexPWM0_Init_v2(void);
extern void FlexPWM0_Init_v3(void);
//void flexpwm_update_val_compl(volatile mcPWM_tag *ptrPWM, FLEXPWM_VAL_COMPL *pPwmVal);


#endif /* _FLEXPWM_H_ */
