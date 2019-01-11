

//========================================================

#define LLD_ServoCtlHighLevelMn  1600   //====Q=V*2000 Unit:ms  0-32.768ms
#define LLD_ServoCtlHighLevelMx  4400   //====Q=V*2000 Unit:ms  0-32.768ms
//#define LLD_ServoCtlDeltaHighLevelMx 2800 //====Q=V*2000 Unit:ms  0-32.768ms





#define PWM_PRCLKB  4
#define PWM_SCLKB   250 //Clock SB = 2M /(2 * 250)


#define PWM_PRCLKA  4
#define PWM_SCLKA   250 //Clock SA = 2M /(2 * 250)

#define PWM_Period_Ch2  2// Clock SB * 2 
#define PWM_Duty_Ch2  1  

#define PWM_Period_Ch4  2// Clock SA * 2   
#define PWM_Duty_Ch4  1


#define SET_PWM_Freq_B(value)   PWMPRCLK_PCKB=value
#define SET_PWM_Freq_A(value)   PWMPRCLK_PCKA=value
#define SET_PWM_Freq_SB(value)  PWMSCLB=value 
#define SET_PWM_Freq_SA(value)  PWMSCLA=value


/************************************************
**
**通道1初始化宏定义
************************************************/ 

#define DISABLE_PWM1            PWME_PWME1=0;
#define ENABLE_PWM1             PWME_PWME1=1;
#define PWM1_CLK_SEL_SA()       PWMCLK_PCLK1=1;
#define SET_PWM1POL(value)      PWMPOL_PPOL1=value
#define SET_PWM1CTL(value)      PWMCTL_CON01=value
#define SET_PWM1CAE(value)      PWMCAE_CAE1=value
/************************************************
**
**通道3初始化宏定义
************************************************/ 
#define DISABLE_PWM3            PWME_PWME3=0;
#define ENABLE_PWM3             PWME_PWME3=1;
#define PWM3_CLK_SEL_SB()       PWMCLK_PCLK3=1;
#define SET_PWM3POL(value)      PWMPOL_PPOL3=value
#define SET_PWM3CTL(value)      PWMCTL_CON23=value
#define SET_PWM3CAE(value)      PWMCAE_CAE3=value
#define SET_PWMPER23(value)      PWMPER23=value 
#define SET_PWMDTY3(value)      PWMDTY3=value

/************************************************
**
**通道4 5初始化宏定义
************************************************/ 

#define DISABLE_PWM5            PWME_PWME5=0;
#define ENABLE_PWM5             PWME_PWME5=1;
#define PWM5_CLK_SEL_SA()       PWMCLK_PCLK5=1;
#define SET_PWM5POL(value)      PWMPOL_PPOL5=value
#define SET_PWM5CTL(value)      PWMCTL_CON45=value
#define SET_PWM5CAE(value)      PWMCAE_CAE5=value


#define SET_PWMPER01(value)      PWMPER01=value 
#define SET_PWMPER45(value)      PWMPER45=value 

#define SET_PWMDTY01(value)      PWMDTY01=value
#define SET_PWMDTY45(value)      PWMDTY45=value
 

void PWM01_Init(UINT16 Freq);
void SET_PWM_DTY(UINT16 TD,UINT16 DTY );
void PWM_UpdateDutyCycle_20ms(void);
void PWM_Init(void);
void PWM_Disable(void);
void PWM23_Init(UINT16 Freq);
void SET_PWM_Freq(UINT16 TD,UINT16 freq);
void PWM45_Init(UINT16 Freq);



                                                 ;