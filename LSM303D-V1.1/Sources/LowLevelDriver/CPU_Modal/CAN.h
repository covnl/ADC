#ifndef __CAN_H
#define __CAN_H



extern UINT32 HLS_CCP_RxID ;          
extern UINT32 HLS_UAVCAN_RxID ;       
extern UINT32 HLS_WBO2_CAN_RxID ; 


//========struct =====================
typedef struct {
	UINT32 ID;		    // 
	UINT8  Data[8];		//
	UINT8  RxFull;    //1- ���ջ����������ȴ�����  0--���ջ������գ����Դ�������
  UINT8  TxComplete;   //1-���ͻ����������ȴ����� 0--���ͻ������գ����Դ�������
  UINT16 TxRate;     //���ݷ��͵�Ƶ�ʣ���׼ʱ��5ms
  UINT8  TxFrameType;
  UINT8  TxLength;
}CAN_Message;

#define CAN_TxBufMx  24
#define CAN_RxBufMx  12

/************************************************
**
**    CAN0ģ���ʼ������
************************************************/ 
//=====================CAN0==================================
#define CAN_EN               CANCTL1_CANE       //CANʹ��λ
#define CAN_INITRQ           CANCTL0_INITRQ     //CAN��ʼ������λ
#define CAN_INITACK          CANCTL1_INITAK     //CAN��ʼ��ģʽȷ��
#define CAN_CLKSRC           CANCTL1_CLKSRC     //CANʱ��Դѡ��
#define CAN_LOOPB            CANCTL1_LOOPB      //�Ի��Բ�ģʽ
#define CAN_LISTEN           CANCTL1_LISTEN     //����ģʽ
#define DISABLED_CANTXEIE    CANTIER=0          //���������ͻ��������ж�
#define ENABLED_CANTXEIE(value)     CANTIER=value       //�������ͻ��������ж�
#define ENABLED_ALL_CANTXEIE CANTIER = 0x03      //��ȫ�������ж�
#define DISABLED_CANRXFIE    CANRIER_RXFIE=0    //�������������ж�����
#define ENABLED_CANRXFIE     CANRIER_RXFIE=1    //�����������ж�����
#define SET_CANCTL1(value)   CANCTL1=value
#define SET_CANCTL0(value)   CANCTL0=value   
#define CLR_CANRFLG()        CANRFLG=0xff
#define CAN_TxBufferEmpty CANTFLG
#define CAN_RxBufferFull  CANRFLG_RXF
#define CAN_CANTBSEL  CANTBSEL
#define CAN_TXEIE     CANTIER

#define CAN_Tx_Id0        CANTXIDR0
#define CAN_Tx_Id1        CANTXIDR1
#define CAN_Tx_Id2        CANTXIDR2
#define CAN_Tx_Id3        CANTXIDR3

#define CAN_Tx_Data0      CANTXDSR0
#define CAN_Tx_Length     CANTXDLR_DLC
#define CAN_Tx_Prio       CANTXTBPR
#define CAN_Tx_TimeStamp  CANTXTSR

#define CAN_Rx_Id0        CANRXIDR0
#define CAN_Rx_Id1        CANRXIDR1
#define CAN_Rx_Id2        CANRXIDR2
#define CAN_Rx_Id3        CANRXIDR3

#define CAN_Rx_Data0      CANRXDSR0
#define CAN_Rx_Length     CANRXDLR_DLC
#define CAN_Rx_TimeStamp  CANRXTSR

#define SET_CANBTR0(value)       CANBTR0=value        //ͬ����ת���Ϊ1��Ԥ��Ƶ����Prescaler_value=5+1=6
#define SET_CANBTR1(value)       CANBTR1=value        //ͬ����Ծ���Ϊ1��
                                                  //TS1Ϊ10+1=11��TS2Ϊ3+1=4������=48Mb/s/6/(1+4+11)=500Kb/s
#define SET_CANIDAC(value)       CANIDAC=value        
                     
#define SET_CANIDAR0()      CANIDAR0 
#define SET_CANIDAR1()      CANIDAR1 
#define SET_CANIDAR2()      CANIDAR2 
#define SET_CANIDAR3()      CANIDAR3
 
#define SET_CANIDAR4()      CANIDAR4 
#define SET_CANIDAR5()      CANIDAR5 
#define SET_CANIDAR6()      CANIDAR6 
#define SET_CANIDAR7()      CANIDAR7

#define SET_CANIDMR0(value)      CANIDMR0=value      //����8��ID��000-700;
#define SET_CANIDMR1(value)      CANIDMR1=value       //ID�Ƿ������� AM0-AM2 =0������  =1��������
#define SET_CANIDMR2(value)      CANIDMR2=value
#define SET_CANIDMR3(value)      CANIDMR3=value
#define SET_CANIDMR4(value)      CANIDMR4=value
#define SET_CANIDMR5(value)      CANIDMR5=value
#define SET_CANIDMR6(value)      CANIDMR6=value
#define SET_CANIDMR7(value)      CANIDMR7=value

#define CAN_RXF  0x01   // RXFG buffer full flag
#define CAN_TXE0 0x01	// Tx0 buffer empty flag
#define CAN_TXE1 0x02	// Tx1 buffer empty flag
#define CAN_TXE2 0x04	// Tx2 buffer empty flag

#define BUSCLOCK  1
#define OSCCLOCK  0

#define Ext_Frame    1
#define Sta_Frame    0

/*********CANͨ���õ�������������********/                                            
#define CAN_TX_TAB_SIZE 1
#define CAN_RX_TAB_SIZE 1

/********************************************

BIT TIME=(Prescaler_value/f_canclk)*(1+TS1+TS2)

******************************************/
#define CAN_Baud_1M  1
#define CAN_Baud_800k  2
#define CAN_Baud_500k  3
#define CAN_Baud_250k  4
#define CAN_Baud_125k  5
#define CAN_Baud_100k  6
#define CAN_Baud_50k  7

void CANBUS_Init(void);
void CAN_Tx_Data(UINT8 Channel,UINT8 TxStatus,UINT8 FrameType,UINT32 TxID,UINT8 *DataPtr,UINT8 TxLen); 
void CAN_Init(UINT16 RxStaID,UINT32 RxExtID);
void CAN_UpdateCANBaud(UINT8 Baud_Sel);
void CAN_SetIDMaskFilter(UINT16 RxStaID,UINT32 RxExtID);
void CAN_TxData_Polling(UINT8 TxLen,UINT8 *DataPtr,UINT32 TxID,UINT8 FrameType);
void CAN_TxData_Interrupt(void);
void CAN_SetIDMaskFilter(UINT16 RxStaID,UINT32 RxExtID);
void CAN_SetIDMaskFilter(UINT16 RxStaID,UINT32 RxExtID);
//==================
void CAN_ConvertTxIDToRegister(UINT32 TxID,UINT8 FrameType);
UINT32 CAN_ConvertRxRegisterToID(UINT8 RxID0,UINT8 RxID1,UINT8 RxID2,UINT8 RxID3);

void CAN_ModelDisabled(void);
void CAN_Tx_Process_r1ms (void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED     
void interrupt CAN_Rx_Isr(void);
void interrupt CAN_Tx_Isr(void); 
#pragma CODE_SEG DEFAULT 






#endif