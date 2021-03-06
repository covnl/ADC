/*
 * File: C:\ECOTRON\Product\SW\SEA\slprj\ert\_sharedutils\BINARYSEARCH_U8_iL.c
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
 * Fixed-Point Binary Search Utility BINARYSEARCH_U8_iL
 */
void BINARYSEARCH_U8_iL( uint_T *piLeft, uint8_T u, const uint8_T *pData, uint_T
 iHi)
{
  uint_T iRght;
  /* Find the location of current input value in the data table. */
  *piLeft = 0;
  iRght = iHi;

  if ( u <= pData[0] )
  {
    /* Less than or equal to the smallest point in the table. */
    iRght = 0;
  }
  else if ( u >= pData[iHi] )
  {
    /* Greater than or equal to the largest point in the table. */
    *piLeft = iHi;
  }
  else
  {
    uint_T i;

    /* Do a binary search. */
    while ( ( iRght - *piLeft ) > 1 )
    {
      /* Get the average of the left and right indices using to Floor rounding. */
      i = (*piLeft + iRght) >> 1;

      /* Move either the right index or the left index so that */
      /*  LeftDataPoint <= CurrentValue < RightDataPoint */
      if ( u < pData[i] )
      {
        iRght = i;
      }
      else
      {
        *piLeft = i;
      }
    }
  }
}

/* end macro BINARYSEARCH_U8_iL
 *********************************************************************/

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
