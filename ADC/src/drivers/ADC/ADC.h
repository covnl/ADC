/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       ADC.h$
* @file             ADC.h
*
* $Date:            Jul-04-2014$
* @date             Jul-04-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description:      ADC driver header file
* @brief            ADC driver header file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage ADC driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains ADC driver for MPC5744P allowing to configure and 
*	control ADC module. Driver is not portable on another platform without 
*	additional changes. 

*  The key features of this package are the following:
*  - Initializate ADC module for Normal and Injected conversions
*  - Change setting of the ADC module
*  - Launch Normal and Injected conversions
*  - Treat results from ADC conversions
*
*  For more information about the functions and configuration items see these documents: 
*
*******************************************************************************
*
* @attention 
*            
*******************************************************************************/
/*==================================================================================================
*   Project              : PowerSBC
*   Platform             : MPC5744P
*   Dependencies         : MPC5744P - Basic SW drivers.
*   All Rights Reserved.
==================================================================================================*/

/*==================================================================================================
Revision History:
                             Modification     Function
Author (core ID)              Date D/M/Y       Name		  Description of Changes
B35993		 				  04/07/2014  	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#ifndef _ADC_H_
#define _ADC_H_

///Standard channel Masks
///Channels 9, 10, 15 internally connected
#define CHSmask		0x000000000000FFFF		
#define CH0Smask	0x0000000000000001
#define CH1Smask	0x0000000000000002
#define CH2Smask	0x0000000000000004
#define CH3Smask	0x0000000000000008
#define CH4Smask	0x0000000000000010		
#define CH5Smask	0x0000000000000020
#define CH6Smask	0x0000000000000040
#define CH7Smask	0x0000000000000080
#define CH8Smask	0x0000000000000100		
#define CH11Smask	0x0000000000000800		//shared between ADC0 and ADC1
#define CH12Smask	0x0000000000001000		//shared between ADC0 and ADC1
#define CH13Smask	0x0000000000002000		//shared between ADC0 and ADC1
#define CH14Smask	0x0000000000004000		//shared between ADC0 and ADC1


///MCR parameters
#define OWRITE_DIS		0x00000000									//overwrite disabled
#define OWRITE_EN		0x80000000									//overwrite enable
#define	ALIGN_R			0x00000000									//result aligned to the rigth
#define	ALIGN_L			0x40000000									//result aligned to the left
#define ONE_SHOT		0x00000000									//one shot mode
#define SCAN			0x20000000									//scan mode
#define PWDN_DIS		0x00000000									//normal mode
#define PWDN_EN			0x00000001									//power down mode
#define ACKO_EN			0x00000020									//auto clock off enabled
#define ACKO_DIS		0x00000000									//auto clock off disabled
#define DEFAULT_ADC		OWRITE_DIS | SCAN | PWDN_DIS | ALIGN_R | ACKO_DIS	//default setting for ADC	


///MSR - ADC status parameters
#define ADC_IDLE	0b000
#define ADC_PWDN	0b001
#define ADC_WAIT	0b010
#define ADC_SAMPLE	0b100
#define ADC_CONV	0b110

///CTR - INPCMP parameters
#define AD_CLK3		0b01	//ADC clock = 3 MHz
#define AD_CLK6		0b10	//ADC clock = 6 MHz
#define AD_CLK9		0b11	//ADC clock = 9 MHz
#define AD_CLK12	0b00	//ADC clock = 12 MHz	NOT possible for Bolero single core

///CTR default setting
#define DEFAULT_CTR 0x00008606

///IMR interrupt parameters
#define EOCTU_FLAG 	0x00000010
#define JEOC_FLAG		0x00000008	
#define JECH_FLAG		0x00000004
#define EOC_FLAG		0x00000002
#define ECH_FLAG		0x00000001
#define EOCTU_FLAG		0x00000010
	
///PSCR presampling parameters
#define VSS		0x00	//Prescaler value = Vss
#define VDD		0x01	//Prescaler value = Vdd

///Memory offset definitions
#define MCR_OFF				0x000
#define MSR_OFF				0x004
#define ISR_OFF				0x010
#define CEOCFR0_OFF			0x014
#define IMR_OFF				0x020
#define CIMR0_OFF			0x024
#define WTISR_OFF			0x030
#define WTIMR_OFF			0x034
#define DMAE_OFF			0x040
#define DMAR0_OFF			0x044
#define THRHLR0_OFF			0x060	
#define THRHLR1_OFF			0x064
#define THRHLR2_OFF			0x068
#define THRHLR3_OFF			0x06C
#define PSCR_OFF			0x080
#define PSR0_OFF			0x084
#define CTR0_OFF			0x094
#define CTR1_OFF			0x098
#define	NCMR0_OFF			0x0A4
#define JCMR0_OFF			0x0B4
#define PDEDR_OFF			0x0C8
#define CDR0_OFF			0x100		//till CDR15 each 4Bytes
#define	THRHLR4_OFF		0x280		//till THRHLR15 each 4Bytes
#define CWSEL0_OFF		0x2B0
#define CWSEL1_OFF		0x2B4
#define CWENR0_OFF		0x2E0
#define AWORR0_OFF		0x2F0


/////MICRO define for adc0_init(),adc1_init(),adc2_init(),adc3_init, enable CTU trigger
/*
ADC0/1/2/3 registers configuration
--------------------------------------
*/
#define ADC0_MCR                       0x80020000UL   //enable CTU trigger ADC
#define ADC0_CTR0                      0x00000016UL

