/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       10/Feb/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#ifndef __TASKS
#define __TASKS

/*-- Includes ----------------------------------------------------------------*/



/*-- Types Definitions -------------------------------------------------------*/
//extern UINT16 gu8Index;

//extern INT8 ai8TempBuffer[4];

/*-- Defines -----------------------------------------------------------------*/
/*-- Macros ------------------------------------------------------------------*/

/* List of tasks to be executed @ 1ms */
#pragma CODE_SEG __NEAR_SEG MY_CODE_ROM
// Data_Management_Digital();
//tasks_1ms(); 
#define EXECUTE_1MS_TASKS()   \
{                             \
   tasks_1ms();             \
}

#pragma CODE_SEG DEFAULT

/* List of tasks to be executed @ 5ms, second group */
#define EXECUTE_5MS_TASKS()   \
{                               \
                                \
}

/* List of tasks to be executed @ 10ms, second group */
#define EXECUTE_10MS_TASKS()   \
{                               \
    tasks_10ms();                \
}
/* List of tasks to be executed @ 20ms */
#define EXECUTE_20MS_TASKS()    \
{                               \
    tasks_20ms();                \
}
/* List of tasks to be executed @ 50ms */
#define EXECUTE_50MS_TASKS()    \
{                               \
    tasks_50ms();               \
}
/* List of tasks to be executed @ 100ms   */
//#ifdef __EMULATOR_HARDWARE_FIRMWARE
#define EXECUTE_100MS_TASKS()   \
{                               \
  tasks_100ms();                 \
}
 /* List of tasks to be executed @ 200ms */
#define EXECUTE_200MS_TASKS()    \
{                               \
     tasks_200ms();              \
}
 /* List of tasks to be executed @ 1000ms */
#define EXECUTE_1000MS_TASKS()    \
{                               \
   tasks_1000ms();             \
}
//#else
//    #define EXECUTE_100MS_TASKS()   \
//    {;}
//#endif

/*============================================================================*/
#endif /*__TASKS */
