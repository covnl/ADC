#include "typedefs.h"



/* ========================================================================= */
/* Define Global Variables                                                   */
/* ========================================================================= */
UINT16 PWM_Period2; //MBE客户需要的通道2
UINT16 PWM_Period4;//  WGVC输出PWM波




/* ========================================================================= */
/* Function Definitions                                                      */
/* MBE客户PWM频率设置：支持16Hz-2000Hz VAL_FreqWg的值在64-8000之间 */
/* ========================================================================= */
void PWM_Init(void)
{
  #ifdef LLD_V10_3W_HK
    PWM23_Init(HLS_GearPmpCyclePWM45_InitVal); //64us
  #else
    PWM45_Init(HLS_GearPmpCyclePWM45_InitVal); //64us
  #endif  
    PWM01_Init(HLS_ServoCtlCyclePWM01_InitVal);//20ms
}



/*========================================================================*/
/* 禁止PWM输出                                                            */
/*========================================================================*/
void PWM_Disable(void)
{
    PWME = 0;
}

/*========================================================================*/
/* 实时更新PWM占空比，频率只设置一次，是个标定量，占空比是个变量          */
/*========================================================================*/

void PWM_UpdateDutyCycle_20ms(void)
{
     //UINT16 PWM_DutyCycle2;
     UINT16 PWM_DutyCycle4;
     
     //====通道2=============================================================
     //PWM_DutyCycle2 = ((UINT32)DcWg *100) / 65536;
     //PWM_DutyCycle2 = PWM_Period2 *  PWM_DutyCycle2/100;

     //PWMDTY2 = PWM_DutyCycle2;
     //====通道4=============================================================
     PWM_DutyCycle4 = ((UINT32)HLS_DcWg *100) / 65536;
     PWM_DutyCycle4 = PWM_Period4 *  PWM_DutyCycle4/100;

     PWMDTY4 = PWM_DutyCycle4;
}    
                                                                                               
/************************************************
**
**  通道0 1初始化
************************************************/ 
void  PWM01_Init(UINT16 Freq)
{
    if(HLS_VAL_ServoCtlOut_En == FALSE) return;
    DISABLE_PWM1;                 //所有通道禁止输出
    SET_PWM1POL(1);               //开始输出高电平，计数完成反转
    SET_PWM1CTL(1);               //23级联输出；2为高8位 3为输出通道
    PWM1_CLK_SEL_SA();            //选择clockSB为时钟源
    SET_PWM1CAE(0);               //所有通道左对齐
    SET_PWM_Freq_A(1);            // PWMPRCLK[6:4],CLOCKB预分频因子。32/2=16M          
    SET_PWM_Freq_SA(4);           // 16/(2*4)=2M
      
    SET_PWMPER01(Freq);         //周期=PWM_Per/PWM_Freq_SB=40000/2M=20Ms  50Hz  
    SET_PWMDTY01(HLS_PWMDTY01_IniValue);         //占空比寄存器 占空比=PWM_Dty/PWM_Per （PWM_Pol=0时）占空比初始化为5% 
    ENABLE_PWM1;
}

void PWM23_Init(UINT16 Freq)
{
    DISABLE_PWM3;                 //所有通道禁止输出
    SET_PWM3POL(1);               //开始输出高电平，计数完成反转
    SET_PWM3CTL(ENABLED);               //23级联输出；2为高8位 3为输出通道
    PWM3_CLK_SEL_SB();            //选择clockSB为时钟源
    SET_PWM3CAE(0);               //所有通道左对齐
    SET_PWM_Freq_B(0);            // PWMPRCLK[6:4],CLOCKB预分频因子。32/1=32M          
    SET_PWM_Freq_SB(2);           // 32/(2*2)=8M      
    SET_PWMPER23(Freq);         //周期=PWM_Per/PWM_Freq_SB=512/8M = 64us
    SET_PWMDTY3(0);         //占空比寄存器 占空比=PWM_Dty/PWM_Per （PWM_Pol=0时）占空比初始化为5% 
    ENABLE_PWM3;
}

void PWM4_Init(void)
{
    //====通道4=============================================================
    PWM_Period4 = 16000 / HLS_VAL_FreqWg;
    if(PWM_Period4>250)PWM_Period4=250;//频率最大值为最小为16Hz
    else if(PWM_Period4<2)PWM_Period4=2;//频率最大值为2000Hz
    
    PWMPOL_PPOL4 = 1;//PWM output is high at the begining.     
    PWMCLK_PCLK4 = 1;//Clock SCLA is the source for PWM.      
    PWMPRCLK_PCKA = PWM_PRCLKA;//Clock B = Bus Clock / 16      2MHz
    PWMSCLA = PWM_SCLKA;//  Clock SB = Clock B /(2*PWMSCLB)        
    PWMCAE = 0;//PWM in left aligned output mode.        
    PWMCTL = 0;      
    PWMPER4 = PWM_Period4;//PWM period = Clock SA * PWMPERx       
    PWMDTY4 = PWM_Duty_Ch4;//Polarity=0: Duty cycle = PWMDTY/PWMPER      
    PWMSDN = 0; //Disable interrupt        
    PWME_PWME4 = ENABLED;//Enable PWM  
}


void PWM45_Init(UINT16 Freq)
{
    DISABLE_PWM5;                 //所有通道禁止输出
    SET_PWM5POL(1);               //开始输出高电平，计数完成反转
    SET_PWM5CTL(ENABLED);               //45级联输出；4为高8位 5为输出通道
    PWM5_CLK_SEL_SA();            //选择clockSA为时钟源
    SET_PWM5CAE(0);               //所有通道左对齐
    SET_PWM_Freq_A(0);            // PWMPRCLK[6:4],CLOCKA预分频因子。32/1=32M          
    SET_PWM_Freq_SA(2);           // 32/(2*2)=8M      
    SET_PWMPER45(Freq);         //周期=PWM_Per/PWM_Freq_SA=512/8M = 64us
    SET_PWMDTY45(0);         //占空比寄存器 占空比=PWM_Dty/PWM_Per （PWM_Pol=0时）占空比初始化为5% 
    ENABLE_PWM5;
}


/************************************************
**立即输出  占空比可变化
**
************************************************/ 
void SET_PWM_DTY(UINT16 TD,UINT16 dty )   //TD为通道数，DTY为占空比比例因子的分子
{  
    switch(TD) 
    {
        case 1: PWMDTY01=dty;break;
        case 3: PWMDTY23=dty;break;  //这个是添加的
        case 5: PWMDTY45=dty;break;
        default:break;
    }
}

void SET_PWM_Freq(UINT16 TD,UINT16 freq)
{
	  switch(TD) 
    {
        case 1: SET_PWMPER01(freq);break;
      	case 3: SET_PWMPER23(freq);break;
        case 5: SET_PWMPER45(freq);break;
        default:break;
    }
}










