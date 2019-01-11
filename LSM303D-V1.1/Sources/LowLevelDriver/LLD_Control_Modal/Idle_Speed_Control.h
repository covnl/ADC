#ifndef __IDLE_SPEED_CONTROL_H
#define __IDLE_SPEED_CONTROL_H



//===========================================
//States of the idle speed motor
#define STOPPED      1
#define CLOSING      2
#define OPENING      3

//stepper motor states
#define MOTOR_OFF     0x00
#define TURN_MOTOR_ON 0xFF

#define LLD_StepPosMx 400
#define LLD_StepPosMn  0









//===========================================
void ISM_Init(void);
void vfn_Half_Step_Forward(void);
void vfn_Half_Step_Backward(void);
void vfnSet_ISM_Position(UINT16 u16Position_Input);
void vfn_ISM_TASK(void);
void ISM_Controller_Run(void);
void Idle_Speed_Controller(void);
void Idle_Speed_Controller_Init(void);









#endif
