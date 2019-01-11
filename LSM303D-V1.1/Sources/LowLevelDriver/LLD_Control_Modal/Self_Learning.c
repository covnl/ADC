#include "typedefs.h"


uint8_T SLM_StableCondition = FALSE;
uint16_T SLM_Tps_StableRef;
uint16_T SLM_N_StableRef;
uint16_T SLM_fLamAdIn_StableRef;
uint16_T SLM_StableCounter;
uint16_T SLM_AN_N_Axis_MaxDeltaLd[SYSTEM_AN_N_AXIS_SIZE];
uint16_T SLM_AN_TPS_Axis_MaxDeltaLd[SYSTEM_AN_TPS_AXIS_SIZE];
uint16_T SLM_PN_Map_Axis_MaxDeltaLd[SYSTEM_PN_MAP_AXIS_SIZE];
uint16_T SLM_PN_N_Axis_MaxDeltaLd[SYSTEM_PN_N_AXIS_SIZE];


//==============================NVM分配内存
#define START_SECTION_SelfLern
#include "pragma.h"

UINT16 MAP_fVe_Map_N_SelfLern[192];
UINT16 MAP_LdTp_Tps_N_SelfLern[192];
UINT16 NVM_SelfLearnHistory[20];

#define STOP_SECTION_SelfLern
#include "pragma.h"




void SLM_init(void){
    uint8_T Local_Index;
    for(Local_Index = 1;Local_Index < SYSTEM_AN_N_AXIS_SIZE;Local_Index++){
        SLM_AN_N_Axis_MaxDeltaLd[Local_Index] = (SYSTEM_AN_N_AXIS[Local_Index] - SYSTEM_AN_N_AXIS[Local_Index-1])/SLM_AN_N_AXIS_TO_LD;
    }
    for(Local_Index = 1;Local_Index < SYSTEM_AN_TPS_AXIS_SIZE;Local_Index++){
        SLM_AN_TPS_Axis_MaxDeltaLd[Local_Index] = (SYSTEM_AN_TPS_AXIS[Local_Index] - SYSTEM_AN_TPS_AXIS[Local_Index-1])/SLM_AN_TPS_AXIS_TO_LD;
    }
    
    for(Local_Index = 1;Local_Index < SYSTEM_PN_MAP_AXIS_SIZE;Local_Index++){
        SLM_PN_Map_Axis_MaxDeltaLd[Local_Index] = (SYSTEM_PN_MAP_AXIS[Local_Index] - SYSTEM_PN_MAP_AXIS[Local_Index-1])/SLM_PN_MAP_AXIS_TO_LD;
    }
    for(Local_Index = 1;Local_Index < SYSTEM_PN_N_AXIS_SIZE;Local_Index++){
        SLM_PN_N_Axis_MaxDeltaLd[Local_Index] = (SYSTEM_PN_N_AXIS[Local_Index] - SYSTEM_PN_N_AXIS[Local_Index-1])/SLM_PN_N_AXIS_TO_LD;
    }
}
void SLM_20ms(void){
    if(!SYSTEM_START_END || !SYSTEM_ENABLE_AUTO_TUNING){
        SLM_StableCondition = FALSE;
        SLM_StableCounter = 0;
    }
    if(SLM_StableCounter > SLM_StableCounter_Goal){
        SLM_StableCondition = TRUE;
    }else{
        SLM_StableCondition = FALSE;
        if(SYSTEM_START_END){
            SLM_StableCounter++;
        }
    }
    
    if(SYSTEM_TPS > SLM_Tps_StableRef){
        if(SYSTEM_TPS - SLM_Tps_StableRef > SLM_TPS_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_Tps_StableRef = SYSTEM_TPS;
        }
    }else{
        if(SLM_Tps_StableRef - SYSTEM_TPS > SLM_TPS_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_Tps_StableRef = SYSTEM_TPS;
        }
    }
    if(SYSTEM_N > SLM_N_StableRef){
        if(SYSTEM_N - SLM_N_StableRef > SLM_N_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_N_StableRef = SYSTEM_N;
        }
    }else{
        if(SLM_N_StableRef - SYSTEM_N > SLM_N_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_N_StableRef = SYSTEM_N;
        }
    }
    if(SYSTEM_LOAD_FACTOR > SLM_fLamAdIn_StableRef){
        if(SYSTEM_LOAD_FACTOR - SLM_fLamAdIn_StableRef > SLM_LOAD_FACTOR_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_fLamAdIn_StableRef = SYSTEM_LOAD_FACTOR;
        }
    }else{
        if(SLM_fLamAdIn_StableRef - SYSTEM_LOAD_FACTOR > SLM_LOAD_FACTOR_STABLE_CHANGE_MIN){
            SLM_StableCounter = 0;
            SLM_fLamAdIn_StableRef = SYSTEM_LOAD_FACTOR;
        }
    }
}

