/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2014 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       CAN.c$
* @file             CAN.c
*
* $Date:            Jul-23-2014$
* @date             Jul-23-2014
*
* $Version:         0.9$
* @version          0.9
*
* Description      CAN driver source file
* @brief           CAN driver source file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage CAN driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains CAN driver allowing to configure/initialize CAN module
*	and transmit CAN frames.

*  The key features of this package are the following:
*  - Initializate CAN module 
*  - Send CAN frames
*  - Disable CAN module
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
B35993		 				  23/07/2014 	   ALL		  Driver created

---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#include "Defines.h"
#include "EXTGLOBALS.h"
#include "CAN.h"
#include "SIUL.h"

volatile struct CAN_tag *CAN[3] = {&CAN_0, &CAN_1, &CAN_2};

/***************************************************************************//*!
*   @brief The function CAN_ConfigurePads configures pads of the CANx module.
*	@par Include 
*					CAN.h
* 	@par Description 
*					This function configures pads (Tx/Rx) for CAN module 
*					specified by nbModule.
* 	@param[in] nbModule
*					Number of the CAN module (0 or 1).
*	@remarks This function is used by the CAN_Init function.
*	@par Code sample
*			CAN_ConfigurePads(0);
*			- Function configures pads for transmission and reception for the 
*				CAN module number 0.
********************************************************************************/
void CAN_ConfigurePads(uint8_t nbModule){
	switch(nbModule){
		case 0 : 	SIUL_DigitalInput(SIUL_PB1,SIUL_IN_PB1, 0, SIUL_ALT2);
    				SIUL_DigitalOutput(SIUL_PB0,SIUL_ALT1); break; 
		
		case 1 :	SIUL_DigitalInput(SIUL_PA15,SIUL_IN_PA15, 0, SIUL_ALT1);
				SIUL_DigitalOutput(SIUL_PA14,SIUL_ALT1); break;
				
		case 2 :	SIUL_DigitalInput(SIUL_PF15,SIUL_IN_PF15, 0, SIUL_ALT1);
				SIUL_DigitalOutput(SIUL_PF14,SIUL_ALT2); break; 

	}
	
}

