/*******************************************************************************
* Freescale Semiconductor Inc.
* (c) Copyright 2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by FREESCALE in this matter are performed AS IS and without
any warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. FREESCALE neither guarantees nor will be
held liable by CUSTOMER for the success of this project.
FREESCALE DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED 
TO THE PROJECT BY FREESCALE, AND OR NAY PRODUCT RESULTING FROM FREESCALE 
SERVICES. IN NO EVENT SHALL FREESCALE BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL 
DAMAGES ARISING OUT OF THIS AGREEMENT.
CUSTOMER agrees to hold FREESCALE harmless against any and all claims demands 
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result 
of the advise or assistance supplied CUSTOMER in connection with product, 
services or goods supplied under this Agreement.
********************************************************************************
* File:             uart.c
* Owner:            PetrS
* Version:          1.0
* Date:             Mar-20-2015
* Classification:   General Business Information
* Brief:            terminal IO. 
********************************************************************************
* Detailed Description: 
* 
* Implements GHS ind_io library function calls to do printf() on LINFlexD0
* Functions "read" and "write" defined in this module replace the ones from the
* library so finally we send printf() to LINFlexD0
*
* ------------------------------------------------------------------------------
* Test HW:  
* Target :  
* Terminal: 
* Fsys:     200MHz
*
********************************************************************************
Revision History:
1.0     Mar-20-2015     PetrS  Initial Version
*******************************************************************************/
/****************************************************************************************
 * Need add following line into "Project Settings => Linker => Miscellaneous" to enable printf()
 * -Xlinker --undefined=__pformatterFP -Xlinker --defsym=__pformatter=__pformatterFP
 ****************************************************************************************/
#include "derivative.h"
#include "uart.h"

/*******************************************************************************
* Global variables
*******************************************************************************/
uint8_t u8Uart0RxBuf[UART0_RX_BUF_SIZE];
UART_RECEIVE_INFO_Tag stUart0RxInfo = {
		u8Uart0RxBuf,
		UART0_RX_BUF_SIZE,
		0,
		0
};

uint8_t u8Uart1RxBuf[UART1_RX_BUF_SIZE];
UART_RECEIVE_INFO_Tag stUart1RxInfo = {
		u8Uart1RxBuf,
		UART1_RX_BUF_SIZE,
		0,
		0
};

/*******************************************************************************
* Constants and macros
*******************************************************************************/

/*******************************************************************************
* Local types
*******************************************************************************/

/*******************************************************************************
* Local function prototypes
*******************************************************************************/

/*******************************************************************************
* Local variables
*******************************************************************************/

/*******************************************************************************
* Local functions
*******************************************************************************/ 

/*******************************************************************************
* Global functions
*******************************************************************************/ 

/*
Methods called by EWL libraries to perform console IO:
*/

UARTError InitializeUART(UARTBaudRate baudRate)
{
#pragma unused(baudRate)
	//LINFlexD_1_Init ();
	vfnUartInit(&LINFlexD_1, 115200);
	return kUARTNoError;
}

UARTError ReadUARTN(void* bytes, unsigned long limit)
{
	int count;
	UARTError err;

	for (count = 0, err = kUARTNoError;	count < limit && err == kUARTNoError; count++)
	{
		//err = ReceiveData( (char *)bytes + count );
		err = vfnUartReceiveByte(&LINFlexD_1, bytes + count);
	}

	return err;
}


UARTError WriteUARTN(const void * bytes, unsigned long length)
{
	//TransmitData ((const char * const)bytes,length);
	vfnUartTransmit(&LINFlexD_1, (uint8_t *)bytes, length);
  	return kUARTNoError;
}

UARTError ReadUARTPoll(char* c)
{
    int32_t rx_data;

    rx_data = LINFlexD_1.BDRM.R; // read whole register due to erratum e4897PS

    if (LINFlexD_1.UARTSR.B.RMB == 0)
        return  kUARTNoData;  // return no data
    else
    {
    	LINFlexD_1.UARTSR.R = 0x0204;
        *c =(unsigned char) rx_data; // read byte of Data
        return kUARTNoError;  // return no error
    }
}


