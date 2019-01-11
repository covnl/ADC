/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Input_Output.c
\brief      Inputs and Outputs functions for Seabreeze Emulator board 
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       12/Feb/2008
*/
/*                                                                             */
/*******************************************************************************/



#include "typedefs.h"
/* -- Variables --------------------------------------------------------*/

/*******************************************************************************/
/**
* \brief    Inputs and Outputs Initialization to default values/configuration \n
            as per Seabreeze Emulator Hardware Test Code Specification version 0.3
* \author   Engineer
* \param    void
* \return   void
*/

void vfnInputs_Outputs_Init(void)
{                  

     /****************************************************************
     ******         Port A Initializtion                     *********
     *****************************************************************/ 
     
     /* Enables Pull-up for all port A input channels */
     PUCR_PUPAE = ENABLED;
     
       /** ISM_ENABLEA, Port A, Channel 0 */
       DDRA_DDRA0 = OUTPUT;
       ISM_ENABLEA = LOW;
       /** ISM_ENABLEB, Port A, Channel 1 */
       DDRA_DDRA1 = OUTPUT;
       ISM_ENABLEB = LOW;
     
     /** UNUSED ,Port A, channel 2 */
     #ifdef LLD_4T1CCD_TR
         DDRA_DDRA2 = INPUT;
     #endif
     
     #ifdef LLD_4T1CTH_TR2_0M
         DDRA_DDRA2 = INPUT;
     #endif
     /** UNUSED ,Port A, channel 3 */
     /** POWEROFF ,Port A, channel 4 */
     DDRA_DDRA4 = OUTPUT;
     #ifdef PowDownDelay_Disabled
       POWEROFF = LOW;
     #else 
       POWEROFF = HIGH;
     #endif    
     /** UNUSED ,Port A, channel 5 */
     /** UNUSED ,Port A, channel 6 */
     /** UNUSED ,Port A, channel 7 */   
     
     /****************************************************************
     ******         Port E Initializtion                     *********
     *****************************************************************/ 
     DDRE_DDRE6 = OUTPUT; 
     /****************************************************************
     ******         Port S Initializtion                     *********
     *****************************************************************/ 
     
     /** RXD, Port S, Channel 0, Pull Up */
     DDRS_DDRS0 = INPUT;
     PERS_PERS0 = ENABLED;
     PPSS_PPSS0 = PULL_UP; 
     /** TXD, Port S, Channel 1, High */
     DDRS_DDRS1 = OUTPUT;

     
     /****************************************************************
     ******         Port T Initializtion                     *********
     *****************************************************************/ 
     
     /* Disconnect all output compare pins on port T */
     OCPD = 0xFF; 
     //================2013-10-30新加的，下载标定数据时关闭所有Timer中断
     TIE = FALSE;
     TSCR2_TOI = FALSE;
       
     /** IGNOUT1, Port T, Channel 1, Low */
     DDRT_DDRT1 = OUTPUT;             
     IGNIN1 = LOW;
     /** IGNOUT2 ,Port T, channel 0 */
     DDRT_DDRT2 = OUTPUT;             
     IGNIN2 = LOW;
     /** Crank_TimeOut ,Port T, channel 2 */
     /** VRSOUT ,Port T, channel 3 */
     DDRT_DDRT3 = INPUT; 
     PERT_PERT3 = ENABLED;             
     PPST_PPST3 = PULL_DOWN;
     /** INJIN2 ,Port T, channel 4 */
     DDRT_DDRT4 = OUTPUT; //单缸系统故障诊断驱动IO口采用喷油2通道
     INJIN2 = LOW;
     /** INJIN1 ,Port T, channel 5 */
     DDRT_DDRT5 = OUTPUT;
     INJIN1 = LOW;
     /** Servo PWM in ,Port T, channel 7 */
     DDRT_DDRT7 = INPUT; 
     /****************************************************************
     ******         Port B Initializtion                     *********
     *****************************************************************/ 
     /** TPMA , Port B, Channel 0*/
       DDRB_DDRB0 = OUTPUT;
       //TPMC = LOW;
       LSM303D_CS = HIGH;
     /** TPMB , Port B, Channel 1*/
       DDRB_DDRB1 = OUTPUT;
       TPMD = LOW;
     /** TPMC , Port B, Channel 2*/
       DDRB_DDRB2 = OUTPUT;
       TPMA = LOW;
     /** TPMD , Port B, Channel 3*/
       DDRB_DDRB3 = OUTPUT;
       TPMB = LOW;
                    
     /****************************************************************
     ******         Port AD0 Initializtion                     *********
     *****************************************************************/ 
     /** W_O2, Port AD0, Channel 0 */
    DDR1AD_DDR1AD0 = INPUT;
    ATDDIEN_IEN0 =  DISABLED;
    PER1AD_PER1AD0 = DISABLED;
    
    /** O2IN2, Port AD0, Channel 1 */
    DDR1AD_DDR1AD1 = INPUT;
    ATDDIEN_IEN1 =  DISABLED;
    PER1AD_PER1AD1 = DISABLED;
    
    /** O2IN1, Port AD0, Channel 2 */
    DDR1AD_DDR1AD2 = INPUT;
    ATDDIEN_IEN2 =  DISABLED;
    PER1AD_PER1AD2 = DISABLED;
    
    /** MAP, Port AD0, Channel 3 */
    DDR1AD_DDR1AD3 = INPUT;
    ATDDIEN_IEN3 =  DISABLED;
    PER1AD_PER1AD3 = DISABLED;
    
    /** TPS, Port AD0, Channel 4 */
    DDR1AD_DDR1AD4 = INPUT;
    ATDDIEN_IEN4 =  DISABLED;
    PER1AD_PER1AD4 = DISABLED;
    
    /** VBAT, Port AD0, Channel 5 */
    DDR1AD_DDR1AD5 = INPUT;
    ATDDIEN_IEN5 =  DISABLED;
    PER1AD_PER1AD5 = DISABLED;
    
    /** ATEMP, Port AD0, Channel 6 */
    DDR1AD_DDR1AD6 = INPUT;
    ATDDIEN_IEN6 =  DISABLED;
    PER1AD_PER1AD6 = DISABLED;
    
    /** ETEMP, Port AD0, Channel 7 */
    DDR1AD_DDR1AD7= INPUT;
    ATDDIEN_IEN7 =  DISABLED;
    PER1AD_PER1AD7 = DISABLED;
    /** Tilt, Port AD0, Channel 8 */
    DDR0AD_DDR0AD0= INPUT;
    ATDDIEN_IEN8 =  DISABLED;
    PER0AD_PER0AD0 = DISABLED;
    /** IGNSW, Port AD0, Channel 9 */ 
    DDR0AD_DDR0AD1= INPUT;
    ATDDIEN_IEN9 =  DISABLED;
    PER0AD_PER0AD1 = DISABLED;
         
     /****************************************************************
     ******         Port P Initializtion                     *********
     *****************************************************************/ 
     
     /** MIL_Lamp , Port P, Channel 1*/
     DDRP_DDRP1 = OUTPUT;
     MIL_Lamp = LOW;
     /** O2HIN1 , Port P, Channel 2*/
     DDRP_DDRP2 = OUTPUT;
     O2H1 = LOW; 
     /** O2HIN2 , Port P, Channel 3*/
     DDRP_DDRP3 = OUTPUT;
     /** FFPOUT , Port P, Channel 3*/
     DDRP_DDRP5 = OUTPUT;

     
     /****************************************************************
     ******         Port M Initializtion                     *********
     *****************************************************************/ 
     /** UNUSED , Port M, Channel 0*/
     #ifdef CAN_MODULE_ENABLE
       DDRJ_DDRJ7 = OUTPUT;
     #else
       DDRM_DDRM0 = OUTPUT;
     #endif  
     ROUT = LOW;
     /****************************************************************
     ******         Port J Initializtion                     *********
     *****************************************************************/ 
     #ifdef LLD_4T1CCD_TR
       /** HALL_F , Port J, Channel 0*/
       DDRJ_DDRJ0 = INPUT;
       PPSJ_PPSJ0 = TRUE;//Rising edge selected
       PIEJ_PIEJ0 = TRUE;//Enable interrupt
       /** HALL_A , Port J, Channel 1*/
       DDRJ_DDRJ1 = INPUT;
       PPSJ_PPSJ1 = TRUE;//Rising edge selected
       PIEJ_PIEJ1 = TRUE;//Enable interrupt
     #endif
     
     #ifdef LLD_4T1CTH_TR2_0M
       /** HALL_F , Port J, Channel 0*/
       DDRJ_DDRJ0 = INPUT;
       PPSJ_PPSJ0 = TRUE;//Rising edge selected
       PIEJ_PIEJ0 = TRUE;//Enable interrupt
       /** HALL_A , Port J, Channel 1*/
       DDRJ_DDRJ1 = INPUT;
       PPSJ_PPSJ1 = TRUE;//Rising edge selected
       PIEJ_PIEJ1 = TRUE;//Enable interrupt 
     #endif
}


void vfnInputs_Outputs_Disabled(void)
{
     
     PERM = DISABLED;
   
     DDRS_DDRS0 = DISABLED;
     PERS_PERS0 = DISABLED;
     PPSS_PPSS0 = DISABLED; 
     /** TXD, Port S, Channel 1, High */
     DDRS_DDRS1 = DISABLED;
   
     DDRT = DISABLED; 
     DDRP = DISABLED;
     DDRM = DISABLED;
   
}
/**********************************************************************/
/*********************************************************************/
    
   
