/*
 * uart_irq.c
 *
 *  Created on: Apr 8, 2016
 *      Author: B33124
 */

#include "derivative.h"
#include "uart.h"
#include "uart_irq.h"


void vfnUart1RxIsr(void)
{
	vfnLINFlexUartIsrHandler(&LINFlexD_1, &stUart1RxInfo);
}

void vfnLINFlexUartIsrHandler(volatile struct LINFlexD_tag *pLin, UART_RECEIVE_INFO_Tag *pRxInfo)
{
	if(pLin->UARTSR.B.DRFRFE == 1)
	{
		if(pRxInfo->nStatus == 0)		//Rx Buffer is ready to save data
		{
			if(pRxInfo->nRxCnt < pRxInfo->nRxSize)		//not received max bytes of data
			{
				pRxInfo->pRxBuf[pRxInfo->nRxCnt] = pLin->BDRM.B.DATA4;
				pRxInfo->nRxCnt++;
			}

			if(pRxInfo->nRxCnt == (pRxInfo->nRxSize))	//if the last byte received
			{
				pRxInfo->nStatus = 1;	//reception completed, Rx Buffer is full of data
				pRxInfo->nRxCnt = 0;		//reset the byte count
			}
		}
	}
	pLin->UARTSR.R = 0x0004;	//clear DRFRFE flag
}
