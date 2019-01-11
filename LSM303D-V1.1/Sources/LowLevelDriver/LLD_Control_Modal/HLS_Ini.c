#include "typedefs.h"


extern void Controller_initialize(void);
/*******************************************************************************/
/**
* \brief    Software constant initialization ,shared memory initialization,and  
            turn on all cluster lamps.
* \author   Engineer 
* \param    void
* \return   void
*/ 
void HLS_Ini()
{
   /* Enable fule pump */
   /* Initial MIL */
   #ifdef Enable_Application_Software
     Controller_initialize();/*  */
     tasks_ini();/*  */
   #endif
}
/*******************************************************************************/
/**
* \brief    Used at engine stal  or for loss of synch.All synchronization related
            initialization is done here. 
* \author   Engineer 
* \param    void
* \return   void
*/ 
void HLS_Inisyn()
{
  // vfnInit_Crank_Sensing(); /* Timer channal 1 input capture is enabled */
   //vfnGoTo_Crank_FirstEdge();/* Go the first edge */
   #ifdef Enable_Application_Software
     tasks_syn_Start();
     tasks_iniSyn();
   #endif
}
/*******************************************************************************/
/**
* \brief  Mainly for sensor input,especially for ADC input.  
* \author   Engineer 
* \param    void
* \return   void
*/ 
void HLS_ini2()
{
   /* Digital and anolog receive buffer initialization(clear) */
  vfnIGNSW_Init();
  #ifdef Enable_Application_Software
    tasks_ini2();
  #endif    
}

void HLS_syn()
{
    #ifdef Enable_Application_Software
      tasks_syn();/*  */
    #endif  
}


//===================================下面这些函数时应用层手动添加的函数=================2015-5-28
//====================================guo chao add===================================
//========
uint8_T UD_B_StaEnd = 0;
uint8_T TOnD_B_StaEnd = 0;
uint8_T B_ClrHealIsOK = 0;
uint8_T B_StartClearAllHeal = 0;

void DSM_ClearHealBit_r100ms(void)
{
    uint8_T i;     
    uint32 DTC_MemoryAddr; //====S12P--16Bit   S12XEP--32Bit
    uint16_T Temp_AllFcm[DTC_Length/2];
    static uint8_T Heal_Counter[DTC_Length/2];
    
    if(HLS_B_StaEnd)
    {       
        if(TOnD_B_StaEnd > 0)
        {
            TOnD_B_StaEnd --;
        }
        else
        {
            TOnD_B_StaEnd = 0;
        }
    }
    else
    {
        TOnD_B_StaEnd = 50;
        B_ClrHealIsOK = FALSE;
    }
    
    B_StartClearAllHeal = HLS_B_StaEnd && (TOnD_B_StaEnd == 0) && (B_ClrHealIsOK==FALSE);
    DTC_MemoryAddr = RAM_DTC;
    
    if(B_StartClearAllHeal)
    {
        B_ClrHealIsOK = TRUE;
        
        for(i=0;i<DTC_Length/2;i++)
        {
            Temp_AllFcm[i] = *(uint16_T *)DTC_MemoryAddr;
            
            if(Temp_AllFcm[i] & 0x02)//Z_Cycle == TRUE   
            {
                if(Temp_AllFcm[i] & 0x01)//E_bit == FALSE
                {                         
                    Heal_Counter[i] = 0;
                }
                else
                {
                    Heal_Counter[i]++;  
                }
                
                if(Heal_Counter[i] >= 3)
                {
                    Temp_AllFcm[i] &= 0xFFFB; //Clear Heal Bit ;
                }
            }
            
            *(uint16_T *)DTC_MemoryAddr = Temp_AllFcm[i];
            DTC_MemoryAddr += 2;
        }
    }
    else//====如果错误是在发动机熄火时产生的，要注意清零
    {
        for(i=0;i<DTC_Length/2;i++)
        {
            Temp_AllFcm[i] = *(uint16_T *)DTC_MemoryAddr;
            if(Temp_AllFcm[i] & 0x02)//Z_Cycle == TRUE   
            {
                if(Temp_AllFcm[i] & 0x01)//E_bit == FALSE
                {                         
                    Heal_Counter[i] = 0;
                }
            }
            *(uint16_T *)DTC_MemoryAddr = Temp_AllFcm[i];
            DTC_MemoryAddr += 2;
        }
    }
              
}







/* Output and update for function-call system: '<S13>/ini' */
#define START_SECTION_InitCode
#include "pragma.h"

//=================================
void Calc_Ini(void)
{
    uint16_T i;
    //===========================================================
    for(i=0;i<192;i++)
    {
        RAM_MAP_LdTp_Tps_N[i] = MAP_LdTp_Tps_N[i];
        RAM_MAP_fVe_Map_N[i] = MAP_fVe_Map_N[i];
    }
    
    for(i=0;i<176;i++)
    {
        RAM_MAP_Iga_N_Ld[i] = MAP_Iga_N_Ld[i]; 
    }
    
    
    for(i=0;i<12;i++)
    {  
        RAM_CUR_fWmp_Tm[i] = CUR_fWmp_Tm[i];        
        RAM_CUR_fAst_TmSta[i] = CUR_fAst_TmSta[i];
    }
    for(i=0;i<18;i++)
    {
        RAM_CUR_Wf_Ldp[i] = CUR_Wf_Ldp[i]; 
    } 
    //=========2015-5-26
    for(i=0;i<64;i++)
    {
        RAM_MAP_fAlt_N_Pam[i] = MAP_fAlt_N_Pam[i];
    }
    //===============================================================
    RAM_VAL_fFlApp = VAL_fFlApp;       
}

