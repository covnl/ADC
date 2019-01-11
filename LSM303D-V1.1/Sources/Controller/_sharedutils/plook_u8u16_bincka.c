/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\plook_u8u16_bincka.c
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
uint8_T plook_u8u16_bincka(uint16_T u, const uint16_T *const bp, uint32_T
 maxIndex)
{
  uint8_T bpIndex;
  /* Prelookup Index
     Search method: 'binary'
     Process out of range input: 'Clip to range'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
   */
  if(u < bp[0UL]) {
    bpIndex = 0U;
  } else if(u < bp[maxIndex]) {
    bpIndex = binsearch_u8u16(u, bp, (maxIndex + 1UL) >> 1UL, maxIndex);
  } else {
    bpIndex = (uint8_T)maxIndex;
  }
  return bpIndex;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
