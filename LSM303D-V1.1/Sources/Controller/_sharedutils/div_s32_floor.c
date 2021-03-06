/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\div_s32_floor.c
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
int32_T div_s32_floor(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T absNumerator;
  uint32_T absDenominator;
  uint32_T tempAbsQuotient;
  uint16_T quotientNeedsNegation;
  if(denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;
    /* divide by zero handler */
  } else {
    absNumerator = (uint32_T)(numerator >= 0 ? numerator : -numerator);
    absDenominator = (uint32_T)(denominator >= 0 ? denominator : -denominator);
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = (uint32_T)(absNumerator / absDenominator);
    if(quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if(absNumerator > 0) {
        tempAbsQuotient++;
      }
    }
   quotient = quotientNeedsNegation ? (int32_T)-(int32_T)tempAbsQuotient :
      (int32_T)tempAbsQuotient;
  }
  return quotient;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
