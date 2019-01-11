#include "typedefs.h"

/*******************************************************************************/
/* Global SCI communication status */
UINT16 Rx_Length;
UINT16 Tx_Length;              
 


extern Receive_Com asc0_CommunicationBuf;
extern Transmit_Receive_Complete_Flag KWP2000_Flg;
extern  UINT8 *Transmit_Complete_Ptr;
extern  UINT8 *Package_Complete_Ptr;
extern UINT8 PeriodicTask_Transmit_Complete;
extern UINT8 PeriodicTask10ms_reserved1_Transmit_Complete;


/* Pointer to current location on Reception array */
UINT8 *pu8SCI_Receive_Data_ptr;
/* Pointer to Transmit data*/
UINT8 *pu8SCI_Transmit_Data_ptr;
UINT8 CopyRightSendOnceFlg;
extern INT8 CopyRight_Buf[24];


/*******************************************************************************/
/**
* \brief    SCI initialization
* \author   Engineer
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   void
*/


void SCI_Init(void)
{                      
     SCIBD_SBR = SCI115200bps; //
     SCICR1 = 0x00;/* 正常的操作模式，无校验，1个起始位，8位数据位，1个停止位 */
     SCICR2 = 0x2C;    //接收中断允许,使能SCI接收器和发送器
            /*       0b00101100
                       ||||||||____ SendBrakeBit
                       |||||||_____ Receiver Wakeup bit
                       ||||||______ Receiver Enable bit
                       |||||_______ Transmiter Enable Bit
                       ||||________ Idle Line Interrupt Enable Bit
                       |||_________ Receiver full interrupt enable bit
                       ||__________ Transmission complete interrupt enable bit
                       |___________ Transmitter Interrupt Enable Bit
            */
      /* Reset auxiliary variables for input buffer management */
     Rx_Length = 0;  
     PeriodicTask_Transmit_Complete = TRUE;
     PeriodicTask10ms_reserved1_Transmit_Complete=TRUE;     
     pu8SCI_Receive_Data_ptr = &(asc0_CommunicationBuf.b_receive[0]);   
     CopyRightSendOnceFlg = FALSE;    
}

void SCI_Disabled(void)
{
    SCIBD =0;
    SCICR2 = 0;
}

/*******************************************************************************/
/**
* \brief    SCI Low-Level Tramsmit Function
* \author   Engineer
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
            UINT8 u8TxDataByte - Data byte to be transmitted
* \return   void
*/
void SCI_WriteWhenStartup(INT8 *array,UINT8 len)
{
    UINT8 i;
    if(CopyRightSendOnceFlg==FALSE)
    {
        CopyRightSendOnceFlg = TRUE;
        Read_CopyRight(2,&CopyRight_Buf[0]);
        Read_CopyRight(1,&CopyRight_Buf[8]);
        Read_CopyRight(0,&CopyRight_Buf[16]);
        for(i=0;i<len;i++)
        {
             SCI_WriteTx(array[i]);   
        }
    }
}

void SCI_WriteTx(UINT8 u8TxDataByte)
{         
     if(SCISR1_TDRE == 1)  //发送数据寄存器空标志
     {
         SCIDRL = u8TxDataByte;
         while(SCISR1_TC==0);
     }  
} 
  

/*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Engineer
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt SCI_Receive_Isr(void)
{   
  	if(SCISR1_RDRF == 1)/* 如果接收数据寄存器满则该标志为1 */
    {
         *pu8SCI_Receive_Data_ptr = SCIDRL;		/* Copy data from input buffer */
         Rx_Length++;
         pu8SCI_Receive_Data_ptr++;          /* Update input buffer pointer */
    }
    else if(SCISR1_TC == 1 && SCICR2_TCIE==1)/* 传送完成进中断 */
    {
      /*  此数据包还未传送完成，要继续传送 */
      if(PeriodicTask_Transmit_Complete==FALSE && Tx_Length>0)
      {
          if(SCISR1_TDRE==1)/* 发送数据寄存器为空 */
          {
              SCIDRL = *pu8SCI_Transmit_Data_ptr++;
              Tx_Length--;
              if(Tx_Length==0)
              {
                  SCICR2_TCIE = 0;/* 屏蔽发送完成中断 */
                  //SCITransmit_Interrupt(DISABLED);
                  /* 数据包传送完毕 */
                  PeriodicTask_Transmit_Complete=TRUE;/* 发包完成标志置1，表示可以发送新的数据包了 */
                  *Package_Complete_Ptr = FALSE; /* 打包完成标志复位，表示可以进行新数据的打包了 */
                  KWP2000_Verify_PeriodicTransmission();/* 检测是否有其他数据包等待发送 */    
              }
           
          }
      }  
      else
      {
          KWP2000_Verify_PeriodicTransmission();/* 屏蔽发送完成中断 */
      }
   }
   else
   {
       SCIDRL=SCIDRL;
       SCI_TC_INTERRUPT(DISABLED);
   }
}

#pragma CODE_SEG DEFAULT

   







/*******************************************************************************/


