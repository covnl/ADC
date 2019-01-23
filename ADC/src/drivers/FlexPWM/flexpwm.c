 /******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     flexpwm.c
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
* This file includes initial setting functions of MPC5744P flexPWM module.
*
******************************************************************************/
//#include "SWLIBS_Inlines.h"
#include "flexpwm.h"
#include "Defines.h"
#include "EXTGLOBALS.h"


/******************************************************************************
* flexPWM variables definition
******************************************************************************/
// Pointer to flexPWM structure
volatile struct FlexPWM_tag *pPWM0;
volatile struct FlexPWM_tag *pPWM1;

/******************************************************************************
* flexPWM functions
*****************************************************************************/
//inline int16_t
//flexpwm_negate_val(register int16_t x)
//{
//    register int32_t y;
//
//    y = -(int32_t)(x);
//    y = (y == -(int32_t) INT16_MIN) ? (int32_t) INT16_MAX:y;
//
//    return (int16_t)(y);
//}

/***************************************************************************//*!
@brief

@param[in,out]  void
@param[in]      void

@return         void

@details

@note

@warning
******************************************************************************/
//void flexpwm_calcduty_50(volatile mcPWM_tag *ptrPWM,FLEXPWM_VAL_COMPL *pPwmVal)
//{
//    pPwmVal->s16A = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),FRAC16(0.5));
//    pPwmVal->s16B = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),FRAC16(0.5));
//    pPwmVal->s16C = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),FRAC16(0.5));
//}

/***************************************************************************//*!
@brief

@param[in,out]  void
@param[in]      void

@return         void

@details

@note

@warning
******************************************************************************/
//void flexpwm_calcduty(volatile mcPWM_tag *ptrPWM,FLEXPWM_VAL_COMPL *pPwmVal, SWLIBS_3Syst *pPwmAbc)
//{
//    pPwmVal->s16A = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),(tFrac16)(pPwmAbc->s32Arg1>>16));
//    pPwmVal->s16B = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),(tFrac16)(pPwmAbc->s32Arg2>>16));
//    pPwmVal->s16C = F16Mul((tFrac16)(ptrPWM->SUB[0].VAL_1.R),(tFrac16)(pPwmAbc->s32Arg3>>16));
//}

/***************************************************************************//*!
@brief

@param[in,out]  void
@param[in]      void

@return         void

@details

@note

@warning
******************************************************************************/
//void flexpwm_update_val_x(uint8_t sub, uint16_t t_off)
//{
//    pPWM0.SUB[sub].VAL[2].R = flexpwm_negate_val(t_off);
//    FLEXPWM_0.SUB[sub].VAL3.R = t_off;
//    FLEXPWM_0.SUB[sub].VAL4.R = flexpwm_negate_val(t_off);
//    FLEXPWM_0.SUB[sub].VAL5.R = t_off;
//}

/***************************************************************************//*!
@brief

@param[in,out]  void
@param[in]      void

@return         void

@details

@note

@warning
******************************************************************************/
//void flexpwm_update_val_compl(volatile mcPWM_tag *ptrPWM, FLEXPWM_VAL_COMPL *pPwmVal)
//{
//    register uint8_t     ldok_test;
//
//    pPwmVal->s16A   &= 0xFFFE;
//    pPwmVal->s16B   &= 0xFFFE;
//    pPwmVal->s16C   &= 0xFFFE;
//
//    ptrPWM->SUB[0].VAL[2].R = flexpwm_negate_val(pPwmVal->s16A);
//    ptrPWM->SUB[0].VAL3.R = (pPwmVal->s16A);
//    ptrPWM->SUB[0].VAL4.R = flexpwm_negate_val(pPwmVal->s16A);
//    ptrPWM->SUB[0].VAL5.R = (pPwmVal->s16A);
//
//    ptrPWM->SUB[1].VAL[2].R = flexpwm_negate_val(pPwmVal->s16B);
//    ptrPWM->SUB[1].VAL3.R = (pPwmVal->s16B);
//    ptrPWM->SUB[1].VAL4.R = flexpwm_negate_val(pPwmVal->s16B);
//    ptrPWM->SUB[1].VAL5.R = (pPwmVal->s16B);
//
//    ptrPWM->SUB[2].VAL[2].R = flexpwm_negate_val(pPwmVal->s16C);
//    ptrPWM->SUB[2].VAL3.R = (pPwmVal->s16C);
//    ptrPWM->SUB[2].VAL4.R = flexpwm_negate_val(pPwmVal->s16C);
//    ptrPWM->SUB[2].VAL5.R = (pPwmVal->s16C);
//
//    ldok_test = ptrPWM->MCTRL.B.LDOK;    // Read the LDOK bit field first
//
//    ptrPWM->MCTRL.B.LDOK = LDOK_SUB0|LDOK_SUB1|LDOK_SUB2|LDOK_SUB3;
//}