/***************************************************************************//*!
*   @brief The function CAN_Init initializes CANx registers.
*	@par Include 
*					CAN.h
* 	@par Description 
*					This function initializes specified CAN module with 
*					the following parameters: <br>	
*					 - Number of message buffers - 32. <br>
*					 - CAN bus speed - 1000 kBd (if a 40-MHz  is populated).
* 	@param[in] nbModule
*				Number of the CAN module (0 or 1).
*	@remarks Clock source from CAN module is configured to be derived directly 
*			 from the crystal resonator.
*	@par Code sample
*			CAN_Init(1);
*			- Function initializes CAN module number 1.
*
*	CanBaud = CANCLK/(PRESDIV+1)/(1+(PROPSEG+1)+(PSEG1+1)+(PSEG2+1))
*	if CANCLK=40MHz,
*	    CanBaud=1Mbps, when    PRESDIV=3,PROPSEG=4,PSEG1=1,PSEG2=1, RJW=1
*       CanBaud=500Kbps, when  PRESDIV=4,PROPSEG=4,PSEG1=4,PSEG2=4, RJW=3
********************************************************************************/
void CAN_Init(uint8_t nbModule)
{
    uint32_t i; 

    CAN_ConfigurePads(nbModule);

    //CLKSRC is 1 for PLL, MDIS still set after reset 
    CAN[nbModule]->CTRL1.B.CLKSRC = 1;

    //Ensure that FlexCan is in FREEZE 
    CAN[nbModule]->MCR.B.MDIS = 0;
    CAN[nbModule]->MCR.B.FRZ = 1;
    CAN[nbModule]->MCR.B.HALT = 1;

    for(i=0; i<2000; i++)
    {
        if (CAN[nbModule]->MCR.B.NOTRDY && CAN[nbModule]->MCR.B.FRZACK && !CAN[nbModule]->MCR.B.LPMACK)
            break;
    }

    //Configuration
    CAN[nbModule]->CTRL1.B.PRESDIV = 3;       // 40 MHz / (3+1) = 10 MHz
    CAN[nbModule]->CTRL1.B.RJW = 1;
    CAN[nbModule]->CTRL1.B.PSEG1 = 1;
    CAN[nbModule]->CTRL1.B.PSEG2 = 1;
    CAN[nbModule]->CTRL1.B.BOFFMSK = 0;
    CAN[nbModule]->CTRL1.B.ERRMSK = 0;
    CAN[nbModule]->CTRL1.B.CLKSRC = 1;        // read-only in freeze mode (value for read-back)
    CAN[nbModule]->CTRL1.B.LPB = 0;           // loopback mode disabled
    CAN[nbModule]->CTRL1.B.TWRNMSK = 0;
    CAN[nbModule]->CTRL1.B.RWRNMSK = 0;
    CAN[nbModule]->CTRL1.B.SMP = 0;
    CAN[nbModule]->CTRL1.B.BOFFREC = 0;
    CAN[nbModule]->CTRL1.B.TSYN = 0;
    CAN[nbModule]->CTRL1.B.LBUF = 0;
    CAN[nbModule]->CTRL1.B.LOM = 0;
    CAN[nbModule]->CTRL1.B.PROPSEG = 4;

    CAN[nbModule]->CTRL2.B.ECRWRE = 0;
    CAN[nbModule]->CTRL2.B.WRMFRZ = 1;        // allow SRAM access in freeze mode
    CAN[nbModule]->CTRL2.B.RFFN = 0;          // 8 Rx FIFO filters
    CAN[nbModule]->CTRL2.B.TASD = 16;
    CAN[nbModule]->CTRL2.B.MRP = 0;
    CAN[nbModule]->CTRL2.B.RRS = 0;
    CAN[nbModule]->CTRL2.B.EACEN = 0;

    CAN[nbModule]->MCR.B.MDIS = 0;
    CAN[nbModule]->MCR.B.FRZ = 1;
    CAN[nbModule]->MCR.B.RFEN = 0;            // RX FIFO not needed 
    CAN[nbModule]->MCR.B.HALT = 1;
    CAN[nbModule]->MCR.B.NOTRDY = 1;
    CAN[nbModule]->MCR.B.SOFTRST = 0;
    CAN[nbModule]->MCR.B.FRZACK = 1;
    CAN[nbModule]->MCR.B.SUPV = 1;
    CAN[nbModule]->MCR.B.WRNEN = 0;
    CAN[nbModule]->MCR.B.LPMACK = 0;
    CAN[nbModule]->MCR.B.SRXDIS = 1;   // SRXDIS =1, self reception disabled
    CAN[nbModule]->MCR.B.IRMQ = 0;
    CAN[nbModule]->MCR.B.LPRIOEN = 0;
    CAN[nbModule]->MCR.B.AEN = 0;
    CAN[nbModule]->MCR.B.IDAM = 0;
    CAN[nbModule]->MCR.B.MAXMB = (64 - 1);

    //Enable all IRQs 
    CAN[nbModule]->IMASK1.R = 0xFFFFFFFF;
    CAN[nbModule]->IMASK2.R = 0xFFFFFFFF;

    //Mem init 
    //Stay in the Freeze mode

    //Clear message buffers
    for(i = 0; i < 64; i++){
        CAN[nbModule]->MB[i].CS.R = 0;
        CAN[nbModule]->MB[i].ID.R = 0;
        CAN[nbModule]->MB[i].DATA.W[0] = 0;
        CAN[nbModule]->MB[i].DATA.W[1] = 0;
    }

    //Clear RX filters
    for(i= 0; i < 64; i++){
        CAN[nbModule]->RXIMR[i].R = 0;
    }

    //Clear internal buffers
    for(i=0; i<24; i++){
        CAN[nbModule]->RXIMR[i+128].R = 0;
    }

    //Disable RX FIFO message filter (accept all)
    CAN[nbModule]->RXMGMASK.R = 0;

    //Enable module 
    CAN[nbModule]->MCR.B.MDIS = 0;
    CAN[nbModule]->MCR.B.HALT = 0;

    CAN[nbModule]->MCR.R = 0x0000080F;   

	for(i=0; i<1000; i++){
        if (!CAN[nbModule]->MCR.B.NOTRDY && !CAN[nbModule]->MCR.B.FRZACK && !CAN[nbModule]->MCR.B.LPMACK)
            break;
    }

} 

