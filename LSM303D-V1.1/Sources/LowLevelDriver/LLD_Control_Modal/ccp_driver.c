/*******************************************************************************/
/**
Copyright (c) 2014 COMPANY_ECOTRONS
\file       ccp_driver.c
\brief      Init CPU ,Init Clock
\author     COMPANY_GC
\version    1.0
\date       Oct/ 2014
*/
/*******************************************************************************/
#include "typedefs.h"

//#ifdef CCP_Driver_En

//UINT8 DTC_Message[1];

struct STCCP g_stCCP;
struct STAddress  g_stAddress;
struct STMemery g_stMemery;
UINT8 W_Dflash_flag=0;
UINT8 W_Pflash_flag=0;
UINT8 W_RAM_flag=0;
UINT8 clr_page;
UINT16 clr_addr;
UINT32 clr_memory_size; 
uint16_t uiStationAddress;
uint8_t CCP_ElementLen;
uint32_t g_ulAddressFrom;
uint32_t g_ulAddressTo;
uint32_t g_ulAddressTo_w;
uint8_t g_pubAddressFrom[4];
uint8_t g_pubAddressTo[4];
uint32_t ReceiveDataToProgramIndex;
uint8_t Flash_error_flag=0;
uint32_t g_ulAddress;
uint8_t ReceiveDataToProgram[32]=0;
UINT8 CCP_ProgrmFlag = 0;
static uint8_t g_ubResourceMask;

extern UINT8 Task_Enable;
extern UINT8 CAN0_Tx_TimeOut;

extern CAN_Message Tx_CAN_Frame[CAN_TxBufMx];
extern CAN_Message Rx_CAN_Frame[CAN_RxBufMx];

//========Defines=================================================================



/*********************CRC16校验查表值********************/

const UINT8 GetCRCLo[256] = {
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,

0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,

0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x01,0xC0,0x80,0x41,0x00, 0xC1,0x81,0x40,0x00,0xC1, 0x81,0x40,0x01,0xC0,0x80,0x41,
0x00,0xC1,0x81,0x40,0x01, 0xC0,0x80,0x41,0x01,0xC0, 0x80,0x41,0x00,0xC1,0x81,0x40
};      //256个数据
   
const UINT8  GetCRCHi[256] = {
0x00,0xC0,0xC1,0x01,0xC3, 0x03,0x02,0xC2,0xC6,0x06, 0x07,0xC7,0x05,0xC5,0xC4,0x04,
0xCC,0x0C,0x0D,0xCD,0x0F, 0xCF,0xCE,0x0E,0x0A,0xCA, 0xCB,0x0B,0xC9,0x09,0x08,0xC8,
0xD8,0x18,0x19,0xD9,0x1B, 0xDB,0xDA,0x1A,0x1E,0xDE, 0xDF,0x1F,0xDD,0x1D,0x1C,0xDC,
0x14,0xD4,0xD5,0x15,0xD7, 0x17,0x16,0xD6,0xD2,0x12, 0x13,0xD3,0x11,0xD1,0xD0,0x10,
0xF0,0x30,0x31,0xF1,0x33, 0xF3,0xF2,0x32,0x36,0xF6, 0xF7,0x37,0xF5,0x35,0x34,0xF4,

0x3C,0xFC,0xFD,0x3D,0xFF, 0x3F,0x3E,0xFE,0xFA,0x3A, 0x3B,0xFB,0x39,0xF9,0xF8,0x38,
0x28,0xE8,0xE9,0x29,0xEB, 0x2B,0x2A,0xEA,0xEE,0x2E, 0x2F,0xEF,0x2D,0xED,0xEC,0x2C,
0xE4,0x24,0x25,0xE5,0x27, 0xE7,0xE6,0x26,0x22,0xE2, 0xE3,0x23,0xE1,0x21,0x20,0xE0,
0xA0,0x60,0x61,0xA1,0x63, 0xA3,0xA2,0x62,0x66,0xA6, 0xA7,0x67,0xA5,0x65,0x64,0xA4,
0x6C,0xAC,0xAD,0x6D,0xAF, 0x6F,0x6E,0xAE,0xAA,0x6A, 0x6B,0xAB,0x69,0xA9,0xA8,0x68,

0x78,0xB8,0xB9,0x79,0xBB, 0x7B,0x7A,0xBA,0xBE,0x7E, 0x7F,0xBF,0x7D,0xBD,0xBC,0x7C,
0xB4,0x74,0x75,0xB5,0x77, 0xB7,0xB6,0x76,0x72,0xB2, 0xB3,0x73,0xB1,0x71,0x70,0xB0,
0x50,0x90,0x91,0x51,0x93, 0x53,0x52,0x92,0x96,0x56, 0x57,0x97,0x55,0x95,0x94,0x54,
0x9C,0x5C,0x5D,0x9D,0x5F, 0x9F,0x9E,0x5E,0x5A,0x9A, 0x9B,0x5B,0x99,0x59,0x58,0x98,
0x88,0x48,0x49,0x89,0x4B, 0x8B,0x8A,0x4A,0x4E,0x8E, 0x8F,0x4F,0x8D,0x4D,0x4C,0x8C,
0x44,0x84,0x85,0x45,0x87, 0x47,0x46,0x86,0x82,0x42, 0x43,0x83,0x41,0x81,0x80,0x40
};        //256个数据
 
/****************************************************************************/ 

