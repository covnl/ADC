/*
 * PIT_IRQ.h
 *
 *  Created on: Jul 27, 2016
 *      Author: B55903
 */

#ifndef DRIVERS_PIT_PIT_IRQ_H_
#define DRIVERS_PIT_PIT_IRQ_H_

void ISR226_PIT_CH0(void);
void ISR36_STM0_CH0(void);
extern uint32_t u32Stm0Ch0PeriodTicks;
#endif /* DRIVERS_PIT_PIT_IRQ_H_ */
