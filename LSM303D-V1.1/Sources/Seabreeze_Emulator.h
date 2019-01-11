/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Seabreeze_Emulator.h
\brief      Seabreeze Emulator Compilation Options.
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       15/Feb/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#ifndef __SEABREEZE_EMULATOR
#define __SEABREEZE_EMULATOR

/*-- Includes ----------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/** Target firmware option - Select ONLY one */
#define __EMULATOR_HARDWARE_FIRMWARE

/** S12X Derivative Selection - Select ONLY one */
#define __S12P128



/*-- Macros ------------------------------------------------------------------*/

/** S12X derivative information */
#ifdef  __S12P128
    #define __S12P_DERIVATIVE   <mc9s12p128.h>
    #define __S12P_LINK_DERIVATIVE  "mc9s12p128"
#else    
    #ifdef  __S12P64
        #define __S12P_DERIVATIVE   <mc9s12p64.h> 
        #define __S12P_LINK_DERIVATIVE  "mc9s12p64"
    #else    
        #ifdef __S12P32  
            #define __S12P_DERIVATIVE   <mc9s12p32.h>
            #define __S12P_LINK_DERIVATIVE  "mc9s12p32"
        #endif
    #endif
#endif

/*-- Function Prototypes -----------------------------------------------------*/

#endif /*__SEABREEZE_EMULATOR */
