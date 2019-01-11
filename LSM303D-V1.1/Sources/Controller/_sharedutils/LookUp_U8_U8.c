/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\LookUp_U8_U8.c
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
 * Fixed-Point Lookup Utility LookUp_U8_U8
 */
void LookUp_U8_U8( uint8_T *pY, const uint8_T *pYData, uint8_T u, const uint8_T
 *pUData, uint_T iHi)
{
  uint_T iLeft;
  uint_T iRght;
  BINARYSEARCH_U8( &(iLeft), &(iRght), u, pUData, iHi);
  INTERPOLATE_U8_U8( pY, pYData[iLeft], pYData[iRght], u, pUData[iLeft],
   pUData[iRght]);
}

/* end function LookUp_U8_U8
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
