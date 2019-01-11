#ifndef SCI_H        /*prevent duplicated includes*/
#define SCI_H


/*-- Defines -----------------------------------------------------------------*/

#define SCI_INTERRUPT(SELECTOR)   SCICR2_RIE = SELECTOR
#define SCI_TC_INTERRUPT(SELECTOR) SCICR2_TCIE = SELECTOR
/* SCI definition defines */
//#define BUS_FREQ     4000000

#define SCIBusClock             BUS_FREQ

/*-- Communication status defines --------------------------------------------*/
#define SCI_COMM_OK                         0
#define SCI_COMM_TX_BUSY                    1
#define SCI_COMM_RX_OVERRUN                 2
#define SCI_COMM_PORT_ERROR                 3

/*-- Macros ------------------------------------------------------------------*/
#define SCI115200bps    (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(1843200))    //115200 * 16
#define SCI57600bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(921600))    //57600 * 16
#define SCI38400bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(614400))    //38400 * 16
#define SCI19200bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(307200))    //19200 * 16
#define SCI9600bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(153600))    // 9600 * 16
#define SCI4800bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(76800))     // 4800 * 16
#define SCI10400bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(166400))
/*-- Function Prototypes -----------------------------------------------------*/


/** SCI Initalization */
void SCI_Init(void);    
void SCI_Disabled(void);
void SCI_WriteWhenStartup(INT8 *array,UINT8 len);
void SCI_WriteTx(UINT8 u8TxDataByte);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt SCI_Receive_Isr (void);  
#pragma CODE_SEG DEFAULT

#endif

/*******************************************************************************/
