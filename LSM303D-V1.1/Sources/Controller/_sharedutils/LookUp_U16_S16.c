/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\LookUp_U16_S16.c
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
 * Fixed-Point Lookup Utility LookUp_U16_S16
 */
void LookUp_U16_S16( uint16_T *pY, const uint16_T *pYData, int16_T u, const
 int16_T *pUData, uint_T iHi)
{
  uint_T iLeft;
  uint_T iRght;
  BINARYSEARCH_S16( &(iLeft), &(iRght), u, pUData, iHi);
  INTERPOLATE_U16_S16( pY, pYData[iLeft], pYData[iRght], u, pUData[iLeft],
   pUData[iRght]);
}

/* end function LookUp_U16_S16
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
