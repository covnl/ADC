/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\Look2D_S8_U8_U8.c
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
 * Fixed-Point 2D Lookup Utility Look2D_S8_U8_U8
 */
void Look2D_S8_U8_U8( int8_T *pY, const int8_T *pYData, uint8_T u0, const
 uint8_T *pU0Data, uint_T iHiU0, uint8_T u1, const uint8_T *pU1Data, uint_T
 iHiU1)
{
  uint_T iLeftU0, iRghtU0, iLeftU1, iRghtU1;

  BINARYSEARCH_U8( &(iLeftU0), &(iRghtU0), u0, pU0Data, iHiU0);

  BINARYSEARCH_U8( &(iLeftU1), &(iRghtU1), u1, pU1Data, iHiU1);

  {
    uint8_T u0Left = pU0Data[iLeftU0];
    uint8_T u0Rght = pU0Data[iRghtU0];
    uint8_T u1Left = pU1Data[iLeftU1];
    uint8_T u1Rght = pU1Data[iRghtU1];

    int8_T yTemp;

    int8_T yLeftLeft;
    int8_T yLeftRght;
    int8_T yRghtLeft;
    int8_T yRghtRght;

    iHiU0++;
    iLeftU1 *= iHiU0;
    iRghtU1 *= iHiU0;

    yRghtLeft = pYData[(iRghtU0+iLeftU1)];
    yRghtRght = pYData[(iRghtU0+iRghtU1)];
    yLeftLeft = pYData[(iLeftU0+iLeftU1)];
    yLeftRght = pYData[(iLeftU0+iRghtU1)];

    /* Interpolate along U1 variable
     *    with the u0 variable locked on the left u0
     */
    INTERPOLATE_S8_U8( pY, yLeftLeft, yLeftRght, u1, u1Left, u1Rght);

    /* Interpolate along U1 variable
     *    with the u0 variable locked on the right u0
     */
    INTERPOLATE_S8_U8( (&(yTemp)), yRghtLeft, yRghtRght, u1, u1Left, u1Rght);

    /*
     * Interpolate along u0 variable
     *    with the u1 variable locked on its interpolated value
     */
    INTERPOLATE_S8_U8( pY, (*pY), yTemp, u0, u0Left, u0Rght);
  }
}

/* end function Look2D_S8_U8_U8
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
