
#include "typedefs.h"


#define FlashingCode_LongTime 20  //2S
#define FlashingCode_ShortTime 5 //500ms

UINT8 FlashingCode_LEDOnTimes=0;
UINT8 FlashingCode_Start=0;
UINT8 FlashingCode_TotalDTCToFlash=0;
UINT8 FlashingCode_OneDTCFlashTimes[16];
UINT8 FlashingCode_GapBetweenDTCs=0;
UINT8 FlashingCode_PortLevel=0;
UINT8 FlashingCode_DTC_Total=0;


extern UINT8 Task_Enable;

/*
位数越低，优先级越高，理论上只有1个bit为真

0--代表没故障灯输出
bit0-- MIL_Lamp
bit1-- INJIN2
bit2-- O2HIN1
bit3-- IGNIN1
bit4-- reserved
*/

/*
闪码：
闪码顺序：

1--CKP

2--MAP

3--Ub

4--TPS

5--ECT

6--IAT

7--LSB1

8--LSB2    


*/
void GetDTCNumFromController(void)
{
    FlashingCode_DTC_Total = 0;
    
    if(HLS_E_Crk)
    {
        FlashingCode_DTC_Total++ ;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_CKP;
    }
    else if(HLS_E_Map)
    {
        FlashingCode_DTC_Total++;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_MAP;
    }
    else if(HLS_E_Tps)
    {
        FlashingCode_DTC_Total++;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_TPS;
    }
    else if(HLS_E_Ub)
    {
        FlashingCode_DTC_Total++ ;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_Ub;
    }     
    else if(HLS_E_Tm)
    {
        FlashingCode_DTC_Total++;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_ECT;
    }
    else if(HLS_E_Ta)
    {
        FlashingCode_DTC_Total++;
        FlashingCode_OneDTCFlashTimes[FlashingCode_DTC_Total] = FlashingCode_IAT;
    }
    
    if(FlashingCode_TotalDTCToFlash==0)
    {
        if(FlashingCode_DTC_Total==0)return;
        FlashingCode_TotalDTCToFlash = FlashingCode_DTC_Total;
        FlashingCode_Start = TRUE;
    }
    else
    {   
        FlashingCode_TotalDTCToFlash--;
    }

}

void DTC_FlashingOnePeriod(void)
{
    static UINT8 LightOnTime = FlashingCode_ShortTime;
    static UINT8 LightOffTime = 0;
    
    if(LightOnTime == 0)
    {
        FlashingCode_PortLevel = OFF;//
        if(LightOffTime>0)LightOffTime --;
        if(LightOffTime == 0)
        {
            LightOnTime = FlashingCode_ShortTime;
            if(FlashingCode_OneDTCFlashTimes[FlashingCode_TotalDTCToFlash]>0)
            {
                FlashingCode_OneDTCFlashTimes[FlashingCode_TotalDTCToFlash] --;
                if(FlashingCode_OneDTCFlashTimes[FlashingCode_TotalDTCToFlash]==0)
                {
                    FlashingCode_GapBetweenDTCs = FlashingCode_LongTime;
                    FlashingCode_TotalDTCToFlash--;
                }
            }
        }
    }
    else
    {
         FlashingCode_PortLevel = ON;
         LightOnTime --;
         LightOffTime = FlashingCode_ShortTime;
    }
       
}


void  Fault_Code_Indication_100ms(void)
{
    UINT8 Local_Lampout_Sel;

    //===============================================
    Local_Lampout_Sel = HLS_CV_LampOutSelect;
    
    #ifdef DTC_FlashingCode_En
        
        //=================================
        if(Task_Enable == FALSE)
        {
            FlashingCode_PortLevel = ~FlashingCode_PortLevel;
        }
        else if(HLS_B_Mil)
        {
            if(FlashingCode_Start==FALSE)//====Port is in idle
            {                   
                GetDTCNumFromController();                
            }
            else
            {
                if(FlashingCode_GapBetweenDTCs == 0)
                {
                    if(FlashingCode_TotalDTCToFlash>0)
                    {
                        DTC_FlashingOnePeriod();
                    }
                    else
                    {
                        FlashingCode_Start = FALSE;
                    }
                }
                else
                {
                    FlashingCode_GapBetweenDTCs --;
                }    
            }
        }
        else
        {
            FlashingCode_PortLevel = FALSE;
            FlashingCode_Start = FALSE;
            FlashingCode_TotalDTCToFlash = 0;
        } 
        
    #else
        FlashingCode_PortLevel = HLS_B_Mil;
    #endif 
    
    //===============================
    switch(Local_Lampout_Sel)
    {
      case 0:
      break;
      
      case 1:
          MIL_Lamp = FlashingCode_PortLevel;
      break;
      
      case 2:
          INJIN2 = FlashingCode_PortLevel;
      break;
      
      case 4:
          O2H1 = FlashingCode_PortLevel; 
      break;
      
      case 8:
          IGNIN1 = FlashingCode_PortLevel;
      break;
      
      
      default:
      break;
    }   
}
  
  
 /* 
  #ifdef LLD_V10_5_2 
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif
  //============================================
  #ifdef LLD_4T1CCD_IA
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif 
  //=========================================
  #ifdef LLD_4T2CCD
    MIL_Lamp = B_Mil;
    return;
  #endif 
  //=========================================
  #ifdef LLD_4T2CTH
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif 
  //=====================================
  #ifdef LLD_4T2C2IG 
    MIL_Lamp = B_Mil;
    return;
  #endif
  //======================================
  #ifdef LLD_4T2C1IG
    MIL_Lamp = B_Mil;
    return;
  #endif
  //======================================
  #ifdef LLD_4T1CCD_TR
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif
  
  //======================================
  #ifdef LLD_4T1CTH_1_1
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif
  
  //======================================
  #ifdef LLD_4T1CTH_IA_1_2
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif
  
  
  //========================================
  #ifdef LLD_4T1CCD_IA_M1
  
    IGNIN1 = B_Mil;
    return;
  #endif
  
  //========================================
  #ifdef LLD_4T1CTH_TR2_0M
    if(VAL_nRevPerCycle ==2)//2T or 4T
    {
        if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
        else if(CV_LSB == 0)//无氧传感器
        {
            O2HIN1 = B_Mil;  
        }
    }
    else
    {
        if(CV_LSB==0) //有无氧传感器
        {
            O2HIN1 = B_Mil;
        }
        else if(CV_FL2TI==0) //1个喷油器还是2个喷油器
        {
            INJIN2 = B_Mil;
        }
    }
    return;
  #endif
  */
  
                                                                                    













