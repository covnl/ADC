#include "typedefs.h"


/*
UINT8 const pro_rom[10]=
{
  0x1c,0x01,0x06,0x80,0x1f,0x01,0x06,0x80,0xfb,0x3D
};
*/
UINT8 pro_ram[10]=
{
   0x1c,0x01,0x06,0x80,0x1f,0x01,0x06,0x80,0xfb,0x3D
};

/*    
UINT8 pro_ram[]=
{
   0x1C,0x01,0x06,0x80,0xCE,0x11,0x94,0x04,0x35,0xFD,0x7E,0x31,0x0F,0x3D
};*/

UINT8 erase_ram[10]=
{
   0x1c,0x01,0x06,0x80,0x1f,0x01,0x06,0x80,0xfb,0x3D
};


UINT16 RAM_Write_Successful_Flag;
UINT16 StartEraseNVM_Flg;
//UINT16 RAM_Write_Block_Flag;
UINT16 RAM_Write_tEngOff_Flag;
UINT8 B_AutoTuningChecksum;

UINT16 *Ram_Ptr;
extern UINT16 Record_Download_Data_Len;
extern UINT8 CV_DLSB;
extern UINT8 CV_LSB;
extern UINT8 CV_SSWO2;
extern UINT16 NVM_ECUFirstRuning_Ptr;
extern UINT8 W_Dflash_flag;
extern UINT8 W_Pflash_flag;
extern UINT8 W_RAM_flag;


/****************************************************
**  ��ʱ����
**
*****************************************************/
void delay(UINT16 j)
{

  UINT8 i;
  for(;j>0;j--)
  for(i=20;i>0;i--);
 
}
/********************************************************
**  д��ַ���������д����Ӧ�ļĴ���
**
********************************************************/
void Write_Address_Command(UINT8 index,UINT8 fcmd,UINT8 addr)
{
  FCCOBIX = index;

  FCCOB = (fcmd<<8) | addr; 
  
}
/********************************************************
**  д�������������д����Ӧ�ļĴ���
**
********************************************************/
void Write_Data_Command(UINT8 index,UINT16 addr)
{
  FCCOBIX = index;

  FCCOB = addr; 
  
}

UINT16 Read_Data_Command(UINT8 index,UINT16 addr)
{
  FCCOBIX = index;

  return FCCOB ; 
  
}
/*****************************************************
**��������־λ
**
*****************************************************/
void Clear_Error() 
{
       if(FSTAT_ACCERR)
        {
          
          FSTAT_ACCERR = 1;
         // delay(200);      //�ƺ��˴��������ʱ
        }
        if(FSTAT_FPVIOL)
        {
          
          FSTAT_FPVIOL = 1;
         
        }
        // delay(100);
}
/*****************************************************
** ����ʱ�ӷ�Ƶ
**
*****************************************************/
void Pre_Start(UINT8 Clock_Divider)
{

 if(FCLKDIV_FDIVLD ==0)
 FCLKDIV |= Clock_Divider;  //����ʱ�ӷ�Ƶ���ⲿ����Ϊ8Mhz
 
}
/*****************************************************
**��ʼ����
**
*****************************************************/
void Start_Command()
{
  FSTAT_CCIF = 1;
  while(FSTAT_CCIF ==0);
}
/****************************************************
**дFLASH֮ǰ��Ҫ���в�������
**
****************************************************/
void Erase_D_Flash(UINT8 NumberOfSector,UINT16 addr)
{
  Pre_Start(0x1F);
  for(;NumberOfSector>0;NumberOfSector--)
  {
    
     if(FSTAT_CCIF)
     {
  
       Clear_Error() ;
       Write_Address_Command(0x00,Erase_Dflash_Sector,D_Flash_High);
       Write_Data_Command(0x01,addr);
  
     }
     DisableInterrupts;
     Start_Command();
     EnableInterrupts;
     addr+=0x100;
     //WatchDog_Refresh_Pulse(); //ˢ�¿��Ź�������һ��������Ҫ��ʱ��Ϊ26ms
     //Restart_COP_Timer();
  }
      
}
void Erase_P_Flash(UINT16 addr,UINT8 Page)
{
   Pre_Start(0x1F);
   if(FSTAT_CCIF)
   {
       Clear_Error() ;
       Write_Address_Command(0x00,Erase_Pflash_Sector,Page);
       Write_Data_Command(0x01,addr);
   }
   //Start_Command();
   DisableInterrupts;
   asm("JSR  erase_ram")   /* ����RAM��ִ���������� */
   EnableInterrupts;
}

