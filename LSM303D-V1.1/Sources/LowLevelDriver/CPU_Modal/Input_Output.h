/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Input_Outpu.h
\brief      Inputs and Outputs functions for Seabreeze Emulator board 
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       20/March/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#ifndef _INPUT_OUTPUT_H
#define _INPUT_OUTPUT_H



/*-- Defines -----------------------------------------------------------------*/
 /*******************************************************************************
**定义结构体变量，用于各输入输出数据
********************************************************************************/

/************** Common signal status bits **********************/
typedef struct 
{
  UINT8 B_failed:1;       /* signal failed *comprehending min,max,and sig */
  UINT8 B_fail_pending:1; /* signal failure pending */
  UINT8 B_max:1;          /* signal value high or short to battery */
  UINT8 B_min:1;          /* signal value low or short to ground */
  UINT8 B_sig:1;          /* signal open load */
  UINT8 B_npl:1;          /* reserved position for HLS signal value non_plausible(EOBD) */
  UINT8 B_substitute:1;   /* substitute value is being passed by LLD */
  UINT8 B_clrerr:1;       /* reserved position for HLS */
}status_bits;




/* Data Direction Register definitions */
#define INPUT           0
#define OUTPUT          1
#define ANALOG_INPUT    2

/* Input pull-up and pull-down definitions */
#define PULL_DOWN       0
#define PULL_UP         1

/* Data output register definition */
#define LOW             0
#define HIGH            1



/** Ports redefinition for macros usability */
#ifndef PTA             
    #define PTA_PTA0 PORTA_PA0 
    #define PTA_PTA1 PORTA_PA1 
    #define PTA_PTA2 PORTA_PA2 
    #define PTA_PTA3 PORTA_PA3 
    #define PTA_PTA4 PORTA_PA4 
    #define PTA_PTA5 PORTA_PA5 
    #define PTA_PTA6 PORTA_PA6 
    #define PTA_PTA7 PORTA_PA7 
#endif

#ifndef PTE             
    #define PTE_PTE0 PORTE_PE0 
    #define PTE_PTE1 PORTE_PE1 
    #define PTE_PTE2 PORTE_PE2 
    #define PTE_PTE3 PORTE_PE3 
    #define PTE_PTE4 PORTE_PE4 
    #define PTE_PTE5 PORTE_PE5 
    #define PTE_PTE6 PORTE_PE6 
    #define PTE_PTE7 PORTE_PE7 
#endif

#ifndef PTB             
    #define PTB_PTB0 PORTB_PB0 
    #define PTB_PTB1 PORTB_PB1 
    #define PTB_PTB2 PORTB_PB2 
    #define PTB_PTB3 PORTB_PB3 
    #define PTB_PTB4 PORTB_PB4 
    #define PTB_PTB5 PORTB_PB5 
    #define PTB_PTB6 PORTB_PB6 
    #define PTB_PTB7 PORTB_PB7 
#endif


#ifndef DDRE_DDRE1
    #define DDRE_DDRE1  DDRE
#endif



/*-- Macros ------------------------------------------------------------------*/

/******************* Emulator Signal Name Abstraction *************************/

/* ~~~~~~~~ Digital Input signal mapping ~~~~~~~~~~~~~~~~~ */

/****************************************************************
******         Port A Initializtion                     *********
*****************************************************************/
  /** ISM_ENABLEA, Port A, Channel 0 */
  #define ISM_ENABLEA  PTA_PTA0
  /** ISM_ENABLEB, Port A, Channel 1 */
  #define ISM_ENABLEB  PTA_PTA1

/** TRACT_EN, Port A ,Channel 2  */
  #define TRACT_EN PTA_PTA2
/** UNUSED, Port A ,Channel 3  */
/** POWEROFF, Port A ,Channel 4  */
#define POWEROFF PTA_PTA4
/** UNUSED, Port A ,Channel 7  */
/** UNUSED, Port A ,Channel 7  */
/** UNUSED, Port A ,Channel 7  */

/****************************************************************
******         Port B Initializtion                     *********
*****************************************************************/
#ifdef Step_ABDC
  /** TPMA, Port B, Channal 0*/
  #define TPMC  PTB_PTB3
  /** TPMB, Port B, Channal 1*/
  #define TPMD  PTB_PTB0
  /** TPMC, Port B, Channel 2 */
  #define TPMA  PTB_PTB2
  /** TPMD, Port B, Channel 3 */
  #define TPMB  PTB_PTB1

