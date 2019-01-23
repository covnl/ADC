/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     ctu.c
*
* @author   r63172
*
* @version  1.0.1.0
*
* @date     Nov-15-2010
*
* @brief    CTU - Cross Triggering Unit for MPC5604P
*
*******************************************************************************
*
* This file includes initial setting function of MPC5604P CTU peripheral module.
*
******************************************************************************/
#include "ctu.h"
#include "Defines.h"
#include "EXTGLOBALS.h"
#include "SIUL.h"

volatile struct CTU_tag *pCTU_0;
volatile struct CTU_tag *pCTU_1;


/******************************************************************************
* CTU functions
*****************************************************************************/

/***************************************************************************//*!
@brief          Cross Triggering Unit 0 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the CTU.

@note

@warning
******************************************************************************/

void ctu0_init(void)
{
    static vuint8_t         i;
    static vuint32_t        readValue32;

    // initialization of peripheral base address
    pCTU_0 = &CTU_0;

    /*-------------------------------------------------------------------------
     * CTU registers reset
    --------------------------------------------------------------------------*/
    pCTU_0->TGSISR.R          	= 0x0;
    pCTU_0->TGSCR.R           	= 0x0;

    for (i = 0; i<=7; i++)
        pCTU_0->TCR[i].R        = 0x0;

    pCTU_0->TGSCCR.R          	= 0x0;
    pCTU_0->TGSCRR.R          	= 0x0;
    pCTU_0->CLCR1.R           	= 0x0;
    pCTU_0->CLCR2.R           	= 0x0;
    pCTU_0->THCR1.R           	= 0x0;
    pCTU_0->THCR2.R           	= 0x0;

    for (i = 0; i<=23; i++)
    	pCTU_0->CLR[i].B.R		= 0x0;

    pCTU_0->FDCR.R				= 0x0F00U;
    pCTU_0->FCR.R             	= 0x0;
    pCTU_0->FTH.R				= 0x0;

    for (i = 0; i<=3; i++)
        pCTU_0->FL[i].R         = 0x0;

    for (i = 0; i<=3; i++)
        pCTU_0->FR[i].R         = 0x0;

    pCTU_0->EFR.R				= 0x0000U;
    pCTU_0->IFR.R				= 0x0000U;   //interrupt flag register
    pCTU_0->IR.R           		= 0x0000U;  ///interrupt enable register
    pCTU_0->COTR.R           	= 0x0000U;
    pCTU_0->CR.R				= 0x0000U;
    pCTU_0->DFR.R				= 0x0000U;
    pCTU_0->EXPAR.R				= 0xFFFFU;
    pCTU_0->EXPBR.R				= 0xFFFFU;
    pCTU_0->CNTRNGR.R			= 0x0000U;
    pCTU_0->LISTCSR.R			= 0x00000000UL;

    /*-------------------------------------------------------------------------
     * CTU Control registers
    --------------------------------------------------------------------------*/
    #ifdef CTU0_TGSISR                   /* TGSISR register */
        pCTU_0->TGSISR.R     = CTU0_TGSISR;
    #endif

    #ifdef CTU0_TGSCR                    /* TGSCR register */
        pCTU_0->TGSCR.R      = CTU0_TGSCR;
    #endif

    #ifdef CTU0_T0CR                     /* TCR[0] register */
        pCTU_0->TCR[0].R     = CTU0_T0CR;
    #endif

    #ifdef CTU0_T1CR                     /* TCR[1] register */
        pCTU_0->TCR[1].R     = CTU0_T1CR;
    #endif

    #ifdef CTU0_T2CR                     /* TCR[2] register */
        pCTU_0->TCR[2].R     = CTU0_T2CR;
    #endif

    #ifdef CTU0_T3CR                     /* TCR[3] register */
        pCTU_0->TCR[3].R     = CTU0_T3CR;
    #endif

    #ifdef CTU0_T4CR                     /* TCR[4] register */
        pCTU_0->TCR[4].R     = CTU0_T4CR;
    #endif

    #ifdef CTU0_T5CR                     /* TCR[5] register */
        pCTU_0->TCR[5].R     = CTU0_T5CR;
    #endif

    #ifdef CTU0_T6CR                     /* TCR[6] register */
        pCTU_0->TCR[6].R     = CTU0_T6CR;
    #endif

    #ifdef CTU0_T7CR                     /* TCR[7] register */
        pCTU_0->TCR[7].R     = CTU0_T7CR;
    #endif

    #ifdef CTU0_TGSCCR                   /* TGSCCR register */
        pCTU_0->TGSCCR.R     = CTU0_TGSCCR;
    #endif

    #ifdef CTU0_TGSCRR                   /* TGSCRR register */
        pCTU_0->TGSCRR.R     = CTU0_TGSCRR;
    #endif

    #ifdef CTU0_CLCR1                    /* CLCR1 register */
        pCTU_0->CLCR1.R      = CTU0_CLCR1;
    #endif

    #ifdef CTU0_CLCR2                    /* CLCR2 register */
        pCTU_0->CLCR2.R      = CTU0_CLCR2;
    #endif

    #ifdef CTU0_THCR1                    /* THCR1 register */
        pCTU_0->THCR1.R      = CTU0_THCR1;
    #endif

    #ifdef CTU0_THCR2                    /* THCR2 register */
        pCTU_0->THCR2.R      = CTU0_THCR2;
    #endif

    #ifdef CTU0_CLR0                     /* CLR[0] register */
       pCTU_0->CLR[0].B.R       = CTU0_CLR0;
    #endif

    #ifdef CTU0_CLR1                     /* CLR_A_[1] register */
       pCTU_0->CLR[1].B.R       = CTU0_CLR1;
    #endif

    #ifdef CTU0_CLR2                     /* CLR_A_[2] register */
       pCTU_0->CLR[2].B.R       = CTU0_CLR2;
    #endif

    #ifdef CTU0_CLR3                     /* CLR[3] register */
       pCTU_0->CLR[3].B.R       = CTU0_CLR3;
    #endif

    #ifdef CTU0_CLR4                     /* CLR[4] register */
       pCTU_0->CLR[4].B.R       = CTU0_CLR4;
    #endif

    #ifdef CTU0_CLR5                     /* CLR[5] register */
       pCTU_0->CLR[5].B.R       = CTU0_CLR5;
    #endif

    #ifdef CTU0_CLR6                     /* CLR[6] register */
       pCTU_0->CLR[6].B.R       = CTU0_CLR6;
    #endif

    #ifdef CTU0_CLR7                     /* CLR[7] register */
       pCTU_0->CLR[7].B.R       = CTU0_CLR7;
    #endif

    #ifdef CTU0_CLR8                     /* CLR[8] register */
       pCTU_0->CLR[8].B.R       = CTU0_CLR8;
    #endif

    #ifdef CTU0_CLR9                     /* CLR[9] register */
       pCTU_0->CLR[9].B.R       = CTU0_CLR9;
    #endif

    #ifdef CTU0_CLR10                    /* CLR[10] register */
       pCTU_0->CLR[10].B.R      = CTU0_CLR10;
    #endif

    #ifdef CTU0_CLR11                    /* CLR[11] register */
       pCTU_0->CLR[11].B.R      = CTU0_CLR11;
    #endif

    #ifdef CTU0_CLR12                    /* CLR[12] register */
       pCTU_0->CLR[12].B.R      = CTU0_CLR12;
    #endif

    #ifdef CTU0_CLR13                    /* CLR[13] register */
       pCTU_0->CLR[13].B.R      = CTU0_CLR13;
    #endif

    #ifdef CTU0_CLR14                    /* CLR[14] register */
       pCTU_0->CLR[14].B.R      = CTU0_CLR14;
    #endif

    #ifdef CTU0_CLR15                    /* CLR[15] register */
       pCTU_0->CLR[15].B.R      = CTU0_CLR15;
    #endif

    #ifdef CTU0_CLR16                    /* CLR[16] register */
       pCTU_0->CLR[16].B.R      = CTU0_CLR16;
    #endif

    #ifdef CTU0_CLR17                    /* CLR[17] register */
       pCTU_0->CLR[17].B.R      = CTU0_CLR17;
    #endif

    #ifdef CTU0_CLR18                    /* CLR[18] register */
       pCTU_0->CLR[18].B.R      = CTU0_CLR18;
    #endif

    #ifdef CTU0_CLR19                    /* CLR[19] register */
       pCTU_0->CLR[19].B.R      = CTU0_CLR19;
    #endif

    #ifdef CTU0_CLR20                    /* CLR[20] register */
       pCTU_0->CLR[20].B.R      = CTU0_CLR20;
    #endif

    #ifdef CTU0_CLR21                    /* CLR[21] register */
       pCTU_0->CLR[21].B.R      = CTU0_CLR21;
    #endif

    #ifdef CTU0_CLR22                    /* CLR[22] register */
       pCTU_0->CLR[22].B.R      = CTU0_CLR22;
    #endif

    #ifdef CTU0_CLR23                    /* CLR[23] register */
       pCTU_0->CLR[23].B.R      = CTU0_CLR23;
    #endif

    #ifdef CTU0_FDCR                       /* CR register */
       pCTU_0->FDCR.R           = CTU0_FDCR;
    #endif

    #ifdef CTU0_FCR                      /* FCR register */
       pCTU_0->FCR.R          = CTU0_FCR;
    #endif

    #ifdef CTU0_FTH                      /* TH1 register */
       pCTU_0->FTH.R          = CTU0_FTH;
    #endif

    #ifdef CTU0_IR                    /* CTUIR register */
       pCTU_0->IR.R				= CTU0_IR;
    #endif

    #ifdef CTU0_COTR                     /* COTR register */
       pCTU_0->COTR.R         = CTU0_COTR;
    #endif

    #ifdef CTU0_DFR                /* DFR register */
       pCTU_0->DFR.R    = CTU0_DFR;
    #endif

	#ifdef CTU0_EXPAR                /* EXPAR register */
	   pCTU_0->EXPAR.R    = CTU0_EXPAR;
	#endif

	#ifdef CTU0_EXPBR                /* EXPBR register */
	   pCTU_0->EXPBR.R    = CTU0_EXPBR;
	#endif

	#ifdef CTU0_CNTRNGR                /* CNTRNGR register */
		   pCTU_0->CNTRNGR.R	= CTU0_CNTRNGR;
	#endif

	#ifdef CTU0_LISTCSR                /* LISTCSR register */
		   pCTU_0->LISTCSR.R	= CTU0_LISTCSR;
	#endif

	// must be defined last in order to correctly write to double buffered
    // registers using GRE and TGSISR_RE
    #ifdef CTU0_CTU0CR                    /* CR register */
       pCTU_0->CR.R        = (CTU0_CTU0CR & (0xFFFB)); // mask out MRS_SG bit
    #endif

       pCTU_0->CR.B.GRE           = 1;    // CTU General Reload Enable

    #ifdef CTU0_CTU0CR                    /* CR register */
       pCTU_0->CR.R        = (CTU0_CTU0CR & (0x4)); // enable MRS_SG bit
    #endif

}

