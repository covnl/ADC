/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\div_s16_floor.c
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
int16_T div_s16_floor(int16_T numerator, int16_T denominator)
{
  int16_T quotient;
  uint16_T absNumerator;
  uint16_T absDenominator;
  uint16_T tempAbsQuotient;
  uint16_T quotientNeedsNegation;
  if(denominator == 0) {
    quotient = numerator >= 0 ? MAX_int16_T : MIN_int16_T;
    /* divide by zero handler */
  } else {
    absNumerator = (uint16_T)(numerator >= 0 ? numerator : -numerator);
    absDenominator = (uint16_T)(denominator >= 0 ? denominator : -denominator);
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = (uint16_T)(absNumerator / absDenominator);
    if(quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if(absNumerator > 0) {
        tempAbsQuotient++;
      }
    }
   quotient = quotientNeedsNegation ? (int16_T)-(int16_T)tempAbsQuotient :
      (int16_T)tempAbsQuotient;
  }
  return quotient;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