/***************************************************************************//*!
@brief          flexPWM0 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the PWM0
                module.

@note

@warning
******************************************************************************/
void flexpwm0_init(void)
{
    static vuint8_t  i,j;
    vuint8_t     ldok_test;

    pPWM0 = &FlexPWM_0;

    /*-------------------------------------------------------------------------
     * FlexPWM0 Reset
    --------------------------------------------------------------------------*/
    for (j=0;j<=3;j++)
    {
        pPWM0->SUB[j].INIT.R		= 0x0;
        pPWM0->SUB[j].CTRL2.R       = 0x0;
        pPWM0->SUB[j].CTRL1.R       = 0x0400U;
        pPWM0->SUB[j].VAL0.R		= 0x0;
        pPWM0->SUB[j].VAL1.R		= 0x0;
        pPWM0->SUB[j].VAL2.R		= 0x0;
        pPWM0->SUB[j].VAL3.R		= 0x0;
        pPWM0->SUB[j].VAL4.R		= 0x0;
        pPWM0->SUB[j].VAL5.R		= 0x0;
        pPWM0->SUB[j].OCTRL.R       = 0x0;
        pPWM0->SUB[j].INTEN.R       = 0x0;
        pPWM0->SUB[j].DMAEN.R       = 0x0;
        pPWM0->SUB[j].TCTRL.R       = 0x0;
        pPWM0->SUB[j].DISMAP.R      = 0xFFFFU;
        pPWM0->SUB[j].DTCNT0.R      = 0x07FFU;
        pPWM0->SUB[j].DTCNT1.R      = 0x07FFU;
        pPWM0->SUB[j].CAPTCTRLX.R   = 0x0;
        pPWM0->SUB[j].CAPTCMPX.R	= 0x0;
    }
    pPWM0->OUTEN.R          = 0x0;
    pPWM0->MASK.R           = 0x0;
    pPWM0->SWCOUT.R         = 0x0;
    pPWM0->DTSRCSEL.R       = 0x0;
    pPWM0->MCTRL.R          = 0x0;
    pPWM0->FCTRL.R          = 0x0;
    pPWM0->FSTS.R           = 0xF;	/* Clear Fault PIN flags manually */
    pPWM0->FFILT.R          = 0x0;


    /*-------------------------------------------------------------------------
     * FlexPWM0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM0_OUTEN                  /* OUTEN register */
        pPWM0->OUTEN.R          = FlexPWM0_OUTEN;
    #endif

    #ifdef FlexPWM0_MASK                   /* MASK register */
        pPWM0->MASK.R           = FlexPWM0_MASK;
    #endif

    #ifdef FlexPWM0_SWCOUT                 /* SWCOUT register */
        pPWM0->SWCOUT.R         = FlexPWM0_SWCOUT;
    #endif

    #ifdef FlexPWM0_DTSRCSEL               /* DTSRCSEL register */
        pPWM0->DTSRCSEL.R       = FlexPWM0_DTSRCSEL;
    #endif

    #ifdef FlexPWM0_FCTRL                  /* FCTRL register */
        pPWM0->FCTRL.R          = FlexPWM0_FCTRL;
    #endif

    #ifdef FlexPWM0_FFILT                  /* FFILT register */
        pPWM0->FFILT.R          = FlexPWM0_FFILT;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM0 sub0 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM0_INIT_sub0              /* INIT register */
        pPWM0->SUB[0].INIT.R    = FlexPWM0_INIT_sub0;
    #endif

    #ifdef FlexPWM0_CTRL2_sub0              /* CTRL2 register */
        pPWM0->SUB[0].CTRL2.R   = FlexPWM0_CTRL2_sub0;
    #endif

    #ifdef FlexPWM0_CTRL1_sub0              /* CTRL register */
        pPWM0->SUB[0].CTRL1.R    = FlexPWM0_CTRL1_sub0;
    #endif

    #ifdef FlexPWM0_VAL0_sub0              /* VAL0 register */
        pPWM0->SUB[0].VAL0.R  = FlexPWM0_VAL0_sub0;
    #endif

    #ifdef FlexPWM0_VAL1_sub0              /* VAL1 register */
        pPWM0->SUB[0].VAL1.R  = FlexPWM0_VAL1_sub0;
    #endif

    #ifdef FlexPWM0_VAL2_sub0              /* VAL2 register */
        pPWM0->SUB[0].VAL2.R  = FlexPWM0_VAL2_sub0;
    #endif

    #ifdef FlexPWM0_VAL3_sub0              /* VAL3 register */
        pPWM0->SUB[0].VAL3.R  = FlexPWM0_VAL3_sub0;
    #endif

    #ifdef FlexPWM0_VAL4_sub0              /* VAL4 register */
        pPWM0->SUB[0].VAL4.R  = FlexPWM0_VAL4_sub0;
    #endif

    #ifdef FlexPWM0_VAL5_sub0              /* VAL5 register */
        pPWM0->SUB[0].VAL5.R  = FlexPWM0_VAL5_sub0;
    #endif

    #ifdef FlexPWM0_OCTRL_sub0             /* OCTRL register */
        pPWM0->SUB[0].OCTRL.R   = FlexPWM0_OCTRL_sub0;
    #endif

    #ifdef FlexPWM0_INTEN_sub0             /* INTEN register */
        pPWM0->SUB[0].INTEN.R   = FlexPWM0_INTEN_sub0;
    #endif

    #ifdef FlexPWM0_DMAEN_sub0             /* DMAEN register */
        pPWM0->SUB[0].DMAEN.R   = FlexPWM0_DMAEN_sub0;
    #endif

    #ifdef FlexPWM0_TCTRL_sub0             /* TCTRL register */
        pPWM0->SUB[0].TCTRL.R   = FlexPWM0_TCTRL_sub0;
    #endif

    #ifdef FlexPWM0_DISMAP_sub0            /* DISMAP register */
        pPWM0->SUB[0].DISMAP.R  = FlexPWM0_DISMAP_sub0;
    #endif

    #ifdef FlexPWM0_DTCNT0_sub0            /* DTCNT0 register */
        pPWM0->SUB[0].DTCNT0.R  = FlexPWM0_DTCNT0_sub0;
    #endif

    #ifdef FlexPWM0_DTCNT1_sub0            /* DTCNT1 register */
        pPWM0->SUB[0].DTCNT1.R  = FlexPWM0_DTCNT1_sub0;
    #endif

    #ifdef FlexPWM0_CAPTCTRLX_sub0          /* CAPCTRLX register */
        pPWM0->SUB[0].CAPTCTRLX.R    = FlexPWM0_CAPTCTRLX_sub0;
    #endif

    #ifdef FlexPWM0_CAPTCOMPX_sub0          /* CAPTCOMPX register */
        pPWM0->SUB[0].CAPTCOMPX.R   = FlexPWM0_CAPTCOMPX_sub0;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM0 sub1 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM0_INIT_sub1              /* INIT register */
        pPWM0->SUB[1].INIT.R    = FlexPWM0_INIT_sub1;
    #endif

    #ifdef FlexPWM0_CTRL2_sub1              /* CTRL2 register */
        pPWM0->SUB[1].CTRL2.R   = FlexPWM0_CTRL2_sub1;
    #endif

    #ifdef FlexPWM0_CTRL1_sub1              /* CTRL register */
        pPWM0->SUB[1].CTRL1.R    = FlexPWM0_CTRL1_sub1;
    #endif

    #ifdef FlexPWM0_VAL0_sub1              /* VAL0 register */
        pPWM0->SUB[1].VAL0.R  = FlexPWM0_VAL0_sub1;
    #endif

    #ifdef FlexPWM0_VAL1_sub1              /* VAL1 register */
        pPWM0->SUB[1].VAL1.R  = FlexPWM0_VAL1_sub1;
    #endif

    #ifdef FlexPWM0_VAL2_sub1              /* VAL2 register */
        pPWM0->SUB[1].VAL2.R  = FlexPWM0_VAL2_sub1;
    #endif

    #ifdef FlexPWM0_VAL3_sub1              /* VAL3 register */
        pPWM0->SUB[1].VAL3.R  = FlexPWM0_VAL3_sub1;
    #endif

    #ifdef FlexPWM0_VAL4_sub1              /* VAL4 register */
        pPWM0->SUB[1].VAL4.R  = FlexPWM0_VAL4_sub1;
    #endif

    #ifdef FlexPWM0_VAL5_sub1              /* VAL5 register */
        pPWM0->SUB[1].VAL5.R  = FlexPWM0_VAL5_sub1;
    #endif

    #ifdef FlexPWM0_OCTRL_sub1             /* OCTRL register */
        pPWM0->SUB[1].OCTRL.R   = FlexPWM0_OCTRL_sub1;
    #endif

    #ifdef FlexPWM0_INTEN_sub1             /* INTEN register */
        pPWM0->SUB[1].INTEN.R   = FlexPWM0_INTEN_sub1;
    #endif

    #ifdef FlexPWM0_DMAEN_sub1             /* DMAEN register */
        pPWM0->SUB[1].DMAEN.R   = FlexPWM0_DMAEN_sub1;
    #endif

    #ifdef FlexPWM0_TCTRL_sub1             /* TCTRL register */
        pPWM0->SUB[1].TCTRL.R   = FlexPWM0_TCTRL_sub1;
    #endif

    #ifdef FlexPWM0_DISMAP_sub1            /* DISMAP register */
        pPWM0->SUB[1].DISMAP.R  = FlexPWM0_DISMAP_sub1;
    #endif

    #ifdef FlexPWM0_DTCNT0_sub1            /* DTCNT0 register */
        pPWM0->SUB[1].DTCNT0.R  = FlexPWM0_DTCNT0_sub1;
    #endif

    #ifdef FlexPWM0_DTCNT1_sub1            /* DTCNT1 register */
        pPWM0->SUB[1].DTCNT1.R  = FlexPWM0_DTCNT1_sub1;
    #endif

    #ifdef FlexPWM0_CAPTCTRLX_sub1          /* CAPCTRLX register */
        pPWM0->SUB[1].CAPTCTRLX.R    = FlexPWM0_CAPTCTRLX_sub1;
    #endif

    #ifdef FlexPWM0_CAPTCOMPX_sub1          /* CAPTCOMPX register */
        pPWM0->SUB[1].CAPTCOMPX.R   = FlexPWM0_CAPTCOMPX_sub1;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM0 sub2 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM0_INIT_sub2              /* INIT register */
        pPWM0->SUB[2].INIT.R    = FlexPWM0_INIT_sub2;
    #endif

    #ifdef FlexPWM0_CTRL2_sub2              /* CTRL2 register */
        pPWM0->SUB[2].CTRL2.R   = FlexPWM0_CTRL2_sub2;
    #endif

    #ifdef FlexPWM0_CTRL1_sub2              /* CTRL register */
        pPWM0->SUB[2].CTRL1.R    = FlexPWM0_CTRL1_sub2;
    #endif

    #ifdef FlexPWM0_VAL0_sub2              /* VAL0 register */
        pPWM0->SUB[2].VAL0.R  = FlexPWM0_VAL0_sub2;
    #endif

    #ifdef FlexPWM0_VAL1_sub2              /* VAL1 register */
        pPWM0->SUB[2].VAL1.R  = FlexPWM0_VAL1_sub2;
    #endif

    #ifdef FlexPWM0_VAL2_sub2              /* VAL2 register */
        pPWM0->SUB[2].VAL2.R  = FlexPWM0_VAL2_sub2;
    #endif

    #ifdef FlexPWM0_VAL3_sub2              /* VAL3 register */
        pPWM0->SUB[2].VAL3.R  = FlexPWM0_VAL3_sub2;
    #endif

    #ifdef FlexPWM0_VAL4_sub2              /* VAL4 register */
        pPWM0->SUB[2].VAL4.R  = FlexPWM0_VAL4_sub2;
    #endif

    #ifdef FlexPWM0_VAL5_sub2              /* VAL5 register */
        pPWM0->SUB[2].VAL5.R  = FlexPWM0_VAL5_sub2;
    #endif

    #ifdef FlexPWM0_OCTRL_sub2             /* OCTRL register */
        pPWM0->SUB[2].OCTRL.R   = FlexPWM0_OCTRL_sub2;
    #endif

    #ifdef FlexPWM0_INTEN_sub2             /* INTEN register */
        pPWM0->SUB[2].INTEN.R   = FlexPWM0_INTEN_sub2;
    #endif

    #ifdef FlexPWM0_DMAEN_sub2             /* DMAEN register */
        pPWM0->SUB[2].DMAEN.R   = FlexPWM0_DMAEN_sub2;
    #endif

    #ifdef FlexPWM0_TCTRL_sub2             /* TCTRL register */
        pPWM0->SUB[2].TCTRL.R   = FlexPWM0_TCTRL_sub2;
    #endif

    #ifdef FlexPWM0_DISMAP_sub2            /* DISMAP register */
        pPWM0->SUB[2].DISMAP.R  = FlexPWM0_DISMAP_sub2;
    #endif

    #ifdef FlexPWM0_DTCNT0_sub2            /* DTCNT0 register */
        pPWM0->SUB[2].DTCNT0.R  = FlexPWM0_DTCNT0_sub2;
    #endif

    #ifdef FlexPWM0_DTCNT1_sub2            /* DTCNT1 register */
        pPWM0->SUB[2].DTCNT1.R  = FlexPWM0_DTCNT1_sub2;
    #endif

    #ifdef FlexPWM0_CAPTCTRLX_sub2          /* CAPCTRLX register */
        pPWM0->SUB[2].CAPTCTRLX.R    = FlexPWM0_CAPTCTRLX_sub2;
    #endif

    #ifdef FlexPWM0_CAPTCOMPX_sub2          /* CAPTCOMPX register */
        pPWM0->SUB[2].CAPTCOMPX.R   = FlexPWM0_CAPTCOMPX_sub2;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM0 sub3 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM0_INIT_sub3              /* INIT register */
        pPWM0->SUB[3].INIT.R    = FlexPWM0_INIT_sub3;
    #endif

    #ifdef FlexPWM0_CTRL2_sub3              /* CTRL2 register */
        pPWM0->SUB[3].CTRL2.R   = FlexPWM0_CTRL2_sub3;
    #endif

    #ifdef FlexPWM0_CTRL1_sub3              /* CTRL register */
        pPWM0->SUB[3].CTRL1.R    = FlexPWM0_CTRL1_sub3;
    #endif

    #ifdef FlexPWM0_VAL0_sub3              /* VAL0 register */
        pPWM0->SUB[3].VAL0.R  = FlexPWM0_VAL0_sub3;
    #endif

    #ifdef FlexPWM0_VAL1_sub3              /* VAL1 register */
        pPWM0->SUB[3].VAL1.R  = FlexPWM0_VAL1_sub3;
    #endif

    #ifdef FlexPWM0_VAL2_sub3              /* VAL2 register */
        pPWM0->SUB[3].VAL2.R  = FlexPWM0_VAL2_sub3;
    #endif

    #ifdef FlexPWM0_VAL3_sub3              /* VAL3 register */
        pPWM0->SUB[3].VAL3.R  = FlexPWM0_VAL3_sub3;
    #endif

    #ifdef FlexPWM0_VAL4_sub3              /* VAL4 register */
        pPWM0->SUB[3].VAL4.R  = FlexPWM0_VAL4_sub3;
    #endif

    #ifdef FlexPWM0_VAL5_sub3              /* VAL5 register */
        pPWM0->SUB[3].VAL5.R  = FlexPWM0_VAL5_sub3;
    #endif

    #ifdef FlexPWM0_OCTRL_sub3             /* OCTRL register */
        pPWM0->SUB[3].OCTRL.R   = FlexPWM0_OCTRL_sub3;
    #endif

    #ifdef FlexPWM0_INTEN_sub3             /* INTEN register */
        pPWM0->SUB[3].INTEN.R   = FlexPWM0_INTEN_sub3;
    #endif

    #ifdef FlexPWM0_DMAEN_sub3             /* DMAEN register */
        pPWM0->SUB[3].DMAEN.R   = FlexPWM0_DMAEN_sub3;
    #endif

    #ifdef FlexPWM0_TCTRL_sub3             /* TCTRL register */
        pPWM0->SUB[3].TCTRL.R   = FlexPWM0_TCTRL_sub3;
    #endif

    #ifdef FlexPWM0_DISMAP_sub3            /* DISMAP register */
        pPWM0->SUB[3].DISMAP.R  = FlexPWM0_DISMAP_sub3;
    #endif

    #ifdef FlexPWM0_DTCNT0_sub3            /* DTCNT0 register */
        pPWM0->SUB[3].DTCNT0.R  = FlexPWM0_DTCNT0_sub3;
    #endif

    #ifdef FlexPWM0_DTCNT1_sub3            /* DTCNT1 register */
        pPWM0->SUB[3].DTCNT1.R  = FlexPWM0_DTCNT1_sub3;
    #endif

    #ifdef FlexPWM0_CAPTCTRLX_sub3          /* CAPCTRLX register */
        pPWM0->SUB[3].CAPTCTRLX.R    = FlexPWM0_CAPTCTRLX_sub3;
    #endif

    #ifdef FlexPWM0_CAPTCOMPX_sub3          /* CAPTCOMPX register */
        pPWM0->SUB[3].CAPTCOMPX.R   = FlexPWM0_CAPTCOMPX_sub3;
    #endif

    #ifdef FlexPWM0_MCTRL                  /* MCTRL register */
        pPWM0->MCTRL.R      |= FlexPWM0_MCTRL;
    #endif

    /* read LDOK bits first then set */
    ldok_test = pPWM0->MCTRL.B.LDOK;    // Read the LDOK bit field first
    pPWM0->MCTRL.R          |= LDOK_SUB0|LDOK_SUB1|LDOK_SUB2|LDOK_SUB3;

}

