/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       IGNSW.h
\brief      Ignition Switch Monitoring.
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\ThirdParty engieer/engieer (lab)
\version    0.2
\date       Aug/ 2008
*/
/*******************************************************************************/

/* Ignition Switch data collection rate check 
#if IGNSW_DATA_COLLECTION_RATE < DATA_MANAGEMENT_TASK
#error "Ignition Switch Data collection periodic rate is faster than the timeout period of the Data Management Task"
#endif*/

/** Function prototypes */
 
#define BATTERY_DIGITAL_11V  1760 //    11V  =160*11 
#define BATTERY_DIGITAL_8V   1278 //1278--8V  =160*8
 
#define BATTERY_DIGITAL_6V   958 //6*6.8/21.8*4096/5*5/8     =160*6

#define IGNSW_LOW    1148 //1532-6V -- 1.87V   1276--5v  1148--4.5v

#define DEBOUNCE_TIME 10
 
void vfnIGNSW_Filter(void);
void vfnIGNSW_Monitoring(void);
void vfnIGNSW_Init(void);
UINT8 CompareUbAdcWith11V(void);
void TRACT_EN_Monitoring(void);

/*******************************************************************************/