void SLM_100ms(void){
    uint16_T Local_N_Input,Local_Tps_Input,Local_Ld_Input;
    uint8_T Local_N_Index,Local_Tps_Index,Local_N_iLeft,Local_N_iRight,Local_Tps_iUp,Local_Tps_iDown;
    uint16_T Local_MaxDeltaLd_Left,Local_MaxDeltaLd_Right,Local_MaxDeltaLd_Up,Local_MaxDeltaLd_Down;
    uint8_T Local_BasedIndex,Local_TempIndex;
    
    uint16_T Local_Map_Input;
    uint8_T Local_Map_Index,Local_N_iUp,Local_N_iDown,Local_Map_iLeft,Local_Map_iRight;
    uint16_T local_SLM_AN_N_AXIS_TO_LD = SLM_AN_N_AXIS_TO_LD;
    uint16_T local_SLM_AN_TPS_AXIS_TO_LD = SLM_AN_TPS_AXIS_TO_LD;
    uint16_T local_SLM_PN_MAP_AXIS_TO_LD = SLM_PN_MAP_AXIS_TO_LD;
    uint16_T local_SLM_PN_N_AXIS_TO_LD = SLM_PN_N_AXIS_TO_LD;

    Local_N_Input = SLM_N_Input;
    Local_Tps_Input = SLM_Tps_Input;
    Local_Map_Input = SLM_Map_Input;
    Local_Ld_Input = SLM_Ld_Input;
    
    if(SLM_StableCondition == FALSE)return;

    if(!SYSTEM_ADJUST_OUT_OF_RANGE){
        SLM_LearnedHistory[Local_Tps_Input / 3276U] |= (uint16_T)1 << (uint8_T)(Local_N_Input / 4000U);
    }
    
    Local_N_iLeft = 0;
    Local_N_iRight = SYSTEM_AN_N_AXIS_SIZE-1;

    if(Local_N_Input <= SYSTEM_AN_N_AXIS[0])
    {
        Local_N_iRight = 0;
    }
    else if(Local_N_Input >= SYSTEM_AN_N_AXIS[SYSTEM_AN_N_AXIS_SIZE-1])
    {
        Local_N_iLeft = SYSTEM_AN_N_AXIS_SIZE-1;
    }
    else
    {
        uint8_T Local_i;
        while (Local_N_iRight - Local_N_iLeft > 1)
        {
          Local_i = (uint8_T)(((uint16_T)Local_N_iRight + Local_N_iLeft) >> 1);
          if(Local_N_Input <= SYSTEM_AN_N_AXIS[Local_i])
          {
            Local_N_iRight = Local_i;
          }
          else
          {
            Local_N_iLeft = Local_i;
          }
        }
    }
    
    Local_Tps_iUp = 0;
    Local_Tps_iDown = SYSTEM_AN_TPS_AXIS_SIZE-1;

    if(Local_Tps_Input <= SYSTEM_AN_TPS_AXIS[0])
    {
        Local_Tps_iDown = 0;
    }
    else if(Local_Tps_Input >= SYSTEM_AN_TPS_AXIS[SYSTEM_AN_TPS_AXIS_SIZE-1])
    {
        Local_Tps_iUp = SYSTEM_AN_TPS_AXIS_SIZE-1;
    }
    else
    {
        uint8_T Local_i;
        while (Local_Tps_iDown - Local_Tps_iUp > 1)
        {
          Local_i = (uint8_T)(((uint16_T)Local_Tps_iDown + Local_Tps_iUp) >> 1);
          if(Local_Tps_Input <= SYSTEM_AN_TPS_AXIS[Local_i])
          {
            Local_Tps_iDown = Local_i;
          }
          else
          {
            Local_Tps_iUp = Local_i;
          }
        }
    }
    
    Local_MaxDeltaLd_Left = (Local_N_Input - SYSTEM_AN_N_AXIS[Local_N_iLeft])/local_SLM_AN_N_AXIS_TO_LD;
    Local_MaxDeltaLd_Right = (SYSTEM_AN_N_AXIS[Local_N_iRight] - Local_N_Input)/local_SLM_AN_N_AXIS_TO_LD;
    Local_MaxDeltaLd_Up = (Local_Tps_Input - SYSTEM_AN_TPS_AXIS[Local_Tps_iUp])/local_SLM_AN_TPS_AXIS_TO_LD;
    Local_MaxDeltaLd_Down = (SYSTEM_AN_TPS_AXIS[Local_Tps_iDown] - Local_Tps_Input)/local_SLM_AN_TPS_AXIS_TO_LD;
    
    Local_TempIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE + Local_Tps_iUp;
    if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up;
        }
    }else{
        if(SLM_AN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Up && Local_Ld_Input > Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Left- Local_MaxDeltaLd_Up;
        }
    }
    Local_BasedIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iLeft; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE; Local_N_Index--){
        for(Local_Tps_Index = Local_Tps_iUp; Local_Tps_Index > 0; Local_Tps_Index--){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index]
                    && SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] > SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_AN_TPS_AXIS_SIZE;
    }
    Local_BasedIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iLeft; Local_N_Index > 0; Local_N_Index--){
        for(Local_Tps_Index = Local_Tps_iUp; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE; Local_Tps_Index--){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] > SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] > SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_AN_TPS_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE + Local_Tps_iUp;
    if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input;
    }else{
        if(SLM_AN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Up && Local_Ld_Input > Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Left- Local_MaxDeltaLd_Up;
        }
    }
    Local_BasedIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iRight; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE; Local_N_Index++){
        for(Local_Tps_Index = Local_Tps_iUp; Local_Tps_Index > 0; Local_Tps_Index--){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index]
                    && SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] > SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index -1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex += SYSTEM_AN_TPS_AXIS_SIZE;
    }
    Local_BasedIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iRight; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE - 1; Local_N_Index++){
        for(Local_Tps_Index = Local_Tps_iUp; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE; Local_Tps_Index--){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1]
                    && SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] > SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex += SYSTEM_AN_TPS_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE + Local_Tps_iDown;
    if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Down){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Down;
        }
    }else{
        SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input;
    }
    Local_BasedIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iLeft; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE; Local_N_Index--){
        for(Local_Tps_Index = Local_Tps_iDown; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE-1; Local_Tps_Index++){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index+1]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index+1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index+1]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index +1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index+1];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index +1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_AN_TPS_AXIS_SIZE;
    }
    Local_BasedIndex = Local_N_iLeft * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iLeft; Local_N_Index > 0; Local_N_Index--){
        for(Local_Tps_Index = Local_Tps_iDown; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE; Local_Tps_Index++){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] > SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] > SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index - SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_AN_TPS_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE + Local_Tps_iDown;
    if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_AN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Right + Local_MaxDeltaLd_Down){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Right + Local_MaxDeltaLd_Down;
        }
    }else{
        if(SLM_AN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Right - Local_MaxDeltaLd_Down && Local_Ld_Input > Local_MaxDeltaLd_Right + Local_MaxDeltaLd_Down){
            SLM_AN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Right- Local_MaxDeltaLd_Down;
        }
    }
    Local_BasedIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iRight; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE; Local_N_Index++){
        for(Local_Tps_Index = Local_Tps_iDown; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE-1; Local_Tps_Index++){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index+1]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index+1] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index+1]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index +1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] + SLM_AN_TPS_Axis_MaxDeltaLd[Local_Tps_Index+1];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index +1] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex += SYSTEM_AN_TPS_AXIS_SIZE;
    }
    Local_BasedIndex = Local_N_iRight * SYSTEM_AN_TPS_AXIS_SIZE;
    for(Local_N_Index = Local_N_iRight; Local_N_Index < SYSTEM_AN_N_AXIS_SIZE - 1; Local_N_Index++){
        for(Local_Tps_Index = Local_Tps_iDown; Local_Tps_Index < SYSTEM_AN_TPS_AXIS_SIZE; Local_Tps_Index++){
            if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index]){
                if(SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] < SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1]
                    && SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] > SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1]){
                    SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index] - SLM_AN_N_Axis_MaxDeltaLd[Local_N_Index +1];
                }
            }else{
                SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index + SYSTEM_AN_TPS_AXIS_SIZE] = SLM_AN_Ld_Table[Local_BasedIndex + Local_Tps_Index];
            }
        }
        Local_BasedIndex += SYSTEM_AN_TPS_AXIS_SIZE;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Local_Map_iLeft = 0;
    Local_Map_iRight = SYSTEM_PN_MAP_AXIS_SIZE-1;

    if(Local_Map_Input <= SYSTEM_PN_MAP_AXIS[0])
    {
        Local_Map_iRight = 0;
    }
    else if(Local_Map_Input >= SYSTEM_PN_MAP_AXIS[SYSTEM_PN_MAP_AXIS_SIZE-1])
    {
        Local_Map_iLeft = SYSTEM_PN_MAP_AXIS_SIZE-1;
    }
    else
    {
        uint8_T Local_i;
        while (Local_Map_iRight - Local_Map_iLeft > 1)
        {
          Local_i = (uint8_T)(((uint16_T)Local_Map_iRight + Local_Map_iLeft) >> 1);
          if(Local_Map_Input <= SYSTEM_PN_MAP_AXIS[Local_i])
          {
            Local_Map_iRight = Local_i;
          }
          else
          {
            Local_Map_iLeft = Local_i;
          }
        }
    }
    
    Local_N_iUp = 0;
    Local_N_iDown = SYSTEM_PN_N_AXIS_SIZE-1;

    if(Local_N_Input <= SYSTEM_PN_N_AXIS[0])
    {
        Local_N_iDown = 0;
    }
    else if(Local_N_Input >= SYSTEM_PN_N_AXIS[SYSTEM_PN_N_AXIS_SIZE-1])
    {
        Local_N_iUp = SYSTEM_PN_N_AXIS_SIZE-1;
    }
    else
    {
        uint8_T Local_i;
        while (Local_N_iDown - Local_N_iUp > 1)
        {
          Local_i = (uint8_T)(((uint16_T)Local_N_iDown + Local_N_iUp) >> 1);
          if(Local_N_Input <= SYSTEM_PN_N_AXIS[Local_i])
          {
            Local_N_iDown = Local_i;
          }
          else
          {
            Local_N_iUp = Local_i;
          }
        }
    }
    
    Local_MaxDeltaLd_Left = (Local_Map_Input - SYSTEM_PN_MAP_AXIS[Local_Map_iLeft])/local_SLM_PN_MAP_AXIS_TO_LD;
    Local_MaxDeltaLd_Right = (SYSTEM_PN_MAP_AXIS[Local_Map_iRight] - Local_Map_Input)/local_SLM_PN_MAP_AXIS_TO_LD;
    Local_MaxDeltaLd_Up = (Local_N_Input - SYSTEM_PN_N_AXIS[Local_N_iUp])/local_SLM_PN_N_AXIS_TO_LD;
    Local_MaxDeltaLd_Down = (SYSTEM_PN_N_AXIS[Local_N_iDown] - Local_N_Input)/local_SLM_PN_N_AXIS_TO_LD;
    
    Local_TempIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE + Local_N_iUp;
    if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input;
    }else{
        if(SLM_PN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Up && Local_Ld_Input > Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Left- Local_MaxDeltaLd_Up;
        }
    }
    Local_BasedIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iLeft; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE; Local_Map_Index--){
        for(Local_N_Index = Local_N_iUp; Local_N_Index > 0; Local_N_Index--){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index]
                    && SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] > SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_PN_N_AXIS_SIZE;
    }
    Local_BasedIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iLeft; Local_Map_Index > 0; Local_Map_Index--){
        for(Local_N_Index = Local_N_iUp; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE; Local_N_Index--){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index]
                    && SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] > SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_PN_N_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE + Local_N_iUp;
    if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Left+ Local_MaxDeltaLd_Up;
        }
    }else{
        if(SLM_PN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Up && Local_Ld_Input > Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Up){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Left- Local_MaxDeltaLd_Up;
        }
    }
    Local_BasedIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iRight; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE; Local_Map_Index++){
        for(Local_N_Index = Local_N_iUp; Local_N_Index > 0; Local_N_Index--){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index]
                    && SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] > SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index -1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex += SYSTEM_PN_N_AXIS_SIZE;
    }
    Local_BasedIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iRight; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE - 1; Local_Map_Index++){
        for(Local_N_Index = Local_N_iUp; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE; Local_N_Index--){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] > SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] > SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index +1]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index +1];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex += SYSTEM_PN_N_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE + Local_N_iDown;
    if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Down){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Down;
        }
    }else{
        if(SLM_PN_Ld_Table[Local_TempIndex] < Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Down
            && Local_Ld_Input > Local_MaxDeltaLd_Left + Local_MaxDeltaLd_Down){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input - Local_MaxDeltaLd_Left - Local_MaxDeltaLd_Down;
        }
    }
    Local_BasedIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iLeft; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE; Local_Map_Index--){
        for(Local_N_Index = Local_N_iDown; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE-1; Local_N_Index++){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index+1]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index+1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index+1]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index +1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index+1];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index +1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_PN_N_AXIS_SIZE;
    }
    Local_BasedIndex = Local_Map_iLeft * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iLeft; Local_Map_Index > 0; Local_Map_Index--){
        for(Local_N_Index = Local_N_iDown; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE; Local_N_Index++){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index]
                    && SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] > SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] - SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index - SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex -= SYSTEM_PN_N_AXIS_SIZE;
    }
    
    Local_TempIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE + Local_N_iDown;
    if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input){
        if(SLM_PN_Ld_Table[Local_TempIndex] > Local_Ld_Input + Local_MaxDeltaLd_Right + Local_MaxDeltaLd_Down){
            SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input + Local_MaxDeltaLd_Right + Local_MaxDeltaLd_Down;
        }
    }else{
        SLM_PN_Ld_Table[Local_TempIndex] = Local_Ld_Input;
    }
    Local_BasedIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iRight; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE; Local_Map_Index++){
        for(Local_N_Index = Local_N_iDown; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE-1; Local_N_Index++){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index+1]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index+1] < SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index+1]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index +1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_N_Axis_MaxDeltaLd[Local_N_Index+1];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index +1] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex += SYSTEM_PN_N_AXIS_SIZE;
    }
    Local_BasedIndex = Local_Map_iRight * SYSTEM_PN_N_AXIS_SIZE;
    for(Local_Map_Index = Local_Map_iRight; Local_Map_Index < SYSTEM_PN_MAP_AXIS_SIZE - 1; Local_Map_Index++){
        for(Local_N_Index = Local_N_iDown; Local_N_Index < SYSTEM_PN_N_AXIS_SIZE; Local_N_Index++){
            if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] > SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index]){
                if(SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] > SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index +1]){
                    SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index] + SLM_PN_Map_Axis_MaxDeltaLd[Local_Map_Index +1];
                }
            }else{
                SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index + SYSTEM_PN_N_AXIS_SIZE] = SLM_PN_Ld_Table[Local_BasedIndex + Local_N_Index];
            }
        }
        Local_BasedIndex += SYSTEM_PN_N_AXIS_SIZE;
    }
}




