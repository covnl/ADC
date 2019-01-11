/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\div_u32.c
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Thu Feb 12 21:48:01 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Thu Feb 12 21:48:03 2015
 */

#include "rtwtypes.h"

#include "rtw_shared_utils.h"
uint32_T div_u32(uint32_T numerator, uint32_T denominator)
{
  uint32_T quotient;
  if(denominator == 0) {
    quotient = MAX_uint32_T;
    /* divide by zero handler */
  } else {
    quotient = (uint32_T)(numerator / denominator);
  }
  return quotient;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
