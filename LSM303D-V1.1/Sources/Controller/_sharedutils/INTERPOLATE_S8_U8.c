/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\INTERPOLATE_S8_U8.c
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
 * Fixed Point Interpolation INTERPOLATE_S8_U8
 */
void INTERPOLATE_S8_U8( int8_T *pY, int8_T yL, int8_T yR, uint8_T x, uint8_T xL,
 uint8_T xR)
{
  int16_T bigProd;
  int8_T yDiff;
  uint8_T xNum;
  uint8_T xDen;

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
    xDen = (uint8_T)((uint16_T)xDen - (uint16_T)xL);

    xNum = x;
    xNum = (uint8_T)((uint16_T)xNum - (uint16_T)xL);

    yDiff = yR;
    yDiff = (int8_T)(yDiff - yL);

    bigProd = yDiff * xNum;

    yDiff = div_s8s16_floor(bigProd, (int16_T)xDen);

    *pY = (int8_T)(*pY + yDiff);
  }
}

/* end INTERPOLATE_S8_U8 
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
