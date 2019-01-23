/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     eTimer.c
*
* @author   b15651
* 
* @version  1.0.1.0
* 
* @date     Aug-29-2013
* 
* @brief    eTimer - eTimer for MPC5744P
*
*******************************************************************************
*
* This file includes initial setting function of MPC5643L eTimer peripheral
* module.
*
******************************************************************************/
#include "eTimer.h"
#include "Defines.h"
#include "EXTGLOBALS.h"


volatile struct ETIMER_tag *pETIMER_0;
volatile struct ETIMER_tag *pETIMER_1;
volatile struct ETIMER_tag *pETIMER_2;


/******************************************************************************
* eTimer functions
*****************************************************************************/

/***************************************************************************//*!
@brief          eTimer0 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the eTimer0.

@note           

@warning        
******************************************************************************/
void etimer0_init(void)
{
    int i;

    // initialization of peripheral base address
    pETIMER_0 = &ETIMER_0;

    /*-------------------------------------------------------------------------
     * eTimer0 Reset
    --------------------------------------------------------------------------*/
    for (i=0;i<=5;i++)
    {
        pETIMER_0->CH[0].COMP1.R	= 0x0;
        pETIMER_0->CH[0].COMP2.R	= 0x0;
        pETIMER_0->CH[0].CAPT1.R	= 0x0;
        pETIMER_0->CH[0].CAPT2.R	= 0x0;
        pETIMER_0->CH[0].LOAD.R		= 0x0;
        pETIMER_0->CH[0].HOLD.R		= 0x0;
        pETIMER_0->CH[0].CNTR.R		= 0x0;
        pETIMER_0->CH[0].CTRL1.R    = 0x0;
        pETIMER_0->CH[0].CTRL2.R	= 0x0;
        pETIMER_0->CH[0].CTRL3.R	= 0x0F00U;
        pETIMER_0->CH[0].STS.R		= 0x0;
        pETIMER_0->CH[0].INTDMA.R	= 0x0;
        pETIMER_0->CH[0].CMPLD1.R	= 0x0;
        pETIMER_0->CH[0].CMPLD2.R	= 0x0;
        pETIMER_0->CH[0].CCCTRL.R	= 0x0;
        pETIMER_0->CH[0].FILT.R		= 0x0;
    }
    pETIMER_0->WDTOL.R				= 0x0;
    pETIMER_0->WDTOH.R				= 0x0;
    pETIMER_0->ENBL.R				= 0x003FU;  ///enable eTimer
    pETIMER_0->DREQ0.R				= 0x0;
    pETIMER_0->DREQ1.R				= 0x0;
    pETIMER_0->DREQ2.R				= 0x0;
    pETIMER_0->DREQ3.R				= 0x0;
    
    /*-------------------------------------------------------------------------
     * eTimer #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_WDTOL                    /* WDTOL register */
        pETIMER_0->WDTOL.R              = eTimer0_WDTOL;
    #endif
    
    #ifdef eTimer0_WDTOH                    /* WDTOH register */
        pETIMER_0->WDTOH.R              = eTimer0_WDTOH;
    #endif
    
    #ifdef eTimer0_ENBL                     /* ENBL register */
        pETIMER_0->ENBL.R               = eTimer0_ENBL;
    #endif
    
    #ifdef eTimer0_DREQ0                    /* DREQ0 register */
        pETIMER_0->DREQ0.R            = eTimer0_DREQ0;
    #endif
    
    #ifdef eTimer0_DREQ1                    /* DREQ1 register */
        pETIMER_0->DREQ1.R            = eTimer0_DREQ1;
    #endif

	#ifdef eTimer0_DREQ2                    /* DREQ2 register */
		pETIMER_0->DREQ2.R            = eTimer0_DREQ2;
	#endif

	#ifdef eTimer0_DREQ3                    /* DREQ3 register */
		pETIMER_0->DREQ3.R            = eTimer0_DREQ3;
	#endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CHANNEL #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH0                /* COMP1 register */
        pETIMER_0->CH[0].COMP1.R   = eTimer0_COMP1_CH0;
    #endif
    
    #ifdef eTimer0_COMP2_CH0                /* COMP2 register */
        pETIMER_0->CH[0].COMP2.R   = eTimer0_COMP2_CH0;
    #endif
    
    #ifdef eTimer0_LOAD_CH0                 /* LOAD register */
        pETIMER_0->CH[0].LOAD.R    = eTimer0_LOAD_CH0;
    #endif
    
    #ifdef eTimer0_CTRL_CH0                 /* CTRL register */
        pETIMER_0->CH[0].CTRL1.R    = eTimer0_CTRL_CH0;
    #endif
    
    #ifdef eTimer0_CTRL2_CH0                /* CTRL2 register */
        pETIMER_0->CH[0].CTRL2.R   = eTimer0_CTRL2_CH0;
    #endif
    
    #ifdef eTimer0_CTRL3_CH0                /* CTRL3 register */
        pETIMER_0->CH[0].CTRL3.R   = eTimer0_CTRL3_CH0;
    #endif
    
    #ifdef eTimer0_INTDMA_CH0               /* INTDMA register */
        pETIMER_0->CH[0].INTDMA.R  = eTimer0_INTDMA_CH0;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH0               /* CMPLD1 register */
        pETIMER_0->CH[0].CMPLD1.R  = eTimer0_CMPLD1_CH0;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH0               /* CMPLD2 register */
        pETIMER_0->CH[0].CMPLD2.R  = eTimer0_CMPLD2_CH0;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH0               /* CCCTRL register */
        pETIMER_0->CH[0].CCCTRL.R  = eTimer0_CCCTRL_CH0;
    #endif
    
    #ifdef eTimer0_FILT_CH0                 /* FILT register */
        pETIMER_0->CH[0].FILT.R    = eTimer0_FILT_CH0;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #1 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH1                /* COMP1 register */
        pETIMER_0->CH[1].COMP1.R   = eTimer0_COMP1_CH1;
    #endif
    
    #ifdef eTimer0_COMP2_CH1                /* COMP2 register */
        pETIMER_0->CH[1].COMP2.R   = eTimer0_COMP2_CH1;
    #endif
    
    #ifdef eTimer0_LOAD_CH1                 /* LOAD register */
        pETIMER_0->CH[1].LOAD.R    = eTimer0_LOAD_CH1;
    #endif
    
    #ifdef eTimer0_CTRL_CH1                 /* CTRL register */
        pETIMER_0->CH[1].CTRL1.R    = eTimer0_CTRL_CH1;
    #endif
    
    #ifdef eTimer0_CTRL2_CH1                /* CTRL2 register */
        pETIMER_0->CH[1].CTRL2.R   = eTimer0_CTRL2_CH1;
    #endif
    
    #ifdef eTimer0_CTRL3_CH1                /* CTRL3 register */
        pETIMER_0->CH[1].CTRL3.R   = eTimer0_CTRL3_CH1;
    #endif
    
    #ifdef eTimer0_INTDMA_CH1               /* INTDMA register */
        pETIMER_0->CH[1].INTDMA.R  = eTimer0_INTDMA_CH1;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH1               /* CMPLD1 register */
        pETIMER_0->CH[1].CMPLD1.R  = eTimer0_CMPLD1_CH1;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH1               /* CMPLD2 register */
        pETIMER_0->CH[1].CMPLD2.R  = eTimer0_CMPLD2_CH1;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH1               /* CCCTRL register */
        pETIMER_0->CH[1].CCCTRL.R  = eTimer0_CCCTRL_CH1;
    #endif
    
    #ifdef eTimer0_FILT_CH1                 /* FILT register */
        pETIMER_0->CH[1].FILT.R    = eTimer0_FILT_CH1;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #2 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH2                /* COMP1 register */
        pETIMER_0->CH[2].COMP1.R   = eTimer0_COMP1_CH2;
    #endif
    
    #ifdef eTimer0_COMP2_CH2                /* COMP2 register */
        pETIMER_0->CH[2].COMP2.R   = eTimer0_COMP2_CH2;
    #endif
    
    #ifdef eTimer0_LOAD_CH2                 /* LOAD register */
        pETIMER_0->CH[2].LOAD.R    = eTimer0_LOAD_CH2;
    #endif
    
    #ifdef eTimer0_CTRL_CH2                 /* CTRL register */
        pETIMER_0->CH[2].CTRL1.R    = eTimer0_CTRL_CH2;
    #endif
    
    #ifdef eTimer0_CTRL2_CH2                /* CTRL2 register */
        pETIMER_0->CH[2].CTRL2.R   = eTimer0_CTRL2_CH2;
    #endif
    
    #ifdef eTimer0_CTRL3_CH2                /* CTRL3 register */
        pETIMER_0->CH[2].CTRL3.R   = eTimer0_CTRL3_CH2;
    #endif
    
    #ifdef eTimer0_INTDMA_CH2               /* INTDMA register */
        pETIMER_0->CH[2].INTDMA.R  = eTimer0_INTDMA_CH2;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH2               /* CMPLD1 register */
        pETIMER_0->CH[2].CMPLD1.R  = eTimer0_CMPLD1_CH2;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH2               /* CMPLD2 register */
        pETIMER_0->CH[2].CMPLD2.R  = eTimer0_CMPLD2_CH2;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH2               /* CCCTRL register */
        pETIMER_0->CH[2].CCCTRL.R  = eTimer0_CCCTRL_CH2;
    #endif
    
    #ifdef eTimer0_FILT_CH2                 /* FILT register */
        pETIMER_0->CH[2].FILT.R    = eTimer0_FILT_CH2;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #3 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH3                /* COMP1 register */
        pETIMER_0->CH[3].COMP1.R   = eTimer0_COMP1_CH3;
    #endif
    
    #ifdef eTimer0_COMP2_CH3                /* COMP2 register */
        pETIMER_0->CH[3].COMP2.R   = eTimer0_COMP2_CH3;
    #endif
    
    #ifdef eTimer0_LOAD_CH3                 /* LOAD register */
        pETIMER_0->CH[3].LOAD.R    = eTimer0_LOAD_CH3;
    #endif
    
    #ifdef eTimer0_CTRL_CH3                 /* CTRL register */
        pETIMER_0->CH[3].CTRL1.R    = eTimer0_CTRL_CH3;
    #endif
    
    #ifdef eTimer0_CTRL2_CH3                /* CTRL2 register */
        pETIMER_0->CH[3].CTRL2.R   = eTimer0_CTRL2_CH3;
    #endif
    
    #ifdef eTimer0_CTRL3_CH3                /* CTRL3 register */
        pETIMER_0->CH[3].CTRL3.R   = eTimer0_CTRL3_CH3;
    #endif
    
    #ifdef eTimer0_INTDMA_CH3               /* INTDMA register */
        pETIMER_0->CH[3].INTDMA.R  = eTimer0_INTDMA_CH3;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH3               /* CMPLD1 register */
        pETIMER_0->CH[3].CMPLD1.R  = eTimer0_CMPLD1_CH3;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH3               /* CMPLD2 register */
        pETIMER_0->CH[3].CMPLD2.R  = eTimer0_CMPLD2_CH3;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH3               /* CCCTRL register */
        pETIMER_0->CH[3].CCCTRL.R  = eTimer0_CCCTRL_CH3;
    #endif
    
    #ifdef eTimer0_FILT_CH3                 /* FILT register */
        pETIMER_0->CH[3].FILT.R    = eTimer0_FILT_CH3;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #4 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH4                /* COMP1 register */
        pETIMER_0->CH[4].COMP1.R   = eTimer0_COMP1_CH4;
    #endif
    
    #ifdef eTimer0_COMP2_CH4                /* COMP2 register */
        pETIMER_0->CH[4].COMP2.R   = eTimer0_COMP2_CH4;
    #endif
    
    #ifdef eTimer0_LOAD_CH4                 /* LOAD register */
        pETIMER_0->CH[4].LOAD.R    = eTimer0_LOAD_CH4;
    #endif
    
    #ifdef eTimer0_CTRL_CH4                 /* CTRL register */
        pETIMER_0->CH[4].CTRL1.R    = eTimer0_CTRL_CH4;
    #endif
    
    #ifdef eTimer0_CTRL2_CH4                /* CTRL2 register */
        pETIMER_0->CH[4].CTRL2.R   = eTimer0_CTRL2_CH4;
    #endif
    
    #ifdef eTimer0_CTRL3_CH4                /* CTRL3 register */
        pETIMER_0->CH[4].CTRL3.R   = eTimer0_CTRL3_CH4;
    #endif
    
    #ifdef eTimer0_INTDMA_CH4               /* INTDMA register */
        pETIMER_0->CH[4].INTDMA.R  = eTimer0_INTDMA_CH4;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH4               /* CMPLD1 register */
        pETIMER_0->CH[4].CMPLD1.R  = eTimer0_CMPLD1_CH4;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH4               /* CMPLD2 register */
        pETIMER_0->CH[4].CMPLD2.R  = eTimer0_CMPLD2_CH4;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH4               /* CCCTRL register */
        pETIMER_0->CH[4].CCCTRL.R  = eTimer0_CCCTRL_CH4;
    #endif
    
    #ifdef eTimer0_FILT_CH4                 /* FILT register */
        pETIMER_0->CH[4].FILT.R    = eTimer0_FILT_CH4;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #5 Control registers
    --------------------------------------------------------------------------*/
    #ifdef eTimer0_COMP1_CH5                /* COMP1 register */
        pETIMER_0->CH[5].COMP1.R   = eTimer0_COMP1_CH5;
    #endif
    
    #ifdef eTimer0_COMP2_CH5                /* COMP2 register */
        pETIMER_0->CH[5].COMP2.R   = eTimer0_COMP2_CH5;
    #endif
    
    #ifdef eTimer0_LOAD_CH5                 /* LOAD register */
        pETIMER_0->CH[5].LOAD.R    = eTimer0_LOAD_CH5;
    #endif
    
    #ifdef eTimer0_CTRL_CH5                 /* CTRL register */
        pETIMER_0->CH[5].CTRL1.R    = eTimer0_CTRL_CH5;
    #endif
    
    #ifdef eTimer0_CTRL2_CH5                /* CTRL2 register */
        pETIMER_0->CH[5].CTRL2.R   = eTimer0_CTRL2_CH5;
    #endif
    
    #ifdef eTimer0_CTRL3_CH5                /* CTRL3 register */
        pETIMER_0->CH[5].CTRL3.R   = eTimer0_CTRL3_CH5;
    #endif
    
    #ifdef eTimer0_INTDMA_CH5               /* INTDMA register */
        pETIMER_0->CH[5].INTDMA.R  = eTimer0_INTDMA_CH5;
    #endif
    
    #ifdef eTimer0_CMPLD1_CH5               /* CMPLD1 register */
        pETIMER_0->CH[5].CMPLD1.R  = eTimer0_CMPLD1_CH5;
    #endif
    
    #ifdef eTimer0_CMPLD2_CH5               /* CMPLD2 register */
        pETIMER_0->CH[5].CMPLD2.R  = eTimer0_CMPLD2_CH5;
    #endif
    
    #ifdef eTimer0_CCCTRL_CH5               /* CCCTRL register */
        pETIMER_0->CH[5].CCCTRL.R  = eTimer0_CCCTRL_CH5;
    #endif
    
    #ifdef eTimer0_FILT_CH5                 /* FILT register */
        pETIMER_0->CH[5].FILT.R    = eTimer0_FILT_CH5;
    #endif
}

