/*
 * uart_irq.h
 *
 *  Created on: Apr 8, 2016
 *      Author: B33124
 */

#ifndef UART_IRQ_H_
#define UART_IRQ_H_

void vfnUart2RxIsr(void);
void vfnLINFlexUartIsrHandler(volatile struct LINFlexD_tag *pLin, UART_RECEIVE_INFO_Tag *pRxInfo);


#endif /* UART_IRQ_H_ */
