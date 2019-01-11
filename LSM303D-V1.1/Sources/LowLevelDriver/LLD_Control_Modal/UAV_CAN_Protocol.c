#include "typedefs.h"
/*****************************************************************
Message publication - one transfer, either unicast or broadcast.

Data Type ID  = 768-800 (ECOTRONS specific message)
Transfer Type = 2（Message broadcast）
Source Node ID = 1
Frame Index = 0
Last Frame = 1（Current frame is the last frame）
Transfer ID = 0

-----------------------------------------------------------------
Service invocation - two subsequent unicast transfers: 
"	From caller to server, i.e., request. 
"	From server to caller, i.e., response. 

Data Type ID  = 101(Calibration command for ECOTRONS's EFI system)
Transfer Type = 0 - 1
Source Node ID = 1
Frame Index = 0 - 62
Last Frame = 0 - 1
Transfer ID = 0


******************************************************************/
#define START_SECTION_DataBufferRAM
#include "pragma.h"

UAVCAN_FrameFormat UAVCAN_Rx_ID;
UAVCAN_FrameFormat UAVCAN_MessagePubliction_ID;
UAVCAN_FrameFormat UAVCAN_ServiceInvocation_ID;
//----------------
UINT16 J1939_N;        //2 bytes
UINT8  J1939_Tps;      //1 bytes
UINT8  J1939_Baro;     //1 bytes
UINT8  J1939_Load;     //1 bytes
//----------------
UINT16 J1939_tInj0;    //2 bytes
UINT16 J1939_tInj1;    //2 bytes
UINT16 J1939_IgaOut;   //2 bytes
UINT8 J1939_tDwl;      //1 bytes
UINT8  J1939_Map;      //1 bytes
//----------------
UINT8  J1939_Tm;       //1 bytes
UINT8  J1939_Ta;       //1 bytes
UINT16 J1939_UbAdc;    //2 bytes
UINT8  J1939_B_StaEnd;  //1 bytes
UINT16 J1939_O2;    //2 bytes
UINT8  J1939_B_CrkErr;  //1 bytes

extern CAN_Message Tx_CAN_Frame[];
extern CAN_Message Rx_CAN_Frame[];
extern UINT8 CAN_RxDataBuf_Index; 
extern UINT8 CAN_TxDataBuf_Index; 

#define STOP_SECTION_DataBufferRAM
#include "pragma.h"



/**************************************************************
** Init
** MessagePubliction只有Data Type ID是可变的
**************************************************************/
void UAV_CAN_Protocol_Init(void)
{    
    UAVCAN_MessagePubliction_ID.TransferType = 2;
    UAVCAN_MessagePubliction_ID.SourceNodeID = 1;
    UAVCAN_MessagePubliction_ID.FrameIndex = 1;
    UAVCAN_MessagePubliction_ID.LastFrame = 1;
    UAVCAN_MessagePubliction_ID.TransferID = 0;
}

/**************************************************************
** 将UAV CAN的ID打包成CAN ID发送
**
**************************************************************/
UINT8 UAVCAN_ReadIdleTxBuffer(void)
{
    UINT8 idle_index =0;
    for(idle_index=0;idle_index<CAN_TxBufMx;idle_index++)
    {
        if(Tx_CAN_Frame[idle_index].TxComplete == FALSE)return idle_index;
    }
    
    return CAN_TxBufMx;
}

