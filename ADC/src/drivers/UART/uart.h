/* EWL
 * Copyright 1995-2009 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2012/06/01 15:44:21 $
 * $Revision: 1.1 $
 */

#ifndef UART_H
#define UART_H

#include "derivative.h"
#include <stdio.h>
#include <stdlib.h>


#if !_EWL_CONSOLE_SUPPORT
#error _EWL_CONSOLE_SUPPORT must not be defined to 1.
#endif

//typedef int UARTError;
typedef uint32_t UARTError;

enum {
	kUARTNoError = 0,
	kUARTUnknownBaudRate,
	kUARTConfigurationError,
	kUARTBufferOverflow,				/* specified buffer was too small */
	kUARTNoData							/* no data available from polling */
};

typedef enum {
	kBaudHWSet = -1,					/* use HW settings such as DIP switches */
	kBaud300 = 300,						/* valid baud rates */
	kBaud600 = 600,
	kBaud1200 = 1200,
	kBaud1800 = 1800,
	kBaud2000 = 2000,
	kBaud2400 = 2400,
	kBaud3600 = 3600,
	kBaud4800 = 4800,
	kBaud7200 = 7200,
	kBaud9600 = 9600,
	kBaud19200 = 19200,
	kBaud38400 = 38400,
	kBaud57600 = 57600,
	kBaud115200 = 115200,
	kBaud230400 = 230400
} UARTBaudRate;

typedef struct UART_RECEIVE_INFO_Struct_Tag
{
	uint8_t *pRxBuf;
	uint32_t nRxSize;
	uint32_t nRxCnt;
	uint32_t nStatus;
}UART_RECEIVE_INFO_Tag;

#define UART0_RX_BUF_SIZE		16
#define UART1_RX_BUF_SIZE		16

extern uint8_t u8Uart0RxBuf[UART0_RX_BUF_SIZE];
extern uint8_t u8Uart1RxBuf[UART1_RX_BUF_SIZE];
extern UART_RECEIVE_INFO_Tag stUart0RxInfo;
extern UART_RECEIVE_INFO_Tag stUart1RxInfo;

UARTError InitializeUART(UARTBaudRate baudRate);
UARTError TerminateUART(void);
void TransmitData(const char *pBuf, uint32_t cnt);

UARTError ReadUARTPoll(char* c);

UARTError ReadUART1(char* c);
UARTError ReadUARTN(void* bytes, unsigned long length);
UARTError ReadUARTString(char* string, unsigned long limit, char terminateChar);

UARTError WriteUART1(char c);
UARTError WriteUARTN(const void* bytes, unsigned long length);
UARTError WriteUARTString(const char* string);

uint32_t vfnUartInit(volatile struct LINFlexD_tag *pLin, UARTBaudRate nBaudrate);
uint32_t vfnUartTransmit(volatile struct LINFlexD_tag *pLin, uint8_t *pBuf, uint32_t cnt);
uint32_t vfnUartReceiveByte(volatile struct LINFlexD_tag *pLin, uint8_t *pBuf);

extern int _EWL_CDECL printf_console(const char * format, ...);
extern UARTError __init_uart_console(void);

#endif /* UART_H */