/***************************************************************************
**将fVe表格转换成Ld
** Ld =fVe * Map * VAL_fPrs2LdNrm
** fVe:Q = V*32768 
** Map: Q = V*25.6
** VAL_fPrs2LdNrm:Q = V*218453.333333
** Ld:Q = V*42.666667
***************************************************************************/
void Convert_fVe_To_Ld(void)
{
    UINT8 i,j;
    UINT32 Local_temp1,Local_temp2;
    
    //fLamAdTab[i*16+j] =  (Local_temp1/32768) * (BP_fVe_Map[i]/25.6) * (VAL_fPrs2LdNrm/218453.333333)
    //============================================================================================
    for(i=0;i<16;i++)
    {
        Local_temp1 = BP_fVe_Map[i];
        Local_temp1 = (Local_temp1 * VAL_fPrs2LdNrm)>>16;
        
        for(j=0;j<12;j++)
        {
            Local_temp2 = MAP_fVe_Map_N_SelfLern[i*12+j];//MAP_fVe_Map_N_SelfLern[i*16+j];
            Local_temp2 = (Local_temp2 * Local_temp1) >> 16;

            fLamAdTab[i*12+j] = (UINT16)(Local_temp2+1);//====加1是为了平衡前面计算过程中产生的误差
        }
    }
    
    //============================================================================================
    for(i=0;i<192;i++)
    {
        fLamAdTab_an[i] = MAP_LdTp_Tps_N_SelfLern[i];
    }
    
    //============================================================================================
    for(i=0;i<20;i++)
    {
        RAM_SelfLearnHistory[i] = NVM_SelfLearnHistory[i];
    }
            
}

