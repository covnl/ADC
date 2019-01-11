/*******************************************************************************/
#include "typedefs.h"

UINT16 uMapRaw;
UINT16 uPumpCurrent; 
UINT16 uLsb2;
UINT16 uEGT;
UINT16 uKnockS;
UINT16 uServoFromVR;//VR--Variable Resistor
/* Array of analog signals to monitor */
UINT8 signals_array[10] = {9,0,1,2,3,4,5,6,7,8};
#define signals_array_length   10

/* Initialize the pointer of the array */
UINT8 signals_pointer = 0;
UINT16 samples_array[signals_array_length];

extern UINT16 uIGNSW;

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt ATD0_conversion_complete(void){
    
    //store current sample in appropiate place 
    switch(signals_array[signals_pointer])
    {
        
        //#ifdef AFR
        case 0:
            uPumpCurrent =ATDDR0; 
            HLS_AD_CH0 = uPumpCurrent;
        break;
        //#endif 
        
        //#ifdef O2H2
        case 1:
         uKnockS = ATDDR0 ; 
         uLsb2 = uKnockS;
        break;
        //#endif 
            
        //#ifdef O2H1
        case 2:
        HLS_AD_CH2 = ATDDR0 ;        
        break;
        //#endif 
        
        //#ifdef MAP
        case 3:
        uMapRaw=ATDDR0;
        HLS_AD_CH3 = uMapRaw;
        break;
        //#endif

        //#ifdef TPS 
        case 4:
        HLS_AD_CH4 = ATDDR0;
        HLS_uServoIn = HLS_AD_CH4;
        break;
        //#endif 
        
        //#ifdef VBAT 
        case 5:
        HLS_AD_CH5 = ((ATDDR0<<2)+ATDDR0)>>3;
        break;
        //#endif
           
        //#ifdef ATEMP
        case 6:
        HLS_AD_CH6 = ATDDR0;
        break;
        //#endif 
        
        //#ifdef ETEMP
        case 7:
        HLS_AD_CH7 = ATDDR0;
        break;
       // #endif
        
        case 8:
        //====debug  外挂ECU定制版本
        HLS_AD_CH8 = ATDDR0;
        uEGT = uPot;
        break;
        
       // #ifdef IGNSW
        case 9:
        uIGNSW = ATDDR0;
        break;
       // #endif
    }
    //trigger next conversion
    signals_pointer++;   
    if(signals_pointer>=signals_array_length)
    {
        signals_pointer = 0; 
    } 
    else 
    {                    
        vfn_convertADC_Channel(signals_array[signals_pointer]);        
    }

    //clear flag    
    ATDSTAT0_SCF = 1;
}

#pragma CODE_SEG DEFAULT

