/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\binsearch_u8u8.c
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
uint8_T binsearch_u8u8(uint8_T u, const uint8_T *const bp, uint32_T startIndex,
 uint32_T maxIndex)
{
  uint8_T bpIndex;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;
  /* Binary Search */
  bpIdx = startIndex;
  iLeft = 0UL;
  iRght = maxIndex;
  while((iRght - iLeft) > 1UL) {
    if(u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      iLeft = bpIdx;
    }
    bpIdx = ((iRght + iLeft) >> 1UL);
  }
  bpIndex = (uint8_T)iLeft;
  return bpIndex;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