/***************************************************************************
**将Ld表格转换成fVe
** fVe = Ld/Map/VAL_fPrs2LdNrm
** fVe:Q = V*32768 
** Map: Q = V*25.6
** VAL_fPrs2LdNrm:Q = V*218453.333333
** Ld:Q = V*42.666667
***************************************************************************/
void Convert_Ld_To_fVe(void)
{
    UINT8 i,j;
    UINT32 Local_temp1,Local_temp2;
    
    //fLamAdTab[i*16+j] = (Local_temp1/42.6667) / (BP_fVe_Map[i]/25.6) / (VAL_fPrs2LdNrm/218453.333333);
    
    for(i=0;i<16;i++)
    {
        Local_temp1 = BP_fVe_Map[i];
        Local_temp1 = (Local_temp1 * VAL_fPrs2LdNrm)>>16;
        if(Local_temp1==0) Local_temp1=1;
        
        for(j=0;j<12;j++)
        {
            Local_temp2 = ((UINT32)fLamAdTab[i*12+j])<<16;//fLamAdTab[i*16+j];
            Local_temp2 = Local_temp2  / Local_temp1 ;
            fLamAdTab[i*12+j] = (UINT16)(Local_temp2);
        }
    }
        
}



/***************************************************************************
**自学习表格初始化
**上次写NVM失败后的初始化
***************************************************************************/
void SelfLearningTabInit(UINT8 Status)
{
    UINT16 i,j;
    UINT32 Local_temp1,Local_temp2;
    
    if(Status == 1)
    {
        //=====================================================
        for(i=0;i<192;i++)
        {
            fLamAdTab_an[i] = MAP_LdTp_Tps_N[i];
        }
        
        //=====================================================  
        for(i=0;i<20;i++)
        {
            RAM_SelfLearnHistory[i] = 0;
        }
        //=====================================================
        for(i=0;i<16;i++)
        {
            Local_temp1 = BP_fVe_Map[i];
            Local_temp1 = (Local_temp1 * VAL_fPrs2LdNrm)>>16;
                
            for(j=0;j<12;j++)
            {
                Local_temp2 = MAP_fVe_Map_N[i*12+j];
                Local_temp2 = (Local_temp2 * Local_temp1) >> 16;
                fLamAdTab[i*12+j] = (UINT16)(Local_temp2+1);//====加1是为了平衡前面计算过程中产生的误差
            }
        }
    
    }
    else
    {
         //=====================================================
        for(i=0;i<192;i++)
        {
            fLamAdTab_an[i] = MAP_LdTp_Tps_N[i];
            fLamAdTab[i] = MAP_fVe_Map_N[i];
        }
        
        //=====================================================  
        for(i=0;i<20;i++)
        {
            RAM_SelfLearnHistory[i] = 0;
        }
        
        //=====================================================
        Erase_D_Flash(4,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS);
        Ram_Ptr = (UINT16 *)RAM_WriteBack_Data;
        Write_D_Flash(Ram_Ptr,Writeback_Data_Length/8+1,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS);

        //=====================================================
        for(i=0;i<16;i++)
        {
            Local_temp1 = BP_fVe_Map[i];
            Local_temp1 = (Local_temp1 * VAL_fPrs2LdNrm)>>16;
                
            for(j=0;j<12;j++)
            {
                Local_temp2 = MAP_fVe_Map_N[i*12+j];
                Local_temp2 = (Local_temp2 * Local_temp1) >> 16;
                fLamAdTab[i*12+j] = (UINT16)(Local_temp2+1);//====加1是为了平衡前面计算过程中产生的误差
            }
        }
    }
    
}