#else  
  /** TPMA, Port B, Channal 0*/
  #define TPMC  PTB_PTB0 
  #define LSM303D_CS  PTB_PTB0
  /** TPMB, Port B, Channal 1*/
  #define TPMD  PTB_PTB1 
  /** TPMC, Port B, Channel 2 */
  #define TPMA  PTB_PTB2 
  /** TPMD, Port B, Channel 3 */
  #define TPMB  PTB_PTB3 
#endif

/** UNUSED, Port B, Channel 4  */
/** UNUSED, Port B, Channel 7*/

/****************************************************************
******         Port E Initializtion                     *********
*****************************************************************/

/** UNUSED ,Port E, channel 0 */
/** UNUSED ,Port E, channel 1 */
/** UNUSED ,Port E, channel 2 */
/** UNUSED ,Port E, channel 3 */
/** UNUSED ,Port E, channel 4 */
/** LAMPIN ,Port E, channel 5 */
/** UNUSED ,Port E, channel 6 */
/** UNUSED ,Port E, channel 7 */

/****************************************************************
******         Port T Initializtion                     *********
*****************************************************************/
/** IGNIN2,Port T, channel 0 */
#define IGNIN2 PTT_PTT0
/** IGNIN ,Port T, channel 1 */
#define IGNIN1 PTT_PTT1
/** output compare for verify port level ,Port T, channel 2 */

/** VRSOUT ,Port T, channel 3 */
#define CRANK_INPUT_PORT_LEVEL  PTT_PTT3
/** INJIN2 ,Port T, channel 4 */
#define INJIN2  PTT_PTT4
/** INJIN1 ,Port T, channel 5 */
#define INJIN1  PTT_PTT5
/** missing tooth interrupt ,Port T, channel 6 */
/** UNUSED ,Port T, channel 7 */


/****************************************************************
******         Port S Initializtion                     *********
*****************************************************************/

/** RXD0 ,Port S, channel 0 */
#define RXD  PTS_PTS0
/** TXD0 ,Port S, channel 1 */
#define TXD PTS_PTS1
/** UNUSED ,Port S, channel 2 */
/** UNUSED ,Port S, channel 3 */
/****************************************************************
******         Port AD0 Initializtion                     *********
*****************************************************************/



/****************************************************************
******         Port P Initializtion                     *********
*****************************************************************/

  /** UNUSED , Port P, Channel 0*/
  /** MIL_Lamp , Port P, Channel 1*/
  #define MIL_Lamp PTP_PTP1
  /** O2HIN1 , Port P, Channel 2*/
#ifdef LLD_4T1CTH_1_1  
  #define O2H1 PTM_PTM0 
  #define ROUT   PTP_PTP2
#else
  #define O2H1 PTP_PTP2 
  #ifdef CAN_MODULE_ENABLE
    #define ROUT   PTJ_PTJ7
  #else
    #define ROUT   PTM_PTM0
  #endif  
#endif
  
  /** O2HIN2 , Port P, Channel 3*/
#ifdef LLD_V10_3W_HK  
  #define O2HIN2  PTP_PTP0
  #define FFPOUT PTP_PTP3
#else
  #define O2H2 PTP_PTP3
#endif  
  /** UNUSED , Port P, Channel 4*/
  /** UNUSED , Port P, Channel 5*/
  #define PWMOUT_MOTO PTP_PTP3
  /** UNUSED , Port P, Channel 6*/
  /** UNUSED , Port P, Channel 7*/

/****************************************************************
******         Port M Initializtion                     *********
*****************************************************************/

/** ROUT , Port M, Channel 0*/
/** UNUSED , Port M, Channel 1*/
/** UNUSED , Port M, Channel 2*/
/** UNUSED , Port M, Channel 3*/
/** UNUSED , Port M, Channel 4*/
/** UNUSED , Port M, Channel 5*/
#ifdef OilPmpPort_Custom1
  #define OIL_PUMP3  PTT_PTT4
  #define OIL_PUMP4  PTP_PTP2
#else
  #define OIL_PUMP3  PTM_PTM4
  #define OIL_PUMP4  PTM_PTM5
#endif
/****************************************************************
******         Port J Initializtion                     *********
*****************************************************************/
/** UNUSED , Port J, Channel 0*/
/** UNUSED , Port J, Channel 1*/
#ifdef LKT4200
  /** UNUSED , Port J, Channel 6*/
  #define  LKT4200_IO  PTJ_PTJ6
  #define  LKT4200_RESET PTE_PTE6
  #define  LKT4200_IO_STATUS(SELECTOR) DDRJ_DDRJ6 = SELECTOR

#endif

/** UNUSED , Port J, Channel 7*/
 //ROUT=PJ7




void vfnInputs_Outputs_Init(void);
void vfnInputs_Outputs_Disabled(void);

#endif /* _INPUT_OUTPUT_H */

/*******************************************************************************/