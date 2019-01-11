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
**  延时函数
**
*****************************************************/
void delay(UINT16 j)
{

  UINT8 i;
  for(;j>0;j--)
  for(i=20;i>0;i--);
 
}
/********************************************************
**  写地址命令，将参数写进相应的寄存器
**
********************************************************/
void Write_Address_Command(UINT8 index,UINT8 fcmd,UINT8 addr)
{
  FCCOBIX = index;

  FCCOB = (fcmd<<8) | addr; 
  
}
/********************************************************
**  写数据命令，将参数写进相应的寄存器
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
**清除错误标志位
**
*****************************************************/
void Clear_Error() 
{
       if(FSTAT_ACCERR)
        {
          
          FSTAT_ACCERR = 1;
         // delay(200);      //似乎此处必须加延时
        }
        if(FSTAT_FPVIOL)
        {
          
          FSTAT_FPVIOL = 1;
         
        }
        // delay(100);
}
/*****************************************************
** 设置时钟分频
**
*****************************************************/
void Pre_Start(UINT8 Clock_Divider)
{

 if(FCLKDIV_FDIVLD ==0)
 FCLKDIV |= Clock_Divider;  //设置时钟分频，外部晶振为8Mhz
 
}
/*****************************************************
**开始命令
**
*****************************************************/
void Start_Command()
{
  FSTAT_CCIF = 1;
  while(FSTAT_CCIF ==0);
}
/****************************************************
**写FLASH之前先要进行擦除操作
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
     //WatchDog_Refresh_Pulse(); //刷新看门狗，擦除一个扇区需要的时间为26ms
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
   asm("JSR  erase_ram")   /* 跳到RAM中执行启动命令 */
   EnableInterrupts;
}

/****************************************************
** 写D_FLASH,按字(Word)写
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
     FCLKDIV |= 0x1F;  //设置时钟分频，总线时钟为32Mhz，需分频到1M
     
     if(FSTAT_CCIF)  /*检测FLASH命令是否执行完毕 */
     {
  
        Clear_Error() ; /* 清除错误标志 */
        Write_Address_Command(0x00,Program_Dflash,D_Flash_High); /* Global address[17:16] */
        
        Write_Data_Command(0x01,des_addr);/* 写FLASH的地址，Global address[15:0] */
        Write_Data_Command(0x02,*Ptr++);   /* 写数据 */ 
        Write_Data_Command(0x03,*Ptr++);
        Write_Data_Command(0x04,*Ptr++);
        Write_Data_Command(0x05,*Ptr++);
       
        des_addr+=8;/* 地址加2 */
        DisableInterrupts;
        FSTAT_CCIF = 1;
        while(FSTAT_CCIF ==0);
        EnableInterrupts;
        //Start_Command(); /* 直接在ROM中执行指令 */
      }
      
     //WatchDog_Refresh_Counter++;
     //if(WatchDog_Refresh_Counter>10) //20ms刷新一次
     //{
      //   Restart_COP_Timer();
      //   WatchDog_Refresh_Counter=0;
     //}
  }
}                    


