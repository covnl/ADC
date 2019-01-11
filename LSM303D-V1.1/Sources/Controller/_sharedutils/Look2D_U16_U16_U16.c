/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\Look2D_U16_U16_U16.c
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
 * Fixed-Point 2D Lookup Utility Look2D_U16_U16_U16
 */
void Look2D_U16_U16_U16( uint16_T *pY, const uint16_T *pYData, uint16_T u0,
 const uint16_T *pU0Data, uint_T iHiU0, uint16_T u1, const uint16_T *pU1Data,
 uint_T iHiU1)
{
  uint_T iLeftU0, iRghtU0, iLeftU1, iRghtU1;

  BINARYSEARCH_U16( &(iLeftU0), &(iRghtU0), u0, pU0Data, iHiU0);

  BINARYSEARCH_U16( &(iLeftU1), &(iRghtU1), u1, pU1Data, iHiU1);

  {
    uint16_T u0Left = pU0Data[iLeftU0];
    uint16_T u0Rght = pU0Data[iRghtU0];
    uint16_T u1Left = pU1Data[iLeftU1];
    uint16_T u1Rght = pU1Data[iRghtU1];

    uint16_T yTemp;

    uint16_T yLeftLeft;
    uint16_T yLeftRght;
    uint16_T yRghtLeft;
    uint16_T yRghtRght;

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
    INTERPOLATE_U16_U16( pY, yLeftLeft, yLeftRght, u1, u1Left, u1Rght);

    /* Interpolate along U1 variable
     *    with the u0 variable locked on the right u0
     */
    INTERPOLATE_U16_U16( (&(yTemp)), yRghtLeft, yRghtRght, u1, u1Left, u1Rght);

    /*
     * Interpolate along u0 variable
     *    with the u1 variable locked on its interpolated value
     */
    INTERPOLATE_U16_U16( pY, (*pY), yTemp, u0, u0Left, u0Rght);
  }
}

/* end function Look2D_U16_U16_U16
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
