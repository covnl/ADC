/*******************************************************************************/



#define Block1            0
#define Block2            1   


 
#define  DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS    0x4400

#define  DFLASH_BLOCK3_ENGINEOFF_GLOBALADDRESS    0x4800
#define  DFLASH_BLOCK3_WRITEERROR_GLOBALADDRESS   0x4810
#define  DFLASH_BLOCK3_STARTERASE_GLOBALADDRESS   0x4820


#define  NVM_ECU_SOFTWARE_SERIAL_ID_GLOBALADDRESS 0x5000 
#define  NVM_RESET_COUNTER_GLOBALADDRESS          0x5100
#define  NVM_SERIAL_NUMBER_COUNTER_GLOBALADDRESS  0x5200
#define  DFLASH_BOOTLOADER_FLG_GLOBALADDRESS      0x5300



#define  DFLASH_BLOCK1_WRITEBACK_LOCALADDRESS     0x400

#define  DFLASH_BLOCK3_ENGINEOFF_LOCALADDRESS     0x800
#define  DFLASH_BLOCK3_WRITEERROR_LOCALADDRESS    0x810
#define  DFLASH_BLOCK3_STARTERASE_LOCALADDRESS    0x810



#define  NVM_SERIAL_NUMBER_COUNTER_LOCALADDRESS   0x1200
#define  ROM_SERIAL_NUMBER                        0x1300


/*********匹配CCP*************************/
#define  NVM_SerialNumber_GlobalAddress  NVM_ECU_SOFTWARE_SERIAL_ID_GLOBALADDRESS
#define  NVM_CALC_Data  RAM_CALC_Data

/**********************************************/


#define   RAM_DTC              0x2800
#define   RAM_WriteBack_Data   0x2800
#define   RAM_WO2_Learn        0x28D0
#define   RAM_CALC_Data        0x4000

#define   ROM_BOOT_VERSION_ADDRESS 0x2000
#define   ROM_DISABLE_ECU_ADDRESS 0x2200

#define Calibration_Data_Length  1203u
#define Writeback_Data_Length  78u
#define DTC_Length       30u  //(不要超过47byte)
#define WO2_Learn_Data_Length 0u

                         
 /************************************************
 ** 函数原型声明
 *************************************************/

void Copy_WriteBackData_To_Ram(void);
void vfnIni_LLD(void);
void Powerup_Interface(void);
void Powerdown_Interface(void);
void vfnDisable_LLD(void);
void Pre_Start_AD(void); 
void Check_B_Pwf_LastTime(void);
void Erase_DFLASH_Sector_2_256_Byte_After_KeyOn(void);