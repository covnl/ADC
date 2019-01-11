/*******************************************************************************/
/**
Copyright (c) 2014 COMPANY_ECOTRONS
\file       SPI.h
\brief      Init SCI
\author     COMPANY_GC
\version    1.0
\date       Oct/ 2014
*/
/*******************************************************************************/

#ifndef __SPI_H
#define __SPI_H



#define SPI_Enable()        (SPICR1_SPE = 1)
#define SPI_Disable()       (SPICR1_SPE = 0)
#define SPI_Sel_Master()    SPICR1_MSTR = 1
#define SPI_Sel_Salve()     SPICR1_MSTR = 0
#define SPI_Sel_Bit(value)  SPICR2_XFRW = value   //0-8bit 1-16bit 
#define SPI_Set_Baud(value) SPIBR = value
#define SPI_enabled         SPICR1_SPE
#define SPI_tx_ready        SPISR_SPTEF
#define SPI_rx_done         SPISR_SPIF
#define SPI_DataBuf         SPIDR


//void SPI_Write(UINT8 Channel,UINT16 Data);
//UINT16 SPI_Read(UINT8 Channel);


void SPI_Init(UINT8 Baud,UINT8 DataBit);
UINT8 SPI_Write(UINT16 data); 
UINT16 SPI_Read(void);
#endif