/***************************************************************************//*!
@brief          Cross Triggering Unit 1 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the CTU.

@note

@warning
******************************************************************************/
void ctu1_init(void)
{
    static vuint8_t         i;
    static vuint32_t        readValue32;

    // initialization of peripheral base address
    pCTU_1 = &CTU_1;

    /*-------------------------------------------------------------------------
     * CTU registers reset
    --------------------------------------------------------------------------*/
    pCTU_1->TGSISR.R          	= 0x0;
    pCTU_1->TGSCR.R           	= 0x0;

    for (i = 0; i<=7; i++)
        pCTU_1->TCR[i].R        = 0x0;

    pCTU_1->TGSCCR.R          	= 0x0;
    pCTU_1->TGSCRR.R          	= 0x0;
    pCTU_1->CLCR1.R           	= 0x0;
    pCTU_1->CLCR2.R           	= 0x0;
    pCTU_1->THCR1.R           	= 0x0;
    pCTU_1->THCR2.R           	= 0x0;

    for (i = 0; i<=23; i++)
    	pCTU_1->CLR[i].B.R		= 0x0;

    pCTU_1->FDCR.R				= 0x0F00U;
    pCTU_1->FCR.R             	= 0x0;
    pCTU_1->FTH.R				= 0x0;

    for (i = 0; i<=3; i++)
        pCTU_1->FL[i].R         = 0x0;

    for (i = 0; i<=3; i++)
        pCTU_1->FR[i].R         = 0x0;

    pCTU_1->EFR.R				= 0x0000U;
    pCTU_1->IFR.R				= 0x0000U;
    pCTU_1->IR.R           		= 0x0000U;
    pCTU_1->COTR.R           	= 0x0000U;
    pCTU_1->CR.R				= 0x0000U;
    pCTU_1->DFR.R				= 0x0000U;
    pCTU_1->EXPAR.R				= 0xFFFFU;
    pCTU_1->EXPBR.R				= 0xFFFFU;
    pCTU_1->CNTRNGR.R			= 0x0000U;
    pCTU_1->LISTCSR.R			= 0x00000000UL;

    /*-------------------------------------------------------------------------
     * CTU Control registers
    --------------------------------------------------------------------------*/
    #ifdef CTU1_TGSISR                   /* TGSISR register */
        pCTU_1->TGSISR.R     = CTU1_TGSISR;
    #endif

    #ifdef CTU1_TGSCR                    /* TGSCR register */
        pCTU_1->TGSCR.R      = CTU1_TGSCR;
    #endif

    #ifdef CTU1_T0CR                     /* TCR[0] register */
        pCTU_1->TCR[0].R     = CTU1_T0CR;
    #endif

    #ifdef CTU1_T1CR                     /* TCR[1] register */
        pCTU_1->TCR[1].R     = CTU1_T1CR;
    #endif

    #ifdef CTU1_T2CR                     /* TCR[2] register */
        pCTU_1->TCR[2].R     = CTU1_T2CR;
    #endif

    #ifdef CTU1_T3CR                     /* TCR[3] register */
        pCTU_1->TCR[3].R     = CTU1_T3CR;
    #endif

    #ifdef CTU1_T4CR                     /* TCR[4] register */
        pCTU_1->TCR[4].R     = CTU1_T4CR;
    #endif

    #ifdef CTU1_T5CR                     /* TCR[5] register */
        pCTU_1->TCR[5].R     = CTU1_T5CR;
    #endif

    #ifdef CTU1_T6CR                     /* TCR[6] register */
        pCTU_1->TCR[6].R     = CTU1_T6CR;
    #endif

    #ifdef CTU1_T7CR                     /* TCR[7] register */
        pCTU_1->TCR[7].R     = CTU1_T7CR;
    #endif

    #ifdef CTU1_TGSCCR                   /* TGSCCR register */
        pCTU_1->TGSCCR.R     = CTU1_TGSCCR;
    #endif

    #ifdef CTU1_TGSCRR                   /* TGSCRR register */
        pCTU_1->TGSCRR.R     = CTU1_TGSCRR;
    #endif

    #ifdef CTU1_CLCR1                    /* CLCR1 register */
        pCTU_1->CLCR1.R      = CTU1_CLCR1;
    #endif

    #ifdef CTU1_CLCR2                    /* CLCR2 register */
        pCTU_1->CLCR2.R      = CTU1_CLCR2;
    #endif

    #ifdef CTU1_THCR1                    /* THCR1 register */
        pCTU_1->THCR1.R      = CTU1_THCR1;
    #endif

    #ifdef CTU1_THCR2                    /* THCR2 register */
        pCTU_1->THCR2.R      = CTU1_THCR2;
    #endif

    #ifdef CTU1_CLR0                     /* CLR[0] register */
       pCTU_1->CLR[0].B.R       = CTU1_CLR0;
    #endif

    #ifdef CTU1_CLR1                     /* CLR_A_[1] register */
       pCTU_1->CLR[1].B.R       = CTU1_CLR1;
    #endif

    #ifdef CTU1_CLR2                     /* CLR_A_[2] register */
       pCTU_1->CLR[2].B.R       = CTU1_CLR2;
    #endif

    #ifdef CTU1_CLR3                     /* CLR[3] register */
       pCTU_1->CLR[3].B.R       = CTU1_CLR3;
    #endif

    #ifdef CTU1_CLR4                     /* CLR[4] register */
       pCTU_1->CLR[4].B.R       = CTU1_CLR4;
    #endif

    #ifdef CTU1_CLR5                     /* CLR[5] register */
       pCTU_1->CLR[5].B.R       = CTU1_CLR5;
    #endif

    #ifdef CTU1_CLR6                     /* CLR[6] register */
       pCTU_1->CLR[6].B.R       = CTU1_CLR6;
    #endif

    #ifdef CTU1_CLR7                     /* CLR[7] register */
       pCTU_1->CLR[7].B.R       = CTU1_CLR7;
    #endif

    #ifdef CTU1_CLR8                     /* CLR[8] register */
       pCTU_1->CLR[8].B.R       = CTU1_CLR8;
    #endif

    #ifdef CTU1_CLR9                     /* CLR[9] register */
       pCTU_1->CLR[9].B.R       = CTU1_CLR9;
    #endif

    #ifdef CTU1_CLR10                    /* CLR[10] register */
       pCTU_1->CLR[10].B.R      = CTU1_CLR10;
    #endif

    #ifdef CTU1_CLR11                    /* CLR[11] register */
       pCTU_1->CLR[11].B.R      = CTU1_CLR11;
    #endif

    #ifdef CTU1_CLR12                    /* CLR[12] register */
       pCTU_1->CLR[12].B.R      = CTU1_CLR12;
    #endif

    #ifdef CTU1_CLR13                    /* CLR[13] register */
       pCTU_1->CLR[13].B.R      = CTU1_CLR13;
    #endif

    #ifdef CTU1_CLR14                    /* CLR[14] register */
       pCTU_1->CLR[14].B.R      = CTU1_CLR14;
    #endif

    #ifdef CTU1_CLR15                    /* CLR[15] register */
       pCTU_1->CLR[15].B.R      = CTU1_CLR15;
    #endif

    #ifdef CTU1_CLR16                    /* CLR[16] register */
       pCTU_1->CLR[16].B.R      = CTU1_CLR16;
    #endif

    #ifdef CTU1_CLR17                    /* CLR[17] register */
       pCTU_1->CLR[17].B.R      = CTU1_CLR17;
    #endif

    #ifdef CTU1_CLR18                    /* CLR[18] register */
       pCTU_1->CLR[18].B.R      = CTU1_CLR18;
    #endif

    #ifdef CTU1_CLR19                    /* CLR[19] register */
       pCTU_1->CLR[19].B.R      = CTU1_CLR19;
    #endif

    #ifdef CTU1_CLR20                    /* CLR[20] register */
       pCTU_1->CLR[20].B.R      = CTU1_CLR20;
    #endif

    #ifdef CTU1_CLR21                    /* CLR[21] register */
       pCTU_1->CLR[21].B.R      = CTU1_CLR21;
    #endif

    #ifdef CTU1_CLR22                    /* CLR[22] register */
       pCTU_1->CLR[22].B.R      = CTU1_CLR22;
    #endif

    #ifdef CTU1_CLR23                    /* CLR[23] register */
       pCTU_1->CLR[23].B.R      = CTU1_CLR23;
    #endif

    #ifdef CTU1_FDCR                       /* CR register */
       pCTU_1->FDCR.R           = CTU1_FDCR;
    #endif

    #ifdef CTU1_FCR                      /* FCR register */
       pCTU_1->FCR.R          = CTU1_FCR;
    #endif

    #ifdef CTU1_FTH                      /* TH1 register */
       pCTU_1->FTH.R          = CTU1_FTH;
    #endif

    #ifdef CTU1_IR                    /* CTUIR register */
       pCTU_1->IR.R				= CTU1_IR;
    #endif

    #ifdef CTU1_COTR                     /* COTR register */
       pCTU_1->COTR.R         = CTU1_COTR;
    #endif

    #ifdef CTU1_DFR                /* DFR register */
       pCTU_1->DFR.R    = CTU1_DFR;
    #endif

	#ifdef CTU1_EXPAR                /* EXPAR register */
	   pCTU_1->EXPAR.R    = CTU1_EXPAR;
	#endif

	#ifdef CTU1_EXPBR                /* EXPBR register */
	   pCTU_1->EXPBR.R    = CTU1_EXPBR;
	#endif

	#ifdef CTU1_CNTRNGR                /* CNTRNGR register */
		   pCTU_1->CNTRNGR.R	= CTU1_CNTRNGR;
	#endif

	#ifdef CTU1_LISTCSR                /* LISTCSR register */
		   pCTU_1->LISTCSR.R	= CTU1_LISTCSR;
	#endif

	// must be defined last in order to correctly write to double buffered
    // registers using GRE and TGSISR_RE
    #ifdef CTU1_CTU1CR                    /* CR register */
       pCTU_1->CR.R        = (CTU1_CTU1CR & (0xFFFB)); // mask out MRS_SG bit
    #endif

       pCTU_1->CR.B.GRE           = 1;    // CTU General Reload Enable

    #ifdef CTU1_CTU1CR                    /* CR register */
       pCTU_1->CR.R        = (CTU1_CTU1CR & (0x4)); // enable MRS_SG bit
    #endif

}

