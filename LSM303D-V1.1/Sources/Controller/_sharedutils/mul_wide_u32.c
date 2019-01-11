/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\mul_wide_u32.c
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
void mul_wide_u32(uint32_T in0, uint32_T in2, uint32_T *ptrOutBitsHi, uint32_T
 *ptrOutBitsLo)
{
  uint32_T outBitsHi;
  uint32_T in0Hi;
  uint32_T in1Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  uint32_T carry;
  in0Hi = (in0 >> 16);
  outBitsHi = in0 & 65535UL;
  in1Hi = (in2 >> 16);
  in1Lo = in2 & 65535UL;
  productHiLo = in0Hi * in1Lo;
  productLoHi = outBitsHi * in1Hi;
  outBitsHi = outBitsHi * in1Lo;
  carry = 0;
  in1Lo = outBitsHi + (productLoHi << 16);
  if(in1Lo < outBitsHi) {
    carry++;
  }
  outBitsHi = in1Lo;
  in1Lo = in1Lo + (productHiLo << 16);
  if(in1Lo < outBitsHi) {
    carry++;
  }
  outBitsHi = ((carry + (in0Hi * in1Hi)) + (productLoHi >> 16)) + (productHiLo
    >> 16);
  *ptrOutBitsHi = outBitsHi;
  *ptrOutBitsLo = in1Lo;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
