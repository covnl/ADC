#include "typedefs.h"


#define START_SECTION_DataBufferRAM
#include "pragma.h"


CAN_Message Tx_CAN_Frame[CAN_TxBufMx];
CAN_Message Rx_CAN_Frame[CAN_RxBufMx];
UINT8 CAN_RxDataBuf_Index; 
UINT8 CAN_TxDataBuf_Index; 

#define STOP_SECTION_DataBufferRAM
#include "pragma.h"

UINT8  CAN_TxLength = 0;
UINT32 CAN_TxID;
UINT8  *CAN_TxData;
UINT8  CAN_TxFrameType;
UINT8  CAN_BufferEmpty_Flag = 0;
UINT8  CAN_RxDataLength = 0;
UINT8  CAN_RxData[10][13] = {0};
UINT8  CAN_Tx_TimeOut;
UINT8  CAN_RecData[13] = {0};
UINT8  E_CAN_Rx;
UINT32 HLS_CCP_RxID ;          
UINT32 HLS_UAVCAN_RxID ;       
UINT32 HLS_WBO2_CAN_RxID ;      







/*****************************************************
** 
* \brief    CAN Init.
* \author   Engineer
* \param    CAN receive ID
* \return   void
* \todo
**
*****************************************************/
void CANBUS_Init(void) 
{
  #ifdef CAN_MODULE_ENABLE
     CAN_Init(0x100,0xcff0001);   
  #endif  
    HLS_CCP_RxID = VAL_CCP_RxID;
    HLS_UAVCAN_RxID = VAL_UAVCAN_RxID;
    HLS_WBO2_CAN_RxID = VAL_WBO2_CAN_RxID; 
}

/*****************************************************
** 
* \brief    CAN Send Data.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void CAN_Tx_Data(UINT8 Channel,UINT8 TxStatus,UINT8 FrameType,UINT32 TxID,UINT8 *DataPtr,UINT8 TxLen)
{
  if(TxStatus == 0)
  {
       switch(Channel)
       {
            case 0:
               CAN_TxData_Polling(TxLen,DataPtr,TxID,FrameType);
            break;
            case 1:
            break;
            
            default:
            break;
       }
  }
  else
  {
       switch(Channel)
       {
            case 0:
                CAN_TxID = TxID;
                CAN_TxLength = TxLen;
                CAN_TxData = DataPtr;
                CAN_TxFrameType = FrameType; 
                CAN_TxData_Interrupt();
            break;
            case 1:
            break;
            
            default:
            break;
       }
  }
  
}
/*****************************************************
** 
* \brief    CAN Init.
* \author   Engineer
* \param    CAN receive ID
* \return   void
* \todo
**
*****************************************************/
void CAN_Init(UINT16 RxStaID,UINT32 RxExtID)
{
    UINT16 TimeOut_Ctr;
    TimeOut_Ctr = 0;
    CAN_Tx_TimeOut = 0;
    
    CAN_INITRQ=ENABLED;                 //进入初始化
    while(CAN_INITACK==0) 
    {
        TimeOut_Ctr++;
        if(TimeOut_Ctr > 30000) return;  
    }                                 //等待应答信号
    CLR_CANRFLG();                        //清除标志位，该寄存器标志位只能由软件清除
    SET_CANCTL1(0xC0);                  // CAN0_LISTEN=DISABLED;CAN0_CLKSRC=BUSCLOCK; CAN0_EN=ENABLED
                                         //CTL1一定要整体赋值，不要分开赋值，否则会产生在BDM下工作正常
                                         //单独加电掉入死循环的情况
    CAN_UpdateCANBaud(VAL_CAN0_BaudRate); 
    SET_CANIDAC(0x00);    //2个32位的验收滤波器
    CAN_SetIDMaskFilter(RxStaID,RxExtID);
    
    SET_CANIDMR0(0x01);   
    SET_CANIDMR1(0xf7);  //不校验ID 4-0   标准帧
    
    SET_CANIDMR4(0x00);
    SET_CANIDMR5(0x00);
    SET_CANIDMR6(0x00);
    SET_CANIDMR7(0x00);  //  扩展帧
    CAN_INITRQ=DISABLED;                //退出初始化模式
    TimeOut_Ctr = 0;
    while(CAN_INITACK==1) 
    {
        TimeOut_Ctr++;
        if(TimeOut_Ctr > 30000) return;    
    }                         //等待应答信号
    SET_CANCTL0(0x00);
    ENABLED_CANRXFIE;                   //产生接收器中断请求
    DISABLED_CANTXEIE;
    
    
 
}

