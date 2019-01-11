/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Relays.h
\brief      Relays control functions
\author     COMPANY_XXX
\author     Application Lab
\ThirdParty engieer/engieer (lab)
\version    0.1
\date       Jun/ 2008
*/
/*******************************************************************************/

/* Define to enable Relay1 operation */


#define RELAY1  1

/* Define to enable Relay2 operation */
#define RELAY2  2

/* Define to enable Relay3 operation */
#define RELAY3  3

#define FUEL_PUMP  RELAY1
/** Function prototypes */
 
 
void OilPump1_PWM_1ms(void);
void OilPump2_PWM_1ms(void);
void FuelPump_Relay_r20ms(void);
void FuelPump_PWM_r1ms(void);
void LLD_ServoCtl_r10ms(void);
void LLD_GearPmpCtl_r20ms(void);

/*******************************************************************************/