/*******************************************************************************/
/**
Copyright (c) 2014 COMPANY_ECOTRONS
\file       SPI.c
\brief      Init SPI
\author     COMPANY_GC
\version    1.0
\date       Oct/ 2014
*/
/*******************************************************************************/
#include "typedefs.h"

 /*****************************************************
** 
* \brief    SPI Init .
* \author   Engineer
* \param    void 
* \return   void
* \todo     
**
*****************************************************/

/*****************************************************
** 
* \brief    SPI send data .
* \author   Engineer
* \param    data:  send data 
*           Channel: SPI number 0, 1, 2
* \return   void
* \todo     
**
*****************************************************/

/*****************************************************
** 
* \brief    SPI read data .
* \author   Engineer
* \param    Channel: SPI number 0,1,2 
* \return   data
* \todo     
**
*****************************************************/


/*****************************************************
** 
* \brief    SPI2 Init .
* \author   Engineer
* \param    void 
* \return   void
* \todo     
**
*****************************************************/
void SPI_Init(UINT8 Baud,UINT8 DataBit)
{
    SPI_Enable();//0b01010000;   //使能SPI，禁止中断，时钟高有效，相位为0
    SPI_Sel_Master();
    SPI_Sel_Bit(DataBit);
    SPI_Set_Baud(Baud);//设置SPI时钟频率为8MHz; 
    SPICR1_CPHA = 1;
    SPICR1_CPOL = 1;
                
}  
/*****************************************************
** 
* \brief    SPI2 send data .
* \author   Engineer
* \param    data:  send data 
* \return   void
* \todo     
**
*****************************************************/
UINT8  SPI_Write(UINT16 data) 
{
   UINT16 count = 0;
   while(!SPI_tx_ready)
   {
       count++;
       if(count > 1000) 
       {
           return FALSE;
       }
   }
   if(SPICR2_XFRW == 1)
   {
        SPIDR=data; 
   }
   else
   {
   	    SPIDRL=(UINT8)data; 
   }
   return TRUE;
}
/*****************************************************
** 
* \brief    SPI2 read data .
* \author   Engineer
* \param    void 
* \return   data
* \todo     
**
*****************************************************/
UINT16  SPI_Read(void) 
{
  UINT16 data;
  UINT16 count = 0;
  SPI_Write(0);
  while(!SPI_rx_done);
  {
      count++;
      if(count > 1000) 
      {
          return FALSE;
      }
  }
  data = SPIDRL;
  return(data);
}
