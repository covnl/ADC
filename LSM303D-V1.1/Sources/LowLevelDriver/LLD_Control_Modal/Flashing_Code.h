
#define FlashingCode_CKP   1
#define FlashingCode_MAP   2
#define FlashingCode_Ub    3
#define FlashingCode_TPS   4
#define FlashingCode_ECT   5
#define FlashingCode_IAT   6
#define FlashingCode_LSB1  7
#define FlashingCode_LSB2  8

/*******************函数原型声明***********************/

 void  Fault_Code_Indication_100ms(void);
 void GetDTCNumFromController(void);
 void DTC_FlashingOnePeriod(void);