/***************************************************************************//*!
@brief          FlexPWM1 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the PWM1
                module.

@note

@warning
******************************************************************************/
void flexpwm1_init(void)
{
    static vuint8_t  i,j;
    vuint8_t     ldok_test;

    pPWM1 = &FlexPWM_1;

    /*-------------------------------------------------------------------------
     * FlexPWM1 Reset
    --------------------------------------------------------------------------*/
    for (j=0;j<=3;j++)
    {
        pPWM1->SUB[j].INIT.R		= 0x0;
        pPWM1->SUB[j].CTRL2.R       = 0x0;
        pPWM1->SUB[j].CTRL1.R       = 0x0400U;
        pPWM1->SUB[j].VAL0.R		= 0x0;
        pPWM1->SUB[j].VAL1.R		= 0x0;
        pPWM1->SUB[j].VAL2.R		= 0x0;
        pPWM1->SUB[j].VAL3.R		= 0x0;
        pPWM1->SUB[j].VAL4.R		= 0x0;
        pPWM1->SUB[j].VAL5.R		= 0x0;
        pPWM1->SUB[j].OCTRL.R       = 0x0;
        pPWM1->SUB[j].INTEN.R       = 0x0;
        pPWM1->SUB[j].DMAEN.R       = 0x0;
        pPWM1->SUB[j].TCTRL.R       = 0x0;
        pPWM1->SUB[j].DISMAP.R      = 0xFFFFU;
        pPWM1->SUB[j].DTCNT0.R      = 0x07FFU;
        pPWM1->SUB[j].DTCNT1.R      = 0x07FFU;
        pPWM1->SUB[j].CAPTCTRLX.R   = 0x0;
        pPWM1->SUB[j].CAPTCMPX.R	= 0x0;
    }
    pPWM1->OUTEN.R          = 0x0;
    pPWM1->MASK.R           = 0x0;
    pPWM1->SWCOUT.R         = 0x0;
    pPWM1->DTSRCSEL.R       = 0x0;
    pPWM1->MCTRL.R          = 0x0;
    pPWM1->FCTRL.R          = 0x0;
    pPWM1->FSTS.R           = 0xF;	/* Clear Fault PIN flags manually */
    pPWM1->FFILT.R          = 0x0;


    /*-------------------------------------------------------------------------
     * FlexPWM1 Control registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM1_OUTEN                  /* OUTEN register */
        pPWM1->OUTEN.R          = FlexPWM1_OUTEN;
    #endif

    #ifdef FlexPWM1_MASK                   /* MASK register */
        pPWM1->MASK.R           = FlexPWM1_MASK;
    #endif

    #ifdef FlexPWM1_SWCOUT                 /* SWCOUT register */
        pPWM1->SWCOUT.R         = FlexPWM1_SWCOUT;
    #endif

    #ifdef FlexPWM1_DTSRCSEL               /* DTSRCSEL register */
        pPWM1->DTSRCSEL.R       = FlexPWM1_DTSRCSEL;
    #endif

    #ifdef FlexPWM1_FCTRL                  /* FCTRL register */
        pPWM1->FCTRL.R          = FlexPWM1_FCTRL;
    #endif

    #ifdef FlexPWM1_FFILT                  /* FFILT register */
        pPWM1->FFILT.R          = FlexPWM1_FFILT;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM1 sub0 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM1_INIT_sub0              /* INIT register */
        pPWM1->SUB[0].INIT.R    = FlexPWM1_INIT_sub0;
    #endif

    #ifdef FlexPWM1_CTRL2_sub0              /* CTRL2 register */
        pPWM1->SUB[0].CTRL2.R   = FlexPWM1_CTRL2_sub0;
    #endif

    #ifdef FlexPWM1_CTRL1_sub0              /* CTRL register */
        pPWM1->SUB[0].CTRL1.R    = FlexPWM1_CTRL1_sub0;
    #endif

    #ifdef FlexPWM1_VAL0_sub0              /* VAL0 register */
        pPWM1->SUB[0].VAL0.R  = FlexPWM1_VAL0_sub0;
    #endif

    #ifdef FlexPWM1_VAL1_sub0              /* VAL1 register */
        pPWM1->SUB[0].VAL1.R  = FlexPWM1_VAL1_sub0;
    #endif

    #ifdef FlexPWM1_VAL2_sub0              /* VAL2 register */
        pPWM1->SUB[0].VAL2.R  = FlexPWM1_VAL2_sub0;
    #endif

    #ifdef FlexPWM1_VAL3_sub0              /* VAL3 register */
        pPWM1->SUB[0].VAL3.R  = FlexPWM1_VAL3_sub0;
    #endif

    #ifdef FlexPWM1_VAL4_sub0              /* VAL4 register */
        pPWM1->SUB[0].VAL4.R  = FlexPWM1_VAL4_sub0;
    #endif

    #ifdef FlexPWM1_VAL5_sub0              /* VAL5 register */
        pPWM1->SUB[0].VAL5.R  = FlexPWM1_VAL5_sub0;
    #endif

    #ifdef FlexPWM1_OCTRL_sub0             /* OCTRL register */
        pPWM1->SUB[0].OCTRL.R   = FlexPWM1_OCTRL_sub0;
    #endif

    #ifdef FlexPWM1_INTEN_sub0             /* INTEN register */
        pPWM1->SUB[0].INTEN.R   = FlexPWM1_INTEN_sub0;
    #endif

    #ifdef FlexPWM1_DMAEN_sub0             /* DMAEN register */
        pPWM1->SUB[0].DMAEN.R   = FlexPWM1_DMAEN_sub0;
    #endif

    #ifdef FlexPWM1_TCTRL_sub0             /* TCTRL register */
        pPWM1->SUB[0].TCTRL.R   = FlexPWM1_TCTRL_sub0;
    #endif

    #ifdef FlexPWM1_DISMAP_sub0            /* DISMAP register */
        pPWM1->SUB[0].DISMAP.R  = FlexPWM1_DISMAP_sub0;
    #endif

    #ifdef FlexPWM1_DTCNT0_sub0            /* DTCNT0 register */
        pPWM1->SUB[0].DTCNT0.R  = FlexPWM1_DTCNT0_sub0;
    #endif

    #ifdef FlexPWM1_DTCNT1_sub0            /* DTCNT1 register */
        pPWM1->SUB[0].DTCNT1.R  = FlexPWM1_DTCNT1_sub0;
    #endif

    #ifdef FlexPWM1_CAPTCTRLX_sub0          /* CAPCTRLX register */
        pPWM1->SUB[0].CAPTCTRLX.R    = FlexPWM1_CAPTCTRLX_sub0;
    #endif

    #ifdef FlexPWM1_CAPTCOMPX_sub0          /* CAPTCOMPX register */
        pPWM1->SUB[0].CAPTCOMPX.R   = FlexPWM1_CAPTCOMPX_sub0;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM1 sub1 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM1_INIT_sub1              /* INIT register */
        pPWM1->SUB[1].INIT.R    = FlexPWM1_INIT_sub1;
    #endif

    #ifdef FlexPWM1_CTRL2_sub1              /* CTRL2 register */
        pPWM1->SUB[1].CTRL2.R   = FlexPWM1_CTRL2_sub1;
    #endif

    #ifdef FlexPWM1_CTRL1_sub1              /* CTRL register */
        pPWM1->SUB[1].CTRL1.R    = FlexPWM1_CTRL1_sub1;
    #endif

    #ifdef FlexPWM1_VAL0_sub1              /* VAL0 register */
        pPWM1->SUB[1].VAL0.R  = FlexPWM1_VAL0_sub1;
    #endif

    #ifdef FlexPWM1_VAL1_sub1              /* VAL1 register */
        pPWM1->SUB[1].VAL1.R  = FlexPWM1_VAL1_sub1;
    #endif

    #ifdef FlexPWM1_VAL2_sub1              /* VAL2 register */
        pPWM1->SUB[1].VAL2.R  = FlexPWM1_VAL2_sub1;
    #endif

    #ifdef FlexPWM1_VAL3_sub1              /* VAL3 register */
        pPWM1->SUB[1].VAL3.R  = FlexPWM1_VAL3_sub1;
    #endif

    #ifdef FlexPWM1_VAL4_sub1              /* VAL4 register */
        pPWM1->SUB[1].VAL4.R  = FlexPWM1_VAL4_sub1;
    #endif

    #ifdef FlexPWM1_VAL5_sub1              /* VAL5 register */
        pPWM1->SUB[1].VAL5.R  = FlexPWM1_VAL5_sub1;
    #endif

    #ifdef FlexPWM1_OCTRL_sub1             /* OCTRL register */
        pPWM1->SUB[1].OCTRL.R   = FlexPWM1_OCTRL_sub1;
    #endif

    #ifdef FlexPWM1_INTEN_sub1             /* INTEN register */
        pPWM1->SUB[1].INTEN.R   = FlexPWM1_INTEN_sub1;
    #endif

    #ifdef FlexPWM1_DMAEN_sub1             /* DMAEN register */
        pPWM1->SUB[1].DMAEN.R   = FlexPWM1_DMAEN_sub1;
    #endif

    #ifdef FlexPWM1_TCTRL_sub1             /* TCTRL register */
        pPWM1->SUB[1].TCTRL.R   = FlexPWM1_TCTRL_sub1;
    #endif

    #ifdef FlexPWM1_DISMAP_sub1            /* DISMAP register */
        pPWM1->SUB[1].DISMAP.R  = FlexPWM1_DISMAP_sub1;
    #endif

    #ifdef FlexPWM1_DTCNT0_sub1            /* DTCNT0 register */
        pPWM1->SUB[1].DTCNT0.R  = FlexPWM1_DTCNT0_sub1;
    #endif

    #ifdef FlexPWM1_DTCNT1_sub1            /* DTCNT1 register */
        pPWM1->SUB[1].DTCNT1.R  = FlexPWM1_DTCNT1_sub1;
    #endif

    #ifdef FlexPWM1_CAPTCTRLX_sub1          /* CAPCTRLX register */
        pPWM1->SUB[1].CAPTCTRLX.R    = FlexPWM1_CAPTCTRLX_sub1;
    #endif

    #ifdef FlexPWM1_CAPTCOMPX_sub1          /* CAPTCOMPX register */
        pPWM1->SUB[1].CAPTCOMPX.R   = FlexPWM1_CAPTCOMPX_sub1;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM1 sub2 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM1_INIT_sub2              /* INIT register */
        pPWM1->SUB[2].INIT.R    = FlexPWM1_INIT_sub2;
    #endif

    #ifdef FlexPWM1_CTRL2_sub2              /* CTRL2 register */
        pPWM1->SUB[2].CTRL2.R   = FlexPWM1_CTRL2_sub2;
    #endif

    #ifdef FlexPWM1_CTRL1_sub2              /* CTRL register */
        pPWM1->SUB[2].CTRL1.R    = FlexPWM1_CTRL1_sub2;
    #endif

    #ifdef FlexPWM1_VAL0_sub2              /* VAL0 register */
        pPWM1->SUB[2].VAL0.R  = FlexPWM1_VAL0_sub2;
    #endif

    #ifdef FlexPWM1_VAL1_sub2              /* VAL1 register */
        pPWM1->SUB[2].VAL1.R  = FlexPWM1_VAL1_sub2;
    #endif

    #ifdef FlexPWM1_VAL2_sub2              /* VAL2 register */
        pPWM1->SUB[2].VAL2.R  = FlexPWM1_VAL2_sub2;
    #endif

    #ifdef FlexPWM1_VAL3_sub2              /* VAL3 register */
        pPWM1->SUB[2].VAL3.R  = FlexPWM1_VAL3_sub2;
    #endif

    #ifdef FlexPWM1_VAL4_sub2              /* VAL4 register */
        pPWM1->SUB[2].VAL4.R  = FlexPWM1_VAL4_sub2;
    #endif

    #ifdef FlexPWM1_VAL5_sub2              /* VAL5 register */
        pPWM1->SUB[2].VAL5.R  = FlexPWM1_VAL5_sub2;
    #endif

    #ifdef FlexPWM1_OCTRL_sub2             /* OCTRL register */
        pPWM1->SUB[2].OCTRL.R   = FlexPWM1_OCTRL_sub2;
    #endif

    #ifdef FlexPWM1_INTEN_sub2             /* INTEN register */
        pPWM1->SUB[2].INTEN.R   = FlexPWM1_INTEN_sub2;
    #endif

    #ifdef FlexPWM1_DMAEN_sub2             /* DMAEN register */
        pPWM1->SUB[2].DMAEN.R   = FlexPWM1_DMAEN_sub2;
    #endif

    #ifdef FlexPWM1_TCTRL_sub2             /* TCTRL register */
        pPWM1->SUB[2].TCTRL.R   = FlexPWM1_TCTRL_sub2;
    #endif

    #ifdef FlexPWM1_DISMAP_sub2            /* DISMAP register */
        pPWM1->SUB[2].DISMAP.R  = FlexPWM1_DISMAP_sub2;
    #endif

    #ifdef FlexPWM1_DTCNT0_sub2            /* DTCNT0 register */
        pPWM1->SUB[2].DTCNT0.R  = FlexPWM1_DTCNT0_sub2;
    #endif

    #ifdef FlexPWM1_DTCNT1_sub2            /* DTCNT1 register */
        pPWM1->SUB[2].DTCNT1.R  = FlexPWM1_DTCNT1_sub2;
    #endif

    #ifdef FlexPWM1_CAPTCTRLX_sub2          /* CAPCTRLX register */
        pPWM1->SUB[2].CAPTCTRLX.R    = FlexPWM1_CAPTCTRLX_sub2;
    #endif

    #ifdef FlexPWM1_CAPTCOMPX_sub2          /* CAPTCOMPX register */
        pPWM1->SUB[2].CAPTCOMPX.R   = FlexPWM1_CAPTCOMPX_sub2;
    #endif

    /*-------------------------------------------------------------------------
     * FlexPWM1 sub3 registers
    --------------------------------------------------------------------------*/
    #ifdef FlexPWM1_INIT_sub3              /* INIT register */
        pPWM1->SUB[3].INIT.R    = FlexPWM1_INIT_sub3;
    #endif

    #ifdef FlexPWM1_CTRL2_sub3              /* CTRL2 register */
        pPWM1->SUB[3].CTRL2.R   = FlexPWM1_CTRL2_sub3;
    #endif

    #ifdef FlexPWM1_CTRL1_sub3              /* CTRL register */
        pPWM1->SUB[3].CTRL1.R    = FlexPWM1_CTRL1_sub3;
    #endif

    #ifdef FlexPWM1_VAL0_sub3              /* VAL0 register */
        pPWM1->SUB[3].VAL0.R  = FlexPWM1_VAL0_sub3;
    #endif

    #ifdef FlexPWM1_VAL1_sub3              /* VAL1 register */
        pPWM1->SUB[3].VAL1.R  = FlexPWM1_VAL1_sub3;
    #endif

    #ifdef FlexPWM1_VAL2_sub3              /* VAL2 register */
        pPWM1->SUB[3].VAL2.R  = FlexPWM1_VAL2_sub3;
    #endif

    #ifdef FlexPWM1_VAL3_sub3              /* VAL3 register */
        pPWM1->SUB[3].VAL3.R  = FlexPWM1_VAL3_sub3;
    #endif

    #ifdef FlexPWM1_VAL4_sub3              /* VAL4 register */
        pPWM1->SUB[3].VAL4.R  = FlexPWM1_VAL4_sub3;
    #endif

    #ifdef FlexPWM1_VAL5_sub3              /* VAL5 register */
        pPWM1->SUB[3].VAL5.R  = FlexPWM1_VAL5_sub3;
    #endif

    #ifdef FlexPWM1_OCTRL_sub3             /* OCTRL register */
        pPWM1->SUB[3].OCTRL.R   = FlexPWM1_OCTRL_sub3;
    #endif

    #ifdef FlexPWM1_INTEN_sub3             /* INTEN register */
        pPWM1->SUB[3].INTEN.R   = FlexPWM1_INTEN_sub3;
    #endif

    #ifdef FlexPWM1_DMAEN_sub3             /* DMAEN register */
        pPWM1->SUB[3].DMAEN.R   = FlexPWM1_DMAEN_sub3;
    #endif

    #ifdef FlexPWM1_TCTRL_sub3             /* TCTRL register */
        pPWM1->SUB[3].TCTRL.R   = FlexPWM1_TCTRL_sub3;
    #endif

    #ifdef FlexPWM1_DISMAP_sub3            /* DISMAP register */
        pPWM1->SUB[3].DISMAP.R  = FlexPWM1_DISMAP_sub3;
    #endif

    #ifdef FlexPWM1_DTCNT0_sub3            /* DTCNT0 register */
        pPWM1->SUB[3].DTCNT0.R  = FlexPWM1_DTCNT0_sub3;
    #endif

    #ifdef FlexPWM1_DTCNT1_sub3            /* DTCNT1 register */
        pPWM1->SUB[3].DTCNT1.R  = FlexPWM1_DTCNT1_sub3;
    #endif

    #ifdef FlexPWM1_CAPTCTRLX_sub3          /* CAPCTRLX register */
        pPWM1->SUB[3].CAPTCTRLX.R    = FlexPWM1_CAPTCTRLX_sub3;
    #endif

    #ifdef FlexPWM1_CAPTCOMPX_sub3          /* CAPTCOMPX register */
        pPWM1->SUB[3].CAPTCOMPX.R   = FlexPWM1_CAPTCOMPX_sub3;
    #endif

    #ifdef FlexPWM1_MCTRL                  /* MCTRL register */
        pPWM1->MCTRL.R      |= FlexPWM1_MCTRL;
    #endif

    /* read LDOK bits first then set */
    ldok_test = pPWM1->MCTRL.B.LDOK;    // Read the LDOK bit field first
    pPWM1->MCTRL.R          |= LDOK_SUB0|LDOK_SUB1|LDOK_SUB2|LDOK_SUB3;

}


