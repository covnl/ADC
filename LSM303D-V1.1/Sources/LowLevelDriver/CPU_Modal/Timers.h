/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Timers.h
\brief      Definitions for S12XEP100 timers configuration
            and interrupts configuration routines
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       December/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#ifndef _TIMERS_H
#define _TIMERS_H

/*-- Includes ----------------------------------------------------------------*/

/*-- Macros ----------------------------------------------------------------*/

/* Timer modules definitions for hardware abstraction layer */

//#define Toggle_Spark_Channel
#ifdef Toggle_Spark_Channel
    /** Timer channel A */
    #define TIMER_CHANNEL_A                 TC1        
    /** Timer channel A interrupt enable/disable */ 
    #define CHANNEL_A_INTERRUPT(SELECT_BIT) TIE_C1I = SELECT_BIT  
    /* Actions on compare event for timer channel A */     
    #define NO_ACTION_ON_COMPARE_EVENT_A()  TCTL2_OM1 = 0; TCTL2_OL1 = 0
    #define TOGGLE_ON_COMPARE_EVENT_A()     TCTL2_OM1 = 0; TCTL2_OL1 = 1                                                                               
    #define CLEAR_ON_COMPARE_EVENT_A()      TCTL2_OM1 = 1; TCTL2_OL1 = 0
    #define SET_ON_COMPARE_EVENT_A()        TCTL2_OM1 = 1; TCTL2_OL1 = 1                                            
    /** Force compare event on timer A */
    #define CHANNEL_A_FORCE_EVENT()         CFORC_FOC1 = 1 

    /** Timer channel B */
    #define TIMER_CHANNEL_B                 TC0        
    /** Timer channel B interrupt enable/disable */ 
    #define CHANNEL_B_INTERRUPT(SELECT_BIT) TIE_C0I = SELECT_BIT  
    /* Actions on compare event for timer channel B */     
    #define NO_ACTION_ON_COMPARE_EVENT_B()  TCTL2_OM0 = 0; TCTL2_OL0 = 0
    #define TOGGLE_ON_COMPARE_EVENT_B()     TCTL2_OM0 = 0; TCTL2_OL0 = 1                                                                               
    #define CLEAR_ON_COMPARE_EVENT_B()      TCTL2_OM0 = 1; TCTL2_OL0 = 0
    #define SET_ON_COMPARE_EVENT_B()        TCTL2_OM0 = 1; TCTL2_OL0 = 1                                            
    /** Force compare event on timer B */
    #define CHANNEL_B_FORCE_EVENT()         CFORC_FOC0 = 1 

#else 
    /** Timer channel A */
    #define TIMER_CHANNEL_A                 TC0        
    /** Timer channel A interrupt enable/disable */ 
    #define CHANNEL_A_INTERRUPT(SELECT_BIT) TIE_C0I = SELECT_BIT  
    /* Actions on compare event for timer channel A */     
    #define NO_ACTION_ON_COMPARE_EVENT_A()  TCTL2_OM0 = 0; TCTL2_OL0 = 0
    #define TOGGLE_ON_COMPARE_EVENT_A()     TCTL2_OM0 = 0; TCTL2_OL0 = 1                                                                               
    #define CLEAR_ON_COMPARE_EVENT_A()      TCTL2_OM0 = 1; TCTL2_OL0 = 0
    #define SET_ON_COMPARE_EVENT_A()        TCTL2_OM0 = 1; TCTL2_OL0 = 1                                            
    /** Force compare event on timer A */
    #define CHANNEL_A_FORCE_EVENT()         CFORC_FOC0 = 1 

    /** Timer channel B */
    #define TIMER_CHANNEL_B                 TC1        
    /** Timer channel B interrupt enable/disable */ 
    #define CHANNEL_B_INTERRUPT(SELECT_BIT) TIE_C1I = SELECT_BIT  
    /* Actions on compare event for timer channel B */     
    #define NO_ACTION_ON_COMPARE_EVENT_B()  TCTL2_OM1 = 0; TCTL2_OL1 = 0
    #define TOGGLE_ON_COMPARE_EVENT_B()     TCTL2_OM1 = 0; TCTL2_OL1 = 1                                                                               
    #define CLEAR_ON_COMPARE_EVENT_B()      TCTL2_OM1 = 1; TCTL2_OL1 = 0
    #define SET_ON_COMPARE_EVENT_B()        TCTL2_OM1 = 1; TCTL2_OL1 = 1                                            
    /** Force compare event on timer B */
    #define CHANNEL_B_FORCE_EVENT()         CFORC_FOC1 = 1 
#endif
/** Timer channel C */
#define TIMER_CHANNEL_C                 TC2        
/** Timer channel C interrupt enable/disable */ 
#define CHANNEL_C_INTERRUPT(SELECT_BIT) TIE_C2I = SELECT_BIT  
/* Actions on compare event for timer channel C */     
#define NO_ACTION_ON_COMPARE_EVENT_C()  TCTL2_OM2 = 0; TCTL2_OL2 = 0
#define TOGGLE_ON_COMPARE_EVENT_C()     TCTL2_OM2 = 0; TCTL2_OL2 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_C()      TCTL2_OM2 = 1; TCTL2_OL2 = 0
#define SET_ON_COMPARE_EVENT_C()        TCTL2_OM2 = 1; TCTL2_OL2 = 1                                            
/** Force compare event on timer C */
#define CHANNEL_C_FORCE_EVENT()         CFORC_FOC2 = 1 

