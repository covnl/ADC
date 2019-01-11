/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\mul_wide_s32.c
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
void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
 *ptrOutBitsLo)
{
  uint32_T outBitsHi;
  uint32_T outBitsLo;
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Lo;
  uint32_T in0Hi;
  uint32_T in1Hi;
  uint32_T productLoHi;
  uint32_T carry;
  absIn0 = (uint32_T)(in0 < 0 ? -in0 : in0);
  absIn1 = (uint32_T)(in1 < 0 ? -in1 : in1);
  in0Hi = (absIn0 >> 16);
  in0Lo = absIn0 & 65535UL;
  in1Hi = (absIn1 >> 16);
  absIn0 = absIn1 & 65535UL;
  absIn1 = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 = in0Lo * absIn0;
  carry = 0;
  outBitsLo = absIn0 + (productLoHi << 16);
  if(outBitsLo < absIn0) {
    carry++;
  }
  absIn0 = outBitsLo;
  outBitsLo = outBitsLo + (absIn1 << 16);
  if(outBitsLo < absIn0) {
    carry++;
  }
  outBitsHi = ((carry + (in0Hi * in1Hi)) + (productLoHi >> 16)) + (absIn1 >> 16);
  if(!((in0 == 0) || (in1 == 0) || ((in0 > 0) == (in1 > 0)))) {
    outBitsHi = ~outBitsHi;
    outBitsLo = ~outBitsLo;
    outBitsLo++;
    if(outBitsLo == 0) {
      outBitsHi++;
    }
  }
  *ptrOutBitsHi = outBitsHi;
  *ptrOutBitsLo = outBitsLo;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
