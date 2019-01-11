/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\intrp1d_u16u8u16n15_lca_f.c
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
uint16_T intrp1d_u16u8u16n15_lca_f(uint8_T bpIndex, uint16_T frac, const
 uint16_T *const table, uint32_T maxIndex)
{
  uint16_T y;
  uint32_T offset_0d;
  uint16_T yL_0d0;
  uint16_T yR_0d0;
  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'floor'
   */
  offset_0d = (uint32_T)bpIndex;
  if((uint32_T)bpIndex == maxIndex) {
    y = table[offset_0d];
  } else {
    yR_0d0 = table[offset_0d + 1UL];
    yL_0d0 = table[offset_0d];
    if(yR_0d0 >= yL_0d0) {
      y = yL_0d0 + (uint16_T)(((uint32_T)frac * (uint32_T)(yR_0d0 - yL_0d0)) >>
        15);
    } else {
      y = yL_0d0 - (uint16_T)(((uint32_T)frac * (uint32_T)(yL_0d0 - yR_0d0)) >>
        15);
    }
  }
  return y;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
