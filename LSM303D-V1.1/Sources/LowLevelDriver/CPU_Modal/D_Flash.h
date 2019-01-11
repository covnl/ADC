#ifndef _D_FLASH_H
#define _D_FLASH_H



/*--  Function Defines -----------------------------------------------------------------*/

void Write_Address_Command(UINT8 index,UINT8 fcmd,UINT8 addr);
void Write_Data_Command(UINT8 index,UINT16 addr);

void Pre_Start(UINT8 Clock_Divider);
void Erase_D_Flash(UINT8 NumberOfSector,UINT16 addr);
void Write_D_Flash(UINT16 *Ptr,UINT16 number,UINT16 des_addr);
void Write_Flag(UINT16 *Ptr,UINT16 addr,UINT8 Clock_Divider);

void Start_Command(void);
void delay(UINT16 j);
void Clear_Error(void);

void Copy_CalcData_To_NVM(void);
UINT8 Copy_WriteBackData_To_NVM(void);

UINT8 Checksum_Test(void);
UINT16 RAM_Checksum_Calc(void);
UINT16 NVM_Checksum_Calc(UINT16 *databuf);
void Write_Successful_Test(void);
void Write_P_Flash(UINT16 *Ptr,INT16 number,UINT16 des_addr);
void Erase_P_Flash(UINT16 addr,UINT8 Page);
void KWP2000_Write_PFlash(UINT16 *Ptr,UINT8 memorySize,UINT16 memoryAddress);
void Read_CopyRight(UINT8 Command_Address,UINT8 *buf);
UINT16 Read_Data_Command(UINT8 index,UINT16 addr);

void Flash_EraseP_Sector(UINT16 Addr,UINT8 Page,UINT8 Sector_Size);
void Flash_WriteD_Array(UINT16 Addr,UINT16 *Data_Ptr,UINT8 Page,UINT16 Size);
uint32_t FLASH_Convert_Address ( uint32_t address) ;
void Flash_EraseD_Sector(UINT16 Addr,UINT8 Page,UINT8 Sector_Size);
void Flash_WriteP_Array(UINT16 Addr,UINT16 *Data_Ptr,UINT8 Page,UINT16 Size);

/******************************************************
**  P-Flash Commands
*/
#define Erase_Verify_All_Blocks       0x01
#define Erase_Verify_Block            0x02
#define Erase_Vefify_Pflash_sector    0x03 
#define Read_Once                     0x04
#define Program_Pflash                0x06
#define Program_Once                  0x07
#define Erase_All_Blocks              0x08
#define Erase_Flash_Block             0x09
#define Erase_Pflash_Sector           0x0a
#define Unsecure_Flash                0x0b
#define Verify_Backdoor_Access_Key    0x0c
#define Set_User_Margin_Level         0x0d
#define Set_Field_Margin_Level        0x0e

/******************************************************
**  D-Flash Commands
*/
#define Erase_Vefify_Dflash_sector    0x10 
#define Program_Dflash                0x11
#define Erase_Dflash_Sector           0x12

/******************************************************
**
*/
#define DFLASH_Sector_Size    256
#define PFLASH_Sector_Size    512


/******************************************************
**
*/    

#define  D_Flash_High  0
#define  P_Flash_Low   2
#define  P_Flash_High  3

//#define  DFLASH_BLOCK1_WRITEBACK_GLOBALADDRESS 0x4400
//#define  DFLASH_BLOCK2_ENGINEOFF_GLOBALADDRESS 0x4500
//#define  DFLASH_BLOCK5_CALCDATA_GLOBALADDRESS   0x4800

#endif