/***************************************************************************//*!
@brief          etimer1 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the etimer1.

@note

@warning
******************************************************************************/
void etimer1_init(void)
{
    int i;

    // initialization of peripheral base address
    pETIMER_1 = &ETIMER_1;

    /*-------------------------------------------------------------------------
     * etimer1 Reset
    --------------------------------------------------------------------------*/
    for (i=0;i<=5;i++)
    {
        pETIMER_1->CH[0].COMP1.R	= 0x0;
        pETIMER_1->CH[0].COMP2.R	= 0x0;
        pETIMER_1->CH[0].CAPT1.R	= 0x0;
        pETIMER_1->CH[0].CAPT2.R	= 0x0;
        pETIMER_1->CH[0].LOAD.R		= 0x0;
        pETIMER_1->CH[0].HOLD.R		= 0x0;
        pETIMER_1->CH[0].CNTR.R		= 0x0;
        pETIMER_1->CH[0].CTRL1.R    = 0x0;
        pETIMER_1->CH[0].CTRL2.R	= 0x0;
        pETIMER_1->CH[0].CTRL3.R	= 0x0F00U;
        pETIMER_1->CH[0].STS.R		= 0x0;
        pETIMER_1->CH[0].INTDMA.R	= 0x0;
        pETIMER_1->CH[0].CMPLD1.R	= 0x0;
        pETIMER_1->CH[0].CMPLD2.R	= 0x0;
        pETIMER_1->CH[0].CCCTRL.R	= 0x0;
        pETIMER_1->CH[0].FILT.R		= 0x0;
    }
    pETIMER_1->WDTOL.R				= 0x0;
    pETIMER_1->WDTOH.R				= 0x0;
    pETIMER_1->ENBL.R				= 0x003FU;
    pETIMER_1->DREQ0.R				= 0x0;
    pETIMER_1->DREQ1.R				= 0x0;
    pETIMER_1->DREQ2.R				= 0x0;
    pETIMER_1->DREQ3.R				= 0x0;

    /*-------------------------------------------------------------------------
     * eTimer #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_WDTOL                    /* WDTOL register */
        pETIMER_1->WDTOL.R              = etimer1_WDTOL;
    #endif

    #ifdef etimer1_WDTOH                    /* WDTOH register */
        pETIMER_1->WDTOH.R              = etimer1_WDTOH;
    #endif

    #ifdef etimer1_ENBL                     /* ENBL register */
        pETIMER_1->ENBL.R               = etimer1_ENBL;
    #endif

    #ifdef etimer1_DREQ0                    /* DREQ0 register */
        pETIMER_1->DREQ0.R            = etimer1_DREQ0;
    #endif

    #ifdef etimer1_DREQ1                    /* DREQ1 register */
        pETIMER_1->DREQ1.R            = etimer1_DREQ1;
    #endif

	#ifdef etimer1_DREQ2                    /* DREQ2 register */
		pETIMER_1->DREQ2.R            = etimer1_DREQ2;
	#endif

	#ifdef etimer1_DREQ3                    /* DREQ3 register */
		pETIMER_1->DREQ3.R            = etimer1_DREQ3;
	#endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CHANNEL #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH0                /* COMP1 register */
        pETIMER_1->CH[0].COMP1.R   = etimer1_COMP1_CH0;
    #endif

    #ifdef etimer1_COMP2_CH0                /* COMP2 register */
        pETIMER_1->CH[0].COMP2.R   = etimer1_COMP2_CH0;
    #endif

    #ifdef etimer1_LOAD_CH0                 /* LOAD register */
        pETIMER_1->CH[0].LOAD.R    = etimer1_LOAD_CH0;
    #endif

    #ifdef etimer1_CTRL_CH0                 /* CTRL register */
        pETIMER_1->CH[0].CTRL1.R    = etimer1_CTRL_CH0;
    #endif

    #ifdef etimer1_CTRL2_CH0                /* CTRL2 register */
        pETIMER_1->CH[0].CTRL2.R   = etimer1_CTRL2_CH0;
    #endif

    #ifdef etimer1_CTRL3_CH0                /* CTRL3 register */
        pETIMER_1->CH[0].CTRL3.R   = etimer1_CTRL3_CH0;
    #endif

    #ifdef etimer1_INTDMA_CH0               /* INTDMA register */
        pETIMER_1->CH[0].INTDMA.R  = etimer1_INTDMA_CH0;
    #endif

    #ifdef etimer1_CMPLD1_CH0               /* CMPLD1 register */
        pETIMER_1->CH[0].CMPLD1.R  = etimer1_CMPLD1_CH0;
    #endif

    #ifdef etimer1_CMPLD2_CH0               /* CMPLD2 register */
        pETIMER_1->CH[0].CMPLD2.R  = etimer1_CMPLD2_CH0;
    #endif

    #ifdef etimer1_CCCTRL_CH0               /* CCCTRL register */
        pETIMER_1->CH[0].CCCTRL.R  = etimer1_CCCTRL_CH0;
    #endif

    #ifdef etimer1_FILT_CH0                 /* FILT register */
        pETIMER_1->CH[0].FILT.R    = etimer1_FILT_CH0;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #1 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH1                /* COMP1 register */
        pETIMER_1->CH[1].COMP1.R   = etimer1_COMP1_CH1;
    #endif

    #ifdef etimer1_COMP2_CH1                /* COMP2 register */
        pETIMER_1->CH[1].COMP2.R   = etimer1_COMP2_CH1;
    #endif

    #ifdef etimer1_LOAD_CH1                 /* LOAD register */
        pETIMER_1->CH[1].LOAD.R    = etimer1_LOAD_CH1;
    #endif

    #ifdef etimer1_CTRL_CH1                 /* CTRL register */
        pETIMER_1->CH[1].CTRL1.R    = etimer1_CTRL_CH1;
    #endif

    #ifdef etimer1_CTRL2_CH1                /* CTRL2 register */
        pETIMER_1->CH[1].CTRL2.R   = etimer1_CTRL2_CH1;
    #endif

    #ifdef etimer1_CTRL3_CH1                /* CTRL3 register */
        pETIMER_1->CH[1].CTRL3.R   = etimer1_CTRL3_CH1;
    #endif

    #ifdef etimer1_INTDMA_CH1               /* INTDMA register */
        pETIMER_1->CH[1].INTDMA.R  = etimer1_INTDMA_CH1;
    #endif

    #ifdef etimer1_CMPLD1_CH1               /* CMPLD1 register */
        pETIMER_1->CH[1].CMPLD1.R  = etimer1_CMPLD1_CH1;
    #endif

    #ifdef etimer1_CMPLD2_CH1               /* CMPLD2 register */
        pETIMER_1->CH[1].CMPLD2.R  = etimer1_CMPLD2_CH1;
    #endif

    #ifdef etimer1_CCCTRL_CH1               /* CCCTRL register */
        pETIMER_1->CH[1].CCCTRL.R  = etimer1_CCCTRL_CH1;
    #endif

    #ifdef etimer1_FILT_CH1                 /* FILT register */
        pETIMER_1->CH[1].FILT.R    = etimer1_FILT_CH1;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #2 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH2                /* COMP1 register */
        pETIMER_1->CH[2].COMP1.R   = etimer1_COMP1_CH2;
    #endif

    #ifdef etimer1_COMP2_CH2                /* COMP2 register */
        pETIMER_1->CH[2].COMP2.R   = etimer1_COMP2_CH2;
    #endif

    #ifdef etimer1_LOAD_CH2                 /* LOAD register */
        pETIMER_1->CH[2].LOAD.R    = etimer1_LOAD_CH2;
    #endif

    #ifdef etimer1_CTRL_CH2                 /* CTRL register */
        pETIMER_1->CH[2].CTRL1.R    = etimer1_CTRL_CH2;
    #endif

    #ifdef etimer1_CTRL2_CH2                /* CTRL2 register */
        pETIMER_1->CH[2].CTRL2.R   = etimer1_CTRL2_CH2;
    #endif

    #ifdef etimer1_CTRL3_CH2                /* CTRL3 register */
        pETIMER_1->CH[2].CTRL3.R   = etimer1_CTRL3_CH2;
    #endif

    #ifdef etimer1_INTDMA_CH2               /* INTDMA register */
        pETIMER_1->CH[2].INTDMA.R  = etimer1_INTDMA_CH2;
    #endif

    #ifdef etimer1_CMPLD1_CH2               /* CMPLD1 register */
        pETIMER_1->CH[2].CMPLD1.R  = etimer1_CMPLD1_CH2;
    #endif

    #ifdef etimer1_CMPLD2_CH2               /* CMPLD2 register */
        pETIMER_1->CH[2].CMPLD2.R  = etimer1_CMPLD2_CH2;
    #endif

    #ifdef etimer1_CCCTRL_CH2               /* CCCTRL register */
        pETIMER_1->CH[2].CCCTRL.R  = etimer1_CCCTRL_CH2;
    #endif

    #ifdef etimer1_FILT_CH2                 /* FILT register */
        pETIMER_1->CH[2].FILT.R    = etimer1_FILT_CH2;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #3 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH3                /* COMP1 register */
        pETIMER_1->CH[3].COMP1.R   = etimer1_COMP1_CH3;
    #endif

    #ifdef etimer1_COMP2_CH3                /* COMP2 register */
        pETIMER_1->CH[3].COMP2.R   = etimer1_COMP2_CH3;
    #endif

    #ifdef etimer1_LOAD_CH3                 /* LOAD register */
        pETIMER_1->CH[3].LOAD.R    = etimer1_LOAD_CH3;
    #endif

    #ifdef etimer1_CTRL_CH3                 /* CTRL register */
        pETIMER_1->CH[3].CTRL1.R    = etimer1_CTRL_CH3;
    #endif

    #ifdef etimer1_CTRL2_CH3                /* CTRL2 register */
        pETIMER_1->CH[3].CTRL2.R   = etimer1_CTRL2_CH3;
    #endif

    #ifdef etimer1_CTRL3_CH3                /* CTRL3 register */
        pETIMER_1->CH[3].CTRL3.R   = etimer1_CTRL3_CH3;
    #endif

    #ifdef etimer1_INTDMA_CH3               /* INTDMA register */
        pETIMER_1->CH[3].INTDMA.R  = etimer1_INTDMA_CH3;
    #endif

    #ifdef etimer1_CMPLD1_CH3               /* CMPLD1 register */
        pETIMER_1->CH[3].CMPLD1.R  = etimer1_CMPLD1_CH3;
    #endif

    #ifdef etimer1_CMPLD2_CH3               /* CMPLD2 register */
        pETIMER_1->CH[3].CMPLD2.R  = etimer1_CMPLD2_CH3;
    #endif

    #ifdef etimer1_CCCTRL_CH3               /* CCCTRL register */
        pETIMER_1->CH[3].CCCTRL.R  = etimer1_CCCTRL_CH3;
    #endif

    #ifdef etimer1_FILT_CH3                 /* FILT register */
        pETIMER_1->CH[3].FILT.R    = etimer1_FILT_CH3;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #4 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH4                /* COMP1 register */
        pETIMER_1->CH[4].COMP1.R   = etimer1_COMP1_CH4;
    #endif

    #ifdef etimer1_COMP2_CH4                /* COMP2 register */
        pETIMER_1->CH[4].COMP2.R   = etimer1_COMP2_CH4;
    #endif

    #ifdef etimer1_LOAD_CH4                 /* LOAD register */
        pETIMER_1->CH[4].LOAD.R    = etimer1_LOAD_CH4;
    #endif

    #ifdef etimer1_CTRL_CH4                 /* CTRL register */
        pETIMER_1->CH[4].CTRL1.R    = etimer1_CTRL_CH4;
    #endif

    #ifdef etimer1_CTRL2_CH4                /* CTRL2 register */
        pETIMER_1->CH[4].CTRL2.R   = etimer1_CTRL2_CH4;
    #endif

    #ifdef etimer1_CTRL3_CH4                /* CTRL3 register */
        pETIMER_1->CH[4].CTRL3.R   = etimer1_CTRL3_CH4;
    #endif

    #ifdef etimer1_INTDMA_CH4               /* INTDMA register */
        pETIMER_1->CH[4].INTDMA.R  = etimer1_INTDMA_CH4;
    #endif

    #ifdef etimer1_CMPLD1_CH4               /* CMPLD1 register */
        pETIMER_1->CH[4].CMPLD1.R  = etimer1_CMPLD1_CH4;
    #endif

    #ifdef etimer1_CMPLD2_CH4               /* CMPLD2 register */
        pETIMER_1->CH[4].CMPLD2.R  = etimer1_CMPLD2_CH4;
    #endif

    #ifdef etimer1_CCCTRL_CH4               /* CCCTRL register */
        pETIMER_1->CH[4].CCCTRL.R  = etimer1_CCCTRL_CH4;
    #endif

    #ifdef etimer1_FILT_CH4                 /* FILT register */
        pETIMER_1->CH[4].FILT.R    = etimer1_FILT_CH4;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #5 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer1_COMP1_CH5                /* COMP1 register */
        pETIMER_1->CH[5].COMP1.R   = etimer1_COMP1_CH5;
    #endif

    #ifdef etimer1_COMP2_CH5                /* COMP2 register */
        pETIMER_1->CH[5].COMP2.R   = etimer1_COMP2_CH5;
    #endif

    #ifdef etimer1_LOAD_CH5                 /* LOAD register */
        pETIMER_1->CH[5].LOAD.R    = etimer1_LOAD_CH5;
    #endif

    #ifdef etimer1_CTRL_CH5                 /* CTRL register */
        pETIMER_1->CH[5].CTRL1.R    = etimer1_CTRL_CH5;
    #endif

    #ifdef etimer1_CTRL2_CH5                /* CTRL2 register */
        pETIMER_1->CH[5].CTRL2.R   = etimer1_CTRL2_CH5;
    #endif

    #ifdef etimer1_CTRL3_CH5                /* CTRL3 register */
        pETIMER_1->CH[5].CTRL3.R   = etimer1_CTRL3_CH5;
    #endif

    #ifdef etimer1_INTDMA_CH5               /* INTDMA register */
        pETIMER_1->CH[5].INTDMA.R  = etimer1_INTDMA_CH5;
    #endif

    #ifdef etimer1_CMPLD1_CH5               /* CMPLD1 register */
        pETIMER_1->CH[5].CMPLD1.R  = etimer1_CMPLD1_CH5;
    #endif

    #ifdef etimer1_CMPLD2_CH5               /* CMPLD2 register */
        pETIMER_1->CH[5].CMPLD2.R  = etimer1_CMPLD2_CH5;
    #endif

    #ifdef etimer1_CCCTRL_CH5               /* CCCTRL register */
        pETIMER_1->CH[5].CCCTRL.R  = etimer1_CCCTRL_CH5;
    #endif

    #ifdef etimer1_FILT_CH5                 /* FILT register */
        pETIMER_1->CH[5].FILT.R    = etimer1_FILT_CH5;
    #endif
}

