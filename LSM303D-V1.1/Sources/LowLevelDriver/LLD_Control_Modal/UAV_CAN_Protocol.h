#ifndef __UAV_CAN_Protocol_H
#define __UAV_CAN_Protocol_H


//========struct =====================
typedef struct {
	UINT32 DataTypeID : 10;		  // 
	UINT32 TransferType : 2;		// 
	UINT32 SourceNodeID : 7;		// 
	UINT32 FrameIndex : 6;	  	// 
	UINT32 LastFrame : 1;		    // 
	UINT32 TransferID : 3;		    // 
}UAVCAN_FrameFormat;




//========define==========================
#define TT_ServiceResponse  0
#define TT_ServiceRequses   1
#define TT_MessageBroadcast 2
#define TT_MessageUnicast   3

#define LF_ExpectMoreFrames  0
#define LF_LastFrame         1


//========function========================
void UAV_CAN_Protocol_Init(void);
void UAVCAN_MessageCollection_r10ms(void);
void UAVCAN_MessageCollection_Syn(void);
UAVCAN_FrameFormat UAVCAN_AnalyzeID(UINT32 CAN_ID);
void UAVCAN_Broadcast_DataTpeID_768(void);
void UAVCAN_Broadcast_DataTpeID_769(void);
void UAVCAN_Broadcast_DataTpeID_770(void);
void UAVCAN_Broadcast_DataTpeID_771(void);
void UAVCAN_Broadcast_DataTpeID_772(void);
void UAVCAN_Broadcast_DataTpeID_773(void);
void UAVCAN_Broadcast_DataTpeID_774(void);







#endif