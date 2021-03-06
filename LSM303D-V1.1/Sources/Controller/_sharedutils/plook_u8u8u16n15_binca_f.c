/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\plook_u8u8u16n15_binca_f.c
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
uint8_T plook_u8u8u16n15_binca_f(uint8_T u, const uint8_T *const bp, uint32_T
 maxIndex, uint16_T *fraction)
{
  uint8_T bpIndex;
  uint8_T bpLeftCast;
  uint32_T u1;
  /* Prelookup Index and Fraction
     Search method: 'binary'
     Process out of range input: 'Clip to range'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'floor'
   */
  if(u < bp[0UL]) {
    bpIndex = 0U;
    *fraction = 0U;
  } else if(u < bp[maxIndex]) {
    bpIndex = binsearch_u8u8(u, bp, (maxIndex + 1UL) >> 1UL, maxIndex);
    bpLeftCast = bp[(uint32_T)bpIndex];
    u1 = (uint32_T)(uint8_T)((uint16_T)bp[(uint32_T)bpIndex + 1UL] -
      (uint16_T)bpLeftCast);
   *fraction = (uint16_T)(u1 == 0 ? MAX_uint32_T :
      (uint32_T)(((uint32_T)(uint8_T)((uint16_T)u - (uint16_T)bpLeftCast) <<
      15U) / u1));
  } else {
    bpIndex = (uint8_T)maxIndex;
    *fraction = 0U;
  }
  return bpIndex;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
