/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************//*!
*
* @file     eTimer.h
*
* @author   r63172
* 
* @version  1.0.1.0
* 
* @date     Nov-15-2010
* 
* @brief    eTimer - eTimer for MPC5643L
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of MPC5643L eTimer
* peripheral module.
*
******************************************************************************/
#ifndef _ETIMER_H_
#define _ETIMER_H_



/******************************************************************************
* Global eTimer variables definition
******************************************************************************/


/******************************************************************************
* eTimer MACRO definitions
******************************************************************************/
#define NO_OPERATION                                            0x0
#define COUNT_RISING_EDGES_OF_PRIMARY_SRC                       0x1
#define COUNT_RISING_AND_FALLING_EDGES_OF_PRIMARY_SRC           0X2
#define COUNT_RISING_EDGES_OF_PRIMSRC_WHILE_SECSRC_HIGH         0X3
#define QUADRATURE_COUNT_MODE                                   0X4
#define COUNT_RISING_EDGES_OF_PRIMSRC_SECSRC_SPECIFIES_DIR      0X5
#define EDGE_OF_SECSRC_TRIG_PRIMARY_COUNT_TILL_CMP              0x6
#define CASCADED_COUNT_MODE                                     0x7

// primary, secondary count sources (note: IPBCLK can not be used as secsrc)
#define COUNTER_0_INPUT                                         0x0
#define COUNTER_1_INPUT                                         0x1
#define COUNTER_2_INPUT                                         0x2
#define COUNTER_3_INPUT                                         0x3
#define COUNTER_4_INPUT                                         0x4
#define COUNTER_5_INPUT                                         0x5
#define AUX_INPUT_0                                             0x8
#define AUX_INPUT_1                                             0x9
#define AUX_INPUT_2                                             0xa
#define COUNTER_0_OUTPUT                                        0x10
#define COUNTER_1_OUTPUT                                        0x11
#define COUNTER_2_OUTPUT                                        0x12
#define COUNTER_3_OUTPUT                                        0x13
#define COUNTER_4_OUTPUT                                        0x14
#define COUNTER_5_OUTPUT                                        0x15
#define IPBCLK_DIV_BY_1                                         0x18
#define IPBCLK_DIV_BY_2                                         0x19
#define IPBCLK_DIV_BY_4                                         0x1A
#define IPBCLK_DIV_BY_8                                         0x1B
#define IPBCLK_DIV_BY_16                                        0x1C
#define IPBCLK_DIV_BY_32                                        0x1D
#define IPBCLK_DIV_BY_64                                        0x1E
#define IPBCLK_DIV_BY_128                                       0x1F

// count duration, one shot or continuous
#define COUNT_UNTIL_COMPARE_AND_STOP                            0x1
#define COUNT_REPEATEDLY                                        0x0

// count lenght
#define COUNT_UNTIL_COMPARE_AND_REINITIALIZE                    0x1
#define COUNT_TO_ROLL_OVER                                      0x0

// count direction
#define COUNT_UP                                                0x0
#define COUNT_DOWN                                              0x1

// Output Enable OEN
#define OFLAG_DISABLE                                           0x0
#define OFLAG_ENABLE                                            0x1

// Redundant Channel RDNT
#define REDUNDANT_CHANNEL_CHECKING_DISABLE                      0x0
#define REDUNDANT_CHANNEL_CHECKING_ENABLE                       0x1

// Polarity selection
#define INVERTED_POLARITY                                       0x1
#define TRUE_POLARITY                                           0x0

// Master Mode MSTR
#define ENABLE_BROADCAST_OF_CMP_EVENTS                          0x1
#define DISABLE_BROADCAST_OF_CMP_EVENTS                         0x0

// Output Mode OUTMODE
#define SOFTWARE_CONTROLLED                                     0X0
#define CLEAR_ON_COMPARE                                        0x1
#define SET_ON_COMPARE                                          0x2
#define TOGGLE_ON_COMPARE                                       0x3
#define TOGGLE_USING_ALTERNATING_COMP_REGISTERS                 0x4
#define SET_ON_COMP1_COMPARE_CLEAR_ON_SECSRC_EDGE               0x5
#define SET_ON_COMP2_COMPARE_CLEAR_ON_SECSRC_EDGE               0x6
#define SET_ON_COMPARE_CLEAR_ON_ROLL_OVER                       0x7
#define SET_ON_COMP1_COMPARE_CLEAR_ON_COMP2_COMPARE             0x8
#define ASSERT_WHILE_CNTR_ACTIVE_CLEAR_WHEN_CNTR_STOPPED        0x9
#define ASSERT_WHEN_COUNTING_UP_CLEAR_WHEN_COUNTING_DOWN        0xa
#define ENABLE_GATED_CLOCK_OUTPUT_WHILE_CNTR_ACTIVE             0xf


/*
eTimer0 registers configuration
--------------------------------------
*/
#define eTimer0_COMP1_CH0              0x07FF /*2017*/
#define eTimer0_COMP2_CH0              0xF800
#define eTimer0_CTRL_CH0               0x8041
#define eTimer0_CTRL2_CH0              0x8003
#define eTimer0_CMPLD1_CH0             0x07FF
#define eTimer0_CMPLD2_CH0             0xF800
#define eTimer0_CCCTRL_CH0             0xDE00   //Capture 2:any edge,capture 1 : falling edge, one shot mode
                                                //channel compare and capture control register
#define eTimer0_ENBL                   0x0001   //enable channel 0


/*
eTimer1 registers configuration
--------------------------------------
*/

#define eTimer1_CTRL_CH4               0xD848
#define eTimer1_CTRL_CH5               0xD848
#define eTimer1_CTRL2_CH4              0x8083
#define eTimer1_CTRL2_CH5              0x8083
#define eTimer1_ENBL                   0x0031  //enable channel 0,1,2



/******************************************************************************
* eTimer registers bit definition
******************************************************************************/

/******************************************************************************
* Exported functions
*******************************************************************************/
extern void etimer0_init(void);
extern void etimer1_init(void);
extern void etimer2_init(void);

extern void eTimer1_vInit(void);
#endif /* _ETIMER_H_ */