/******************************************************************************
* Inline functions
*******************************************************************************/
/*------------------------------------------------------------------------*//*!
@brief        Inline function for enabling PWM outputs

@return       void
*//*-------------------------------------------------------------------------*/
inline void flexpwm_enable_outputs(volatile struct FlexPWM_tag *ptrPWM)
{
    ptrPWM->MASK.R = 0x0;
}

/*------------------------------------------------------------------------*//*!
@brief      Inline function for disabling PWM outputs

@return     void

@note       PWM outputs are disabled by internal masking out of generated
            PWM signals
*//*-------------------------------------------------------------------------*/
inline void flexpwm_disable_outputs(volatile struct FlexPWM_tag *ptrPWM)
{
    ptrPWM->MASK.R = 0x0EEE; // Sub1/2/3
}


/**********another kind of FlexPWM0 initial***************/

/* *****************************************************************************
   Function:        void FlexPWM0_Init_v1(void)
   Description:     FlexPWM Module 0 Initialization
                    FlexPWM[0].[3]: Independent PWM Output, Edge Aligned Mode
                    No Dead Time Insertion, Duty Cycle: PWMA 75%; PWMB: 25%
   Parameters:      Input:    void
                    Output:   void
   Notes:
   ***************************************************************************** */
void FlexPWM0_Init_v1(void)
{
  pPWM0 = &FlexPWM_0;
// Initialize FlexPWM Module 0
  pPWM0->MCTRL.B.RUN          = 0;             // Stop All Channels

// SubModule 3 Configuration
// Center Aligned Mode, No Dead Time Insertion, Duty Cycle: PWMA 75%; PWMB: 25%
  pPWM0->SUB[3].CTRL1.B.FULL   = 0;             // Full Cycle ReLoad Disabled
  pPWM0->SUB[3].CTRL1.B.HALF   = 1;             // Half-Cycle Reloads Enabled
  pPWM0->SUB[3].CTRL1.B.DBLEN = 0;             // Double Switching Disabled
  pPWM0->SUB[3].CTRL1.B.PRSC   = 7;             // PreScaler = 2 ^ PRSC
  pPWM0->SUB[3].CTRL2.B.INDEP = 1;             // PWMA & PWMB Outputs Are Complementary (0) / Independent (1)
  pPWM0->SUB[3].CTRL2.B.DBGEN = 1;             // PWM Runs In DeBug Mode
  pPWM0->SUB[3].DTCNT0.R      = 0x0000;        // PWMA Dead Time
  pPWM0->SUB[3].DTCNT1.R      = 0x0000;        // PWMB Dead Time
  pPWM0->SUB[3].DISMAP.R      = 0xF000;        // ReSet PWMA And PWMB Fault Disable Mask Of Selected SubModule

  pPWM0->SUB[3].INIT.R        = 0xFF00;        // Initial Count Value
  pPWM0->SUB[3].VAL0.R      = 0x0000;        // Mid-Cycle ReLoad Point
  pPWM0->SUB[3].VAL1.R      = 0x0100;        // Max. Value For Counter

  pPWM0->SUB[3].VAL2.R      = 0xFF00;
  pPWM0->SUB[3].VAL3.R      = 0x0080;
  pPWM0->SUB[3].VAL4.R      = 0xFF00;
  pPWM0->SUB[3].VAL5.R      = 0xFF80;


/*****Center Aligned Mode, No Dead Time Insertion, Duty Cycle: PWMA 66%; PWMB: 33%******/
#if 0
  pPWM0->SUB[3].VAL2.R      = 0xFF55;
  pPWM0->SUB[3].VAL3.R      = 0x00AA;
  pPWM0->SUB[3].VAL4.R      = 0xFFAA;
  pPWM0->SUB[3].VAL5.R      = 0x0055;
#endif

  pPWM0->OUTEN.B.PWMA_EN     |= 1 << 3;
  pPWM0->OUTEN.B.PWMB_EN     |= 1 << 3;
  pPWM0->OUTEN.B.PWMX_EN     |= 1 << 3;
  pPWM0->MCTRL.B.RUN         |= 1 << 3;

  pPWM0->MCTRL.B.LDOK        |= 1 << 3;        // Load New Sub Module 3 Values
}

