/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\INTERPOLATE_U16_U8.c
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
 * Fixed Point Interpolation INTERPOLATE_U16_U8
 */
void INTERPOLATE_U16_U8( uint16_T *pY, uint16_T yL, uint16_T yR, uint8_T x,
 uint8_T xL, uint8_T xR)
{
  uint32_T bigProd;
  uint16_T yDiff;
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
      yDiff = yDiff - yL;
    }
    else
    {
      yDiff = yL;
      yDiff = yDiff - yR;
    }

    bigProd = (uint32_T)yDiff * (uint32_T)xNum;

    {
      uint32_T rtb_u32_tmp;
      rtb_u32_tmp = (uint32_T)xDen;
     yDiff = (uint16_T)(rtb_u32_tmp == (uint32_T)0 ? MAX_uint32_T :
        (uint32_T)(bigProd / rtb_u32_tmp));
    }

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

/* end INTERPOLATE_U16_U8 
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
