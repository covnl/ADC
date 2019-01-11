/*******************************************************************************/
/**
Copyright (c) 2014 COMPANY_ECOTRONS
\file       ccp_driver.h
\brief      Init CPU ,Init Clock
\author     COMPANY_GC
\version    1.0
\date       Oct/ 2014
*/
/*******************************************************************************/
#ifndef __CCP_DRIVER_H
#define __CCP_DRIVER_H

extern struct STCCP g_stCCP;

#define CCP_Transmit_CTR 				(g_stCCP.pubCANTransmit[2])
#define CCP_Transmit_PID 				(g_stCCP.pubCANTransmit[0])
#define CCP_Transmit_ERR 				(g_stCCP.pubCANTransmit[1])
#define CCP_Transmit_ID_Length 			(g_stCCP.pubCANTransmit[3])
#define CCP_Transmit_Type 				(g_stCCP.pubCANTransmit[4])
#define CCP_Transmit_Availabitity_Mask 	(g_stCCP.pubCANTransmit[5])
#define CCP_Transmit_Protection_Mask 	(g_stCCP.pubCANTransmit[6])
#define CCP_Transmit_Address_Head		&(g_stCCP.pubCANTransmit[4])
#define CCP_Transmit_DataHead           &(g_stCCP.pubCANTransmit[3])
#define CCP_Transmit_Extension			(g_stCCP.pubCANTransmit[3])
#define CCP_Transmit_DAQ_Size 			(g_stCCP.pubCANTransmit[3])
#define CCP_Transmit_First_PID			(g_stCCP.pubCANTransmit[4])
#define CCP_Transmit  					(g_stCCP.pubCANTransmit)
#define CCP_Transmit_BuildChecksum_Size (g_stCCP.pubCANTransmit[3])


#define EVENT_MAP(__event,__process) case __event: __process();break;
#define CCP_StationAddress 			g_stCCP.uiStationAddress
#define CCP_LoadStationAddress()    g_stCCP.uiStationAddress=g_stCCP.pubCANReceive[3];g_stCCP.uiStationAddress<<=8;g_stCCP.uiStationAddress+=g_stCCP.pubCANReceive[2];

#define CCP_Session_Status    		g_stCCP.ubSessionStatus
#define CCP_User_SessionStatus		g_stCCP.ubUserSessionStatus
#define CCP_SendStatus				g_stCCP.ubSendStatus

#define CCP_Receive_ResourceMask g_stCCP.pubCANReceive[2]
#define CCP_Protection_Status g_stCCP.ubProtectionStatus
#define CCP_Transmit_ProtectionStatus (g_stCCP.pubCANTransmit[3])

#define CCP_Receive_CMD  			(g_stCCP.pubCANReceive[0])
#define CCP_Receive_CTR  			(g_stCCP.pubCANReceive[1])
#define CCP_Receive_MTA_Number  	(g_stCCP.pubCANReceive[2])
#define CCP_Receive_MTA_Extension 	(g_stCCP.pubCANReceive[3])
#define CCP_Receive_Address_0    	(g_stCCP.pubCANReceive[4])
#define CCP_Receive_Address_1    	(g_stCCP.pubCANReceive[5])
#define CCP_Receive_Address_2    	(g_stCCP.pubCANReceive[6])
#define CCP_Receive_Address_3    	(g_stCCP.pubCANReceive[7])
#define CCP_Receive_Data_Size		(g_stCCP.pubCANReceive[2])
#define CCP_Receive_Data_Head		&(g_stCCP.pubCANReceive[3])
#define CCP_Receive_DAQ_List     	(g_stCCP.pubCANReceive[2])
#define CCP_Receive_DAQ_Select      (g_stCCP.pubCANReceive[2])
#define CCP_Receive_ODT_Select		(g_stCCP.pubCANReceive[3])
#define CCP_Receive_Element_Select	(g_stCCP.pubCANReceive[4])
#define CCP_Receive_Daq_Mode		(g_stCCP.pubCANReceive[2])
#define CCP_Receive_DAQ_Select_2	(g_stCCP.pubCANReceive[3])
#define CCP_Receive_Last_ODT		(g_stCCP.pubCANReceive[4])
#define CCP_Receive_EventChannel	(g_stCCP.pubCANReceive[5])
#define CCP_Receive_RatePrescalerHead	&(g_stCCP.pubCANReceive[6])
#define CCP_Receive_DisconnectCmd   (g_stCCP.pubCANReceive[2])
#define CCP_Receive_StationAddressHead  &(g_stCCP.pubCANReceive[4])
#define CCP_Receive_Session_Status  (g_stCCP.pubCANReceive[2])
#define CCP_Receive_BuildChecksum_Len &(g_stCCP.pubCANReceive[2])
#define CCP_Receive_UPLOAD_DATASIZE  (g_stCCP.pubCANReceive[2])