/**************************************************************
** 将UAV CAN的ID打包成CAN ID发送
**
**************************************************************/
UINT32 UAVCAN_PackageID(UAVCAN_FrameFormat uavcan_id)
{
    UINT32 rt_id;
    rt_id = ((UINT32)uavcan_id.DataTypeID << 19)
           | ((UINT32)uavcan_id.TransferType << 17)
           | ((UINT32)uavcan_id.SourceNodeID << 10)
           | ((UINT32)uavcan_id.FrameIndex << 4)
           | ((UINT32)uavcan_id.LastFrame << 3)
           | ((UINT32)uavcan_id.TransferID );
    return rt_id;       
}
/**************************************************************
**将CAN ID解析成UAV CAN的ID
**
**************************************************************/
UAVCAN_FrameFormat UAVCAN_AnalyzeID(UINT32 CAN_ID)
{
    UAVCAN_FrameFormat UAVCAN_Rec_ID;
    
    UAVCAN_Rec_ID.DataTypeID = (CAN_ID & 0x1FF80000)>>19;    //0b0001 1111 1111 1000 0000 0000 0000 0000
    UAVCAN_Rec_ID.TransferType = (CAN_ID & 0x60000)>>17;     //0b0000 0000 0000 0110 0000 0000 0000 0000
    UAVCAN_Rec_ID.SourceNodeID = (CAN_ID & 0x1FC00)>>10;     //0b0000 0000 0000 0001 1111 1100 0000 0000
    UAVCAN_Rec_ID.FrameIndex = (CAN_ID & 0x3F0)>>4;          //0b0000 0000 0000 0000 0000 0011 1111 0000
    UAVCAN_Rec_ID.LastFrame = (CAN_ID & 0x08)>>3;            //0b0000 0000 0000 0000 0000 0000 0000 1000
    UAVCAN_Rec_ID.TransferID = (CAN_ID & 0x07)>>3;           //0b0000 0000 0000 0000 0000 0000 0000 0111
    
    return  UAVCAN_Rec_ID;
}

/**************************************************************
**将应用层的变量按照J1939协议定标进行转换
**
**************************************************************/
void UAVCAN_ConvertParameters_r10ms(void)
{
    UINT32 J1939_N_Temp;
    UINT16 T_temp;
    //-----Data Type ID 768-----------    
    J1939_B_StaEnd = HLS_B_StaEnd;               //HLS_B_StaEnd:Q = V ; J1939_B_StaEnd:Q = V
    J1939_B_CrkErr = HLS_B_CrkErr;               //HLS_B_CrkErr:Q = V ; J1939_B_CrkErr:Q = V
    J1939_Load = (UINT8)(((UINT32)HLS_Load *1536)>>16);  //HLS_Load:Q = V*42.666667 ; J1939_Load:Q = V;
    
    J1939_N_Temp = (UINT32)HLS_EngineSpeed * 2;  //HLS_EngineSpeed:Q = V*4 ; J1939_N:Q = V*8
    if(J1939_N_Temp >65535)
    {
        J1939_N = 65535;
    }
    else
    {
        J1939_N = J1939_N_Temp;
    }
    //-----Data Type ID 769-----------    
    J1939_Tps = (UINT8)(HLS_TPS / 262);    //HLS_TPS:Q = V*655.36 ; J1939_Tps:Q = V*2.5
    //-----Data Type ID 770-----------
    if(HLS_Baro<32000) 
    {
        J1939_Baro = (UINT8)((UINT32)HLS_Baro / 128);  //HLS_Baro:Q = V*25.6 hpa; J1939_Baro:Q = V*2  kpa
    }
    else
    {
        J1939_Baro = 250;
    }
    //-----Data Type ID 771----------- 
    J1939_tInj0 = HLS_tInj0;                //HLS_tInj0:Q = V*1000 ; J1939_tInj0:Q = V*1000
    J1939_tInj1 = HLS_tInj1;                //HLS_tInj1:Q = V*1000 ; J1939_tInj1:Q = V*1000
    J1939_IgaOut = (UINT16)HLS_IgaOut*96+25600;   //HLS_IgaOut:Q = V*1.333333 ; J1939_IgaOut:Q = (V + 200)*128
    J1939_tDwl = HLS_tDwl;                  //HLS_tDwl:Q = V*10 ; J1939_tDwl:Q = V*10
    //-----Data Type ID 772-----------
    J1939_Map = (UINT8)((UINT32)HLS_Map/512);  //HLS_Map:Q = V*25.6 hpa; J1939_Map:Q = V*0.5 kpa
    
    T_temp = (UINT16)HLS_Ta*5/4;                    //HLS_Ta:Q = (V+40)/1.25 ; J1939_Ta:Q = V+40
    if(T_temp >= 255)
    {
        J1939_Ta = 255;
    } 
    else 
    {
        J1939_Ta = T_temp; 
    }      
              
    //-----Data Type ID 773-----------
    T_temp = (UINT16)HLS_Tm*5/4;                               //HLS_Tm:Q = (V+40)/1.25 ; J1939_Tm:Q = V+40
    if(T_temp >= 255)
    {
        J1939_Tm = 255;
    } 
    else 
    {
        J1939_Tm = T_temp; 
    }
    
    //-----Data Type ID 774-----------
    J1939_O2 = HLS_LamO2_FromCAN;       //HLS_LamO2_FromCAN:Q = (V+12)/0.000514 ; J1939_Lambda:Q = (V+12)/0.000514
    J1939_UbAdc = HLS_BatteryVol / 8;            //HLS_BatteryVol:Q = V*160 ; J1939_UbAdc:Q = V*20    
}

