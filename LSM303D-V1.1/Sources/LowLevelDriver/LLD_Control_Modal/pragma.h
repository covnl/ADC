
/****************************************
**��������ĵ�ַ�ռ�
**
**
*****************************************/ 

#ifdef START_SECTION_FastRam   //����RAM��
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_FastRam
#endif

#ifdef STOP_SECTION_FastRam  
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FastRam
#endif

/******************************************************************/
#ifdef START_SECTION_SlowRam  
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_SlowRam
#endif

#ifdef STOP_SECTION_SlowRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SlowRam
#endif

/******************************************************************/
#ifdef START_SECTION_SlowNVM  //��д���ݵ�NVM�� 0x2864-0x28DF
  #pragma DATA_SEG  WRITE_BACK_RAM
  #undef START_SECTION_SlowNVM
#endif

#ifdef STOP_SECTION_SlowNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SlowNVM
#endif

/******************************************************************/
 #ifdef START_SECTION_FcmNVM  //�������RAM�� 0x2800-0x2864
  #pragma DATA_SEG  WRITE_BACK_RAM
  #undef START_SECTION_FcmNVM
#endif

#ifdef STOP_SECTION_FcmNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FcmNVM
#endif


/******************************************************************/
 #ifdef START_SECTION_FastNVM  //��ѧϰ�������0x28E0 - 0x2BFF
  #pragma DATA_SEG  WO2_LEARN_RAM
  #undef START_SECTION_FastNVM
#endif

#ifdef STOP_SECTION_FastNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FastNVM
#endif

/******************************************************************/
#ifdef START_SECTION_SynRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_SynRam
#endif

#ifdef STOP_SECTION_SynRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SynRam
#endif

/******************************************************************/

#ifdef START_SECTION_SynRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_SynRom
#endif

#ifdef STOP_SECTION_SynRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SynRom
#endif

/******************************************************************/
#ifdef START_SECTION_ini2Rom
  #pragma DATA_SEG __NEAR_SEG  CALC_NVM
  #undef START_SECTION_ini2Rom
#endif

#ifdef STOP_SECTION_ini2Rom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_ini2Rom
#endif

/******************************************************************/

#ifdef START_SECTION_r100msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r100msRam
#endif

#ifdef STOP_SECTION_r100msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r100msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r100msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r100msRom
#endif

#ifdef STOP_SECTION_r100msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r100msRom
#endif

/******************************************************************/

#ifdef START_SECTION_r10msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r10msRam
#endif

#ifdef STOP_SECTION_r10msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r10msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r10msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r10msRom
#endif

#ifdef STOP_SECTION_r10msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r10msRom
#endif


/******************************************************************/

 #ifdef START_SECTION_r1msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r1msRam
#endif

#ifdef STOP_SECTION_r1msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r1msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r1msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r1msRom
#endif

#ifdef STOP_SECTION_r1msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r1msRom
#endif


/******************************************************************/

#ifdef START_SECTION_r1000msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r1000msRam
#endif

#ifdef STOP_SECTION_r1000msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r1000msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r1000msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r1000msRom
#endif

#ifdef STOP_SECTION_r1000msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r1000msRom
#endif

/******************************************************************/

#ifdef START_SECTION_r200msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r200msRam
#endif

#ifdef STOP_SECTION_r200msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r200msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r200msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r200msRom
#endif

#ifdef STOP_SECTION_r200msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r200msRom
#endif

/******************************************************************/


#ifdef START_SECTION_r20msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r20msRam
#endif

#ifdef STOP_SECTION_r20msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r20msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r20msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r20msRom
#endif

#ifdef STOP_SECTION_r20msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r20msRom
#endif

/******************************************************************/

#ifdef START_SECTION_r50msRam
  #pragma DATA_SEG  COMMON_RAM
  #undef START_SECTION_r50msRam
#endif

#ifdef STOP_SECTION_r50msRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r50msRam
#endif

/******************************************************************/

#ifdef START_SECTION_r50msRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_r50msRom
#endif

#ifdef STOP_SECTION_r50msRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_r50msRom
#endif

#ifdef START_SECTION_FastRom
  #pragma DATA_SEG __NEAR_SEG CALC_NVM
  #undef START_SECTION_FastRom
#endif

#ifdef STOP_SECTION_FastRom
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FastRom
#endif
  
/*************************************************
**
**
**************************************************/

#ifdef START_SECTION_FcmNVM
  #pragma DATA_SEG  DTC_NVM
  #undef START_SECTION_FcmNVM
#endif

#ifdef STOP_SECTION_FcmNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FcmNVM
#endif

/***********************************************
**�����������Ӧ�Ĵ���ĵ�ַ�ռ�
**
**
************************************************


#ifdef START_SECTION_SynCode
  #pragma CODE_SEG __NEAR_SEG MY_CODE_ROM
  #undef START_SECTION_SynCode
#endif

#ifdef STOP_SECTION_SynCode
  #pragma CODE_SEG  DEFAULT
  #undef STOP_SECTION_SynCode
#endif

******************************************************************

#ifdef START_SECTION_r1msCode
  #pragma CODE_SEG __NEAR_SEG  MY_CODE_ROM
  #undef START_SECTION_r1msCode
#endif

#ifdef STOP_SECTION_r1msCode
  #pragma CODE_SEG  DEFAULT
  #undef STOP_SECTION_r1msCode
#endif

 */
/************************************************
**  ������PFLASH�����ݣ���200���ֽ�
**   CONST_SEG Ҫ��ؼ���const���ʹ��
*************************************************/              

#ifdef START_SECTION_SynPFLASH
  #pragma DATA_SEG __NEAR_SEG  CALC_NVM
  #undef START_SECTION_SynPFLASH
#endif

#ifdef STOP_SECTION_SynPFLASH
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SynPFLASH
#endif

/*************************************************
**
**���俪ͷ��FLASH�ı�����DFLASH��
**************************************************/
/*
#ifdef START_SECTION_CalcNVM
  #pragma DATA_SEG  MY_DATA_DFLASH
  #undef START_SECTION_CalcNVM
#endif

#ifdef STOP_SECTION_CalcNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_CalcNVM
#endif
           */

/*************************************************
**���䲿�ֱ궨������RAM��
**
**************************************************/

#ifdef START_SECTION_CalRam
  #pragma DATA_SEG  CALC_RAM
  #undef START_SECTION_CalRam
#endif

#ifdef STOP_SECTION_CalRam
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_CalRam
#endif



/*************************************************
**NVM��д���ݶ���
**
**************************************************/

#ifdef START_SECTION_SelfLern
  #pragma DATA_SEG  WRITE_BACK_NVM
  #undef START_SECTION_SelfLern
#endif

#ifdef STOP_SECTION_SelfLern
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SelfLern
#endif

/*************************************************
**���ݻ�����������CAN���պͷ��ͣ�
**
**************************************************/

#ifdef START_SECTION_DataBufferRAM
  #pragma DATA_SEG  DATA_BUFFER_RAM
  #undef START_SECTION_DataBufferRAM
#endif

#ifdef STOP_SECTION_DataBufferRAM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_DataBufferRAM
#endif