void CAN_ModelDisabled(void)
{
    UINT16 TimeOut_Ctr;
    TimeOut_Ctr = 0;
    
    CAN_INITRQ=ENABLED;
    DISABLED_CANTXEIE; 
    DISABLED_CANRXFIE;
    while(CAN_INITACK==0) 
    {
        TimeOut_Ctr++;
        if(TimeOut_Ctr > 30000) return;  
    }  
    SET_CANCTL1(0x40);
       
}

/*****************************************************
** 
* \brief    CAN Send Data.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void CAN_TxData_Polling(UINT8 TxLen,UINT8 *DataPtr,UINT32 TxID,UINT8 FrameType)
{
    UINT8 *tx_buf_ptr;   
    UINT8 index = 1;
    UINT16 Wait_Count =0;
    UINT8 i;
    index = 1;
    
    while(index && CAN_Tx_TimeOut<5)   
    {
        Wait_Count++;
        if(Wait_Count>2000)
        {
            CAN_Tx_TimeOut++;
            return;
        }
        if(CAN_TxBufferEmpty & CAN_TXE0)
          { 
             CAN_CANTBSEL = CAN_TxBufferEmpty;
             CAN_BufferEmpty_Flag = CAN_TXE0;
             tx_buf_ptr = &CAN_Tx_Data0;
             index = 0;
          
          }

          else if(CAN_TxBufferEmpty & CAN_TXE1)
          {   
             CAN_CANTBSEL = CAN_TxBufferEmpty;
             CAN_BufferEmpty_Flag = CAN_TXE1;
             tx_buf_ptr = &CAN_Tx_Data0;
             index = 0;
          }
          else if(CAN_TxBufferEmpty & CAN_TXE2)
          {
             CAN_CANTBSEL = CAN_TxBufferEmpty;
             CAN_BufferEmpty_Flag = CAN_TXE2;
             tx_buf_ptr = &CAN_Tx_Data0;
             index = 0;
          } 
    }
    CAN_ConvertTxIDToRegister(TxID,FrameType);
     
    for(i=0;i<TxLen;i++)
    {
      *tx_buf_ptr++ = *DataPtr++;
    }
    CAN_Tx_Length = TxLen;
    CAN_Tx_Prio = 7;
    
    CAN_TxBufferEmpty &= CAN_BufferEmpty_Flag;
   
    
      
} 

/*****************************************************
** 
* \brief    CAN Send Data.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void CAN_TxData_Interrupt(void)
{   
    UINT8 index = 1;
    UINT16 Wait_Count =0;
    index = 1;
    
     while(index)   
     {
        Wait_Count++;
        if(Wait_Count>2000)
          return;
        if(CAN_TxBufferEmpty & CAN_TXE0)
        { 
           CAN_CANTBSEL = CAN_TXE0;
           CAN_BufferEmpty_Flag = CAN_TXE0;
           ENABLED_CANTXEIE(CAN_TXE0);
           index = 0;
        }

        else if(CAN_TxBufferEmpty & CAN_TXE1)
        {   
           CAN_CANTBSEL = CAN_TXE1;
           CAN_BufferEmpty_Flag = CAN_TXE1;
           ENABLED_CANTXEIE(CAN_TXE1);
           index = 0;
        }
        else if(CAN_TxBufferEmpty & CAN_TXE2)
        {
           CAN_CANTBSEL = CAN_TXE2;
           CAN_BufferEmpty_Flag = CAN_TXE2;
           ENABLED_CANTXEIE(CAN_TXE2);
           index = 0;
        }
    }        
}

/*****************************************************
** 
* \brief    Set CAN ID.
* \author   Engineer
* \param    Receive CAN ID
* \return   void
* \todo
**
*****************************************************/
void CAN_SetIDMaskFilter(UINT16 RxStaID,UINT32 RxExtID)
{
    SET_CANIDAR0() = (UINT8)(RxStaID >> 3);
    SET_CANIDAR1() = (UINT8)((RxStaID & 0x07) << 5);
     
    SET_CANIDAR4() = (UINT8)(RxExtID>>21); //21-28
    SET_CANIDAR5() = ((((UINT8)(RxExtID>>18))<<5) | (((UINT8)(RxExtID>>15))&0x07))|0x18; 
    SET_CANIDAR6() = (UINT8)(RxExtID>>7); //7--14
    SET_CANIDAR7() = (UINT8)(RxExtID<<1); //0-6
}