/**************************************************************
** Data Type ID = 768
** B_StaEnd / B_CrkErr / LOAD / Engine Speed
** Rate:syn
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_768(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 1)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 0;// syn
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 768;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = J1939_B_StaEnd;
        Tx_CAN_Frame[local_index].Data[1] = J1939_B_CrkErr;
        Tx_CAN_Frame[local_index].Data[2] = J1939_Load;
        Tx_CAN_Frame[local_index].Data[3] = (UINT8)J1939_N;  
        Tx_CAN_Frame[local_index].Data[4] = (UINT8)(J1939_N>>8); 
        Tx_CAN_Frame[local_index].Data[5] = 0;
        Tx_CAN_Frame[local_index].Data[6] = 0;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}

/**************************************************************
** Data Type ID = 769
** Engine Throttle Position
** Rate:100ms
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_769(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 10)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 20;//20*5 =100ms
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 769;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = 0;
        Tx_CAN_Frame[local_index].Data[1] = 0;
        Tx_CAN_Frame[local_index].Data[2] = 0;
        Tx_CAN_Frame[local_index].Data[3] = 0;  
        Tx_CAN_Frame[local_index].Data[4] = 0; 
        Tx_CAN_Frame[local_index].Data[5] = 0;
        Tx_CAN_Frame[local_index].Data[6] = J1939_Tps;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}

/**************************************************************
** Data Type ID = 770
** Barometric Pressure
** Rate:1000ms
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_770(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 100)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 200;//200*5 =1000ms
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 770;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = J1939_Baro;
        Tx_CAN_Frame[local_index].Data[1] = 0;
        Tx_CAN_Frame[local_index].Data[2] = 0;
        Tx_CAN_Frame[local_index].Data[3] = 0;  
        Tx_CAN_Frame[local_index].Data[4] = 0; 
        Tx_CAN_Frame[local_index].Data[5] = 0;
        Tx_CAN_Frame[local_index].Data[6] = 0;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}

/**************************************************************
** Data Type ID = 771
** IgaOut / tDwl / tInj0 / tInj1
** Rate:syn
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_771(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 1)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 0;// syn
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 771;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = (UINT8)J1939_IgaOut;
        Tx_CAN_Frame[local_index].Data[1] = (UINT8)(J1939_IgaOut>>8);
        Tx_CAN_Frame[local_index].Data[2] = J1939_tDwl;
        Tx_CAN_Frame[local_index].Data[3] = 0;  
        Tx_CAN_Frame[local_index].Data[4] = (UINT8)J1939_tInj0; 
        Tx_CAN_Frame[local_index].Data[5] = (UINT8)(J1939_tInj0>>8);
        Tx_CAN_Frame[local_index].Data[6] = (UINT8)J1939_tInj1;
        Tx_CAN_Frame[local_index].Data[7] = (UINT8)(J1939_tInj1>>8);
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}

/**************************************************************
** Data Type ID = 772
** Map / Ta
** Rate:500ms
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_772(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 50)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 100;// 100*5 = 500ms
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 772;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = 0;
        Tx_CAN_Frame[local_index].Data[1] = J1939_Map;
        Tx_CAN_Frame[local_index].Data[2] = J1939_Ta;
        Tx_CAN_Frame[local_index].Data[3] = 0;  
        Tx_CAN_Frame[local_index].Data[4] = 0; 
        Tx_CAN_Frame[local_index].Data[5] = 0;
        Tx_CAN_Frame[local_index].Data[6] = 0;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}


/**************************************************************
** Data Type ID = 773
** Tm
** Rate:1000ms
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_773(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 100)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 200;// 200*5 = 1000ms
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 773;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = J1939_Tm;
        Tx_CAN_Frame[local_index].Data[1] = 0;
        Tx_CAN_Frame[local_index].Data[2] = 0;
        Tx_CAN_Frame[local_index].Data[3] = 0;  
        Tx_CAN_Frame[local_index].Data[4] = 0; 
        Tx_CAN_Frame[local_index].Data[5] = 0;
        Tx_CAN_Frame[local_index].Data[6] = 0;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}


/**************************************************************
** Data Type ID = 774
** UbAdc / Aftertreatment 1 Outlet %O2
** Rate:50ms
**************************************************************/
void UAVCAN_Broadcast_DataTpeID_774(void)
{
    static UINT8 Inc_cnt = 0;
    UINT8 local_index;
    UINT32 local_ID;
    
    Inc_cnt++;
    if(Inc_cnt >= 5)
    {
        Inc_cnt = 0;
        local_index = UAVCAN_ReadIdleTxBuffer();
        if(local_index >= CAN_TxBufMx)return;
        Tx_CAN_Frame[local_index].TxComplete = TRUE;
        Tx_CAN_Frame[local_index].TxRate = 10;// 10*5 = 50ms
        //-------------------------------------------
        UAVCAN_MessagePubliction_ID.DataTypeID = 774;
        local_ID = UAVCAN_PackageID(UAVCAN_MessagePubliction_ID);
        Tx_CAN_Frame[local_index].ID = local_ID;
        Tx_CAN_Frame[local_index].Data[0] = 0;
        Tx_CAN_Frame[local_index].Data[1] = 0;
        Tx_CAN_Frame[local_index].Data[2] = (UINT8)J1939_O2;;
        Tx_CAN_Frame[local_index].Data[3] = (UINT8)(J1939_O2>>8);  
        Tx_CAN_Frame[local_index].Data[4] = (UINT8)J1939_UbAdc; 
        Tx_CAN_Frame[local_index].Data[5] = (UINT8)(J1939_UbAdc>>8);
        Tx_CAN_Frame[local_index].Data[6] = 0;
        Tx_CAN_Frame[local_index].Data[7] = 0;
        Tx_CAN_Frame[local_index].TxLength = 8;
        Tx_CAN_Frame[local_index].TxFrameType = Ext_Frame;  
    }
}

/**************************************************************
** 数据采集
** Rate:10ms
** 所有基于时间的数据采集
**************************************************************/
void UAVCAN_MessageCollection_r10ms(void)
{
    /*UAVCAN_ConvertParameters_r10ms();
    UAVCAN_Broadcast_DataTpeID_769();
    UAVCAN_Broadcast_DataTpeID_770();
    UAVCAN_Broadcast_DataTpeID_772();
    UAVCAN_Broadcast_DataTpeID_773();
    UAVCAN_Broadcast_DataTpeID_774();*/
}

/**************************************************************
**数据采集
**Rate: Syn
**************************************************************/
void UAVCAN_MessageCollection_Syn(void)
{
    /*UAVCAN_Broadcast_DataTpeID_768();
    UAVCAN_Broadcast_DataTpeID_771();*/    
}




