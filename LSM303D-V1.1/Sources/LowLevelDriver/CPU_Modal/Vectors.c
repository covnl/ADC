/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Vectors.c
\brief      Interrupt service routine vectors
\author     COMPANY_XXX
\author     Application Lab
\author     Engineer
\version    0.1
\date       08/Feb/2008
*/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "typedefs.h"

/* Startup defined in Start12.c */
extern void interrupt  _Startup(void);

UINT8 Test_VAR;

/*******************************************************************************/

/* Dummy interrupt service routine */
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Dummy_D_Isr()
{
    //DISABLE_INTERRUPTS();
    //asm
    //{
    //    JMP $F400
    //}
    Test_VAR = 0;
    SCI_WriteTx(0);
}



                         


/*******************************************************************************/
/* 中断向量地址重映射 */
#ifdef Enable_CrankLLD
void (* near const  vectors[])(void) @ 0xEE80 =  {
         
    Dummy_D_Isr,        /* 0x40  0xFF80 ivVsi           */
  Dummy_D_Isr,        /* 0x41  0xFF82 ivVu8Reserved62   */
  Dummy_D_Isr,        /* 0x42  0xFF84 Vatdcompare   */
  Dummy_D_Isr,        /* 0x43  0xFF86 Vhti   */
  Task_10ms,        /* 0x44  0xFF88 ivVapi   */
  Dummy_D_Isr,        /* 0x45  0xFF8A Vlvi   */
  Dummy_D_Isr,        /* 0x46  0xFF8C Vpwmesdn    */
  Dummy_D_Isr,        /* 0x47  0xFF8E Vportp    */
  Dummy_D_Isr,        /* 0x48  0xFF90 ivVu8Reserved55    */
  Dummy_D_Isr,        /* 0x49  0xFF92 ivVu8Reserved54    */
  Dummy_D_Isr,        /* 0x4A  0xFF94 ivVu8Reserved53       */
  Dummy_D_Isr,        /* 0x4B  0xFF96 ivVu8Reserved52       */
  Dummy_D_Isr,        /* 0x4C  0xFF98 ivVu8Reserved51       */
  Dummy_D_Isr,        /* 0x4D  0xFF9A ivVu8Reserved50       */
  Dummy_D_Isr,        /* 0x4E  0xFF9C ivVu8Reserved49        */
  Dummy_D_Isr,        /* 0x4F  0xFF9E ivVu8Reserved48     */
  Dummy_D_Isr,        /* 0x50  0xFFA0 ivVu8Reserved47    */
  Dummy_D_Isr,        /* 0x51  0xFFA2 ivVu8Reserved46    */
  Dummy_D_Isr,        /* 0x52  0xFFA4 ivVu8Reserved45 */
  Dummy_D_Isr,        /* 0x53  0xFFA6 ivVu8Reserved44 */
  Dummy_D_Isr,        /* 0x54  0xFFA8 ivVu8Reserved43   */
  Dummy_D_Isr,        /* 0x55  0xFFAA ivVu8Reserved42   */
  Dummy_D_Isr,        /* 0x56  0xFFAC ivVu8Reserved41   */
  Dummy_D_Isr,        /* 0x57  0xFFAE ivVu8Reserved40   */
  CAN_Tx_Isr,        /* 0x58  0xFFB0 ivVcantx       */
  CAN_Rx_Isr,        /* 0x59  0xFFB2 ivVcanrx       */
  Dummy_D_Isr,        /* 0x5A  0xFFB4 ivVcanerr      */
  Dummy_D_Isr,        /* 0x5B  0xFFB6 ivVcanwkup     */
  Dummy_D_Isr,        /* 0x5C  0xFFB8 ivVflash        */
  Dummy_D_Isr,        /* 0x5D  0xFFBA Vflashfd       */
  Dummy_D_Isr,        /* 0x5E  0xFFBC ivVu8Reserved33   */
  Dummy_D_Isr,        /* 0x5F  0xFFBE ivVu8Reserved32         */
  Dummy_D_Isr,        /* 0x60  0xFFC0 ivVu8Reserved31   */
  Dummy_D_Isr,        /* 0x61  0xFFC2 ivVu8Reserved30   */
  Dummy_D_Isr,        /* 0x62  0xFFC4 ivVu8Reserved29       */
  Dummy_D_Isr,        /* 0x63  0xFFC6 ivVcpmupllclk    */
  Dummy_D_Isr,        /* 0x64  0xFFC8 ivVcpmuocsns    */
  Dummy_D_Isr,        /* 0x65  0xFFCA ivVu8Reserved26      */
  Dummy_D_Isr,        /* 0x66  0xFFCC ivVu8Reserved25   */
  PORT_J_ISR,        /* 0x67  0xFFCE ivVportj   */
  Dummy_D_Isr,        /* 0x68  0xFFD0 ivVu8Reserved23  */
  ATD0_conversion_complete,   /* 0x69  0xFFD2 ivVatd    */
  Dummy_D_Isr,        /* 0x6A  0xFFD4 ivVu8Reserved21         */
  SCI_Receive_Isr,    /* 0x6B  0xFFD6 ivVsci         */
  Dummy_D_Isr,        /* 0x6C  0xFFD8 ivVspi         */
  Dummy_D_Isr,        /* 0x6D  0xFFDA ivVtimpaie      */
  Dummy_D_Isr,        /* 0x6E  0xFFDC ivVtimpaaovf    */
  ECT_OVF_ISR,        /* 0x6F  0xFFDE ivVtimovf       */
  ECT7_ISR, /* 0x70  0xFFE0 ivVtimch7       */
  ECT6_ISR,        /* 0x71  0xFFE2 ivVtimch6       */
  ECT5_ISR,  /* 0x72  0xFFE4 ivVtimch5       */
  ECT4_ISR,        /* 0x73  0xFFE6 ivVtimch4       */    
  ECT3_ISR, /* 0x74  0xFFE8 ivVtimch3       */  
  ECT2_ISR, /* 0x75  0xFFEA ivVtimch2       */
  ECT1_ISR,  /* 0x76  0xFFEC ivVtimch1       */
  ECT0_ISR,  /* 0x77  0xFFEE ivVtimch0       */
  Task_1ms,        /* 0x78  0xFFF0 ivVrti          */
  Dummy_D_Isr,        /* 0x79  0xFFF2 ivVirq          */
  Dummy_D_Isr,        /* 0x7A  0xFFF4 ivVxirq         */
  Dummy_D_Isr,        /* 0x7B  0xFFF6 ivVswi          */
  Dummy_D_Isr,        /* 0x7C  0xFFF8 ivVtrap         */
  Dummy_D_Isr,           /* 0xFFFA  ivVcop               */
  Dummy_D_Isr  /* 0xFFFC  ivVclkmon            */
// _Startup             /*0xFFFE  ivVreset             */
} ;

