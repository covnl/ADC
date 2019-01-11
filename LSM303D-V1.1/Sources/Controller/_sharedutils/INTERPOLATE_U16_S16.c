/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\INTERPOLATE_U16_S16.c
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
 * Fixed Point Interpolation INTERPOLATE_U16_S16
 */
void INTERPOLATE_U16_S16( uint16_T *pY, uint16_T yL, uint16_T yR, int16_T x,
 int16_T xL, int16_T xR)
{
  int32_T bigProd;
  uint16_T yDiff;
  int16_T xNum;
  int16_T xDen;

  *pY = yL;

  /* If x is not strictly between xR and xL
   * then an interpolation calculation is not necessary x == xL
   * or not valid.  The invalid situation is expected when the input
   * is beyond the left or right end of the table.  The design is
   * that yL holds the correct value for *pY
   * in invalid situations.
   */
  if ( (xR > xL) && (x > xL) )
  {
    xDen = xR;
    xDen = xDen - xL;

    xNum = x;
    xNum = xNum - xL;

    if ( yR >= yL )
    {
      yDiff = yR;
      yDiff = yDiff - yL;
    }
    else
    {
      yDiff = yL;
      yDiff = yDiff - yR;
    }

    bigProd = (int32_T)yDiff * (int32_T)xNum;

    yDiff = (uint16_T)div_s32_floor(bigProd, (int32_T)xDen);

    if ( yR >= yL )
    {
      *pY = *pY + yDiff;
    }
    else
    {
      *pY = *pY - yDiff;
    }
  }
}

/* end INTERPOLATE_U16_S16 
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