#define CCP_ClearMemorySectorSize   &(g_stCCP.pubCANReceive[2])               //数据为[2]-[5]

#define CCP_MTA                		g_stCCP.ppubMTA
#define CCP_MTA_Current       		CCP_MTA[CCP_Receive_MTA_Number]
#define CCP_Flash_Page        CCP_MTA[0][1]
#define CCP_CurrentDaq				g_stCCP.ubCurrentDaq
#define CCP_CurrentOdt				g_stCCP.ubCurrentOdt
#define CCP_ODT_Entry        		(g_stCCP.pstOdtEntry)
#define CCP_DaqList             	(g_stCCP.pstDaqList)

//#define CCP_DaqStart(value)       (g_stCCP.pstDaqList[value].ubFlags = DAQ_FLAG_START)
#define CCP_DAQ_Stop	0
#define CCP_DAQ_Start	1
#define CCP_DAQ_Prepare	2
#define CCP_StationID g_stCCP.pbStationID
//PGM(Memery programming),DAQ(Data Acquistion),CAL(Calibration)
#define CCP_Resource_PGM   0x40
#define CCP_Resource_DAQ   2
#define CCP_Resource_CAL   1
#define Password_H     0x010203
#define Password_L     0x040506





//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Pub_To_Ul_HF(__ul,__pub) (__ul)=__pub[0];(__ul)<<=8;(__ul)+=(__pub)[1];(__ul)<<=8;(__ul)+=(__pub)[2];(__ul)<<=8;(__ul)+=(__pub)[3];
#define Pub_To_Ui_HF(__ui,__pub) (__ui)=(__pub)[0];(__ui)<<=8;(__ui)+=(__pub)[1];
#define Ul_To_Pub_HF(__pub,__ul) (__pub)[3]=(__ul)&0xff;(__ul)>>=8;(__pub)[2]=(__ul)&0xff;(__ul)>>=8;(__pub)[1]=(__ul)&0xff;(__ul)>>=8;(__pub)[0]=(__ul)&0xff;
#define Ui_To_Pub_HF(__pub,__ui) (__pub)[1]=(__ui)&0xff;(__ui)>>=8;(__pub)[0]=(__ui)&0xff;
#define Pub4_Move(__pubT,__pubF) (__pubT)[0]=(__pubF)[0];(__pubT)[1]=(__pubF)[1];(__pubT)[2]=(__pubF)[2];(__pubT)[3]=(__pubF)[3];
#define Pub2_Move(__pubT,__pubF) (__pubT)[0]=(__pubF)[0];(__pubT)[1]=(__pubF)[1];

#define Pub_To_Ul_LF(__ul,__pub) (__ul)=__pub[3];(__ul)<<=8;(__ul)+=(__pub)[2];(__ul)<<=8;(__ul)+=(__pub)[1];(__ul)<<=8;(__ul)+=(__pub)[0];
#define Pub_To_Ui_LF(__ui,__pub) (__ui)=(__pub)[1];(__ui)<<=8;(__ui)+=(__pub)[0];
#define Ul_To_Pub_LF(__pub,__ul) (__pub)[0]=(__ul)&0xff;(__ul)>>=8;(__pub)[1]=(__ul)&0xff;(__ul)>>=8;(__pub)[2]=(__ul)&0xff;(__ul)>>=8;(__pub)[3]=(__ul)&0xff;
#define Ui_To_Pub_LF(__pub,__ui) (__pub)[0]=(__ui)&0xff;(__ui)>>=8;(__pub)[1]=(__ui)&0xff;

