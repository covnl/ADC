/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\div_repeat_u32_sat.c
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
uint32_T div_repeat_u32_sat(uint32_T numerator, uint32_T denominator, uint16_T
 nRepeatSub)
{
  uint32_T quotient;
  uint16_T iRepeatSub;
  uint8_T numeratorExtraBit;
  uint32_T tempQuotient;
  uint8_T overflow;
  if(denominator == 0) {
    quotient = MAX_uint32_T;
    /* divide by zero handler */
  } else {
    overflow = 0U;
    tempQuotient = numerator / denominator;
    numerator %= denominator;
    for(iRepeatSub = 0; iRepeatSub < nRepeatSub; iRepeatSub++) {
      numeratorExtraBit = (numerator >= 2147483648UL);
      numerator <<= 1;
      overflow = ((overflow) || (tempQuotient >= 2147483648UL));
      tempQuotient <<= 1;
      if((numeratorExtraBit) || (numerator >= denominator)) {
        tempQuotient++;
        numerator = numerator - denominator;
      }
    }
    if(overflow) {
      quotient = MAX_uint32_T;
    } else {
      quotient = tempQuotient;
    }
  }
  return quotient;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
