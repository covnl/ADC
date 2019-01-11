#include "typedefs.h"


UINT8 kwp2000_Tgt;
UINT8 kwp2000_Src;
UINT8 Delay_Task10ms_PeriodicTransmit;//10ms发送数据包任务延迟20ms，为了解决混合发送时问题
UINT8 b_ResponsePending;
UINT8 b_ServiceOK;
UINT8 kwp2000_Checksum;
UINT8 *kwp2000_Datas;
UINT8 asc0_ComMode;
UINT8 headerSize;
UINT8 b_Transmitted;
UINT8 b_Received;
UINT8 rolling_counter_100ms;
UINT8 rolling_counter_10ms;
UINT8 rolling_counter_syn;    
UINT16 asc0_CommunicationBufReadPos;
UINT16 asc0_CommunicationBufWritePos;    
UINT8 kwp2000_Len;
UINT8 kwp2000_Format;
UINT8 kwp2000_ServiceId; 
UINT16 kwp2000_MessageSize_Flash;
UINT8 *kwp2000_MessageAddress;
UINT8 *kwp2000_Message;
UINT8 *Transmit_Complete_Ptr;
UINT8 *Package_Complete_Ptr;    
UINT8 Periodic_Parameter;
UINT16 SizeToReceive;

void (*asc0_KWP2000_HeaderAnalyse_Function)(void);
Receive_Com asc0_CommunicationBuf;
Transmit_Receive_Complete_Flag KWP2000_Flg;  

//UINT8 KWP2000_NumberOfPackage;/* 用来表示在第几个缓冲区进行打包 */

/* 当开始发送定时数据包时此位置0，定时任务数据包传送完成时此标志置1，即一旦开始发送就不允许被打断 */
UINT8 PeriodicTask_Transmit_Complete;
UINT8 PeriodicTask10ms_reserved1_Transmit_Complete;
UINT8 PeriodicTask10ms_reserved2_Transmit_Complete;
//UINT8 PeriodicTask10ms_reserved3_Transmit_Complete;


UINT8 PeriodicTask10ms_reserved1_Package_Complete;
UINT8 PeriodicTask10ms_reserved2_Package_Complete;
//UINT8 PeriodicTask10ms_reserved3_Package_Complete;
UINT8 PeriodicTask100ms_Package_Complete;
UINT8 PeriodicTasksyn_Package_Complete;
UINT8 PositiveResponse_Package_Complete;

UINT8 Packet;/* 在标定数据传输时存储数据包ID */
UINT16 Record_Download_Data_Len;//下载标定数据时用于记录数据的长度
UINT16 RAM_SerialNumber_Counter;    
UINT16 DownLoadAddress;    




extern UINT16 Rx_Length; 
extern UINT8 *pu8SCI_Receive_Data_ptr;
extern UINT8 *pu8SCI_Transmit_Data_ptr;
extern UINT16 Tx_Length;
extern UINT8 Syn_Minute;
extern UINT16 Syn_Ms;
extern UINT8 AfterRun_Flg;
extern UINT32 RAM_VAL_ECU_Passwd;
extern UINT8 Start_Syn_Counter;
extern UINT8 Task_Enable;
extern UINT8 LKT4200_Successful;
extern UINT8 AutoSend100msData;

//============定义ECU的所有版本号


#ifdef LLD_V10_5_2
  const volatile UINT8 Hardware_Version[16]={"V10_5_5"};  
#endif

#ifdef LLD_4T1CCD_IA
  const volatile UINT8 Hardware_Version[16]={"4T1CCD_IA"};  
#endif

#ifdef LLD_4T2CCD
  const volatile UINT8 Hardware_Version[16]={"4T2CCD"};  
#endif

#ifdef LLD_4T2CTH
  const volatile UINT8 Hardware_Version[16]={"4T2CTH"};  
#endif

#ifdef LLD_4T2C2IG
  const volatile UINT8 Hardware_Version[16]={"4T2C2IG"};  
#endif

#ifdef LLD_4T2C1IG
  const volatile UINT8 Hardware_Version[16]={"4T2C1IG"};  
#endif

#ifdef LLD_4T1CCD_TR
  const volatile UINT8 Hardware_Version[16]={"T1CCD_TR"};  
#endif

#ifdef LLD_4T1CTH_1_1
  const volatile UINT8 Hardware_Version[16]={"4T1CTH_1_1"};  
#endif  

#ifdef LLD_4T1CTH_IA_1_2
  const volatile UINT8 Hardware_Version[16]={"4T1CTH_IA1.2"};  
#endif 
  
#ifdef LLD_4T1CCD_IA_M1
  const volatile UINT8 Hardware_Version[16]={"4T1CCD_IA_M1"};  
#endif 
 
#ifdef LLD_4T1CTH_TR2_0M
  const volatile UINT8 Hardware_Version[16]={"4T1CTH_TR2.0M"};  
#endif 

#ifdef LLD_DF4T2C_IA
  const volatile UINT8 Hardware_Version[16]={"DF_4T2CIA1.1M"};  
#endif 

#ifdef LLD_V10_3W_HK
  const volatile UINT8 Hardware_Version[16]={"V10_3W_HK"};  
#endif

#ifdef LLD_4T2CCDB_1_1M
  const volatile UINT8 Hardware_Version[16]={"4T2CCDB_1.1M"};  
#endif

#ifdef LLD_4T2CCDA_1_1M
  const volatile UINT8 Hardware_Version[16]={"4T2CCDA_1.1M"};  
#endif

#ifdef LLD_4T2CCDA_C_1_0M
  const volatile UINT8 Hardware_Version[16]={"4T2CCDA_C_1.0M"};  
#endif
  /*硬件版本号 
                                                    --V10-5-2 & V10
                                                    --V1.1 & 4T1CCD-TR
                                                    --V1.1 & 4T1CTH-TR
                                                    --V1.1 & 4T2CCD   */
#ifdef STEP_MOTOR_CONTROL_FOR_IDLE
  #ifdef Step_ABDC
    const volatile UINT8 Software_LLD_Version[16]=
    {"L589_ABDC"}; //底层驱动版本号 
  #else
    const volatile UINT8 Software_LLD_Version[16]=
    {"L589_ACBD"}; //底层驱动版本号 
  #endif  
#else
  #ifdef STEP_MOTOR_PID_FOR_IDLE
    #ifdef Step_ABDC
      const volatile UINT8 Software_LLD_Version[16]=
      {"L589_ABDC_PID"}; //底层驱动版本号 
    #else
      const volatile UINT8 Software_LLD_Version[16]=
      {"L589_ACBD_PID"}; //底层驱动版本号 
    #endif
  #else  
    const volatile UINT8 Software_LLD_Version[16]=
    {"L589_AT35"}; //底层驱动版本号
  #endif  
#endif  

const volatile UINT8 Software_HLD_Version[16]=
{"SEA_b1771"}; /*应用程序版本号 
                                                    --b132 & SEA
                                                    --b131 & SE2B
                                          */          
//#ifdef Common_IGBT_2T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_1"}; 
//#endif

#ifdef Common_IGBT_4T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_2"}; 
#endif

#ifdef Common_CDI_2T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_3"}; 
#endif

#ifdef Common_CDI_4T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_4"}; 
#endif

#ifdef Ninja250                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_5"}; 
#endif

#ifdef JH600                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_6"}; 
#endif

#ifdef CDI_4T2C_V_2_Y                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_7"}; 
#endif

#ifdef Old_Engine                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_8"}; 
#endif

#ifdef EGT_2T2C                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_9"}; 
#endif

#ifdef Step_2T1C                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_10"}; 
#endif

#ifdef LiFan_2V49                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_11"}; 
#endif

#ifdef Linear_Motor                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_12"}; 
#endif

#ifdef TaiJia                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_13"}; 
#endif

#ifdef V2_2T2C                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_14"}; 
#endif

#ifdef PWM_2T2C                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_15"}; 
#endif

#ifdef CDI_4T_Step                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_16"}; 
#endif

#ifdef Step_IGBT4T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_17"}; 
#endif

#ifdef CDI2T_Wankel                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_18"}; 
#endif

#ifdef MD40_CrII1_0                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_19"}; 
#endif

#ifdef PWM_Step_2T1C                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_20"}; 
#endif

#ifdef Dual_Fuel_CDI4T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_21"}; 
#endif

#ifdef CDI4T_COP                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_22"}; 
#endif

#ifdef PWM_CDI_4T                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_23"}; 
#endif

#ifdef CDI_4T_Step_UN                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_24"}; 
#endif

#ifdef Step_2T1C_UN                                     
  const volatile UINT8 Software_CLD_Version[16]= {"CrII148_29"}; 
#endif


/*Crank 底层驱动
                                                    --V225 & IGBT_2T 
                                                    --V225 & IGBT_4T
                                                    --V225 & CDI_2T
                                                    --V225 & CDI_4T
                                                    --V225 & ONLY_MAP
                                                    --V225 & 4T_4Teeth                        
                                          */
                              

/* Definition of the services index table (Converts an Service Id in an Index for the table) (ROM Table) */
/************************************************************************
***    发送负响应
***
*************************************************************************/
void asc0_KWP2000_ServiceNegativeResponse(UINT8 ServiceID)
{
  //  UINT8 checksum;
    UINT8 i;
    asc0_CommunicationBuf.b_transmit[0] = 0x80;
    asc0_CommunicationBuf.b_transmit[1] = 0x8F;
    asc0_CommunicationBuf.b_transmit[2] = 0xEA;
    asc0_CommunicationBuf.b_transmit[3] = 0x02;
    asc0_CommunicationBuf.b_transmit[4] = 0x7F;
    asc0_CommunicationBuf.b_transmit[5] = ServiceID;
    asc0_CommunicationBuf.b_transmit[6] = (UINT8)(0x7A+ServiceID);
    for(i=0;i<7;i++)
    {
        if(SCISR1_TDRE == 1)  //发送数据寄存器空标志
        {  
           SCIDRL = asc0_CommunicationBuf.b_transmit[i];
           while(SCISR1_TC==0);
        }
    }
}

  

UINT8 asc0_KWP2000_ServiceNotImplemented(UINT8 *blokcByte)
 {
    UINT8 bufPos=0;
    
    *blokcByte =  KWP2000_NEGATIVERESPONSE;
    bufPos = 1;
    return(bufPos);
 }
 
UINT8 asc0_KWP2000_Diag_PeriodicTransmissionMode(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    UINT8 length;
    UINT8 data_byte;
    UINT8 headersize;
    UINT16 memoryAddress;
    
    *blockByte++ = KWP2000_STARTDIAGNOSTICSESSION_POSITIVERESPONSE;
    length = (kwp2000_Len-3)/3;/* 两个字节的地址代表一个变量 */
    
    for(length = 0;length<kwp2000_Len;length++)
    {
        data_byte=asc0_CommunicationBuf.b_receive[headersize+4];
        memoryAddress = (((UINT16)(asc0_CommunicationBuf.b_receive[headersize+5])<<8)|(asc0_CommunicationBuf.b_receive[headersize+6]));
        switch(data_byte)
        {
          case ONE_BYTE:  *(blockByte++)=*((UINT8 *)memoryAddress++); 
          break;
          case TWO_BYTES: *(UINT16 *)(blockByte) = *((UINT16 *)memoryAddress++);blockByte+=2;
          break;
          case FOUR_BYTES: *(UINT32 *)(blockByte) = *((UINT32 *)memoryAddress++); blockByte+=4;
          break;
          default:return FALSE;
          break;
        }
        bufPos += data_byte;
        headersize += 3;
    }
   return bufPos; 
}
/**************************************************************
**  标定数据的校验和计算
**
***************************************************************/
UINT16 Num;
UINT16 Calc_DataChecksum(void)
{
   UINT16 checksum=0;
   UINT16 MemoryAddress=0;
  // UINT16 *Addr_Ptr;
   
   MemoryAddress = RAM_CALC_Data;
  // Addr_Ptr = ((UINT16 *)MemoryAddress);
   for(Num=Calibration_Data_Length/2;Num>0;Num--)
   {
       checksum+=*((UINT16 *)MemoryAddress);
       MemoryAddress+=2;
   }
   if(Calibration_Data_Length%2)
   {
      checksum+=*((UINT8 *)MemoryAddress);//计算16位校验和，如果标定数据个数为奇数个，那么最后剩余的
   }//一个变量要加在低8位，
   return checksum;
}
/*******************************************************
** 传送标定数据的校验和、总长度、起始地址给PC机
**
********************************************************/
UINT8 asc0_KWP2000_CheckCalibrationData(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    UINT16 checksum;
    UINT16 memoryAddress;
    UINT16 memorySize;
    UINT16 Counter_ECU_temp;
    UINT16 Counter_Reset_temp;
    UINT16 Address;
    
       checksum=Calc_DataChecksum();
     
 
       memoryAddress = RAM_CALC_Data;/* 在烧写程序前从.MAP文件中将标定数据的长度与地址读出来直接写在这里 */
       memorySize = Calibration_Data_Length;         
       *blockByte++ = KWP2000_CHECKCALIBRATIONDATA_POSITIVERESPONSE;
       
       *(UINT16 *)(blockByte)= memorySize;/* 标定数据总长度 */
       blockByte+=2;
       //================================================== 
       *blockByte++ = (UINT8)(memoryAddress>>8);/* 标定数据起始地址高字节 */
       *blockByte++ = (UINT8)memoryAddress; /* 标定数据起始地址低字节 */
       *blockByte++ = (UINT8)(checksum>>8);
       *blockByte++ = (UINT8)checksum;
       bufPos+=7;
       
       Address = ROM_BOOT_VERSION_ADDRESS+4;
       if(*(UINT16 *)Address >= 0x0503 && *(UINT16 *)Address != 0xFFFF)
       {}       
       //======================2012-4-25
       *blockByte++ = LKT4200_Successful;
       bufPos+=1;  
       
       PositiveResponse_Package_Complete = TRUE;   
       return bufPos;
}