#define ADC1_MCR                       0x80020000UL
#define ADC1_CTR0                      0x00000016UL

#define ADC2_MCR                       0x80020000UL
#define ADC2_CTR0                      0x00000016UL

#define ADC3_MCR                       0x80020000UL
#define ADC3_CTR0                      0x00000016UL


uint8_t ADC_IsNormalConvRunning(uint8_t);
uint8_t ADC_IsInjectedConvAborted(uint8_t);
uint8_t ADC_IsInjectedConvRunning(uint8_t);
uint8_t ADC_IsCTUconvRunning(uint8_t);
uint8_t ADC_GetCurrentChannelAddress(uint8_t);
uint8_t ADC_GetAutoClockOffState(uint8_t);
uint8_t ADC_GetStatus(uint8_t);
void ADC_Init(uint8_t, uint64_t, uint64_t, uint32_t);
void ADC_StartNormalConversion(uint8_t, uint32_t);
void ADC_StopConversion(uint8_t);
void ADC_StartInjectedConversion(uint8_t, uint64_t);
void ADC_SetOneShotMode(uint8_t);
void ADC_SetScanMode(uint8_t);
void ADC_AutoClockOffEnable(uint8_t);
void ADC_AutoClockOffDisable(uint8_t);
uint16_t ADC_GetChannelValue(uint8_t, uint32_t);
void ADC_SetInt(uint8_t, uint32_t,uint32_t);
void ADC_ClearEOCflag(uint8_t,uint32_t);
void ADC_ClearAllEOCflags(uint8_t);
void ADC_ClearEOCTUflag(uint8_t);
void ADC_ClearEOCTUflag(uint8_t);
void ADC_ClearJECHflag(uint8_t);
void ADC_ClearECHflag(uint8_t);
void ADC_SetThldRegister(uint8_t, uint8_t, uint16_t, uint16_t, uint32_t);
void ADC_SetThldForChannel(uint8_t, uint32_t, uint8_t);
void ADC_ClearThldFlags(uint8_t);
void ADC_SetVDDforPresampling(uint8_t, vuint32_t);
void ADC_SetVSSforPresampling(uint8_t, vuint32_t);
void ADC_EnableSampleBypass(uint8_t);
void ADC_DisableSampleBypass(uint8_t);
void ADC_SetSamplingTime(uint8_t, uint32_t, float);

////adc0/1/2/3 initial
void adc0_init(void);
void adc1_init(void);
void adc2_init(void);
void adc3_init(void);

void ADC1_Init_v1(void);
#endif
