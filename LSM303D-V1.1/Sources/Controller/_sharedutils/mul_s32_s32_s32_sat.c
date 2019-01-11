/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\mul_s32_s32_s32_sat.c
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Wed May 06 15:39:18 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Wed May 06 15:39:20 2015
 */

#include "rtwtypes.h"

#include "rtw_shared_utils.h"
int32_T mul_s32_s32_s32_sat(int32_T a, int32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  if(((int32_T)u32_chi > 0) || ((u32_chi == 0) && (u32_clo >= 2147483648UL))) {
    result = MAX_int32_T;
  } else if(((int32_T)u32_chi < -1L) || (((int32_T)u32_chi == -1L) && (u32_clo <
     2147483648UL))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }
  return result;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
