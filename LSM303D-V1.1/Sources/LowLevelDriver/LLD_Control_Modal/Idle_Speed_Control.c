#include "typedefs.h"


//====Define===================================
//ISM control definitions
//Control commands
#define STAY 0 
#define CLOSE 1
#define OPEN 2
//Controller loop time
//Based on User Management Task ever 10ms
//Control time set for 500ms
#define ISM_TOUT 50



//===Variables===============================

UINT8  u8ISM_State;
UINT8  u8_motor_state;
UINT16 u16Current_ISM_Position;
UINT16 u16Commanded_ISM_Position;





//extern UINT16 u16Current_ISM_Position;
extern UINT16 StepPosDsr_WB;
extern UINT8 StepMovedOneStep;

//====Functions=============================

void ISM_Init(void)
{
 //Set the ISM control signals to a default state and initialize 
  //the controller.  Run this function on every key on cycle.  
  
  //Set control signals to initialized motor position of state 1
  ISM_ENABLEA = TRUE;
  ISM_ENABLEB = TRUE;
  //===========有2种步进电机，引脚顺序不同，注意区分=========
  
    TPMA = 0;
    TPMB = 0;
    TPMC = 0;
    TPMD = 0;

  //Set motor control state to match signals of state 1.
  u8_motor_state = 0x01;
  //Set the ISM control state to stopped.
  u8ISM_State = STOPPED;
  //Set the last motor state to first position.
  //u8_last_motor_state = 0x01;
  //Init the current position to zero
  #ifdef NoBatterySystem
    StepPosDsr_WB = StepPos;
  #else
    if(HLS_B_Pwf)
    {
        u16Current_ISM_Position = HLS_VAL_StepPosMx + 10;
    }
    else
    {
        if(HLS_StepPos != 0xFFFF) u16Current_ISM_Position = HLS_StepPos;//Read data from NVM
        else u16Current_ISM_Position = HLS_VAL_StepPosMx + 10;
    }

    //Init the desired position match current position
    u16Commanded_ISM_Position = 0;
    HLS_StepPos = u16Current_ISM_Position;
  #endif  

}

/******************************************************
**
**
******************************************************/
void vfn_Half_Step_Backward(void)
{
    
    switch(u8_motor_state)
    {
        //first stage
        case 0x01:
          TPMA = 0;
          TPMB = 0;
          TPMC = 0;
          TPMD = 1;

          u8_motor_state=0x08;
          break;
        
        //second stage
        case 0x02:

          TPMA = 1;
          TPMB = 0;
          TPMC = 0;
          TPMD = 1;

          u8_motor_state--;
          break;
        
        //third stage
        case 0x03:

          TPMA = 1;          
          TPMB = 0;
          TPMC = 0;
          TPMD = 0;

          u8_motor_state--;
          break;
        
        //fourth stage
        case 0x04:

          TPMA = 1;          
          TPMB = 0;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state--;
          break;
        
        //fifth stage
        case 0x05:

          TPMA = 0;           
          TPMB = 0;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state--;
        break;
        
        //sixth stage
        case 0x06:

          TPMA = 0;          
          TPMB = 1;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state--;
          break;
        
        //seventh stage
        case 0x07:

          TPMA = 0;
          TPMB = 1;
          TPMC = 0;          
          TPMD = 0;

          u8_motor_state--;
          break;
        
        //eigth stage
        case 0x08:

          TPMA = 0;
          TPMB = 1;
          TPMC = 0;
          TPMD = 1;

          u8_motor_state--;
          break;
        
        default:
          break;
    }
    u16Current_ISM_Position--;
}

/******************************************************
**
**
******************************************************/
void vfn_Half_Step_Forward(void)
{
    
    switch(u8_motor_state)
    {
        case 0x01:
          TPMA = 1;
          TPMB = 0;
          TPMC = 0;
          TPMD = 1;

          u8_motor_state++;
          break;
        
        //second stage
        case 0x02:

          TPMA = 1;          
          TPMB = 0;
          TPMC = 0;
          TPMD = 0;

          u8_motor_state++;
          break;
        
        //third stage
        case 0x03:

          TPMA = 1;          
          TPMB = 0;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state++;
          break;
        
        //fourth stage
        case 0x04:

          TPMA = 0;           
          TPMB = 0;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state++;
          break;
        
        //fifth stage
        case 0x05:

          TPMA = 0;          
          TPMB = 1;
          TPMC = 1;
          TPMD = 0;

          u8_motor_state++;
        break;
        
        //sixth stage
        case 0x06:

          TPMA = 0;
          TPMB = 1;
          TPMC = 0;          
          TPMD = 0;

          u8_motor_state++;
          break;
        
        //seventh stage
        case 0x07:

          TPMA = 0;
          TPMB = 1;
          TPMC = 0;
          TPMD = 1;

          u8_motor_state++;
          break;
        
        //eigth stage
        case 0x08:

          TPMA = 0;
          TPMB = 0;
          TPMC = 0;
          TPMD = 1;
          
          u8_motor_state = 0x01;
          break;
        
        default:
          break;
    }
    u16Current_ISM_Position++;
}

/******************************************************
**
**
******************************************************/
void vfnSet_ISM_Position(UINT16 u16Position_Input)
{
    //Use u16Commanded_Position to set the position for the ISM.
    u16Commanded_ISM_Position = u16Position_Input;
    //In the

    if(u16Commanded_ISM_Position > HLS_VAL_StepPosMx)u16Commanded_ISM_Position = HLS_VAL_StepPosMx + StepMovedOneStep;
}

/******************************************************
**
**
******************************************************/
void vfn_ISM_TASK(void)
{  
    if(u16Commanded_ISM_Position < u16Current_ISM_Position)
    {        
        u8ISM_State = OPENING;
        vfn_Half_Step_Backward();
    }
    else if(u16Commanded_ISM_Position > u16Current_ISM_Position)
    {        
        u8ISM_State = CLOSING;
        vfn_Half_Step_Forward();
    }else
    {
        u8ISM_State = STOPPED;
        TPMA = 0;
        TPMC = 0;
        TPMB = 0;
        TPMD = 0;   
    }
    //=======update the position========================
     StepPos = u16Current_ISM_Position;
    //====================================
}

/******************************************************
**
**
******************************************************/
void Idle_Speed_Controller_Init(void)
{
    //Initialize the low level controller.
    ISM_Init();
}

/******************************************************
**
**
******************************************************/
void Idle_Speed_Controller(void)
{
}


/******************************************************
**
**
******************************************************/

void ISM_Controller_Run(void)
{
}