int write (int fno, const void *buf, int size)
{ 
	//TransmitData ((const char *)buf,size);
	vfnUartTransmit(&LINFlexD_1, (uint8_t *)buf, size);
  	return size; 
}

int read (int fno, void *buf, int size)
{
	int count;

	for (count = 0; count < size; count++)
    {
	    //ReceiveData( (char *)buf + count );
		vfnUartReceiveByte(&LINFlexD_1, (uint8_t *)buf + count);
    }

	return size;
}

uint32_t vfnUartInit(volatile struct LINFlexD_tag *pLin, UARTBaudRate nBaudrate)
{
	/* enter INIT mode */
	pLin->LINCR1.R = 0x0081; /* SLEEP=0, INIT=1 */

	/* wait for the INIT mode */
	while (0x1000 != (pLin->LINSR.R & 0xF000)) {}

	/* configure for UART mode */
	//pLin->UARTCR.R = 0x0001; /* set the UART bit first to be able to write the other bits */

	pLin->UARTCR.R = 0x0001;	// set the UART bit first to be able to write the other bits, it's a must on MPC57xx but not on MPC56
	pLin->UARTCR.R = 0x0033;
	//pLin->UARTCR.R = 0x003B; /* 8bit data, no parity, Tx and Rx enabled, UART mode */
								 /* Transmit buffer size = 1 (TDFL = 0 */
								 /* Receive buffer size = 1 (RDFL = 0) */

//#if LIN_CLK_64MHZ
#if 1
	pLin->LINIBRR.R = (uint16_t)(LIN_CLK_FREQ/16/((uint32_t)nBaudrate));	//pLin->LINIBRR.R = (uint16_t)(64000000/16/((uint32_t)nBaudrate));
	pLin->LINFBRR.R = (uint16_t)((LIN_CLK_FREQ/((uint32_t)nBaudrate))%16);	//pLin->LINFBRR.R = (uint16_t)((64000000/((uint32_t)nBaudrate))%16);
#elif LIN_CLK_100MHZ
	//pLin->LINFBRR.R = 2;
	//pLin->LINIBRR.R = 65;
	pLin->LINIBRR.R = 100000000/16/nBaudrate;
	pLin->LINFBRR.R = (100000000/nBaudrate)%16;
#else
#error "LIN_CLK not defined"
#endif

	pLin->UARTSR.R = 0xFFFFFFFFU;
	pLin->LINIER.B.DRIE = 1;			//data reception interrupt enable
	/* enter NORMAL mode */
	pLin->LINCR1.R = 0x0080; /* INIT=0 */

	return kUARTNoError;
}

uint32_t vfnUartTransmit(volatile struct LINFlexD_tag *pLin, uint8_t *pBuf, uint32_t cnt)
{
    uint32_t	j = 0; // Dummy variable

    for (j=0; j< cnt; j++)
    {  // Loop for character string
    	pLin->BDRL.B.DATA0 = *(pBuf+j);
   	      //write character to transmit buffer
	    while (1 != pLin->UARTSR.B.DTFTFF) {}//while (1 != LINFLEX_0.UARTSR.B.DTFTFF) {}
	      // Wait for data transmission completed flag
	    pLin->UARTSR.R = 0x0002;
	      // clear the DTF flag and not the other flags
    }
    return cnt;
}

/* receive on byte date from Rx Buffer */
uint32_t vfnUartReceiveByte(volatile struct LINFlexD_tag *pLin, uint8_t *pBuf)
{

    uint32_t rx_data;

    	/* wait for DRF */
	while (1 != pLin->UARTSR.B.DRFRFE) {} //while (1 != LINFLEX_0.UARTSR.B.DRFRFE) {}  /* Wait for data reception completed flag */

	/* wait for RMB */
	while (1 != pLin->UARTSR.B.RMB) {}  /* Wait for Release Message Buffer */

	/* get the data */

	rx_data = pLin->BDRM.R; // read whole register due to erratum e4897PS

	*pBuf = (uint8_t)rx_data; // take

	/* clear the DRF and RMB flags by writing 1 to them */
	pLin->UARTSR.R = 0x0204;
	return kUARTNoError;
}
