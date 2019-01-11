/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       typedefs.h
\brief      Variable types and common macros
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer/Engineer
\version    0.2
\date       14/Feb/2008
\warning   
* History:
*/
/*******************************************************************************/

#ifndef TYPEDEFS_H        /*prevent duplicated includes*/
#define TYPEDEFS_H

/*-- Includes ----------------------------------------------------------------*/
#include "ctypes.h"

/*-- Types Definitions -------------------------------------------------------*/
typedef unsigned char   UINT8;  /*unsigned 8 bit definition */
typedef unsigned int  UINT16; /*unsigned 16 bit definition*/
typedef unsigned long   UINT32; /*unsigned 32 bit definition*/
typedef signed char     INT8;   /*signed 8 bit definition */
typedef int           INT16;  /*signed 16 bit definition*/
typedef long int        INT32;  /*signed 32 bit definition*/

typedef unsigned char   uint8_t;  /*unsigned 8 bit definition */
typedef unsigned int    uint16_t; /*unsigned 16 bit definition*/
typedef unsigned long   uint32_t; /*unsigned 32 bit definition*/
typedef signed char     int8_t;   /*signed 8 bit definition */
typedef int           int16_t;  /*signed 16 bit definition*/
typedef long int        int32_t;  /*signed 32 bit definition*/




/*-- Defines -----------------------------------------------------------------*/

/* Common Constants */
#define ON          1
#define OFF         0
#define TRUE        1
#define FALSE       0
#define PASS        0u
#define FAIL        1u
#define SET         1u
#define CLEAR       0u
#define ENABLED     1
#define DISABLED    0
#define INPUT           0
#define OUTPUT          1

/*-- Defines -----------------------------------------------------------------*/
/* Common Bit masks */

/* The following two lines were modified for S12XS compatibility */
#define ENABLE_INTERRUPTS()  {__asm CLI;}        /*interrupts enabled        */
#define DISABLE_INTERRUPTS() {__asm SEI;}        /*interrupts disabled       */



/* Common Constants */
#define ON          1
#define OFF         0
#define TRUE        1
#define FALSE       0
#define PASS        0u
#define FAIL        1u
#define SET         1u
#define CLEAR       0u
#define ENABLED     1
#define DISABLED    0

#define rt_MAX(u1,u2) ( ((u1)   >= (u2)) ? (u1)  : (u2)   )
#define rt_MIN(u1,u2) ( ((u1)   <= (u2)) ? (u1)  : (u2)   )

/*-- Macros ------------------------------------------------------------------*/
//#define S12XEP_MCU
#define S12P_MCU

/*-- Function Prototypes -----------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include <mc9s12p128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12p128"



//=====LowLevelDriver includes===========================
#include "Application Definitions.h"
#include "pragma.h"
#include "LKT4200.h"
#include "CPU.h"
#include "SCI.h"
#include "ADC.h"
#include "PWM.h"
#include "Input_Output.h"   
#include "Scheduler.h"
#include "Idle_Speed_Control.h"
#include "Data Management.h"
#include "Flashing_Code.h"
#include "IGNSW.h"
#include "O2H.h"
#include "Relays.h"
#include "D_Flash.h"
#include "Ini_LLD.h"
#include "Relays.h"
#include "Timers.h"
#include "HLS_VariablesForLLD.h"
#include "CAN.h"
#include "UAV_CAN_Protocol.h"
#include "CANDataProcess.h"
#include "SPI.h"
#include "LSM303D.h"
#include "SAE_J1939_Driver.h"
#include "IMU.h"


#ifdef Enable_CrankLLD
  #include "Includes_for_LLD.h"
#endif

#include "kwp2000.h"
#include "ccp_driver.h"
#include "HLS_Ini.h"

#ifdef Enable_Application_Software
  #include "Controller.h"
  #include "Controller_private.h"
  #include "ctypes.H"   
#endif
#include "rtwtypes.h"
#include "Tasks.h"
#include "Self_Learning.h"
#include "afterrun.h"













#endif /* TYPEDEFS_H */