/*******************************************************
**  传送全部标定数据给PC机
**
********************************************************/
UINT8 asc0_KWP2000_TransmitCalibrationData(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    UINT8 i;
    static UINT16 memoryAddress;
    static UINT16 memorySize;
    
    if(Packet==0)
    {  
       KWP2000_Flg.Transmit_Calibration_Data_Complete=FALSE; 
       memoryAddress =RAM_CALC_Data;/* 在烧写程序前从.MAP文件中将标定数据的长度与地址读出来直接写在这里 */
       memorySize = Calibration_Data_Length;         
       *blockByte++ = KWP2000_TRANSMITCALIBRATIONDATA_POSITIVERESPONSE;
       *blockByte++ = ++Packet;/* 数据包ID */
       bufPos+=2;
       
       for(i=0;i<Calc_Data_Buf2;i++)
       {
           *(blockByte++)=*((UINT8 *)memoryAddress++);
           bufPos++;
           memorySize--;
       }
       PositiveResponse_Package_Complete = TRUE; 
       return bufPos; 
    }
    else 
    {
        *blockByte++ = KWP2000_TRANSMITCALIBRATIONDATA_POSITIVERESPONSE;
        *blockByte++ = ++Packet;/* 数据包ID */
        bufPos+=2;
        for(i=0;i<Calc_Data_Buf2;i++)
        {
           *(blockByte++)=*((UINT8 *)memoryAddress++); 
           bufPos++;
           memorySize--;
           if(memorySize==0) /* 如果标定数据发送完，立即退出 */
           {
              KWP2000_Flg.Transmit_Calibration_Data_Complete = TRUE;
              PositiveResponse_Package_Complete = TRUE;
              Packet = 0;/* 数据包ID恢复到初始值 */
              return bufPos; /* 如果此数据包未满但标定数据已经传送完成，立即退出开始传送 */
           }
            
        }
        PositiveResponse_Package_Complete = TRUE;
        return bufPos;
    }
}

/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_StartDiagnosticSession                  ***
*** Returns  : bufPos                                               ***
*** Inputs   : blockByte, b_CanStopDiag, kwp2000_Len, kwp2000_Datas ***
*** Outputs  : blockByte, b_ServiceOK, b_CanStopDiag                ***
*** Calls    : asc0_KWP2000_Diag_DefaultMode,                       ***
***            asc0_KWP2000_Diag_ECUProgrammingMode_Flash,          ***
***            asc0_KWP2000_Diag_ECUDevelopmentMode,                ***
***            asc0_KWP2000_NegativeResponse                        ***
*** Action   : Start a diagnostic session                           ***
*** Modified : 15/09/1997                                           ***
***                                                                 ***
**********************************************************************/
UINT8 asc0_KWP2000_StartDiagnosticSession(UINT8 *blockByte)
{
	UINT8 bufPos=0;
	UINT16 i;

      PeriodicTask_Transmit_Complete= TRUE;//发包完成标志置1，表示可以发送新的数据包了
			switch (asc0_CommunicationBuf.b_receive[headerSize+1])
			{
				/* Diagnostic default mode */
				case KWP2000_DIAG_DEFAULTMODE :

					break;
				/* Programming ECU mode */
				case KWP2000_DIAG_ECUPROGRAMMINGMODE :

					break;
				/* ECU development mode */
				case KWP2000_DIAG_ECUDEVELOPMENTMODE :

					break;
				/* ECU periodic transmission */	
			  case KWP2000_DIAG_ECUPERIODICTRANSMISSION:
			   /* 读取定时间隔参数 */
			    Periodic_Parameter = asc0_CommunicationBuf.b_receive[headerSize+2];
			    
			    Start_Syn_Counter=TRUE;
			    AutoSend100msData = FALSE; //====联机后停止自动广播数据
			    PeriodicTask100ms_Package_Complete = FALSE;
			    
			    if(Periodic_Parameter == PERIODIC_SYN)
			    { 
			         ///////////////////////////////////////////////////////////////////////////////////////////////////////
               //rolling_counter_syn =0;//滚动计数器清零
               /////////////////////////////////////////////////////////////////////////////////////////////////////////
			        /* 将变量的地址信息缓存起来，以便数据打包时调用 */
			        for(i = 0;i<(kwp2000_Len+5);i++)
			        {
			           asc0_CommunicationBuf.b_receive_syn[i]=asc0_CommunicationBuf.b_receive[i];
			        } 
			        
			        KWP2000_Flg.Periodic_Transmission_syn = TRUE; 
              PeriodicTasksyn_Package_Complete = FALSE; 
              KWP2000_Flg.Periodic_Package_syn = TRUE;
			       
			    }
			    else if(Periodic_Parameter == PERIODIC_10MS)
			    {
			        //////////////////////////////////////////////////////////////////////////////////////////////
              //rolling_counter_10ms =0;//滚动计数器清零
             ///////////////////////////////////////////////////////////////////////////////////////////////
			        for(i = 0;i<(kwp2000_Len+5);i++)
			        {
			           asc0_CommunicationBuf.b_receive_10ms[i]=asc0_CommunicationBuf.b_receive[i];
			        } 
			        
			        KWP2000_Flg.Periodic_Transmission_10ms = TRUE; 
              KWP2000_Flg.Periodic_Package_10ms = TRUE; 
              PeriodicTask10ms_reserved1_Package_Complete = FALSE;
			       
			    }
			    else if(Periodic_Parameter == PERIODIC_100MS)
			    {
			        //////////////////////////////////////////////////////////////////////////////////////////
              //rolling_counter_100ms=0;
              ///////////////////////////////////////////////////////////////////////////////////////////
			        for(i = 0;i<(kwp2000_Len+5);i++)
			        {
			           asc0_CommunicationBuf.b_receive_100ms[i] = asc0_CommunicationBuf.b_receive[i];
			        } 
			        KWP2000_Flg.Periodic_Transmission_100ms = TRUE;
              PeriodicTask100ms_Package_Complete =FALSE;
              KWP2000_Flg.Periodic_Package_100ms = TRUE;
			    }
			    else
			    {
			        /* error */
			        return FALSE;
			    }
  		    /* ECU接收到定时信息后先做准备工作，准备好了就给PC机一个正响应，然后等待PC机的开始传送命令 */
			   *blockByte++ = KWP2000_STARTDIAGNOSTICPREPARE_POSITIVERESPONSE;
		     *blockByte   = Periodic_Parameter;
		     bufPos=2;
         b_ServiceOK=TRUE;
         break;
				/* Other diagnostic mode */
				default :
					/* Diagnostic mode not implemented */
					/* Prepares the negative response */
				  	return FALSE;
		  	break;
			}
			
   PositiveResponse_Package_Complete = TRUE;   
	return(bufPos);
} 
/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_StopDiagnosticSession                   ***
*** Returns  : bufPos                                               ***
*** Inputs   :                                                      ***
*** Outputs  :                                                      ***
*** Action   : Stop a diagnostic session                            ***
*** Modified : 15/09/1997                                           ***
***                                                                 ***
**********************************************************************/
UINT8 asc0_KWP2000_StopDiagnosticSession(UINT8 *blockByte)
{
	  UINT8 bufPos=0;
    UINT8 periodic_parameter;
    UINT8 version;
    
    AutoSend100msData = FALSE; //====联机后停止自动广播数据
    PeriodicTask100ms_Package_Complete = FALSE;
    
    periodic_parameter = asc0_CommunicationBuf.b_receive[headerSize+1];
    if(asc0_CommunicationBuf.b_receive[headerSize-1]==3)
    {
        version = asc0_CommunicationBuf.b_receive[headerSize+2];
    }
    else
    {
        version = 0;
    }
    
  //  switch(periodic_parameter)
   // {
  //   case PERIODIC_SYN:
  //                      KWP2000_Flg.Periodic_Transmission_syn = FALSE;/* 定时发送标志清零，将停止定时发送任务 */
  //                      KWP2000_Flg.Periodic_Package_syn = FALSE;     /* 定时打包标志清零，将停止定时打包任务 */
  //                      PeriodicTasksyn_Package_Complete = TRUE;
  //   break;
  //    case PERIODIC_10MS:
  //                      KWP2000_Flg.Periodic_Transmission_10ms = FALSE;/* 定时发送标志清零，将停止定时发送任务 */
  //                      KWP2000_Flg.Periodic_Package_10ms = FALSE;     /* 定时打包标志清零，将停止定时打包任务 */
 //                       PeriodicTask10ms_reserved1_Package_Complete = TRUE;
   //   break;
   //   case PERIODIC_100MS:
   //                     KWP2000_Flg.Periodic_Transmission_100ms = FALSE; /* 定时发送标志清零，将停止定时发送任务 */
   //                     KWP2000_Flg.Periodic_Package_100ms = FALSE;      /* 定时打包标志清零，将停止定时打包任务 */
   //                     PeriodicTask100ms_Package_Complete =TRUE;
   //   break;
  //    default: b_ServiceOK=TRUE;
  //             return bufPos;           
  //    break;
   // }
   //  SCICR2_TCIE = 0;/* 关闭发送完成中断 */
    if(version>=6 && version < 128) //以此限制老版ProCAL与新版软件通讯
    //if(version == 128)//======128--Richard客户
    //if(version == 129)//======129--MBE客户
    //if(version == 130)//======130--2T2CEGT客户/意大利Matteo客户 
    {
        *blockByte++ = KWP2000_STOPDIAGNOSTICSESSION_POSITIVERESPONSE;
    }
    else
    {
        *blockByte++ = PROCAL_VERSION_MISMATCH_POSITIVERESPONSE;
    }
    *blockByte++ = periodic_parameter;
    bufPos+=2;
    KWP2000_PeriodicTaskTransmit_Disable();
    //asc0_KWP2000_ProtocolInit_FLASH();
    b_ServiceOK=TRUE;
    PositiveResponse_Package_Complete = TRUE;
  	return (bufPos);
}
/***************************************************************************
**开始传定时数据送命令函数
**
****************************************************************************/

UINT8 asc0_KWP2000_StartPeriodicTransmit(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    UINT8 periodic_parameter;
    
    /* 取得定时参数 */
    periodic_parameter =  asc0_CommunicationBuf.b_receive[headerSize+1];
    switch(periodic_parameter)
    {
      case PERIODIC_SYN: //KWP2000_Flg.Periodic_Transmission_syn = TRUE; 
                         //PeriodicTasksyn_Package_Complete = FALSE; 
                         //KWP2000_Flg.Periodic_Package_syn = TRUE;  
                         
      break; /* 同步传送任务开始执行 */
      case PERIODIC_10MS:// KWP2000_Flg.Periodic_Transmission_10ms = TRUE; 
                         // KWP2000_Flg.Periodic_Package_10ms = TRUE; 
                         // PeriodicTask10ms_reserved1_Package_Complete = FALSE;
      break; /* 10ms定时任务开始执行 */
      case PERIODIC_100MS:// KWP2000_Flg.Periodic_Transmission_100ms = TRUE;
                          // PeriodicTask100ms_Package_Complete =FALSE;
                          // KWP2000_Flg.Periodic_Package_100ms = TRUE;
                           
      break;/* 100ms定时任务开始发送 */
      default:return FALSE;break;
    }
    Start_Syn_Counter=1;
    *blockByte++ = KWP2000_STARTPERIODICTRANSMIT_POSITIVERESPONSE;
    *blockByte = periodic_parameter;
    bufPos = 2;
    
    AutoSend100msData = FALSE; //====联机后停止自动广播数据
    PeriodicTask100ms_Package_Complete = FALSE;
    
    b_ServiceOK=TRUE;
    PositiveResponse_Package_Complete = TRUE;
    return bufPos; /* 当接收到开始定时传送命令后不会给PC机响应，因为当定时时间到时，便会传送数据 */
}

/***************************************************************************
** 10ms定时的打包任务
** 此函数放在10ms的中断函数中进行
** 10ms的发送缓冲区有3个，当第一个缓冲区未发送打包任务
****************************************************************************/