/*****************************************************
** 
* \brief    Set CAN ID.
* \author   Engineer
* \param    Receive CAN ID
* \return   void
* \todo
**
*****************************************************/
void CAN_ConvertTxIDToRegister(UINT32 TxID,UINT8 FrameType)
{
    UINT32  ID_Convert_buf=0;
    if(FrameType==1)
    {
       ID_Convert_buf = TxID << 3;
       ID_Convert_buf = ID_Convert_buf & 0xFFE00000;    //取扩展帧ID28-18位
       ID_Convert_buf = ID_Convert_buf | 0x00180000;    //设置SRR、IDE位
       ID_Convert_buf = ID_Convert_buf + ((TxID & 0x0003FFFF)<<1); // 取扩展帧ID17-0位
       ID_Convert_buf = ID_Convert_buf & 0xFFFFFFFE;     //设置RTR位
       
       CAN_Tx_Id0 = (UINT8)(ID_Convert_buf>>24);
       CAN_Tx_Id1 = (UINT8)(ID_Convert_buf>>16);
       CAN_Tx_Id2 = (UINT8)(ID_Convert_buf>>8);
       CAN_Tx_Id3 = (UINT8)(ID_Convert_buf);       
    }
    else
    {
       ID_Convert_buf = TxID << 5;         //取标准帧ID
       ID_Convert_buf = ID_Convert_buf & 0x0000FFE0;     //设置RTR、IDE位
       
       CAN_Tx_Id0 = (UINT8)(ID_Convert_buf>>8);
       CAN_Tx_Id1 = (UINT8)(ID_Convert_buf);
       CAN_Tx_Id2 = 0;
       CAN_Tx_Id3 = 0;
    } 
}   

/*****************************************************
** 
* \brief    CAN send ID.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/              
UINT32 CAN_ConvertRxRegisterToID(UINT8 RxID0,UINT8 RxID1,UINT8 RxID2,UINT8 RxID3)
{
    UINT32 Temp_RxId;
    UINT32 temp1, temp2, temp3, temp4;
    if((RxID1&0x08)== 0)//VAL_Sel_StandardFrame
    {
        Temp_RxId=RxID0;
        Temp_RxId<<=3;
        Temp_RxId+=(RxID1>>5);   
    }
    else
    {
        temp1 = RxID3>>1; // 0--6    total 7 bit
        temp2 = RxID2;  //7--14   total 8 bit
        temp3 = (((RxID1&0xe0)>>2)+(RxID1&0x07)); //15-20   total 6 bit
        temp4 = RxID0;//21-28   total 8 bit
        Temp_RxId = temp4<<21 | temp3<<15 | temp2<<7 | temp1; 
    }    
    return  Temp_RxId;
}

/*****************************************************
** 
* \brief    Updata CAN Baud.
* \author   Engineer
* \param    void
* \return   void
* \todo     1M 500k 250k 125k 100k 50k
**
*****************************************************/   
void CAN_UpdateCANBaud(UINT8 Baud_Sel)
{
    switch(Baud_Sel)
    {
      case CAN_Baud_1M: 
          {
              SET_CANBTR0(0x83); 	   //SJW = 4, prescale = 3    32/(3+1)=8M
              SET_CANBTR1(0x32);	// Tseg2 = 4, Tseg1 = 3       8/(4+3+1)=1M
          }
      break;
      
      case CAN_Baud_800k: 
          {
              SET_CANBTR0(0x83); 	   //SJW = 4, prescale = 3    32/(3+1)=8M
              SET_CANBTR1(0x34);	// Tseg2 = 4, Tseg1 = 5       8/(4+5+1)=800K
          }
      break;
      case CAN_Baud_500k: 
          {
              SET_CANBTR0(0x83); 	   //SJW = 4, prescale = 3    32/(3+1)=8M
              SET_CANBTR1(0x3A);	// Tseg2 = 4, Tseg1 = 11      8/(4+11+1)=500K
          }
      break;
      
      case CAN_Baud_250k: 
          {
              SET_CANBTR0(0x87); 	   //SJW = 4, prescale = 7    32/(7+1)=4M
              SET_CANBTR1(0x3A);	// Tseg2 = 4, Tseg1 = 11      4/(4+11+1)=250K
          }
      break;
      
      case CAN_Baud_125k: 
          {        
              SET_CANBTR0(0x8F); 	   //SJW = 4, prescale = 15   32/(15+1)=2M
              SET_CANBTR1(0x3A);	// Tseg2 = 4, Tseg1 = 11      2/(4+11+1)=125k
          }
      break;
      
      case CAN_Baud_100k: 
          {
              SET_CANBTR0(0x8F); 	   //SJW = 4, prescale = 15   32/(15+1)=2M
              SET_CANBTR1(0x5C);	// Tseg2 = 6, Tseg1 = 13      2/(6+13+1)=100k
          }
      break;
      
      case CAN_Baud_50k: 
          {
              SET_CANBTR0(0x9F); 	   //SJW = 4, prescale = 31    32/(31+1)=1M
              SET_CANBTR1(0x5C);	// Tseg2 = 6, Tseg1 = 13       1/(6+13+1)=50k
          }
      break;

      default:      //500k
          {
              SET_CANBTR0(0x83); 	   //SJW = 4, prescale = 3     32/(3+1)=8M
              SET_CANBTR1(0x3A);  // Tseg2 = 4, Tseg1 = 11      8/(4+11+1)=500K
          }
      break;

    }
}

