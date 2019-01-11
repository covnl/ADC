/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\TuneParamCast_S16_U8_SL8_SAT.c
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

/*********************************************************************
 * Tunable Parameter Data Type and Scaling Conversion Utility
 *   TuneParamCast_S16_U8_SL8_SAT
 *
 * This utility was generated because a tunable parameter was
 * declared using one data type and scaling, but a user of that 
 * parameter (typically a block) requires the parameter's value to 
 * be represented using a different data type and scaling.
 * This usage must be in the form of an expression.  In order to
 * provide an expression, the statements required for the conversion
 * have been wrapped in this function.  
 */
int16_T TuneParamCast_S16_U8_SL8_SAT(uint8_T B)
{
  int16_T C;

  {
    uint8_T rtb_u8_tmp;
    int16_T rtb_s16_tmp;
    rtb_u8_tmp = B;
    if(rtb_u8_tmp > 127U) {
      rtb_s16_tmp = MAX_int16_T;
    } else {
      rtb_s16_tmp = (rtb_u8_tmp << 8);
    }
    C = rtb_s16_tmp;
  }
  return (C);
}

/* end TuneParamCast_S16_U8_SL8_SAT
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