#if 0
/* *****************************************************************************
   Function:        void FlexPWM0_Init_v2(void)
   Description:     FlexPWM Module 0 Initialization
                    FlexPWM[0].[3]: Independent PWM Output, Phase Shifted (25% Period) Output
                    No Dead Time Insertion, PWM Duty Cycle: 50%, Phase-Shift (25% Period)
   Parameters:      Input:    void
                    Output:   void
   Notes:
   ***************************************************************************** */
void FlexPWM0_Init_v2(void)
{
  pPWM0 = &FlexPWM_0;
// Initialize FlexPWM Module 0
  pPWM0.MCTRL.B.RUN          = 0;             // Stop All Channels

// SubModule 3 Configuration
// Phase Shifted (25% Period) Output, No Dead Time Insertion, PWM Duty Cycle: 50%
  pPWM0->SUB[3].CTRL1.B.FULL   = 0;             // Full Cycle ReLoad Disabled
  pPWM0->SUB[3].CTRL1.B.HALF   = 1;             // Half-Cycle Reloads Enabled
  pPWM0->SUB[3].CTRL1.B.DBLEN = 0;             // Double Switching Disabled
  pPWM0->SUB[3].CTRL1.B.PRSC   = 7;             // PreScaler = 2 ^ PRSC
  pPWM0->SUB[3].CTRL2.B.INDEP = 1;             // PWMA & PWMB Outputs Are Complementary (0) / Independent (1)
  pPWM0->SUB[3].CTRL2.B.DBGEN = 1;             // PWM Runs In DeBug Mode
  pPWM0->SUB[3].DTCNT0.R      = 0x0000;        // PWMA Dead Time
  pPWM0->SUB[3].DTCNT1.R      = 0x0000;        // PWMB Dead Time
  pPWM0->SUB[3].DISMAP.R      = 0xF000;        // ReSet PWMA And PWMB Fault Disable Mask Of Selected SubModule

  pPWM0->SUB[3].INIT.R        = 0xFF00;        // Initial Count Value
  pPWM0->SUB[3].VAL0.R      = 0x0000;        // Mid-Cycle ReLoad Point
  pPWM0->SUB[3].VAL1.R      = 0x0100;        // Max. Value For Counter

  pPWM0->SUB[3].VAL2.R      = 0xFF40;
  pPWM0->SUB[3].VAL3.R      = 0x0040;
  pPWM0->SUB[3].VAL4.R      = 0xFFC0;
  pPWM0->SUB[3].VAL5.R      = 0x00C0;

  pPWM0->OUTEN.B.PWMA_EN     |= 1 << 3;
  pPWM0->OUTEN.B.PWMB_EN     |= 1 << 3;
  pPWM0->OUTEN.B.PWMX_EN     |= 1 << 3;
  pPWM0->MCTRL.B.RUN         |= 1 << 3;

  pPWM0->MCTRL.B.LDOK        |= 1 << 3;        // Load New Sub Module 3 Values
}
#endif


