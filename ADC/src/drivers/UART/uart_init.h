/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   uart_init.h
*
* @brief  FreeMASTER driver private declarations, used internally by the driver
*
* @version 1.0.1.0
* 
* @date Nov-15-2010
* 
*******************************************************************************/
#ifndef _H_UART
#define _H_UART
//#include "MPC5744P_qs.h"

#include "../FreeMASTER/freemaster.h"
#include "../FreeMASTER/freemaster_MPC56xx.h"
// *****************************************************************************
extern void uart_init(void);
extern void uart_rx_isr();
extern void uart_tx_isr();
extern void transmit_test();

extern volatile struct LINFlexD_tag *linflex0;

// *****************************************************************************

#endif
