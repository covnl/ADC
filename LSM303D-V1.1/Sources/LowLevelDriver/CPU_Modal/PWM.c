#include "typedefs.h"



/* ========================================================================= */
/* Define Global Variables                                                   */
/* ========================================================================= */
UINT16 PWM_Period2; //MBE�ͻ���Ҫ��ͨ��2
UINT16 PWM_Period4;//  WGVC���PWM��




/* ========================================================================= */
/* Function Definitions                                                      */
/* MBE�ͻ�PWMƵ�����ã�֧��16Hz-2000Hz VAL_FreqWg��ֵ��64-8000֮�� */
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
/* ��ֹPWM���                                                            */
/*========================================================================*/
void PWM_Disable(void)
{
    PWME = 0;
}

/*========================================================================*/
/* ʵʱ����PWMռ�ձȣ�Ƶ��ֻ����һ�Σ��Ǹ��궨����ռ�ձ��Ǹ�����          */
/*========================================================================*/

void PWM_UpdateDutyCycle_20ms(void)
{
     //UINT16 PWM_DutyCycle2;
     UINT16 PWM_DutyCycle4;
     
     //====ͨ��2=============================================================
     //PWM_DutyCycle2 = ((UINT32)DcWg *100) / 65536;
     //PWM_DutyCycle2 = PWM_Period2 *  PWM_DutyCycle2/100;

     //PWMDTY2 = PWM_DutyCycle2;
     //====ͨ��4=============================================================
     PWM_DutyCycle4 = ((UINT32)HLS_DcWg *100) / 65536;
     PWM_DutyCycle4 = PWM_Period4 *  PWM_DutyCycle4/100;

     PWMDTY4 = PWM_DutyCycle4;
}    
                                                                                               
/************************************************
**
**  ͨ��0 1��ʼ��
************************************************/ 
void  PWM01_Init(UINT16 Freq)
{
    if(HLS_VAL_ServoCtlOut_En == FALSE) return;
    DISABLE_PWM1;                 //����ͨ����ֹ���
    SET_PWM1POL(1);               //��ʼ����ߵ�ƽ��������ɷ�ת
    SET_PWM1CTL(1);               //23���������2Ϊ��8λ 3Ϊ���ͨ��
    PWM1_CLK_SEL_SA();            //ѡ��clockSBΪʱ��Դ
    SET_PWM1CAE(0);               //����ͨ�������
    SET_PWM_Freq_A(1);            // PWMPRCLK[6:4],CLOCKBԤ��Ƶ���ӡ�32/2=16M          
    SET_PWM_Freq_SA(4);           // 16/(2*4)=2M
      
    SET_PWMPER01(Freq);         //����=PWM_Per/PWM_Freq_SB=40000/2M=20Ms  50Hz  
    SET_PWMDTY01(HLS_PWMDTY01_IniValue);         //ռ�ձȼĴ��� ռ�ձ�=PWM_Dty/PWM_Per ��PWM_Pol=0ʱ��ռ�ձȳ�ʼ��Ϊ5% 
    ENABLE_PWM1;
}

void PWM23_Init(UINT16 Freq)
{
    DISABLE_PWM3;                 //����ͨ����ֹ���
    SET_PWM3POL(1);               //��ʼ����ߵ�ƽ��������ɷ�ת
    SET_PWM3CTL(ENABLED);               //23���������2Ϊ��8λ 3Ϊ���ͨ��
    PWM3_CLK_SEL_SB();            //ѡ��clockSBΪʱ��Դ
    SET_PWM3CAE(0);               //����ͨ�������
    SET_PWM_Freq_B(0);            // PWMPRCLK[6:4],CLOCKBԤ��Ƶ���ӡ�32/1=32M          
    SET_PWM_Freq_SB(2);           // 32/(2*2)=8M      
    SET_PWMPER23(Freq);         //����=PWM_Per/PWM_Freq_SB=512/8M = 64us
    SET_PWMDTY3(0);         //ռ�ձȼĴ��� ռ�ձ�=PWM_Dty/PWM_Per ��PWM_Pol=0ʱ��ռ�ձȳ�ʼ��Ϊ5% 
    ENABLE_PWM3;
}

void PWM4_Init(void)
{
    //====ͨ��4=============================================================
    PWM_Period4 = 16000 / HLS_VAL_FreqWg;
    if(PWM_Period4>250)PWM_Period4=250;//Ƶ�����ֵΪ��СΪ16Hz
    else if(PWM_Period4<2)PWM_Period4=2;//Ƶ�����ֵΪ2000Hz
    
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
    DISABLE_PWM5;                 //����ͨ����ֹ���
    SET_PWM5POL(1);               //��ʼ����ߵ�ƽ��������ɷ�ת
    SET_PWM5CTL(ENABLED);               //45���������4Ϊ��8λ 5Ϊ���ͨ��
    PWM5_CLK_SEL_SA();            //ѡ��clockSAΪʱ��Դ
    SET_PWM5CAE(0);               //����ͨ�������
    SET_PWM_Freq_A(0);            // PWMPRCLK[6:4],CLOCKAԤ��Ƶ���ӡ�32/1=32M          
    SET_PWM_Freq_SA(2);           // 32/(2*2)=8M      
    SET_PWMPER45(Freq);         //����=PWM_Per/PWM_Freq_SA=512/8M = 64us
    SET_PWMDTY45(0);         //ռ�ձȼĴ��� ռ�ձ�=PWM_Dty/PWM_Per ��PWM_Pol=0ʱ��ռ�ձȳ�ʼ��Ϊ5% 
    ENABLE_PWM5;
}


/************************************************
**�������  ռ�ձȿɱ仯
**
************************************************/ 
void SET_PWM_DTY(UINT16 TD,UINT16 dty )   //TDΪͨ������DTYΪռ�ձȱ������ӵķ���
{  
    switch(TD) 
    {
        case 1: PWMDTY01=dty;break;
        case 3: PWMDTY23=dty;break;  //�������ӵ�
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