UINT8 KWP2000_Task10ms_PeriodicGetData()
{
    UINT8 bufPos=0;
    UINT8 length;
    UINT8 data_byte;
    UINT8 headersize;
    UINT16 memoryAddress;
    UINT8 *blockByte;
    
    
    
    
    //if((Periodic_Package_100ms==TRUE)&&(KWP2000_PeriodicTask100ms_Package_Complete==TRUE))
    if(KWP2000_Flg.Periodic_Package_10ms==TRUE)
    {
        if(PeriodicTask10ms_reserved1_Package_Complete == FALSE)
        {
          
           // KWP2000_PeriodicTask100ms_Package_Complete=FALSE;/* 打包完成标志清零 */
            headersize = 4; /* 先把头字节储存起来 */
            length =  (asc0_CommunicationBuf.b_receive_10ms[headersize-1]-4)/3;/* 获得变量的总长度 */
            
            if(length==0) return FALSE;

             blockByte = &asc0_CommunicationBuf.b_transmit_10ms[0];

            *blockByte++ = 0x80;/* 格式字节设为0 */
    	      *blockByte++= 0x8F;
    	      *blockByte++ = 0xEA;
    	      *blockByte++ = 0;//len     
            *blockByte++ = KWP2000_STARTDIAGNOSTICSESSION_POSITIVERESPONSE;
            *blockByte++ = PERIODIC_10MS;
            *blockByte++ = Syn_Minute;
            *blockByte++ = (UINT8)(Syn_Ms>>8);
            *blockByte++ = (UINT8)Syn_Ms;
            
           
            bufPos +=5;
                 
            for(;length>0;length--)
            {
                data_byte=asc0_CommunicationBuf.b_receive_10ms[headersize+4];
                memoryAddress = (((UINT16)(asc0_CommunicationBuf.b_receive_10ms[headersize+5])<<8)|(asc0_CommunicationBuf.b_receive_10ms[headersize+6]));
                switch(data_byte)
                {
                  case ONE_BYTE:  *(blockByte++)=*((UINT8 *)memoryAddress++); 
                  break;
                  case TWO_BYTES: *(UINT16 *)(blockByte) = *((UINT16 *)memoryAddress++);blockByte+=2;
                  break;
                  case FOUR_BYTES: *(UINT32 *)(blockByte) = *((UINT32 *)memoryAddress++); blockByte+=4;
                  break;
                  default:return FALSE;break;
                }
                bufPos += data_byte;
                headersize += 3;
            }
        
            /* Calculate the size of the message (without CS) */
    	      	kwp2000_MessageSize_Flash=4+bufPos;
 
        	    /* 数据包的长度 */
        	    asc0_CommunicationBuf.b_transmit_10ms[3] = bufPos;
        	   	/* Defines the beginning address of the message */
        	    kwp2000_MessageAddress=&(asc0_CommunicationBuf.b_transmit_10ms[0]);
        		  /* Calculates the checksum and write it in the buffer and increments the message size */
        	  	asc0_CommunicationBuf.b_transmit_10ms[4+bufPos]=kwp2000_Checksum_Calc(kwp2000_MessageAddress,kwp2000_MessageSize_Flash++);
            
              PeriodicTask10ms_reserved1_Package_Complete=TRUE;/* 打包完成标志置1 */
        }
       return TRUE;
    }
    return FALSE;
}

/***************************************************************************
**  同步传送的打包任务
**  这个函数放在同步中断中进行
****************************************************************************/

UINT8 KWP2000_Tasksyn_PeriodicGetData(UINT16 missing_tooth_period)
{
    UINT8 bufPos=0;
    UINT8 length;
    UINT8 data_byte;
    UINT8 headersize;
    UINT16 memoryAddress;
    UINT8 *blockByte;
   // static UINT8 rolling_counter=0;/* 滚动计数器 */
    
    
    
   //if((Periodic_Package_syn==TRUE)&&(KWP2000_PeriodicTasksyn_Package_Complete==TRUE))
    if(KWP2000_Flg.Periodic_Package_syn==TRUE)
    {
    
       if(PeriodicTasksyn_Package_Complete == FALSE)
       {
            // KWP2000_PeriodicTasksyn_Package_Complete=FALSE;/* 打包完成标志清零 */
            headersize = 4;
            length =  (asc0_CommunicationBuf.b_receive_syn[headersize-1]-4)/3;/* 获得变量的总长度 */
            if(length==0) return FALSE; 
                     
            blockByte = &asc0_CommunicationBuf.b_transmit_syn[4];
            *blockByte++ = KWP2000_STARTDIAGNOSTICSESSION_POSITIVERESPONSE;
            *blockByte++ = PERIODIC_SYN;
            *blockByte++ = Syn_Minute; 
            *blockByte++ =(UINT8)(missing_tooth_period>>8);  /* 时间差高字节，把两次同步的时间差计算出来，加到数据包中发给PC机， */
            *blockByte++ = (UINT8)missing_tooth_period;  /* 时间差低字节 */
            bufPos += 5;
                
             for(;length>0;length--)
            {
                data_byte=asc0_CommunicationBuf.b_receive_syn[headersize+4];
                memoryAddress = (((UINT16)(asc0_CommunicationBuf.b_receive_syn[headersize+5])<<8)|(asc0_CommunicationBuf.b_receive_syn[headersize+6]));
                switch(data_byte)
                {
                  case ONE_BYTE:  *(blockByte++)=*((UINT8 *)memoryAddress++); 
                  break;
                  case TWO_BYTES: *(UINT16 *)(blockByte) = *((UINT16 *)memoryAddress++);blockByte+=2;
                  break;
                  case FOUR_BYTES: *(UINT32 *)(blockByte) = *((UINT32 *)memoryAddress++); blockByte+=4;
                  break;
                  default: return FALSE;break;
                }
                bufPos += data_byte;
                headersize += 3;
            }
        
           /* Calculate the size of the message (without CS) */
    	    	kwp2000_MessageSize_Flash=4+bufPos;
    	    	asc0_CommunicationBuf.b_transmit_syn[0] = 0x80;/* 格式字节设为0 */
    	    	asc0_CommunicationBuf.b_transmit_syn[1] = 0x8F;
    	    	asc0_CommunicationBuf.b_transmit_syn[2] = 0xEA;
    	  	  /* 数据字节的长度 */
    	    	asc0_CommunicationBuf.b_transmit_syn[3] = bufPos;
    	    	/* Defines the beginning address of the message */
    	    	kwp2000_MessageAddress=&(asc0_CommunicationBuf.b_transmit_syn[0]);
    		    /* Calculates the checksum and write it in the buffer and increments the message size */
    	    	asc0_CommunicationBuf.b_transmit_syn[4+bufPos]=kwp2000_Checksum_Calc(kwp2000_MessageAddress,kwp2000_MessageSize_Flash++);
        
            PeriodicTasksyn_Package_Complete=TRUE;/* 打包完成标志置1 */
       }
       return TRUE;
    }
    return FALSE;
}

/***************************************************************************
** 10ms定时的打包任务
** 这个函数放在100ms中断函数内
****************************************************************************/

UINT8 KWP2000_Task100ms_PeriodicGetData(void)
{
    UINT8 bufPos=0;
    UINT8 length;
    UINT8 data_byte;
    UINT8 headersize;
    UINT16 memoryAddress;
    UINT8 *blockByte;
    
    
    
    
    //if((Periodic_Package_100ms==TRUE)&&(KWP2000_PeriodicTask100ms_Package_Complete==TRUE))
    if(AutoSend100msData == TRUE)
    {
        blockByte = &asc0_CommunicationBuf.b_transmit_100ms[4];
        
        *blockByte++ = KWP2000_STARTDIAGNOSTICSESSION_POSITIVERESPONSE;
        *blockByte++ = PERIODIC_100MS_Auto;
        
        *blockByte++ =(UINT8)(HLS_RPM >> 8);
        *blockByte++ =(UINT8)HLS_RPM;
        
        *blockByte++ =(UINT8)(HLS_MAP >> 8);
        *blockByte++ =(UINT8)HLS_MAP;
                
        *blockByte++ =(UINT8)(HLS_TPS >> 8);
        *blockByte++ =(UINT8)HLS_TPS;
        
        *blockByte++ =(UINT8)(HLS_ECT >> 8);
        *blockByte++ =(UINT8)HLS_ECT;
        
        *blockByte++ =(UINT8)(HLS_IAT >> 8);
        *blockByte++ =(UINT8)HLS_IAT;
        
        *blockByte++ =(UINT8)(HLS_O2S >> 8);
        *blockByte++ =(UINT8)HLS_O2S;
        
        *blockByte++ =(UINT8)(HLS_SPARK >> 8);
        *blockByte++ =(UINT8)HLS_SPARK;
        
        *blockByte++ =(UINT8)(HLS_FUELPW1 >> 8);
        *blockByte++ =(UINT8)HLS_FUELPW1;
        
        *blockByte++ =(UINT8)(HLS_FUELPW2 >> 8);
        *blockByte++ =(UINT8)HLS_FUELPW2;
        
        *blockByte++ =(UINT8)(HLS_BatteryVol >> 8);
        *blockByte++ =(UINT8)HLS_BatteryVol;
        
        bufPos += 22;
        KWP2000_Flg.Periodic_Transmission_100ms = TRUE;
         
        kwp2000_MessageSize_Flash = 4+bufPos;
        asc0_CommunicationBuf.b_transmit_100ms[0] = 0x80;/* 格式字节设为0 */
        asc0_CommunicationBuf.b_transmit_100ms[1] = 0x8F;
        asc0_CommunicationBuf.b_transmit_100ms[2] = 0xEA;
        /* 数据包的长度 */
        asc0_CommunicationBuf.b_transmit_100ms[3] = bufPos;
        /* Defines the beginning address of the message */
        kwp2000_MessageAddress=&(asc0_CommunicationBuf.b_transmit_100ms[0]);
        /* Calculates the checksum and write it in the buffer and increments the message size */
        asc0_CommunicationBuf.b_transmit_100ms[4+bufPos]=kwp2000_Checksum_Calc(kwp2000_MessageAddress,kwp2000_MessageSize_Flash++);
            
         PeriodicTask100ms_Package_Complete=TRUE;/* 打包完成标志置1 */
        return TRUE;   
    }
    else
    {
      
        if(KWP2000_Flg.Periodic_Package_100ms==TRUE)
        {
            if (PeriodicTask100ms_Package_Complete == FALSE)
            {
                // KWP2000_PeriodicTask100ms_Package_Complete=FALSE;/* 打包完成标志清零 */
                headersize = 4; /* 先把头字节储存起来 */
                length =  (asc0_CommunicationBuf.b_receive_100ms[headersize-1]-4)/3;/* 获得变量的总长度 */
                if(length==0) return FALSE;
                
                blockByte = &asc0_CommunicationBuf.b_transmit_100ms[4];
                *blockByte++ = KWP2000_STARTDIAGNOSTICSESSION_POSITIVERESPONSE;
                *blockByte++ = PERIODIC_100MS;
                *blockByte++ = Syn_Minute;
                *blockByte++ = (UINT8)(Syn_Ms>>8);
                *blockByte++ = (UINT8)Syn_Ms;
                
               
                bufPos +=5;
                     
                for(;length>0;length--)
                {
                    data_byte=asc0_CommunicationBuf.b_receive_100ms[headersize+4];
                    memoryAddress = (((UINT16)(asc0_CommunicationBuf.b_receive_100ms[headersize+5])<<8)|(asc0_CommunicationBuf.b_receive_100ms[headersize+6]));
                    switch(data_byte)
                    {
                      case ONE_BYTE:  *(blockByte++)=*((UINT8 *)memoryAddress++); 
                      break;
                      case TWO_BYTES: *(UINT16 *)(blockByte) = *((UINT16 *)memoryAddress++);blockByte+=2;
                      break;
                      case FOUR_BYTES: *(UINT32 *)(blockByte) = *((UINT32 *)memoryAddress++); blockByte+=4;
                      break;
                      default:return FALSE;break;
                    }
                    bufPos += data_byte;
                    headersize += 3;
                }
            
                /* Calculate the size of the message (without CS) */
        	      	kwp2000_MessageSize_Flash=4+bufPos;
        	      	asc0_CommunicationBuf.b_transmit_100ms[0] = 0x80;/* 格式字节设为0 */
        	      	asc0_CommunicationBuf.b_transmit_100ms[1] = 0x8F;
        	      	asc0_CommunicationBuf.b_transmit_100ms[2] = 0xEA;
        	       	/* 数据包的长度 */
        	      	asc0_CommunicationBuf.b_transmit_100ms[3] = bufPos;
        	      	/* Defines the beginning address of the message */
        	      	kwp2000_MessageAddress=&(asc0_CommunicationBuf.b_transmit_100ms[0]);
        		      /* Calculates the checksum and write it in the buffer and increments the message size */
        	  	    asc0_CommunicationBuf.b_transmit_100ms[4+bufPos]=kwp2000_Checksum_Calc(kwp2000_MessageAddress,kwp2000_MessageSize_Flash++);
            
               PeriodicTask100ms_Package_Complete=TRUE;/* 打包完成标志置1 */
            }
            return TRUE;
        }
        
    }
    return FALSE;
}

/***************************************************************************
** 10ms定时的传送任务
**放在10ms的任务调度中，在API中断中确定任务调度的线程，在中断函数外判断任务
**线程然后执行
****************************************************************************/
void KWP2000_Task10ms_PeriodicTransmission(void)
{
     if((KWP2000_Flg.Periodic_Transmission_10ms == TRUE)&&(PeriodicTask_Transmit_Complete==TRUE)) /* 当开始传送命令到来时才开始传送数据 */
     {
            /* 传送完成标志置0，表示必须等这个数据包发送完成方可发送其他定时数据包，它置1操作发生在SCI发送中断 */
            PeriodicTask_Transmit_Complete=FALSE;

            Package_Complete_Ptr=&PeriodicTask10ms_reserved1_Package_Complete; 
            pu8SCI_Transmit_Data_ptr = &asc0_CommunicationBuf.b_transmit_10ms[0];
            /* Tx_Length = 数据字节长度 + 头字节长度 + 校验字节 */
            Tx_Length = asc0_CommunicationBuf.b_transmit_10ms[3]+5;

            //SCICR2_TCIE = 1;/* 打开发送中断后会立即进入中断函数 */
            SCI_TC_INTERRUPT(ENABLED);
     }
}
/***************************************************************************
** 100ms定时的传送任务
**
****************************************************************************/