/* *****************************************************************************
   Function:        void FlexPWM0_Init_v3(void)
   Description:     FlexPWM Module 0 Initialization
                    FlexPWM[0].[3]: Independent PWM Output, Edge Aligned Mode
                    No Dead Time Insertion, Duty Cycle: PWMA Duty Cycle Decided By ADC[1].[5]; PWMB Duty Cycle Is 100%-PWMA
   Parameters:      Input:    void
                    Output:   void
   Notes:
   ***************************************************************************** */
void FlexPWM0_Init_v3(void)
{
   pPWM0 = &FlexPWM_0;
// Initialize FlexPWM Module 0
  pPWM0->MCTRL.B.RUN               = 0;        // Stop All Channels

// SubModule 3 Configuration
// Edge Aligned Mode, No Dead Time Insertion, Duty Cycle: PWMA Duty Cycle Decided By ADC[1].[5]; PWMB Duty Cycle Is 100%-PWMA
  pPWM0->SUB[3].CTRL1.B.LDFQ        = 0;        // Every PWM Opportunity
  pPWM0->SUB[3].CTRL1.B.FULL        = 1;        // Full Cycle ReLoad Enabled
  pPWM0->SUB[3].CTRL1.B.HALF        = 0;        // Half-Cycle ReLoad Disabled
  pPWM0->SUB[3].CTRL1.B.DBLEN      = 0;        // Double Switching Disabled
  pPWM0->SUB[3].CTRL1.B.PRSC        = 7;        // PreScaler = 2 ^ PRSC = 128

  pPWM0->SUB[3].CTRL2.B.INDEP      = 1;        // PWMA & PWMB Outputs Are Complementary (0) / Independent (1)
  pPWM0->SUB[3].CTRL2.B.DBGEN      = 1;        // PWM Runs In DeBug Mode
  //pPWM0->SUB[3].CTRL2.B.WAITEN     = 0;        // Wait Disabled
  pPWM0->SUB[3].CTRL2.B.PWM23_INIT = 0;        // PWM23 Initial Value
  pPWM0->SUB[3].CTRL2.B.PWM45_INIT = 0;        // PWM45 Initial Value
  pPWM0->SUB[3].CTRL2.B.PWMX_INIT  = 0;        // PWMX Initial Value
  pPWM0->SUB[3].CTRL2.B.INIT_SEL   = 0;        // 00 = Local Sync (PWMX) Causes Initialization
  pPWM0->SUB[3].CTRL2.B.FRCEN      = 0;        // Initialization From A Force Out Event Is Disabled
  pPWM0->SUB[3].CTRL2.B.FORCE      = 0;        // Force Initialization
  pPWM0->SUB[3].CTRL2.B.FORCE_SEL  = 0;        // Force Source Select
  pPWM0->SUB[3].CTRL2.B.RELOAD_SEL = 0;        // The Local RELOAD Signal Is Used To ReLoad Registers
  pPWM0->SUB[3].CTRL2.B.CLK_SEL    = 0;        // The IPBus Clock Is Used

  pPWM0->SUB[3].DTCNT0.R           = 0x0000;   // PWMA Dead Time
  pPWM0->SUB[3].DTCNT1.R           = 0x0000;   // PWMB Dead Time
  pPWM0->SUB[3].DISMAP.R           = 0xF000;   // ReSet PWMA And PWMB Fault Disable Mask Of Selected SubModule

  pPWM0->SUB[3].INIT.R             = 0xFF00;   // Initial Count Value
  pPWM0->SUB[3].VAL0.R           = 0x0000;   // Mid-Cycle ReLoad Point
  pPWM0->SUB[3].VAL1.R           = 0x0100;   // Max. Value For Counter
  pPWM0->SUB[3].VAL2.R           = 0xFF00;
  pPWM0->SUB[3].VAL4.R           = 0xFF00;

  pPWM0->OUTEN.B.PWMA_EN          |= 1 << 3;
  pPWM0->OUTEN.B.PWMB_EN          |= 1 << 3;
  pPWM0->OUTEN.B.PWMX_EN          |= 1 << 3;
  pPWM0->MCTRL.B.RUN              |= 1 << 3;   // Run PWM

  pPWM0->MCTRL.B.LDOK             |= 1 << 3;   // Load New Sub Module 3 Values
}

/* END OF FILE */