void CCP_delay(UINT16 j)
{
  UINT16 i;
  for(i=0;i<j;i++);
}
/*****************************************************
** 
* \brief    CCP Address add.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_Address_vAdd(void)
{
    Pub_To_Ul_HF(g_ulAddress,g_stAddress.pubAddress);
    g_ulAddress+=g_stAddress.ubShortAdd;
    Ul_To_Pub_HF(g_stAddress.pubAddress,g_ulAddress);
}
/*****************************************************
** 
* \brief    CCP Address sub.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_Address_vSub(void)
{
    Pub_To_Ul_HF(g_ulAddress,g_stAddress.pubAddress);
	  g_ulAddress-=g_stAddress.ubShortSub;
	  Ul_To_Pub_HF(g_stAddress.pubAddress,g_ulAddress);
}
/*****************************************************
** 
* \brief    CCP memory move.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_Memory_vMove(void)
{
	  uint32_t index;
  	uint32_t ulFrom;
	  uint32_t ulTo;
	  uint8_t* pubFrom;
	  uint8_t* pubTo;
	  
	  Pub_To_Ul_HF(ulFrom,g_stMemery.pubFrom);
	  ulFrom = FLASH_Convert_Address(ulFrom);
	  pubFrom=(uint8_t*)(ulFrom);
	  Pub_To_Ul_HF(ulTo,g_stMemery.pubTo);
	  pubTo=(uint8_t*)(ulTo);
	  
	  for(index=0;index<g_stMemery.ulLength;index++)
		    pubTo[index]=pubFrom[index];
}

/*****************************************************
** 
* \brief    convert Byte data to Long data.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
uint32_t CCP_Convert_ub_To_ul(uint8_t* DataByte)
{
    uint32_t retval;
    
    retval = DataByte[0];
    retval<<=8;
    retval += DataByte[1];
    retval<<=8;
    retval += DataByte[2];	
    retval<<=8;
    retval += DataByte[3];	
    
    return retval;
}
/*****************************************************
** 
* \brief    get calibration checksum.
* \author   Engineer
* \param    void
* \return   checksum
* \todo     
**
*****************************************************/
uint16_t CCP_GetCalibrationDataChecksum(uint16_t *CalDataStartAddr)
{
    if((CCP_Session_Status&SS_CONNECTED)==0)
	  	  return;
}
/*****************************************************
** 
* \brief    stop All Daq list.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vStopAllDaq(void)
{
	  uint8_t i;

	  for (i=0;i<CCP_MAX_DAQ;i++)
		    CCP_DaqList[i].ubFlags = 0;
	  CCP_Session_Status &= ~SS_RUN;
	  
	  
}
/*****************************************************
** 
* \brief    stop one Daq.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vStopDaq (void)
{
    uint8_t i;

    if (CCP_Receive_DAQ_List>=CCP_MAX_DAQ)
	      return;
    CCP_DaqList[CCP_Receive_DAQ_List].ubFlags = 0;    //将相应DAQ_LIST标志位清0

    /* check if all DAQ lists are stopped */
    for (i=0;i<CCP_MAX_DAQ;i++)
    {
        if (CCP_DaqList[CCP_Receive_DAQ_List].ubFlags&DAQ_FLAG_START)
    	      return;
    }

    CCP_Session_Status &= ~SS_RUN;          //停止运行
    
    
}
/*****************************************************
** 
* \brief    clear Daq list.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vClearDaqList(UINT8 daq)
{
	  uint8_t* pubAddress;
	  uint16_t uiLength;
	  uint8_t i,j,k;

	  if (CCP_Receive_DAQ_List>=CCP_MAX_DAQ)
	  {
		  CCP_Transmit_DAQ_Size=0;
		  return;
	  }
	  /* Clear this daq list to zero */
	  uiLength=sizeof(struct STDaqList);    //获取大小
	  pubAddress=(uint8_t*)&(CCP_DaqList[CCP_Receive_DAQ_List]);    //获取DAQ_LIST首地址
	 
	  for(j=0;j<CCP_MAX_ODT;j++)
	  {
	  	  for(k=0;k<CCP_MAX_ODT_ENTRY;k++)
	  	  {
	  	  	  CCP_DaqList[daq].pstOdt[j][k].pubAddress[0] = 0;
	  	  	  CCP_DaqList[daq].pstOdt[j][k].pubAddress[1] = 0;
	  	  	  CCP_DaqList[daq].pstOdt[j][k].pubAddress[2] = 0;
	  	  	  CCP_DaqList[daq].pstOdt[j][k].pubAddress[3] = 0;
	  	  	  CCP_DaqList[daq].pstOdt[j][k].ubLength = 0;
	  	  	  CCP_DaqList[daq].uiPrescaler = 0;
	  	  	  CCP_DaqList[daq].uiCycle = 0;
	  	  	  CCP_DaqList[daq].ubEventChannel = 0;
	  	  	  CCP_DaqList[daq].ubLast = 0;
	  	  	  CCP_DaqList[daq].ubFlags = 0;
	  	  }
	  }

	  /* @@@@ Not DAQ list specific */
	  CCP_Session_Status |= SS_DAQ;

	  CCP_CurrentDaq=0;
	  CCP_CurrentOdt=0;

	  CCP_Transmit_DAQ_Size=CCP_MAX_ODT;
}
/*****************************************************
** 
* \brief    transmit data by CAN.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vTransmit(void)
{
    UINT8 i;
    	  
    CAN_Tx_Data(0,0,0,g_uiCCPCANSendID,&g_stCCP.pubCANTransmit,8);
    for(i=0;i<8;i++) 
    {
        g_stCCP.pubCANTransmit[i]=0;
    }  
}
/*****************************************************
** 
* \brief    get Seed.
* \author   Engineer
* \param    void
* \return   seed
* \todo     
**
*****************************************************/
void CCP_vGetSeed(void)
{
    if((CCP_Session_Status&SS_CONNECTED)==0)
		return;    
}
/*****************************************************
** 
* \brief    connect command 0x01.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandConnect(void)
{
    uint16_t localChecksum=0;
    uint16_t CalDataLen=0;
    
	  Pub_To_Ui_LF(uiStationAddress,(uint8_t*)&(g_stCCP.pubCANReceive[2]));
	  if(uiStationAddress!=CCP_STATION_ADDR&&            //0X111
			 uiStationAddress!=CCP_BROADCAST_STATION_ADDR)    //0
  	{
	      if (CCP_Session_Status&SS_CONNECTED)
	      {
	    	    CCP_Session_Status &= ~SS_CONNECTED;          //如果联机，择重新断开
	    	    CCP_Session_Status |= SS_TMP_DISCONNECTED;
	      }
	      return;
	   }

	  if (!(CCP_Session_Status&SS_TMP_DISCONNECTED))
	  {
	      CCP_vStopAllDaq();     //停止一切测量
	      CCP_SendStatus = 0; /* Clear all transmission flags */
	  }

	  CCP_Session_Status |= SS_CONNECTED;
  	CCP_Session_Status &= ~SS_TMP_DISCONNECTED;          //未联机位清0

	  CCP_Transmit_PID=0xff;
  	CCP_Transmit_ERR=CRC_OK;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
    
  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    set Address 0x02.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandSetMTA(void)
{

	  if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
	  
	  Pub4_Move(CCP_MTA_Current,((UINT8*)&CCP_Receive_Address_0));
	  Pub_To_Ul_HF(g_ulAddressTo,CCP_MTA_Current); 
	  g_ulAddressTo = FLASH_Convert_Address(g_ulAddressTo); 	  
	  CCP_Transmit_PID=0xff;
  	CCP_Transmit_ERR=0;//CRC_OK;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
  	CCP_vTransmit();
} 
/*****************************************************
** 
* \brief    DownLoad 0x03.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDNLoad(void)
{	 
	  UINT8    i;
	  UINT8   *g_ulAddressTo_P;
	  UINT8    page;
	  UINT16   addr;
	 
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
    if(CCP_Protection_Status&CCP_Resource_CAL)
    {
    	  CCP_Transmit_ERR = CRC_ACCESS_DENIED;
    }
    else
    {
    	  CCP_Transmit_ERR=CRC_OK;
        page=(uint8_t)(g_ulAddressTo>>16);
        addr=(uint16_t) (g_ulAddressTo&0x00ffff);        
        if(W_RAM_flag==1) 
        {
            W_RAM_flag=0;
            g_ulAddressTo_P=(UINT8 *)g_ulAddressTo;
            for(i=0;i<CCP_Receive_Data_Size;i++)
            {  
                g_ulAddressTo_P[i]=g_stCCP.pubCANReceive[3+i];
            }
            g_ulAddressTo +=CCP_Receive_Data_Size;
         }
    }
   	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
  	g_stCCP.pubCANTransmit[4] = (UINT8)(g_ulAddressTo>>24);
  	g_stCCP.pubCANTransmit[5] = (UINT8)(g_ulAddressTo>>16);
  	g_stCCP.pubCANTransmit[6] = (UINT8)(g_ulAddressTo>>8);
    g_stCCP.pubCANTransmit[7] = (UINT8)(g_ulAddressTo);


  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    Upload 0x04.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandUpLoad(void)
{	  
	  UINT8 i;
    uint8_t *UPLOAD_DATA_ADDR;
    UINT8 page = 0;
    UINT32 addr = 0; 
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
	  
    page = (UINT8)(g_ulAddressTo>>16);
    addr = g_ulAddressTo;
    //UPLOAD_DATA_ADDR=(UINT8 *)addr;
    
    if((addr>=0x4000 && addr<0xffff) || (addr>=0x7f4000 && addr<=0x7fffff))
    {
       for(i=0;i<CCP_Receive_UPLOAD_DATASIZE;i++) 
       {
           g_stCCP.pubCANTransmit[i+3]=*(UINT8 *)addr++;
       }
       g_ulAddressTo+=CCP_Receive_UPLOAD_DATASIZE;
     	 CCP_Transmit_PID=0xff;
    }
    else
    {
        CCP_Transmit_PID = 0xfe;
    }
  	CCP_Transmit_CTR=CCP_Receive_CTR;
  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    test 0x05.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandTest(void)
{
 	  if((CCP_Session_Status&SS_CONNECTED)==0)
		return;

    CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
    CCP_Transmit_ERR = CRC_OK;

  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    start or stop Daq 0x06.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandStartStop(void)
{
	  uint8_t* puiRatePrescaler;
	  puiRatePrescaler=CCP_Receive_RatePrescalerHead;
  	if((CCP_Session_Status&SS_CONNECTED)==0)
	  return;

    #ifdef KEY_SEED
    if ((CCP_Protection_Status&CCP_Resource_DAQ)==0)
    {
    	  CCP_Transmit_ERR = CRC_ACCESS_DENIED;
    	  goto Exit;
    }
  	if ((CCP_Session_Status&SS_DAQ)==0)
	  {
		    CCP_Transmit_ERR = CRC_DAQ_INIT_REQUEST;
		    goto Exit;
	  }
    #endif
    
	  if (CCP_Receive_DAQ_Select_2>=CCP_MAX_DAQ)           //列表数超出最大
	  {
	      CCP_Transmit_ERR=CRC_CMD_SYNTAX;
	      goto Exit;
	  }
  	switch(CCP_Receive_Daq_Mode)
	  {
	      case CCP_DAQ_Stop:
      	     CCP_DaqList[CCP_Receive_DAQ_Select_2].ubFlags = 0;
		         CCP_Session_Status &= ~SS_RUN;
           	 break;
	      case CCP_DAQ_Start:
             CCP_DaqList[CCP_Receive_DAQ_Select_2].ubEventChannel = CCP_Receive_EventChannel;
		         if (*puiRatePrescaler==0)  *puiRatePrescaler = 1;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].uiPrescaler = *puiRatePrescaler;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].uiCycle = 1;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].ubLast = CCP_Receive_Last_ODT;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].ubFlags = DAQ_FLAG_START;
		         CCP_Session_Status |= SS_RUN;
           	 break;
 	      case CCP_DAQ_Prepare:
             CCP_DaqList[CCP_Receive_DAQ_Select_2].ubEventChannel = CCP_Receive_EventChannel;
		         if (*puiRatePrescaler==0)  *puiRatePrescaler = 1;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].uiPrescaler = *puiRatePrescaler;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].uiCycle = 1;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].ubLast = CCP_Receive_Last_ODT;
		         CCP_DaqList[CCP_Receive_DAQ_Select_2].ubFlags = DAQ_FLAG_PREPARED;
   	         break;
	      default:
	           CCP_Transmit_ERR = CRC_CMD_SYNTAX;
		         goto Exit;
		         break;
	   }
    Exit:
	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    Disconnect 0x07.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDisconnect(void)
{
	  uint8_t i;

  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;

  	CCP_Session_Status &= ~SS_CONNECTED;

	  if (CCP_Receive_DisconnectCmd==0x00)
	  { /* Temporary */
	      CCP_Session_Status |= SS_TMP_DISCONNECTED;
	  }
	  else
	  {           /* End of session */
		    for(i=0;i<CCP_MAX_DAQ;i++)
		    {
			      CCP_DaqList[i].ubFlags = 0;
		    }
		    CCP_Session_Status &= ~SS_RUN;
		    CCP_Protection_Status = 0; /* Clear Protection Status */
	  }

	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    start or stop all Daq.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandStartStopAll(void)
{
	  uint8_t i;
	 

  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;

    #ifdef KEY_SEED
	  if ((CCP_Session_Status&SS_DAQ)==0)
	  {
		    CCP_Transmit_ERR = CRC_DAQ_INIT_REQUEST;
		    goto Exit;
	  }
    #endif

	  switch(CCP_Receive_Daq_Mode)
	  {
	      case CCP_DAQ_Stop:
		         for(i=0;i<CCP_MAX_DAQ;i++)
		         {
			           CCP_DaqList[i].ubFlags = 0;
		         }
		         CCP_Session_Status &= ~SS_RUN;
	  	       break;
	      case CCP_DAQ_Start:
		         for (i=0;i<CCP_MAX_DAQ;i++)
		         {
			           if (CCP_DaqList[i].ubFlags==DAQ_FLAG_PREPARED)
				         CCP_DaqList[i].ubFlags= DAQ_FLAG_START;
		         }
		         CCP_Session_Status |= SS_RUN;
		         break;
	      default:
		         CCP_Transmit_ERR = CRC_CMD_SYNTAX;
		         goto Exit;
		         break;
	  }

    Exit:
	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    short Upload 6Byte 0x0f.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandShortUpLoad(void)
{
	  UINT8 i;
	  UINT8* UPLOAD_DATA_ADDR;
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
     UPLOAD_DATA_ADDR=(UINT8 *)g_ulAddressTo;
    for(i=0;i<CCP_Receive_UPLOAD_DATASIZE;i++) 
    {
        g_stCCP.pubCANTransmit[i+3]=*UPLOAD_DATA_ADDR++;
    }
  	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;

  	CCP_vTransmit();	
  	
}
/*****************************************************
** 
* \brief    set Daq size 0x14.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDAQSize(void)
{
	  uint32_t* pulIdentifier;
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
   	CCP_Transmit_ERR=CRC_OK;
	  CCP_vStopDaq();
	  pulIdentifier=(uint32_t*)(&CCP_Receive_Address_0);      //获取ID

	  if((*pulIdentifier)!=CCP_DTO_ID)
		    CCP_Transmit_ERR=CRC_CMD_SYNTAX;               //验证ID

	  CCP_vClearDaqList(g_stCCP.pubCANReceive[2]);              //清空LIST

	  CCP_Transmit_First_PID=CCP_MAX_ODT*CCP_Receive_DAQ_List;//

	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;
	 

	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    set daq point data.   0x15
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDAQPtr(void)                //设置指针指向注定的数据
{
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;

    if (CCP_Receive_DAQ_Select>=CCP_MAX_DAQ||
    		CCP_Receive_ODT_Select>=CCP_MAX_ODT||
    		CCP_Receive_Element_Select>CCP_MAX_ODT_ENTRY)
    {
    	  CCP_Transmit_ERR = CRC_CMD_SYNTAX;       //数据错误
    	  CCP_ODT_Entry = 0;
    }
    else
    {
    	  CCP_Transmit_ERR = CRC_OK;
    	  CCP_ODT_Entry =
    		  &CCP_DaqList[CCP_Receive_DAQ_Select].pstOdt[CCP_Receive_ODT_Select][CCP_Receive_Element_Select];
    }      //指向 所选的DAQ中的 所选的ODT中的  ELEMENT
  	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;

  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    write odt entry. 0x16
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandWriteDAQ(void)
{
	  
    if((CCP_Session_Status & SS_CONNECTED)==0)
		return;

    if ((CCP_Receive_Data_Size!=4)&&(CCP_Receive_Data_Size!=2)&&(CCP_Receive_Data_Size!=1))
    {
    	  CCP_Transmit_ERR = CRC_CMD_SYNTAX;        //如果不是 4、2、1则发生错误
    	  goto Exit;
    }
    if(CCP_ODT_Entry==0)
    {
    	  CCP_Transmit_ERR = CRC_CMD_SYNTAX;
    	  goto Exit;
    }

    Pub4_Move(CCP_ODT_Entry->pubAddress,(uint8_t*)&CCP_Receive_Address_0);
    CCP_ODT_Entry->ubLength=CCP_Receive_Data_Size;
    
    Exit:
  	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;

  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    exchange id.  0x17
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/

void CCP_vCommandExchangeID(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
  	CCP_Transmit_PID=0xff;
  	CCP_Transmit_ERR=CRC_OK;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
  	CCP_Transmit_ID_Length=32;//====strlen(CCP_StationID);
  	CCP_Transmit_Type=0;

  	CCP_Transmit_Availabitity_Mask=CCP_Resource_DAQ;
  	CCP_Transmit_Availabitity_Mask+=CCP_Resource_CAL;

  	CCP_Transmit_Protection_Mask=CCP_Resource_DAQ;
  	CCP_Transmit_Protection_Mask+=CCP_Resource_CAL;

  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    get ccp version 0x1b.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandCCPVersion(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
  	
  	g_stCCP.pubCANTransmit[3] = 0x84;
  	g_stCCP.pubCANTransmit[4] = 0x33;
  	g_stCCP.pubCANTransmit[5] = 0x66;
  	g_stCCP.pubCANTransmit[6] = 0x66;
  	g_stCCP.pubCANTransmit[7] = 0x16;
  	
    CCP_Transmit_PID=0xff;
    CCP_Transmit_CTR=CCP_Receive_CTR;
    CCP_vTransmit();
	
}
/*****************************************************
** 
* \brief    get ECU version 0x1c.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
extern UINT8 Hardware_Version[16]; 
extern UINT8 Software_LLD_Version[16];
extern UINT8 Software_HLD_Version[16];                                                    
extern UINT8 Software_CLD_Version[16]; 

void CCP_vCommandECUVersion(void)
{
   UINT8 bufPos =0;
   UINT8 i,j;
   UINT32 address = 0;
   if((CCP_Session_Status&SS_CONNECTED)==0)
	     return;
  //================Hardware_Version=========== 
   
  for(j=0;j<4;j++)
  {
      g_stCCP.pubCANTransmit[0] = 0xff;
      g_stCCP.pubCANTransmit[1] = 0;
      g_stCCP.pubCANTransmit[2] = 0x1c;
      g_stCCP.pubCANTransmit[3] = j;
      for(i=0;i<4;i++)
      {
          g_stCCP.pubCANTransmit[i+4] = Hardware_Version[i+j*4];
       
      }
      CCP_vTransmit();
  }	 
  //================Software_LLD_Version===========     
  for(j=0;j<4;j++)
  {
      g_stCCP.pubCANTransmit[0] = 0xff;
      g_stCCP.pubCANTransmit[1] = 0;
      g_stCCP.pubCANTransmit[2] =0x1c;
      g_stCCP.pubCANTransmit[3] =(0x10+j);
      for(i=0;i<4;i++)
      {
          g_stCCP.pubCANTransmit[i+4] = Software_LLD_Version[i+j*4];
      }
      CCP_vTransmit();
  }	 
//================Software_HLD_Version===========      
  for(j=0;j<4;j++)
  {
      g_stCCP.pubCANTransmit[0] = 0xff;
      g_stCCP.pubCANTransmit[1] = 0;  
      g_stCCP.pubCANTransmit[2] =0x1c;
      g_stCCP.pubCANTransmit[3] =0x20+j;
      for(i=0;i<4;i++)
      {
          g_stCCP.pubCANTransmit[i+4] = Software_HLD_Version[i+j*4];
       
      }
      CCP_vTransmit();
  }
//================Software_CLD_Version===========       
  for(j=0;j<4;j++)
  {
      g_stCCP.pubCANTransmit[0] = 0xff;
      g_stCCP.pubCANTransmit[1] = 0;
      g_stCCP.pubCANTransmit[2] =0x1c;
      g_stCCP.pubCANTransmit[3] =0x30+j;
      for(i=0;i<5;i++)
      {
          g_stCCP.pubCANTransmit[i+4] = Software_CLD_Version[i+j*4];
       
      }
      CCP_vTransmit();
  }
//================BoootLoader=========== 

  address = NVM_SerialNumber_GlobalAddress;
  for(i= 0;i<2;i++)
  {
    g_stCCP.pubCANTransmit[0] = 0xff;
    g_stCCP.pubCANTransmit[1] = 0;
    g_stCCP.pubCANTransmit[2] =0x1c;
    g_stCCP.pubCANTransmit[3] =0x40+i;
    if(i==0)
    {
        g_stCCP.pubCANTransmit[4] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[5] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[6] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[7] = *(UINT8 *)address++;
    }
    if(i==1)
    {
        g_stCCP.pubCANTransmit[4] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[5] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[6] = *(UINT8 *)address++;
        g_stCCP.pubCANTransmit[7] = *(UINT8 *)address++;
    }
    CCP_vTransmit(); 
  }
    
}
/*****************************************************
** 
* \brief    get download password 0x1d.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDNload_Password(void)
{
    UINT32   RCV_Password_H=0;
    UINT32   RCV_Password_L=0;
    UINT8   Password_error_FLG=0;
    UINT8   i;
    if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
    for(i=0;i<3;i++) 
    {   
        RCV_Password_H<<=8; 
        RCV_Password_H+=g_stCCP.pubCANReceive[2+i];
        RCV_Password_L<<=8; 
        RCV_Password_L+=g_stCCP.pubCANReceive[5+i]; 
    }
   
    if ((RCV_Password_H==Password_H)&&(RCV_Password_L==Password_L)) 
    { 
        CCP_Transmit_ERR=CRC_OK;
        CCP_Transmit_PID=0xff;
	      CCP_Transmit_CTR=CCP_Receive_CTR;
	      CCP_vTransmit();  
    } 
    else
    {
        CCP_Transmit_ERR=CRC_OUT_OF_RANGE;
        CCP_Transmit_PID=0xff;
	      CCP_Transmit_CTR=CCP_Receive_CTR;
	      CCP_vTransmit(); 
    } 
}
/*****************************************************
** 
* \brief    download 6byte 0x23.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDNLoad_6(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;

    if (CCP_Protection_Status&CCP_Resource_CAL)
    {
    	  CCP_Transmit_ERR = CRC_ACCESS_DENIED;
    }
    else
    {
      	CCP_Transmit_ERR=CRC_OK;
        g_ulAddressFrom=(uint32_t)CCP_Receive_Data_Head;
    	  Ul_To_Pub_HF(g_pubAddressFrom,g_ulAddressFrom);
    	  MEMORY_MOVE(CCP_MTA[0],g_pubAddressFrom,6);
    	  ADDRESS_ADD(CCP_MTA[0],6);
    	  CCP_Transmit_Extension=0;

    	  Pub4_Move(CCP_Transmit_Address_Head,CCP_MTA[0]);
    }

  	CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    get cal page 0x09.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandGetCalPage(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
    
    g_stCCP.pubCANTransmit[3] = 0;
    g_stCCP.pubCANTransmit[4] = 0;
    g_stCCP.pubCANTransmit[5] = 0;
    g_stCCP.pubCANTransmit[6] = 0x40;
    g_stCCP.pubCANTransmit[7] = 0;
  
  	CCP_Transmit_PID=0xff;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  CCP_vTransmit();  	
}
/*****************************************************
** 
* \brief    set run status 0x0c.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandSetSStatus(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
    /* Set Resume and Store mode in SessionStatus */
  	CCP_Session_Status &= ~(SS_STORE|SS_RESUME);         //清零STORE  RESUME  标志位
  	CCP_Session_Status |= (CCP_Receive_Session_Status&(SS_STORE|SS_RESUME));       //置位标志位

      /* Save as UserSessionStatus */
  	CCP_User_SessionStatus = CCP_Receive_Session_Status;       

  	CCP_Transmit_ERR=CRC_OK;

  	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;

  	CCP_vTransmit();
}
/*****************************************************
** 
* \brief    get status 0x0d.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandGetSStatus(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
    g_stCCP.pubCANTransmit[3] = CCP_User_SessionStatus;
    g_stCCP.pubCANTransmit[4] = 0;
    
   	CCP_Transmit_PID=0xff;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
  	CCP_vTransmit();  	
}
/*****************************************************
** 
* \brief    calculate checksum 0x0e.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandBuildCheckSum(void)
{
  	uint16_t locakchecksum=0;
    uint32_t i;
    uint32_t SizeToBeBuildChecksum;
    UINT8    *addr;
    UINT8    CRC16Hi = 0xFF;
    UINT8    CRC16Lo = 0xFF;
    UINT8    iIndex;
    UINT8  CalPage_Index = 0xff;
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
    
    SizeToBeBuildChecksum = CCP_Convert_ub_To_ul(CCP_Receive_BuildChecksum_Len);   
    //addr=(UINT8 *)g_ulAddressTo;
    addr=(UINT8 *)FLASH_Convert_Address(NVM_CALC_Data);
    if(Calibration_Data_Length==SizeToBeBuildChecksum)
    {
        for(i=0;i<SizeToBeBuildChecksum;i++)
	      {
	          iIndex = *addr^CRC16Lo;
	          addr++;
	          CRC16Lo = CRC16Hi^GetCRCLo[iIndex];
	          CRC16Hi = GetCRCHi[iIndex]; 	
	      }
	      locakchecksum = CRC16Hi;
	      locakchecksum=locakchecksum<<8;
	      locakchecksum+=CRC16Lo;
	
	      CCP_Transmit_BuildChecksum_Size = 2;
	      Ui_To_Pub_HF(&g_stCCP.pubCANTransmit[4],locakchecksum);
	
	      CCP_Transmit_ERR=CRC_OK;
        CCP_Transmit_PID=0xff;
	      CCP_Transmit_CTR=CCP_Receive_CTR;

	      CCP_vTransmit();
	  } 
    else
    {
  	    CCP_Transmit_ERR=CRC_OUT_OF_RANGE;              //大小不符发生错误时发送错误码
        CCP_Transmit_PID=0xff;                      //发生错误时发送0xff
	      CCP_Transmit_CTR=CCP_Receive_CTR;

	      CCP_vTransmit(); 
    }
}
/*****************************************************
** 
* \brief    clear memory 0x10.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandClearMemory(void)
{
    
    UINT8  *CCP_ClearMemorySectorSize_T;
    if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
    
    clr_page=(g_ulAddressTo>>16);
	  clr_addr=(uint16_t)(g_ulAddressTo&0x0000ffff);
    
    CCP_ClearMemorySectorSize_T=(UINT8 *)CCP_ClearMemorySectorSize;
	  Pub_To_Ul_HF(clr_memory_size,CCP_ClearMemorySectorSize_T);
	  Task_Enable = FALSE;    
    clr_memory();
    
	  CCP_Transmit_ERR = CRC_OK;//Erase successful 	
	  CCP_Transmit_PID = 0xff;
	  CCP_Transmit_CTR = CCP_Receive_CTR;
	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    clear flash.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void clr_memory (void)
{   
    if(W_Pflash_flag==1) 
	  { 
	      clr_memory_size=clr_memory_size/PFLASH_Sector_Size+1;
	      Flash_EraseP_Sector(clr_addr,clr_page,clr_memory_size);
	  } 
	  else if(W_Dflash_flag==1) 
	  {
	      clr_memory_size=clr_memory_size/DFLASH_Sector_Size+1;	 
	      Flash_EraseD_Sector(clr_addr,clr_page,clr_memory_size);        
	  }
}
/*****************************************************
** 
* \brief    set cal page 0x11.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandSetCalPage(void)
{
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
  	
		CCP_Transmit_PID = 0xff;
	  CCP_Transmit_CTR = CCP_Receive_CTR;
	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    get seed 0x12.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandGetSeed(void)
{
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_ERR=CRC_OK;
	  CCP_Transmit_CTR=CCP_Receive_CTR;

	  if(CCP_Protection_Status&CCP_Receive_ResourceMask)
		    CCP_Transmit_ProtectionStatus=1;
	  else
		    CCP_Transmit_ProtectionStatus=0;
	  //Get Seed not define.
	  CCP_vGetSeed();   
	  CCP_vTransmit();
}
/*****************************************************
** 
* \brief    unlock 0x13.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
extern UINT8 Task_Enable;
void CCP_vCommandUnLock(void)
{
	  //====debug
	  Task_Enable = FALSE;
	  Powerdown_Interface();
    Disable_All_Interrupts();
     __asm  
    {
       JMP $F000;
    }
	  
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
	  CCP_Transmit_PID=0xff;
	  CCP_Transmit_ERR=0;//CRC_OK;
  	CCP_Transmit_CTR=CCP_Receive_CTR;
    /* Check key */
     
	  //CCP_Protection_Status |= ccpUnlock(&com[2]); /* Reset the appropriate resource protection mask bit */
  	CCP_Transmit_ProtectionStatus = CCP_Protection_Status; /* Current Protection Status */
}
/*****************************************************
** 
* \brief    program data to flash 0x18.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandProgram(void)
{
  	uint8_t i;
    UINT8   page;
	  UINT16  addr;

	  uint8_t Check_Erro_Flag=0;
	  UINT8   CCP_ProgramCompleteFlg=0;
   
  	if((CCP_Session_Status&SS_CONNECTED)==0)
		return;
  	
    if((g_stCCP.pubCANReceive[2]==0))                                    //发送数据为零，发送完毕
    {
        g_ulAddressFrom=(uint32_t)&ReceiveDataToProgram;
        page=(uint8_t)(g_ulAddressTo>>16);
        addr=(uint16_t) (g_ulAddressTo&0x00ffff);
        if(W_Dflash_flag==1) 
        {                
             Flash_WriteD_Array(addr,(uint16_t*)g_ulAddressFrom,page, ReceiveDataToProgramIndex); 
        }
        else if(W_Pflash_flag==1) 
        {
             Flash_WriteP_Array(addr,(uint16_t*)g_ulAddressFrom,page, ReceiveDataToProgramIndex); 
        }
         ReceiveDataToProgramIndex = 0; 
         g_ulAddressTo=g_ulAddressTo+ReceiveDataToProgramIndex;
         W_Dflash_flag = 0;
         W_Pflash_flag = 0;
         CCP_ProgramCompleteFlg=TRUE;
     }    	  
     else
     {
         for(i=0;i<g_stCCP.pubCANReceive[2];i++)                              //不为零接收数据
         {
             ReceiveDataToProgram[ReceiveDataToProgramIndex] = g_stCCP.pubCANReceive[i+3];
             ReceiveDataToProgramIndex++;
             if(ReceiveDataToProgramIndex == 32)// PFLASH_Sector_Size
             {
                 g_ulAddressFrom=(uint32_t)&ReceiveDataToProgram;
              	 page=(uint8_t)(g_ulAddressTo>>16);
                 addr=(uint16_t) (g_ulAddressTo&0x00ffff);
                 if(W_Dflash_flag==1) 
                 {
                      Flash_WriteD_Array(addr,(uint16_t*)g_ulAddressFrom,page, ReceiveDataToProgramIndex); 

                 }
                 else if(W_Pflash_flag==1) 
                 {
                      Flash_WriteP_Array(addr,(uint16_t*)g_ulAddressFrom,page, ReceiveDataToProgramIndex);
                 }
              	 g_ulAddressTo=g_ulAddressTo+ReceiveDataToProgramIndex;
                 ReceiveDataToProgramIndex = 0;
             }
         }
    }
    CCP_Transmit_Extension=0;
  	Pub4_Move(((uint8_t*)CCP_Transmit_Address_Head),CCP_MTA[0]);

    CCP_Transmit_PID=0xff;
    CCP_Transmit_CTR=CCP_Receive_CTR;
    CCP_Transmit_ERR=CRC_OK;
    CCP_vTransmit();
    
    if(CCP_ProgramCompleteFlg)
    {  
    
        CCP_delay(1000);
        Powerdown_Interface();
        Disable_All_Interrupts();
        __asm   
        {
            JMP $C000;
        }
    }

}
/*****************************************************
** 
* \brief    move memory 0x19.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandMoveMemory(void)
{
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
}
/*****************************************************
** 
* \brief    ADC Init.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandDiagService(void)
{
    UINT8 Error_Count = 0;
    UINT8 DTC_DataCount = 0;
    UINT8 i,j=0;
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
	  
	  //Error_Count = SAE_J1939Tx_DTC();
       
    if(Error_Count != 0)
    {
        if(Error_Count%4 == 0)
        {
          DTC_DataCount = Error_Count/4;
        }
        else
        {
           DTC_DataCount = Error_Count/4+1;
        }              
        for(i=0;i<DTC_DataCount;i++)
        {
           g_stCCP.pubCANTransmit[0] = 0xff;
           g_stCCP.pubCANTransmit[1] = 0x00;
           g_stCCP.pubCANTransmit[2] = 0x20;
           for(j=0;j<4;j++)
           {
               //g_stCCP.pubCANTransmit[j+3] = DTC_Message[j+4*i];   
           }
            CCP_vTransmit();           
        } 
    }
    else
    {
        g_stCCP.pubCANTransmit[0] = 0xff;
        g_stCCP.pubCANTransmit[1] = 0x00;
        g_stCCP.pubCANTransmit[2] = 0x20;
        CCP_vTransmit(); 
    }
    //=========
    for(i=0;i<32;i++)
    {
       //DTC_Message[i] = 0;
    }
}
/*****************************************************
** 
* \brief    diagnosis service 0x21.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandActionService(void)
{
	  if((CCP_Session_Status&SS_CONNECTED)==0)
		    return;
}
/*****************************************************
** 
* \brief    program 6byte 0x22.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandProgram_6(void)
{
	  if((CCP_Session_Status&SS_CONNECTED)==0)
	  	  return;
}
/*****************************************************
** 
* \brief    ccp entry.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vCommandProcess(void)
{
    uint8_t local_cmd;
    
    local_cmd = CCP_Receive_CMD;	
	  switch(local_cmd)
    {
	      EVENT_MAP(CC_CONNECT,		       CCP_vCommandConnect);
      	EVENT_MAP(CC_SET_MTA,		       CCP_vCommandSetMTA);
      	EVENT_MAP(CC_DNLOAD,	  	     CCP_vCommandDNLoad);
	      EVENT_MAP(CC_UPLOAD,		       CCP_vCommandUpLoad);
	      EVENT_MAP(CC_TEST,			       CCP_vCommandTest);
	      EVENT_MAP(CC_START_STOP,     	 CCP_vCommandStartStop);
	      EVENT_MAP(CC_DISCONNECT,	     CCP_vCommandDisconnect);
	      EVENT_MAP(CC_START_STOP_ALL,   CCP_vCommandStartStopAll);
      	EVENT_MAP(CC_SHORT_UPLOAD,	   CCP_vCommandShortUpLoad);
	      EVENT_MAP(CC_GET_DAQ_SIZE,	   CCP_vCommandDAQSize);
	      EVENT_MAP(CC_SET_DAQ_PTR,	     CCP_vCommandDAQPtr);
	      EVENT_MAP(CC_WRITE_DAQ,		     CCP_vCommandWriteDAQ);
	      EVENT_MAP(CC_EXCHANGE_ID,    	 CCP_vCommandExchangeID);
 	      EVENT_MAP(CC_GET_CCP_VERSION,  CCP_vCommandCCPVersion);
	      EVENT_MAP(CC_GET_ECU_VERSION,  CCP_vCommandECUVersion);
	      EVENT_MAP(CC_Download_Password,CCP_vCommandDNload_Password);
	      EVENT_MAP(CC_DNLOAD_6,		     CCP_vCommandDNLoad_6);
	      EVENT_MAP(CC_GET_CAL_PAGE,   	 CCP_vCommandGetCalPage);
	      EVENT_MAP(CC_SET_S_STATUS,   	 CCP_vCommandSetSStatus);
	      EVENT_MAP(CC_GET_S_STATUS,	   CCP_vCommandGetSStatus);
	      EVENT_MAP(CC_BUILD_CHKSUM,	   CCP_vCommandBuildCheckSum);
	      EVENT_MAP(CC_CLEAR_MEMORY,	   CCP_vCommandClearMemory);
	      EVENT_MAP(CC_SET_CAL_PAGE,	   CCP_vCommandSetCalPage);
	      EVENT_MAP(CC_GET_SEED,		     CCP_vCommandGetSeed);
	      EVENT_MAP(CC_UNLOCK,		       CCP_vCommandUnLock);
      	EVENT_MAP(CC_PROGRAM,		       CCP_vCommandProgram);
	      EVENT_MAP(CC_MOVE_MEMORY,	     CCP_vCommandMoveMemory);
	      EVENT_MAP(CC_DIAG_SERVICE,	   CCP_vCommandDiagService);
	      EVENT_MAP(CC_ACTION_SERVICE,   CCP_vCommandActionService);
	      EVENT_MAP(CC_PROGRAM_6,		     CCP_vCommandProgram_6);
    }       
}

/*****************************************************
** 
* \brief    Daq Cycle to upload.
* \author   Engineer
* \param    void
* \return   void
* \todo     daq 0
**
*****************************************************/
void CCP_vDAQTransmit_Syn(void)
{ 
    #define Element_Length0   	CCP_DaqList[0].pstOdt[j][k].ubLength
    #define Element_Address0  	CCP_DaqList[0].pstOdt[j][k].pubAddress
    #define ODT_Last0		      	CCP_DaqList[0].ubLast
    uint8_t i,j,k;
    uint8_t ubIndex;
    uint32_t g_ulAddressTo_syn;
    uint8_t g_pubAddressTo_syn[4];
    uint8_t g_pubAddressFrom_syn[4];
    
	  if((CCP_Session_Status & SS_RUN)==0)
		    return;
    
    if(CCP_DaqList[0].ubFlags&DAQ_FLAG_START)
    {
	     // CCP_DaqList[i].ubFlags&=~DAQ_FLAG_START;
	      for(j=0;j<=ODT_Last0;j++)
	      {
		        if(j>=CCP_MAX_ODT)
		           goto Transmit;   
		        ubIndex=1;           //7
            CCP_Transmit_PID=j;      
		        for(k=0;k<CCP_MAX_ODT_ENTRY;k++)
		        {                  //4
			          if(Element_Length0==0)
			          goto Transmit;
			          if(ubIndex+Element_Length0>8)
				        goto Transmit;
	            
			          g_ulAddressTo_syn=(uint32_t)(&CCP_Transmit[ubIndex]);
		            Ul_To_Pub_HF(g_pubAddressTo_syn,g_ulAddressTo_syn);
                Pub4_Move(g_pubAddressFrom_syn,Element_Address0);
			          MEMORY_MOVE(g_pubAddressTo_syn,g_pubAddressFrom_syn,Element_Length0);
			          ubIndex+=Element_Length0;	
		        }
            Transmit:
		        CCP_vTransmit();
		        if(CAN0_Tx_TimeOut > 4)return;
   		  }
    }

}
/*****************************************************
** 
* \brief    Daq Cycle to upload.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vDAQTransmit_20ms(void)
{
    #define Element_Length1   	CCP_DaqList[1].pstOdt[j][k].ubLength
    #define Element_Address1  	CCP_DaqList[1].pstOdt[j][k].pubAddress
    #define ODT_Last1		    	CCP_DaqList[1].ubLast
    uint8_t i,j,k;
    uint8_t ubIndex;
    uint32_t g_ulAddressTo_20ms;
    uint8_t g_pubAddressTo_20ms[4];
    uint8_t g_pubAddressFrom_20ms[4];
    
	  if((CCP_Session_Status & SS_RUN)==0)
		    return;

    
    if(CCP_DaqList[1].ubFlags&DAQ_FLAG_START)
    {
	      //CCP_DaqList[i].ubFlags&=~DAQ_FLAG_START;
	      for(j=0;j<=ODT_Last1;j++)
	      {
	          if(j>=CCP_MAX_ODT)
               goto Transmit;
		        ubIndex=1;           //7
            CCP_Transmit_PID=CCP_MAX_ODT*1+j;      
		        for(k=0;k<CCP_MAX_ODT_ENTRY;k++)
		        {
			          if(Element_Length1==0)
			          goto Transmit;
			          if(ubIndex+Element_Length1>8)
				        goto Transmit;
	            
			          g_ulAddressTo_20ms=(uint32_t)(&CCP_Transmit[ubIndex]);
		            Ul_To_Pub_HF(g_pubAddressTo_20ms,g_ulAddressTo_20ms);
                Pub4_Move(g_pubAddressFrom_20ms, Element_Address1);
			          MEMORY_MOVE(g_pubAddressTo_20ms,g_pubAddressFrom_20ms,Element_Length1);
			          ubIndex+=Element_Length1;	
		        }
            Transmit:
		        CCP_vTransmit();
		        if(CAN0_Tx_TimeOut > 4)return;
   		  }
    }
   
}
/*****************************************************
** 
* \brief    Daq Cycle to upload.
* \author   Engineer
* \param    void
* \return   void
* \todo     
**
*****************************************************/
void CCP_vDAQTransmit_100ms(void)
{
    #define Element_Length2   	CCP_DaqList[2].pstOdt[j][k].ubLength
    #define Element_Address2  	CCP_DaqList[2].pstOdt[j][k].pubAddress
    #define ODT_Last2		       	CCP_DaqList[2].ubLast
    uint8_t i,j,k;
    uint8_t ubIndex;
    uint32_t g_ulAddressTo_100ms;
    uint8_t g_pubAddressTo_100ms[4];
    uint8_t g_pubAddressFrom_100ms[4];
    
	  if((CCP_Session_Status & SS_RUN)==0)
		    return;
   
    if(CCP_DaqList[2].ubFlags&DAQ_FLAG_START)
    {
	     // CCP_DaqList[i].ubFlags&=~DAQ_FLAG_START;
	      for(j=0;j<=ODT_Last2;j++)
	      {
	          if(j>=CCP_MAX_ODT)
		           goto Transmit;
		        ubIndex=1;           //7
            CCP_Transmit_PID=CCP_MAX_ODT*2+j;      
		        for(k=0;k<CCP_MAX_ODT_ENTRY;k++)
		        {
			          if(Element_Length2==0)
			          goto Transmit;
			          if(ubIndex+Element_Length2>8)
				        goto Transmit;
	              
			          g_ulAddressTo_100ms=(uint32_t)(&CCP_Transmit[ubIndex]);
		            Ul_To_Pub_HF(g_pubAddressTo_100ms,g_ulAddressTo_100ms);
                Pub4_Move(g_pubAddressFrom_100ms, Element_Address2);
			          MEMORY_MOVE(g_pubAddressTo_100ms,g_pubAddressFrom_100ms,Element_Length2);
			          ubIndex+=Element_Length2;	
		        }
            Transmit:
		        CCP_vTransmit();
		        if(CAN0_Tx_TimeOut > 4)return;
   		  }
    }
}