/***************************************************************************//*!
@brief          etimer2 init function

@param[in,out]  void
@param[in]      void

@return         void

@details        This function initializes basic start-up setting of the etimer2.

@note

@warning
******************************************************************************/
void etimer2_init(void)
{
    int i;

    // initialization of peripheral base address
    pETIMER_2 = &ETIMER_2;

    /*-------------------------------------------------------------------------
     * etimer2 Reset
    --------------------------------------------------------------------------*/
    for (i=0;i<=5;i++)
    {
        pETIMER_2->CH[0].COMP1.R	= 0x0;
        pETIMER_2->CH[0].COMP2.R	= 0x0;
        pETIMER_2->CH[0].CAPT1.R	= 0x0;
        pETIMER_2->CH[0].CAPT2.R	= 0x0;
        pETIMER_2->CH[0].LOAD.R		= 0x0;
        pETIMER_2->CH[0].HOLD.R		= 0x0;
        pETIMER_2->CH[0].CNTR.R		= 0x0;
        pETIMER_2->CH[0].CTRL1.R    = 0x0;
        pETIMER_2->CH[0].CTRL2.R	= 0x0;
        pETIMER_2->CH[0].CTRL3.R	= 0x0F00U;
        pETIMER_2->CH[0].STS.R		= 0x0;
        pETIMER_2->CH[0].INTDMA.R	= 0x0;
        pETIMER_2->CH[0].CMPLD1.R	= 0x0;
        pETIMER_2->CH[0].CMPLD2.R	= 0x0;
        pETIMER_2->CH[0].CCCTRL.R	= 0x0;
        pETIMER_2->CH[0].FILT.R		= 0x0;
    }
    pETIMER_2->WDTOL.R				= 0x0;
    pETIMER_2->WDTOH.R				= 0x0;
    pETIMER_2->ENBL.R				= 0x003FU;
    pETIMER_2->DREQ0.R				= 0x0;
    pETIMER_2->DREQ1.R				= 0x0;
    pETIMER_2->DREQ2.R				= 0x0;
    pETIMER_2->DREQ3.R				= 0x0;

    /*-------------------------------------------------------------------------
     * eTimer #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_WDTOL                    /* WDTOL register */
        pETIMER_2->WDTOL.R              = etimer2_WDTOL;
    #endif

    #ifdef etimer2_WDTOH                    /* WDTOH register */
        pETIMER_2->WDTOH.R              = etimer2_WDTOH;
    #endif

    #ifdef etimer2_ENBL                     /* ENBL register */
        pETIMER_2->ENBL.R               = etimer2_ENBL;
    #endif

    #ifdef etimer2_DREQ0                    /* DREQ0 register */
        pETIMER_2->DREQ0.R            = etimer2_DREQ0;
    #endif

    #ifdef etimer2_DREQ1                    /* DREQ1 register */
        pETIMER_2->DREQ1.R            = etimer2_DREQ1;
    #endif

	#ifdef etimer2_DREQ2                    /* DREQ2 register */
		pETIMER_2->DREQ2.R            = etimer2_DREQ2;
	#endif

	#ifdef etimer2_DREQ3                    /* DREQ3 register */
		pETIMER_2->DREQ3.R            = etimer2_DREQ3;
	#endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CHANNEL #0 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH0                /* COMP1 register */
        pETIMER_2->CH[0].COMP1.R   = etimer2_COMP1_CH0;
    #endif

    #ifdef etimer2_COMP2_CH0                /* COMP2 register */
        pETIMER_2->CH[0].COMP2.R   = etimer2_COMP2_CH0;
    #endif

    #ifdef etimer2_LOAD_CH0                 /* LOAD register */
        pETIMER_2->CH[0].LOAD.R    = etimer2_LOAD_CH0;
    #endif

    #ifdef etimer2_CTRL_CH0                 /* CTRL register */
        pETIMER_2->CH[0].CTRL1.R    = etimer2_CTRL_CH0;
    #endif

    #ifdef etimer2_CTRL2_CH0                /* CTRL2 register */
        pETIMER_2->CH[0].CTRL2.R   = etimer2_CTRL2_CH0;
    #endif

    #ifdef etimer2_CTRL3_CH0                /* CTRL3 register */
        pETIMER_2->CH[0].CTRL3.R   = etimer2_CTRL3_CH0;
    #endif

    #ifdef etimer2_INTDMA_CH0               /* INTDMA register */
        pETIMER_2->CH[0].INTDMA.R  = etimer2_INTDMA_CH0;
    #endif

    #ifdef etimer2_CMPLD1_CH0               /* CMPLD1 register */
        pETIMER_2->CH[0].CMPLD1.R  = etimer2_CMPLD1_CH0;
    #endif

    #ifdef etimer2_CMPLD2_CH0               /* CMPLD2 register */
        pETIMER_2->CH[0].CMPLD2.R  = etimer2_CMPLD2_CH0;
    #endif

    #ifdef etimer2_CCCTRL_CH0               /* CCCTRL register */
        pETIMER_2->CH[0].CCCTRL.R  = etimer2_CCCTRL_CH0;
    #endif

    #ifdef etimer2_FILT_CH0                 /* FILT register */
        pETIMER_2->CH[0].FILT.R    = etimer2_FILT_CH0;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #1 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH1                /* COMP1 register */
        pETIMER_2->CH[1].COMP1.R   = etimer2_COMP1_CH1;
    #endif

    #ifdef etimer2_COMP2_CH1                /* COMP2 register */
        pETIMER_2->CH[1].COMP2.R   = etimer2_COMP2_CH1;
    #endif

    #ifdef etimer2_LOAD_CH1                 /* LOAD register */
        pETIMER_2->CH[1].LOAD.R    = etimer2_LOAD_CH1;
    #endif

    #ifdef etimer2_CTRL_CH1                 /* CTRL register */
        pETIMER_2->CH[1].CTRL1.R    = etimer2_CTRL_CH1;
    #endif

    #ifdef etimer2_CTRL2_CH1                /* CTRL2 register */
        pETIMER_2->CH[1].CTRL2.R   = etimer2_CTRL2_CH1;
    #endif

    #ifdef etimer2_CTRL3_CH1                /* CTRL3 register */
        pETIMER_2->CH[1].CTRL3.R   = etimer2_CTRL3_CH1;
    #endif

    #ifdef etimer2_INTDMA_CH1               /* INTDMA register */
        pETIMER_2->CH[1].INTDMA.R  = etimer2_INTDMA_CH1;
    #endif

    #ifdef etimer2_CMPLD1_CH1               /* CMPLD1 register */
        pETIMER_2->CH[1].CMPLD1.R  = etimer2_CMPLD1_CH1;
    #endif

    #ifdef etimer2_CMPLD2_CH1               /* CMPLD2 register */
        pETIMER_2->CH[1].CMPLD2.R  = etimer2_CMPLD2_CH1;
    #endif

    #ifdef etimer2_CCCTRL_CH1               /* CCCTRL register */
        pETIMER_2->CH[1].CCCTRL.R  = etimer2_CCCTRL_CH1;
    #endif

    #ifdef etimer2_FILT_CH1                 /* FILT register */
        pETIMER_2->CH[1].FILT.R    = etimer2_FILT_CH1;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #2 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH2                /* COMP1 register */
        pETIMER_2->CH[2].COMP1.R   = etimer2_COMP1_CH2;
    #endif

    #ifdef etimer2_COMP2_CH2                /* COMP2 register */
        pETIMER_2->CH[2].COMP2.R   = etimer2_COMP2_CH2;
    #endif

    #ifdef etimer2_LOAD_CH2                 /* LOAD register */
        pETIMER_2->CH[2].LOAD.R    = etimer2_LOAD_CH2;
    #endif

    #ifdef etimer2_CTRL_CH2                 /* CTRL register */
        pETIMER_2->CH[2].CTRL1.R    = etimer2_CTRL_CH2;
    #endif

    #ifdef etimer2_CTRL2_CH2                /* CTRL2 register */
        pETIMER_2->CH[2].CTRL2.R   = etimer2_CTRL2_CH2;
    #endif

    #ifdef etimer2_CTRL3_CH2                /* CTRL3 register */
        pETIMER_2->CH[2].CTRL3.R   = etimer2_CTRL3_CH2;
    #endif

    #ifdef etimer2_INTDMA_CH2               /* INTDMA register */
        pETIMER_2->CH[2].INTDMA.R  = etimer2_INTDMA_CH2;
    #endif

    #ifdef etimer2_CMPLD1_CH2               /* CMPLD1 register */
        pETIMER_2->CH[2].CMPLD1.R  = etimer2_CMPLD1_CH2;
    #endif

    #ifdef etimer2_CMPLD2_CH2               /* CMPLD2 register */
        pETIMER_2->CH[2].CMPLD2.R  = etimer2_CMPLD2_CH2;
    #endif

    #ifdef etimer2_CCCTRL_CH2               /* CCCTRL register */
        pETIMER_2->CH[2].CCCTRL.R  = etimer2_CCCTRL_CH2;
    #endif

    #ifdef etimer2_FILT_CH2                 /* FILT register */
        pETIMER_2->CH[2].FILT.R    = etimer2_FILT_CH2;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #3 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH3                /* COMP1 register */
        pETIMER_2->CH[3].COMP1.R   = etimer2_COMP1_CH3;
    #endif

    #ifdef etimer2_COMP2_CH3                /* COMP2 register */
        pETIMER_2->CH[3].COMP2.R   = etimer2_COMP2_CH3;
    #endif

    #ifdef etimer2_LOAD_CH3                 /* LOAD register */
        pETIMER_2->CH[3].LOAD.R    = etimer2_LOAD_CH3;
    #endif

    #ifdef etimer2_CTRL_CH3                 /* CTRL register */
        pETIMER_2->CH[3].CTRL1.R    = etimer2_CTRL_CH3;
    #endif

    #ifdef etimer2_CTRL2_CH3                /* CTRL2 register */
        pETIMER_2->CH[3].CTRL2.R   = etimer2_CTRL2_CH3;
    #endif

    #ifdef etimer2_CTRL3_CH3                /* CTRL3 register */
        pETIMER_2->CH[3].CTRL3.R   = etimer2_CTRL3_CH3;
    #endif

    #ifdef etimer2_INTDMA_CH3               /* INTDMA register */
        pETIMER_2->CH[3].INTDMA.R  = etimer2_INTDMA_CH3;
    #endif

    #ifdef etimer2_CMPLD1_CH3               /* CMPLD1 register */
        pETIMER_2->CH[3].CMPLD1.R  = etimer2_CMPLD1_CH3;
    #endif

    #ifdef etimer2_CMPLD2_CH3               /* CMPLD2 register */
        pETIMER_2->CH[3].CMPLD2.R  = etimer2_CMPLD2_CH3;
    #endif

    #ifdef etimer2_CCCTRL_CH3               /* CCCTRL register */
        pETIMER_2->CH[3].CCCTRL.R  = etimer2_CCCTRL_CH3;
    #endif

    #ifdef etimer2_FILT_CH3                 /* FILT register */
        pETIMER_2->CH[3].FILT.R    = etimer2_FILT_CH3;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #4 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH4                /* COMP1 register */
        pETIMER_2->CH[4].COMP1.R   = etimer2_COMP1_CH4;
    #endif

    #ifdef etimer2_COMP2_CH4                /* COMP2 register */
        pETIMER_2->CH[4].COMP2.R   = etimer2_COMP2_CH4;
    #endif

    #ifdef etimer2_LOAD_CH4                 /* LOAD register */
        pETIMER_2->CH[4].LOAD.R    = etimer2_LOAD_CH4;
    #endif

    #ifdef etimer2_CTRL_CH4                 /* CTRL register */
        pETIMER_2->CH[4].CTRL1.R    = etimer2_CTRL_CH4;
    #endif

    #ifdef etimer2_CTRL2_CH4                /* CTRL2 register */
        pETIMER_2->CH[4].CTRL2.R   = etimer2_CTRL2_CH4;
    #endif

    #ifdef etimer2_CTRL3_CH4                /* CTRL3 register */
        pETIMER_2->CH[4].CTRL3.R   = etimer2_CTRL3_CH4;
    #endif

    #ifdef etimer2_INTDMA_CH4               /* INTDMA register */
        pETIMER_2->CH[4].INTDMA.R  = etimer2_INTDMA_CH4;
    #endif

    #ifdef etimer2_CMPLD1_CH4               /* CMPLD1 register */
        pETIMER_2->CH[4].CMPLD1.R  = etimer2_CMPLD1_CH4;
    #endif

    #ifdef etimer2_CMPLD2_CH4               /* CMPLD2 register */
        pETIMER_2->CH[4].CMPLD2.R  = etimer2_CMPLD2_CH4;
    #endif

    #ifdef etimer2_CCCTRL_CH4               /* CCCTRL register */
        pETIMER_2->CH[4].CCCTRL.R  = etimer2_CCCTRL_CH4;
    #endif

    #ifdef etimer2_FILT_CH4                 /* FILT register */
        pETIMER_2->CH[4].FILT.R    = etimer2_FILT_CH4;
    #endif

    /*-------------------------------------------------------------------------
     * eTimer #0 CH #5 Control registers
    --------------------------------------------------------------------------*/
    #ifdef etimer2_COMP1_CH5                /* COMP1 register */
        pETIMER_2->CH[5].COMP1.R   = etimer2_COMP1_CH5;
    #endif

    #ifdef etimer2_COMP2_CH5                /* COMP2 register */
        pETIMER_2->CH[5].COMP2.R   = etimer2_COMP2_CH5;
    #endif

    #ifdef etimer2_LOAD_CH5                 /* LOAD register */
        pETIMER_2->CH[5].LOAD.R    = etimer2_LOAD_CH5;
    #endif

    #ifdef etimer2_CTRL_CH5                 /* CTRL register */
        pETIMER_2->CH[5].CTRL1.R    = etimer2_CTRL_CH5;
    #endif

    #ifdef etimer2_CTRL2_CH5                /* CTRL2 register */
        pETIMER_2->CH[5].CTRL2.R   = etimer2_CTRL2_CH5;
    #endif

    #ifdef etimer2_CTRL3_CH5                /* CTRL3 register */
        pETIMER_2->CH[5].CTRL3.R   = etimer2_CTRL3_CH5;
    #endif

    #ifdef etimer2_INTDMA_CH5               /* INTDMA register */
        pETIMER_2->CH[5].INTDMA.R  = etimer2_INTDMA_CH5;
    #endif

    #ifdef etimer2_CMPLD1_CH5               /* CMPLD1 register */
        pETIMER_2->CH[5].CMPLD1.R  = etimer2_CMPLD1_CH5;
    #endif

    #ifdef etimer2_CMPLD2_CH5               /* CMPLD2 register */
        pETIMER_2->CH[5].CMPLD2.R  = etimer2_CMPLD2_CH5;
    #endif

    #ifdef etimer2_CCCTRL_CH5               /* CCCTRL register */
        pETIMER_2->CH[5].CCCTRL.R  = etimer2_CCCTRL_CH5;
    #endif

    #ifdef etimer2_FILT_CH5                 /* FILT register */
        pETIMER_2->CH[5].FILT.R    = etimer2_FILT_CH5;
    #endif
}


