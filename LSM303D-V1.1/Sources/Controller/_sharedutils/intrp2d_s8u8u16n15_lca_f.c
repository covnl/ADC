/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\intrp2d_s8u8u16n15_lca_f.c
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
int8_T intrp2d_s8u8u16n15_lca_f(const uint8_T *const bpIndex, const uint16_T
 *const frac, const int8_T *const table, uint32_T stride, const uint32_T *const
 maxIndex)
{
  int8_T y;
  int8_T yL_1d;
  int8_T yR_1d;
  int8_T yR_0d0;
  uint32_T offset_0d;
  /* Interpolation 2-D
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'floor'
   */
  offset_0d = ((uint32_T)bpIndex[1UL] * stride) + (uint32_T)bpIndex[0UL];
  if((uint32_T)bpIndex[0UL] == maxIndex[0UL]) {
    yL_1d = table[offset_0d];
  } else {
    yR_0d0 = table[offset_0d + 1UL];
    yR_1d = table[offset_0d];
    if(yR_0d0 >= yR_1d) {
      yL_1d = (int8_T)((int16_T)yR_1d + (int16_T)(uint8_T)(((uint32_T)frac[0UL]
        * (uint32_T)(uint8_T)((uint16_T)yR_0d0 - (uint16_T)yR_1d)) >> 15));
    } else {
      yL_1d = (int8_T)((int16_T)yR_1d - (int16_T)(uint8_T)(((uint32_T)frac[0UL]
        * (uint32_T)(uint8_T)((uint16_T)yR_1d - (uint16_T)yR_0d0)) >> 15));
    }
  }
  if((uint32_T)bpIndex[1UL] == maxIndex[1UL]) {
    y = yL_1d;
  } else {
    offset_0d = offset_0d + stride;
    if((uint32_T)bpIndex[0UL] == maxIndex[0UL]) {
      yR_1d = table[offset_0d];
    } else {
      yR_0d0 = table[offset_0d + 1UL];
      yR_1d = table[offset_0d];
      if(yR_0d0 >= yR_1d) {
        yR_1d = (int8_T)((int16_T)yR_1d +
          (int16_T)(uint8_T)(((uint32_T)frac[0UL] *
          (uint32_T)(uint8_T)((uint16_T)yR_0d0 - (uint16_T)yR_1d)) >> 15));
      } else {
        yR_1d = (int8_T)((int16_T)yR_1d -
          (int16_T)(uint8_T)(((uint32_T)frac[0UL] *
          (uint32_T)(uint8_T)((uint16_T)yR_1d - (uint16_T)yR_0d0)) >> 15));
      }
    }
    if(yR_1d >= yL_1d) {
      y = (int8_T)((int16_T)yL_1d + (int16_T)(uint8_T)(((uint32_T)frac[1UL] *
        (uint32_T)(uint8_T)((uint16_T)yR_1d - (uint16_T)yL_1d)) >> 15));
    } else {
      y = (int8_T)((int16_T)yL_1d - (int16_T)(uint8_T)(((uint32_T)frac[1UL] *
        (uint32_T)(uint8_T)((uint16_T)yL_1d - (uint16_T)yR_1d)) >> 15));
    }
  }
  return y;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
