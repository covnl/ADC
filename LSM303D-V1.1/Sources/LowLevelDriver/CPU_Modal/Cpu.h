/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       CPU.h
\brief      CPU initialization prototypes and definitions
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.4
\date       11/Feb/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#ifndef _CPU_H
#define _CPU_H

/*-- Defines -----------------------------------------------------------------*/
/**** 选用内部时钟 ***/ 
#define  BUS_FREQ        32000000       
#define  XTAL_FREQ        8000000
#define  INTERNAL_CLOCK
//#define  EXTERNAL_CLOCK

#ifdef  INTERNAL_CLOCK

// BUS_FREQ = XTAL_FREQ * (SYNR+1) / ((REFDV+1)(2*POSTDIV))  
#define POSTDIV_VALUE   0
#define SYNR_VALUE      0x1F
#define REFDV_VALUE     0
#define VCOFRQ_VALUE    1
#define REFFRQ_VALUE    0

#endif


#ifdef EXTERNAL_CLOCK

/**** 选用外部时钟 ***/ 
/** System configuration definitions */
// BUS_FREQ = XTAL_FREQ * (SYNR+1) / ((REFDV+1)(POSTDIV+1))  

#define POSTDIV_VALUE   0
#define SYNR_VALUE      3
#define REFDV_VALUE     ((XTAL_FREQ*(SYNR_VALUE+1)/BUS_FREQ)-1) 
#define VCOFRQ_VALUE    1  /* 1: 48M<fVCO<64M */
#define REFFRQ_VALUE    2  /* 0: 1M<=fREF<=2M  1: 2M<fREF<=6M  2: 6M<fREF<=12M  */


#endif 

/** System Clock status definitions */      
#define CLOCK_STATUS_OK                 0
#define CLOCK_STATUS_PLL_LOCK_ERROR     1
#define CLOCK_STATUS_SCM_ERROR          2


/****寄存器名称重定义************************************/
#define PLL_PROT      CPMUPROT_PROT
#define PLL_PLLSEL    CPMUCLKS_PLLSEL
#define PLL_SYNDIV    CPMUSYNR_SYNDIV
#define PLL_REFDIV    CPMUREFDIV_REFDIV
#define PLL_REFFRQ    CPMUREFDIV_REFFRQ
#define PLL_POSTDIV   CPMUPOSTDIV_POSTDIV
#define PLL_VCOFRQ    CPMUSYNR_VCOFRQ
#define PLL_LOCK      CPMUFLG_LOCK
#define PLL_LOCKIF    CPMUFLG_LOCKIF
#define PLL_LOCKIE    CPMUINT_LOCKIE
#define PLL_OSCE      CPMUOSC_OSCE



/***********************************************/

#define COP_Word1  0x55
#define COP_Word2  0xAA




/*-- Function Prototypes -----------------------------------------------------*/

/** Othe CPU initalization parameters */
void vfnCpu_init(void);

/** System clock and PLL initialization */
void vfnClock_Init(void);

void Clock_Disabled(void);
void COP_Init(void);
void Restart_COP_Timer(void);
void Disable_COP_Timer(void);
/** Clock Monitor Interrupt Service Routine */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Clock_Monitor_Isr(void);
void interrupt COP_Isr(void);
#pragma CODE_SEG DEFAULT

#endif /* _CPU_H */

/*******************************************************************************/