/* *******************another kind of eTimer initial********************/
/* *****************************************************************************
   Function:        void eTimer1_vInit(void)
   Description:     eTimer Module 1 Initialization
                    PWM Frequency: 1KHz Fixed; Duty Cycle: 50% Fixed
   Parameters:      Input:    void
                    Output:   void
   Notes:
   ***************************************************************************** */
void eTimer1_vInit(void)
{
	pETIMER_1 = &ETIMER_1;
// 0xEA60 (60000) Is For 1 ms Period When Running On 120 MHz PLL
	pETIMER_1->CH[5].COMP1.R   = 0xEA60;          // Count Untill This Value, Then ReInitialize To 0x0000 (0x0190 = 400 --> 16MHz / 400 = 40KHz --> Toggle Every 25us)(0x3E80 = 16000 --> 16MHz / 16000 = 1kHz --> Toggle Every ms)
	pETIMER_1->CH[5].CMPLD1.R  = 0xEA60;
	pETIMER_1->CH[5].CTRL1.R   = 0x3840;          // Counts Only Rising Edge Of The fSys (120MHz In RUN[0]), Divide By PreScaler, Count Up Untill Comp Then ReInit, Count Up, Count Repeatedly
    pETIMER_1->CH[5].CTRL2.R   = 0x8003;          // OFLAG Is Driven To External Pin, Toggle OFLAG On Successful Compare To Comp1 & 2
    pETIMER_1->CH[5].CCCTRL.R  = 0x0A00;          // Load COMP1 With CMPLD1 On Compare, Compare With COMP1 / COMP2 If Counting Up/Down

    pETIMER_1->ENBL.R          = 0x0020;          // Enable eTimer[1].[5]

}


/* End of FILE */
