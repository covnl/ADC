/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#include <MPC5744P.h>



#define ENTER_CRITICAL()	__asm__(" wrteei 0");
#define EXIT_CRITICAL()		__asm__(" wrteei 1");


#define DISABLE_IRQ()               asm("wrteei 0")
#define ENABLE_IRQ()                asm("wrteei 1")


#define LIN_CLK_FREQ 100000000


