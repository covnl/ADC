/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\INTERPOLATE_U8_U8.c
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
 * Fixed Point Interpolation INTERPOLATE_U8_U8
 */
void INTERPOLATE_U8_U8( uint8_T *pY, uint8_T yL, uint8_T yR, uint8_T x, uint8_T
 xL, uint8_T xR)
{
  uint16_T bigProd;
  uint8_T yDiff;
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

    bigProd = (uint16_T)yDiff * (uint16_T)xNum;

    {
      uint16_T rtb_u16_tmp;
      rtb_u16_tmp = (uint16_T)xDen;
     yDiff = (uint8_T)(rtb_u16_tmp == (uint16_T)0 ? MAX_uint16_T :
        (uint16_T)(bigProd / rtb_u16_tmp));
    }

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

/* end INTERPOLATE_U8_U8 
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