/****************************************************
** дD_FLASH,����(Word)д
**
*****************************************************/
void Write_D_Flash(UINT16 *Ptr,UINT16 number,UINT16 des_addr)
{
  UINT16 num;
  static UINT8 WatchDog_Refresh_Counter=0;
  for(num=0;num<number;num++) 
  {
    
     //Pre_Start(0x1F);
     if(FCLKDIV_FDIVLD ==0)
     FCLKDIV |= 0x1F;  //����ʱ�ӷ�Ƶ������ʱ��Ϊ32Mhz�����Ƶ��1M
     
     if(FSTAT_CCIF)  /*���FLASH�����Ƿ�ִ����� */
     {
  
        Clear_Error() ; /* ��������־ */
        Write_Address_Command(0x00,Program_Dflash,D_Flash_High); /* Global address[17:16] */
        
        Write_Data_Command(0x01,des_addr);/* дFLASH�ĵ�ַ��Global address[15:0] */
        Write_Data_Command(0x02,*Ptr++);   /* д���� */ 
        Write_Data_Command(0x03,*Ptr++);
        Write_Data_Command(0x04,*Ptr++);
        Write_Data_Command(0x05,*Ptr++);
       
        des_addr+=8;/* ��ַ��2 */
        DisableInterrupts;
        FSTAT_CCIF = 1;
        while(FSTAT_CCIF ==0);
        EnableInterrupts;
        //Start_Command(); /* ֱ����ROM��ִ��ָ�� */
      }
      
     //WatchDog_Refresh_Counter++;
     //if(WatchDog_Refresh_Counter>10) //20msˢ��һ��
     //{
      //   Restart_COP_Timer();
      //   WatchDog_Refresh_Counter=0;
     //}
  }
}                    


/****************************************************
** дD_FLASH,����(Word)д
**
*****************************************************/
void Write_P_Flash(UINT16 *Ptr,INT16 number,UINT16 des_addr)
{
  static UINT8 WatchDog_Refresh_Counter=0;
  
  for(;number>0;number-=8) 
  {
     //Pre_Start();
     if(FCLKDIV_FDIVLD ==0)
     FCLKDIV |= 0x1F;  //����ʱ�ӷ�Ƶ������ʱ��Ϊ32Mhz�����Ƶ��1M
     
     if(FSTAT_CCIF)  /*���FLASH�����Ƿ�ִ����� */
     {
        Clear_Error() ; /* ��������־ */
        Write_Address_Command(0x00,(UINT16)Program_Pflash,P_Flash_High); /* Global address[22:16] */
        Write_Data_Command(0x01,des_addr);/* дFLASH�ĵ�ַ��Global address[15:0] */
        Write_Data_Command(0x02,*Ptr++);   /* д���� */
        Write_Data_Command(0x03,*Ptr++);
        Write_Data_Command(0x04,*Ptr++);
        Write_Data_Command(0x05,*Ptr++);
        des_addr+=8;/* ��ַ��2 */
        
        DisableInterrupts;//дFLASHʱ��ֹһ���ж�
        asm("JSR  pro_ram")/* ����RAM��ִ���������� */
       //Start_Command();
        EnableInterrupts;
      }
      
     // WatchDog_Refresh_Counter++;
     //if(WatchDog_Refresh_Counter>10) //
     //{
      //   Restart_COP_Timer();
      //   WatchDog_Refresh_Counter=0;
     //}
  } 

}

/*******************************************************
** д��־,���������־��д�ɹ���־д��D_FLASH�д洢����
** ����1:Դ���ݵ�ַ
** ����2:Ŀ���ַ
** ����3:дDFLASHʱ��CLOCK��Ƶֵ
*****************************************************/
void Write_Flag(UINT16 *Ptr,UINT16 addr,UINT8 Clock_Divider)
{
  
     
     Pre_Start(Clock_Divider);
     
     if(FSTAT_CCIF)  /*���FLASH�����Ƿ�ִ����� */
     {
        Clear_Error() ; /* ��������־ */
        Write_Address_Command(0x00,(UINT16)Program_Dflash,D_Flash_High); /* Global address[22:16] */
        
        Write_Data_Command(0x01,addr);/* дFLASH�ĵ�ַ��Global address[15:0] */
    
        Write_Data_Command(0x02,*Ptr); /* д���� */
        DISABLE_INTERRUPTS();  
        Start_Command(); /* ֱ����ROM��ִ��ָ�� */
        ENABLE_INTERRUPTS();
      }

} 
/****************************************************
** ���RAM�л�д���ݵ�У���
**
****************************************************/
UINT16 RAM_Checksum_Calc()
{
   UINT8 i;
   UINT16 checksum=0;
   
   for(i=0;i<127;i++)
   {
     // checksum+=RAM_WriteBack_Data[i];
   }
   return checksum;
}

