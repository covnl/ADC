/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Timers.c
\brief      S12XEP100 timers configuration
            and interrupts configuration routines
\author     COMPANY_XXX
\author     Application Lab
\author     B20740
\version    0.1
\date       December/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "typedefs.h"
/* -- Variables --------------------------------------------------------*/


/*******************************************************************************/
/**
* \brief    Timer Module initalization 
* \author   Engineer
* \param    void
* \return   void
*/

void TimerModule_Disabled(void)
{
   TIE = 0;
   TCTL1 = 0;
   TCTL2 = 0;
   TCTL3 = 0;
   TCTL4 = 0;
   
   TIOS = 0;
   TSCR1 = 0;
   TSCR2 = 0; 
}
/*******************************************************************************/
/**
* \brief    Timer channel: Input compare configuration
* \author   Engineer
* \param    void
* \return   void
*/
//void vfnTimer_Config_InputCompare(UINT8 u8Channel, UINT8 u8Action_on_Event)     
//{   
   

//}
UINT16 Get_FunctionExecute_Time()
{
   static UINT16 previous_timer=0;
   static UINT16 current_timer;
   UINT16 execute_time;
  
   current_timer = TCNT;
   if(current_timer>previous_timer)
   {
      execute_time =current_timer - previous_timer;  
   }
   else
   {
       execute_time =current_timer+(0xFFFF - previous_timer);
   }
   previous_timer = current_timer;
   
   return execute_time;
}

/*******************************************************************************/