#else

void (* near const  vectors[])(void) @ 0xEE80 =  {
         
    Dummy_D_Isr,        /* 0x40  0xFF80 ivVsi           */
  Dummy_D_Isr,        /* 0x41  0xFF82 ivVu8Reserved62   */
  Dummy_D_Isr,        /* 0x42  0xFF84 Vatdcompare   */
  Dummy_D_Isr,        /* 0x43  0xFF86 Vhti   */
  Task_10ms,        /* 0x44  0xFF88 ivVapi   */
  Dummy_D_Isr,        /* 0x45  0xFF8A Vlvi   */
  Dummy_D_Isr,        /* 0x46  0xFF8C Vpwmesdn    */
  Dummy_D_Isr,        /* 0x47  0xFF8E Vportp    */
  Dummy_D_Isr,        /* 0x48  0xFF90 ivVu8Reserved55    */
  Dummy_D_Isr,        /* 0x49  0xFF92 ivVu8Reserved54    */
  Dummy_D_Isr,        /* 0x4A  0xFF94 ivVu8Reserved53       */
  Dummy_D_Isr,        /* 0x4B  0xFF96 ivVu8Reserved52       */
  Dummy_D_Isr,        /* 0x4C  0xFF98 ivVu8Reserved51       */
  Dummy_D_Isr,        /* 0x4D  0xFF9A ivVu8Reserved50       */
  Dummy_D_Isr,        /* 0x4E  0xFF9C ivVu8Reserved49        */
  Dummy_D_Isr,        /* 0x4F  0xFF9E ivVu8Reserved48     */
  Dummy_D_Isr,        /* 0x50  0xFFA0 ivVu8Reserved47    */
  Dummy_D_Isr,        /* 0x51  0xFFA2 ivVu8Reserved46    */
  Dummy_D_Isr,        /* 0x52  0xFFA4 ivVu8Reserved45 */
  Dummy_D_Isr,        /* 0x53  0xFFA6 ivVu8Reserved44 */
  Dummy_D_Isr,        /* 0x54  0xFFA8 ivVu8Reserved43   */
  Dummy_D_Isr,        /* 0x55  0xFFAA ivVu8Reserved42   */
  Dummy_D_Isr,        /* 0x56  0xFFAC ivVu8Reserved41   */
  Dummy_D_Isr,        /* 0x57  0xFFAE ivVu8Reserved40   */
  CAN_Tx_Isr,        /* 0x58  0xFFB0 ivVcantx       */
  CAN_Rx_Isr,        /* 0x59  0xFFB2 ivVcanrx       */
  Dummy_D_Isr,        /* 0x5A  0xFFB4 ivVcanerr      */
  Dummy_D_Isr,        /* 0x5B  0xFFB6 ivVcanwkup     */
  Dummy_D_Isr,        /* 0x5C  0xFFB8 ivVflash        */
  Dummy_D_Isr,        /* 0x5D  0xFFBA Vflashfd       */
  Dummy_D_Isr,        /* 0x5E  0xFFBC ivVu8Reserved33   */
  Dummy_D_Isr,        /* 0x5F  0xFFBE ivVu8Reserved32         */
  Dummy_D_Isr,        /* 0x60  0xFFC0 ivVu8Reserved31   */
  Dummy_D_Isr,        /* 0x61  0xFFC2 ivVu8Reserved30   */
  Dummy_D_Isr,        /* 0x62  0xFFC4 ivVu8Reserved29       */
  Dummy_D_Isr,        /* 0x63  0xFFC6 ivVcpmupllclk    */
  Dummy_D_Isr,        /* 0x64  0xFFC8 ivVcpmuocsns    */
  Dummy_D_Isr,        /* 0x65  0xFFCA ivVu8Reserved26      */
  Dummy_D_Isr,        /* 0x66  0xFFCC ivVu8Reserved25   */
  Dummy_D_Isr,        /* 0x67  0xFFCE ivVportj   */
  Dummy_D_Isr,        /* 0x68  0xFFD0 ivVu8Reserved23  */
  ATD0_conversion_complete,   /* 0x69  0xFFD2 ivVatd    */
  Dummy_D_Isr,        /* 0x6A  0xFFD4 ivVu8Reserved21         */
  SCI_Receive_Isr,    /* 0x6B  0xFFD6 ivVsci         */
  Dummy_D_Isr,        /* 0x6C  0xFFD8 ivVspi         */
  Dummy_D_Isr,        /* 0x6D  0xFFDA ivVtimpaie      */
  Dummy_D_Isr,        /* 0x6E  0xFFDC ivVtimpaaovf    */
  Dummy_D_Isr,        /* 0x6F  0xFFDE ivVtimovf       */
  Dummy_D_Isr, /* 0x70  0xFFE0 ivVtimch7       */
  Dummy_D_Isr,        /* 0x71  0xFFE2 ivVtimch6       */
  Dummy_D_Isr,  /* 0x72  0xFFE4 ivVtimch5       */
  Dummy_D_Isr,        /* 0x73  0xFFE6 ivVtimch4       */    
  Dummy_D_Isr, /* 0x74  0xFFE8 ivVtimch3       */  
  Dummy_D_Isr, /* 0x75  0xFFEA ivVtimch2       */
  Dummy_D_Isr,  /* 0x76  0xFFEC ivVtimch1       */
  Dummy_D_Isr,  /* 0x77  0xFFEE ivVtimch0       */
  Task_1ms,        /* 0x78  0xFFF0 ivVrti          */
  Dummy_D_Isr,        /* 0x79  0xFFF2 ivVirq          */
  Dummy_D_Isr,        /* 0x7A  0xFFF4 ivVxirq         */
  Dummy_D_Isr,        /* 0x7B  0xFFF6 ivVswi          */
  Dummy_D_Isr,        /* 0x7C  0xFFF8 ivVtrap         */
  Dummy_D_Isr,           /* 0xFFFA  ivVcop               */
  Dummy_D_Isr  /* 0xFFFC  ivVclkmon            */
// _Startup             /*0xFFFE  ivVreset             */
} ;

#endif

/*******************************************************************************/