/***************************************************************************//*!
*   @brief The function CAN_Send sends a frame via CAN bus.
*	@par Include 
*					CAN.h
* 	@par Description 
*				This function sends a CAN frame with the specified ID and 8-Byte 
*				message. Message can be sent using one of the 32 Message 
*				buffers.
* 	@param[in] nbModule
*					Number of the CAN module (0 or 1).
* 	@param[in] nbBuffer
*					Number of the CAN message buffer (from 0 till 31).
* 	@param[in] message
*					64-bit message to be sent through CAN bus. 
* 	@param[in] id
*					CAN message identifier - 32-bit number that contains 
*					standard (11 bits) and extended (18 bits) identifier. 
*					Local priority number is placed on the 3 most significant 
*					bits in the same register as the IDs. 
*	@remarks CAN module shall be initialized before (see CAN_Init function for 
*			 details).
*	@par Code sample
*			CAN_Send (0,31,0xA0A0A0A0A0A0A0A0, 0x15555555);
*			- Function sends message 0xA0A0A0A0A0A0A0A0 via CAN module 
*			number 0 using 31st message buffer with the following parameters:
*			Local priority:	0 / Standard ID: 0x555 / Extended ID: 0x15555
********************************************************************************/
void CAN_Send(uint8_t nbModule, uint8_t nbBuffer, uint64_t message, uint32_t id) {

	CAN[nbModule]->MB[nbBuffer].CS.R = 0x08680000;   //Length = 8 Bytes
	CAN[nbModule]->MB[nbBuffer].ID.R = id;  			//Load frame IDentifier
 
	CAN[nbModule]->MB[nbBuffer].DATA.W[0] = (uint32_t)(message >> 32);			//Byte0 - Byte3  of the message
	CAN[nbModule]->MB[nbBuffer].DATA.W[1] = (uint32_t)message;					//Byte4 - Byte7 of the message   
	CAN[nbModule]->MB[nbBuffer].CS.B.CODE = 0xc;  	//After transmission, the MB automatically becomes an Rx MB with the same ID.
}



void CAN_Receive(uint8_t nbModule,uint8_t nbBuffer,uint64_t* message, uint32_t* id) {

    uint32_t temp = 0;
    uint32_t CAN_ID =0;
    uint32_t CAN_length=0;
    uint32_t CAN_L=0;
    uint64_t CAN_H=0;

    /* subscribe FlexCAN_B's MB9 for Rx - extended frame format */
    //CAN_0.MB[nbBuffer].ID.R = 0x12340000; /* Ext.ID = 0x12340000 */
    //CAN_0.MB[nbBuffer].CS.R = 0x04200000; /* Rx active and empty + IDE */

	/* upon receiving the interrupt flag */


    /* mandatory - read control/status word - lock the MB */
	temp = CAN[nbModule]->MB[nbBuffer].CS.R;
	/* check the ID field */
	/* not really needed in this example */
	/* useful in case when multiple IDs are received
	 * by one message buffer (Rx mask feature) */
	if(CAN[nbModule]->MB[nbBuffer].CS.B.IDE == 0)
	{
		CAN_ID = CAN[nbModule]->MB[nbBuffer].ID.B.ID_STD;
	}
	else
	{
		CAN_ID = CAN[nbModule]->MB[nbBuffer].ID.R;
	}
	*id= CAN_ID;

	/* read the received data */
	CAN_length = CAN[nbModule]->MB[nbBuffer].CS.B.DLC; // data length code
	CAN_H = ((uint64_t)CAN[nbModule]->MB[nbBuffer].DATA.W[0])<<32;
	CAN_L = CAN[nbModule]->MB[nbBuffer].DATA.W[1];
	*message=CAN_H | CAN_L;
	//memcpy(rxdata_buf, &CAN_0.MB[9].DATA.B, 8);


	/* release the internal lock for all Rx MBs
	 * by reading the TIMER */
	temp = CAN[nbModule]->TIMER.R;

}

/***************************************************************************//*!
*   @brief The function CAN_Stop disables the CAN message buffer.
*	@par Include 
*					CAN.h
* 	@par Description 
*				This function clears last transmission flag in the IFLAG1 register 
*				and puts the specified message buffer into an Inactive mode.
* 	@param[in] nbModule
*					Number of the CAN module (0 or 1).
* 	@param[in] nbBuffer
*					Number of the CAN message buffer (from 0 till 31).
*	@remarks CAN module shall be initialized before using of this function 
*			(see CAN_Init function for details).
*	@par Code sample
*			CAN_Stop(0, 31);
*			- Function clears last transmission flag and puts message buffer 
*			number 31 of the CAN module number 0 into the Inactive state.
********************************************************************************/
void CAN_Stop(uint8_t nbModule, uint8_t nbBuffer) {

  	CAN[nbModule]->IFLAG1.R= (1 << nbBuffer);		//clear last transmission flag
	CAN[nbModule]->MB[nbBuffer].CS.B.CODE = 0;  	// put the message buffer into INACTIVE mode, so it

}

