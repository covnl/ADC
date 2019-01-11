/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\div_u16_SR.c
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
uint16_T div_u16_SR(uint16_T numerator, uint16_T denominator, uint16_T
 nShiftRight)
{
  uint16_T quotient;
  if(denominator == 0) {
    quotient = MAX_uint16_T;
    /* divide by zero handler */
  } else {
   quotient = (uint16_T)(nShiftRight >= 16U ? (uint16_T)0 :
      (uint16_T)(numerator / denominator) >> nShiftRight);
  }
  return quotient;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