#define ADDRESS_ADD(__addr,__v)  	g_stAddress.ubShortAdd=__v;g_stAddress.pubAddress=__addr;CCP_Address_vAdd();

#define ADDRESS_SUB(__addr,__v)  	g_stAddress.ubShortSub=__v;g_stAddress.pubAddress=__addr;Address_vSub();

#define MEMORY_MOVE(__To,__From,__Length) g_stMemery.pubFrom=(__From);g_stMemery.pubTo=(__To);g_stMemery.ulLength=(__Length);CCP_Memory_vMove();











#define CCP_DTO_ID        1           /* CAN identifier ECU -> Master */
#define CCP_CRO_ID        2           /* CAN identifier Master -> ECU */
#define g_uiCCPCANSendID  0x101
#define g_uiCCPCANReceiveID  0x100

/* Basic */
#define CC_CONNECT           0x01    
#define CC_SET_MTA           0x02
#define CC_DNLOAD            0x03
#define CC_UPLOAD            0x04
#define CC_TEST              0x05 /* V2.1 */
#define CC_START_STOP        0x06
#define CC_DISCONNECT        0x07
#define CC_START_STOP_ALL    0x08 /* V2.1 */
#define CC_SHORT_UPLOAD      0x0F
#define CC_GET_DAQ_SIZE      0x14
#define CC_SET_DAQ_PTR       0x15
#define CC_WRITE_DAQ         0x16
#define CC_EXCHANGE_ID       0x17
#define CC_GET_CCP_VERSION   0x1B /* V2.1 */
#define CC_GET_ECU_VERSION   0x1C  /*自定义*/
#define CC_Download_Password  0x1d  /*自定义*/
#define CC_DNLOAD_6           0x23

/* Optional */
#define CC_GET_CAL_PAGE      0x09
#define CC_SET_S_STATUS      0x0C
#define CC_GET_S_STATUS      0x0D
#define CC_BUILD_CHKSUM      0x0E
#define CC_CLEAR_MEMORY      0x10
#define CC_SET_CAL_PAGE      0x11
#define CC_GET_SEED          0x12
#define CC_UNLOCK            0x13
#define CC_PROGRAM           0x18
#define CC_MOVE_MEMORY       0x19
#define CC_DIAG_SERVICE      0x20
#define CC_ACTION_SERVICE    0x21
#define CC_PROGRAM_6          0x22
/* Vector extensions */

#define CC_PROGRAM_START     0x1F   /* Start flash kernel at MTA[0] */
#define CC_PROGRAM_END   0x1D   /* Prepare for flash kernel download */

#define CC_PROGRAM_ERROR_COUNTER  0x80
/* Returncodes */
#define CRC_OK                 0x00

/* C1 */
#define CRC_CMD_BUSY           0x10
#define CRC_DAQ_BUSY           0x11
#define CRC_KEY_REQUEST        0x18
#define CRC_STATUS_REQUEST     0x19

/* C2 */
#define CRC_COLD_START_REQUEST 0x20
#define CRC_CAL_INIT_REQUEST   0x21
#define CRC_DAQ_INIT_REQUEST   0x22
#define CRC_CODE_REQUEST       0x23

/* C3 (Errors) */
#define CRC_CMD_UNKNOWN        0x30
#define CRC_CMD_SYNTAX         0x31
#define CRC_OUT_OF_RANGE       0x32
#define CRC_ACCESS_DENIED      0x33
#define CRC_OVERLOAD           0x34
#define CRC_ACCESS_LOCKED      0x35

#define CCP_MAX_ODT          12
#define CCP_MAX_DAQ          3
#define CCP_MAX_ODT_ENTRY    4
/* Session Status */
#define SS_CAL                0x01
#define SS_DAQ                0x02
#define SS_RESUME             0x04
#define SS_TMP_DISCONNECTED   0x10
#define SS_CONNECTED          0x20
#define SS_STORE              0x40
#define SS_RUN                0x80