/****************************************************
** ȡ��D_FLASH�����ݵ�У���
**
****************************************************/
UINT16 NVM_Checksum_Calc(UINT16 *databuf)
{
   UINT8 i;
   UINT16 checksum=0; /* clear  */
   
   for(i=0;i<127;i++)
   {
   //   checksum+=databuf[i];
   }
   return checksum;
  
}
/****************************************************
** �Ƚϼ����
** �����ͬ��˵��д�ɹ��������ͬ������FALSE������д
****************************************************/
UINT8 Checksum_Test(void)
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   /////��һ���ݵ�ַ�Ƚ���ֵ///////////////////////////////////////////////////////////////////////
    UINT16 i;
    UINT16  RAM_StartAddr;
    UINT16  NVM_StartAddr;
    
    
    //////////�Ƚϻ�д�����Ƿ���ȷ/////////////////////////////////////////////////////////////////
    RAM_StartAddr = RAM_WriteBack_Data;
    NVM_StartAddr = DFLASH_BLOCK1_WRITEBACK_LOCALADDRESS;
    
    for(i=0;i<Writeback_Data_Length;i++)
    {
        if(*((UINT8 *)RAM_StartAddr++) != *((UINT8 *)NVM_StartAddr++))//��������ݲ���� �������˳�����������FALSE
        {
            return FALSE;
        }
    }
    
    //////////�ȽϹ������Ƿ�д�ɹ�////////////////////////////////////////////////////////////////
    /*RAM_StartAddr = RAM_DTC;
    NVM_StartAddr = DFLASH_BLOCK4_DTC_LOCALADDRESS;
    
    for(i=0;i<DTC_Length;i++)
    {
        if(*((UINT8 *)RAM_StartAddr++) != *((UINT8 *)NVM_StartAddr++))
        {
            return FALSE;
        }
    }   */
    
    //////////�Ƚ���ѧϰ����Ƿ�д�ɹ�/////////////////////////////////////////////////////////////
    /*if(B_AutoTuningChecksum == TRUE)
    {
        RAM_StartAddr = RAM_WO2_Learn;
        NVM_StartAddr = DFLASH_BLOCK6_WO2_LEARN_LOCALADDRESS;
        
        for(i=0;i<WO2_Learn_Data_Length;i++)
        {
            if(*((UINT8 *)RAM_StartAddr++) != *((UINT8 *)NVM_StartAddr++))
            {
                return FALSE;
            }
        }
    }*/
    
    return TRUE;
}

/****************************************************
** ����RAM�еĻ�д���ݵ�D_FLASH��
**
*****************************************************/
 
UINT8 Copy_WriteBackData_To_NVM(void)
{
    UINT8 temp1,temp2,temp3;

    B_AutoTuningChecksum = FALSE;

    //============�˱�־λ����NVM�Ѿ���ʼ����
    /*StartEraseNVM_Flg = 0;
    Erase_D_Flash(1,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS); 
    Write_Flag(&StartEraseNVM_Flg,DFLASH_BLOCK3_STARTERASE_GLOBALADDRESS,0x1F);  */

    //=====================   
    Erase_D_Flash(4,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS);//����0x400��0x10FF  3584 bytes
    //д��д����
    Ram_Ptr = (UINT16 *)RAM_WriteBack_Data;
    if(Writeback_Data_Length>0)Write_D_Flash(Ram_Ptr,Writeback_Data_Length/8+1,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS); /* Write block2 */
    
    //д������
    //Ram_Ptr = (UINT16 *)RAM_DTC;
    //if(DTC_Length>0)Write_D_Flash(Ram_Ptr,DTC_Length/8+1,DFLASH_BLOCK4_DTC_GLOBALADDRESS);

    //д��ѧϰ���
    /*Ram_Ptr = (UINT16 *)RAM_WO2_Learn;  
    temp2 = CV_SSWO2 & 7;

    if((*(UINT16 *)NVM_ECUFirstRuning_Ptr == 0xFFFF) || ((WO2_Learn_Data_Length>0) && (temp2==7) )) //���û��ʹ����ѧϰ���ܣ��������д
    {
       Erase_D_Flash(4,DFLASH_BLOCK6_WO2_LEARN_GLOBALADDRESS);
       Convert_Ld_To_fVe();//====2012-12-26 ��ldת����fVe
       Write_D_Flash(Ram_Ptr,WO2_Learn_Data_Length/8+1,DFLASH_BLOCK6_WO2_LEARN_GLOBALADDRESS);
       B_AutoTuningChecksum = TRUE;
    }  */

    if(Checksum_Test()) // Test checksum 
    {
      return TRUE;
    }
    else 
    {
      return FALSE;
    }
}