/******************************************************************************
* Inline functions
*******************************************************************************/
inline void ctu0_disable(void)
{
    pCTU_0->CR.B.CTU_ODIS       = 0x1;      // Disable CTU output
    pCTU_0->CR.B.CTU_ADC_R		= 0x1;      // Reset CTU/ADC state machine
}

inline void ctu_enable(void)
{
   pCTU_0->CR.B.CTU_ODIS   = 0x0;          // Enable CTU output
}


void CTU0_Init_v1(void)
{
  pCTU_0 = &CTU_0;
  pCTU_0->TGSISR.B.I12_RE   = 1;          // Trigger On PWM SUB 3 Rising Edge, see reference manual Page 242

// Configure Trigger Generator SubUnit - TGS
  pCTU_0->TGSCR.B.TGS_M     = 0;          // Triggered Mode
  pCTU_0->TGSCR.B.PRES      = 0;          // TGS And SU PreScaler Selection 0x00 = 1
  pCTU_0->TGSCR.B.ET_TM     = 1;          // Enable External Trigger
  pCTU_0->TGSCRR.R          = 0x0000;     // TGS Delay Counter Reload Register
  pCTU_0->TGSCCR.R          = 0x1000;     // TGS Delay Counter Count-to (Compare) Register

// Enable Trigger Compare Register 0  - Generates Trigger Event On TCR Match With TGS Counter
// Disable Other TCR's
  pCTU_0->TCR[0].R          = 0x0500;
  pCTU_0->TCR[1].R          = 0;
  pCTU_0->TCR[2].R          = 0;
  pCTU_0->TCR[3].R          = 0;
  pCTU_0->TCR[4].R          = 0;
  pCTU_0->TCR[5].R          = 0;
  pCTU_0->TCR[6].R          = 0;
  pCTU_0->TCR[7].R          = 0;

// Enable CTU Trigger 1 For Trigger Event 1
  pCTU_0->THCR1.B.T0_E      = 1;          // Enable Trigger
  pCTU_0->THCR1.B.T0_ADCE   = 1;          // Enable Trigger 1 For ADC
  pCTU_0->CLCR1.B.T0_INDEX   = 0;          // Pointer Index For ADC Command

// Enable External Trigger For CTU Trigger 1
  pCTU_0->THCR1.B.T0_ETE    = 1;          // External Trigger Enable

// ADC Command List Register Format
// Bit 0     = CIR  : Command Interrupt Request
// Bit 1     = LC   : Last Command
// Bit 2     = CMS  : Conversion Mode Select
// Bit 4:5   = FIFO : FIFO Select 0-3
// Bit 6     = ST   : Self-Test Bit (0: Normal Mode; 1: Self-Test Mode)
// Bit 10    = SU   : Selection Unit - ADC_0 Or ADC_1
// Bit 12:15 = CH   : ADC Channel
  pCTU_0->CLR[0].A.R          = 0x0025;     // Single Command On ADC_1 On Channel 5, FIFO 0
  pCTU_0->CLR[1].A.R          = 0x4025;     // Last Command On ADC_1 On Channel 5, FIFO 0

// Load Double Buffer Registers
  pCTU_0->CR.B.GRE       = 1;          // ReLoad Enable
  pCTU_0->CR.B.TGSISR_RE = 1;          // ReLoad Enable On PWM Event
}