/** Timer channel D */
#define TIMER_CHANNEL_D                 TC3        
/** Timer channel D interrupt enable/disable */ 
#define CHANNEL_D_INTERRUPT(SELECT_BIT) TIE_C3I = SELECT_BIT  
/* Actions on compare event for timer channel D */     
#define NO_ACTION_ON_COMPARE_EVENT_D()  TCTL2_OM3 = 0; TCTL2_OL3 = 0
#define TOGGLE_ON_COMPARE_EVENT_D()     TCTL2_OM3 = 0; TCTL2_OL3 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_D()      TCTL2_OM3 = 1; TCTL2_OL3 = 0
#define SET_ON_COMPARE_EVENT_D()        TCTL2_OM3 = 1; TCTL2_OL3 = 1                                            
/** Force compare event on timer D */
#define CHANNEL_D_FORCE_EVENT()         CFORC_FOC3 = 1 

/** Timer channel E */
#define TIMER_CHANNEL_E                 TC4        
/** Timer channel E interrupt enable/disable */ 
#define CHANNEL_E_INTERRUPT(SELECT_BIT) TIE_C4I = SELECT_BIT  
/* Actions on compare event for timer channel E */     
#define NO_ACTION_ON_COMPARE_EVENT_E()  TCTL1_OM4 = 0; TCTL1_OL4 = 0
#define TOGGLE_ON_COMPARE_EVENT_E()     TCTL1_OM4 = 0; TCTL1_OL4 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_E()      TCTL1_OM4 = 1; TCTL1_OL4 = 0
#define SET_ON_COMPARE_EVENT_E()        TCTL1_OM4 = 1; TCTL1_OL4 = 1                                            
/** Force compare event on timer E */
#define CHANNEL_E_FORCE_EVENT()         CFORC_FOC4 = 1 

/** Timer channel F */
#define TIMER_CHANNEL_F                 TC5        
/** Timer channel F interrupt enable/disable */ 
#define CHANNEL_F_INTERRUPT(SELECT_BIT) TIE_C5I = SELECT_BIT  
/* Actions on compare event for timer channel F */     
#define NO_ACTION_ON_COMPARE_EVENT_F()  TCTL1_OM5 = 0; TCTL1_OL5 = 0
#define TOGGLE_ON_COMPARE_EVENT_F()     TCTL1_OM5 = 0; TCTL1_OL5 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_F()      TCTL1_OM5 = 1; TCTL1_OL5 = 0
#define SET_ON_COMPARE_EVENT_F()        TCTL1_OM5 = 1; TCTL1_OL5 = 1                                               
/** Force compare event on timer F */
#define CHANNEL_F_FORCE_EVENT()         CFORC_FOC5 = 1 

/** Timer channel G */
#define TIMER_CHANNEL_G                 TC6        
/** Timer channel G interrupt enable/disable */ 
#define CHANNEL_G_INTERRUPT(SELECT_BIT) TIE_C6I = SELECT_BIT  
/* Actions on compare event for timer channel G */     
#define NO_ACTION_ON_COMPARE_EVENT_G()  TCTL1_OM6 = 0; TCTL1_OL6 = 0
#define TOGGLE_ON_COMPARE_EVENT_G()     TCTL1_OM6 = 0; TCTL1_OL6 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_G()      TCTL1_OM6 = 1; TCTL1_OL6 = 0
#define SET_ON_COMPARE_EVENT_G()        TCTL1_OM6 = 1; TCTL1_OL6 = 1                                               
/** Force compare event on timer G */
#define CHANNEL_G_FORCE_EVENT()         CFORC_FOC6 = 1 

/** Timer channel H */
#define TIMER_CHANNEL_H                 TC7        
/** Timer channel H interrupt enable/disable */ 
#define CHANNEL_H_INTERRUPT(SELECT_BIT) TIE_C7I = SELECT_BIT
/* Actions on compare event for timer channel H */       
#define NO_ACTION_ON_COMPARE_EVENT_H()  TCTL1_OM7 = 0; TCTL1_OL7 = 0
#define TOGGLE_ON_COMPARE_EVENT_H()     TCTL1_OM7 = 0; TCTL1_OL7 = 1                                                                               
#define CLEAR_ON_COMPARE_EVENT_H()      TCTL1_OM7 = 1; TCTL1_OL7 = 0
#define SET_ON_COMPARE_EVENT_H()        TCTL1_OM7 = 1; TCTL1_OL7 = 1                                            
/** Force compare event on timer channel A */
#define CHANNEL_H_FORCE_EVENT()         CFORC_FOC7 = 1 


/*-- Function Prototypes ---------------------------------------------------*/

UINT16 Get_FunctionExecute_Time();
void TimerModule_Disabled(void);


#endif /* _TIMERS_H */

/*******************************************************************************/