/*****************************************************
** 
* \brief    CAN Interrupt Tx process.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/


void CAN_Tx_Process_r1ms (void)
{
    UINT8 i;
    if((CAN_TXEIE & 0x03) == 0)
    {
        for(i=0;i<CAN_TxBufMx;i++)
        {
            if(Tx_CAN_Frame[i].TxComplete == TRUE)
            {
                ENABLED_ALL_CANTXEIE;
            }
        }
    }
}



//======================================================
#pragma CODE_SEG __NEAR_SEG NON_BANKED
/*****************************************************
** 
* \brief    CAN Interrupt.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void interrupt CAN_Rx_Isr(void) 
{
    static UINT8 DataEmpty;
    UINT8 i,n;
    UINT8 * addr;
    UINT32 RecID;
    
    addr=(UINT8 *)&CAN_Rx_Id0;
    for(i=0;i<12;i++)      //先接收数据
    {
       CAN_RecData[i]=addr[i];
    }
    CAN_RecData[12] = CAN_Rx_Length;
    
    RecID = CAN_ConvertRxRegisterToID(CAN_RecData[0],CAN_RecData[1],CAN_RecData[2],CAN_RecData[3]);
    
    if(RecID == HLS_CCP_RxID);
    //else if(RecID == VAL_UAVCAN_RecID);
    //else if(RecID == VAL_CCP_RecID);
    else
    {
        CLR_CANRFLG();
        return;  //如果都不是，那么不存储数据，直接返回 
    }
    
    for(i=0;i<12;i++)
    {
        if(DataEmpty>=12) DataEmpty = 0;
        if(Rx_CAN_Frame[DataEmpty].RxFull == FALSE)
        {
            Rx_CAN_Frame[DataEmpty].ID = RecID;
            for(n=0;n<8;n++)
            {
                Rx_CAN_Frame[DataEmpty].Data[n] = CAN_RecData[n+4];
            }
            Rx_CAN_Frame[DataEmpty].RxFull = TRUE;
            DataEmpty++;
            break;
        }
        DataEmpty++;
        if(i>=11) 
        {
            E_CAN_Rx = TRUE;
        }
    }
    
    CLR_CANRFLG();                                              
} 

void interrupt CAN_Tx_Isr(void) 
{
    UINT8 *tx_buf_ptr;
    UINT8 *data_buf_ptr;   
    UINT8 i;
    static UINT8 TxBufferEmpty;
    
    DISABLED_CANTXEIE;
    
    if(TxBufferEmpty >= CAN_TxBufMx)      //如果所有的缓冲区都检查了一边，则退出
    {
        TxBufferEmpty = 0;
        return;
    }
    if(Tx_CAN_Frame[TxBufferEmpty].TxComplete == FALSE) 
    {
        TxBufferEmpty ++;
        ENABLED_ALL_CANTXEIE;
        return;
    }
    if(CAN_TxBufferEmpty & CAN_TXE0)
    { 
       CAN_CANTBSEL = CAN_TXE0;
       CAN_BufferEmpty_Flag = CAN_TXE0;
    }
    else if(CAN_TxBufferEmpty & CAN_TXE1)
    {   
       CAN_CANTBSEL = CAN_TXE1;
       CAN_BufferEmpty_Flag = CAN_TXE1;
    }
    else if(CAN_TxBufferEmpty & CAN_TXE2)
    {
       CAN_CANTBSEL = CAN_TXE2;
       CAN_BufferEmpty_Flag = CAN_TXE2;
    }        
    
    tx_buf_ptr = &CAN_Tx_Data0;
    data_buf_ptr = &Tx_CAN_Frame[TxBufferEmpty].Data;   
    
    CAN_ConvertTxIDToRegister(Tx_CAN_Frame[TxBufferEmpty].ID,Tx_CAN_Frame[TxBufferEmpty].TxFrameType);
    for(i=0;i<Tx_CAN_Frame[TxBufferEmpty].TxLength;i++)
    {
      *tx_buf_ptr++ = *data_buf_ptr++;
    }
    CAN_Tx_Length = Tx_CAN_Frame[TxBufferEmpty].TxLength;
    CAN_Tx_Prio = 7;  
    CAN_Tx_TimeStamp = 0;
    CAN_TxBufferEmpty &= CAN_BufferEmpty_Flag;
    Tx_CAN_Frame[TxBufferEmpty].TxComplete = FALSE;      //缓冲区空
    TxBufferEmpty ++; 
    ENABLED_ALL_CANTXEIE;
}

#pragma CODE_SEG DEFAULT  