/****************************************************
** ��֤�˴�дD_FLASH�����Ƿ�ɹ�
** ����ɹ������棬���óɹ���־
** ���ʧ�ܣ��ٴε���дFLASH��������д��
** �������ʧ�����Σ���ʧ�ܱ�־��Ҳ������
*****************************************************/
void Write_Successful_Test(void)
{
   UINT8 i;
   for(i=3;i>0;i++)
   {
      if(Copy_WriteBackData_To_NVM())
      {
          RAM_Write_Successful_Flag = 0;/* д�ɹ���־���� */
          Write_Flag(&RAM_Write_Successful_Flag,DFLASH_BLOCK3_WRITEERROR_GLOBALADDRESS,0x1F);   /* Write Write_Successful_Flag and Write_Block_Flag*/
          break;   /* �˳�for ѭ�� */
      }
      else
      {
         RAM_Write_Successful_Flag = 0;
      }
      
   }
}


/****************************************************
** ����RAM�еı궨���ݵ�D_FLASH��
**
*****************************************************/
//extern UINT8 BP_InjAngAbt_N[8];
void Copy_CalcData_To_NVM()
{
     //Ram_Ptr = (UINT16 *)RAM_CALC_Data; /* Get the start address of RAM */
     //Ram_Ptr = &BP_InjAngAbt_N[0];
     //Erase_D_Flash(12,DFLASH_BLOCK5_CALCDATA_GLOBALADDRESS); /*Erase 8 sectors up to 2K */
     //Write_D_Flash(Ram_Ptr,Calibration_Data_Length/8+1,DFLASH_BLOCK5_CALCDATA_GLOBALADDRESS);/* Write  */
}


/****************************************************
**  �������ʱ��дFLASH����
**
*****************************************************/
void KWP2000_Write_PFlash(UINT16 *Ptr,UINT8 memorySize,UINT16 memoryAddress)
{
    UINT8 i;
    UINT16 Address_buf;
    
    if(memoryAddress==RAM_CALC_Data)
    {
        Record_Download_Data_Len = 0;
        vfnInputs_Outputs_Init();//====2012-9-17 �����������calʱ��Ȼ���ͺ͵��
        Address_buf = memoryAddress;
        for(i=0;i<16;i++) //Eease 8K 
        {
            Erase_P_Flash(Address_buf,P_Flash_High);
            Address_buf+=PFLASH_Sector_Size;
        }
    }

    Write_P_Flash(Ptr,(INT16)(memorySize),memoryAddress);    
      
}

/***************************************************************
** Read CopyRight
**
***************************************************************/
void Read_CopyRight(UINT8 Command_Address,UINT8 *buf)
{
     UINT16 temp_buf[4];
     
     Pre_Start(0x1F);
     if(FSTAT_CCIF)  /*���FLASH�����Ƿ�ִ����� */
     {
        Clear_Error() ; /* ��������־ */
        Write_Address_Command(0x00,(UINT16)Read_Once,0); /* Global address[22:16] */
        Write_Data_Command(0x01,Command_Address);/* дFLASH�ĵ�ַ��Global address[15:0] */

        DisableInterrupts;//дFLASHʱ��ֹһ���ж�
        //Start_Command();
        asm("JSR  pro_ram")/* ����RAM��ִ���������� */
        EnableInterrupts;
        
        temp_buf[0]=Read_Data_Command(0x02,0); 
        temp_buf[1]=Read_Data_Command(0x03,0);
        temp_buf[2]=Read_Data_Command(0x04,0);
        temp_buf[3]=Read_Data_Command(0x05,0);
        
        *(UINT16 *)buf = temp_buf[0];
        buf+=2;
        *(UINT16 *)buf = temp_buf[1];
        buf+=2;
        *(UINT16 *)buf = temp_buf[2];
        buf+=2;
        *(UINT16 *)buf = temp_buf[3];
        
      }
}


