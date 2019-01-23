/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   uart_init.c
*
* @brief  FreeMASTER driver private declarations, used internally by the driver
*
* @version 1.0.1.0
* 
* @date Nov-15-2010
* 
*******************************************************************************/
#include "uart_init.h"
#include "Defines.h"

volatile struct LINFlexD_tag *linflex1;

void uart_init(void)
{
    linflex1 = &LINFlexD_1;



    // configure linflex1
    linflex1->LINCR1.B.SLEEP = 0x0;     // disable sleep mode
    linflex1->LINCR1.B.INIT  = 0x1;     // init mode
    linflex1->UARTCR.B.UART  = 0x1;     // UART mode
    

    linflex1->UARTCR.B.TDFL_TFC	= 0x0;      // bufer size = 1
    linflex1->UARTCR.B.RDFL_RFC	= 0x0;      // bufer size = 1
    linflex1->UARTCR.B.RxEn		= 0x1;      // reciever enable
    linflex1->UARTCR.B.TxEn		= 0x1;      // transmiter enable
    linflex1->UARTCR.B.PC0		= 0x1;      // parity is even
    linflex1->UARTCR.B.PCE		= 0x0;      // parity control disable
    linflex1->UARTCR.B.WL0		= 0x1;      // word length 8-bit data + parity bit


    linflex1->LINIBRR.B.IBR     =54;
	linflex1->LINFBRR.B.FBR     =4;

	// configure interupts - enable
    // or disable
    linflex1->LINIER.B.DRIE			= 0x0;     // data reception complete interrupt
    linflex1->LINIER.B.DTIE			= 0x0;     // data transmition complete interrupt
    linflex1->LINIER.B.DBFIE		= 0x0;     //
    linflex1->LINIER.B.DBEIETOIE	= 0x0;     //
    
    linflex1->LINCR1.B.INIT			= 0x0;      // normal mode
}

// for testing purpose
void uart_rx_isr()
{ 
	FMSTR_SCI_RDCLRSR(); 
	FMSTR_SCI_PUTCHAR(FMSTR_SCI_GETCHAR()); // output - input
}

void uart_tx_isr()
{ 
	FMSTR_SCI_RDCLRSR();  
	linflex1->UARTSR.B.DTFTFF		= 0x1;
}	    

// *****************************************************************************
