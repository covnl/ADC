#include "typedefs.h"


extern UINT8   VAL_SAEJ1939_Broadcast_En;
extern UINT16  VAL_Angle_Broadcast_Rate ;
extern UINT8   VAL_Angle_Broadcast_FrameType ;
extern UINT32  VAL_Angle_Broadcast_CANID ; //pgn 61459  
extern UINT16  VAL_Acceleration_Broadcast_Rate ;
extern UINT8   VAL_Acceleration_Broadcast_FrameType ;
extern UINT32  VAL_Acceleration_Broadcast_CANID ; //pgn 61449
extern INT16   Roll_Angle_Output;
extern INT16   Pitch_Angle_Output;
extern INT16   X_acc;
extern UINT8   Task_Enable;

UINT16 J1939_RollAng_output;
UINT16 J1939_PitchAng_output;
UINT8  J1939_Longitudinal_Acc_output;

UINT16  HLS_Angle_Broadcast_Rate ;
UINT8   HLS_Angle_Broadcast_FrameType ;
UINT32  HLS_Angle_Broadcast_CANID ; //pgn 61459  
UINT16  HLS_Acceleration_Broadcast_Rate ;
UINT8   HLS_Acceleration_Broadcast_FrameType ;
UINT32  HLS_Acceleration_Broadcast_CANID ; //pgn 61449


/*****************************************************
** 
* \brief    flash time .
* \author   Engineer
* \param    void
* \return   void
* \todo     Get ADC Channels value
**
*****************************************************/
void SAE_J1939Brodcast_Init(void)
{
    HLS_Angle_Broadcast_Rate = VAL_Angle_Broadcast_Rate;
    HLS_Angle_Broadcast_FrameType = VAL_Angle_Broadcast_FrameType;
    HLS_Angle_Broadcast_CANID = VAL_Angle_Broadcast_CANID;
    HLS_Acceleration_Broadcast_Rate = VAL_Acceleration_Broadcast_Rate;
    HLS_Acceleration_Broadcast_FrameType = VAL_Acceleration_Broadcast_FrameType;
    HLS_Acceleration_Broadcast_CANID = VAL_Acceleration_Broadcast_CANID;
}


void SAE_J1939Brodcast_1ms(void)
{
    static UINT16 J1939_Angle_Brodcast_Count = 0;
    static UINT16 J1939_Acceleration_Brodcast_Count = 0;
    UINT8 SAE_J1939BrodcastData[8]= {0xff};
    UINT8 i,j = 0;
    UINT32 temp = 0;
    INT16  Roll_Angle_Output_temp;
    INT16  Pitch_Angle_Output_temp;
    INT16  X_acc_temp;
    
    if((VAL_SAEJ1939_Broadcast_En == ENABLED)&&(Task_Enable == TRUE))    
    {
    
        // J1939_RollAng_output  V = Q * 0.002 - 64; -64 ~ +64.51
        // RollAng_output Q = V * 100;  Q -6400~+6451
        if(Roll_Angle_Output >= 6451) 
        {
            Roll_Angle_Output_temp = 6451;
        } 
        else if(Roll_Angle_Output <= -6400)
        {
            Roll_Angle_Output_temp = -6400;
        } 
        else
        {
            Roll_Angle_Output_temp = Roll_Angle_Output;
        }
        if(Pitch_Angle_Output >= 6451) 
        {
            Pitch_Angle_Output_temp = 6451;
        } 
        else if(Pitch_Angle_Output <= -6400)
        {
            Pitch_Angle_Output_temp = -6400;
        } 
        else
        {
            Pitch_Angle_Output_temp = Pitch_Angle_Output;
        }
        J1939_RollAng_output = (UINT16)((INT32)(Roll_Angle_Output_temp + 6400)*5); 
        J1939_PitchAng_output = (UINT16)((INT32)(Pitch_Angle_Output_temp + 6400)*5);

        // J1939_Longitudinal_Acc_output V = Q * 0.1 - 12.5     -12.5~+12.5
        // Y_acc  Q = V * 100
        if(X_acc >= 1250) 
        {
            X_acc_temp = 1250;
        } 
        else if(X_acc <= -1250)
        {
            X_acc_temp = -1250;
        } 
        else
        {
            X_acc_temp = X_acc;
        }
        J1939_Longitudinal_Acc_output = (UINT8)((INT32)(X_acc_temp + 1250)/10);

  
        J1939_Angle_Brodcast_Count++;
        if(J1939_Angle_Brodcast_Count == HLS_Angle_Broadcast_Rate)
        {
            // spn 3318    pgn 61459    intel类型
            J1939_Angle_Brodcast_Count = 0;
            SAE_J1939BrodcastData[0] =(UINT8)(J1939_PitchAng_output);
            SAE_J1939BrodcastData[1] =(UINT8)(J1939_PitchAng_output>>8);
            // spn 3319    pgn 61459    intel类型
            SAE_J1939BrodcastData[2] =(UINT8)(J1939_RollAng_output);
            SAE_J1939BrodcastData[3] =(UINT8)(J1939_RollAng_output>>8);
            
            CAN_Tx_Data(0,0,HLS_Angle_Broadcast_FrameType,HLS_Angle_Broadcast_CANID,&SAE_J1939BrodcastData,8);  
            for(i=0;i<8;i++)
              SAE_J1939BrodcastData[i]= 0xff;
        }
        
        J1939_Acceleration_Brodcast_Count++;
        if(J1939_Acceleration_Brodcast_Count == VAL_Acceleration_Broadcast_Rate)
        {
            // spn 1810    pgn 61449      intel类型
            J1939_Acceleration_Brodcast_Count = 0;
            SAE_J1939BrodcastData[7] =(UINT8)(J1939_Longitudinal_Acc_output);
            
            CAN_Tx_Data(0,0,HLS_Acceleration_Broadcast_FrameType,HLS_Acceleration_Broadcast_CANID,&SAE_J1939BrodcastData,8);  
            for(i=0;i<8;i++)
              SAE_J1939BrodcastData[i]= 0xff;
        }
    }
}




