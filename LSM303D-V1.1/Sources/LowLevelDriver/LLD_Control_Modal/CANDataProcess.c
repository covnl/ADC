/*******************************************************************************/
/**
Copyright (c) 2014 COMPANY_ECOTRONS
\file       CAN.c
\brief      Init CAN 
\author     COMPANY_GC
\version    1.0
\date       Oct/ 2014
*/
/*******************************************************************************/
#include "typedefs.h"


#define START_SECTION_DataBufferRAM
#include "pragma.h"

extern CAN_Message Tx_CAN_Frame[];
extern CAN_Message Rx_CAN_Frame[];
extern UINT8 CAN_RxDataBuf_Index; 
extern UINT8 CAN_TxDataBuf_Index; 

#define STOP_SECTION_DataBufferRAM
#include "pragma.h"


/*****************************************************
** 
* \brief    CAN Interrupt receive.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/     
void CAN_RxDataProcess_r1ms(void)
{
    UINT8 DataEmpty,i;
    UINT32 RxID;
    for(DataEmpty=0;DataEmpty<CAN_RxBufMx;DataEmpty++)
    {
        if(Rx_CAN_Frame[DataEmpty].RxFull == TRUE)
        {
            RxID = Rx_CAN_Frame[DataEmpty].ID;    
                        
            if(RxID == HLS_CCP_RxID)
            {
                for(i=0;i<8;i++)
                {
                   g_stCCP.pubCANReceive[i] = Rx_CAN_Frame[DataEmpty].Data[i];    	
                }
                CCP_vCommandProcess();
            }
            else if(RxID == HLS_UAVCAN_RxID)
            {
            }
            else if(RxID == HLS_WBO2_CAN_RxID)
            {
                ALMBroadcastData_Process(DataEmpty);
            }
            else
            {
            }
            
         for(i=0;i<8;i++)
         {
             Rx_CAN_Frame[DataEmpty].Data[i] = 0;
         }
         Rx_CAN_Frame[DataEmpty].ID = 0;
         Rx_CAN_Frame[DataEmpty].RxFull = FALSE;
       }
    }     
}


  
void ALMBroadcastData_Process(UINT8 DateIndex)
{
    UINT16 ALM_RxO2,ALM_RxLambda,ALM_RxTemperature,ALM_RxPWM_Duty;
    UINT8  ALM_RxDTC; 
    INT32 temp;
    
    ALM_RxO2 = (((UINT16)Rx_CAN_Frame[DateIndex].Data[1])<<8)+(Rx_CAN_Frame[DateIndex].Data[0]);
    ALM_RxLambda = (((UINT16)Rx_CAN_Frame[DateIndex].Data[3])<<8)+(Rx_CAN_Frame[DateIndex].Data[2]);
    ALM_RxTemperature = (((UINT16)Rx_CAN_Frame[DateIndex].Data[5])<<8)+(Rx_CAN_Frame[DateIndex].Data[4]);
    ALM_RxPWM_Duty =(((UINT16)Rx_CAN_Frame[DateIndex].Data[6]&0xf0)<<4)+Rx_CAN_Frame[DateIndex].Data[7];
    ALM_RxDTC =  Rx_CAN_Frame[DateIndex].Data[6]&0x0f; 
    
    temp = (INT32)ALM_RxO2*10/19 - 12288;
    ALM_Lambda_FromCAN = ALM_RxLambda;
    ALM_lsuTemp_FromCAN = ALM_RxTemperature;
    ALM_lsuDTC_FromCAN = ALM_RxDTC;
    ALM_lsuO2_FromCAN = (INT16)(temp*1000/3125); //需要转换定标 A2L中  Q=V*327.68  定标相互转换 Q = (V+12.000000)/0.000514
    ALM_lsuHtDtcy_FromCAN = ALM_RxPWM_Duty;
}
  
  
  
  
  
  
  
  
  
  
  