/*****************************************************
** 
* \brief    Flash_WriteP_Array.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
uint32_t FLASH_Convert_Address ( uint32_t address) 
{
    UINT16  adr=0; 
    UINT32  page=0; 
    page=(address>>16);
	  adr=(uint16_t)(address&0x0000ffff);


	   /**************P-FLASH����************************************/
	  if((address>=0x4000)&&(address<0xfeff)&&(page==0))         
	  {
	         address=address+0x030000;                 
	         W_Pflash_flag=1;
	  }
	 
	    /********* P-FLASH��ҳ����***********************/
	  if((page>=0x08)&&(page<=0x0e))              //PFLASH��ҳ���� 0x08-0x0b&&0x0e
	  {
	  
	    address=(page-0x08)*0x4000+0x20000+(adr-0x8000);    //��ַ����
	    W_Pflash_flag=1;
	  }
	  
     /**************RAM����************************************/
	  if((address>=0x2800)&&(address<0x4000)) 
	  {                 
	         W_RAM_flag=1;//6K RAM
	  }
	  
	   /**************D-FLASH����************************************/        
	  if((page==0x01)&&(adr>=0x0400)&&(adr<0x1400)) 
	  {
	       address=0x004000+adr;
	       W_Dflash_flag=1;
	  }
	  return(address);
}

/*****************************************************
** 
* \brief    Erase PFlash.
* \author   Engineer
* \param    addr:Lacal Addr
*           Page:Flash page 2 3
*           clr_memory_size: 1 is a Pflash_Sector  512Byte
* \return   void
* \todo
**
*****************************************************/

void Flash_EraseP_Sector(UINT16 Addr,UINT8 Page,UINT8 Sector_Size)
{
    UINT8 i;
    
    /*for(i=0;i<Sector_Size;i++)
    {
        Erase_P_Flash(Addr,Page);
        Addr +=PFLASH_Sector_Size;    
    }*/
    for(i=0;i<16;i++)
    {
        Erase_P_Flash(Addr,P_Flash_High);
        Addr +=PFLASH_Sector_Size;    
    }
    
}

/*****************************************************
** 
* \brief    Erase DFlash.
* \author   Engineer
* \param    addr:Lacal Addr
*           Page:Flash page 2 3
*           clr_memory_size: 1 is a Pflash_Sector  512Byte
* \return   void
* \todo
**
*****************************************************/

void Flash_EraseD_Sector(UINT16 Addr,UINT8 Page,UINT8 Sector_Size)
{
    
    Erase_D_Flash(Sector_Size,Addr);
    
}

/*****************************************************
** 
* \brief    Flash_WriteP_Array.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void Flash_WriteP_Array(UINT16 Addr,UINT16 *Data_Ptr,UINT8 Page,UINT16 Size)
{
    UINT16 i,SizeOf8,StartAddr;
    if(Size <= 8)
    {
        SizeOf8 = 1;
    }
    else
    {
        if(Size % 8)
        {
            SizeOf8 = Size >>3 + 1;
        }
        else
        {
            SizeOf8 = Size >>3;
        }
    }

    StartAddr = Addr;
    
    Write_P_Flash(Data_Ptr,Size,StartAddr);
}

 
/*****************************************************
** 
* \brief    Flash_WriteD_Array.
* \author   Engineer
* \param    void
* \return   void
* \todo
**
*****************************************************/
void Flash_WriteD_Array(UINT16 Addr,UINT16 *Data_Ptr,UINT8 Page,UINT16 Size)
{
    UINT16 i,SizeOf8,StartAddr;
    if(Size <= 8)
    {
        SizeOf8 = 1;
    }
    else
    {
        if(Size % 8)
        {
            SizeOf8 = Size >>3 + 1;
        }
        else
        {
            SizeOf8 = Size >>3;
        }
    }

    StartAddr = Addr;
    
    Write_D_Flash(Data_Ptr,Size,Addr);
}
                                                                         