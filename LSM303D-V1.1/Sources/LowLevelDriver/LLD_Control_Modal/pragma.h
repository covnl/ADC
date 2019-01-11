
/****************************************
**分配变量的地址空间
**
**
*****************************************/ 

#ifdef START_SECTION_FastRam   //常用RAM区
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
#ifdef START_SECTION_SlowNVM  //回写数据的NVM区 0x2864-0x28DF
  #pragma DATA_SEG  WRITE_BACK_RAM
  #undef START_SECTION_SlowNVM
#endif

#ifdef STOP_SECTION_SlowNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_SlowNVM
#endif

/******************************************************************/
 #ifdef START_SECTION_FcmNVM  //故障码的RAM区 0x2800-0x2864
  #pragma DATA_SEG  WRITE_BACK_RAM
  #undef START_SECTION_FcmNVM
#endif

#ifdef STOP_SECTION_FcmNVM
  #pragma DATA_SEG  DEFAULT
  #undef STOP_SECTION_FcmNVM
#endif


/******************************************************************/
 #ifdef START_SECTION_FastNVM  //自学习表格区域0x28E0 - 0x2BFF
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
**分配需快速响应的代码的地址空间
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
**  分配在PFLASH的数据，共200个字节
**   CONST_SEG 要与关键词const配合使用
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
**分配开头带FLASH的变量到DFLASH中
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
**分配部分标定数据至RAM中
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
**NVM回写数据定义
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
**数据缓冲区（用于CAN接收和发送）
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













