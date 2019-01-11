/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\mul_u32_u32_u32_sr6_sat.c
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Sun Mar 08 15:37:25 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Sun Mar 08 15:37:28 2015
 */

#include "rtwtypes.h"

#include "rtw_shared_utils.h"
uint32_T mul_u32_u32_u32_sr6_sat(uint32_T a, uint32_T b)
{
  uint32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_u32(a, b, &u32_chi, &u32_clo);
  u32_clo = (u32_chi << 26) | (u32_clo >> 6);
  u32_chi = (u32_chi >> 6);
  if(u32_chi) {
    result = MAX_uint32_T;
  } else {
    result = u32_clo;
  }
  return result;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
