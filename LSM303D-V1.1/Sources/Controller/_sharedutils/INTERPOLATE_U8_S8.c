/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\INTERPOLATE_U8_S8.c
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
 * Fixed Point Interpolation INTERPOLATE_U8_S8
 */
void INTERPOLATE_U8_S8( uint8_T *pY, uint8_T yL, uint8_T yR, int8_T x, int8_T
 xL, int8_T xR)
{
  int16_T bigProd;
  uint8_T yDiff;
  int8_T xNum;
  int8_T xDen;

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
    xDen = (int8_T)(xDen - xL);

    xNum = x;
    xNum = (int8_T)(xNum - xL);

    if ( yR >= yL )
    {
      yDiff = yR;
      yDiff = (uint8_T)((uint16_T)yDiff - (uint16_T)yL);
    }
    else
    {
      yDiff = yL;
      yDiff = (uint8_T)((uint16_T)yDiff - (uint16_T)yR);
    }

    bigProd = yDiff * xNum;

    yDiff = (uint8_T)div_s16_floor(bigProd, (int16_T)xDen);

    if ( yR >= yL )
    {
      *pY = (uint8_T)((uint16_T)*pY + (uint16_T)yDiff);
    }
    else
    {
      *pY = (uint8_T)((uint16_T)*pY - (uint16_T)yDiff);
    }
  }
}

/* end INTERPOLATE_U8_S8 
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
