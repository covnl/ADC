/*******************************************************************************/
/**
Copyright (c) 2009 COMPANY_XXX
COMPANY_Confidential_Proprietary
\file       Scheduler.h
\brief      Task scheduler function prototypes
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

#ifndef SCHEDULER_H        /*prevent duplicated includes*/
#define SCHEDULER_H

/*-- Includes ----------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

#define   RTI_RTDEC     CPMURTI_RTDEC
#define   RTI_RTR       CPMURTI_RTR
#define   RTI_RTIF      CPMUFLG_RTIF
#define   RTI_RTIE      CPMUINT_RTIE
#define   RTI_RTIOSCSEL CPMUCLKS_RTIOSCSEL

#define   API_APIFE     CPMUAPICL_APIFE
#define   API_APICLK    CPMUAPICL_APICLK
#define   API_APIES     CPMUAPICL_APIES
#define   API_APIEA     CPMUAPICL_APIEA
#define   API_APIFE     CPMUAPICL_APIFE
#define   API_APIE      CPMUAPICL_APIE
#define   API_APIF      CPMUAPICL_APIF
#define   API_APIR      CPMUAPIR



/*-- Defines -----------------------------------------------------------------*/
#define CrackECU_RunCounters  40//抄板ECU允许的运行次数
#define KeyOnCountersForDZ001  50 //====定制客户keyon次数上限

#define Crank_TimeOut_Timer   60

#define RTI_INTERRUPT(SELECTOR)   CPMUINT_RTIE = SELECTOR
#define API_INTERRUPT(SELECTOR)   CPMUAPICL_APIE = SELECTOR

#define DISABLE_1MS_INTERRUPT     CPMUINT_RTIE=0
#define ENABLE_1MS_INTERRUPT      CPMUINT_RTIE=1 

#define RTI_Prescaler  0x00
#define API_Prescaler  49    //APICLK=0:API分频系数计算公式API_Prescaler = （X-4）/2+1;  X=定时时间*10
                            // 
/* Task Scheduler state machine status definitions */
#define NO_TASK_PENDING     0x00
#define TASKS_1_MS          0x01
#define TASKS_2_MS          0x02
#define TASKS_5_MS          0x03
#define TASKS_10_MS         0x04
#define TASKS_20_MS         0x05
#define TASKS_50_MS         0x06
#define TASKS_100_MS        0x07
#define TASKS_200_MS        0x08
#define TASKS_1000_MS       0x09
#define TASKS_SYN           0x10


#define TASKS_2_MS_A        0x0A
#define TASKS_2_MS_B        0x0B
/* API 初始化用到的定义 */
#define Internal_Clock  0
#define External_Clock  1


/* Global Task Scheduler Status definitions */
#define TASK_SCHEDULER_OK               0x00   
#define TASK_SCHEDULER_OVERLOAD_1MS     0x01
#define TASK_SCHEDULER_OVERLOAD_2MS_A   0x02
#define TASK_SCHEDULER_OVERLOAD_2MS_B   0x03

       
#define  ZERO   0
#define  RTI_DecSelect  1
#define  RTI_BinSelect  0
#define  IRCCLK  0
#define  OSCCLK  1
#define  RTI_INIT_VALUE 0x80
#define  TwentyMs_Per_Second   49
#define  OneS_Per_Minute    10 //59
#define  OneM_Per_Hour      0  //59
#define  TwentyMs_50Ms  3
#define  TwentyMs_100Ms 5
#define  TwentyMs_200Ms 10
#define  TwentyMs_1000Ms 50
#define  OneMs_5Ms 5








//看门狗宏定义
#define FEED_WATCHDOG        2
#define SET_WATCHDOG_RFSH    0
#define CLEAR_WATCHDOG_RFSH  1
/*-- Macros ------------------------------------------------------------------*/
//=====================定义加密字节内容和地址
#define Security_Address 0xFF0E
#define Security_Value   0xFFFE
#define DISABLE_HLS      0x0101


/*-- Function Prototypes -----------------------------------------------------*/

/** Sheduler Initalization (arming) */
void vfnScheduler_Init(void);
void Scheduler_Flg_Clear(void);
void Disable_All_Interrupts(void);

/** Multi-thread round robin task scheduler */
void vfnTask_Scheduler(void);
void KeyOn_Again(void) ;
void EngOff_Timer(void);
void LLD_WriteBackNVM_r10ms(void);
void LLD_EXECUTE_r1ms(void);
void LLD_EXECUTE_r5ms(void);
void LLD_EXECUTE_r10ms(void);
void LLD_EXECUTE_r20ms(void);
void LLD_EXECUTE_r50ms(void);
void LLD_EXECUTE_r100ms(void);
void LLD_EXECUTE_r1000ms(void);
void LLD_Task_Syn(void);

/** ISR that provides time base to MTRR Task Scheduler - */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Task_1ms(void);
void interrupt Task_10ms(void);
#pragma CODE_SEG DEFAULT

void Syn_Counter(void);
void  Check_Security(void);
void Increase_Reset_Counter(void);
/*******************************************************************************/

#endif /* SCHEDULER_H */