void KWP2000_Task100ms_PeriodicTransmission(void)
{
     if((KWP2000_Flg.Periodic_Transmission_100ms == TRUE)&&(PeriodicTask_Transmit_Complete==TRUE)) /* 当开始传送命令到来时才开始传送数据 */
     {
            /* 传送完成标志置0，表示必须等这个数据包发送完成方可发送其他定时数据包，它置1操作发生在SCI发送中断 */
            PeriodicTask_Transmit_Complete=FALSE;
            //Transmit_Complete_Ptr = &PeriodicTask_Transmit_Complete;
            Package_Complete_Ptr=&PeriodicTask100ms_Package_Complete; 
            pu8SCI_Transmit_Data_ptr = &asc0_CommunicationBuf.b_transmit_100ms[0];
            /* Tx_Length = 数据字节长度 + 头字节长度 + 校验字节 */
            Tx_Length = asc0_CommunicationBuf.b_transmit_100ms[3]+5;
            //SCICR2_TCIE = 1;/* 打开发送中断后会立即进入中断函数 */
            SCI_TC_INTERRUPT(ENABLED);
     }
}
/***************************************************************************
**同步的传送任务
**
****************************************************************************/
void KWP2000_Tasksyn_PeriodicTransmission(void)
{
    if((KWP2000_Flg.Periodic_Transmission_syn == TRUE)&&(PeriodicTask_Transmit_Complete==TRUE))/* 当开始传送命令到来时才开始传送数据 */
    {

           PeriodicTask_Transmit_Complete=FALSE;
           //Transmit_Complete_Ptr = &PeriodicTask_Transmit_Complete;
           Package_Complete_Ptr=&PeriodicTasksyn_Package_Complete; 
           pu8SCI_Transmit_Data_ptr = &asc0_CommunicationBuf.b_transmit_syn[0];
           /* Tx_Length = 数据字节长度 + 头字节长度 + 校验字节 */
           Tx_Length = asc0_CommunicationBuf.b_transmit_syn[3]+5;
           //SCICR2_TCIE = 1;/* 打开发送中断后会立即进入中断函数 */
           SCI_TC_INTERRUPT(ENABLED);

    }
}
/***************************************************************************
**  当一个数据包发送完成后调用此函数，用来判断当发送完一个数据包后是否有
**  其他任务在等待，如果有，要及时发送
****************************************************************************/
void KWP2000_Verify_PeriodicTransmission()
{
   //////////////////////判断有没有正响应需要发送///////////////////////////////////////////////////// 
    // if(PositiveResponse_Package_Complete)
     //{
         //
         //*Transmit_Complete_Ptr=FALSE;/* 发包完成标志置0，表示不可以发送定时数据包 */
         //Delay_Task10ms_PeriodicTransmit=TRUE;
        // Positive_Response_Normal_Transmit();
        // PositiveResponse_Package_Complete = FALSE;//发送完正响应后数据包后将标志复
     //}
    //////////////////////////////////////////////////////////////////////////////////////////////////
    if(PeriodicTasksyn_Package_Complete)
    {
        KWP2000_Tasksyn_PeriodicTransmission();
    }
    else if(PeriodicTask10ms_reserved1_Package_Complete)
    {
        KWP2000_Task10ms_PeriodicTransmission();
    }
    else if(PeriodicTask100ms_Package_Complete)
    {
        KWP2000_Task100ms_PeriodicTransmission();
    }    
    else
    {
        //SCICR2_TCIE = 0;/* 当没有数据包打包完成时，屏蔽发送完成中断 */       
        SCI_TC_INTERRUPT(DISABLED);
    }
}
  
 /*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Engineer
* \param    void
* \return   void
*/ 
UINT8 asc0_KWP2000_ReadDataByLocalIdentifier(UINT8 *blockByte) 
{
    UINT8   bufPos;
    UINT16  memoryAddress;
    UINT8   length;
    UINT8   i;
    UINT8   data_byte;
    UINT8   headersize;
    
    
    headersize = headerSize;
    length = (kwp2000_Len-1)/3;
    
    *blockByte++ = KWP2000_READDATABYLOCALIDENTIFIER_POSITIVERESPONSE;
    
    for(i=0;i<length;i++)
    {
        data_byte=asc0_CommunicationBuf.b_receive[headersize+1];
        memoryAddress = (((UINT16)(asc0_CommunicationBuf.b_receive[headersize+2])<<8)|(asc0_CommunicationBuf.b_receive[headersize+3]));
        switch(data_byte)
        {
          case ONE_BYTE:  *(blockByte++)=*((UINT8 *)memoryAddress++); 
          break;
          case TWO_BYTES: *(UINT16 *)(blockByte) = *((UINT16 *)memoryAddress++);blockByte+=2;
          break;
          case FOUR_BYTES: *(UINT32 *)(blockByte) = *((UINT32 *)memoryAddress++); blockByte+=4;
          break;
          default:break;
        }
        bufPos += data_byte;
        headersize +=3;/* 每三个字节的信息表示一个变量 */
    }
    
	  b_ServiceOK=TRUE;
	 
   return(bufPos);
}

/*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Engineer
* \param    void
* \return   void
*/
 UINT8 asc0_KWP2000_WriteDataByLocalIdentifier(UINT8 *blockByte)
 {
    UINT8   bufPos=0;
    UINT16  memoryAddress;
    UINT8   length;
    UINT8   databyte;
    UINT8   headersize;
    UINT8   variable_size=0;/* 接收到得变量的个数 */
    UINT8 *dataValue_ptr;
    
    headersize = headerSize;
    length = kwp2000_Len;
    bufPos+=2;/* 数据字节中服务ID和数据包ID占用了两个字节，此处要加上 */
    length -= bufPos;/*  */
    do
    {
        
        databyte = asc0_CommunicationBuf.b_receive[headersize+bufPos];
        bufPos++;
        memoryAddress = (((UINT16)asc0_CommunicationBuf.b_receive[headersize+bufPos]<<8)|(asc0_CommunicationBuf.b_receive[headersize+bufPos+1]));
        bufPos+=2;/* 变量字节数和变量地址占用了3个字节，此处要加上 */
        dataValue_ptr = &asc0_CommunicationBuf.b_receive[headersize+bufPos];
        switch(databyte)
        {
            
          case ONE_BYTE:*((UINT8 *)memoryAddress++) = *dataValue_ptr; bufPos++;length-=4;/* 如果变量的值是字节类型的，bufPos要加1 */
          break;
          case TWO_BYTES:*((UINT16 *)memoryAddress++) = *(UINT16 *)dataValue_ptr;bufPos+=2;length-=5; /* 如果变量的值是字类型的，bufPos要加2 */
          break;
          case FOUR_BYTES:*((UINT32 *)memoryAddress++) = *(UINT32 *)dataValue_ptr;bufPos+=4;length-=7;/* 如果变量的值是双字类型的，bufPos要加4 */ 
          break;
          default:break;
        }
        
        variable_size++;
          
    }while(length>0);
    
    *blockByte++ = KWP2000_WRITEDATABYLOCALIDENTIFIER_POSITIVERESPONSE; /* 正响应 */
    *blockByte = variable_size;/* 将接收到变量的个数返回给PC机 */
    bufPos=2;
    b_ServiceOK=TRUE;
    PositiveResponse_Package_Complete = TRUE;
    return bufPos;
 }
/*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Engineer
* \param    void
* \return   void
*/ 
UINT8 KWP2000_ReadMemoryByAddress(UINT8 *blockByte)
{
    UINT16  memoryAddress;
    UINT8   memorySize;
    UINT8   i;
    UINT8   bufPos=0;
    UINT8 PasswdStart;
    
   /* UINT8 *point_address;   */
    memoryAddress = (((UINT16)asc0_CommunicationBuf.b_receive[headerSize+2]<<8)|(asc0_CommunicationBuf.b_receive[headerSize+3]));/* Load 16 bit address */
    memorySize = asc0_CommunicationBuf.b_receive[headerSize+4];   /* Store memory size */
    
    //==2014-2-25==B_Passwd逻辑取反，保证标定数据bit为1时，不需要密码，否则客户下载一半再下载的话就该要密码了
    
    if(HLS_B_Passwd == FALSE)//====需要密码
    {
        PasswdStart = asc0_CommunicationBuf.b_receive[3] + headerSize - 6;
        if(KWP2000_CheckPasswordBeforeDownloadOrUpload(&asc0_CommunicationBuf.b_receive[PasswdStart])==FALSE)
        {
            *blockByte++ = KWP2000_NEGATIVERESPONSE;
            *blockByte++ = DOWNLOAD_PASSWORDFAILED_NEGATIVERESONSE; /* Load the address to transmit databyte */
		        bufPos=2;
            return bufPos;        
        }
    }
        
    *blockByte = KWP2000_READMEMORYBYADDRESS_POSITIVERESPONSE;/* Load service ID */ 
    for(i=0;i<memorySize;i++)
    {
        *(++blockByte)=*((UINT8 *)memoryAddress++); /* 强制转换为一个指针,start copy data*/
    }
    
    bufPos = 1 + memorySize;
		/* Sets the serviceOK flag */
	  b_ServiceOK=TRUE;
	 
   return(bufPos);
}
/*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Engineer
* \param    void
* \return   void
*/ 
UINT8 KWP2000_WriteMemoryByAddress(UINT8 *blockByte)
{
    UINT16  memoryAddress;
    UINT8   memorySize;
    UINT8 i;
    UINT8 bufPos=0;
    UINT8 Memory_Type;
    UINT8 PasswdStart;
   /* UINT8 *point_address;   */
    
    
    memoryAddress = (((UINT16)asc0_CommunicationBuf.b_receive[headerSize+2]<<8)|(asc0_CommunicationBuf.b_receive[headerSize+3]));/* Load 16 bit address */
    memorySize = asc0_CommunicationBuf.b_receive[headerSize+4];   /* Store memory size */
    
    Memory_Type = KWP2000_MemoryWrite_AddressTest(memorySize,memoryAddress);
    
    
    //==2014-2-25==B_Passwd逻辑取反，保证标定数据bit为1时，不需要密码，否则客户下载一半再下载的话就该要密码了
    
    if(HLS_B_Passwd == FALSE)//====需要密码
    {
        PasswdStart = asc0_CommunicationBuf.b_receive[3] + headerSize - 6;
        if(KWP2000_CheckPasswordBeforeDownloadOrUpload(&asc0_CommunicationBuf.b_receive[PasswdStart])==FALSE)
        {
            *blockByte++ = KWP2000_NEGATIVERESPONSE;
            *blockByte++ = DOWNLOAD_PASSWORDFAILED_NEGATIVERESONSE; /* Load the address to transmit databyte */
		        bufPos=2;
            return bufPos;        
        }
    }
    
    switch(Memory_Type)
    {
      case KWP2000_MEMTYPE_RAM:
      
         for(i=0;i<memorySize;i++)
         {
             *((UINT8 *)memoryAddress++) = asc0_CommunicationBuf.b_receive[headerSize+5+i]; /* 强制转换为一个指针,start copy data*/
         }
         *blockByte++=KWP2000_WRITEMEMORYBYADDRESS_POSITIVERESPONSE;
	  	   *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+1]; /* Load the address to transmit databyte */
	  	   *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+2]; /* Load the address to transmit databyte */
		     *blockByte =  asc0_CommunicationBuf.b_receive[headerSize+3];
		     bufPos+=4;
		     break;
      case  KWP2000_MEMTYPE_DFLASH:
         /* 对D_FLASH的操作要使用全局地址直接进行，必须把局部地址转化为对应的全局地址 */
         if(memoryAddress >=0x400 && memoryAddress <=0xFFF)
         {
             memoryAddress = memoryAddress | 0x4000;
         }
         else
         {
             memoryAddress = memoryAddress | 0x5000; 
         }
       //  KWP2000_Write_DFlash(&(asc0_CommunicationBuf.b_receive[headerSize+4]),memorySize,memoryAddress);
         
         *blockByte++=KWP2000_WRITEMEMORYBYADDRESS_POSITIVERESPONSE;
	  	   *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+1]; /* Load the address to transmit databyte */
	  	   *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+2]; /* Load the address to transmit databyte */
		     *blockByte =  asc0_CommunicationBuf.b_receive[headerSize+3] ;
		     bufPos+=4;
         break;
      case  KWP2000_MEMTYPE_PFLASH:
         //=========================
         Task_Enable = FALSE;
         
         KWP2000_Write_PFlash(&(asc0_CommunicationBuf.b_receive[headerSize+5]),memorySize,memoryAddress);
         Record_Download_Data_Len+=memorySize;
         DownLoadAddress =  memoryAddress + memorySize;
         //=========================
         *blockByte++= KWP2000_WRITEMEMORYBYADDRESS_POSITIVERESPONSE;
         *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+1]; /* Load the address to transmit databyte */
	  	   *blockByte++= asc0_CommunicationBuf.b_receive[headerSize+2]; /* Load the address to transmit databyte */
		     *blockByte =  asc0_CommunicationBuf.b_receive[headerSize+3] ;
		     bufPos+=4;
         break;
      case  KWP2000_MEMTYPE_UNDEFINED:
         *blockByte++=KWP2000_NEGATIVERESPONSE;
         *blockByte++= KWP2000_WRITEMEMORYBYADDRESS_REQUEST; /* Load the address to transmit databyte */
		     *blockByte = 0x12 ;
		     bufPos=3;
         break;
    }
		
	/* Sets the serviceOK flag */
	  b_ServiceOK=TRUE;	
	  return(bufPos);
    
}
/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP_ReadOneDTC                                  ***
*** Returns  : bufPos                                               ***   
*** Inputs   : dtc, full, errorMemory, numberOfErrors               ***
*** Outputs  : blockBytes                                           ***
*** Calls    : 			                                                ***
*** Action   : Read one DTC from the error memory                   ***
***            with or without Errordata                            ***
*** Modified : 06/03/1998                                           ***
***                                                                 ***
**********************************************************************/
static UINT8 asc0_KWP_ReadOneDTC(UINT8 withData,UINT8 *blockByte)
{
    UINT8 bufPos;
    if(withData)
    {
       *blockByte++ = KWP2000_READSTATUSOFDIAGNOSTICTROUBLECODES_POSITIVERESPONSE;
    }
    bufPos = 1;
    return bufPos;
}
/**********************************************************
** Name    :
** Function:
** Input   :
** Output  :
************************************************************/


