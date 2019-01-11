/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Cpu.c
\brief      S12XEP100 CPU initialization, bus clock @40MHz \n
            and interrupts configuration routines
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

#include "typedefs.h"

/* -- Variables --------------------------------------------------------*/

/* Global variable that holds status of Clock */
UINT16 gu16ClockGlobalStatus;
/* Loss of Lock counter, private variable */
static UINT16 u16PLL_Loss_of_Lock_Counter;

/*******************************************************************************/
/**
* \brief    Other CPU initalization parameters
* \author   Engineer
* \param    void
* \return   void
* \todo     none
*/
void vfnCpu_init(void)
{               
    DIRECT = 0;     /* Default location for direct page */              
    IVBR = 0xEE;    /* Default vector base address */    

    //Disable IRQ pin
    IRQCR_IRQEN = 0;
}

/*******************************************************************************/
/**
* \brief    PLL initialization, Bus Clock @ 40MHz
* \author   Engineer
* \param    void
* \return   void
*/
void vfnClock_Init(void)
{                 
    PLL_PROT = 0;
    PLL_PLLSEL = 1; 
    PLL_SYNDIV = SYNR_VALUE; 
    // PLL_REFDIV = REFDV_VALUE; 
    PLL_REFFRQ = REFFRQ_VALUE;
    PLL_POSTDIV = POSTDIV_VALUE;     
    PLL_VCOFRQ = VCOFRQ_VALUE;  
  
    gu16ClockGlobalStatus = CLOCK_STATUS_OK;  
    u16PLL_Loss_of_Lock_Counter = 0;   

    while(!PLL_LOCK){;}
  
    PLL_LOCKIF = 1;    
    PLL_LOCKIE = 1;     
    PLL_OSCE = 0;    /* Enable oscillator,write the register when FPROT=0 and PLLSEL = 1 */  

    //=========ECLK output========
    ECLKCTL = 0x43;//8MHz output
 
}


void Clock_Disabled(void)   //1M
{
 
}

/*******************************************************************************
**看门狗初始化
**
*******************************************************************************/
void COP_Init(void)
{
    CPMUCLKS_COPOSCSEL = 0;//0--IRCCLK 1--OSCCLK
    CPMUCOP_RSBCK = 0;//Allow COP keep running in BDM mode.
    CPMUCOP_CR = 0x02;//1--16.384ms  2--65.536ms  3--262.144ms  4--1048.576ms
}

void Restart_COP_Timer(void)
{
    CPMUARMCOP = COP_Word1;
    CPMUARMCOP = COP_Word2;
}

void Disable_COP_Timer(void)
{
    CPMUCOP_CR = DISABLED;
}
/*******************************************************************************/
/**
* \brief    Clock monitor Interrupt Service routine.
* \author   Engineer
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Clock_Monitor_Isr(void)
{   
    /* Verify that IPLL Lock Interrupt Flag caused the interrupt */
    if (PLL_LOCKIF == 1)
    {
        /* Clear IPLL Lock Interrupt Flag */  
        PLL_LOCKIF = 1;
        /* Update Loss-of-Lock event counter */
        u16PLL_Loss_of_Lock_Counter++;
        if (u16PLL_Loss_of_Lock_Counter >= 5)
        {
            /* Set gu16ClockGlobalStatus to its appropriate status */
            gu16ClockGlobalStatus = CLOCK_STATUS_PLL_LOCK_ERROR;
            /* Configure all I/O to their default values */
            /* If we reach Loss-of-Lock 5 consecutive times, get into an infinite loop */
            //for (;;){;}
        }
    }

}


void interrupt COP_Isr(void)
{   
    SCI_WriteTx(0x80);
    Disable_All_Interrupts();
    asm
    {
       JMP $F000
    }
}



#pragma CODE_SEG DEFAULT    
        
/*******************************************************************************/
