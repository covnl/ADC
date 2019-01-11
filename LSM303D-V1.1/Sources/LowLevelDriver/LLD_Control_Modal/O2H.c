/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       O2H.c
\brief      O2 Heater Drive Control
\author     COMPANY_XXX
\author     Application Lab
\ThirdParty engieer/engieer (lab)
\version    0.1
\date       Jul/ 2008
*/
/*******************************************************************************/
#include "typedefs.h"




void LLD_O2H_Control_r20ms(void)
{
    if(HLS_CV_LSB == 7) //是否有氧传感器
    {
        if(HLS_B_LsbHtEn)
        {
            O2H1 = ON;
        }
        else
        {
            O2H1 = OFF;
        }
    }
}


/*******************************************************************************/