UINT8 Get_Number_Of_DTCs()
{
//    UINT8 i;
//    for(i=0;i<60;i++)
//    {
//        if(Group_DTCs[i++] == 0xFFFF)
//        {
//           return i;
//        }
 //   }
    return 60;
}
/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_ReadDiagnosticTroubleCodesByStatus      ***
*** Returns  : bufPos                                               ***
*** Inputs   : kwp2000_Len, kwp2000_Datas,                          ***
*** Outputs  : blockByte, b_ServiceOK                               ***
*** Calls    : asc0_KWP2000_NegativeResponse,                       ***
***            asc0_KWP2000_ReadAllDTCs,                            ***
***            asc0_KWP2000_ReadOneDTC                              ***
*** Action   :                                                      ***
***                                                                 ***
*** Modified : 06/03/1998                                           ***
***                                                                 ***
***********************************************************************/
//extern UINT16 FcmCrk;
//extern UINT16 FcmTa;
//extern UINT16 FcmUb;

UINT8 asc0_KWP2000_ReadDiagnosticTroubleCodesByStatus(UINT8 *blockByte)
{
    UINT8   bufPos=0;
                           

    *blockByte++ = KWP2000_READDIAGNOSTICTROUBLECODESBYSTATUS_POSITIVERESPONSE;/* Load service ID */ 

    *(UINT16 *)blockByte = HLS_FcmCrk;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmLsb;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmLsb2;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmMap;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmPam;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmPgv;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmPot;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmTa;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmTilt;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmTm;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmTps;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmUb;
    blockByte += 2;
    
    *(UINT16 *)blockByte = HLS_FcmAirInj1;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmAirInj2;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmAirInj3;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmAirInj4;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmAps;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmIgn1;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmIgn2;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmIgn3;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmIgn4;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmInj1;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmInj2;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmInj3;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmInj4;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmNtrl;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmOil;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmPump;
    blockByte += 2;
    *(UINT16 *)blockByte = HLS_FcmTps2;
    blockByte += 2;
    
    
    bufPos = 25+34;            
		/* Sets the serviceOK flag */
	  b_ServiceOK=TRUE;
	 
    return(bufPos);
}
/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_ClearDiagnosticInformation              ***
*** Returns  : bufPos                                               ***
*** Inputs   : kwp2000_Len, kwp2000_Datas                           ***
*** Outputs  : blockByte, b_ServiceOK, 						                  ***
*** Calls    : asc0_KWP2000_NegativeResponse                        ***
*** Action   : Request a cleared error memory                       ***
***            or a single erased error in the DFPM                 ***
*** Modified : 23/10/1996                                           ***
***                                                                 ***
**********************************************************************/


UINT8 asc0_KWP2000_ClearDiagnosticInformation(UINT8 *blockByte)
{

    
    UINT16  memoryAddress;
    UINT8   memorySize;
    //UINT8   i;
    UINT8   bufPos=0;
   /* UINT8 *point_address;   */
    memoryAddress = RAM_DTC;/* Load 16 bit address */
    memorySize = DTC_Length;   /* Store memory size */
    
    //=============================2011-6-18  告诉应用软件清除所有故障码
     HLS_B_ClrAll = TRUE;
    
        
    *blockByte++ = KWP2000_CLEARDIAGNOSTICINFORMATION_POSITIVERESPONSE;/* Load service ID */ 
    //for(i=0;i<memorySize;i++)
    //{
        //*((UINT8 *)memoryAddress++) = 0; /* 强制转换为一个指针,start copy data*/
    //}
    *blockByte++=0;
    *blockByte++=0;
    bufPos=3;
		/* Sets the serviceOK flag */
	  b_ServiceOK=TRUE;
	 
   return(bufPos);
    
}

/*******************************************************************************/
/**
* \brief    Calc checksum .
* \author   Engineer
* \param    numberOfBytes
* \return   sum
*/
UINT8 KWP2000_RequestDownload_Request(UINT8 *blockByte)
{
   UINT8 Local_i;
   UINT8 bufPos;
   UINT16 Address_buf;
   
   //=======================用于坏bootloader，擦除9、A两块PFLASH，

   #ifdef Bootloader_V40 
     GoTo_MonitorProgram();
   #endif  
   
   *blockByte++ = KWP2000_REQUESTDOWNLOAD_POSITIVERESPONSE;
   bufPos=1;
   
   return bufPos;
}


/*******************************************************************************
**用于一次性传输一个大的表格
**
********************************************************************************/
void  KWP2000_Transmit_Table(void)
{
    UINT16 Table_Len ;
    UINT16 memoryAddress;
    UINT8 i;
    UINT16 j;
    UINT8 temp;
    UINT8 *blockByte;
    UINT8 temp_sum;
    
    memoryAddress = (((UINT16)asc0_CommunicationBuf.b_receive[headerSize+1]<<8)|(asc0_CommunicationBuf.b_receive[headerSize+2]));/* Load 16 bit address */
    Table_Len =(((UINT16)asc0_CommunicationBuf.b_receive[headerSize+3]<<8)|(asc0_CommunicationBuf.b_receive[headerSize+4])) ;  /* Store memory size */
    
    blockByte = (UINT16 *)memoryAddress;//获取数组首地址

    //SCICR2_TCIE = 0;//关闭发送完成中断
    SCI_TC_INTERRUPT(DISABLED);
    temp_sum = 0;
    
    SCI_WriteTx(128);//传输头
    temp_sum += 128;
    SCI_WriteTx(143);//传输头
    temp_sum += 143;
    SCI_WriteTx(234);//传输头
    temp_sum += 234;
    SCI_WriteTx(193);//数据长度
    temp_sum += 193;
    SCI_WriteTx(Transmit_Table_PositiveResponse);//正响应ID
    temp_sum += Transmit_Table_PositiveResponse;
    for(j=0;j<Table_Len;j++)
    {
         temp = *blockByte++;
         SCI_WriteTx(temp);//传送数据
         temp_sum += temp;
    } 
    SCI_WriteTx(temp_sum);
     
}

/*******************************************************************************
**用于传输ECU的版本号
**
********************************************************************************/
UINT8 GetECUVersion_Request(UINT8 *blockByte)
{
    UINT8 bufPos =0;
    UINT8 i,j;
    UINT16 memoryAddress1;
    UINT16 memoryAddress2;
    
    memoryAddress1 = ROM_SERIAL_NUMBER;
    memoryAddress2 = ROM_BOOT_VERSION_ADDRESS;
    
    *blockByte++ = GET_ECU_VERSION_POSITIVERESPONSE;/* Load service ID */ 
    bufPos++ ;

    for(i=0;i<6;i++)
    {
        for(j=0;j<16;j++)
        {
          switch(i)
          {
          case 0:
              *blockByte++ = Hardware_Version[j];
              bufPos++ ;
          break;
          case 1:
              *blockByte++ = Software_LLD_Version[j];
              bufPos++ ;
          break;
          case 2:
              *blockByte++ = Software_HLD_Version[j];
              bufPos++ ;
          break;
          case 3:
              *blockByte++ = Software_CLD_Version[j];
              bufPos++ ;
          break;
          case 4:
              *blockByte++ = *(UINT8 *)memoryAddress1++;
              bufPos++ ;
          break;
          
          case 5:
              *blockByte++ = *(UINT8 *)memoryAddress2++;
              bufPos++ ;
          break ;
 
          }
        }
    } 
    for(i=0;i<18;i++)
    {
        *blockByte++ = HLS_CUR_Customer_Inf[i];
        bufPos++ ;
    }
    *blockByte++ = (UINT8)(HLS_VAL_Customer_Counter>>8);
    *blockByte++ = (UINT8)HLS_VAL_Customer_Counter;
    bufPos+=2;
    
    /*if(N==0) //=====否则会造成熄火
    {
        Read_CopyRight(7,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(6,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(5,blockByte);
        bufPos+=8;  
        *blockByte +=8;
        Read_CopyRight(4,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(3,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(2,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(1,blockByte);
        bufPos+=8;
        *blockByte +=8;
        Read_CopyRight(0,blockByte);
        bufPos+=8;
        *blockByte +=8;    
    }*/
    
    
    return bufPos;
}

/*******************************************************************************
**用于禁止ECU的运行
**
********************************************************************************/
UINT8 DisableECU_Run_Request(UINT8 *blockByte)
{}

/*******************************************************************************
**用于使能ECU的运行
**
********************************************************************************/
UINT8 EnableECU_Run_Request(UINT8 *blockByte)
{}

/*******************************************************************************/
/**
* \brief    Calc checksum .
* \author   Engineer
* \param    numberOfBytes
* \return   sum
*/
UINT8 kwp2000_Checksum_Calc(UINT8 *dataBuffer,UINT16 numberOfBytes)
{
 
	UINT8 sum;
	UINT16 i;

	/* Resets the sum */
	sum=0;
	/* for each byte */
	for (i=0;i<numberOfBytes;i++)
	{
	  	 /* add the value to the sum */
	  	 sum+=dataBuffer[i];
	}
	return (sum);
}	
    

 /*******************************************************************************/
/**
* \brief    比较接收到校验和与程序中计算出的校验和是否相等。
* \author   Engineer
* \param    void
* \return   answer
*/
UINT8 kwp2000_Checksum_Test(void)
{
  UINT8 answer;
	UINT8 CS;

	/* Calculates the message Checksum */
	CS=kwp2000_Checksum_Calc(&(asc0_CommunicationBuf.b_receive[0]),(UINT16)headerSize+kwp2000_Len);
	/* Verifies it with the one that was in the message */
	if (CS==kwp2000_Checksum)
	{
		/* it is ok */
		answer=TRUE;
	}
	else
	{
		/* it is not the same */
		answer=FALSE;
	}

	return (answer);
}