/* DAQ list */
#define DAQ_FLAG_START    0x01
#define DAQ_FLAG_SEND     0x02
#define DAQ_FLAG_PREPARED 0x04
#define DAQ_FLAG_OVERRUN  0x80

/*Extra Flash Read*/
#define CC_Extra_Flash_Read  0x86
#define CC_Extra_Flash_ChipErase  0x87

/*Updata PWMOUT2 DTY Freq*/
#define CC_Updata_PWMOUT2_DTY_Freq 0x88

struct STMemery
{
	uint8_t *pubFrom;
	uint8_t *pubTo;
	uint32_t ulLength;
};

struct STAddress
{
	uint8_t ubShortAdd;
	uint8_t ubShortSub;
	uint8_t*   pubAddress;
};

struct STOdtEntry
{
	uint8_t pubAddress[4];
	uint8_t ubLength;
};


struct STDaqList
{
  struct STOdtEntry pstOdt[CCP_MAX_ODT][CCP_MAX_ODT_ENTRY];
  uint16_t	uiPrescaler;
  uint16_t	uiCycle;
  uint8_t	ubEventChannel;
  uint8_t ubLast;
  uint8_t ubFlags;
};

#define CCP_STATION_ADDR   0x112
#define CCP_BROADCAST_STATION_ADDR 0



struct STCCP
{
	uint8_t pubCANTransmit[8];
	uint8_t pubCANTransmitLength;
	uint8_t pubCANReceive[8];
	
	uint8_t ubSessionStatus;
	uint8_t ubUserSessionStatus;
	uint8_t ubSendStatus;
	struct STDaqList pstDaqList[CCP_MAX_DAQ];
	uint8_t pbStationID[32];
	uint8_t ubProtectionStatus;//If set the bit,means the option is not protected.
	uint8_t ubCurrentDaq;
	uint8_t ubCurrentOdt;
	struct STOdtEntry* pstOdtEntry;
	uint8_t ppubMTA[2][4];
};






void CCP_Address_vSub(void);
void CCP_Address_vAdd(void);
void CCP_Memory_vMove(void);
uint32_t CCP_Convert_ub_To_ul(uint8_t* DataByte);
uint16_t CCP_GetCalibrationDataChecksum(uint16_t *CalDataStartAddr);
void CCP_vStopAllDaq(void);
void CCP_vStopDaq (void);
void CCP_vClearDaqList(UINT8 daq);
void CCP_vGetSeed(void);
void CCP_vTransmit(void);
void CCP_vCommandConnect(void);
void CCP_vCommandSetMTA(void);
void CCP_vCommandDNLoad(void);
void CCP_vCommandUpLoad(void);
void CCP_vCommandTest(void);
void CCP_vCommandStartStop(void);
void CCP_vCommandDisconnect(void);
void CCP_vCommandStartStopAll(void);
void CCP_vCommandShortUpLoad(void);
void CCP_vCommandDAQSize(void);
void CCP_vCommandDAQPtr(void);
void CCP_vCommandWriteDAQ(void);
void CCP_vCommandExchangeID(void);
void CCP_vCommandCCPVersion(void);
void CCP_vCommandECUVersion(void);
void CCP_vCommandDNload_Password(void);
void CCP_vCommandDNLoad_6(void);
void CCP_vCommandGetCalPage(void);
void CCP_vCommandSetSStatus(void);
void CCP_vCommandGetSStatus(void);
void CCP_vCommandBuildCheckSum(void);
void CCP_vCommandClearMemory(void);
void CCP_vCommandSetCalPage(void);
void CCP_vCommandGetSeed(void);
void CCP_vCommandUnLock(void);
void CCP_vCommandProgram(void);
void CCP_vCommandMoveMemory(void);
void CCP_vCommandDiagService(void);
void CCP_vCommandActionService(void);
void CCP_vCommandProgram_6(void);
void CCP_vCommandProcess(void);
void CCP_vDAQTransmit_Syn(void);
void CCP_vDAQTransmit_20ms(void);
void CCP_vDAQTransmit_100ms(void);
void clr_memory (void);
void CCP_delay(UINT16 j);
#endif