/****************************************************
** 写D_FLASH,按字(Word)写
**
*****************************************************/
void Write_P_Flash(UINT16 *Ptr,INT16 number,UINT16 des_addr)
{
  static UINT8 WatchDog_Refresh_Counter=0;
  
  for(;number>0;number-=8) 
  {
     //Pre_Start();
     if(FCLKDIV_FDIVLD ==0)
     FCLKDIV |= 0x1F;  //设置时钟分频，总线时钟为32Mhz，需分频到1M
     
     if(FSTAT_CCIF)  /*检测FLASH命令是否执行完毕 */
     {
        Clear_Error() ; /* 清除错误标志 */
        Write_Address_Command(0x00,(UINT16)Program_Pflash,P_Flash_High); /* Global address[22:16] */
        Write_Data_Command(0x01,des_addr);/* 写FLASH的地址，Global address[15:0] */
        Write_Data_Command(0x02,*Ptr++);   /* 写数据 */
        Write_Data_Command(0x03,*Ptr++);
        Write_Data_Command(0x04,*Ptr++);
        Write_Data_Command(0x05,*Ptr++);
        des_addr+=8;/* 地址加2 */
        
        DisableInterrupts;//写FLASH时禁止一切中断
        asm("JSR  pro_ram")/* 跳到RAM中执行启动命令 */
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
** 写标志,将块擦除标志和写成功标志写到D_FLASH中存储起来
** 参数1:源数据地址
** 参数2:目标地址
** 参数3:写DFLASH时的CLOCK分频值
*****************************************************/
void Write_Flag(UINT16 *Ptr,UINT16 addr,UINT8 Clock_Divider)
{
  
     
     Pre_Start(Clock_Divider);
     
     if(FSTAT_CCIF)  /*检测FLASH命令是否执行完毕 */
     {
        Clear_Error() ; /* 清除错误标志 */
        Write_Address_Command(0x00,(UINT16)Program_Dflash,D_Flash_High); /* Global address[22:16] */
        
        Write_Data_Command(0x01,addr);/* 写FLASH的地址，Global address[15:0] */
    
        Write_Data_Command(0x02,*Ptr); /* 写数据 */
        DISABLE_INTERRUPTS();  
        Start_Command(); /* 直接在ROM中执行指令 */
        ENABLE_INTERRUPTS();
      }

} 
/****************************************************
** 求得RAM中回写数据的校验和
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
** 取得D_FLASH中数据的校验和
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
** 比较检验后，
** 如果相同，说明写成功，如果不同，返回FALSE，重新写
****************************************************/
UINT8 Checksum_Test(void)
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   /////逐一根据地址比较数值///////////////////////////////////////////////////////////////////////
    UINT16 i;
    UINT16  RAM_StartAddr;
    UINT16  NVM_StartAddr;
    
    
    //////////比较回写数据是否正确/////////////////////////////////////////////////////////////////
    RAM_StartAddr = RAM_WriteBack_Data;
    NVM_StartAddr = DFLASH_BLOCK1_WRITEBACK_LOCALADDRESS;
    
    for(i=0;i<Writeback_Data_Length;i++)
    {
        if(*((UINT8 *)RAM_StartAddr++) != *((UINT8 *)NVM_StartAddr++))//如果有数据不相等 ，立即退出函数，返回FALSE
        {
            return FALSE;
        }
    }
    
    //////////比较故障码是否写成功////////////////////////////////////////////////////////////////
    /*RAM_StartAddr = RAM_DTC;
    NVM_StartAddr = DFLASH_BLOCK4_DTC_LOCALADDRESS;
    
    for(i=0;i<DTC_Length;i++)
    {
        if(*((UINT8 *)RAM_StartAddr++) != *((UINT8 *)NVM_StartAddr++))
        {
            return FALSE;
        }
    }   */
    
    //////////比较自学习表格是否写成功/////////////////////////////////////////////////////////////
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
** 复制RAM中的回写数据到D_FLASH中
**
*****************************************************/
 
UINT8 Copy_WriteBackData_To_NVM(void)
{
    UINT8 temp1,temp2,temp3;

    B_AutoTuningChecksum = FALSE;

    //============此标志位代表NVM已经开始擦除
    /*StartEraseNVM_Flg = 0;
    Erase_D_Flash(1,DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS); 
    Write_Flag(&StartEraseNVM_Flg,DFLASH_BLOCK3_STARTERASE_GLOBALADDRESS,0x1F);  */

    //=====================   
    Erase_D_Flash(4,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS);//擦除0x400至0x10FF  3584 bytes
    //写回写数据
    Ram_Ptr = (UINT16 *)RAM_WriteBack_Data;
    if(Writeback_Data_Length>0)Write_D_Flash(Ram_Ptr,Writeback_Data_Length/8+1,DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS); /* Write block2 */
    
    //写故障码
    //Ram_Ptr = (UINT16 *)RAM_DTC;
    //if(DTC_Length>0)Write_D_Flash(Ram_Ptr,DTC_Length/8+1,DFLASH_BLOCK4_DTC_GLOBALADDRESS);

    //写自学习表格
    /*Ram_Ptr = (UINT16 *)RAM_WO2_Learn;  
    temp2 = CV_SSWO2 & 7;

    if((*(UINT16 *)NVM_ECUFirstRuning_Ptr == 0xFFFF) || ((WO2_Learn_Data_Length>0) && (temp2==7) )) //如果没有使能自学习功能，不允许回写
    {
       Erase_D_Flash(4,DFLASH_BLOCK6_WO2_LEARN_GLOBALADDRESS);
       Convert_Ld_To_fVe();//====2012-12-26 将ld转换成fVe
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
** 验证此次写D_FLASH操作是否成功
** 如果成功返回真，并置成功标志
** 如果失败，再次调用写FLASH函数重新写，
** 如果连续失败三次，置失败标志，也返回真
*****************************************************/
void Write_Successful_Test(void)
{
   UINT8 i;
   for(i=3;i>0;i++)
   {
      if(Copy_WriteBackData_To_NVM())
      {
          RAM_Write_Successful_Flag = 0;/* 写成功标志清零 */
          Write_Flag(&RAM_Write_Successful_Flag,DFLASH_BLOCK3_WRITEERROR_GLOBALADDRESS,0x1F);   /* Write Write_Successful_Flag and Write_Block_Flag*/
          break;   /* 退出for 循环 */
      }
      else
      {
         RAM_Write_Successful_Flag = 0;
      }
      
   }
}


/****************************************************
** 复制RAM中的标定数据到D_FLASH中
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
**  用于诊断时擦写FLASH功能
**
*****************************************************/
void KWP2000_Write_PFlash(UINT16 *Ptr,UINT8 memorySize,UINT16 memoryAddress)
{
    UINT8 i;
    UINT16 Address_buf;
    
    if(memoryAddress==RAM_CALC_Data)
    {
        Record_Download_Data_Len = 0;
        vfnInputs_Outputs_Init();//====2012-9-17 避免出现下载cal时依然喷油和点火
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
     if(FSTAT_CCIF)  /*检测FLASH命令是否执行完毕 */
     {
        Clear_Error() ; /* 清除错误标志 */
        Write_Address_Command(0x00,(UINT16)Read_Once,0); /* Global address[22:16] */
        Write_Data_Command(0x01,Command_Address);/* 写FLASH的地址，Global address[15:0] */

        DisableInterrupts;//写FLASH时禁止一切中断
        //Start_Command();
        asm("JSR  pro_ram")/* 跳到RAM中执行启动命令 */
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


	   /**************P-FLASH部分************************************/
	  if((address>=0x4000)&&(address<0xfeff)&&(page==0))         
	  {
	         address=address+0x030000;                 
	         W_Pflash_flag=1;
	  }
	 
	    /********* P-FLASH分页部分***********************/
	  if((page>=0x08)&&(page<=0x0e))              //PFLASH分页部分 0x08-0x0b&&0x0e
	  {
	  
	    address=(page-0x08)*0x4000+0x20000+(adr-0x8000);    //地址换算
	    W_Pflash_flag=1;
	  }
	  
     /**************RAM部分************************************/
	  if((address>=0x2800)&&(address<0x4000)) 
	  {                 
	         W_RAM_flag=1;//6K RAM
	  }
	  
	   /**************D-FLASH部分************************************/        
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
                                                                         