/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_BuildResponse_Flash                     ***
*** Returns  : -                                                    ***
*** Inputs   : kwp2000_Datas, kwp2000_Services_Mask,                ***
***            kwp2000_Services, asc0_CommunicationBuf              ***
*** Outputs  : kwp2000_ServiceId, kwp2000_MessageSize_Flash,        ***
***            kwp2000_MessageAddress                               ***
*** Calls    : kwp2000_Services[..], asc0_KWP2000_PrepareHeader_F..,***
***            asc0_KWP2000_ChecksumCalculate_Flash_Ptr             ***
*** Action   : Builds the response message to the service asked.    ***
***            If the message size is 0 do nothing.                 ***
*** Modified : 04/08/1997                                           ***
**********************************************************************/
void asc0_KWP2000_BuildResponse_Flash(void)
{
//	UINT8 shortServiceId;
	UINT8 headersize;
	UINT8 datasize;

	
  /* FLASH initial */	
 // kwp2000_Services=&kwp2000_Services_Flash;
 // kwp2000_PhysicalAddress=KWP2000_PHYSICALADDRESS;
//	kwp2000_FunctionalAddress=KWP2000_FUNCTIONALADDRESS;
//	kwp2000_Keybyte1=KWP2000_KEYBYTE1;
//	kwp2000_Keybyte2=KWP2000_KEYBYTE2;

		  kwp2000_ServiceId=*kwp2000_Datas;
     // KWP2000_PeriodicTaskTransmit_Disable();
	    switch(kwp2000_ServiceId)                          
	    {
	      /*  */
	      case KWP2000_STARTCOMMUNICATION_REQUEST:  
	           datasize=KWP2000_StartCommunication_Flash(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_READMEMORYBYADDRESS_REQUEST:
	           datasize=KWP2000_ReadMemoryByAddress(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_WRITEMEMORYBYADDRESS_REQUEST:
	           //======如果电池电压低于11V禁止写FLASH
	           //if(CompareUbAdcWith11V() == TRUE)
	           datasize=KWP2000_WriteMemoryByAddress(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	           //else datasize = 0;
	      break;
	      case KWP2000_READDIAGNOSTICTROUBLECODESBYSTATUS_REQUEST:
	           datasize=asc0_KWP2000_ReadDiagnosticTroubleCodesByStatus(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;     
	      case KWP2000_READDATABYLOCALIDENTIFIER_REQUEST:
	           datasize = asc0_KWP2000_ReadDataByLocalIdentifier(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_STARTDIAGNOSTICSESSION_REQUEST:
	           datasize = asc0_KWP2000_StartDiagnosticSession(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_STOPDIAGNOSTICSESSION_REQUEST:
	           datasize = asc0_KWP2000_StopDiagnosticSession(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_STARTPERIODICTRANSMIT_REQUEST:
	           datasize = asc0_KWP2000_StartPeriodicTransmit(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_TRANSMITCALIBRATIONDATA_REQUEST:
	           datasize = asc0_KWP2000_TransmitCalibrationData(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_WRITEDATABYLOCALIDENTIFIER_REQUEST:
	           datasize = asc0_KWP2000_WriteDataByLocalIdentifier(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break; 
	      case KWP2000_CHECKCALIBRATIONDATA_REQUEST:
	           datasize = asc0_KWP2000_CheckCalibrationData(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case KWP2000_CLEARDIAGNOSTICINFORMATION_REQUEST:
	           datasize = asc0_KWP2000_ClearDiagnosticInformation(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      case TRANSMIT_CODE:
	           //Erase_CodeWriteSuccessfulFlg();
	           datasize=0;
	      break;
	      case KWP2000_REQUESTDOWNLOAD_REQUEST:
	          datasize = KWP2000_RequestDownload_Request(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      
	      case Transmit_Table_Request:
	           KWP2000_Transmit_Table();
	           datasize=0;
	      break;
	      
	      case GET_ECU_VERSION_REQUEST:
	           datasize = GetECUVersion_Request(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      
	      case DISABLE_ECU_RUN_REQUEST:  
	           datasize = DisableECU_Run_Request(&(asc0_CommunicationBuf.b_transmit[headerSize]));     
	      break;
	      
	      case ENABLE_ECU_RUN_REQUEST:
	           datasize = EnableECU_Run_Request(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      
	      case DOWNLOAD_NEED_PASSWORD_REQUEST:
	           datasize = Send_NeedPassword_PositiveResponse(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      
	      case DOWNLOAD_CHECK_PASSWORD_REQUEST:
	           datasize = Send_CheckPassword_PositiveResponse(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      
	      case RESET_SELFLEARNTABLE_REQUEST:
	           datasize = Reset_SelfLearnTab_PositiveResponse(&(asc0_CommunicationBuf.b_transmit[headerSize]));
	      break;
	      	      
	      default:datasize=0;
	              asc0_KWP2000_ServiceNegativeResponse(4);//(asc0_CommunicationBuf.b_receive[headerSize]); /* 发送负响应 */ 
	      break;
	       	       
	    }
	    
	/* Tests the returned message size */
	if (datasize!=0)                                                                    
	{
		/* Message size is not 0 */
		/* defines the header of the message */
  	//	headersize=asc0_KWP2000_PrepareHeader_Function(dataSize);
	   if(kwp2000_ServiceId ==  KWP2000_STARTCOMMUNICATION_REQUEST)
	   {
	       headersize = 4; 
	       asc0_KWP2000_PrepareHeader_StatCom();
	   }
	   else
	   {
	      
	       headersize=asc0_KWP2000_PrepareHeader_CARB(datasize);
	   }
	  	/* Calculate the size of the message (without CS) */
	  	kwp2000_MessageSize_Flash=(UINT16)headersize+datasize;
	  	/* Defines the beginning address of the message */
	  	kwp2000_MessageAddress=&(asc0_CommunicationBuf.b_transmit[0]);
		  /* Calculates the checksum and write it in the buffer and increments the message size */
	  	asc0_CommunicationBuf.b_transmit[headersize+datasize]=kwp2000_Checksum_Calc(kwp2000_MessageAddress,kwp2000_MessageSize_Flash++);
	}
	else
	{
		/* Message size is 0 */
		kwp2000_MessageSize_Flash=0;
	}
	
}

/**********************************************************************
**
**
***********************************************************************/
void  KWP2000_PeriodicTaskTransmit_Disable(void)
{
        KWP2000_Flg.Periodic_Transmission_syn = FALSE;/* 定时发送标志清零，将停止定时发送任务 */
        KWP2000_Flg.Periodic_Package_syn = FALSE;     /* 定时打包标志清零，将停止定时打包任务 */
        PeriodicTasksyn_Package_Complete = FALSE;

        KWP2000_Flg.Periodic_Transmission_10ms = FALSE;/* 定时发送标志清零，将停止定时发送任务 */
        KWP2000_Flg.Periodic_Package_10ms = FALSE;     /* 定时打包标志清零，将停止定时打包任务 */
        PeriodicTask10ms_reserved1_Package_Complete = FALSE;

        KWP2000_Flg.Periodic_Transmission_100ms = FALSE; /* 定时发送标志清零，将停止定时发送任务 */
        KWP2000_Flg.Periodic_Package_100ms = FALSE;      /* 定时打包标志清零，将停止定时打包任务 */
        PeriodicTask100ms_Package_Complete =FALSE;
        
        Start_Syn_Counter=0;//停止时间计数

       // SCICR2_TCIE = 0;/* 关闭发送完成中断 */
        SCI_TC_INTERRUPT(DISABLED);
       PeriodicTask_Transmit_Complete=TRUE;/* 发包完成标志置1，表示可以发送新的数据包了 */
       *Package_Complete_Ptr = FALSE; /* 打包完成标志复位，表示可以进行新数据的打包了 */
}









/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_SendResponse                            ***
*** Returns  : -                                                    ***
*** Inputs   : kwp2000_MessageAddress, kwp2000_MessageSize_Flash    ***
*** Outputs  : kwp2000_Message                                      ***
*** Calls    : asc0_KWP2000_DataTransmission_Flash, 			        	***
***			   asc0_KWP2000_NextState							                    	***
*** Action   : Defines the beginning of the message, begins the     ***
***            transmission and prepares the next state             ***
*** Modified : 04/08/1997                                           ***
**********************************************************************/
void asc0_KWP2000_SendResponse_Flash(void)
{
	/* Defines the message beginning */
//	kwp2000_Message=kwp2000_MessageAddress;
	/* Initiates the communication */
  	UINT8 i;
  	i= asc0_KWP2000_DataTransmission_Flash(kwp2000_MessageSize_Flash);
    asc0_KWP2000_NextState();
    //如果下载数据完成，复位ECU
    if(Record_Download_Data_Len==Calibration_Data_Length || DownLoadAddress==RAM_CALC_Data+Calibration_Data_Length)
    {
         Record_Download_Data_Len=0;
         AfterRun_Flg = DISABLED;
         Powerdown_Interface();
         Disable_All_Interrupts();
         __asm   //使用这种方法的话下电计时的时间参数无法传递给应用程序
        {
           JMP $C000;//程序计数器PC跳转到程序复位后的地址处
        }
    }

}
/*************************************************************************
**清空缓冲区
**
**************************************************************************/
void Clear_Buffer()
{
    UINT16 i;
     for(i=0;i<256;i++)
    {
       asc0_CommunicationBuf.b_receive[i] = 0;
    }
    
   /* for(i=0;i<256;i++)
    {
       asc0_CommunicationBuf.b_receive[i] = 0;
       asc0_CommunicationBuf.b_transmit[i] = 0;
       asc0_CommunicationBuf.b_receive_100ms[i]=0;
       asc0_CommunicationBuf.b_receive_syn[i]=0;
    }
    for(i=0;i<128;i++)
    {
       asc0_CommunicationBuf.b_receive_10ms[i]=0;
       asc0_CommunicationBuf.b_transmit_syn[i]=0; 
       asc0_CommunicationBuf.b_transmit_100ms[i]=0;
    }
    for(i=0;i<48;i++)
    {
       asc0_CommunicationBuf.b_transmit_10ms[i]=0;  
    }  */
}
/****************************************************************************
**
**
*****************************************************************************/
void asc0_KWP2000_NextState()
{
   // while(KWP2000_Flg.Transmit_Calibration_Data_Complete ==FALSE) /* 只要标定数据没发完就一直打包然后发送 */
   // {
   //     asc0_KWP2000_BuildResponse_Flash();/* 打包 */
   //     asc0_KWP2000_DataTransmission_Flash(kwp2000_MessageSize_Flash);/* 发送 */
   // }
    /* 当发送完成后复位 */
    asc0_ComMode=KWP2000_WAITRECEPTION;
    Rx_Length = 0; 
	  pu8SCI_Receive_Data_ptr=(&(asc0_CommunicationBuf.b_receive[0]));
	  kwp2000_ServiceId=0;
	  headerSize=0;
	  b_Transmitted =0;
	 // Clear_Buffer();
}
/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_PrepareHeader_CARB                      ***
*** Returns  : headerSize                                           ***
*** Inputs   : dataSize, kwp2000_Format, kwp2000_Src                ***
*** Outputs  : asc0_CommunicationBuf                                ***
*** Calls    : -                                                    ***
*** Action   : Constructs the message header                        ***
***            (adapted for ISO 14230-4)  可能是对发送的信息进行包装***
*** Modified : 19/11/1997                                           ***
**********************************************************************/
 UINT8 asc0_KWP2000_PrepareHeader_CARB(UINT8 datasize)
{
//	UINT8 headersize;
//	UINT8 fmt;

	/* Resets the header size */
	//headersize=1;

	/* Tests the data size */
//	if (datasize>63)
//	{
		/* Too big to be written in the format byte, needs additional length byte */
	//	headersize = 2;
	//	fmt=kwp2000_Format<<6;
	//	asc0_CommunicationBuf.b_transmit[headerSize - 1]=datasize;
	//  asc0_CommunicationBuf.b_transmit[headerSize - 2]=0;
//	}
//	else
//	{
		/* Format and size in the same byte */
//		fmt=(kwp2000_Format<<6)|datasize;
//		headersize = 3;
//	}
	/* Test the format used */
	switch (kwp2000_Format)
	{
		case KWP2000_FORMAT_NOADDRESS :
			/* if no address then nothing to add at header */
			break;
		case KWP2000_FORMAT_CARB : /* Not used */
			/* CARB mode */
		
			break;
		case KWP2000_FORMAT_FUNCTIONALADDRESSING :
		case KWP2000_FORMAT_PHYSICALADDRESSING :
			/* Physical addressing */
			asc0_CommunicationBuf.b_transmit[1]=kwp2000_Tgt;
			asc0_CommunicationBuf.b_transmit[2]=kwp2000_Src;
			break;
	}
//	asc0_CommunicationBuf.b[4-headersize]=fmt;
//  	asc0_CommunicationBuf.b[0]=fmt;
		asc0_CommunicationBuf.b_transmit[headerSize - 1]=datasize;
	  asc0_CommunicationBuf.b_transmit[0]=0x80;

	return(headerSize);
}	 

/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_FormatAnalyse_FLASH                     ***
*** Returns  : headerSize                                           ***
*** Inputs   : asc0_CommunicationBuf                                ***
*** Outputs  : kwp2000_Format,kwp2000_Len,kwp2000_Datas             ***
*** Calls    : -                                                    ***
*** Action   : Analyses the format byte and returns the different   ***
***            informations                                         ***
*** Modified : 18/11/96                                             ***
**********************************************************************/
 UINT8 asc0_KWP2000_FormatAnalyse_FLASH(void)
{
	UINT8 headersize;
  //kwp2000_Format= asc0_CommunicationBuf.b_receive[0];
 
    	/* Extracts the format information */
    	kwp2000_Format=(asc0_CommunicationBuf.b_receive[0]&0xC0)>>6;
    	//kwp2000_Format=0x80;
    	/* Extracts the message length */
    	kwp2000_Len=asc0_CommunicationBuf.b_receive[0]&0x3F;
    	//kwp2000_Len = kwp2000_Format &0x3F;   
    	/* Resets the headerSize */
    	headersize=1;
    	/* Tests the format */
	    switch (kwp2000_Format)
    	{
    		case KWP2000_FORMAT_NOADDRESS :
 		  	/* There's no address */
	   		break;
	    	case KWP2000_FORMAT_CARB : /* Not used*/
			/* There are source and target addresses */
			//kwp2000_Len=0;
	   		break;
    		case KWP2000_FORMAT_PHYSICALADDRESSING :
	    	case KWP2000_FORMAT_FUNCTIONALADDRESSING :
		  	/* There are source and target addresses */
		  	headersize+=2;
		  	break;
		  	default: break;
    	}
	   /* Tests the message length */
   	if(kwp2000_Len==0)
   	{
		/* it was 0 so there's an additional length byte */
	    	headersize++;
  	}

	 /* Sets the pointer at the beginning of the datas */
  	kwp2000_Datas=&(asc0_CommunicationBuf.b_receive[headersize]);
    
	return (headersize);
}	

/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_HeaderAnalyse_StartCom                  ***
*** Returns  : -                                                    ***
*** Inputs   : HeaderSize, asc0_CommunicationBuf                    ***
*** Outputs  : Kwp2000_Len, Kwp2000_Tgt, Kwp2000_Src, Kwp2000_Len   ***
*** Calls    : -                                                    ***
*** Action   : Copies the datas from the buffer to the variables    ***
***            in respect of the header description                 ***
*** Modified : 05/08/98                                             ***
**********************************************************************/
 void asc0_KWP2000_HeaderAnalyse_StartCom(void)
{
    	/* Tests the header size */
	switch (headerSize)
	{
		case 1 :
			/* 1 byte  -> FMT */
			break;
		case 2 :
			/* 2 bytes -> FMT LEN */
		
			break;
		case 4 :
			/* 4 bytes -> FMT TGT SRC LEN */
			kwp2000_Len=asc0_CommunicationBuf.b_receive[3];
		case 3 :
			/* 3 bytes -> FMT TGT SRC */
	//		kwp2000_Tgt=asc0_CommunicationBuf.b_receive[1];
	//		kwp2000_Src=asc0_CommunicationBuf.b_receive[2];
			if(kwp2000_Format==KWP2000_FORMAT_FUNCTIONALADDRESSING)
			{

			}
			else
			{
				/* physical address => do nothing */
			}
			break;
	}
}
/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_HeaderAnalyse_FLASH                     ***
*** Returns  : -                                                    ***
*** Inputs   : HeaderSize, asc0_CommunicationBuf                    ***
*** Outputs  : Kwp2000_Len, Kwp2000_Tgt, Kwp2000_Src, Kwp2000_Len   ***
*** Calls    : -                                                    ***
*** Action   : Copies the datas from the buffer to the variables    ***
***            in respect of the header description                 ***
*** Modified : 04/09/97                                             ***
**********************************************************************/

void asc0_KWP2000_HeaderAnalyse_FLASH(void)
{
	/* Tests the header size */
	switch (headerSize)
	{
		case 1 :
			/* 1 byte  -> FMT */
			break;
		case 2 :
			/* 2 bytes -> FMT LEN */
			kwp2000_Len=asc0_CommunicationBuf.b_receive[1];
			break;
		case 3 :
			/* 3 bytes -> FMT TGT SRC */
			kwp2000_Tgt=asc0_CommunicationBuf.b_receive[1];
			kwp2000_Src=asc0_CommunicationBuf.b_receive[2];
			break;
		case 4 :
			/* 4 bytes -> FMT TGT SRC LEN */
			kwp2000_Tgt=asc0_CommunicationBuf.b_receive[1];
			kwp2000_Src=asc0_CommunicationBuf.b_receive[2];
			/* Normal protocol -> extract the length */
			kwp2000_Len=asc0_CommunicationBuf.b_receive[3];
		 // kwp2000_Datas=&(asc0_CommunicationBuf.b_receive[headerSize]);
		  
			break;
	}
}	

/**********************************************************************
*** Task     : -                                                    ***
*** Name     : KWP2000_StartCommunication_Flash                     ***
*** Returns  : bufPos                                               ***
*** Inputs   : kwp2000_Predefined_Services_Mask, blockByte,         ***
***            kwp2000_Keybyte1, kwp2000_Keybyte2                   ***
*** Outputs  : b_ServiceOK, b_CanStop, b_CanStopDiag, b_Unlocked,   ***
***            kwp2000_DiagMode, kwp2000_Modif, kwp2000_Format      ***
*** Calls    : -                                                    ***
*** Action   : Prepares the answer for the service                  ***
***            startCommunication                                   ***
*** Modified : 05/08/1998                                           ***
**********************************************************************/
UINT8 KWP2000_StartCommunication_Flash(Byte *blockByte)
{
	UINT8 bufPos;


	/* Resets the flag bits */
	b_ServiceOK = TRUE;
   asc0_KWP2000_HeaderAnalyse_Function=&asc0_KWP2000_HeaderAnalyse_FLASH;

	bufPos=3;
	/* Puts the positive response message in the buffer */
	*(blockByte++)=KWP2000_STARTCOMMUNICATION_POSITIVERESPONSE;
	*(blockByte++)=KWP2000_KEYBYTE1;
	*blockByte=KWP2000_KEYBYTE2;
 	return (bufPos);
}

/**********************************************************************
*** Task     : -                                                    ***
*** Name     : KWP2000_StartCommunication_Flash                     ***
*** Returns  : bufPos                                               ***
*** Inputs   : kwp2000_Predefined_Services_Mask, blockByte,         ***
***            kwp2000_Keybyte1, kwp2000_Keybyte2                   ***
*** Outputs  : b_ServiceOK, b_CanStop, b_CanStopDiag, b_Unlocked,   ***
***            kwp2000_DiagMode, kwp2000_Modif, kwp2000_Format      ***
*** Calls    : -                                                    ***
*** Action   : Prepares the answer for the service                  ***
***            startCommunication                                   ***
*** Modified : 05/08/1998                                           ***
**********************************************************************/
UINT8 KWP2000_StopCommunication_Flash(Byte *blockByte)
{
	/* Resets the flag bits */
	b_ServiceOK=TRUE;

 	return (0);
}
void asc0_KWP2000_PrepareHeader_StatCom(void)
{
  	asc0_CommunicationBuf.b_transmit[0] = RESPONSE_FUNCTIONALADDRESS | 0x03;
    asc0_CommunicationBuf.b_transmit[1] = kwp2000_Tgt;
		asc0_CommunicationBuf.b_transmit[2] = kwp2000_Src;   
}

UINT8 asc0_KWP2000_AddressTest()
{
   return TRUE;
    
}

/**********************************************************************
*** Task     : 10ms                                                 ***
*** Name     : asc0_KWP2000_FLASH_10ms                              ***
*** Returns  : -                                                    ***
*** Inputs   : asc0_ComMode...                                      ***
*** Outputs  : ...                                                  ***
*** Calls    : ...                                                  ***
*** Action   : KWP2000 communication mode and end of initialisation ***
*** Modified : 18/11/1996                                           ***
**********************************************************************/
void asc0_KWP2000_FLASH_10ms(void)
{
	UINT16 temp;
  static UINT8 Kwp2000_TimeOut=0;
	/* Tests the ComMode */
	switch (asc0_ComMode)
	{
		/* Wait reception mode */
		case KWP2000_WAITRECEPTION :
			/* Is the last transmission ended */
			if (b_Transmitted==0)
			{
				/* Yes */
				/* Calculates the new write position */
			//	asc0_CommunicationBuf.b[0]= 0x80;
			//	pu8SCI_Receive_Data_ptr++;
			//	b_Transmitted = 1;
				asc0_CommunicationBufWritePos=pu8SCI_Receive_Data_ptr-&(asc0_CommunicationBuf.b_receive[0]);
			
				/* Tests the position */
				if (asc0_CommunicationBufWritePos>2)
				{
				   if(asc0_CommunicationBuf.b_receive[2]==0xAA)
				   {
				       Return_Answer(0xAA);
				       asc0_KWP2000_ProtocolInit_FLASH();
				       return;
				   }
				
					/* The Fmt byte has arrived */
					headerSize=asc0_KWP2000_FormatAnalyse_FLASH();
				
					/* Goes in the wait header mode (no wait) */
					asc0_ComMode=KWP2000_WAITHEADER;
					Kwp2000_TimeOut=0;
				}
				else
				{
					/* The Fmt byte has not arrived */
					break;
				}
			}
			else
			{
				/* No */
				break;
			}
		/* Wait header mode */
		case KWP2000_WAITHEADER :
			/* Calculates the new write position */
       
			asc0_CommunicationBufWritePos=pu8SCI_Receive_Data_ptr-&(asc0_CommunicationBuf.b_receive[0]);
			/* Tests if the datas already received are greater than the header */
			if (asc0_CommunicationBufWritePos>=headerSize)
			{

				/* Analyse the header */
		
			     // asc0_KWP2000_HeaderAnalyse_Function();
			      asc0_KWP2000_HeaderAnalyse_FLASH();
	
			    	/* Calculates the complete size of the message incl. checksum */
				    SizeToReceive=headerSize+kwp2000_Len+1;
			    	/* Goes in the wait datas mode (no wait) */
			    	asc0_ComMode=KWP2000_WAITDATAS;
			                                                                                                 
			}
			else
			{
				/* The header is not complete */
				break;
			}
		/* Wait datas mode */
		case KWP2000_WAITDATAS :
          Kwp2000_TimeOut++;  //溢出参数
       if(Kwp2000_TimeOut>=20) //如果数据 传输时有丢失，则temp始终大于0，所以asc0_ComMode就会一直在这个case
                                     //中循环，这个case每20ms进一次，当连续10次进入这个case时，说明数据有丢失
       {
            Kwp2000_TimeOut=0;
            asc0_KWP2000_ServiceNegativeResponse(asc0_CommunicationBuf.b_receive[headerSize]); /* 发送负响应 */				
           
            
					  pu8SCI_Receive_Data_ptr=(&(asc0_CommunicationBuf.b_receive[0]));
				    Rx_Length = 0;
					 /* Goes in the wait reception mode (with wait) */
						asc0_ComMode=KWP2000_WAITRECEPTION;  
       }
      
                  
			asc0_CommunicationBufWritePos=pu8SCI_Receive_Data_ptr-&(asc0_CommunicationBuf.b_receive[0]);
			/* Calculate the difference between the size to receive and the datas already received */
			temp=SizeToReceive-asc0_CommunicationBufWritePos;
			/* Are they more to receive */
			if (temp<=0)
			{
			  	/* The good number of bytes received or more */
					/* Goes in the communication mode */
					asc0_ComMode=KWP2000_COMMUNICATION;
					/* all the datas arrived before the test */
		      Kwp2000_TimeOut=0 ;
					b_Received=1;
					/* switch to the maximal baudrate because of collision avoidance */
			}
			else
			{
				/* Yes -> wait */
				break;
			}
		/* Communication mode */
		case KWP2000_COMMUNICATION :
			/* Has all the datas been received */
			if (b_Received==1)
			{
				   /* Yes */
		
			    	b_Received=0;
	
					  /* Extracts the checksum */
					  kwp2000_Checksum=asc0_CommunicationBuf.b_receive[SizeToReceive-1];
				  	/* Verifies the checksum */
					  if (kwp2000_Checksum_Test()==TRUE)
				  	{
					  	/* Checksum OK */
					  	/* Goes in the build response mode (no wait) */
				  		asc0_ComMode=KWP2000_BUILDRESPONSE;
						
				  	}
				  	else
				  	{
					  	/* Checksum is not correct */
					    asc0_KWP2000_ServiceNegativeResponse(2);//(asc0_CommunicationBuf.b_receive[headerSize]); /* 发送负响应 */				
					  	pu8SCI_Receive_Data_ptr=(&(asc0_CommunicationBuf.b_receive[0]));
				      Rx_Length = 0;
						  /* Goes in the wait reception mode (with wait) */
					  	asc0_ComMode=KWP2000_WAITRECEPTION;
						  break;
					  }
	  	}
			else
			{
				/* All the datas have not been received -> wait */
				break;
			}
		/* Build response mode */
		case KWP2000_BUILDRESPONSE :
			/* Build the response to the service requested */
         asc0_KWP2000_BuildResponse_Flash();

			/* Is there a message to send */
			if (kwp2000_MessageSize_Flash==0)
			{
				/* No, wait and rebuild the response */
				  pu8SCI_Receive_Data_ptr=(&(asc0_CommunicationBuf.b_receive[0]));
		      Rx_Length = 0;
					asc0_ComMode=KWP2000_WAITRECEPTION;
					asc0_KWP2000_ServiceNegativeResponse(kwp2000_ServiceId);
				break;
			}
			else
			{
				/* There's a message to send */
				/* Goes in the send response mode (no wait) */
				asc0_ComMode=KWP2000_SENDRESPONSE;
			}
		/* Send response mode */
		case KWP2000_SENDRESPONSE :

				asc0_KWP2000_SendResponse_Flash();

			break;
		/* Modify configuration mode */
		case KWP2000_MODIFYCONFIG :
			/* waits until the configuration is modified */
			break;
		/* End mode */
		case KWP2000_END :
			/* Finishs the communication */
		//	asc0_KWP2000_End();
			break;
		default:
			break;
	}

}	


/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_DataTransmission_Flash                  ***
*** Returns  : -                                                    ***
*** Inputs   : messageSize                                          ***
*** Outputs  : b_Transmitted, asc0_CommunicationBufWritePos,        ***
***            asc0_CommunicationBufReadPos                         ***
*** Calls    : -                                                    ***
*** Action   : Configures the pointers for a transmission of        ***
***            messageSize Bytes and initiates the communication    ***
*** Modified : 04/08/1997                                           ***
**********************************************************************/

 	
 	
UINT8 asc0_KWP2000_DataTransmission_Flash(UINT16 messageSize)
{
  UINT16 Tx_Size;
	/* in transmission mode */
   
    kwp2000_Message = &(asc0_CommunicationBuf.b_transmit[0]);
   #ifndef Full_Duplex
   SCICR2_RE = 0;
   #endif

   if(messageSize>=(headerSize+1))
   {
       
       //if(PeriodicTask_Transmit_Complete == TRUE)
       //{
            PositiveResponse_Package_Complete=FALSE;//复位正响应打包完成标志
       //     PeriodicTask_Transmit_Complete = FALSE;//避免定时数据包打断正响应的发送
            for(Tx_Size=0;Tx_Size<messageSize;Tx_Size++)
	          {
	              if(SCISR1_TDRE == 1)  //发送数据寄存器空标志
	              {
			             SCIDRL=*kwp2000_Message++;
		               while(SCISR1_TC ==0);
                }
	          }
	      //    PeriodicTask_Transmit_Complete = TRUE;
       //} 
       //else 
       //{
       //     Positive_Response_Interrupt_Transmit();
       //}
   }
   else
   {
       asc0_KWP2000_ServiceNegativeResponse(3);//(asc0_CommunicationBuf.b_receive[headerSize]);
   }
   
   
   #ifndef Full_Duplex
   SCICR2_RE = 1;
   #endif
   
  if(kwp2000_ServiceId == KWP2000_REQUESTDOWNLOAD_REQUEST)
  {    /* 如果是刷写ECU请求，那么发送完正响应后要跳转到监控程序的入口 */
      return(FALSE);
      
  }
  else
  {
      
      return(TRUE);	
  }
		     
//	b_Transmitted=1;   
}
/**********************************************************************************************
**
**
***********************************************************************************************/
void Positive_Response_Interrupt_Transmit(void)
{
     // if((*Transmit_Complete_Ptr == TRUE)&&(asc0_CommunicationBuf.b_transmit[2]!=KWP2000_STARTPERIODICTRANSMIT_POSITIVERESPONSE))
     //  while(*Transmit_Complete_Ptr == TRUE)
     while(PeriodicTask_Transmit_Complete == FALSE);
     {
     }
            /* 传送完成标志置0，表示必须等这个数据包发送完成方可发送其他定时数据包，它置1操作发生在SCI发送中断 */
            PeriodicTask_Transmit_Complete=FALSE;
            //Transmit_Complete_Ptr = &PeriodicTask_Transmit_Complete;
            Package_Complete_Ptr=&PositiveResponse_Package_Complete; 
            pu8SCI_Transmit_Data_ptr = &asc0_CommunicationBuf.b_transmit[0];
            /* Tx_Length = 数据字节长度 + 头字节长度 + 校验字节 */
            Tx_Length = asc0_CommunicationBuf.b_transmit[3]+5;
           // SCICR2_TCIE = 1;/* 打开发送中断后会立即进入中断函数 */
           SCI_TC_INTERRUPT(ENABLED);
}
/**********************************************************************************************
**
**
***********************************************************************************************/
void Positive_Response_Normal_Transmit(void)
{
       UINT16 Tx_Size,Tx_Len;
       
       Tx_Len = asc0_CommunicationBuf.b_transmit[1]+3;
       kwp2000_Message = &(asc0_CommunicationBuf.b_transmit[0]);
       if(PeriodicTask_Transmit_Complete== TRUE)
       {
            //SCICR2_TCIE = 0;/* 关闭发送中断 */
            SCI_TC_INTERRUPT(DISABLED);
          	//for(Tx_Size =messageSize;Tx_Size>0;Tx_Size--)
            for(Tx_Size=0;Tx_Size<Tx_Len;Tx_Size++)
	          {
	              if(SCISR1_TDRE == 1)  //发送数据寄存器空标志
	              {
			             SCIDRL=*kwp2000_Message++;
		               while(SCISR1_TC ==0);
                }
	          }
   
       } 

}
/**********************************************************************
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_ProtocolInit_FLASH                      ***
*** Returns  : -                                                    ***
*** Inputs   : ...                                                  ***
*** Outputs  : ...                                                  ***
*** Calls    : -                                                    ***
*** Action   : Initialises the different local variables.           ***
*** Modified : 05.08.98                                             ***
**********************************************************************/
void asc0_KWP2000_ProtocolInit_FLASH(void)
{
	/* initialization of the functional keyword2000 address */

    asc0_KWP2000_HeaderAnalyse_Function=&asc0_KWP2000_HeaderAnalyse_StartCom;
	/* Initialisation of the keybytes */
	b_ServiceOK = TRUE;
  KWP2000_Flg.Transmit_Calibration_Data_Complete=TRUE;/* 如果为FALSE就会进入传送标定数据模式 */
  KWP2000_Flg.Periodic_Package_100ms = FALSE;
  KWP2000_Flg.Periodic_Package_syn = FALSE;
  KWP2000_Flg.Periodic_Package_10ms = FALSE;
  KWP2000_Flg.Periodic_Transmission_10ms = FALSE;
  KWP2000_Flg.Periodic_Transmission_100ms = FALSE;
  KWP2000_Flg.Periodic_Transmission_syn = FALSE;
  KWP2000_Flg.Periodic_Transmission_Error = FALSE;
	//b_ResponsePending=0;
	Packet=0;/* 数据包ID清零，当传送标定数据时保证先打第一个包 */
	PeriodicTask_Transmit_Complete = TRUE;
  Package_Complete_Ptr = &PeriodicTask10ms_reserved1_Package_Complete;
  pu8SCI_Receive_Data_ptr = &(asc0_CommunicationBuf.b_receive[0]);
  PeriodicTask10ms_reserved1_Transmit_Complete =TRUE;
  PeriodicTask10ms_reserved2_Transmit_Complete = TRUE;
  
  
  PeriodicTask10ms_reserved1_Package_Complete = FALSE;
  PeriodicTask10ms_reserved2_Package_Complete = FALSE;
  PeriodicTask100ms_Package_Complete = FALSE;
  PeriodicTasksyn_Package_Complete = FALSE;
  PositiveResponse_Package_Complete =FALSE;
  
  //Delay_Task10ms_PeriodicTransmit=FALSE;//延迟时间复位
  

//	kwp2000_Format=0x00;
	kwp2000_ServiceId = 0;
  Clear_Buffer();
	asc0_ComMode=KWP2000_WAITRECEPTION;
  b_Transmitted =0;
  Record_Download_Data_Len = 0;
//	asc0_MaxToReceive=KWP2000_MAXTORECEIVE;
}

/**********************************************************************
***                                                                 ***
*** Task     : -                                                    ***
*** Name     : asc0_KWP2000_MemoryWrite_AddressTest                 ***
*** Returns  : KWP2000_MEMTYPE_EEPROM, KWP2000_MEMTYPE_EFLASH,   	  ***
***			   KWP2000_MEMTYPE_XRAM, KWP2000_MEMTYPE_IRAM, 		        	***
***			   KWP2000_MEMTYPE_ERAM,KWP2000_MEMTYPE_UNDEFINED           ***
*** Inputs   : memorySize, memoryAddress                            ***
*** Outputs  : -                                                    ***
*** Calls    : -                                                    ***
*** Action   : Tests the if the given range of address is writable  ***
***                                                                 ***
*** Modified : 12/08/1997                                           ***
***                                                                 ***
**********************************************************************/
UINT8 KWP2000_MemoryWrite_AddressTest(UINT8 memorySize,UINT16 memoryAddress)
{
  	UINT16 endAddress;

  	endAddress=(UINT16)memoryAddress+memorySize-1;
  	/* is the requested area within the external ram area */
  	if(((UINT16)memoryAddress>=0x2000)&&((UINT16)endAddress<=0x3FFF))
  	{
  		/* the memoryAddress is within the external ram area */
  		return KWP2000_MEMTYPE_RAM;
  	}
  	else if(((UINT16)memoryAddress>=0x4000)&&((UINT16)endAddress<=0xFFFF))
  	{
  		/* the memoryAddress is within the internal ram area */
  		return KWP2000_MEMTYPE_PFLASH;
  	}
    else if(((UINT16)memoryAddress>=0x400)&&((UINT16)endAddress<=0x13FF))
  	{
  		/* the memoryAddress is within the internal ram area */
  		return KWP2000_MEMTYPE_DFLASH;
  	}
  	else
  	{
  	    return KWP2000_MEMTYPE_UNDEFINED;
  	}
}





/*********************************************************
**返回握手成功正响应
**
**********************************************************/
void Return_Answer(UINT8 service_id)
{
    UINT8 answer_buf[6] = {0x80,0x00,0x00,0x01,0x00,0x00};
    UINT8 i;
    answer_buf[4]=service_id;
    for(i=0;i<6;i++)
    {
       SCI_WriteTx(answer_buf[i]);
    } 
}


/*********************************************************
** 根据标定数据告知ProCAL是否需要密码才下载数据   
**
**********************************************************/         
UINT8 Send_NeedPassword_PositiveResponse(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    
    *blockByte++ = DOWNLOAD_NEED_PASSWORD_POSITIVERESPONSE;
    *blockByte++ = (CV_DSM  & 16)>>4;//B_Passwd;
    bufPos += 2;
    
    return bufPos;
}



/*********************************************************
**将ProCAL返回的密码进行验证，返回验证结果
**
**********************************************************/
UINT8 Send_CheckPassword_PositiveResponse(UINT8 *blockByte)
{
    UINT8 bufPos=0;
    UINT32 passwd_temp[8];
    UINT32 temp;
    temp = VAL_ECU_Passwd;
    *blockByte++ = DOWNLOAD_CHECK_PASSWORD_POSITIVERESPONSE;
    
    passwd_temp[0] =temp/10000000;
    
    temp = temp%10000000;
    passwd_temp[1] =temp/1000000;
    
    temp = temp%1000000;
    passwd_temp[2] =temp/100000;
    temp = temp%100000;
    passwd_temp[3] =temp/10000;
    temp = temp%10000;
    passwd_temp[4] =temp/1000;
    temp = temp%1000;
    passwd_temp[5] =temp/100;
    temp = temp%100;
    passwd_temp[6] =temp/10;
    temp = temp%10;
    passwd_temp[7] =temp;
    
    if((UINT8)passwd_temp[0] == asc0_CommunicationBuf.b_receive[headerSize+1]
       && (UINT8)passwd_temp[1] == asc0_CommunicationBuf.b_receive[headerSize+2]
       && (UINT8)passwd_temp[2] == asc0_CommunicationBuf.b_receive[headerSize+3]
       && (UINT8)passwd_temp[3] == asc0_CommunicationBuf.b_receive[headerSize+4]
       && (UINT8)passwd_temp[4] == asc0_CommunicationBuf.b_receive[headerSize+5]
       && (UINT8)passwd_temp[5] == asc0_CommunicationBuf.b_receive[headerSize+6]
       && (UINT8)passwd_temp[6] == asc0_CommunicationBuf.b_receive[headerSize+7]
       && (UINT8)passwd_temp[7] == asc0_CommunicationBuf.b_receive[headerSize+8])
     //=====密码验证成功
    {
        *blockByte++ = 1;
    }
    else//====密码验证失败
    {
        *blockByte++ = 0;
    }
    bufPos+=2;
    
    return bufPos;
}

/*********************************************************
**验证序列号的Counter是否写成功
**
**********************************************************/
UINT8 CheckSerialNumCounter(UINT16 counter)
{
     UINT16 memoryAddress;
     UINT16 Counter_ECU_temp;
     memoryAddress = NVM_SERIAL_NUMBER_COUNTER_LOCALADDRESS;
     Counter_ECU_temp = *(UINT16 *)memoryAddress;
     if(counter != Counter_ECU_temp)//=====写失败
     {
         Erase_D_Flash(1,NVM_SERIAL_NUMBER_COUNTER_GLOBALADDRESS);
         Write_Flag(&counter,NVM_SERIAL_NUMBER_COUNTER_GLOBALADDRESS,0x1F);
     }
     
     Counter_ECU_temp = *(UINT16 *)memoryAddress;
     if(counter == Counter_ECU_temp) return TRUE;
     else return FALSE;
}

/*********************************************************
**复位自学习表格
**
**********************************************************/
UINT8 Reset_SelfLearnTab_PositiveResponse(UINT8 *blockByte)
{
    UINT16 InitValue_AN,InitValue_PN;
    UINT8 bufPos=0;
    
    InitValue_AN = asc0_CommunicationBuf.b_receive[headerSize+1];
    InitValue_AN <<= 8;
    InitValue_AN += asc0_CommunicationBuf.b_receive[headerSize+2];
    
    InitValue_PN = asc0_CommunicationBuf.b_receive[headerSize+3];
    InitValue_PN <<= 8;
    InitValue_PN += asc0_CommunicationBuf.b_receive[headerSize+4];
    
    //====2015-3-10SelfLearningTabInit(0);
    
    bufPos+=2;
    *blockByte++ = RESET_SELFLEARNTABLE_POSITIVERESPONSE;
    
    return bufPos;
}

/*********************************************************
**比对密码
**
**********************************************************/
UINT8 KWP2000_CheckPasswordBeforeDownloadOrUpload(UINT8 *Ptr_Passwd)
{
    UINT8 bufPos=0;
    UINT32 passwd_temp[6];
    UINT32 temp;
    temp = RAM_VAL_ECU_Passwd % 1000000;
    
    passwd_temp[0] =temp/100000;
    temp = temp%100000;             
    passwd_temp[1] =temp/10000;
    temp = temp%10000;
    passwd_temp[2] =temp/1000;
    temp = temp%1000;
    passwd_temp[3] =temp/100;
    temp = temp%100;
    passwd_temp[4] =temp/10;
    temp = temp%10;
    passwd_temp[5] =temp;
    
    if((UINT8)passwd_temp[0] == *Ptr_Passwd++
       && (UINT8)passwd_temp[1] == *Ptr_Passwd++
       && (UINT8)passwd_temp[2] == *Ptr_Passwd++
       && (UINT8)passwd_temp[3] == *Ptr_Passwd++
       && (UINT8)passwd_temp[4] == *Ptr_Passwd++
       && (UINT8)passwd_temp[5] == *Ptr_Passwd++)
     //=====密码验证成功
    {
        return TRUE;
    }
    else//====密码验证失败
    {
        return FALSE;
    }
}
