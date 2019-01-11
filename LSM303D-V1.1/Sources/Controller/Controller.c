/*
 * File: Controller.c
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Mon Jun 15 15:15:07 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Mon Jun 15 15:15:09 2015
 */
#include "typedefs.h"
#include "Controller.h"
#include "Controller_private.h"

/* Named constants for block: '<S1115>/LC_SM' */
#define Controller_IN_NO_ACTIVE_CHILD  (0)
#define Controller_IN_LC_inactive      (2)
#define Controller_IN_Enrich_I         (4)
#define Controller_IN_Enlean_P         (2)
#define Controller_IN_Enlean_I         (1)
#define Controller_IN_Enlean_td        (3)
#define Controller_IN_Enrich_td        (6)
#define Controller_IN_Enrich_P         (5)
#define Controller_IN_LC_active        (1)
#define Controller_true                (1U)
#define Controller_false               (0U)
#define Controller_SIGNBMIN            (MIN_int8_T)

/* Named constants for block: '<S1135>/fLcM_SM' */
#define Controller_IN_NO_ACTIVE_CHILD_f (0)
#define Controller_IN_LC_not_activ     (4)
#define Controller_IN_LC_wait          (5)
#define Controller_IN_LC_activ         (2)
#define Controller_IN_LC_Out           (1)
#define Controller_IN_LC_jump          (3)
#define Controller_true_l              (1U)
#define Controller_false_d             (0U)

/* Named constants for block: '<S1492>/_task_trigger_generator' */
#define Controller_IN_DELAY            (2)
#define Controller_IN_POWERUP          (4)
#define Controller_IN_RUN              (5)
#define Controller_IN_POWEROFF         (3)
#define Controller_IN_AFTEER_RUN       (1)
#define Controller_PERIOD_1ms          (1U)
#define Controller_PERIOD_2ms          (2U)
#define Controller_PERIOD_50ms         (50U)
#define Controller_PERIOD_100ms        (100U)
#define Controller_PERIOD_200ms        (200U)
#define Controller_PERIOD_500ms        (500U)
#define Controller_PERIOD_1000ms       (1000U)
#define Controller_PERIOD_5ms          (5U)
#define Controller_PERIOD_10ms         (10U)
#define Controller_PERIOD_20ms         (20U)
#define Controller_false_l             (0U)
#define Controller_true_n              (1U)

/* Exported block states */
uint32_T INT_IntMafLcFof;              /* '<S1112>/Data Store Memory' */
uint16_T UD_LCAD_fLcAdLo;              /* '<S1190>/Data Store Memory' */
uint16_T UD_LCAD_fLcAdUp;              /* '<S1197>/Data Store Memory' */
int16_T UD_LCAD_OfsLcAdSyn;            /* '<S1204>/Data Store Memory' */

#define START_SECTION_CalRam
#include "pragma.h"

/* Definition for custom storage class: Rom */
uint16_T RAM_CUR_Wf_Ldp[18] = { 0U, 24U, 71U, 144U, 285U, 507U, 771U, 1096U,
  1383U, 1708U, 2027U, 2353U, 2679U, 2986U, 3293U, 3600U, 3894U, 4054U };/* characteristic curve: fuel wall film, depenedent on Load predicted  */

uint8_T RAM_CUR_fAst_TmSta[12] = { 96U, 88U, 82U, 70U, 50U, 49U, 39U, 36U, 29U,
  28U, 13U, 12U };                    /* input<BP_fAst_TmSta>, after start enrichment factor */

uint8_T RAM_CUR_fWmp_Tm[12] = { 106U, 106U, 124U, 52U, 50U, 24U, 23U, 12U, 11U,
  9U, 0U, 0U };                       /* Char. Curve, warm-up factor, dependent on engine temp. */

int8_T RAM_MAP_Iga_N_Ld[176] = { 17, 21, 27, 33, 33, 40, 41, 43, 43, 44, 47, 47,
  47, 47, 47, 47, 10, 15, 22, 29, 30, 34, 38, 40, 40, 44, 45, 45, 45, 45, 45, 45,
  1, 8, 17, 21, 21, 24, 31, 35, 34, 40, 42, 42, 42, 42, 42, 42, -10, 2, 12, 15,
  15, 20, 25, 29, 29, 31, 35, 37, 37, 37, 37, 37, -19, -4, 7, 9, 12, 16, 22, 24,
  27, 26, 29, 32, 32, 32, 32, 32, -27, -8, 3, 5, 9, 14, 20, 20, 25, 21, 25, 24,
  24, 24, 24, 24, -27, -11, 0, 2, 6, 12, 17, 18, 22, 18, 22, 21, 21, 21, 21, 21,
  -27, -13, -2, 0, 3, 8, 15, 15, 18, 15, 19, 19, 19, 19, 19, 19, -27, -15, -4, 0,
  1, 7, 12, 13, 15, 13, 16, 18, 19, 19, 19, 19, -27, -17, -4, 0, 0, 7, 11, 11,
  13, 11, 15, 12, 19, 19, 19, 19, -27, -17, -4, 0, 0, 7, 11, 11, 13, 11, 13, 11,
  19, 19, 19, 19 };                   /* characteristic map,  basic ignition angle, dependent on engine speed and load */

uint16_T RAM_MAP_LdTp_Tps_N[192] = { 0U, 1538U, 1848U, 2263U, 2517U, 2851U,
  2994U, 3010U, 3044U, 3096U, 3097U, 3287U, 3297U, 3305U, 3289U, 3289U, 0U,
  1538U, 1775U, 2073U, 2517U, 2851U, 2994U, 3010U, 3044U, 3096U, 3097U, 3287U,
  3297U, 3305U, 3289U, 3289U, 0U, 1538U, 1685U, 1838U, 2429U, 2773U, 3054U,
  3034U, 3097U, 3133U, 3241U, 3287U, 3297U, 3305U, 3289U, 3289U, 0U, 1386U,
  1526U, 1716U, 2174U, 2466U, 2842U, 2987U, 3021U, 3077U, 3021U, 3028U, 3042U,
  3076U, 3067U, 3067U, 0U, 1281U, 1578U, 1783U, 2058U, 2417U, 2794U, 3017U,
  3331U, 3300U, 3239U, 3276U, 3274U, 3281U, 3298U, 3298U, 0U, 1157U, 1554U,
  1765U, 2101U, 2423U, 2767U, 3003U, 3447U, 3619U, 3644U, 3640U, 3639U, 3673U,
  3666U, 3666U, 0U, 982U, 1440U, 1607U, 1816U, 2105U, 2511U, 2722U, 3156U, 3409U,
  3446U, 3467U, 3509U, 3473U, 3484U, 3484U, 0U, 982U, 1312U, 1542U, 1634U, 1862U,
  2091U, 2307U, 2866U, 3119U, 3301U, 3362U, 3374U, 3366U, 3382U, 3382U, 0U,
  1203U, 1372U, 1561U, 1752U, 1939U, 2198U, 2414U, 2871U, 3112U, 3283U, 3357U,
  3413U, 3413U, 3413U, 3413U, 0U, 1189U, 1280U, 1513U, 1596U, 1853U, 2007U,
  2238U, 2707U, 2932U, 3134U, 3280U, 3355U, 3413U, 3413U, 3413U, 0U, 1178U,
  1248U, 1419U, 1582U, 1736U, 1898U, 2042U, 2413U, 2761U, 2953U, 3127U, 3258U,
  3353U, 3413U, 3413U, 0U, 1170U, 1226U, 1340U, 1552U, 1610U, 1827U, 1939U,
  2270U, 2609U, 2818U, 2992U, 3142U, 3258U, 3413U, 3413U };/* characteristic map,  normalized load based on TPS and engine speed (Alpha/N model) */

uint16_T RAM_MAP_fAlt_N_Pam[64] = { 12595U, 12595U, 12595U, 12595U, 12595U,
  12595U, 12595U, 12595U, 12606U, 12606U, 12606U, 12606U, 12606U, 12606U, 12606U,
  12606U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U, 13443U,
  13443U, 13443U, 13443U, 13443U, 13443U, 13443U, 13443U, 14746U, 14746U, 14746U,
  14746U, 14746U, 14746U, 14746U, 14746U, 15565U, 15565U, 15565U, 15565U, 15565U,
  15565U, 15565U, 15565U, 15892U, 15892U, 15892U, 15892U, 15892U, 15892U, 15892U,
  15892U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U };/* Factor altitude for load, dependent on baro pressure and engine speed */

uint16_T RAM_MAP_fVe_Map_N[192] = { 22284U, 22284U, 21806U, 18367U, 19762U,
  21220U, 18416U, 19675U, 17096U, 17925U, 20286U, 21988U, 20095U, 20095U, 20072U,
  19424U, 21426U, 21690U, 19790U, 19807U, 18865U, 19789U, 20405U, 20985U, 21060U,
  21060U, 21060U, 21566U, 23554U, 24335U, 27188U, 25041U, 27004U, 25247U, 26177U,
  26323U, 22665U, 22665U, 22665U, 21834U, 23703U, 26064U, 27424U, 25858U, 29951U,
  28471U, 28006U, 28006U, 21201U, 21201U, 23949U, 23264U, 25120U, 27578U, 27726U,
  28282U, 30962U, 30602U, 28312U, 29596U, 22607U, 22607U, 24419U, 23874U, 25431U,
  27771U, 27201U, 29818U, 30637U, 32638U, 30819U, 27316U, 24364U, 24364U, 25402U,
  24857U, 26561U, 28265U, 28651U, 29328U, 31746U, 34353U, 32742U, 29739U, 24048U,
  26121U, 27123U, 26394U, 28035U, 29675U, 29441U, 28646U, 32542U, 33667U, 32928U,
  31214U, 25189U, 26627U, 27454U, 24102U, 27894U, 29436U, 26347U, 31183U, 33612U,
  36563U, 31994U, 31421U, 25212U, 25448U, 27272U, 27713U, 31237U, 30872U, 28998U,
  28915U, 31595U, 35244U, 32905U, 33227U, 27141U, 27141U, 28672U, 27577U, 30424U,
  31515U, 28759U, 27912U, 31906U, 38809U, 38339U, 34932U, 26886U, 26886U, 27486U,
  25920U, 28474U, 30515U, 28019U, 27554U, 30827U, 38591U, 38245U, 35379U, 25273U,
  25273U, 25684U, 25553U, 27910U, 29958U, 28865U, 26741U, 30702U, 38074U, 37849U,
  33546U, 24472U, 24472U, 25756U, 24070U, 26556U, 29139U, 27629U, 26753U, 29851U,
  36674U, 36568U, 32962U, 22972U, 22972U, 22974U, 22324U, 24595U, 26866U, 26112U,
  24997U, 28281U, 33574U, 34676U, 30540U, 22972U, 22972U, 22974U, 22324U, 24595U,
  26866U, 25681U, 24847U, 27616U, 33406U, 34503U, 30387U };/* Factor Volumatric Efficiency, dependent on pressure and engine speed */

uint8_T RAM_VAL_fFlApp = 64U;          /* fuel enrichment factor, user defined */

#define STOP_SECTION_CalRam
#include "pragma.h"
#define START_SECTION_DFLASH
#include "pragma.h"

/* Definition for custom storage class: Ram */
/*const volatile*/ uint8_T cntEolTst;      /* counter, End Of Line tester allowed */
/*const volatile*/ uint8_T cntrChaoBan;    /* counter */

#define STOP_SECTION_DFLASH
#include "pragma.h"
#define START_SECTION_FastNVM
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T RAM_SelfLearnHistory[20];      /*  Self-learning history, based on the wideband lambda control */
uint16_T fLamAdTab[192];               /* input-X <BP_fVe_N>,input-Y <BP_fVe_Map>, wideband lambda adaptation table */
uint16_T fLamAdTab_an[192];            /* input-X <BP_fVe_N>,input-Y <BP_fVe_Pim>, wideband lambda adaptation table */

#define STOP_SECTION_FastNVM
#include "pragma.h"
#define START_SECTION_FastRam
#include "pragma.h"

/* Declaration for custom storage class: Imported */
/*extern*/ boolean_T B_Afr;                /* ECU control for ECU switch off delay */
/*extern*/ boolean_T B_AfrStaEnd;          /* condition start of ECU-after run or end of start (1->0) */
/*extern*/ boolean_T B_Brk;                /* condition: brake operated */
/*extern*/ boolean_T B_CatHt;              /* condition catalyst heating activated */
/*extern*/ boolean_T B_CatHtFst;           /* Flag for catalyst fast heating */
/*extern*/ boolean_T B_CatWm;              /* Condition catalyst warming */
/*extern*/ boolean_T B_DgPgv;              /*  condition for start of TEV opening */
/*extern*/ boolean_T B_FMemClr;            /* Memory Error flag */
/*extern*/ boolean_T B_FlAdPha;            /* condition fuel adaptation phase */
/*extern*/ boolean_T B_FlAdpDis;           /* condition for basic mixture adaptation disabled */
/*extern*/ boolean_T B_IdlRdy;             /* ready entry into idle */
/*extern*/ boolean_T B_Lsd;                /* Condition antijerking function is active */
/*extern*/ boolean_T B_Pg;                 /* condition for purge active */
/*extern*/ boolean_T B_PgAirLcRst;         /* condition for purge air flow learning, LC reset */
/*extern*/ boolean_T B_Pwf;                /* condition for powerfail */
/*extern*/ boolean_T B_StepDgE;            /* Condition: stepper power stage diagnosis (stepper exclus. triggered f. diagn.) */
/*extern*/ boolean_T B_Syn;                /* is synchronized? */
/*extern*/ boolean_T B_TherOff;            /* power stage switch off for reasons of overtemperature */
/*extern*/ boolean_T B_TstFlSyDg;          /* condition tester request diagnoses fuel supply system */
/*extern*/ boolean_T B_TstReq;             /* condition general tester request */
/*extern*/ uint32_T Current_Timer;         /* current timer of LLD  */
/*extern*/ boolean_T E_FlSyDg;             /* condition for adaption fault thresholds momentarily exceeded; */
/*extern*/ boolean_T E_Lsb;                /* global error: lambda sensor (LSU) upstream pre catalyst */
/*extern*/ boolean_T E_Map;                /* error flag:main load sensor */
/*extern*/ boolean_T E_Pg;                 /* canister purge system diagnosis */
/*extern*/ boolean_T E_Tps;                /* error flag:throttle position sensor error */
/*extern*/ uint8_T EfcCah;                 /* efficiency while catalyst heating */
/*extern*/ uint16_T Err_Calibration_Flag;  /* LLD variable */
/*extern*/ int16_T FlPg;                   /* relative fuel part of the purge control */
/*extern*/ uint8_T Gr;                     /* vehicle Gear detection */
/*extern*/ uint8_T IntMaf_b;               /* integrated air mass flow from engine start to maximum value  */
/*extern*/ boolean_T IsIacErr;             /* Condition: error idle actuator control */
/*extern*/ uint16_T LamAstWmp;             /* lambda setpoint during afterstart and warming up */
/*extern*/ uint16_T LamCatHt;              /* Lambda setpoint for catalyst heating */
/*extern*/ uint16_T LamCatPur;             /* Lambda setpoint catalyst o2 purge function */
/*extern*/ uint16_T LamCmpProt;            /* lambda for component protection */
/*extern*/ uint16_T LamDrv;                /* lambda driver requested */
/*extern*/ uint8_T LamDsr_b;               /* Desired Lambda limitation */
/*extern*/ uint32_T Last_Falling_Edge_Timer;/* LLD timer */
/*extern*/ uint16_T Last_Period_Min_Map_Record;/* LLD variable */
/*extern*/ uint32_T Last_Rising_Edge_Timer;/* LLD timer */
/*extern*/ uint32_T Last_Rising_Edge_Timer_Bak;/* LLD timer */
/*extern*/ uint16_T MafNrmIdcDsr;          /* desired standardised air mass flow through ISA (word) */
/*extern*/ uint16_T MafPgv;                /* mass flow purge control into the manifold */
/*extern*/ uint8_T MafPgv_b;               /* mass flow purge control into the manifold */
/*extern*/ uint16_T Max_Map_Record;        /* LLD variable */
/*extern*/ uint16_T Max_Map_Record_index;  /* LLD variable */
/*extern*/ uint16_T Min_Map_Record;        /* LLD variable */
/*extern*/ uint16_T Min_Map_Record_index;  /* LLD variable */
/*extern*/ uint8_T NIdcCatHt;              /* Idling speed for catalyzer heating */
/*extern*/ uint16_T Nraw;                  /* Engine speed in rpm from LLD */
/*extern*/ uint16_T TqiLsd;                /* indicated torque drivers request after filtering by antijerking function */
/*extern*/ uint16_T UbAdc;                 /* battery voltage; scanned value of microprocessor ADC  */
/*extern*/ uint8_T fFlPgAct;               /* Request form cat monitoring: modify lambda controller amplitude  */
/*extern*/ uint16_T fLcMPg;                /* Request form cat monitoring: modify lambda controller amplitude  */
/*extern*/ uint16_T tEngOff;               /* stop time */
/*extern*/ uint32_T tSeg_l;                /* segment cycle time  */
/*extern*/ uint16_T tToothDrv;             /* tooth period of driven wheel speed sensor */
/*extern*/ uint16_T tToothNonDrv;          /* tooth period of non-driven wheel speed sensor */
/*extern*/ int8_T tdLcCatPur;              /*  Time delay for switching lambda control from catalyst purging */
/*extern*/ uint16_T uLsb;                  /* Voltage signal from the lambda sensor before catalyst */
/*extern*/ uint16_T uMap;                  /* Voltage signal of manifold pressure sensor  */
/*extern*/ uint16_T uMapLd;                /* Voltage signal of manifold pressure sensor,for load  */
/*extern*/ uint16_T uPot;                  /* ADC-voltage of potentiometer sensor  */
/*extern*/ uint16_T uTa;                   /* ADC-voltage of intake air temperature sensor */
/*extern*/ uint16_T uTm;                   /* ADC-voltage of engine coolant temperature sensor */

/* Definition for custom storage class: FastBitField */
struct CSN_BitField_tag CSN_BitField;
struct DLSV_BitField_tag DLSV_BitField;
struct FIRSM_BitField_tag FIRSM_BitField;
struct GenFast_BitField_tag GenFast_BitField;
struct IDCSTP_BitField_tag IDCSTP_BitField;
struct LCEN_BitField_tag LCEN_BitField;
struct LC_BitField_tag LC_BitField;
struct LSH_BitField_tag LSH_BitField;
struct OCSTA_BitField_tag OCSTA_BitField;
struct OFPMP_BitField_tag OFPMP_BitField;
struct SSBARO_BitField_tag SSBARO_BitField;
struct SSMAP_BitField_tag SSMAP_BitField;

/* Definition for custom storage class: Ram */
boolean_T B_LamOvr;                    /* lambda override switch, switch to 2nd fuel table */
boolean_T isLLDCal;                    /* is low level driver calibration enabled? */

#define STOP_SECTION_FastRam
#include "pragma.h"
#define START_SECTION_FastRom
#include "pragma.h"



INT16  VAL_Acc_offset_X = -135;            
INT16  VAL_Acc_offset_Y = -250;
INT16  VAL_Acc_offset_Z = 500; 

UINT8   VAL_SAEJ1939_Broadcast_En = 1;
UINT16  VAL_Angle_Broadcast_Rate = 10;
UINT8   VAL_Angle_Broadcast_FrameType = 1;
UINT32  VAL_Angle_Broadcast_CANID = 0x18F01301; //pgn 61459  
UINT16  VAL_Acceleration_Broadcast_Rate = 10;
UINT8   VAL_Acceleration_Broadcast_FrameType = 1;
UINT32  VAL_Acceleration_Broadcast_CANID = 0x18F00901;

INT16  VAL_Pitch_offset = 0;
INT16  VAL_Roll_offset = 0;

UINT16  VAL_Acc_g = 8200;

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T CV_LampOutSelect = 0U;
/*const volatile*/ uint8_T VAL_Blind_Inj_Times = 3U;
/*const volatile*/ uint8_T VAL_Blind_spark_delay_time = 10U;
/*const volatile*/ uint8_T VAL_CAN0_BaudRate = 3U;/*  CAN bus baudrate 1--1000k 2--800k 3--500k 4--250k 5--125k 6--100k 7--50k 8--20k 9--10k 10--5k  */
/*const volatile*/ uint32_T VAL_CCP_RxID = 256U;/*  CCP protocols Rx ID 11-bit default  */
/*const volatile*/ uint16_T VAL_CDI_pulse_width = 500U;/* CDI trigger pulse width  */
/*const volatile*/ uint8_T VAL_CKP_Pulse_Polarity = 1U;/* = 1 voltage high, =0; voltage low */
/*const volatile*/ uint8_T VAL_CamToothLevel = 1U;/* cam sensor tooth level high or low */
/*const volatile*/ uint16_T VAL_Customer_Counter = 0U;
/*const volatile*/ uint32_T VAL_ECU_Passwd = 0U;/* ECU password, calibratable, customer security only */
/*const volatile*/ uint8_T VAL_GapDetector = 1U;/*  Trigger wheel Gap detection method: 0--Adding tooth; 1--Missing tooth  */
/*const volatile*/ int8_T VAL_IgaOut_Init_Value = -5;
/*const volatile*/ uint8_T VAL_Ign1_Per_360Deg = 0U;/* boolean, use Ignition channel 1 to control both sparks, one spark per 360 CrA */
/*const volatile*/ boolean_T VAL_KickStartEn = 1;/* kick start enabled or not, if enabled, fuel and spark will happen without being synch. */
/*const volatile*/ int16_T VAL_MPIDC_DGain = 0;
/*const volatile*/ int16_T VAL_MPIDC_D_Part_Max = 0;
/*const volatile*/ int16_T VAL_MPIDC_D_Part_Min = 0;
/*const volatile*/ uint8_T VAL_MPIDC_Delay = 0U;
/*const volatile*/ int16_T VAL_MPIDC_PGain = 0;
/*const volatile*/ uint16_T VAL_MPIDC_PID_Max = 0U;
/*const volatile*/ uint16_T VAL_MPIDC_PID_Min = 0U;
/*const volatile*/ int16_T VAL_MPIDC_P_Part_Max = 0;
/*const volatile*/ int16_T VAL_MPIDC_P_Part_Min = 0;
/*const volatile*/ int16_T VAL_MPIDC_TConst = 0;
/*const volatile*/ int16_T VAL_MPIDC_dNmin_Ipart = 0;
/*const volatile*/ uint8_T VAL_Map_Sensor_Location_Y_Manifold = 0U;/* = 1 center, =0; cylinder 1 */
/*const volatile*/ uint8_T VAL_MaxErrTeethPerCyc = 5U;/* Max number of error teeth allowed per cycle, greater than which will cause re-synch; */
/*const volatile*/ int16_T VAL_McDashpotInitValue = 3;
/*const volatile*/ uint16_T VAL_McDashpot_DeltaDecrements = 12U;
/*const volatile*/ uint8_T VAL_McDashpot_NCondition = 10U;
/*const volatile*/ int16_T VAL_McDashpot_TpsCondition = -981;
/*const volatile*/ uint16_T VAL_NTpBlip_Max = 2500U;
/*const volatile*/ uint8_T VAL_N_low_use_second_tooth = 0U;/* use second pulse and the 1st pulse to calculate RPM, when RPM is low  */
/*const volatile*/ uint16_T VAL_NidlUp_IgaMn = 2300U;
/*const volatile*/ uint16_T VAL_NmaxFastSynByMapDrop = 12000U;/* Max engine speed, below which the faster synchro is allowed based on MAP sensor signal drop */
/*const volatile*/ uint8_T VAL_Number_Of_Fuel_Channels_Per_Cylinder = 1U;
/*const volatile*/ uint8_T VAL_Number_Of_Spark_Channels = 0U;
/*const volatile*/ int8_T VAL_OfsTDC2ToothEdge = -5;/* offset angle from the TDC to the TDC tooth edge */
/*const volatile*/ uint8_T VAL_Phase_Detector = 1U;/* 0 --> Cam Sensor  1--> Map Drop  2--> Double Map Drop */
/*const volatile*/ uint8_T VAL_RM0_tooth = 38U;/* tooth number of RM0 (reference mark 0, which is synchro trigger for 1st cyl, it is 2nd tooth rising edge after the Gap for 36-2 config.) */
/*const volatile*/ uint8_T VAL_RM2_tooth = 2U;/* tooth number of RM2 (reference mark 2, which is 360 CrA away from the RM0) */
/*const volatile*/ uint8_T VAL_RM3_tooth = 0U;
/*const volatile*/ uint8_T VAL_RM4_tooth = 0U;
/*const volatile*/ uint16_T VAL_SLM_AN_N2LdRaw = 16U;
/*const volatile*/ uint16_T VAL_SLM_AN_Tps2LdRaw = 12U;
/*const volatile*/ uint16_T VAL_SLM_PN_Map2LdRaw = 3U;
/*const volatile*/ uint16_T VAL_SLM_PN_N2LdRaw = 25U;
/*const volatile*/ uint16_T VAL_SLM_StableCounterGoal = 50U;
/*const volatile*/ uint16_T VAL_SLM_dFactorStableMin = 328U;
/*const volatile*/ uint16_T VAL_SLM_dNStableMin = 800U;
/*const volatile*/ int16_T VAL_SLM_dTpsStableMin = 492;
/*const volatile*/ uint8_T VAL_SelfLearnTabEn = 0U;
/*const volatile*/ uint16_T VAL_ServoNoiseWidthMx = 300U;/*  Servo PWM signal noise high level width max value in us (micro-second) */
/*const volatile*/ uint16_T VAL_ServoPWMHighLevelMn = 500U;/*  Servo PWM signal high level min value in us (micro-second) */
/*const volatile*/ uint16_T VAL_ServoPWMHighLevelMx = 2500U;/*  Servo PWM signal high level max value in us (micro-second) */
/*const volatile*/ uint16_T VAL_ServoPWMPeriod = 7000U;/*  Servo PWM period in us (micro-second) */
/*const volatile*/ boolean_T VAL_ToothDetByRiseEdge = 1;/* If true, detect tooth by the rising edage, otherwise by the falling edge */
/*const volatile*/ uint8_T VAL_ToothTDC = 11U;/* tooth number of TDC position, counting from the Gap, or reference mark (RM0) */
/*const volatile*/ uint8_T VAL_ToothTDC2 = 0U;
/*const volatile*/ uint8_T VAL_ToothTDC3 = 0U;
/*const volatile*/ uint8_T VAL_ToothTDC4 = 0U;
/*const volatile*/ uint32_T VAL_UAVCAN_RxID = 402916376U;/*  UAV CAN Rx ID 29-bit default  */
/*const volatile*/ boolean_T VAL_UseMapLowestForLd = 1;/* Use the MAP sensor voltage signal lowest value for load calculation */
/*const volatile*/ uint8_T VAL_V2_450_DeltaTooth = 0U;
/*const volatile*/ uint8_T VAL_V2_450_N1_Start_Tooth = 0U;
/*const volatile*/ uint8_T VAL_V2_450_N2_Start_Tooth = 0U;
/*const volatile*/ uint32_T VAL_WBO2_CAN_RxID = 218038273U;/*  Wideband O2 controller CAN Rx ID 29-bit default  */
/*const volatile*/ uint8_T VAL_cntCamToothLevelDebounce = 5U;/* counter, cam sensor tooth level debounced */
/*const volatile*/ int8_T VAL_dIgaGap2TdcAdj = -29;/* Ignition angle adjustment from GAP to TDC, for different engines */
/*const volatile*/ int8_T VAL_dIgaIdcMax = 0;/* delta Ignition angle adjustment max for idle control */
/*const volatile*/ int8_T VAL_dIgaIdcMin = -20;/* delta Ignition angle adjustment min for idle control */
/*const volatile*/ uint8_T VAL_dIgaMn_Nidl = 2U;
/*const volatile*/ int16_T VAL_dIgaRmp_Nidl = 799;
/*const volatile*/ int8_T VAL_dInjAngGap2TdcAdj = 0;/* Injection angle adjustment from GAP to TDC, for different engines */
/*const volatile*/ uint8_T VAL_dNIdcIgaBand = 5U;/* Idle RPM control band, withing this band, ignition angle does not change any more.  */
/*const volatile*/ uint16_T VAL_dNidlUp_IgaMn = 200U;
/*const volatile*/ uint8_T VAL_ddIgaMn_Nidl = 10U;
/*const volatile*/ uint8_T VAL_dtInjTpBlip_Max = 0U;
/*const volatile*/ uint8_T VAL_dtInjTpBlip_Min = 0U;
/*const volatile*/ boolean_T VAL_ignore_second_tooth_enable = 1;/* Ignore the second pulse from the pickup? */
/*const volatile*/ uint8_T VAL_ignore_second_tooth_x_apart = 2U;/* second pulse apart from the 1st pulse multiplying factor  */
/*const volatile*/ uint8_T VAL_nTeethBtw2Tdcs = 2U;/* Number of teeth between cylinder #1 TDC to cylinder #2 TDC */
/*const volatile*/ uint8_T VAL_nTeethMiss = 2U;/* number of missing tooth on the tooth-wheel, usually 1 or 2; */
/*const volatile*/ uint8_T VAL_nTeethTot = 36U;/* Total number of teeth on the tooth-wheel, including the missing tooth */
/*const volatile*/ uint8_T VAL_nTeethWheel = 4U;/* Number of mechanical teeth on the trigger wheel */
/*const volatile*/ uint8_T VAL_rTooth_P1_P = 48U;/*  Tooth period ratio, Pre-Period #1 to current Period  */
/*const volatile*/ uint8_T VAL_rTooth_P1_P3 = 48U;/*  Tooth period ratio, Pre-Period #1 to Pre-Period #3  */
/*const volatile*/ uint8_T VAL_rTooth_P2_P = 48U;/*  Tooth period ratio, Pre-Period #2 to current Period  */
/*const volatile*/ uint8_T VAL_rTooth_P2_P3 = 48U;/*  Tooth period ratio, Pre-Period #2 to Pre-Period #3 */
/*const volatile*/ int8_T VAL_stepper_position_ctrl_max = 50;/* stepper motor controller max delta   */
/*const volatile*/ int8_T VAL_stepper_position_ctrl_min = -50;/* stepper motor controller min delta, negative value   */
/*const volatile*/ uint8_T VAL_stepper_position_delta = 1U;/* stepper motor moving delta per control cycle   */
/*const volatile*/ uint16_T VAL_stepper_position_max = 600U;/* Maximum stepper motor position   */
/*const volatile*/ uint16_T VAL_stepper_position_min = 0U;/* Minimum stepper motor position   */
/*const volatile*/ uint16_T VAL_tAftRunMx = 0U;/* ECU after-run timer max */
/*const volatile*/ uint16_T VAL_tEngOffMx = 10U;/* ECU engine-off timer max */
/*const volatile*/ uint16_T VAL_tIgaMn_Nidl = 1000U;
/*const volatile*/ uint16_T VAL_tInj2CSplitLow = 4500U;/* Injection time histeresis lower, for split injection in 2-cycle mode */
/*const volatile*/ uint16_T VAL_tInj2CSplitUp = 5500U;/* Injection time histeresis upper, for split injection in 2-cycle mode */
/*const volatile*/ uint16_T VAL_tInjBrkMin = 2000U;/* minimum injector pulse break time, between every 2 pulses. */
/*const volatile*/ uint16_T VAL_tInjHoldOff = 200U;/* injector open hold OFF time */
/*const volatile*/ uint16_T VAL_tInjHoldOn = 100U;/* injector open hold ON time */
/*const volatile*/ uint16_T VAL_tInjIdleEst = 2500U;/* injection time during idle, estimated; for kick start */
/*const volatile*/ uint16_T VAL_tInjPick = 3000U;/* injector open pick time */
/*const volatile*/ uint32_T VAL_tSegMin_KickStartEn = 120000U;/* segment time > min-threshold, to enable kick start, kick-start not enabled with higher RPM */
/*const volatile*/ uint8_T VAL_toothCamFallingEdge = 34U;/* cam sensor falling edge tooth # from Gap */
/*const volatile*/ uint8_T VAL_toothCamRisingEdge = 30U;/* cam sensor rising edge tooth #, from Gap */
/*const volatile*/ uint16_T VAL_toothDebncTime = 20000U;/* First tooth detecting debounce time */
/*const volatile*/ uint8_T VAL_toothIntkVlvClos = 32U;/* tooth number at which the intake valve closes */
/*const volatile*/ uint8_T VAL_toothMapDropEnd = 29U;/* tooth number at which the MAP sensor signal ends to drop */
/*const volatile*/ uint8_T VAL_toothMapDropStart = 29U;/* tooth number at which the MAP sensor signal starts to drop */
/*const volatile*/ uint32_T VAL_tooth_high_time_max = 3000U;/* max tooth level high time, for tooth validation */
/*const volatile*/ uint16_T VAL_tooth_high_time_min = 60U;/* min tooth level high time, for tooth validation */
/*const volatile*/ uint8_T VAL_tooth_level_verify_counter = 4U;/* low level cal, counter to verify the tooth level */
/*const volatile*/ uint8_T VAL_tooth_level_verify_counter_success = 3U;/* low level cal, successful counter to verify the tooth level */
/*const volatile*/ uint8_T VAL_tooth_level_verify_interval = 15U;/* low level cal, interval break to verify the tooth level */
/*const volatile*/ uint32_T VAL_tooth_low_time_max = 480000U;/* max tooth level low time, for tooth validation */
/*const volatile*/ uint16_T VAL_tooth_low_time_min = 4870U;/* min tooth level low time, for tooth validation */
/*const volatile*/ uint16_T VAL_uMapDropIntkMin = 999U;/* MAP sensor voltage drop during intake stroke, min value for a valid drop */
/*const volatile*/ boolean_T VAL_uMapDropVerifyInSyn = 1;/* MAP sensor voltage drop validation in synch mode enabled */
/*const volatile*/ boolean_T VAL_use_second_tooth_enable = 0;/* Ignore the second pulse from the pickup? */
/*const volatile*/ uint8_T VAL_use_second_tooth_x_apart = 2U;/* second pulse apart from the 1st pulse multiplying factor  */

#define STOP_SECTION_FastRom
#include "pragma.h"
#define START_SECTION_FcmNVM
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T FcmBaro;                      /* Fault code memeory, baro pressure sensor code */
uint16_T FcmCrk;                       /* Fault code memeory, Crank sensor */
uint16_T FcmLsb;                       /* Fault code memeory, lambda sensor before-Cat */
uint16_T FcmLsb2;                      /* Fault code memeory, lambda sensor #2 */
uint16_T FcmLsu;                       /* Fault code memeory, LSU sensor */
uint16_T FcmMap;                       /* Fault code memeory, MAP sensor code */
uint16_T FcmPam;                       /* Fault code memeory, baro pressure sensor code */
uint16_T FcmPgv;                       /* Fault code memeory, canister purge valve */
uint16_T FcmPot;                       /* Fault code memeory, Pot sensor code */
uint16_T FcmTa;                        /* Fault code memeory, intake air temperature sensor code */
uint16_T FcmTilt;                      /* Fault code memeory, Tilt sensor code */
uint16_T FcmTm;                        /* Fault code memeory, engine temperature sensor code */
uint16_T FcmTps;                       /* Fault code memeory, TPS sensor code */
uint16_T FcmTps2;                      /* Fault code memeory, TPS sensor #2 */
uint16_T FcmUb;                        /* Fault code memeory, Battery voltage sensor code */

#define STOP_SECTION_FcmNVM
#include "pragma.h"
#define START_SECTION_SlowNVM
#include "pragma.h"

/* Definition for custom storage class: Ram */
boolean_T B_HotSta;                    /* Condition hot restart */
boolean_T B_LsbDewLst;                 /* condition dew-point exceeds upstream (last trip) */
boolean_T B_StepAfrStp;                /* flag , after-run allowed to be terminated (stepper prepositioned) */
boolean_T B_StepLrn;                   /* flag , for stepper position learning */
boolean_T B_StepLrnAfr;                /* flag , after-run stepper zero position learn) */
boolean_T B_StepLrnEndAfr;             /* flag , end of after-run stepper zero position learning ) */
uint16_T Baro;                         /* Barometric pressure sensor */
uint16_T Err_CrankSensing_Flag;        /* bitFields crank sensing errors, stored in NVM */
uint8_T Err_Fuel_Flag;                 /* bitFields fuel driver errors, stored in NVM */
uint8_T Err_Spark_Flag;                /* bitFields spark driver errors, stored in NVM */
uint32_T Odo_L;                        /* Odo-Meter, in KiloMeter, 32-bit  */
int16_T OfsLcAd;                       /* additive adaptive correction of the relative fuel amount  */
int16_T OfsLcAdSyn;                    /* additive correction (per ignition) of the mixture adaptation */
uint16_T Pam;                          /* Ambient pressure */
uint8_T Pam_b;                         /* Ambient pressure(byte)  */
uint16_T StepPos;                      /* Actual position of stepper motor */
uint8_T TaOff;                         /* Intake air temperature when engine is shut-off */
uint8_T TcatMainOff;                   /* exhaust gas temperature downstream cat.(modelled) at switch off */
uint8_T TexBfCatOff;                   /* exhaust gas temperature (modelled) at switch off */
uint8_T TmOff;                         /* Engine temperature when engine is shut-off */
uint16_T TpsIdl;                       /* Throttle position at idle condition */
uint16_T TpsIdlUp;                     /* Throttle idle position adaptation upper limit */
uint16_T TpsWot;                       /* Throttle position at WOT, raw value  */
uint16_T TpsWotLow;                    /* Throttle WOT position adaptation lower limit */
int16_T dLdIdlAd;                      /* delta load adaptation at idle */
uint16_T fLcAd;                        /* multiplicative correction of the mixture adaptation */
uint16_T fLcAdLo;                      /* multipl. mixture adaptation factor of the lower mult. section  */
uint16_T fLcAdUp;                      /* multipl. mixture adaptation factor higher load */
uint16_T tSokEstm;                     /* soak time for exhaust temperature model */

/* Definition for custom storage class: SlowNVM */
uint8_T nDewNotLsb;                    /* Counter, number of restart without Dew-Point-End Before Cat */

#define STOP_SECTION_SlowNVM
#include "pragma.h"
#define START_SECTION_SlowRam
#include "pragma.h"

/* Definition for custom storage class: SlowBitField */
struct CSPAM_BitField_tag CSPAM_BitField;
struct ESTM_BitField_tag ESTM_BitField;
struct GenSlow_BitField_tag GenSlow_BitField;
struct SSPot_BitField_tag SSPot_BitField;
struct SSTA_BitField_tag SSTA_BitField;
struct SSTM_BitField_tag SSTM_BitField;
struct SSTPS_BitField_tag SSTPS_BitField;
struct SSUB_BitField_tag SSUB_BitField;
struct SSVSP_BitField_tag SSVSP_BitField;
struct SSWO2_BitField_tag SSWO2_BitField;
struct USR_BitField_tag USR_BitField;

#define STOP_SECTION_SlowRam
#include "pragma.h"
#define START_SECTION_SynRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T AccumulatorEnable_FIRSM;      /* accumulation */
boolean_T B_2ndFuelSw;                 /* switch ON to change to secondary fuel (CNG)  */
boolean_T B_FlTrsS;                    /* Enable condition short time part of transient control */
boolean_T B_KeyOn;                     /* Is key switch on? */
boolean_T B_Kill;                      /* Is kill switch on? */
boolean_T B_MapAvg;                    /* Condiion MAP signal Averaged */
boolean_T B_RedWf;                     /* Enable reduction of wall film memory */
boolean_T B_Trs;                       /* transient control active */
boolean_T B_TrsEn;                     /* Enable condition for transient control  */
boolean_T B_WmpEnd;                    /* warm up phase ends */
boolean_T B_WmpRmp;                    /* warm up factor ramping condition */
boolean_T B_WoIgaIntv;                 /* condition no ignition angle intervention of torque structure  */
boolean_T B_fFlRsm;                    /* Condition factor fuel cut-in */
boolean_T B_nfFlRsm;                   /* flag number of restart fuel feed factors */
boolean_T B_tInjMn;                    /* Condition minimum injection time reached  */
boolean_T B_tInjMn2;                   /* Condition minimum injection time reached  */
uint8_T Ctr_FIRSMB_nfFlRsm;
uint16_T DcWg;                         /* duty cycle of the waste gate */
int16_T DcWgI;                         /* I-part, duty cycle of the waste gate,  */
uint16_T DcWgOl;                       /* open-loop control, duty cycle of the waste gate,  */
int16_T DcWgP;                         /* P-part, duty cycle of the waste gate,  */
uint16_T DcWgPid;                      /* PID controller output, duty cycle of the waste gate,  */
boolean_T ER_B_Syn_Ast;                /* Edge rising, synchronized first time */
boolean_T ER_fWmpRmp;                  /* Edge rising, warm up factor rampping starts */
uint16_T FUELPW1;                      /* fuel pulse width, injector #1  */
uint16_T FUELPW2;                      /* fuel pulse width, injector #2  */
uint16_T Fl;                           /* Relative fuel mass */
uint16_T FlTemp2;                      /* Relative fuel mass, temp-value */
int16_T FlTrs;                         /* rel. fuel mass transition compensation without adjustment */
int16_T FlTrsCr;                       /* rel. fuel mass transition compensation  */
int16_T FlTrsS;                        /* rk short term part of transient control */
uint16_T Fuel_Pulse1_In;               /* LLD injection pluse width measured at the input */
uint16_T HrsPerKg;                     /* fuel economy, Hours per Kilogram  */
uint16_T HrsPerKg_A;                   /* fuel economy, Hours per Kilogram  */
uint16_T HrsPerLit;                    /* fuel economy, Hours per Liter  */
uint16_T HrsPerLit_A;                  /* fuel economy, Hours per Liter  */
boolean_T Hysteresis_FL2TI_U16;        /* hysteresis to split the injection time */
boolean_T Hysteresis_FL2TI_U16_2;      /* hysteresis to split the injection time */
int16_T INT_FlTRS_Short;               /* Integrator ,for memory content of the wall wetting difference for short term portion */
int8_T IgaAct;                         /* actual ignition angle */
int8_T IgaBas;                         /* basic ignition angle */
int8_T IgaDsr;                         /* desired ignition angle  */
int8_T IgaFil;                         /* filtered ignition angle  */
int8_T IgaOut;                         /* Ignition angle output value */
int8_T IgaSel;                         /* selected ignition angle  */
int8_T IgaVmx;                         /* ignition angle retard for max vehicle speed */
uint8_T InjAngAbt;                     /* angle injection abort */
uint8_T InjAngAbt0;                    /* angle injection abort */
uint8_T InjAngEnd;                     /* angle injection-end in normal operation */
uint8_T InjAngEnd0;                    /* angle injection-end in normal operation */
int8_T InjAngEnd1;                     /* angle injection-end in normal operation */
int8_T InjAngEnd_Signed;               /* angle injection-end, signed  */
uint16_T KmPerKg;                      /* fuel economy, Kilometer per Kilogram  */
uint16_T KmPerKg_A;                    /* fuel economy, Kilometer per Kilogram  */
uint16_T KmPerLit;                     /* fuel economy, Kilometer per Liter  */
uint16_T KmPerLit_A;                   /* fuel economy, Kilometer per Liter  */
uint16_T LOAD;                         /* Absolute load value */
uint16_T LP100Km;                      /* fuel economy, Miles Per Gallon  */
uint32_T LPK_fAstFil_U32;              /* LowPassFilterK state, afterstart fuel filter  */
uint16_T LPK_fWmpRmp_U8;               /* LowPassFilter K-type, warm up factor */
uint32_T LPT_FlTrsSub_U32;             /* LowPassFilterT state, afterstart counter/filter  */
uint16_T LamAn;                        /* Lambda converted from an Analog voltage input */
uint16_T LamAnDiag;                    /* Lambda converted from an Analog voltage, after diagnosis */
uint16_T LamAnRaw;                     /* Lambda converted from an Analog voltage input, raw value */
uint16_T LamCan;                       /* Lambda from CAN bus, etc */
uint16_T LamCom;                       /* Lambda from communiction, SCI or CAN bus, etc */
uint16_T LamWO2;                       /* Actual Lambda measured by WO2 controller */
uint16_T Ld;                           /* Load, or relative air charge */
uint16_T LdAvgIdl;                     /* Load, averaged for stable idle */
uint8_T LdLmpN;                        /* relative air charge when limp home signal error,depending on Rpm */
uint16_T LdMap;                        /* relative air charge, or load, based on MAP sensor */
uint16_T LdMapPrd;                     /* load predicted based on MAP sensor  */
uint16_T LdMod;                        /* relative air charge, or load, modelled based on TPS */
uint8_T LdNtrl;                        /* relative air charge when in neutral gear */
uint16_T LdPrd;                        /* load predicted for injection time calculation */
uint16_T LdPrdAdd;                     /* load predicted added by delta TPS predicted */
uint16_T LdPrdWt;                      /* load predicted based on weighted MAP vs TPS model */
uint8_T LdPrd_b;                       /* load predicted for injection calculation(byte) */
uint16_T LdSel;                        /* Load, selected from different models (speed density vs. alpha-N) */
uint16_T LdTp;                         /* Load, or air charge, through throttle valve */
uint16_T LdTpCr;                       /* Load through throttle valve, corrected */
uint16_T LdTpNrm;                      /* Load through throttle valve, normalized */
uint16_T LdTpNrmPrd;                   /* relative air charge predicted, normalized */
uint16_T LdTpPrd;                      /* load predicted based on TPS sensor */
uint16_T LdTpTemp;                     /* Load through throttle valve */
uint8_T Ld_b;                          /* Load, or relative air charge (byte) */
uint16_T MAP;                          /* Manifold absolute pressure */
uint16_T Map;                          /* Intake manifold pressure measured with MAP sensor */
uint16_T MapAvg;                       /* Intake manifold pressure averaged over one segment */
uint16_T MapIni;                       /* Intake manifold pressure, initial value */
uint16_T MapInvCls;                    /* Intake manifold pressure at intake valve close moment */
uint8_T Map_b;                         /* Intake manifold pressure, byte value */
uint16_T MeterPerGram;                 /* fuel economy, meter per gram, m/g  */
uint16_T MilePerGal;                   /* fuel economy, Miles Per Gallon  */
uint16_T MilePerGal_A;                 /* fuel economy, Miles Per Gallon  */
uint16_T N;                            /* Engine speed in Rpm */
uint8_T N_b;                           /* engine speed, byte value */
uint8_T N_b1;                          /* engine speed, byte value */
uint8_T N_b2;                          /* engine speed, byte value */
int16_T NgFil;                         /* filtered engine-speed gradient */
int8_T NgFil_b;                        /* filtered engine-speed gradient, byte value */
uint16_T OilPmpOpenCnt;                /* Oil pump open counter   */
uint16_T OilPmpOpenCnt2;               /* Oil pump #2 open counter   */
uint16_T Pim;                          /* intake manifold pressure */
uint16_T PimDsr;                       /* desired intake manifold pressure, boost control */
uint16_T PimMod;                       /* modeled intake manifold pressure */
uint16_T PimPrd;                       /* predicted intake manifold pressure */
uint16_T PimPrdExt;                    /* extrapolated intake manifold pressure */
uint16_T PimPrdM;                      /* predicted intake manifold pressure */
uint8_T Pim_b;                         /* intake manifold pressure (byte) */
uint16_T Pld;                          /* pressure in combustion chamber for load calculation */
uint16_T Qstat;                        /* inejctor flow rate in mg/ms  */
uint16_T Qstat2;                       /* inejctor flow rate in mg/ms  */
uint16_T RPM;                          /* Engine speed */
int8_T SPARK;                          /* spark advance, degree before TDC of #1 cylinder */
uint8_T TpsEqu_b;                      /* throttle position in neutral gear, byte */
uint8_T TpsUnTp;                       /* throttle position at the unthrottled, during which 95% load is reached */
boolean_T UD_B_WmpEnd;                 /* unit delay, warm up factor ends */
uint16_T UD_CSIMM_Ld;                  /* unit delay state, relative air charge  */
uint16_T UD_CSIMM_Ld1;                 /* unit delay state, relative air charge  */
uint16_T UD_CSIMM_Ld2;                 /* unit delay state, relative air charge  */
uint16_T UD_CSIMM_Map2;                /* unit delay state, intake manifold pressure */
uint16_T UD_CSIMM_PimMod;              /* unit delay state, intake manifold pressure */
uint16_T UD_CSIMM_Pmap;                /* unit delay state, intake manifold pressure */
uint16_T UD_CSLDP_LdPrd;               /* unit delay state, relative air charge predicted */
uint16_T UD_CSN_N;                     /* uint delay, filtered engine speed */
uint16_T UD_Cnt_1s;                    /* counter in 1s   */
int32_T UD_DcWgI;                      /* unit delay, I-part, duty cycle of the waste gate,  */
uint8_T UD_FIRSM_DSNumInj_b;
uint8_T UD_FIRSM_DSnCylFlRsm;
uint8_T UD_FLTRS_nInj_b;               /* unit delay, number of injections */
int16_T UD_FlTrsS;                     /* unit delay , transient fuel, short term */
uint16_T UD_Ld_idle1;                  /* unit delay, Load for idle average */
uint16_T UD_Ld_idle2;                  /* unit delay, Load for idle average */
uint16_T UD_Ld_idle3;                  /* unit delay, Load for idle average */
uint16_T UD_MapRaw;                    /* Intake manifold pressure, 2-step delay */
uint16_T UD_N_LdAvgIdl;                /* uint delay, engine speed, for idle load averaging */
int16_T UD_Wf;                         /* unit delay, delta wall film */
uint8_T UD_fWmp1;                      /* unit delay state, warm up fuel factor  */
uint32_T UD_mFuel2_L;                  /* fuel mas accumulated, 32bit  */
uint32_T UD_mFuel_L;                   /* fuel mas accumulated, 32bit  */
uint32_T UD_mFuel_L_1s;                /* fuel mas accumulated, 32bit  */
uint16_T UD_nInj;                      /* number of injections, unit delay  */
uint8_T UD_nInj_b;                     /* number of injections, unit delay  */
int16_T Wf;                            /* wall wetting quantity */
uint16_T WfBas;                        /* wall wetting quantity, base value */
int8_T dIgaRaw;                        /* delta ignition angle raw, considering knock protection,knock control,warm-up */
int16_T dLd;                           /* delta load */
int16_T dLdPrd;                        /* delta predicted load for injection time calculation */
int16_T dLdTpPrd;                      /* delta predicted load based on TPS prediction */
int8_T dPamPim;                        /* delta between ambient and intake manifold pressure */
int16_T dPim;                          /* delta fresh air partial pressure in manifold */
int16_T dPimErr;                       /* PID control error, delta intake manifold pressure, boost control */
int16_T dWf;                           /* Delta fuel of wall film quantity  */
int16_T dWfMemS;                       /* memory of the delta wall film for short term portion */
uint16_T dmFuel;                       /* fuel mass flow rate, g/min  */
uint16_T dmFuelKgPH;                   /* fuel mass flow rate, Kg/Hour  */
uint16_T dmFuelKgPH_A;                 /* fuel mass flow rate, Kg/Hour  */
uint16_T dmFuelPS;                     /* fuel mass for one injection, mg/syn  */
uint16_T dmFuelPS_A;                   /* fuel mass flow rate, g/min  */
uint16_T dmFuel_A;                     /* fuel mass flow rate, g/min  */
uint16_T fAst;                         /* factor after start fuel */
uint16_T fAst0;                        /* factor after start fuel */
uint8_T fAstAlt;                       /* after start factor altitude */
uint8_T fAstHot;                       /* after start factor hot condition */
uint16_T fAstWmp;                      /* Factor afterstart and warm-up fuel */
uint16_T fFl2Ti;                       /* factor: conversion rel. fuel mass into effect. injection time */
uint16_T fFl2Ti2;                      /* factor: conversion rel. fuel mass into effect. injection time */
uint16_T fFl2TiStat;                   /* factor: conversion rel. fuel mass into effect. injection time, static condition */
uint16_T fFl2TiStat2;                  /* factor: conversion rel. fuel mass into effect. injection time, static condition */
uint8_T fFlPrsCr;                      /* factor to correct fuel pressure   */
uint8_T fFlRsm;                        /* fuel resuming factor */
uint16_T fFlSta;                       /* start-fuel factor   */
uint16_T fFlSta0;                      /* start-fuel factor   */
uint16_T fLd2Maf;                      /* factor converting load to mass air flow */
uint16_T fLd2MafSyn;                   /* factor converting load to mass air flow per sync  */
uint16_T fPreCtl;                      /* factor: pre-control fuel */
uint8_T fTfuel;                        /* factor to correct fuel density dependent on temperature   */
uint16_T fTpsPrd;                      /* Factor TPS predicted depending on segment time */
uint16_T fTrsCr;                       /* correction factor short/long time part of transient control */
uint16_T fVe;                          /* volumetric efficiency factor, for converting pressure to load */
uint16_T fVeRaw;                       /* volumetric efficiency factor, for converting pressure to load */
uint16_T fWfAlt;                       /* wall film factor depending on Ambient Pressure */
uint8_T fWmp;                          /* Warm up factor */
uint8_T fWmp0;                         /* Warm up factor step 0 */
uint8_T fWmp1;                         /* Warm up factor step 1 */
uint8_T fWmp2;                         /* Warm up factor step 2 */
uint8_T fWmp3;                         /* Warm up factor step 3 */
uint8_T fWmpRmp;                       /* Warm up factor , rampped  */
uint8_T fwLdpMapTps;                   /* weighting factor of TPS based vs MAP based  predicted load */
boolean_T isMap2Cyl;                   /* is MAP sensor used for synch of 2-cyl system? */
uint16_T kAstFil;                      /* filter coefficient for afterstart fuel   */
uint16_T mFuel;                        /* fuel mass accumulated, gram, 16-bit  */
uint32_T mFuel2_L;                     /* fuel mas accumulated, 32bit  */
uint16_T mFuelSyn;                     /* fuel mass of one sync, mg/syn  */
uint16_T mFuelSyn2;                    /* fuel mass for one injection, mg/syn  */
uint16_T mFuel_1g;                     /* fuel mass accumulated, gram  */
uint32_T mFuel_L;                      /* fuel mas accumulated, 32bit  */
uint8_T nCylFlRsmStp;                  /* number of processed fuel cut-in factors */
uint16_T nInj;                         /* number of injections  */
uint8_T nInjSta;                       /* injection counter for start  */
uint8_T nInj_b;                        /* number of injections, rolling counter  */
uint16_T tInj;                         /* injection time in (ms) */
uint16_T tInj0;                        /* injection time for injector #0  */
uint16_T tInj0Cr;                      /* injection pulse width for fuel mass correction  */
uint16_T tInj1;                        /* injection time for injector #1  */
uint16_T tInj1Cr;                      /* injection pulse width for fuel mass correction  */
uint16_T tInj1stRaw;                   /* raw injection time , 1st injector   */
uint16_T tInj2;                        /* injection time in (ms) */
uint16_T tInj2ndFuel;                  /* injection time, 2nd fuel (CNG)   */
uint16_T tInj2ndRaw;                   /* raw injection time, 2nd injector   */
uint16_T tInjCr;                       /* corercted injection time */
uint16_T tInjCr2;                      /* corercted injection time */
uint16_T tInjIn;                       /* injection pluse width measured at the input */
uint16_T tInjMaxAlw;                   /* max allowed injection time because of high RPM  */
uint16_T tInjPreSta;                   /* injection pulse width for pre-start injection  */
uint16_T tInjRaw;                      /* theoretical raw injection time before fine adjustment   */
uint16_T tInjRaw2;                     /* theoretical raw injection time of injector #2 */
uint8_T tInj_b;                        /* injection pulse in ms, byte  */
uint16_T tRun;                         /* engine running time in second   */
int16_T tdInjUb;                       /* injection time correction dependent on battery voltage */
int16_T tdInjUb2;                      /* injection time correction dependent on battery voltage */
uint16_T vFuel;                        /* fuel volume consumption. accumulated in mL  */
uint16_T vFuelL;                       /* fuel volume consumption. accumulated in L  */

#define STOP_SECTION_SynRam
#include "pragma.h"
#define START_SECTION_SynRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T BP_InjAngAbt_N[8] = { 12U, 23U, 33U, 53U, 67U, 83U, 100U,
  117U };                             /* break points,Engine speed in rpm */

/*const volatile*/ uint8_T BP_InjAngEnd_Ld[8] = { 13U, 27U, 40U, 53U, 67U, 80U, 100U,
  120U };                             /* break points,relative air charge  */

/*const volatile*/ uint8_T BP_InjAngEnd_N[8] = { 12U, 14U, 23U, 33U, 53U, 67U, 83U,
  100U };                             /* break points,Engine speed in rpm */

/*const volatile*/ uint16_T BP_Wf_Ldp[18] = { 0U, 256U, 512U, 768U, 1024U, 1280U,
  1536U, 1792U, 2048U, 2304U, 2560U, 2816U, 3072U, 3328U, 3584U, 3840U, 4096U,
  4352U };                            /* break points, fuel wall film, depenedent on Load predicted */

/*const volatile*/ uint8_T BP_dTaHotSta_TaOff[5] = { 64U, 72U, 80U, 88U, 96U };/* break points,Intake air temperature when engine is shut-off   */

/*const volatile*/ uint8_T BP_fCldReStaRed_TmSta[4] = { 8U, 20U, 40U, 48U };/* prelookup break points, engine temperature at start   */

/*const volatile*/ uint8_T BP_fCldReStaRed_tEngOff[4] = { 0U, 15U, 50U, 100U };/* prelookup break points, engine-off time  */

/*const volatile*/ uint8_T BP_fCldSta_TmSta[12] = { 8U, 12U, 16U, 20U, 24U, 32U, 40U,
  48U, 56U, 64U, 80U, 104U };         /* break points,engine temperature at start   */

/*const volatile*/ uint8_T BP_fFlPrs_N[8] = { 24U, 30U, 46U, 55U, 73U, 93U, 100U,
  133U };                             /* break points, Engine speed in rpm, for Factor to fuel pressure */

/*const volatile*/ uint8_T BP_fFlPrs_Ub[8] = { 90U, 100U, 110U, 120U, 130U, 140U,
  150U, 160U };                       /* break points, battery voltage, for Factor to fuel pressure */

/*const volatile*/ uint8_T BP_fHotSta_Ta[6] = { 72U, 80U, 88U, 96U, 104U, 112U };/* break points,Intake air temperature  */

/*const volatile*/ int8_T BP_fRLFS_dPamPim[11] = { 0, 10, 20, 30, 40, 50, 60, 70, 80,
  90, 100 };                          /* delta between ambient and intake manifold pressure */

/*const volatile*/ uint8_T BP_fStaAlt_fAlt[4] = { 32U, 45U, 58U, 61U };/* break points, altitude factor  */

/*const volatile*/ uint8_T BP_ftOilCyc_Tm[8] = { 8U, 24U, 32U, 48U, 64U, 80U, 104U,
  128U };                             /* break points, engine temperature    */

/*const volatile*/ uint8_T BP_ftOilCyc_Tm2[8] = { 8U, 24U, 32U, 48U, 64U, 80U, 104U,
  128U };                             /* break points, engine temperature    */

/*const volatile*/ uint8_T BP_fwCldStaNum_NumInjSta[4] = { 0U, 4U, 8U, 16U };/* prelookup break points, injection counter at start  */

/*const volatile*/ uint8_T BP_fwCldStaNum_TmSta[12] = { 8U, 12U, 16U, 20U, 24U, 28U,
  32U, 40U, 48U, 56U, 92U, 104U };    /* prelookup break points, engine temperature at start   */

/*const volatile*/ uint8_T BP_nCylFlRsmStp[16] = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U,
  8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U };/* BP number of processed fuel cut-in factors */

/*const volatile*/ uint8_T BP_tIacSolAst_Tm[6] = { 8U, 32U, 48U, 80U, 104U, 128U };/* break points, engine temperature    */

/*const volatile*/ uint8_T BP_tdInjUb_Ub[9] = { 80U, 90U, 100U, 110U, 120U, 130U,
  140U, 150U, 160U };                 /* break point, Battery voltage  */

/*const volatile*/ uint8_T CUR_InjAngAbt_N[8] = { 23U, 27U, 32U, 41U, 50U, 59U, 71U,
  45U };                              /* char. curve, angle injection abort  */

/*const volatile*/ uint16_T CUR_Wf_Ldp[18] = { 0U, 24U, 71U, 144U, 285U, 507U, 771U,
  1096U, 1383U, 1708U, 2027U, 2353U, 2679U, 2986U, 3293U, 3600U, 3894U, 4054U };/* characteristic curve: fuel wall film, depenedent on Load predicted  */

/*const volatile*/ uint8_T CUR_dTaHotSta_TaOff[5] = { 40U, 40U, 36U, 34U, 32U };/* delta Ta for determining hot start  */

/*const volatile*/ uint8_T CUR_fCldSta_TmSta[12] = { 152U, 121U, 104U, 91U, 76U, 56U,
  36U, 20U, 14U, 11U, 6U, 4U };       /* start fuel factor for cold start, dependent on engine start temp.  */

/*const volatile*/ uint8_T CUR_fFlRmsJmp_nCylFlRsm[16] = { 141U, 141U, 141U, 141U,
  134U, 134U, 134U, 134U, 132U, 132U, 132U, 132U, 128U, 128U, 128U, 128U };/* Factor pulse abrupt */

/*const volatile*/ uint8_T CUR_fFlRmsSmth_nCylFlRsm[16] = { 141U, 141U, 141U, 141U,
  138U, 138U, 138U, 138U, 137U, 137U, 137U, 137U, 136U, 136U, 136U, 136U };/* Factor pulse smooth */

/*const volatile*/ uint8_T CUR_fHotSta_Ta[6] = { 4U, 4U, 4U, 4U, 4U, 5U };/* factor hot start fueling, dependent on intake air temp.  */

/*const volatile*/ uint8_T CUR_fRLFS_dPamPim[11] = { 128U, 126U, 124U, 122U, 120U,
  119U, 117U, 115U, 114U, 112U, 111U };/* injection correction for manifold vacuum */

/*const volatile*/ uint8_T CUR_fStaAlt_fAlt[4] = { 176U, 151U, 149U, 128U };/* correction factor start fueling, dependent on altitude  */

/*const volatile*/ uint8_T CUR_tdInj2Ub_Ub[9] = { 200U, 200U, 200U, 200U, 150U, 150U,
  150U, 125U, 125U };                 /* char. curve, injection time correction dependent on batt voltage */

/*const volatile*/ int8_T CUR_tdInjUb_Ub[9] = { 56, 37, 24, 12, 0, -7, -13, -17, -23
};                                    /* char. curve, injection time correction dependent on batt voltage */

/*const volatile*/ uint8_T CV_APP = 0U;    /* Application purpose, code variants */
/*const volatile*/ uint8_T CV_CSIMM = 2U;  /* code variant for intake manifold model  */
/*const volatile*/ uint8_T CV_FIANG = 0U;  /* code variant, injection end angle */
/*const volatile*/ uint8_T CV_FL2TI = 1U;  /* code variant for fuel to injection time conversion  */
/*const volatile*/ uint8_T CV_IGA = 0U;    /* code variants, ignition angle user configured */
/*const volatile*/ uint8_T CV_LCWB = 0U;   /* code variant, non-linear close-loop adaptations  */
/*const volatile*/ uint8_T CV_LSB = 7U;    /* code variants, Lambda sensor before CAT */
/*const volatile*/ uint8_T CV_SSMAP = 3U;  /* code variant, sensor signal MAP  */
/*const volatile*/ uint8_T CV_SSWO2 = 3U;  /* code variant, sensor signal MAP  */
/*const volatile*/ uint8_T MAP_InjAngEnd_N_Ld[64] = { 81U, 83U, 87U, 92U, 99U, 107U,
  114U, 125U, 80U, 81U, 84U, 87U, 92U, 98U, 102U, 108U, 78U, 80U, 81U, 83U, 84U,
  87U, 90U, 93U, 78U, 78U, 78U, 78U, 78U, 78U, 78U, 78U, 77U, 75U, 74U, 72U, 69U,
  68U, 65U, 62U, 75U, 74U, 71U, 68U, 63U, 57U, 53U, 53U, 72U, 71U, 65U, 60U, 51U,
  44U, 48U, 53U, 71U, 68U, 60U, 53U, 41U, 42U, 48U, 53U };/* characteristic map, end of injection angle */

/*const volatile*/ int8_T MAP_InjAngEnd_N_Ld_Signed[64] = { 81, 83, 87, 92, 99, 107,
  114, 125, 80, 81, 84, 87, 92, 98, 102, 108, 78, 80, 81, 83, 84, 87, 90, 93, 78,
  78, 78, 78, 78, 78, 78, 78, 77, 75, 74, 72, 69, 68, 65, 62, 75, 74, 71, 68, 63,
  57, 53, 53, 72, 71, 65, 60, 51, 44, 48, 53, 71, 68, 60, 53, 41, 42, 48, 53 };/* characteristic map, end of injection angle, signed value, before the reference mark its positive, after the reference mark, its negative */

/*const volatile*/ uint8_T MAP_fCldReStaRed_tEngOff_TmSta[16] = { 41U, 45U, 77U, 77U,
  45U, 54U, 81U, 81U, 52U, 57U, 88U, 87U, 70U, 87U, 96U, 103U };/* char. map, factor cold re-start for reduction of start-fuel   */

/*const volatile*/ uint8_T MAP_fFlPrs_Ub_N[64] = { 136U, 133U, 135U, 131U, 129U,
  131U, 131U, 131U, 132U, 131U, 128U, 128U, 131U, 131U, 131U, 131U, 136U, 136U,
  128U, 128U, 128U, 128U, 128U, 128U, 131U, 131U, 124U, 128U, 128U, 137U, 137U,
  137U, 134U, 134U, 128U, 128U, 129U, 133U, 133U, 133U, 132U, 132U, 132U, 128U,
  128U, 128U, 128U, 128U, 128U, 128U, 128U, 129U, 129U, 129U, 129U, 129U, 128U,
  128U, 128U, 128U, 129U, 129U, 129U, 129U };/* Factor to correct fuel pressure, dependent on batt voltage and engine speed */

/*const volatile*/ uint8_T MAP_fwCldStaNum_TmSta_NumInjSta[48] = { 128U, 74U, 58U,
  45U, 128U, 76U, 54U, 39U, 128U, 76U, 50U, 38U, 128U, 63U, 45U, 35U, 128U, 54U,
  41U, 34U, 128U, 52U, 38U, 33U, 128U, 54U, 38U, 34U, 128U, 58U, 41U, 35U, 128U,
  65U, 46U, 33U, 128U, 78U, 59U, 57U, 128U, 96U, 77U, 75U, 128U, 128U, 128U,
  128U };                             /*  char. map, weighting factor of cold start fueling  */

/*const volatile*/ uint8_T VAL_AngInvClsRM = 4U;/* Angle between intake valve close to Reference Mark */
/*const volatile*/ uint8_T VAL_DualFuel = 3U;/* Dual fuel applications: 0 - gasoline; 1 - gasoline and CNG  */
/*const volatile*/ int16_T VAL_FlTrsMin = 27;/* Min threshold sum of long-/short term transient fuel */
/*const volatile*/ int16_T VAL_FlTrsSMin = 5;/* Min threshold for short term transient fuel portion */
/*const volatile*/ uint16_T VAL_FuelDensity = 47186U;/* fuel flow rate correction for n-heptane fuel */
/*const volatile*/ uint8_T VAL_InjAngEndSta = 73U;/* Injection end angle during start */
/*const volatile*/ int8_T VAL_InjAngEndSta_Signed = 0;/* Injection end angle during start */
/*const volatile*/ uint8_T VAL_IntMafHotSta = 20U;/* integrated flow of air-mass for hot start   */
/*const volatile*/ uint16_T VAL_KpBpc = 2621U;/* P-gain, boost pressure control  */
/*const volatile*/ uint16_T VAL_Qstat = 6900U;/* Injector static flow rate, in g/min */
/*const volatile*/ uint16_T VAL_Qstat2 = 17251U;/* 2nd Injector static flow rate, in g/min */
/*const volatile*/ uint16_T VAL_StoicAFR = 15053U;/* Stoic air fuel ratio for the fuel used */
/*const volatile*/ uint16_T VAL_StoicAFR2 = 35123U;/* Stoic air fuel ratio for the fuel used */
/*const volatile*/ uint8_T VAL_TmHotSta = 100U;/* engine temperature threshold for hot start   */
/*const volatile*/ uint8_T VAL_TmHotStaLm = 108U;/* engine temp. hot-start limit   */
/*const volatile*/ uint8_T VAL_TmIacSolOpen = 80U;/* engine temperature threshold to close the IAC solenoid valve   */
/*const volatile*/ uint16_T VAL_dtInjBrkMin = 500U;/* delta injector close time for hysteresis injector switching */
/*const volatile*/ uint16_T VAL_duMapDrp2CylSyn = 1638U;/* delta MAP sensor voltage drop between 2 consecutive intake strokes, to detect whether 1st cyl or 2nd cyl intake stroke, for 2-cyl system   */
/*const volatile*/ uint8_T VAL_fFlApp = 64U;/* fuel enrichment factor, user defined */
/*const volatile*/ uint16_T VAL_fQstatCr = 16384U;/* Injector static flow rate correction factor for different pressure regulators */
/*const volatile*/ uint16_T VAL_fQstatCr2 = 16384U;/* Injector static flow rate correction factor for different pressure regulators */
/*const volatile*/ uint8_T VAL_fTrsRedS = 0U;/* reduction factor short-term memory of transient fuel  */
/*const volatile*/ uint8_T VAL_fWfN = 0U;  /* wall film factor dependent on engine speed */
/*const volatile*/ uint16_T VAL_nHeptCr = 34406U;/* fuel flow rate correction for n-heptane fuel */
/*const volatile*/ uint16_T VAL_nHeptCr2 = 34406U;/* fuel flow rate correction for n-heptane fuel */
/*const volatile*/ uint16_T VAL_tInjInAdj = 200U;/* adjustment of input injection time measured */
/*const volatile*/ uint16_T VAL_tInjMin = 1000U;/* minimum possible injection time for an injector */
/*const volatile*/ uint16_T VAL_tInjMin2 = 5000U;/* minimum possible injection time for an injector */
/*const volatile*/ uint16_T VAL_tInjPreSta = 5000U;/* minimum possible injection time for an injector */
/*const volatile*/ uint16_T VAL_tInjSplitMin = 2000U;/* minimum possible injection time for an injector */
/*const volatile*/ uint16_T VAL_uPamMn = 3482U;/* maximum input voltage for pressure sensor diagnosis  */
/*const volatile*/ uint16_T VAL_vEng = 6355U;/* volume of engine displacement in cc or mL  */
/*const volatile*/ uint16_T VAL_vFuelTank = 10000U;/* volume, fuel tank in Liters */

#define STOP_SECTION_SynRom
#include "pragma.h"
#define START_SECTION_r1000msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T BARO;                         /* barometric pressure */
boolean_T B_AltAdp;                    /* condition altitude adaption valid */
boolean_T B_PamAdp;                    /* Condition ambient pressure adaptation active */
boolean_T B_PamAdpFast;                /* Condition ambient pressure adaptation at WOT enable */
uint16_T Count_CSPAM_PamAdp;           /* counter state, count times of ambient pressure adaptation */
uint32_T LPT_CSPAM_Pam_U32;            /* LowPassFilterT state, fliter Pam */
uint8_T TOfD_CSPAM_Heal;               /* Turn Off Delay for healing ambient pressure adaptation err */
uint8_T TOnD_CSPAM_PamAdpErr_U16;      /* Turn On Delay for detect ambient pressure adaptation error */
uint8_T TOnD_CSPAM_PamAdpOk_U16;       /* Turn On Delay for detect ambient pressure adaptation ok */
uint16_T dPamPbtp;                     /* delta Pressure drop across the air filter */
uint16_T fAlt;                         /* Altitude correction factor */
uint16_T fAltLd;                       /* Altitude correction factor */
uint16_T fAltRaw;                      /* Altitude correction factor */
uint8_T fAlt_b;                        /* Altitude correction factor(byte) */
uint16_T fPbtp;                        /* Factor pressure in front of throttle valve of pressure sensor */

#define STOP_SECTION_r1000msRam
#include "pragma.h"
#define START_SECTION_r1000msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T BP_TpPosAltAdpL_N[6] = { 14U, 27U, 33U, 50U, 67U, 100U };/* break points,engine speed  */

/*const volatile*/ uint16_T BP_dPamPbtp_Maf[8] = { 0U, 833U, 2500U, 4167U, 6250U,
  8333U, 10417U, 11833U };            /* break points, mass air flow  */

/*const volatile*/ uint8_T CUR_TpPosAltAdpL_N[6] = { 90U, 108U, 110U, 115U, 128U,
  128U };                             /* Low threshold throttle plate for altitude adaptation */

/*const volatile*/ uint16_T CUR_dPamPbtp_Maf[8] = { 0U, 0U, 13U, 69U, 163U, 287U,
  452U, 588U };                       /* pressure drop across the air filter */

/*const volatile*/ uint8_T VAL_NDisPamAdpSta = 3U;/* Deactivation threshold for ambient pressure adaptation during start */
/*const volatile*/ uint8_T VAL_PamMn = 101U;/* Ambient pressure limitation minimum */
/*const volatile*/ uint8_T VAL_PamMx = 101U;/* Ambient pressure limitation maximum */
/*const volatile*/ uint8_T VAL_PamSubErr = 101U;/* substitute value for ambient pressure in case of sensor failure */
/*const volatile*/ uint8_T VAL_fAltMn = 58U;/* minimum factor for diagnosis of altitude correction  */
/*const volatile*/ uint8_T VAL_fAltMx = 154U;/* maximum factor for diagnosis of altitude correction */
/*const volatile*/ uint16_T VAL_tcPamAdpFast = 3U;/* Time constant ambient pressure fast filter during engine not running */
/*const volatile*/ uint16_T VAL_tcPamAdpNm = 360U;/* Time constant ambient pressure adaptation during normal operating */
/*const volatile*/ uint8_T VAL_tdPamAdp = 10U;/* debounce time for error entry, ambient pressure adaption */
/*const volatile*/ uint8_T VAL_tdPamHeal = 20U;/* debounce time for error entry, ambient pressure adaption */
/*const volatile*/ uint8_T VAL_tdZPamAdp = 10U;/* time delay for setting cycle flag for ambient pressure adaptation */

#define STOP_SECTION_r1000msRom
#include "pragma.h"
#define START_SECTION_r100msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T Accumulator_SSTM2;
boolean_T B_CrkErr;                    /* Error condition for crank sensor */
boolean_T B_Lc;                        /* condition for Lambda closed loop control upstream catalyst */
boolean_T B_LcAdp;                     /* condition for basic mixture adaptation enabled; */
boolean_T B_LcPre;                     /* condition for Lambda closed loop control prepared */
boolean_T B_LcTm;                      /* Engine Temperature dependend condition for lambda closed loop control */
boolean_T B_LcTmSta;                   /* Lambda control enable, dependent on engine start temperatures */
boolean_T B_LcTmTa;                    /* Engine/air Temperature dependend condition for lambda closed loop control */
boolean_T B_Limp;                      /* limp home condition for crank/MAP sensor */
boolean_T B_LsbHtMx;                   /* Condition maximal power of lambda sensor heating pre cat */
boolean_T B_LsbRdyDly;                 /* delay of lambda sensor readiness, dependent on engine temperature */
boolean_T B_MapDrpErr;                 /* Error condition for MAP sensor, no dropping during crank */
boolean_T B_NoStaEol;                  /* No start because of EOL tester failed */
boolean_T B_TaStaLow;                  /* condition start for low intake air temperatures */
boolean_T B_Tester;                    /* boolean, tester present */
uint16_T BaroFil;                      /* Baro pressure filtered */
uint16_T BaroIni;                      /* Baro pressure, initial value */
uint16_T BaroRaw;                      /* Baro pressure raw value */
uint8_T Baro_b;                        /* Baro pressure, byte value */
uint8_T DutyPump;                      /* Duty cycle of PWM fuel pump */
uint8_T DutyPumpPrime;                 /* Duty cycle of fuel pump during prime */
uint8_T DutyPumpPrimeBas;              /* Duty cycle of fuel pump during prime, base value */
uint8_T DutyPumpSyn;                   /* Duty cycle of fuel pump in synch */
uint8_T DutyPumpSynBas;                /* Duty cycle of fuel pump in synch, base value */
uint8_T ECT;                           /* Engine coolant temperature */
boolean_T E_Crk;                       /* Error condition for crank sensor */
boolean_T E_Lsb2;                      /* condition for lambda sensor upstream cat ready for operation */
boolean_T E_Ta;                        /* error flag: intake air temperature */
boolean_T E_Tm;                        /* error flag:  Engine coolant temperature */
uint8_T IAT;                           /* Intake air temperature */
uint32_T INK_LCADWB_fLamAd;            /* integrator of lambda control adaptation, lower range */
int32_T INT_dLdIdlAd_U32;              /* interator for leakage air mass calculation */
boolean_T IsChaoBan;                   /* boolean,  */
boolean_T JinZhiPenYou;
uint16_T LAMBDA;                       /* commanded equivalence ratio, or Lambda */
uint32_T LPT_Baro_U32;
uint16_T LPT_CSFTM_TmEndMod;           /* LowPassFilterT state, engine temperature filted2 */
uint16_T LPT_CSFTM_TmFlt;              /* LowPassFilterT state, engine temperature filted */
uint32_T LPT_FITRS_PstSta_U32;         /* LowPassFilterT state, afterstart counter/filter  */
uint16_T LPT_SSTA1;
uint16_T LPT_SSTM_TmBfFil;
uint32_T LPT_SSTPS1_U32;
uint32_T LPT_TpsWOT_U32;
uint16_T LamDrvFil;                    /* Driver desired Lambda filtered */
uint8_T PwrLsbHtNorm;                  /* normalized heating power of lambda sensor upstream of catalyst */
uint8_T TOfD_LCADWB_Fof;               /* Turn on delay for the wideband lambda adaption   */
uint8_T TOfD_SSTA_Heal;
uint8_T TOfD_SSTM_Heal;
uint8_T TOfD_SSUB_Heal;
uint8_T TOfD_TpsBpcLo;
uint8_T TOnD_CrkErr;
uint8_T TOnD_CrkHeal;
uint8_T TOnD_CrkOk;
uint16_T TOnD_DLSV7;
uint16_T TOnD_DLSV_BLsbTheoRdyHt;
uint16_T TOnD_DLSV_B_Fof;
uint8_T TOnD_DLSV_B_LsbHtRdy;
uint8_T TOnD_DLSV_B_LsbRdyset;
uint16_T TOnD_DLSV_B_LsbScMx2;
uint16_T TOnD_DLSV_B_LsbScNotRdy;
uint16_T TOnD_DLSV_B_LsbWirBrkPoss;
uint8_T TOnD_DLSV_B_uLsbFaultRst;
uint8_T TOnD_LCADEN_B_LcAdp;           /* Turn on delay for the lambda adaption   */
uint16_T TOnD_LCADWB_B_LamAd;          /* Turn on delay for the wideband lambda adaption   */
uint16_T TOnD_LCADWB_B_StaEnd;         /* Turn on delay for the wideband lambda adaption after start  */
uint8_T TOnD_LCADWB_IsLamAdCelEn;      /* Turn on delay for the wideband lambda adaption after entering a cell  */
uint16_T TOnD_LCEN_B_LsbRdy;           /* Turn on delay, lambda control enable after lambda sensor ready, Tm dependent  */
uint16_T TOnD_LCEN_B_StaEnd1;          /* Turn on delay, lambda control enable after start end, Tm dependent  */
uint8_T TOnD_LCEN_B_StaEnd2;           /* Turn on delay, lambda control enable delay, after start, hot start */
uint8_T TOnD_LdAvgIdl;                 /* turn on delay, idle condition for load average */
uint8_T TOnD_SSTA1;
uint8_T TOnD_SSTA2;
uint8_T TOnD_SSTA3;                    /* Turn-on-Delay */
uint16_T TOnD_SSTA_StaEnd;
uint8_T TOnD_SSTM1;
uint8_T TOnD_SSTM_B_TmBak;
uint8_T TOnD_SSTM_StaEnd;
uint8_T TOnD_TpsWotAd;
uint8_T TOnD_uBaroErr;
uint8_T TOnD_uBaroHeal;
uint8_T TOnD_uBaroOk;
uint8_T TOnD_uLamErr;
uint8_T TOnD_uLamHeal;
uint8_T TOnD_uLamOk;
uint8_T TOnD_uMapErr;
uint8_T TOnD_uMapHeal;
uint8_T TOnD_uMapOk;
uint8_T TOnD_uPotErr;
uint8_T TOnD_uPotHeal;
uint8_T TOnD_uPotOk;
uint16_T TOnD_uPotStaEnd;
uint8_T TOnD_uTpsErr;
uint8_T TOnD_uTpsHeal;
uint8_T TOnD_uTpsOk;
uint8_T Ta;                            /* Intake air temperature */
uint8_T TaInvfTcmb;                    /* temperature input for curve CUR_ffTcmb_TaInv  */
uint8_T TaLin;                         /* intake air temperature, linearized */
uint8_T TaSta;                         /* air temperature at engine start  */
uint8_T Taini;                         /* intake air temperature, initial value */
uint8_T Tfuel;                         /* fuel (CNG) temperature */
uint8_T TimEndMod;                     /* Modeled intake manifold end-part temperature  */
uint16_T Timer_LsbHtMx_U8;             /* Time for maximal lambda sensor heating after start */
uint8_T TinvMod;                       /* modeled temperature at intake valve  */
uint8_T Tm;                            /* Engine temperature */
uint8_T TmBfFil;                       /* engine coolant temperature before filtered */
uint8_T TmFil;                         /* filtered engine temperature  */
int8_T TmGrdMod;                       /* delta in model-based substitute value for engine temperature signal in case of error  */
uint8_T TmLin;                         /* Engine temperature, linearized */
uint8_T TmMod;                         /* model-based substitute value for engine temperature signal in case of error  */
uint8_T TmModIv;                       /* Mod engine coolant temperature at low-pass input */
uint8_T TmRaw;                         /* Engine temperature raw value */
uint8_T TmSta;                         /* engine temperature at start */
uint8_T Tmini;                         /* Engine coolant temperature at initializations */
uint16_T TppIdlOldMn;                  /* Throttle idle position min value compared to old value */
uint16_T TpsWotOldMx;                  /* Throttle wot position max value compared to old value */
uint8_T UD_LCADWB_idxN;                /* unit delay, engine speed index */
uint8_T UD_LCADWB_idxPcmb;             /* unit delay, pressure chamber index */
uint16_T UD_OCSTA_tKoefL;              /* unit delay state,  */
uint16_T UD_OCSTA_tStaEndL;            /* unit delay state, for calculation tStaEndL */
uint16_T UD_SSTPS_TPP;
uint16_T UD_SSTPS_TpsIdl;
uint16_T UD_SSTPS_TpsIdlOld;
uint16_T UD_TpsWot;
uint16_T UD_TpsWotOld;
uint8_T dTmCr;                         /* factor to correct engine temperaturee */
uint8_T dTmTa;                         /* delta between engine temperature and intake air temperature */
uint16_T fAclTmCr;                     /* factor short/long time part of trans.control during acceleration  */
uint16_T fDclTmCr;                     /* factor short/long time part of trans.control during deceleration  */
uint8_T fTbtp;                         /* correction factor:temperature before throttle valve */
uint16_T fTcmb;                        /* correction factor: temperature in combustion chamber */
uint8_T fTcmb_b;                       /* correction factor: temperature in combustion chamber(byte) */
uint8_T fTim;                          /* correction factor:intake air temperature */
uint8_T fTmTa;                         /* weighting fator of temperature model between Tm and Ta */
uint8_T fTrsCrAcl;                     /* factor short/long time part of trans.control during acceleration  */
uint8_T fTrsCrDcl;                     /* factor short/long time part of trans.control during deceleration  */
uint16_T tAfrApp;                      /* engine after-run-time, for application purpose  */
uint16_T tAstL;                        /* time after end of start(long) */
uint16_T tHtOffAct;                    /* heater off duration for sensor heating upstream catalyst */
uint8_T tHtOffUncr;                    /* Un-corrected switch off time for lambda senor heating pre-cat */
uint16_T tKoefL;                       /* Key On Engine Off time (long) */
uint16_T uBaro;                        /* Voltage signal of BARO pressure sensor  */

#define STOP_SECTION_r100msRam
#include "pragma.h"
#define START_SECTION_r100msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T BP_LdLmp_N[6] = { 10U, 13U, 20U, 25U, 33U, 50U };/* break points, engine speed  */

/*const volatile*/ uint16_T BP_Ta_uTa[14] = { 246U, 303U, 373U, 481U, 611U, 795U,
  1081U, 1452U, 2082U, 3066U, 3477U, 3681U, 3830U, 3934U };/* voltage signal of intake air temperature sensor */

/*const volatile*/ uint8_T BP_TmGrdMod_Maf[5] = { 1U, 3U, 8U, 16U, 33U };/* break points, mass air flow */

/*const volatile*/ uint16_T BP_Tm_uTm[18] = { 92U, 131U, 154U, 165U, 221U, 261U,
  307U, 382U, 506U, 671U, 891U, 1205U, 1639U, 2903U, 3358U, 3632U, 3768U, 3937U
};                                    /* ADC-voltage for  Engine coolant temperature */

/*const volatile*/ uint8_T BP_dTmCr_dTmTa[6] = { 0U, 8U, 16U, 24U, 32U, 40U };/* break points, delta between Tm and Ta */

/*const volatile*/ uint8_T BP_fTrsAstIni_TmSta[9] = { 8U, 16U, 24U, 32U, 48U, 63U,
  80U, 96U, 104U };                   /* break points,engine start temperature   */

/*const volatile*/ uint16_T BP_fTrsSub_N[8] = { 4000U, 8000U, 10000U, 12000U, 16000U,
  20000U, 24000U, 32000U };           /* break points,engine speed, for transient fuel substitution   */

/*const volatile*/ uint16_T BP_fWf_Pam[8] = { 15360U, 17920U, 19200U, 20480U, 21760U,
  23040U, 25600U, 28160U };           /* break points, factor wall film, dependent on ambient pressure  */

/*const volatile*/ uint8_T BP_fWf_Tm[9] = { 8U, 24U, 32U, 48U, 64U, 80U, 96U, 104U,
  116U };                             /* input<Tm>, prelookup break points, factor wall film, dependent on engine temperature    */

/*const volatile*/ uint8_T BP_ffLcI_Tm[5] = { 8U, 24U, 48U, 64U, 112U };/* Break points, engine temperature for factor-factor lambda control I gain  */

/*const volatile*/ uint8_T BP_ffLcI_TmSta[4] = { 16U, 32U, 48U, 80U };/* Break points, engine temperature at start for factor-factor lambda control I gain  */

/*const volatile*/ uint8_T BP_ffTcmb_N[8] = { 13U, 17U, 24U, 39U, 55U, 73U, 85U,
  100U };                             /* break points, engine speed */

/*const volatile*/ uint8_T BP_ffTcmb_Pim[10] = { 20U, 25U, 30U, 35U, 40U, 50U, 60U,
  70U, 85U, 100U };                   /* break points, intake manifold pressure */

/*const volatile*/ uint8_T BP_ffTcmb_TaInv[14] = { 0U, 8U, 16U, 24U, 32U, 40U, 48U,
  56U, 64U, 72U, 80U, 88U, 96U, 104U };/* break points, intake air temperature */

/*const volatile*/ uint8_T BP_tLcEnDly_TmSta[5] = { 32U, 48U, 64U, 80U, 96U };/* engine temperature at start */

/*const volatile*/ uint8_T BP_tLsbRdyDly_TmSta[4] = { 8U, 24U, 49U, 96U };/*  engine temperature at start */

/*const volatile*/ uint8_T BP_tOilCyc_N[16] = { 13U, 17U, 25U, 33U, 42U, 50U, 58U,
  67U, 75U, 83U, 92U, 100U, 108U, 117U, 125U, 133U };/* break points, engine speed  */

/*const volatile*/ uint8_T BP_tOilCyc_N2[16] = { 13U, 17U, 25U, 33U, 42U, 50U, 58U,
  67U, 75U, 83U, 92U, 100U, 108U, 117U, 125U, 133U };/* break points, engine speed  */

/*const volatile*/ uint8_T CUR_Customer_Index[18] = { 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U,
  9U, 11U, 12U, 13U, 15U, 16U, 17U, 18U, 19U, 20U };/* Customer infomation */

/*const volatile*/ uint8_T CUR_Customer_Inf[18] = { 32U, 32U, 32U, 32U, 32U, 32U,
  32U, 32U, 32U, 32U, 32U, 32U, 32U, 32U, 32U, 32U, 32U, 32U };/* Customer infomation */

/*const volatile*/ uint8_T CUR_Ta_uTa[14] = { 152U, 140U, 132U, 122U, 114U, 104U,
  93U, 82U, 66U, 44U, 32U, 24U, 16U, 8U };/* Characteristic curve, intake air temperature sensor */

/*const volatile*/ int8_T CUR_TmGrdMod_Maf[5] = { 12, 22, 34, 43, 52 };/* char. curve for gradient of engine coolant temperature in substitute temperature model */

/*const volatile*/ uint8_T CUR_Tm_uTm[18] = { 192U, 176U, 168U, 165U, 153U, 146U,
  140U, 131U, 121U, 110U, 100U, 89U, 77U, 48U, 36U, 26U, 20U, 8U };/* Characteristic curve, engine coolant temperature sensor */

/*const volatile*/ uint8_T CUR_dTmCr_dTmTa[6] = { 0U, 4U, 8U, 12U, 20U, 24U };/* delta to correct engine temperature, dependent on air temperature */

/*const volatile*/ uint8_T CUR_fTrsAstIni_TmSta[9] = { 90U, 88U, 86U, 82U, 71U, 60U,
  49U, 37U, 32U };                    /* initial value of transient control after start factor */

/*const volatile*/ uint8_T CUR_fTrsCrAcl_Tm[9] = { 98U, 87U, 68U, 36U, 21U, 15U, 10U,
  7U, 6U };                           /* input<BP_fWf_Tm>,correction factor for transient fuel, accel. enrichment, dependent on temperature */

/*const volatile*/ uint8_T CUR_fTrsCrDcl_Tm[9] = { 37U, 32U, 28U, 23U, 15U, 11U, 6U,
  4U, 4U };                           /* input<BP_fWf_Tm>,correction factor for transient fuel, decel. enleanment,  dependent on temperature */

/*const volatile*/ uint16_T CUR_fWf_Pam[8] = { 32768U, 32768U, 32768U, 32768U,
  32768U, 32768U, 32768U, 32768U };   /* wall film fuel factor, depending on the ambient pressure */

/*const volatile*/ uint8_T CUR_ffLcI_Tm[5] = { 64U, 64U, 64U, 64U, 64U };/* Engine temperature dependent factor to modify I-dynamic of lambda control  */

/*const volatile*/ uint16_T CUR_ffLcI_TmSta[4] = { 26241U, 26241U, 32640U, 32640U };/* tmst dependent factor to modify I-dynamic of lambda control */

/*const volatile*/ uint8_T CUR_ffTcmb_TaInv[14] = { 118U, 121U, 123U, 126U, 128U,
  130U, 133U, 135U, 137U, 139U, 141U, 143U, 146U, 148U };/* weighting factor for fTcmb as a function of TaInv */

/*const volatile*/ uint8_T CUR_tLcEnDly_TmSta[5] = { 30U, 15U, 10U, 8U, 5U };/* Turn-on delay lambda control after start, depending on engine start temperature */

/*const volatile*/ uint8_T CUR_tLsbRdyDly_TmSta[4] = { 60U, 10U, 1U, 1U };/*  time delay control readiness after sensor readiness */

/*const volatile*/ uint8_T CV_SSBARO = 0U; /* code variant, sensor signal BARO  */
/*const volatile*/ uint8_T CW_fTcmbTaInv = 1U;/* code word, factor for combustion chamber temperature model  */
/*const volatile*/ uint8_T MAP_ffTcmb_Pim_N[80] = { 147U, 142U, 123U, 112U, 100U,
  77U, 67U, 58U, 54U, 51U, 135U, 115U, 98U, 92U, 75U, 63U, 59U, 53U, 52U, 49U,
  117U, 87U, 74U, 59U, 50U, 45U, 37U, 35U, 31U, 30U, 111U, 82U, 59U, 46U, 44U,
  37U, 35U, 32U, 26U, 26U, 87U, 72U, 50U, 42U, 36U, 30U, 26U, 23U, 17U, 10U, 77U,
  44U, 17U, 16U, 15U, 13U, 11U, 6U, 1U, 1U, 82U, 46U, 24U, 22U, 25U, 13U, 10U,
  5U, 0U, 0U, 103U, 69U, 33U, 27U, 24U, 17U, 12U, 7U, 0U, 0U };/* Weighting factor Ta/Tm for air charge temperature model, dependent on engine speed and load */

/*const volatile*/ int16_T VAL_BaroOfs = 2653;/* offset for baro pressure sensor characteristics, pressure = voltage * slope + offset  */
/*const volatile*/ uint16_T VAL_BaroSlope = 12092U;/* Slope for baro pressure sensor characteristics, pressure = voltage * slope + offset */
/*const volatile*/ uint16_T VAL_BaroSubErr = 25933U;/* offset for baro pressure sensor characteristics, pressure = voltage * slope + offset  */
/*const volatile*/ uint8_T VAL_HysLcEnTm = 3U;/*  hysteresis, lambda control enable, engine temperature dependent   */
/*const volatile*/ uint8_T VAL_LcEnTaStaHot = 80U;/* threshold intake air temp.for lambda control enable during hot start */
/*const volatile*/ uint8_T VAL_LcEnTmEmis = 48U;/*  lambda control enable, engine temperature dependent, no emission test  */
/*const volatile*/ uint8_T VAL_LcEnTmIdle = 48U;/*  lambda control enable, engine temperature dependent, idle */
/*const volatile*/ uint8_T VAL_LcEnTmPart = 48U;/*  lambda control enable, engine temperature dependent, part load */
/*const volatile*/ uint8_T VAL_LcEnTmStaHot = 100U;/* threshold engine temp.for lambda control enable during hot start */
/*const volatile*/ uint8_T VAL_LcTaStaLow = 36U;/*  air temperature threshold for closed loop lambda - control switching on */
/*const volatile*/ uint16_T VAL_TC_ffLcI = 200U;/* Time Constant, filter factor-factor lambda control I gain based on engine temperature */
/*const volatile*/ uint8_T VAL_TaErr = 48U;/* substitute value air temperature in case of fault */
/*const volatile*/ uint8_T VAL_TaMn = 3U;  /* intake-air temperature min */
/*const volatile*/ uint8_T VAL_TaMx = 135U;/* intake-air temperature max */
/*const volatile*/ uint8_T VAL_TmHtRed = 104U;/*  engine temperature for reduction lambda sensor heating */
/*const volatile*/ uint8_T VAL_TmLcAdp = 99U;/* cut-in temperature adaptive precontrol for lambda closed-loop control */
/*const volatile*/ uint8_T VAL_TmLowTa = 24U;/* substitute value engine temperature in case of fault */
/*const volatile*/ uint8_T VAL_TmMn = 8U;  /* engine temperature min */
/*const volatile*/ uint8_T VAL_TmModFnl = 100U;/* substitute value engine temperature in case of fault */
/*const volatile*/ uint8_T VAL_TmModMn = 24U;/* substitute value engine temperature min in case of fault */
/*const volatile*/ uint8_T VAL_TmModMx = 100U;/* substitute value engine temperature max in case of fault */
/*const volatile*/ uint8_T VAL_TmMx = 166U;/* engine temperature max */
/*const volatile*/ uint8_T VAL_TmStaMod = 40U;/* substitute value engine temperature in case of fault */
/*const volatile*/ uint8_T VAL_TpsLcAdp = 128U;/* threshold throttle angle for activation of the mixture adaptation */
/*const volatile*/ uint8_T VAL_UbHtNom = 135U;/* Nominal battery voltage for lambda sensor heating   */
/*const volatile*/ uint8_T VAL_UbHtOff = 140U;/* battery voltage threshold for switching off oxygen  */
/*const volatile*/ int16_T VAL_dLdIdlAd = 0;/* delta load adaptation for idle leakage air  */
/*const volatile*/ int16_T VAL_dLdIdlMn = -427;/* minimum delta load adaptation for idling air  */
/*const volatile*/ int16_T VAL_dLdIdlMx = 853;/* maximum delta load adaptation for idling air  */
/*const volatile*/ int16_T VAL_dLd_idle_unstable = 128;/* minimal charge change for triggering of post injection */
/*const volatile*/ int16_T VAL_dN_LdAvgIdl = 400;/* delta load during idle to enable load averaging */
/*const volatile*/ uint8_T VAL_dtTmMod = 100U;/* time-constant for low pass filter of  engine temperature */
/*const volatile*/ uint16_T VAL_duBaroErrHys = 410U;/* Hysterisis voltage of BARO sensor, diagnosis purpose  */
/*const volatile*/ uint16_T VAL_duTpsIdl = 410U;/* delta TPS voltage for idle position adaptations */
/*const volatile*/ uint16_T VAL_duTpsWot = 164U;/* delta TPS voltage for WOT position adaptations */
/*const volatile*/ uint8_T VAL_fwDclAst = 115U;/* weighting factor of deceleration during post-cranking */
/*const volatile*/ uint8_T VAL_kLdIdlAd = 10U;/* k coefficient for idling load adaptation integrator  */
/*const volatile*/ uint16_T VAL_tAfrApp = 5U;/* engine after-run-time, for application purpose  */
/*const volatile*/ uint16_T VAL_tBaroFil = 100U;/* time-constant for low pass filter of baro pressure */
/*const volatile*/ uint16_T VAL_tHtAstMx = 250U;/* Time for maximal lambda sensor heating after start , pre */
/*const volatile*/ uint16_T VAL_tLsbMon2LcOff = 250U;/* monitoring time closed-loop control (upstream CAT) -> sensor off  */
/*const volatile*/ uint8_T VAL_tLsbMon2LcOn = 2U;/* monitoring time -> closed-loop control on */
/*const volatile*/ uint16_T VAL_tTheoRdyHt = 800U;/* period for theoretical operation readiness of sensor with heating */
/*const volatile*/ uint16_T VAL_tTrsAst = 200U;/* time constant of transient control after start factor */
/*const volatile*/ uint8_T VAL_tcTaFil = 4U;/* time-constant for low pass filter of intake air temperature */
/*const volatile*/ uint8_T VAL_tcTcmb = 15U;/* time constant,enging tempetature for combustion chamber temperature model  */
/*const volatile*/ uint8_T VAL_tcTmTcmb = 250U;/* time constant,enging tempetature for combustion chamber temperature model  */
/*const volatile*/ uint16_T VAL_tdAstTaDg = 2400U;/* exhaust manifold warming time from start, for Ta - Diagnostic */
/*const volatile*/ uint8_T VAL_tdHtLsbRdy = 0U;/* Delay time for condition Lambda sensor ready bit */
/*const volatile*/ uint16_T VAL_tdLamAd = 100U;/* delay time for activation of the wideband lambda adaption   */
/*const volatile*/ uint16_T VAL_tdLamAdAst = 6000U;/* delay time for activation of the wideband lambda adaption after start   */
/*const volatile*/ uint8_T VAL_tdLamAdCel = 10U;/* delay time for activation of the wideband lambda adaption after entering a cell   */
/*const volatile*/ uint8_T VAL_tdLamAdFof = 50U;/* delay time for activation of the wideband lambda adaptation after fuel cut off   */
/*const volatile*/ uint8_T VAL_tdLcAdp = 20U;/* delay time for activation of the lambda adaption after lambda control active  */
/*const volatile*/ uint8_T VAL_tdLcEnStaHot = 100U;/* delay time lambda control enable during hot start */
/*const volatile*/ uint8_T VAL_tdLdAvgIdl = 50U;/* time delay for idle load averaging */
/*const volatile*/ uint16_T VAL_tdLsbOpnGrdFof = 150U;/* time after fuel cut off for commen open sensor ground  */
/*const volatile*/ uint8_T VAL_tdTaDg = 2U;/* time for diagnosis intake air temperature sensor */
/*const volatile*/ uint8_T VAL_tdTaErrIdl = 100U;/* intake-air temperature error detection/time-out */
/*const volatile*/ uint8_T VAL_tdTaHeal = 100U;/* intake-air temperature error healing delay time */
/*const volatile*/ uint8_T VAL_tdTmErr = 5U;/* engine temperature error detection/time-out */
/*const volatile*/ uint8_T VAL_tdTmHeal = 100U;/* engine temperature error healing time-out */
/*const volatile*/ uint8_T VAL_tdUbHeal = 100U;/* Battery voltage error healing delay time */
/*const volatile*/ uint16_T VAL_tuLsbLeak2ub = 500U;/* time delay for detec. current leakage to Ubattery upstream cat */
/*const volatile*/ uint16_T VAL_tuLsbMx = 250U;/* monitoring time for Usmax */
/*const volatile*/ uint16_T VAL_tuLsbW2w = 1000U;/* delay time code for detec. wire-to-wire sh. circ. of the oxyg. sens. upstr. cat   */
/*const volatile*/ uint16_T VAL_uBaroMn = 819U;/* minimum input voltage for baro pressure sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uBaroMx = 3940U;/* maximum input voltage for baro pressure sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uTpsIdl = 1229U;/* input voltage of TPS sensor at idle position  */
/*const volatile*/ uint16_T VAL_uTpsWot = 3932U;/* input voltage of TPS sensor at idle position  */

#define STOP_SECTION_r100msRom
#include "pragma.h"
#define START_SECTION_r10msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
uint16_T ALM_Lambda_FromCAN;           /* Lambda from communiction, SCI or CAN bus, etc */
uint16_T ALM_lsuDTC_FromCAN;           /* bit-Fields LSU sensor errors, from CAN bus */
uint16_T ALM_lsuHtDtcy_FromCAN;        /* LSU sensor heater duty cycle in % */
int16_T ALM_lsuO2_FromCAN;             /* O2 concentration in % */
uint16_T ALM_lsuTemp_FromCAN;          /* LSU sensor temperature from CAN bus  */
int32_T Accum_fLc_S32;                 /* data store memory, factor lambda control */
boolean_T B_Acl;                       /* Condition acceleration enrichment */
boolean_T B_AclEnr;                    /* Condition large accel. enrichment */
boolean_T B_AfrIni;                    /* flag ,  */
boolean_T B_AsrEn;                     /* condition: anti-slip-regulation enabled via user switch  */
boolean_T B_BpcEn;                     /* Boost pressure control enable */
boolean_T B_ClrAll;                    /* boolean, Clear All command from the tester */
boolean_T B_Dcl;                       /* Condition deceleration enleanment  */
boolean_T B_DclEnl;                    /* Condition large deceleration enleanment */
boolean_T B_Enrich;                    /* Indication of rich / lean mixture pre cat due to delay time control  */
boolean_T B_Fil;                       /* condition: low pass filter for transition to or from fuel cut-off active  */
boolean_T B_Fof;                       /* Condition fuel cut-off  */
boolean_T B_FofAsr;                    /* condition: anti-slip-regulation request, via fuel-cut-off  */
boolean_T B_FofInhTcat;                /* Condition: inhibition of fuel cut-off due to catalyst temperature */
boolean_T B_FofReq;                    /* Condition fuel cut-off requested */
boolean_T B_FofReqD;                   /* Condition fuel cut-off requested */
boolean_T B_FofReqDly;                 /* Condition fuel cut-off requested, delayed */
boolean_T B_FofReqGr0;                 /* Condition fuel cut-off requested at neutral gear */
boolean_T B_FuelEn;                    /* fuel supply system is enabled */
boolean_T B_IacSol;                    /* idle air control, solenoid valve open  */
boolean_T B_Idl;                       /* Condition idle from the drivers sight  */
boolean_T B_IgaAsr;                    /* condition: anti-slip-regulation active, via ignition angle retarding  */
boolean_T B_IgaMin;                    /* condition min- ignition angle */
boolean_T B_InjPreSta;                 /* boolean pre-start injection enabled */
boolean_T B_InsInj;                    /* condition for instant-injection immediately at acceleration */
boolean_T B_InsInjReset;               /* condition for instant-injection immediately reset */
boolean_T B_InsInjSet;                 /* condition for instant-injection set */
boolean_T B_Koef;                      /* condition: end of start  */
boolean_T B_LaJmp;                     /* Flag O2 sensor voltage crosses threshold detected */
boolean_T B_LamDsrDef;                 /* Condition: defined desired lambda */
boolean_T B_LamRichLim;                /* condition lambda rich limit active */
boolean_T B_LcAclDcl;                  /* disable lambda control, for transient fueling */
boolean_T B_LcBlk;                     /* Condition of start of delay time in LR for signal interference elimination */
boolean_T B_LcBlkEn;                   /* LR: Condition Start of delay time */
boolean_T B_LcDisDsr;                  /* disable lambda control, for desired situations: accel/decel, lambda !=0, etc.  */
boolean_T B_LcDisFof;                  /* lambda control disabled, during and after fuel cut off */
boolean_T B_LcStat;                    /* static condition for lambda controller */
boolean_T B_LcStatAmp;                 /* static condition for lambda controller, time and amplitude */
boolean_T B_LcStatPer;                 /* Periodic time valid, static cond. for %LR (amplitude/periodic time) = TRUE  */
boolean_T B_LdAvgIdl;                  /* Boolean, Load averaged for stable idle  */
boolean_T B_LdPrd;                     /* condition for load prediction */
boolean_T B_LdPrdAllow;                /* condition for instant-injection immediately when getting out of idle */
boolean_T B_LdPrdAst;                  /* enable condition load prediction after start */
boolean_T B_LdTpAdEn;                  /* condition enable throttle load adaptation */
boolean_T B_LdTpAdRst;                 /* condition reset throttle load adaptation */
boolean_T B_Lean;                      /* calculation sign for mixture upstream cat (Bool) */
boolean_T B_LeanOld;                   /* Indication of rich / lean mixture pre cat, 1 slot retarded */
boolean_T B_LrnOrNor_Afr;              /* flag ,  */
boolean_T B_LsbHtEn;                   /* condition for lambda sensor heater on, upstream catalyst */
boolean_T B_LsuRdy;                    /* is LSU sensor ready (heated to 780C)?  */
boolean_T B_Mil;                       /* boolean, MIL lamp on or not */
boolean_T B_N;                         /* condition engine speed detected: n > NMn  */
boolean_T B_NMn;                       /* condition engine speed too low: n < NMn */
boolean_T B_Neutral;                   /* Neutral Switch status */
boolean_T B_Nmx;                       /* condition: max engine speed  */
boolean_T B_NmxFofAll;                 /* Condition engine speed max limitation with fuel cut-off in all cylinders  */
boolean_T B_Nup0;                      /* flag ,  ) */
boolean_T B_Passwd;                    /* boolean, MIL lamp on or not */
boolean_T B_Pmp;                       /* fuel pump commanded on */
boolean_T B_PmpPrim;                   /* fuel pump prime on */
boolean_T B_Sta;                       /* condition for start  */
boolean_T B_StaEnd;                    /* condition: end of start  */
boolean_T B_StepDg_En;                 /* Condition for enable diag Stepper motor  */
boolean_T B_StepOff;                   /* flag , condition power cut-off for stepper motor */
boolean_T B_StepPosCr;                 /* flag , condition for stepper position general correction */
boolean_T B_StepPosMn;                 /* flag , condition ISA falls under the minimal position */
boolean_T B_StepPosMx;                 /* flag , condition ISA passes the maximum position */
boolean_T B_StepPrePos;                /* flag , for stepper preposition */
boolean_T B_StpDgInhLow;               /* flag , Condition stepper diag inhibition for low tension */
boolean_T B_Tilt;                      /* Vehicle tilted too big  */
boolean_T B_TpsPrd;                    /* condition throttle position prediction active */
boolean_T B_TrsAst;                    /* Enable condition transient control after start  */
boolean_T B_TrsStaEnd;                 /* condition transient after end of start */
boolean_T B_UbNpl;                     /* Error type: signal of battery voltage not plausible  */
boolean_T B_UnTp;                      /* condition: unthrottled, at which 95% load realized */
boolean_T B_Wf;                        /* Condition wall film calculation enabled */
boolean_T B_Wot;                       /* Condition for wide open throttle  */
boolean_T B_dfLcLean;                  /* lean deviation by %LR detected */
boolean_T B_dfLcRich;                  /* rich deviation by %LR detected */
boolean_T B_fLcIni;                    /* static condition for lambda controller */
boolean_T B_fLcInt;                    /* Lambda control Condition Intregation allowed */
boolean_T B_fLcJmp;                    /* Flag controller factor fr is jumping */
boolean_T B_fLcM_En;                   /* condition for enable mean value calculation   */
boolean_T B_fLcM_Jmp;                  /* Condition for mean value calculation at the lambda jump */
boolean_T B_fLcMn;                     /* lambda control sets bit when lambda controller reaches its limit FRMIN  */
boolean_T B_fLcMx;                     /* Is factor lambda control max value reached? */
boolean_T B_fLcOutRange;               /* condition for initialize frm   */
boolean_T B_fLdTpAdpMn;                /* fast  mass flow  adaption at the lower arrester */
boolean_T B_fLdTpAdpMx;                /* fast mass air flow adaption factor at the upper limit */
boolean_T EF_LCADEN_B_Brk;             /* Data store memory for Edge falling of B_brk */
boolean_T EF_OCFOFRSM1;                /* edge falling1, fuel cut off */
boolean_T EF_OCFOFRSM2;                /* edge falling2, fuel cut off */
boolean_T E_Baro;                      /* Error Baro sensor */
boolean_T E_Tilt;                      /* error condition of Tilt sensor  */
boolean_T E_Ub;                        /* error flag: power supply voltage  */
boolean_T Err_LamAn;                   /* is LSU Analog input Error?  */
uint16_T Err_LsuCan;                   /* bit-Fields LSU sensor errors */
boolean_T Err_ServoCmd;                /* servo command out of range error  */
boolean_T Err_uLam;                    /* is LSU Analog input Error?  */
boolean_T FP;                          /* fuel pump commanded on */
int16_T FlTrsSub;                      /* rel. fuel mass transition compensation substitute value */
uint16_T FuelLvlEst;                   /* Fuel level percentage, estimated based on fuel consumption */
boolean_T HTR;                         /* oxygen sensor heater on */
boolean_T Hys_OCFOFRSM_S16;            /* Hysteresis, vehicle speed threshold for cut off engine speed increase */
int8_T IGNC_Delta_IgaOut;              /* LLD delta ignition angle for idle control) */
uint32_T INK_LCAD_dfLcM1;              /* integrator of lambda control adaptation, lower range */
uint32_T INK_LCAD_dfLcM2;              /* integrator of lambda control adaptation, lower range */
int32_T INK_LCAD_dfLcM4;               /* integrator of lambda control adaptation, lower range */
int16_T INTK_OCFOFRSM_S16;             /* Integrator, Delta n overrun cut-off high with reference to n reinstatement */
int32_T INT_TQNMX_dTqNmx;              /* integrator, Torque request by engine speed limitation? */
uint32_T INT_fLdTpCr_U32;              /* integrator for fLdTpCr */
int8_T IgaAsr;                         /* Ignition angle retard for anti-slip-regulations */
int8_T IgaMin;                         /* minimum ignition angle */
int8_T IgaNmx;                         /* Ignition angle requested by engine speed limitation  */
int8_T IgaOpt;                         /* optimized igntion angle */
int8_T IgaPre;                         /* Predefined igntion angle */
int8_T IgaSta;                         /* ignition angle at start  */
int8_T IgaStaIni;                      /* ignition angle at start  */
uint16_T IntMafLcFof;                  /* Air mass based switch off Lambda Control during and after fuel cut off */
boolean_T IsFofAstEn;                  /* Is fuel cut-off enabled by after start timer? */
uint32_T LPT_LamDrv_U32;               /* driver desired lambda filter data store memory */
uint32_T LPT_LamWO2_U32;               /* driver desired lambda filter data store memory */
uint32_T LPT_TQFOFRSM_TqiFofRsmFil_U32;/* Lowpass filter, Indicated driver requested torque after cutoff/reinjection filtering function? */
uint32_T LPT_ffLcI_U16;                /* factor-factor lambda control I part filter data store memory */
uint8_T LamBas;                        /* basic lambda */
uint16_T LamDrvRaw;                    /* Driver desired Lambda raw value */
uint16_T LamDsr;                       /* Desired Lambda */
uint16_T LamDsrLsb;                    /* desired lambda referred to lambda sensor fitting location */
uint16_T LamDsrUnl;                    /* lambda desired unlimited */
uint16_T MafNrmIdc;                    /* mass air flow, from idle actuator contorl  */
uint8_T NFof;                          /* Engine speed for fuel cut-off */
uint16_T NLm;                          /* limited engine speed  */
uint16_T NPrd;                         /* Predicted engine speed for max-rpm control */
uint8_T NRsm;                          /* engine speed for fuel resuming */
uint16_T N_10ms;                       /* Engine speed in Rpm, calculated in 10ms rate */
uint8_T Nidl;                          /* idle engine speed */
uint16_T OnTime_ServoPWM_In;           /* ON time, read from Servo PWM control signal  */
uint16_T Pbtp;                         /* pressure upstrean of throttle valve */
uint8_T Pbtp_b;                        /* pressure upstrean of throttle valve (byte) */
boolean_T RSFF_BPCEN;                  /* RSFF for boost pressure control */
boolean_T RSFF_OCFOFRSM1;              /* RS Flip Flop1 */
boolean_T RSFF_OCFOFRSM2;              /* RS Flip Flop2 */
boolean_T RSFF_OCFOFRSM3;              /* RS Flip Flop3 */
boolean_T RSFF_lc_bb_stat;             /* Data store memory for RSFF in lc bb block */
uint8_T SM_fLc;                        /* Condition byte of LR-machine */
uint8_T SM_fLcM;                       /* Condition byte, Creation of fr-mean value frm_w */
uint16_T StepPosDsr;                   /* Desired position of stepper motor */
uint16_T TOfD_IdlSol_U16;              /* turn off delay  */
uint8_T TOfD_InsInj_Brk;               /* Turn off delay for the break time of the instant injection  */
uint16_T TOfD_LCEN_B_AclEnr;           /* Turn on delay, lambda sensor readiness */
uint16_T TOfD_LCEN_B_DclEnl;           /* Turn on delay, lambda sensor readiness */
uint16_T TOfD_StaSol_U16;              /* turn off delay  */
uint8_T TOnD_B_IdlGr_U8;               /* turn on delay, gear detected based on load */
uint16_T TOnD_CSLDP_AstLdP_U16;        /* Turn on delay for load prediction after start  */
uint16_T TOnD_FITRS_U16;               /* disabling time of transient control during post-cranking */
uint16_T TOnD_FOFASR_U16;              /* Turn On Delay, fuel-cut-off request for anti-slip-regulation  */
uint16_T TOnD_IGASR_U16;               /* Turn On Delay, ignition angle retard for anti-slip-regulation  */
uint8_T TOnD_InsInj_Allow;             /* Turn on delay for allowing the instant injection  */
uint16_T TOnD_LAMDRV2_U16;
uint16_T TOnD_LAMDRV_U16;
uint16_T TOnD_LSH2;
uint16_T TOnD_LdTpAdEn_U16;            /* turn on delay */
uint8_T TOnD_OCFOFRSM1_U16;            /* turn on delay 1 */
uint8_T TOnD_OCFOFRSM2_U16;            /* turn on delay 2 */
uint8_T TOnD_OCFOFRSM3_U16;            /* turn on delay 3 */
uint8_T TOnD_SSUB1_U16;
uint8_T TOnD_SSUB2_U16;
uint8_T TOnD_SSUB3_U16;
uint8_T TOnD_SSUB_MaxErr_U16;
uint16_T TPS;                          /* throttle position in percentage */
uint16_T T_lsu;                        /* LSU sensor temperature  */
uint16_T ThrottleCmdPercent;           /* Throttle command in percentage, raw value from communication  */
uint16_T ThrottleCmdPulseWidth;        /* Servo pulse width command from communication bus */
uint16_T Timer_HLS_OnTime_U16;         /* timer of the O2 sensor heating switch off */
uint8_T Timer_U8_tLcBlk;               /* data store memory for timer of tLcBlk */
uint8_T TofD_B_LdPrd;                  /* Turn off delay for load prediction  */
uint16_T Tps;                          /* throttle position with respect to lower mechanical stop */
uint16_T TpsIdlIni;                    /* Throttle position at idle, max possible, raw value  */
uint16_T TpsIdlMax;                    /* Throttle position at idle, max possible, raw value  */
uint16_T TpsPrd;                       /* predicted throttle position for fuel-calculation */
uint16_T TpsRaw;                       /* Throttle position percentage, raw value  */
uint16_T TpsWotIni;                    /* Throttle position at WOT, min possible, raw value  */
uint16_T TpsWotMin;                    /* Throttle position at WOT, min possible, raw value  */
uint8_T Tps_b;                         /* Throttle position, byte value  */
int16_T UD_CSTPP_dTps;                 /* unit delay state, gradient of actual throttle blade position */
boolean_T UD_DSOCFOFRSM;               /* unit delay */
int8_T UD_DSTQNMX_TqiNmx;              /* unit delay, Torque request by engine speed limitation? */
int8_T UD_IGFOF_IGFIL;                 /* unit delay, Indicated driver requested torque after cutoff/reinjection filtering function? */
int8_T UD_IgaPre;                      /* Predefined igntion angle */
int8_T UD_IgaSta;
uint16_T UD_LC_dfLcJmp;                /* unit delay, Lambda control factor peak to peak amplitude */
uint16_T UD_LC_fLc;                    /* unit delay, Lambda control feedback factor */
uint16_T UD_LC_fLcJmp;                 /* unit delay, Lambda control feedback factor at lambda jump */
uint16_T UD_LC_fLcM;                   /* Lambda controller output (word) */
uint16_T UD_OCSTA_tStaEnd;             /* unit delay state, for calculation tStaEnd */
uint16_T UD_TpsPrd;                    /* unit delay state, TPS predicted position */
uint16_T UD_tOilPrim;                  /* unit delay state,  */
uint16_T UD_tOilPrim2;                 /* unit delay state,  */
uint16_T UbAdcIni;                     /* battery voltage initial value  */
uint8_T UbAdc_b;                       /* battery voltage; scanned value of microprocessor ADC */
uint8_T Ub_b;                          /* Battery voltage, byte value */
uint16_T VPWR;                         /* battery voltage, conversed to ISO standard quantization  */
uint16_T dFlTrsSub;                    /* Delta of the relative fuel mass ,default value  */
int8_T dIgaAct;                        /* Efficiency ignition angle for Exhaust temperature model */
int8_T dIgaActM;                       /* Efficiency ignition angle mean value for Exhaust temperature model */
uint8_T dIgaCtrEtm;                    /* Efficiency ignition angle counter for Exhaust temperature model */
int8_T dIgaIdc;                        /* delta ignition angle for idle control) */
int8_T dIgaKnp;                        /* Delta ignition angle for knock protection  */
int8_T dIgaNmxI;                       /* delta ignition angle by integral component of engine speed limit control */
int8_T dIgaNmxP;                       /* delta ignition angle by proportional component of engine speed limit control */
int8_T dIgaOptLam;                     /* delta ignition angle dependent on lambda */
int16_T dIgaSumEtm;                    /* delta ignition angle Sum for Exhaust temperature model */
int8_T dIgaWmp;                        /* delta zwgru considering knock protection,knock control,warm-up */
int16_T dLdSenMod;                     /* delta load between sensor measured (MAP) and modelled (TPS) */
uint8_T dNFof;                         /* delta N hysteresis for fuel cut-off  */
int8_T dNFofNorm;                      /* delta N hysteresis for fuel cut-off */
uint8_T dNIdcIgaBand;                  /* delta RPM, idle engine control, ignition angle control band */
int16_T dNmxDsrAct;                    /* Difference between engine speed limit and actual engine speed */
int8_T dStepPos;                       /* delta position of stepper motor */
int16_T dTps;                          /* delta throttle position in persentage */
int16_T dTpsPrd;                       /* delta TPS corrected for segment time */
int16_T ddTps;                         /* acceleration of throttle position */
int16_T dfLcBand;                      /* deviations of LC amplitude band width.  */
int16_T dfLcJmp;                       /* delta peak value lambda control factor frsp */
int16_T dfLcJmpStat;                   /* A/F ratio controller output stroke (steady-state condition) */
int16_T dfLciBand;                     /* deviations of LC amplitude band width.  */
uint16_T fAclAst;                      /* after start factor of transient control during acceleration */
uint16_T fAirDenTp;                    /* correction factor: air density across the throttle valve */
uint16_T fDclAst;                      /* after start factor of transient control during deceleration */
uint8_T fDutyPumpUb;                   /* adjustment Factor for fuel pump duty cycle, dependent on batt voltage */
uint16_T fLamDrv;                      /* multiplicative factor, driver desired lambda  */
uint16_T fLamDrvRaw;                   /* factor driver desired lambda, raw value  */
uint16_T fLc;                          /* Lambda controller output (word) */
uint8_T fLcI;                          /* LR with integrator stop: gradient from KFRI(n,tL) or corresp. to DSLS  */
uint8_T fLcIBas;                       /* factor lambda control I gain, basic value */
uint16_T fLcIni;                       /* factor lambda control initialization value */
uint16_T fLcJmp;                       /* Lambda close loop control: Regulation factor fr before p-jump */
uint16_T fLcM;                         /* fast mean value of lambda control factor */
uint16_T fLcM_Jmp;                     /* fast mean value of lambda control factor from jamp */
uint16_T fLcM_Stat;                    /* fast mean value of lambda control factor from jamp Stat */
uint16_T fLcMn;                        /* Minimum limit. of integrator fr  */
uint16_T fLcMx;                        /* Maximum limit. of integrator fr  */
uint8_T fLcP;                          /* LR with integrator stop; P-jump from KFRP(n,tL), or DSLS enabled  */
uint8_T fLcPBas;                       /* factor lambda control P gain, basic value */
uint16_T fLcS;                         /* Lambda controller output , Switchng type O2 sensor */
uint16_T fLdTpAd;                      /* throttle position based Load adaptation  */
uint16_T fLdTpCr;                      /* correction factor for load through the throttle */
uint8_T fPbtp_b;                       /* correction factor for pressure upstream throttle (byte) */
uint8_T ffLcI;                         /* factor factor lambda control I part correction */
uint16_T ffLcIP;                       /* factor-factor lambda control I/P part correction */
uint8_T ftOilCycTm;                    /* adjustment Factor for oil pump cycle time, dependent on engine temp */
uint8_T ftOilCycTm2;                   /* adjustment Factor for oil pump cycle time, dependent on engine temp */
uint8_T ftOilOnUb;                     /* adjustment Factor for oil pump on time, dependent on batt voltage */
uint8_T ftOilOnUb2;                    /* adjustment Factor for oil pump on time, dependent on batt voltage */
boolean_T isServo;                     /* is there a servo in the system?  */
uint16_T tAst;                         /* time after end of start  */
uint8_T tCyclePump;                    /* PWM Pump Cycle time  */
uint8_T tCyclePumpPrime;               /* PWM Pump Cycle time, during prime */
uint8_T tCyclePumpSyn;                 /* PWM Fuel Pump Cycle time  */
uint8_T tEngOff_b;                     /* engine stop-time  */
uint16_T tOilCyc;                      /* Oil Pump Cycle time  */
uint16_T tOilCyc2;                     /* Oil Pump Cycle time  */
uint16_T tOilCycBas;                   /* Oil Pump Cycle time, basic value */
uint16_T tOilCycBas2;                  /* Oil Pump Cycle time, basic value */
uint16_T tOilCycCr;                    /* Oil Pump Cycle time, corrected value */
uint16_T tOilCycCr2;                   /* Oil Pump Cycle time, corrected value */
uint16_T tOilCycPrim;                  /* Oil Pump cycle time, for prime */
uint16_T tOilCycPrim2;                 /* Oil Pump cycle time, for prime */
uint16_T tOilOn;                       /* Oil Pump ON time */
uint16_T tOilOn2;                      /* Oil Pump ON time */
uint16_T tOilOnBas;                    /* Oil Pump ON time, base value */
uint16_T tOilOnBas2;                   /* Oil Pump ON time, base value */
uint16_T tOilPrim;                     /* Oil pump prime time  */
uint16_T tOilPrim2;                    /* Oil pump prime time  */
uint16_T tOnServoCtrl;                 /* ON time, Servo PWM control output, ECU drives the servo  */
uint16_T tOnServoPwmIn;                /* ON time, read from Servo PWM control signal  */
uint16_T tPerLsb;                      /* cycle period of lambda sensor upstream cat */
int8_T td;                             /* delay timer lambda controller before switching */
int8_T tdLc;                           /* LR: total value for delayed controller switch tv */
int8_T tdLcBas;                        /* time delay lambda control switching, basic value */
uint8_T tdLcSys;                       /*  Stop time for lambda close loop system  */
uint16_T tfLcNeg;                      /* time duration lambda controller negative slope */
uint16_T tfLcNegInt;                   /* counter to measure time duration lambda controller negativ slope */
uint16_T tfLcPos;                      /* time duration lambda controller positive slope */
uint16_T tfLcPosInt;                   /* counter to measure the time duration lambda controller positiv slope */
uint16_T uLam;                         /*  analog voltage for equivalent lambda, 0-5v linear  */
uint16_T uServoIn;                     /*  voltage input from the servo control command  */
uint16_T uTps;                         /* voltage of throttle position sensor  */
uint16_T uTpsEqu;                      /* Equivalent voltage of throttle position sensor  */
uint16_T uTpsIn;                       /* voltage of throttle position input  */

#define STOP_SECTION_r10msRam
#include "pragma.h"
#define START_SECTION_r10msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint16_T BP_Bpc_N[12] = { 4800U, 5600U, 6600U, 8000U, 10000U,
  12000U, 14000U, 16000U, 20000U, 24000U, 28000U, 32000U };/* input<N>, Break points, prelookup for boost pressure control */

/*const volatile*/ uint16_T BP_Bpc_Tps[16] = { 0U, 6554U, 13107U, 19661U, 26214U,
  32768U, 36045U, 39322U, 42598U, 45875U, 49152U, 52429U, 55706U, 58982U, 62259U,
  64881U };                           /* input<Tps>, break points, prelookup throttle position for boost control  */

/*const volatile*/ uint8_T BP_DutyCyclePump_N[8] = { 13U, 20U, 27U, 33U, 50U, 67U,
  83U, 100U };                        /* break points, engine speed  */

/*const volatile*/ uint8_T BP_DutyCyclePump_tInj[8] = { 0U, 16U, 31U, 47U, 63U, 78U,
  117U, 156U };                       /* break points, injectin pusle width in ms  */

/*const volatile*/ uint8_T BP_DutyPumpPrime_Tm[8] = { 8U, 24U, 32U, 48U, 64U, 80U,
  104U, 128U };                       /* break points, engine temperature    */

/*const volatile*/ uint8_T BP_IgaIdc_Ld[6] = { 24U, 33U, 40U, 47U, 54U, 60U };/* break points, load, for ignition angle at idle */

/*const volatile*/ uint8_T BP_IgaIdc_N[6] = { 20U, 22U, 23U, 25U, 27U, 30U };/* break points, engine speed, for ignition angle at idle */

/*const volatile*/ uint8_T BP_IgaSta_N[6] = { 6U, 8U, 12U, 17U, 22U, 25U };/* engine speed */

/*const volatile*/ uint8_T BP_IgaSta_TmSta[6] = { 8U, 20U, 32U, 48U, 80U, 104U };/* engine start temp. */

/*const volatile*/ uint8_T BP_Iga_Ld[11] = { 27U, 35U, 43U, 51U, 59U, 67U, 75U, 83U,
  91U, 99U, 107U };                   /* load */

/*const volatile*/ uint8_T BP_Iga_N[16] = { 20U, 28U, 33U, 41U, 50U, 59U, 67U, 75U,
  83U, 92U, 100U, 117U, 133U, 150U, 167U, 168U };/* engine speed */

/*const volatile*/ uint8_T BP_LdNtrl_Tps[8] = { 0U, 13U, 27U, 43U, 67U, 94U, 121U,
  207U };                             /* input<TpsEqu>, break points, throttle position  */

/*const volatile*/ uint16_T BP_LdTp_N[12] = { 4800U, 5600U, 6600U, 8000U, 10000U,
  12000U, 14000U, 16000U, 20000U, 24000U, 28000U, 32000U };/* break point, engine speed */

/*const volatile*/ uint16_T BP_LdTp_Tps[16] = { 0U, 2069U, 3451U, 4829U, 6899U,
  8969U, 11039U, 13107U, 17245U, 20696U, 24145U, 27593U, 31043U, 34493U, 41391U,
  52865U };                           /* input<TpsEqu>, break points, throttle position  */

/*const volatile*/ uint8_T BP_NDsrStepPos_Tm[6] = { 8U, 20U, 32U, 48U, 80U, 104U };/* break points, engine temperature, for  initial positioning of the stepper */

/*const volatile*/ int8_T BP_NRsm_Ng[5] = { -94, -62, -37, -19, 0 };/* break points,filtered engine-speed gradient */

/*const volatile*/ uint8_T BP_NRsm_Tm[5] = { 8U, 24U, 52U, 72U, 104U };/* prelookup break points, engine temperature */

/*const volatile*/ uint8_T BP_N_b1[6] = { 13U, 23U, 33U, 50U, 67U, 83U };/* break points, engine speed  */

/*const volatile*/ uint8_T BP_NstaEnd_Tm[3] = { 8U, 32U, 104U };/* break points, engine temperature   */

/*const volatile*/ uint16_T BP_StepPrePos_N[2] = { 2000U, 3200U };/* break points, engine speed, for stepper motor control */

/*const volatile*/ uint8_T BP_StepPrePos_Tm[15] = { 8U, 16U, 24U, 32U, 40U, 48U, 56U,
  64U, 72U, 80U, 88U, 104U, 111U, 120U, 132U };/* break points, engine temperature, for stepper motor control */

/*const volatile*/ uint8_T BP_TQBAS_Lam[10] = { 90U, 96U, 102U, 109U, 115U, 122U,
  128U, 134U, 141U, 147U };           /* break points, basic lambda, for basic lambda efficiency */

/*const volatile*/ uint8_T BP_TpPosUnTp_N[12] = { 13U, 17U, 24U, 33U, 39U, 46U, 55U,
  62U, 73U, 85U, 93U, 100U };         /* input<N_b>, break points, engine speed  */

/*const volatile*/ uint8_T BP_fDutyPump_Ub[8] = { 80U, 90U, 100U, 110U, 120U, 130U,
  140U, 160U };                       /* break point, Battery voltage  */

/*const volatile*/ uint8_T BP_fFlPg_ffLc[5] = { 3U, 5U, 7U, 10U, 12U };/* Break pint of FKATEI for looking up table   */

/*const volatile*/ uint8_T BP_fIgaKnp_Ld[10] = { 47U, 53U, 60U, 67U, 73U, 80U, 87U,
  93U, 100U, 107U };                  /* load */

/*const volatile*/ uint8_T BP_fIgaKnp_N[12] = { 30U, 33U, 37U, 40U, 47U, 50U, 57U,
  60U, 67U, 70U, 77U, 80U };          /* engine speed */

/*const volatile*/ uint8_T BP_fIgaKnp_fAlt[6] = { 38U, 45U, 51U, 54U, 58U, 61U };/* factor altitude */

/*const volatile*/ int16_T BP_fLdPrd_dTps[8] = { 3, 16, 33, 98, 197, 328, 655, 1638
};                                    /* input<dTps>, break points, delta TPS in 10ms  */

/*const volatile*/ uint8_T BP_fStepPos_Ta[6] = { 0U, 24U, 55U, 80U, 96U, 128U };/* break points, intake temperature , for preposition stepper motor control */

/*const volatile*/ uint8_T BP_fStepPos_fAlt[6] = { 32U, 38U, 45U, 51U, 58U, 64U };/* break points, altitude factor, for preposition stepper motor control */

/*const volatile*/ uint8_T BP_ftOilOn_Ub[8] = { 80U, 90U, 100U, 110U, 120U, 130U,
  140U, 160U };                       /* break point, Battery voltage  */

/*const volatile*/ uint8_T BP_ftOilOn_Ub2[8] = { 80U, 90U, 100U, 110U, 120U, 130U,
  140U, 160U };                       /* break point, Battery voltage  */

/*const volatile*/ uint8_T BP_fwLdpMapTps_N[8] = { 20U, 33U, 42U, 50U, 67U, 83U,
  100U, 133U };                       /* input<N_b>, break points, engine speed  */

/*const volatile*/ uint8_T BP_tCyclePump_N[8] = { 13U, 20U, 27U, 33U, 50U, 67U, 83U,
  100U };                             /* break points, engine speed  */

/*const volatile*/ uint8_T BP_tLsbHtOff_Texh[8] = { 30U, 50U, 130U, 150U, 170U, 180U,
  190U, 200U };                       /* break points, clutch torque driver desired, without anti-jerking, for the lower threshold load surge damping active */

/*const volatile*/ uint8_T BP_tOilCyc_Ld[12] = { 0U, 14U, 22U, 35U, 40U, 49U, 53U,
  63U, 80U, 108U, 120U, 133U };       /* break points, engine load  */

/*const volatile*/ uint8_T BP_tOilCyc_Ld2[12] = { 0U, 14U, 22U, 35U, 40U, 49U, 53U,
  63U, 80U, 108U, 120U, 133U };       /* break points, engine load  */

/*const volatile*/ uint16_T BP_tOilCyc_tEngOff[6] = { 0U, 60U, 120U, 600U, 1200U,
  3600U };                            /* break points, engine-off time  */

/*const volatile*/ uint16_T BP_tOilCyc_tEngOff2[6] = { 0U, 60U, 120U, 600U, 1200U,
  3600U };                            /* break points, engine-off time  */

/*const volatile*/ uint8_T CUR_DutyPumpPrime_Tm[8] = { 77U, 77U, 51U, 51U, 26U, 26U,
  26U, 26U };                         /* Duty cycle of PWM pump during primie, depending on the engine temperature */

/*const volatile*/ int8_T CUR_IgaSta_N[6] = { 0, 3, 5, 8, 11, 13 };/* ignition angle at start depend on engine speed */

/*const volatile*/ int8_T CUR_IgaSta_TmSta[6] = { 12, 12, 12, 12, 12, 12 };/* ignition angle at start depend on engine start temp. */

/*const volatile*/ uint16_T CUR_KiBpc_N[12] = { 2621U, 2097U, 1311U, 524U, 262U,
  131U, 52U, 26U, 21U, 16U, 13U, 8U };/* input <BP_Bpc_N>, characteristic curve, I-gain for boost pressure control */

/*const volatile*/ uint8_T CUR_LdLmp_N[6] = { 27U, 27U, 33U, 40U, 47U, 60U };/* limp-home relative air charge in case of sensor errors */

/*const volatile*/ uint8_T CUR_LdNtrl_Tps[8] = { 13U, 27U, 27U, 33U, 40U, 47U, 60U,
  80U };                              /* Neutral gear relative air charge, dependent on TPS  */

/*const volatile*/ uint16_T CUR_NDsrStepPos_Tm[6] = { 4600U, 4200U, 3600U, 3200U,
  3200U, 3000U };                     /* characteristic curve, Desired speed for initial positioning of the stepper */

/*const volatile*/ uint8_T CUR_NRsm_Tm[5] = { 29U, 27U, 22U, 22U, 22U };/* char. curve, fuel resuming speed, dependent on engine temp.  */

/*const volatile*/ uint8_T CUR_NstaEnd_Tm[3] = { 12U, 11U, 9U };/* Engine speed threshold for end of start  */

/*const volatile*/ uint16_T CUR_PimDsrMx_N[12] = { 38400U, 38400U, 38400U, 51200U,
  51200U, 51200U, 51200U, 51200U, 64000U, 64000U, 64000U, 64000U };/* input <BP_Bpc_N>, characteristic curve, max possible boost pressure in the manifold, dependent on RPM */

/*const volatile*/ uint8_T CUR_TppLmp_N[6] = { 15U, 18U, 23U, 38U, 58U, 90U };/* limp home throttle position  */

/*const volatile*/ uint8_T CUR_TpsUnTp_N[12] = { 205U, 205U, 205U, 205U, 205U, 205U,
  205U, 205U, 205U, 205U, 205U, 205U };/* throttle position for 95 % of load, dependent on the engine speed */

/*const volatile*/ int8_T CUR_dIgaOpt_Lam[10] = { -3, -4, -5, -5, -4, -2, 0, 3, 5, 7
};                                    /* Characteristic Curve, delta ignition angle, dependent on basic lambda */

/*const volatile*/ uint8_T CUR_dNRsm_Ng[5] = { 10U, 7U, 3U, 1U, 0U };/* delta N for fuel resuming, dependent on speed gradient  */

/*const volatile*/ uint8_T CUR_fDutyPump_Ub[8] = { 192U, 154U, 141U, 134U, 128U,
  122U, 115U, 115U };                 /* adjustment factor, on fuel pump duty cylce, depending on batt voltage */

/*const volatile*/ uint8_T CUR_fIgaKnp_fAlt[6] = { 0U, 0U, 128U, 154U, 230U, 255U };/* altitude correction factor for knock protection */

/*const volatile*/ uint16_T CUR_fLdPrd_dTps[8] = { 16384U, 16384U, 16384U, 16384U,
  16384U, 16384U, 16384U, 16384U };   /* Predicted load adjustment factor, dependent on TPS gradient  */

/*const volatile*/ uint8_T CUR_fTrsSub_N[8] = { 32U, 32U, 32U, 32U, 32U, 32U, 32U,
  32U };                              /* factor of transient control fuel substitution */

/*const volatile*/ uint8_T CUR_ffLc_fFlPg[5] = { 128U, 128U, 128U, 128U, 128U };/* Rating of factor fkatei from %TEB to optimize the regulation parameter  */

/*const volatile*/ uint8_T CUR_ftOilCyc_Tm[8] = { 128U, 128U, 128U, 128U, 128U, 128U,
  128U, 128U };                       /* char. curve, adjustment factor, oil pump cycle time, depending on engine temp */

/*const volatile*/ uint8_T CUR_ftOilCyc_Tm2[8] = { 128U, 128U, 128U, 128U, 128U,
  128U, 128U, 128U };                 /* char. curve, adjustment factor, oil pump cycle time, depending on engine temp */

/*const volatile*/ uint8_T CUR_ftOilOn_Ub[8] = { 128U, 128U, 128U, 128U, 128U, 128U,
  128U, 128U };                       /* char. curve, adjustment factor, oil pump on time, depending on batt voltage */

/*const volatile*/ uint8_T CUR_ftOilOn_Ub2[8] = { 128U, 128U, 128U, 128U, 128U, 128U,
  128U, 128U };                       /* char. curve, adjustment factor, oil pump on time, depending on batt voltage */

/*const volatile*/ uint8_T CUR_fwLdpMapTps_N[8] = { 255U, 255U, 255U, 255U, 0U, 0U,
  0U, 0U };                           /* weighting factor of TPS based vs MAP based predicted load  */

/*const volatile*/ uint8_T CUR_tCyclePump_N[8] = { 100U, 80U, 70U, 60U, 50U, 40U,
  30U, 20U };                         /* char. curve, PW pump control Period, depending on the engine speed N */

/*const volatile*/ uint16_T CUR_tIacSolAst_Tm[6] = { 5000U, 2500U, 500U, 250U, 250U,
  250U };                             /* char. curve, time to open the idle air control solenoid after engine starts */

/*const volatile*/ uint8_T CUR_tLsbHtOff_Texh[8] = { 0U, 0U, 0U, 0U, 0U, 1U, 25U,
  75U };                              /* Characteristic Curve, the lower threshold load surge damping active, dependent on clutch torque driver desired, without anti-jerking */

/*const volatile*/ uint16_T CUR_tOilCyc_tEngOff[6] = { 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U };                     /* char. curve, oil pump cycle time for prime, depending on engine off time */

/*const volatile*/ uint16_T CUR_tOilCyc_tEngOff2[6] = { 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U };                     /* char. curve, oil pump cycle time for prime, depending on engine off time */

/*const volatile*/ uint16_T CUR_tOilOn_Tm[8] = { 2050U, 2050U, 2050U, 2050U, 2050U,
  2050U, 2050U, 2050U };              /* char. curve, oil pump ON time, depending on engine temp */

/*const volatile*/ uint16_T CUR_tOilOn_Tm2[8] = { 2050U, 2050U, 2050U, 2050U, 2050U,
  2050U, 2050U, 2050U };              /* char. curve, oil pump ON time, depending on engine temp */

/*const volatile*/ uint8_T CUR_tdFof_N[8] = { 50U, 50U, 50U, 50U, 0U, 0U, 0U, 0U };/* delay time for fuel cut-off */

/*const volatile*/ uint8_T CV_BPC = 0U;    /* code variant, boost pressure control  */
/*const volatile*/ uint8_T CV_CSTPP = 1U;  /* Code variant, CSTPP module */
/*const volatile*/ uint8_T CV_DLSB = 255U; /* Application purpose, code variants */
/*const volatile*/ uint8_T CV_DSM = 1U;    /* code variant to DSM module */
/*const volatile*/ uint8_T CV_LAMDRV = 0U; /* code variant, lambda driver desired  */
/*const volatile*/ uint16_T CV_LIMP = 1U;  /* code variant limp selections */
/*const volatile*/ uint16_T CV_MIL = 1U;   /* code variant limp selections */
/*const volatile*/ uint8_T CV_N = 0U;      /* code variant, engine speed module */
/*const volatile*/ uint8_T CV_OILP = 0U;   /* code variant, oil pump control  */
/*const volatile*/ uint8_T CV_PAM = 0U;    /* code variant, ambient pressure */
/*const volatile*/ uint8_T CV_SERVO = 1U;  /* code variant, servo controls  */
/*const volatile*/ uint8_T CV_SSFLAM = 0U; /* code variant, sensor signal POT  */
/*const volatile*/ uint8_T CV_SSTPS = 0U;  /* code variant, sensor signal TPS  */
/*const volatile*/ uint8_T CV_SSUB = 0U;   /* code variant , Sensor signal battery voltage */
/*const volatile*/ uint8_T CV_SSVSP = 1U;  /* code variant to SSVSP */
/*const volatile*/ uint8_T CW_CSLDP = 1U;  /* Code variant, CSLDP module */
/*const volatile*/ uint8_T CW_CSMAFTP = 1U;/* codeword for mass-flow adaption active */
/*const volatile*/ uint8_T CW_FofRsm = 1U; /* code word to enable fuel cut off - fuel resume */
/*const volatile*/ uint16_T MAP_DcWgOl_Tps_N[192] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U, 41288U, 49152U,
  57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U,
  41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U,
  23593U, 32113U, 41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U, 41288U, 49152U,
  57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U,
  41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 9830U, 16384U,
  23593U, 32113U, 41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 9830U, 16384U, 23593U, 32113U, 41288U, 49152U, 57672U, 64881U
};                                    /* input-X <BP_Bpc_Tps>,input-Y <BP_Bpc_N>, characteristic map, open-loop waste gate duty-cycle, dependent on TPS and RPM */

/*const volatile*/ uint8_T MAP_DutyCyclePump_tInj_N[64] = { 51U, 51U, 51U, 51U, 51U,
  51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U, 51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U,
  51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U, 51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U,
  51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U, 51U, 51U, 26U, 51U, 51U, 51U, 51U, 51U,
  51U, 51U, 26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U, 26U };/* Pump duty cycle, dependent on injection time and RPM */

/*const volatile*/ int8_T MAP_IgaIdc_N_Ld[36] = { -7, -7, -7, -7, -7, -7, -7, -7, -7,
  -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
  -7, -7, -7, -7, -7, -7, -7 };       /* characteristic map,  ignition angle for idle, dependent on engine speed and load */

/*const volatile*/ int8_T MAP_IgaMn_N_Ld[176] = { -17, -4, 0, 3, 3, 3, 9, 11, 21, 27,
  30, 31, 34, 34, 34, 34, -28, -15, -14, -15, -12, -6, -1, -1, 7, 15, 18, 18, 25,
  25, 25, 25, -37, -25, -26, -25, -22, -19, -11, -8, -7, 3, 6, 6, 15, 15, 15, 15,
  -44, -33, -33, -32, -27, -26, -20, -15, -15, -10, -5, -5, 4, 4, 4, 4, -51, -39,
  -38, -38, -34, -33, -25, -20, -20, -19, -14, -11, -5, -5, -5, -5, -56, -44,
  -43, -42, -38, -36, -29, -23, -24, -23, -18, -17, -13, -13, -13, -13, -59, -48,
  -47, -46, -42, -38, -32, -25, -26, -26, -22, -20, -19, -19, -19, -19, -60, -52,
  -50, -50, -44, -39, -35, -27, -28, -27, -24, -21, -21, -21, -21, -21, -60, -58,
  -53, -53, -45, -41, -38, -30, -31, -28, -26, -23, -23, -23, -23, -23, -60, -60,
  -57, -57, -46, -45, -40, -33, -33, -29, -27, -26, -26, -26, -26, -26, -60, -60,
  -60, -60, -48, -48, -43, -35, -36, -31, -28, -28, -28, -28, -28, -28 };/* characteristic map,  minimum ignition angle, dependent on engine speed and load */

/*const volatile*/ int8_T MAP_Iga_N_Ld[176] = { 17, 21, 27, 33, 33, 40, 41, 43, 43,
  44, 47, 47, 47, 47, 47, 47, 10, 15, 22, 29, 30, 34, 38, 40, 40, 44, 45, 45, 45,
  45, 45, 45, 1, 8, 17, 21, 21, 24, 31, 35, 34, 40, 42, 42, 42, 42, 42, 42, -10,
  2, 12, 15, 15, 20, 25, 29, 29, 31, 35, 37, 37, 37, 37, 37, -19, -4, 7, 9, 12,
  16, 22, 24, 27, 26, 29, 32, 32, 32, 32, 32, -27, -8, 3, 5, 9, 14, 20, 20, 25,
  21, 25, 24, 24, 24, 24, 24, -27, -11, 0, 2, 6, 12, 17, 18, 22, 18, 22, 21, 21,
  21, 21, 21, -27, -13, -2, 0, 3, 8, 15, 15, 18, 15, 19, 19, 19, 19, 19, 19, -27,
  -15, -4, 0, 1, 7, 12, 13, 15, 13, 16, 18, 19, 19, 19, 19, -27, -17, -4, 0, 0,
  7, 11, 11, 13, 11, 15, 12, 19, 19, 19, 19, -27, -17, -4, 0, 0, 7, 11, 11, 13,
  11, 13, 11, 19, 19, 19, 19 };       /* characteristic map,  basic ignition angle, dependent on engine speed and load */

/*const volatile*/ uint16_T MAP_LamDrv_Tps_N[192] = { 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U, 4096U,
  4096U };                            /* characteristic map,  Driver desired lambda, dependent on TPS and N */

/*const volatile*/ uint16_T MAP_LdTp_Tps_N[192] = { 0U, 1538U, 1848U, 2263U, 2517U,
  2851U, 2994U, 3010U, 3044U, 3096U, 3097U, 3287U, 3297U, 3305U, 3289U, 3289U,
  0U, 1538U, 1775U, 2073U, 2517U, 2851U, 2994U, 3010U, 3044U, 3096U, 3097U,
  3287U, 3297U, 3305U, 3289U, 3289U, 0U, 1538U, 1685U, 1838U, 2429U, 2773U,
  3054U, 3034U, 3097U, 3133U, 3241U, 3287U, 3297U, 3305U, 3289U, 3289U, 0U,
  1386U, 1526U, 1716U, 2174U, 2466U, 2842U, 2987U, 3021U, 3077U, 3021U, 3028U,
  3042U, 3076U, 3067U, 3067U, 0U, 1281U, 1578U, 1783U, 2058U, 2417U, 2794U,
  3017U, 3331U, 3300U, 3239U, 3276U, 3274U, 3281U, 3298U, 3298U, 0U, 1157U,
  1554U, 1765U, 2101U, 2423U, 2767U, 3003U, 3447U, 3619U, 3644U, 3640U, 3639U,
  3673U, 3666U, 3666U, 0U, 982U, 1440U, 1607U, 1816U, 2105U, 2511U, 2722U, 3156U,
  3409U, 3446U, 3467U, 3509U, 3473U, 3484U, 3484U, 0U, 982U, 1312U, 1542U, 1634U,
  1862U, 2091U, 2307U, 2866U, 3119U, 3301U, 3362U, 3374U, 3366U, 3382U, 3382U,
  0U, 1203U, 1372U, 1561U, 1752U, 1939U, 2198U, 2414U, 2871U, 3112U, 3283U,
  3357U, 3413U, 3413U, 3413U, 3413U, 0U, 1189U, 1280U, 1513U, 1596U, 1853U,
  2007U, 2238U, 2707U, 2932U, 3134U, 3280U, 3355U, 3413U, 3413U, 3413U, 0U,
  1178U, 1248U, 1419U, 1582U, 1736U, 1898U, 2042U, 2413U, 2761U, 2953U, 3127U,
  3258U, 3353U, 3413U, 3413U, 0U, 1170U, 1226U, 1340U, 1552U, 1610U, 1827U,
  1939U, 2270U, 2609U, 2818U, 2992U, 3142U, 3258U, 3413U, 3413U };/* characteristic map,  normalized load based on TPS and engine speed (Alpha/N model) */

/*const volatile*/ uint16_T MAP_PimDsr_Tps_N[192] = { 12800U, 14080U, 15360U, 16640U,
  17920U, 19200U, 20480U, 23040U, 25600U, 28160U, 30720U, 33280U, 35840U, 40960U,
  46080U, 51200U, 12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 23040U,
  25600U, 28160U, 30720U, 33280U, 35840U, 40960U, 46080U, 51200U, 12800U, 14080U,
  15360U, 16640U, 17920U, 19200U, 20480U, 23040U, 25600U, 28160U, 30720U, 33280U,
  35840U, 40960U, 46080U, 51200U, 12800U, 14080U, 15360U, 16640U, 17920U, 19200U,
  20480U, 23040U, 25600U, 28160U, 30720U, 33280U, 35840U, 40960U, 46080U, 51200U,
  12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 23040U, 25600U, 28160U,
  30720U, 33280U, 35840U, 40960U, 46080U, 51200U, 12800U, 14080U, 15360U, 16640U,
  17920U, 19200U, 20480U, 23040U, 25600U, 28160U, 30720U, 33280U, 35840U, 40960U,
  46080U, 51200U, 12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 23040U,
  25600U, 28160U, 30720U, 33280U, 35840U, 40960U, 46080U, 51200U, 12800U, 14080U,
  15360U, 16640U, 17920U, 19200U, 20480U, 23040U, 25600U, 28160U, 30720U, 33280U,
  35840U, 40960U, 46080U, 51200U, 12800U, 14080U, 15360U, 16640U, 17920U, 19200U,
  20480U, 23040U, 25600U, 28160U, 30720U, 33280U, 35840U, 40960U, 46080U, 51200U,
  12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 23040U, 25600U, 28160U,
  30720U, 33280U, 35840U, 40960U, 46080U, 51200U, 12800U, 14080U, 15360U, 16640U,
  17920U, 19200U, 20480U, 23040U, 25600U, 28160U, 30720U, 33280U, 35840U, 40960U,
  46080U, 51200U, 12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 23040U,
  25600U, 28160U, 30720U, 33280U, 35840U, 40960U, 46080U, 51200U };/* input-X <BP_Bpc_Tps>,input-Y <BP_Bpc_N>, characteristic map, desired boost pressure in manifold, dependent on TPS and RPM */

/*const volatile*/ uint16_T MAP_StepPrePos_Tm_N[30] = { 230U, 220U, 185U, 156U, 155U,
  100U, 91U, 88U, 85U, 82U, 80U, 60U, 60U, 70U, 70U, 230U, 220U, 185U, 156U,
  155U, 100U, 91U, 88U, 85U, 82U, 80U, 65U, 65U, 70U, 70U };/* characteristic map,  Pre-positioning value of stepper motor */

/*const volatile*/ uint8_T MAP_fIgaKnp_N_Ld[120] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
  0U, 0U, 0U, 0U, 64U, 64U, 51U, 51U, 51U, 51U, 51U, 38U, 38U, 77U, 77U, 77U,
  115U, 77U, 64U, 64U, 64U, 51U, 51U, 38U, 38U, 102U, 102U, 77U, 115U, 90U, 77U,
  64U, 64U, 51U, 51U, 38U, 38U, 102U, 102U, 77U, 115U, 102U, 90U, 77U, 77U, 51U,
  51U, 38U, 38U, 102U, 102U, 77U, 115U, 115U, 102U, 90U, 90U, 64U, 64U, 51U, 51U,
  102U, 102U, 77U, 115U, 115U, 115U, 102U, 102U, 77U, 77U, 64U, 64U, 102U, 102U,
  77U, 115U, 115U, 115U, 115U, 115U, 90U, 90U, 77U, 77U, 102U, 102U, 77U, 115U,
  115U, 115U, 115U, 115U, 90U, 90U, 77U, 77U, 102U, 102U, 90U, 127U, 127U, 127U,
  127U, 127U, 115U, 115U, 102U, 102U, 102U, 102U, 90U };/* characteristic map,  correction factor of ignition angle for knock protection, dependent on engine speed and relative load */

/*const volatile*/ uint8_T MAP_fStepPos_Ta_fAlt[36] = { 166U, 166U, 166U, 166U, 166U,
  166U, 157U, 157U, 157U, 157U, 157U, 157U, 154U, 154U, 154U, 154U, 154U, 154U,
  147U, 147U, 147U, 147U, 147U, 147U, 128U, 128U, 128U, 128U, 0U, 0U, 128U, 128U,
  128U, 128U, 0U, 0U };               /* characteristic map,  Correction factor intake temperature & altitude dependant */

/*const volatile*/ uint16_T MAP_tOilCyc_Ld_N[192] = { 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U };                            /* Oil pump cycle time, dependent on Load and RPM */

/*const volatile*/ uint16_T MAP_tOilCyc_Ld_N2[192] = { 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U, 1200U,
  1200U };                            /* Oil pump cycle time, dependent on Load and RPM */

/*const volatile*/ uint8_T VAL_CylNum = 1U;/* Number of cylinders */
/*const volatile*/ int16_T VAL_DcWgIMn = -3277;/* duty cycle, waste gate, I part max permissable  */
/*const volatile*/ int16_T VAL_DcWgIMx = 3277;/* duty cycle, waste gate, I part max permissable  */
/*const volatile*/ uint16_T VAL_DcWgUsr = 19661U;/* duty cycle, waste gate, user defined, for test purpose  */
/*const volatile*/ int16_T VAL_FlAclEnRich = 172;/* fuel transient threshold, for deceleration enleanment */
/*const volatile*/ int16_T VAL_FlDclEnLean = -172;/* fuel transient threshold, for deceleration enleanment */
/*const volatile*/ uint16_T VAL_FreqWg = 100U;/* Frequency, waste gate, control signal  */
/*const volatile*/ int8_T VAL_IgaApp = 0;  /* user applications interface ignition angle adjustment */
/*const volatile*/ int8_T VAL_IgaKnp = -8; /* Ignition angle for knock protection */
/*const volatile*/ uint16_T VAL_LamDrvLow = 2048U;/* driver desired lambda lower threshold */
/*const volatile*/ uint16_T VAL_LamDrvUp = 6144U;/* driver desired lambda upper threshold */
/*const volatile*/ uint8_T VAL_LamLeanLim = 128U;/* lambda limit lean */
/*const volatile*/ uint8_T VAL_LamRichLim = 89U;/* lambda limit rich */
/*const volatile*/ uint16_T VAL_LamSenLimLow = 4090U;/* Lambda sensor lower limit for 1.0 */
/*const volatile*/ uint16_T VAL_LamSenLimUp = 4101U;/* Lambda sensor upper limit for 1.0 */
/*const volatile*/ uint16_T VAL_LamWot = 4096U;/* driver desired lambda at Wide Open Throttle */
/*const volatile*/ uint8_T VAL_LdWotErr = 93U;/* WOT TPS error detection / load-signal threshold maximal  */
/*const volatile*/ uint16_T VAL_MafLcEnFof = 405U;/*  load thresh., turn-off lambda contr. during and after decel fuel cut off  */
/*const volatile*/ uint8_T VAL_MafMxIdlNpl = 3U;/* maximum rate of air flow for plausibility test of idle TPS  */
/*const volatile*/ uint16_T VAL_MnStCLc = 22937U;/* lower limit for static condition of lambda controller */
/*const volatile*/ uint16_T VAL_MxStCLc = 42598U;/* upper limit for static condition of lambda controller */
/*const volatile*/ uint16_T VAL_NLowInsInj = 8000U;/* Upper Engine speed threshold for load prediction */
/*const volatile*/ uint16_T VAL_NUpWf = 65532U;/* Upper Engine speed threshold for Wall Film calculations */
/*const volatile*/ uint8_T VAL_NWotErr = 20U;/* Engine speed threshold for WOT error of TPS  */
/*const volatile*/ uint8_T VAL_NgFofHysDec = 0U;/* Engine speed gradient during decreasing the cut-off hysteresis */
/*const volatile*/ int16_T VAL_NgrdFofRsmDis = -2000;/*  Threshold engine speed gradient for disabling filter for transition fuel cut-off  */
/*const volatile*/ uint16_T VAL_NlowMapAvg = 28000U;/* lower Engine speed threshold for MAP averaging */
/*const volatile*/ uint16_T VAL_Nmax = 48000U;/*  max engine speed allowed  */
/*const volatile*/ uint16_T VAL_NmaxLimp = 20000U;/*  max engine speed allowed in the limp home mode */
/*const volatile*/ uint16_T VAL_Nmin = 480U;/* Min engine speed can be detected */
/*const volatile*/ uint8_T VAL_NmxCtlP = 26U;/* Characteristic Curve, P-element in Nmax control */
/*const volatile*/ uint16_T VAL_NmxVspErr = 24800U;/*  engine speed limit at fault of the vehicle speed signal  */
/*const volatile*/ uint8_T VAL_Nsta = 1U;  /* engine speed threshold for cold start  */
/*const volatile*/ uint16_T VAL_NupLdPrd = 24000U;/* Upper Engine speed threshold for load prediction */
/*const volatile*/ uint16_T VAL_NupMapAvg = 44000U;/* Upper Engine speed threshold for MAP averaging */
/*const volatile*/ uint16_T VAL_PimUnTp = 22272U;/* threshold of pressure intake manifold of unthrottled */
/*const volatile*/ uint8_T VAL_SegPerCycle = 1U;/* Number of segments per MAP sensor cycle, between 2 MAP sensor drops */
/*const volatile*/ uint8_T VAL_ServoCmdSource = 0U;/* Servo command source: 0---Servo command from analog voltage input; 1----Servo command from communication bus as TPS percentage 2----Servo command from communication bus as pulth width  */
/*const volatile*/ int16_T VAL_ServoPWM2VoltOffset = 4096;/* Servo PWM ON time to 0-5v voltage conversion Offset  */
/*const volatile*/ int16_T VAL_ServoPWM2VoltSlope = -4194;/* Servo PWM ON time to voltage conversion, slope  */
/*const volatile*/ uint8_T VAL_ServoPWMSource = 0U;/* Servo PWM source: 0---Servo PWM from hardwire; 1----Servo PWM from communication as TPS percentage 2----Servo command from communication bus as pulth width  */
/*const volatile*/ int16_T VAL_ServoVolt2PWMOffset = 200;/* Servo command voltage to servo  ON time conversion Offset  */
/*const volatile*/ int16_T VAL_ServoVolt2PWMSlope = -1000;/* Servo command voltage to servo ON time conversion, slope  */
/*const volatile*/ uint16_T VAL_StepPosMn = 2U;/* lower limitation of ISA position */
/*const volatile*/ uint16_T VAL_StepPosMx = 220U;/* upper limitation of ISA position */
/*const volatile*/ uint8_T VAL_TcatFof = 250U;/* Catalyst temp. for fuel cut off   */
/*const volatile*/ uint8_T VAL_TexLsbCsd = 255U;/* threshold for exhaust temperature for measuring CSD */
/*const volatile*/ uint8_T VAL_TexLsbDgEn = 130U;/* temp. threshold from exhaust temp. modell for diagn. sensor upstream */
/*const volatile*/ uint8_T VAL_TofD_B_LdPrd = 2U;/* Turn off delay timer, for load prediction */
/*const volatile*/ uint8_T VAL_TppAdLow = 8U;/* Lower threshold for TPS error detection  */
/*const volatile*/ uint8_T VAL_TppIdl = 4U;/* Throttle valve angle threshold for idle detection  */
/*const volatile*/ uint16_T VAL_TpsBpcLo = 32768U;/* lower threshold to enable boost pressure control  */
/*const volatile*/ int16_T VAL_TpsComm2PwmOffset = 200;/* TPS from communication converted to servo ON time, Offset  */
/*const volatile*/ int16_T VAL_TpsComm2PwmSlope = -10000;/* TPS from communication converted to servo  ON time, slope  */
/*const volatile*/ int16_T VAL_TpsComm2VoltOffset = 410;/* TPS from communication converted voltage, Offset  */
/*const volatile*/ uint16_T VAL_TpsComm2VoltSlope = 4096U;/* TPS from communication converted voltage, slope  */
/*const volatile*/ uint8_T VAL_TpsSource = 0U;/* TPS signal source: 0---TPS sensor; 1----Servo PWM   */
/*const volatile*/ uint8_T VAL_TpsWot = 251U;/* Throttle position threshold for Wide open throttle detection  */
/*const volatile*/ uint8_T VAL_TpsWotAdUp = 251U;/* Upper threshold for TPS WOT adaptation  */
/*const volatile*/ uint16_T VAL_UbAdcBak = 2048U;/* replace value for UBATT at damaged AD-channel  */
/*const volatile*/ uint8_T VAL_UbLowHiIdle = 120U;/* low battery voltage for high idle request  */
/*const volatile*/ uint8_T VAL_UbLsbDgEn = 107U;/* battery voltage threshold for release the sensor diagnosis */
/*const volatile*/ uint8_T VAL_UbMnAdc = 25U;/* min. battery voltage (ADC)  */
/*const volatile*/ uint8_T VAL_UbMnPwr = 100U;/* min. battery voltage (power supply)  */
/*const volatile*/ uint8_T VAL_UbMx = 160U;/* max. battery voltage  */
/*const volatile*/ uint8_T VAL_UbStepMn = 66U;/* Tension threshold for unactivating diag stepper motor */
/*const volatile*/ uint8_T VAL_UbStepMx = 160U;/* Voltage threshold for switching off the stepper */
/*const volatile*/ uint8_T VAL_VspFof_Tcat = 4U;/* vehicle speed  */
/*const volatile*/ uint8_T VAL_VspMnUbDg = 20U;/* Lower threshold of vehicle speed for battery voltage diagnosis  */
/*const volatile*/ uint8_T VAL_cntEolUp = 15U;/* counter, threshold for EOL tester allowed  */
/*const volatile*/ uint8_T VAL_cntrChaoBan = 15U;/* counter */
/*const volatile*/ int8_T VAL_dIgaHysFof = 3;/* ignition-hysteresis for decision cylinder fuel cut-off  */
/*const volatile*/ int8_T VAL_dIgaPreLm = 4;/* change limitation of predefine ignition angle */
/*const volatile*/ int8_T VAL_dIgaRstFof = 3;/* ignition-hysteresis for decision cylinder fuel cut-off  */
/*const volatile*/ uint16_T VAL_dLamDrvEn = 41U;/* driver desired lambda delta to enable */
/*const volatile*/ int16_T VAL_dLdInsInj = 10;/* minimal charge change for triggering of instant injection */
/*const volatile*/ int16_T VAL_dLdMn = 10; /* minimal charge change for triggering of post injection */
/*const volatile*/ int16_T VAL_dMapRaw = 1920;/* delta raw MAP change to disalble MAP average */
/*const volatile*/ uint8_T VAL_dNFofH = 13U;/* Delta N fuel cut-off high with reference to fuel resuming */
/*const volatile*/ uint8_T VAL_dNFofIdl = 9U;/* Fuel cut-off N hysteresis for resuming at idle */
/*const volatile*/ uint8_T VAL_dNFofL = 7U;/* Delta N fuel cut-off low with reference to fuel resuming */
/*const volatile*/ uint16_T VAL_dNmxFofAll = 400U;/* Exceeding of the engine speed limit leading to fuel cut-off in all cylinders  */
/*const volatile*/ uint8_T VAL_dTcatFof = 26U;/* hysteresis, Catalyst temp. for fuel cut off   */
/*const volatile*/ uint16_T VAL_dTpPosPrdL = 328U;/* lower limit for prediction of throttle position */
/*const volatile*/ uint8_T VAL_dTppAdUp = 3U;/* Limitation of upward adaptation of the TPS  */
/*const volatile*/ int16_T VAL_dTpsBpcLo = 983;/* threshold gradient throttle angle for load prediction */
/*const volatile*/ int16_T VAL_dTpsInsInj = 983;/* threshold gradient throttle angle for instant injection */
/*const volatile*/ int16_T VAL_dTpsLdPrd = 102;/* threshold gradient throttle angle for load prediction */
/*const volatile*/ int16_T VAL_dTpsMapAvg = 102;/* delta throttle angle to disalble MAP average */
/*const volatile*/ int16_T VAL_dTpsTpBlip_Min = 328;/* lower limit throttle position for blipping fuel */
/*const volatile*/ uint8_T VAL_dTpsWotAd = 3U;/* Limitation of delta WOT adaptation of the TPS  */
/*const volatile*/ int16_T VAL_dWhlSpdAsr = 1280;/* delta wheel speed threshold to activate anti-slip-regulation  */
/*const volatile*/ int16_T VAL_dfLcMn = 655;/* min. lambda deviation for steady state cond. and adaptation of transient contrl. */
/*const volatile*/ int16_T VAL_dfLcPeak = 1966;/* stroke of A/F ratio controller signal (standard value)  */
/*const volatile*/ uint8_T VAL_dfLdTpCrMn = 2U;/* Delta VAL_fLdTpCr for resetting of B_fLdTpCrMn  */
/*const volatile*/ uint8_T VAL_dfLdTpCrMx = 2U;/* Delta VAL_fLdTpCr for resetting of B_fLdTpCrMx  */
/*const volatile*/ uint16_T VAL_duMapErrHys = 41U;/* Hysteresis delta MAP voltage for diagnosis */
/*const volatile*/ uint16_T VAL_duPotErrHys = 0U;/* Hysteresis delta Pot voltage for diagnosis */
/*const volatile*/ uint16_T VAL_duTpsErrHys = 82U;/* Hysteresis delta TPS voltage for diagnosis */
/*const volatile*/ uint16_T VAL_fLamDrvBas = 12288U;/* base factor for the fuel dial  */
/*const volatile*/ uint16_T VAL_fLcMn = 24576U;/* Characteristic value, factor lambda control max value */
/*const volatile*/ uint16_T VAL_fLcMx = 40960U;/* Characteristic value, factor lambda control max value */
/*const volatile*/ uint8_T VAL_fLdTpCrMn = 48U;/* low limit for load correction of throttle valve  */
/*const volatile*/ uint8_T VAL_fLdTpCrMx = 80U;/* high limit for load correction of throttle valve  */
/*const volatile*/ uint8_T VAL_ffLcIPDgPgv = 128U;/* Factor adjustment of fri and frp during active DTEV  */
/*const volatile*/ uint8_T VAL_ffLcIPPgErr = 128U;/* Factor adjustment of fri and frp at fault open TEV pinch  */
/*const volatile*/ uint16_T VAL_kdfLcJmpStat = 6554U;/* filter constant for calc. of A/F ratio contr. stroke mean value  */
/*const volatile*/ uint8_T VAL_nInjBatch = 1U;/* Number of injectors in batch mode */
/*const volatile*/ uint8_T VAL_nInjBatch2 = 1U;/* Number of injectors in batch mode, for the 2nd batch of injectors */
/*const volatile*/ uint8_T VAL_nInjPerCyl = 1U;/* Number of injectors per cylinder, for high perfomance engine */
/*const volatile*/ uint8_T VAL_nRevPerCycle = 2U;/* Number of revolutions per engine cycle */
/*const volatile*/ uint8_T VAL_tHtOffBfDew = 12U;/* off time to reduce heater power before the dew point */
/*const volatile*/ uint16_T VAL_tInsInj_pulse = 10000U;/* instant injection pulse width */
/*const volatile*/ uint8_T VAL_tNmxPrd = 0U;/*  rpm prediction time for NMAX control  */
/*const volatile*/ uint16_T VAL_tOilCycMan = 10000U;/* Oil pump cycle time, manual setting */
/*const volatile*/ uint16_T VAL_tOilCycMan2 = 10000U;/* Oil pump cycle time, manual setting */
/*const volatile*/ uint16_T VAL_tOilCycMn = 400U;/* Oil pump cycle time, min limit */
/*const volatile*/ uint16_T VAL_tOilCycMn2 = 400U;/* Oil pump cycle time, min limit */
/*const volatile*/ uint16_T VAL_tOilCycMx = 20000U;/* Oil pump cycle time, max limit */
/*const volatile*/ uint16_T VAL_tOilCycMx2 = 20000U;/* Oil pump cycle time, max limit */
/*const volatile*/ uint16_T VAL_tOilPrimMx = 1000U;/* oil pump prime duration max */
/*const volatile*/ uint16_T VAL_tOilPrimMx2 = 1000U;/* oil pump prime duration max */
/*const volatile*/ uint16_T VAL_tOnServoCtrlMax = 30000U;/* Servo control ON time max allowed  */
/*const volatile*/ uint16_T VAL_tOnServoCtrlMin = 1000U;/* Servo control ON time min allowed  */
/*const volatile*/ uint16_T VAL_tOnServoCtrl_Err = 30000U;/* Servo control ON time error, tolerance  */
/*const volatile*/ uint16_T VAL_tServoCtrlCycle = 40000U;/* Servo control cycle time, inverse of the frequency  */
/*const volatile*/ uint16_T VAL_tTpPrd = 20000U;/* prediction time for future throttle position */
/*const volatile*/ uint16_T VAL_tTrsSub = 2U;/* Time constant transient contol substitute value  */
/*const volatile*/ uint16_T VAL_tcLamDrvFil = 150U;/* time constant for driver desired lambda filter  */
/*const volatile*/ uint16_T VAL_tcTppIdl = 30U;/* Time constant for idle-speed TPS adaptation  */
/*const volatile*/ uint16_T VAL_tcTpsWot = 10U;/* Time constant for WOT TPS adaptation  */
/*const volatile*/ uint8_T VAL_tcTqNmxInt = 2U;/* Characteristic Curve, I-gradient for Nmx control */
/*const volatile*/ uint16_T VAL_tcTqiFofFil = 15U;/* Time constant PT1 filter for transition to fuel cut-off  */
/*const volatile*/ uint16_T VAL_tcTqiRsmFil = 10U;/* Time constant of PT1 filter for transition from fuel cut-off  */
/*const volatile*/ uint16_T VAL_tcWO2Fil = 10U;/* time constant for driver desired lambda filter  */
/*const volatile*/ uint16_T VAL_tdAstLdP = 248U;/* time rl prediction suppression in post-start */
/*const volatile*/ uint8_T VAL_tdBaroErr = 20U;/* Time delay to set the BARO sensor error  */
/*const volatile*/ uint8_T VAL_tdBaroHeal = 20U;/* Time delay to heal the BARO sensor error  */
/*const volatile*/ uint8_T VAL_tdCrkErr = 50U;/* Time delay to set the MAP sensor error  */
/*const volatile*/ uint8_T VAL_tdCrkHeal = 100U;/* Time delay to heal the MAP sensor error  */
/*const volatile*/ uint8_T VAL_tdFofAsr = 20U;/*  debounce timer to activate anti-slip-regulation  */
/*const volatile*/ uint8_T VAL_tdFofAst = 20U;/* delay fuel cut off after start */
/*const volatile*/ uint8_T VAL_tdFofGr0 = 0U;/* delay fuel cut off at gear neutral */
/*const volatile*/ uint8_T VAL_tdIgaAsr = 10U;/*  debounce timer to activate anti-slip-regulation  */
/*const volatile*/ uint16_T VAL_tdLamDrvEn = 150U;/* time delay for driver desired lambda enable  */
/*const volatile*/ uint16_T VAL_tdLamWotEn = 50U;/* time delay for driver desired lambda enable  */
/*const volatile*/ uint16_T VAL_tdLdTpAdp = 0U;/* time delay for release of mass flow adaptation after B_StaEnd */
/*const volatile*/ uint8_T VAL_tdMapErr = 100U;/* Time delay to set the MAP sensor error  */
/*const volatile*/ uint8_T VAL_tdMapHeal = 100U;/* Time delay to heal the MAP sensor error  */
/*const volatile*/ uint8_T VAL_tdPotErr = 100U;/* Time delay to set the Pot error  */
/*const volatile*/ uint8_T VAL_tdPotHeal = 100U;/* Time delay to Heal the Pot error  */
/*const volatile*/ uint8_T VAL_tdTpsBpcLo = 50U;/* Turn off delay for boost pressure control based on TPS  */
/*const volatile*/ uint8_T VAL_tdTpsErr = 100U;/* Time delay to set the TPS error  */
/*const volatile*/ uint8_T VAL_tdTpsHeal = 100U;/* Time delay to Heal the TPS error  */
/*const volatile*/ uint16_T VAL_tdTrsAst = 100U;/* disabling time of transient control during post-cranking */
/*const volatile*/ uint8_T VAL_tdUbAst = 100U;/* time period for battery after start  */
/*const volatile*/ uint8_T VAL_tdUbMax = 1U;/* delay time of battery voltage max error  */
/*const volatile*/ uint8_T VAL_tdUbMin = 5U;/* delay time of battery voltage min error  */
/*const volatile*/ uint8_T VAL_tdUbRst = 10U;/* delay time of battery voltage error reset   */
/*const volatile*/ uint8_T VAL_tdWotAd = 10U;/* Time delay to start WOT TPS adaptation  */
/*const volatile*/ uint8_T VAL_td_B_IdlGr = 5U;/* time delay for gear detection based on load */
/*const volatile*/ uint8_T VAL_td_InsInj_Brk = 50U;/* time break for the next instant injection */
/*const volatile*/ uint8_T VAL_td_InsInj_allow = 25U;/* time allowed for the current instant injection */
/*const volatile*/ uint8_T VAL_td_uLamErr = 100U;/* Time delay to set the LSU analog error  */
/*const volatile*/ uint8_T VAL_td_uLamHeal = 100U;/* Time delay to Heal the LSU analog error  */
/*const volatile*/ uint16_T VAL_tdfLamEn = 15000U;/* Time delay to enable driver lambda factor  */
/*const volatile*/ uint16_T VAL_uLamMax = 3932U;/* maximum input voltage for LSU sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uLamMin = 164U;/* Mininum input voltage for LSU sensor diagnosis  */
/*const volatile*/ uint8_T VAL_uLsBcRef = 125U;/* Characteristic value, lambda sensor before catyalyst reference value */
/*const volatile*/ uint16_T VAL_uLsbFaultRst = 449U;/* threshold for reset of fault °±potential offset°± of sensor upstream cat  */
/*const volatile*/ uint16_T VAL_uLsbLowLm = 49U;/* lower limit wire-to-wire detection and defective O2-sensor limited voltage range  */
/*const volatile*/ uint16_T VAL_uLsbMn = 33U;/* threshold for short circuit of sensor to ground   */
/*const volatile*/ uint16_T VAL_uLsbMx = 1229U;/* threshold for short circuit of sensor  */
/*const volatile*/ uint16_T VAL_uLsbOpnGnd = 165U;/* sensor voltage threshold for commen open sensor ground */
/*const volatile*/ uint16_T VAL_uLsbRefLean = 329U;/* threshold for operation readiness of sensor at lean mixture (upstream CAT) */
/*const volatile*/ uint16_T VAL_uLsbRefRich = 489U;/* threshold for operation readiness of sensor at rich mixture (upstream CAT) */
/*const volatile*/ uint16_T VAL_uLsbUpLm = 329U;/*  upper limit wire-to-wire detection and defective O2-sensor limited voltage range  */
/*const volatile*/ uint16_T VAL_uMapMn = 164U;/* Mininum input voltage for MAP sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uMapMx = 4014U;/* maximum input voltage for MAP sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uPot2Fct = 6554U;/* convert Pot voltage to percentage  */
/*const volatile*/ uint16_T VAL_uPotMn = 0U;/* Mininum input voltage for Pot sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uPotMx = 4096U;/* maximum input voltage for Pot sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uPotPreInj = 819U;/* Lower Pot voltage threshold for pre-start injection enable   */
/*const volatile*/ uint16_T VAL_uPotSw = 819U;/* switch to enrichment table when the Pot voltage is high  */
/*const volatile*/ uint16_T VAL_uTpsMn = 164U;/* Mininum input voltage for TPS sensor diagnosis  */
/*const volatile*/ uint16_T VAL_uTpsMx = 3441U;/* maximum input voltage for TPS sensor diagnosis  */

#define STOP_SECTION_r10msRom
#include "pragma.h"
#define START_SECTION_r1msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
boolean_T B_Koef_too_long;             /* condition key on engine off too long time */
boolean_T B_PWPump;                    /* condition Pulse Width Pump ON */
boolean_T B_PWPumpExist;               /* condition Pulse Width Pump existing */
uint16_T Ctr_PWPumpPrime_10ms;         /* Counter Pulse Width Pump prime time in 10ms rate  */
uint16_T MapRaw;                       /* Intake manifold pressure, raw value */
uint16_T Map_1ms;                      /* Intake manifold pressure measured with pressure sensor at manifold */
boolean_T UD_B_PWPumpPrimeEn;          /* condition PW Pump Prime ON, uint delay */

#define STOP_SECTION_r1msRam
#include "pragma.h"
#define START_SECTION_r1msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T CV_PWPUMP = 0U; /* code variant, Pusle Width pump control  */
/*const volatile*/ uint16_T VAL_LamBak = 4096U;/* backup lambda for wideband O2 sensor is not ready or at fault  */
/*const volatile*/ uint16_T VAL_PmapGrd = 12092U;/* gradient for manifold pressure sensor characteristics, pressure = voltage * gradient + offset */
/*const volatile*/ int16_T VAL_PmapOfs = 2653;/* offset for manifold pressure sensor characteristics  */
/*const volatile*/ uint8_T VAL_dVspFof = 4U;/* delta vehicle speed for cut off speed increase */
/*const volatile*/ uint16_T VAL_kMapFil = 32768U;/* filter coefficient, MAP signal */
/*const volatile*/ uint16_T VAL_rVd2VinvCls = 34377U;/* ratio, volume of total displacement to the volume of chamber at intake valve close */
/*const volatile*/ uint8_T VAL_tCyclePumpPrime = 64U;/* PW pump cycle time during prime */
/*const volatile*/ uint16_T VAL_tPumpPrimeMx = 6000U;/* Timer, PWM pump prime max time */
/*const volatile*/ uint16_T VAL_uLamOfs = 2867U;/* offset for wideband O2 linearized output  */
/*const volatile*/ uint16_T VAL_uLamSlope = 5120U;/* gradient for wideband O2 linearized output */

#define STOP_SECTION_r1msRom
#include "pragma.h"
#define START_SECTION_r200msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
boolean_T B_EstmEn;                    /* Flag start-value tabgmst, tkatmst calculated */
boolean_T B_LcAdRstRdy;                /* condition reset readiness of mixture adaptation; */
boolean_T B_LcW_SS;                    /* Steady state for wideband lambda control; */
boolean_T B_LsbDew;                    /* condition temperature upstream catalyst exceeds dew-point */
boolean_T B_NoOfsLcAdSyn;              /*   condition additive correction of the mixture adaptation switched off ; */
boolean_T B_NofLamAd;                  /* condition no lambda adaptation active; */
boolean_T B_NofLcAd;                   /* condition no fra adaptation active; */
boolean_T B_OfsLcAdSyn;                /* condition adaptation area rkaz active */
boolean_T B_fLamAd;                    /* condition wideband lambda adaptation active; */
boolean_T B_fLamEn;                    /* enable wideband lambda control; */
boolean_T B_fLcAdLo;                   /* condition enable adaptation of frau */
boolean_T B_fLcAdUp;                   /* condition for enabling adaption of frao */
uint32_T INT_IntMafEstm;               /* Integrator, Integrated Heat Before Catalyst */
uint16_T IntMafEstm;                   /* Integrated mass air(word) */
uint8_T IntMafEstm_b;                  /* Integrated mass air */
boolean_T IsLamAdCelEn;                /* Is lambda adaptation in the operating cell enabled?; */
boolean_T IsOfsLcAdSynOut;             /* Is offset lambda control adaptation out of range? - additive fuel per injection; */
boolean_T IsfLamAdOut;                 /* Is lambda adaptation out of range?; */
boolean_T IsfLcAdLoOut;                /* Is lambda control factor out of range ? -lower adaptation range */
boolean_T IsfLcAdUpOut;                /* Is lambda control factor out of range ? -upper adaptation range */
uint32_T LPT_TexStat1_U32;             /* LowPassT Memory, Temperature */
uint32_T LPT_TexoInMainCat3_U32;       /* LowPassT Memory, Temperature */
uint32_T LPT_TexoInMainCat_U32;        /* LowPassT Memory, Temperature */
uint8_T NdsrIdcTm;                     /* desired engine speed dependent on engine temperature and altitude  */
uint16_T TOnD_TexLsbDew_U16;           /* Turn-On Delay, Exhaust temperature reaching Dew-Point-End before Cat */
uint8_T TaTam;                         /* intake air or ambient temperature */
uint16_T TcatInPre;                    /* exhaust gas temperature in pre-catalyst (modelled) */
uint8_T TcatInPre_b;                   /* exhaust gas temperature in pre-catalyst (modelled) */
uint16_T TcatMain;                     /* main catalyst temperature modelled  */
uint8_T TcatMain_UD;                   /* Exhaust gas temperature downstream main catalyst, modelled */
uint8_T TcatMain_b;                    /* Main catalyst temperature (model) */
uint8_T TcatSta;                       /* catalyst temperature modelled start value = f(last value, soak time) */
uint8_T TexBas;                        /* exhaust gas temperature, basic value */
uint16_T TexBfCat;                     /* Exhaust gas temperature before the catalyst from model */
uint8_T TexBfCatSta;                   /* Exhaust gas temperature at engine start */
uint8_T TexBfCat_UD;                   /* Exhaust gas temperature downstream main catalyst, modelled */
uint8_T TexBfCat_b;                    /* exhaust gas temperature upstream cat from exhaust temperature model */
uint8_T TexStat;                       /* exhaust gas temperature-modelled steady-state */
int16_T TexoInMainCat;                 /* exothermic temperature increase in the main catalyst */
int16_T TexoInPreCat;                  /* exothermic temperature increase in the pre-catalyst */
uint8_T UD_TaTam;                      /* intake air or ambient temperature */
uint16_T UD_tSok;                      /* Unit-Delay, Temperature exhaust gas after the exhaust vavle */
uint16_T UD_tSok1;                     /* Unit-Delay, Temperature exhaust gas after the exhaust vavle */
int8_T dIgaKnpTmTa;                    /* Delta ignition angle for knock protection depending on Tm  and Ta  */
int8_T dIgaMnTmTa;                     /* delta min-ignition angle knock limit shift */
int16_T dLamAct;                       /* delta of actual lambda vs desired lambda */
int16_T dfLcM;                         /* deviation of fast lambda controller mean value from 1.0 */
uint16_T fAstFil;                      /* afterstart fuel filter factor */
uint8_T fIgaAlt;                       /* altitude correction factor for knock protection */
uint16_T fLamAd;                       /* multipl. mixture adaptation factor via wide band lambda meter  */
uint16_T fLamAdIn;                     /* Input of the table, mixture adaptation factor via wide band lambda meter  */
uint16_T fLamAdOut;                    /* output of the table, mixture adaptation factor via wide band lambda meter  */
uint16_T fLamAdOut_an;                 /* output of the table, mixture adaptation factor via wide band lambda meter  */
uint16_T fVeCr;                        /* Volumetric efficiency correction based on lambda adaptation */
uint8_T idxLd;                         /* index of Load, manifold pressure break point */
uint8_T idxN;                          /* index of N, engine speed break point */
boolean_T isAutoTune;                  /* condition wideband lambda adaptation active; */
uint8_T nDewNotLsbOld;                 /* number of restart without Dew-Point-End Before Cat */
uint8_T nDewNotLsbOut;                 /* Counter, number of restart without Dew-Point-End Before Cat */
uint8_T tdFof;                         /* delay fuel cut-off */

#define STOP_SECTION_r200msRam
#include "pragma.h"
#define START_SECTION_r200msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint16_T BP_ESTM_Maf[7] = { 417U, 1667U, 3333U, 5000U, 6667U,
  10000U, 13333U };                   /* Break points, ESTM, air mass flow filtered */

/*const volatile*/ uint8_T BP_TexEstm_Ld_b[8] = { 20U, 29U, 40U, 55U, 68U, 80U, 93U,
  113U };                             /* break points, Fuel total, for Temperature exhaust gas stationary value */

/*const volatile*/ uint8_T BP_TexEstm_N_b[8] = { 13U, 20U, 33U, 50U, 67U, 83U, 92U,
  100U };                             /* Break points, Rpm, for Temperature exhaust gas stationary value */

/*const volatile*/ uint8_T BP_dIgaIdc_Tm[10] = { 8U, 12U, 20U, 24U, 32U, 40U, 48U,
  68U, 88U, 104U };                   /* break points, engine temperature, for idle ignition angle */

/*const volatile*/ uint8_T BP_dIgaIdc_Ub[10] = { 80U, 90U, 100U, 105U, 110U, 115U,
  120U, 130U, 140U, 150U };           /* break points, battery voltage, for idle ignition angle */

/*const volatile*/ uint8_T BP_dIgaKnp_Ta[6] = { 64U, 72U, 80U, 88U, 96U, 104U };/* intake air temperature */

/*const volatile*/ uint8_T BP_dIgaKnp_Tm[6] = { 80U, 100U, 104U, 108U, 111U, 123U };/* engine coolant temperature */

/*const volatile*/ uint8_T BP_dIgaMn_Ta[6] = { 64U, 72U, 80U, 88U, 96U, 104U };/* intake air temperature */

/*const volatile*/ uint8_T BP_dIgaMn_Tm[6] = { 80U, 100U, 104U, 108U, 111U, 123U };/* engine coolant temperature */

/*const volatile*/ uint8_T BP_dTexEstm_Lam[6] = { 45U, 51U, 58U, 61U, 64U, 74U };/* Break points, lambda desired limited, for map exhaust gas temperature correction = f(lambda) */

/*const volatile*/ uint8_T BP_dTexEstm_TaTam[3] = { 7U, 24U, 48U };/* Break points, intake air or ambient temperature, for temperature correction of the exhaust model temperature */

/*const volatile*/ uint8_T BP_fAstAlt_fAlt[4] = { 32U, 48U, 58U, 61U };/* Correction factor altitude */

/*const volatile*/ uint8_T BP_fAstHot_Ta[6] = { 72U, 80U, 88U, 96U, 104U, 112U };/* input<Ta>, break points,Intake air temperature   */

/*const volatile*/ uint8_T BP_fAst_TmSta[12] = { 8U, 12U, 16U, 20U, 24U, 32U, 44U,
  48U, 56U, 64U, 80U, 104U };         /* input<TmSta>, break points,engine temperature at start  */

/*const volatile*/ int8_T BP_fTexStat_dIga[6] = { 0, 7, 13, 27, 40, 67 };/* Break points, ignition efficiency, for exhaust gas temperature correktion = f(ignition-variation) */

/*const volatile*/ uint8_T BP_fWmp_Tm[12] = { 8U, 12U, 16U, 20U, 24U, 32U, 42U, 48U,
  56U, 80U, 104U, 120U };             /* prelookup break points, engine temperature   */

/*const volatile*/ uint8_T BP_fwReSta_TmSta[6] = { 8U, 16U, 26U, 32U, 48U, 88U };/* prelookup break points, engine temperature at start   */

/*const volatile*/ uint8_T BP_fwReSta_tEngOff[6] = { 1U, 50U, 100U, 150U, 200U, 250U
};                                    /* prelookup break points, engine off time  */

/*const volatile*/ uint8_T BP_fwWmp_Ld[6] = { 13U, 27U, 53U, 80U, 93U, 133U };/* relative air charge  */

/*const volatile*/ uint8_T BP_fwWmp_N[6] = { 17U, 33U, 50U, 67U, 83U, 100U };/* Engine speed in Rpm */

/*const volatile*/ int16_T BP_kLamAd_dLam[6] = { 164, 655, 1638, 3277, 16384, 32767
};                                    /* Break points, delta lambda desired vs actual lambda from wideband */

/*const volatile*/ uint8_T BP_tDlyLsbDew_TmSta[7] = { 7U, 32U, 48U, 72U, 100U, 104U,
  112U };                             /* break points, engine start temperature, for heat threshold dew-point-end */

/*const volatile*/ uint16_T BP_tSokEstm[6] = { 10U, 270U, 600U, 1000U, 1400U, 3500U
};                                    /* Break points, soak time for ETM model */

/*const volatile*/ uint8_T BP_tdFof_N[8] = { 15U, 25U, 27U, 45U, 50U, 67U, 83U, 100U
};                                    /* prelookup break points, engine temperature at start */

/*const volatile*/ int8_T CUR_TexinMainCat_Maf[7] = { 17, 17, 17, 19, 18, 17, 16 };/* Temperature increase of the exotherme in the main catalyst */

/*const volatile*/ uint8_T CUR_TexinMainEnri_Lam[6] = { 52U, 58U, 78U, 86U, 128U,
  128U };                             /* Temperature of the exotherme decrease during enrichment */

/*const volatile*/ uint8_T CUR_TexinMainIga_EfcIga[6] = { 109U, 111U, 114U, 119U,
  124U, 128U };                       /* Temperature of the exotherme decrease in cat during ignition retard */

/*const volatile*/ int8_T CUR_TexoMainCat_Maf[7] = { 3, 5, 8, 8, 8, 8, 8 };/* Temperature increase of the exotherme in the main catalyst */

/*const volatile*/ uint8_T CUR_TexoMainEnri_Lam[6] = { 26U, 32U, 38U, 45U, 128U,
  128U };                             /* Temperature of the exotherme decrease during enrichment */

/*const volatile*/ uint8_T CUR_TexoMainIga_EfcIga[6] = { 119U, 119U, 120U, 122U,
  125U, 128U };                       /* Temperature of the exotherme decrease in main-cat during ignition retard */

/*const volatile*/ int8_T CUR_dIgaIdc_Tm[10] = { 40, 33, 33, 33, 33, 33, 33, 13, 0,
  0 };                                /* Characteristic Curve, delta ignition angle of engine temperature effect */

/*const volatile*/ int8_T CUR_dIgaIdc_Ub[10] = { 40, 33, 33, 33, 33, 33, 33, 13, 0,
  0 };                                /* Characteristic Curve, delta ignition angle of battery voltage effect */

/*const volatile*/ int8_T CUR_dTexEstm_Tam[3] = { 12, 6, 0 };/* temperature correction of the exhaust model temperature */

/*const volatile*/ uint8_T CUR_fAstAlt_fAlt[4] = { 152U, 150U, 147U, 128U };/* altitude correction of afterstart enrichment */

/*const volatile*/ uint8_T CUR_fAstHot_Ta[6] = { 44U, 44U, 53U, 62U, 71U, 77U };/* input<BP_fAstHot_Ta>, hot after start factor */

/*const volatile*/ uint8_T CUR_fAst_TmSta[12] = { 96U, 88U, 82U, 70U, 50U, 49U, 39U,
  36U, 29U, 28U, 13U, 12U };          /* input<BP_fAst_TmSta>, after start enrichment factor */

/*const volatile*/ uint16_T CUR_fDecAstCld1_TmSta[12] = { 655U, 983U, 1311U, 1638U,
  2048U, 2294U, 2621U, 2949U, 3277U, 3604U, 3932U, 4588U };/* input<BP_fAst_TmSta>, factor for ign. sync. decreasing of afterstart enrichment at cold start range 1  */

/*const volatile*/ uint8_T CUR_fDecAstH1_Ta[6] = { 8U, 8U, 7U, 5U, 5U, 4U };/* input<BP_fAstHot_Ta>, factor for ign. sync. decreasing of afterstart enrichment at hot start range 1  */

/*const volatile*/ uint8_T CUR_fTcatSok_tOff[6] = { 252U, 141U, 77U, 41U, 25U, 0U };/* factor reduction of catalyst temperature dependent on engine off timer */

/*const volatile*/ uint8_T CUR_fTexSok_tOff[6] = { 238U, 210U, 179U, 141U, 102U, 0U
};                                    /* factor reduction of exhaust temperature dependent on engine off timer */

/*const volatile*/ uint8_T CUR_fTexStat_EfcIga[6] = { 0U, 0U, 0U, 0U, 0U, 0U };/* characteristic curve,  exhaust gas temperature correction = f(lambda) */

/*const volatile*/ uint8_T CUR_fTexStat_Lam[6] = { 64U, 64U, 64U, 64U, 64U, 64U };/* characteristic curve,  exhaust gas temperature correction = f(lambda) */

/*const volatile*/ uint8_T CUR_fWmp_Tm[12] = { 106U, 106U, 124U, 52U, 50U, 24U, 23U,
  12U, 11U, 9U, 0U, 0U };             /* Char. Curve, warm-up factor, dependent on engine temp. */

/*const volatile*/ uint16_T CUR_kLamAd_dLam[6] = { 2U, 33U, 82U, 164U, 819U, 1638U };/* coefficiency  for integrator of mixture adaption wideband */

/*const volatile*/ uint8_T CUR_tDlyLsbDew_TmSta[7] = { 255U, 255U, 100U, 60U, 30U,
  30U, 30U };                         /* characteristic map,  for heat-quantity threshold dew-point end upstream bank1 */

/*const volatile*/ uint8_T CUR_tcTcatMain_Maf[7] = { 142U, 80U, 34U, 24U, 19U, 16U,
  17U };                              /* time constant for main catalyst temperature model */

/*const volatile*/ uint8_T CUR_tcTcatPre_Maf[7] = { 183U, 81U, 33U, 17U, 13U, 12U,
  11U };                              /* time constant for pre-catalyst temperature model */

/*const volatile*/ uint8_T CUR_tcTex_Maf[7] = { 73U, 27U, 16U, 13U, 10U, 9U, 7U };/* time constant for exhaust gas temperature model */

/*const volatile*/ uint8_T CV_FLAST = 0U;  /* code variant to FLAST module */
/*const volatile*/ uint8_T CV_IACSOL = 0U; /* code variant, idle air control solenoid valve */
/*const volatile*/ uint8_T CV_IDCND = 0U;  /* code variant, idle speed control N desired */
/*const volatile*/ uint8_T CW_NotLcAd = 33U;/* codeword for release of adaptation */
/*const volatile*/ uint8_T MAP_TexEstm_N_Ld[64] = { 70U, 77U, 88U, 99U, 110U, 121U,
  131U, 139U, 89U, 95U, 103U, 112U, 122U, 133U, 142U, 149U, 113U, 120U, 128U,
  135U, 143U, 149U, 158U, 164U, 125U, 137U, 142U, 153U, 161U, 170U, 176U, 184U,
  142U, 150U, 156U, 165U, 173U, 181U, 187U, 193U, 152U, 159U, 168U, 176U, 182U,
  188U, 194U, 200U, 159U, 166U, 174U, 183U, 189U, 195U, 201U, 206U, 165U, 173U,
  181U, 190U, 196U, 201U, 206U, 210U };/* characteristic map,  Temperature exhaust gas, steady-state value, dependent on Rpm and load */

/*const volatile*/ int8_T MAP_dIgaKnp_Tm_Ta[36] = { 0, 0, 0, 0, 0, 0, 0, -4, -4, -4,
  -4, -4, 0, -4, -6, -6, -8, -8, 0, -4, -8, -8, -8, -8, 0, -4, -8, -8, -8, -8, 0,
  -4, -8, -8, -8, -8 };               /* characteristic map,  delta ignition angle for knock protection, dependent on engine coolant temperature and intake air temperature */

/*const volatile*/ int8_T MAP_dIgaMn_Tm_Ta[36] = { 0, 0, 0, 0, 0, 0, 0, -4, -4, -4,
  -4, -4, 0, -4, -6, -6, -8, -8, 0, -4, -8, -8, -8, -8, 0, -4, -8, -8, -8, -8, 0,
  -4, -8, -8, -8, -8 };               /* characteristic map,  delta min-ignition angle for knock protection, dependent on engine coolant temperature and intake air temperature */

/*const volatile*/ uint8_T MAP_fwReSta_tEngOff_TmSta[36] = { 42U, 46U, 60U, 76U,
  102U, 128U, 42U, 46U, 61U, 81U, 102U, 128U, 83U, 90U, 102U, 115U, 128U, 128U,
  84U, 90U, 103U, 115U, 128U, 128U, 115U, 115U, 115U, 128U, 128U, 128U, 128U,
  128U, 128U, 128U, 128U, 128U };     /* char. map, weighting factor of repeated start, dependent on engine-off time and start temp. */

/*const volatile*/ uint8_T MAP_fwWmp_N_Ld[36] = { 64U, 64U, 64U, 64U, 64U, 64U, 64U,
  64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U,
  64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U, 64U };/* char. map, weighting warm-up factor, dependent on load / speed */

/*const volatile*/ uint8_T VAL_IntMafTamTa = 10U;/* threshold integrated air mass for determination ambient temp. (from Ta) */
/*const volatile*/ uint8_T VAL_LdLo2 = 40U;/*  lower load-signal threshold range 2 */
/*const volatile*/ uint8_T VAL_LdLo3 = 21U;/* lower load-signal threshold range 3 */
/*const volatile*/ uint8_T VAL_LdLo4 = 73U;/*  lower load threshold of the upper multiplicative section */
/*const volatile*/ uint8_T VAL_LdUp2 = 94U;/*  upper load threshold of range 2 */
/*const volatile*/ uint8_T VAL_LdUp3 = 33U;/*  upper load threshold of range 3 */
/*const volatile*/ uint16_T VAL_MafLo2 = 1250U;/*   lower air-quantity threshold range 2    */
/*const volatile*/ uint16_T VAL_MafLo4 = 5833U;/*  lower air-quantity threshold range 4 */
/*const volatile*/ uint16_T VAL_MafUp2 = 4167U;/* upper air-quantity threshold range 2 */
/*const volatile*/ uint16_T VAL_MafUp3 = 1042U;/*    upper air-quantity threshold range 3 */
/*const volatile*/ uint8_T VAL_NLo2 = 33U; /* lower engine-speed threshold range 2 */
/*const volatile*/ uint8_T VAL_NLo3 = 27U; /* lower engine-speed threshold range 3 */
/*const volatile*/ uint8_T VAL_NUp2 = 67U; /* upper engine-speed threshold range 2 */
/*const volatile*/ uint8_T VAL_NmnTamTa = 30U;/* threshold engine speed for determination ambient temperature (from Ta) */
/*const volatile*/ int16_T VAL_OfsLcAdSynMn = -1624;/* lower threshold of additive correction per ignition */
/*const volatile*/ int16_T VAL_OfsLcAdSynMx = 1624;/*  up threshold of additive correction per ignition */
/*const volatile*/ uint16_T VAL_T_LsuDiag = 38400U;/* LSU sensor temperature threshold to enable diagnosis */
/*const volatile*/ uint16_T VAL_T_Lsu_LcEn = 38400U;/* LSU sensor temperature threshold to enable lambda control */
/*const volatile*/ uint8_T VAL_TamIni = 48U;/* inital value of ambient temperature (from Ta) */
/*const volatile*/ uint8_T VAL_TexBfCatDew = 80U;/* Characteristic value, Temperature threshold for lambda sensor dew point */
/*const volatile*/ uint8_T VAL_TexCatLitOff = 60U;/* Characteristic value, Exhaust-gas temperature below the catalyzer light-off temperature */
/*const volatile*/ uint8_T VAL_TexDew = 21U;/* Characteristic value, exhaust temperature at dew point */
/*const volatile*/ uint8_T VAL_TexFof = 22U;/* Characteristic value, exhaust gas temperature at fuel cut off */
/*const volatile*/ uint8_T VAL_TmLamAd = 100U;/*  cut-in temperature adaptive precontrol for lambda closed-loop control  */
/*const volatile*/ uint8_T VAL_TmWmpEstm = 104U;/* Characteristic value, engine temperature warmed up engine, for temperature correction cold engine */
/*const volatile*/ uint8_T VAL_VspFof = 8U;/* vehicle speed threshold for cut off engine speed increase */
/*const volatile*/ uint8_T VAL_VspMnTamTa = 0U;/* threshold vehicle speed for determination ambient temperature from Ta */
/*const volatile*/ uint8_T VAL_dNFofVspLow = 0U;/* cut off engine speed increase at low vehicle speed */
/*const volatile*/ int8_T VAL_dTexWoTexo = 0;/* Characteristic value */
/*const volatile*/ int8_T VAL_dTexinWoTexo = 0;/* Characteristic value */
/*const volatile*/ int16_T VAL_dTpsLamAd = 983;/* threshold gradient throttle angle for wideband lambda adaptation */
/*const volatile*/ uint8_T VAL_fHtLsbDewNotLst = 64U;/* Characteristic value, correction factor, Heat threshold without Dew-Point-End before Cat in the last trip */
/*const volatile*/ uint8_T VAL_fLamAdMn = 64U;/* lower limit of wideband lambda adaptation   */
/*const volatile*/ uint8_T VAL_fLamAdMx = 192U;/* upper limit of wideband lambda adaptation  */
/*const volatile*/ uint8_T VAL_fLcAdLoMn = 96U;/* lower limit of correction factor frau  */
/*const volatile*/ uint8_T VAL_fLcAdLoMx = 137U;/* upper limit of correction factor frau  */
/*const volatile*/ uint8_T VAL_fLcAdUpMn = 96U;/* lower limit of correction factor frao   */
/*const volatile*/ uint8_T VAL_fLcAdUpMx = 160U;/* upper limit of correction factor frao  */
/*const volatile*/ uint8_T VAL_fWmpMin = 129U;/* Minimum warm-up factor, that indicates warm up phase is end */
/*const volatile*/ uint8_T VAL_fddTps = 128U;/* factor, ddTps , TPS acceleration multiplicative factor */
/*const volatile*/ uint8_T VAL_kfWmpRmp = 128U;/* filter coefficient, warm up factor */
/*const volatile*/ uint16_T VAL_tAstIdlGr = 600U;/* Minimum after start timer, to use load to detect the gear status */
/*const volatile*/ uint16_T VAL_tDlyLsbDewMin = 600U;/* minimal delay time for dew point reached, for protecting O2 sensor */
/*const volatile*/ uint16_T VAL_tWmpMax = 9000U;/* Minimum warm-up factor, that indicates warm up phase is end */
/*const volatile*/ uint16_T VAL_tWmpMin = 9000U;/* Minimum warm-up factor, that indicates warm up phase is end */
/*const volatile*/ uint16_T VAL_tcLcAdRst = 25U;/* time constant  for reset of mixture correction on last trip value */
/*const volatile*/ uint16_T VAL_tcOfsLcAdSyn = 164U;/* integration speed integrator OfsLcAd */
/*const volatile*/ uint16_T VAL_tcfLcAdLo = 164U;/* time constant for frau-integrator */
/*const volatile*/ uint16_T VAL_tcfLcAdUp = 164U;/* time constant for fLcAdUp-integrator */

#define STOP_SECTION_r200msRom
#include "pragma.h"
#define START_SECTION_r20msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
int16_T Acl;                           /* vehicle acceleration in the longitudinal direction  */
boolean_T B_IdlGr;                     /* Idle speed with gear engaged condition */
boolean_T B_IgFlwUp;                   /* Condition follow-up ignitions */
boolean_T B_LsbDgEn;                   /* condition for lambda sensor diagnosis enabled */
boolean_T B_LsbLeakUb;
boolean_T B_LsbLmAmp;                  /* lambda sensor error, limited amplitude */
boolean_T B_LsbOpnGndDyn;              /* lambda sensor open to ground, dynamically */
boolean_T B_LsbPlausEn;                /* condition: lambda sensor plausibility test enable */
boolean_T B_LsbRdy;                    /* condition for lambda sensor ready for operation, upstream cat  */
boolean_T B_LsbRdyset;
boolean_T B_LsbScMn;                   /* lambda sensor short circuit to ground, min error */
boolean_T B_LsbScMx;                   /* lambda sensor short circuit, max error */
boolean_T B_LsbScUb;                   /* Short circiut to battery voltage at O2 sensor pre cat */
boolean_T B_LsbSigErr;                 /* Signal interruption at O2 sensor upstream cat  */
boolean_T B_LsbTheoRdyHt;
boolean_T B_LsbWirBrk;
boolean_T B_VspNul;                    /* condition vehicle at stillstand  */
boolean_T E_Vsp;                       /* Error flag: vehicle speed signal  */
uint16_T LDistKm;                      /* vehicle distance travelled, in KiloMeter, 16-bit  */
uint16_T LDistM;                       /* vehicle distance travelled, in KiloMeter, 16-bit  */
uint32_T LDist_L;                      /* vehicle distance travelled, in meter, 32-bit  */
uint16_T LPT_IDCND_NDsrIdc_U32;        /* Desired engine speed for Idc filter data store memory */
uint32_T LPT_SSVSP_U32;
uint16_T MAF;                          /* Mass air flow */
uint16_T Maf;                          /* Mass air flow */
uint8_T Maf_b;                         /* Mass air flow (byte) */
uint8_T NDsrIdc;                       /* idle reference speed */
uint8_T NDsrIdcFlwUp;                  /* followed-up target speed */
uint8_T NDsrIdcSta;                    /* desired  idle speed during start */
uint8_T Nstat;                         /* Engine stationary speed in Rpm */
uint16_T O2S;                          /* oxygen sensor voltage  */
uint8_T TOnD_DLSV1;
uint8_T TOnD_DLSV2;
uint8_T TOnD_DLSV3;
uint8_T TOnD_DLSV4;
uint16_T TOnD_DLSV5;
uint8_T TOnD_DLSV6;
uint8_T TOnD_DLSV_B_LsbScMx1;
uint16_T TOnD_SSVSP1_U16;
uint16_T TOnD_SSVSP2_U16;
uint16_T UD_DS_SSVSP_Vsp;
uint8_T UD_IDCND_NDsrIdc;              /* Unit-Dealy, idc desried engine speed */
uint32_T UD_LDist_L;                   /* vehicle distance travelled, in meter, 32-bit  */
uint32_T UD_Odo_L;                     /* vehicle distance travelled, in meter, 32-bit  */
uint16_T VSS;                          /* Vehicle speed, Sensor measured  */
uint16_T Vsp;                          /* Vehicle speed  */
uint16_T VspRaw;                       /* vehicle speed output value to scan tool  */
uint16_T VspWhlDrv;                    /* Vehicle Speed from the driven wheel speed sensor */
uint16_T VspWhlNonDrv;                 /* Vehicle Speed from the non-driven wheel speed sensor */
uint8_T Vsp_b;                         /* vehicle speed (Km/h)  */
uint16_T VssMps;                       /* vehicle speed in meter per second  */
int8_T dNstat;                         /* difference of idle speed stationary */
uint8_T nIgFlwUp;                      /* number of follow-up ignitions */
uint16_T tBrkFlwUp;                    /* break time between follow-up ignitions */
uint8_T tDwl;                          /* dwell time */
uint16_T tDwlFlwUp;                    /* dwell time for follow-up ignitions */

#define STOP_SECTION_r20msRam
#include "pragma.h"
#define START_SECTION_r20msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint8_T BP_NDsr_Tm[9] = { 8U, 20U, 32U, 48U, 64U, 80U, 100U, 112U,
  124U };                             /* break points, engine temperature , for desired idle speed */

/*const volatile*/ uint8_T BP_nFlwUp_N[8] = { 0U, 1U, 5U, 7U, 10U, 14U, 17U, 33U };/* engine speed */

/*const volatile*/ uint8_T BP_nFlwUp_Tm[8] = { 0U, 12U, 15U, 20U, 24U, 41U, 60U, 77U
};                                    /* engine coolant temperature */

/*const volatile*/ uint8_T BP_tDwl_N[8] = { 1U, 3U, 7U, 11U, 17U, 33U, 50U, 106U };/* engine speed */

/*const volatile*/ uint8_T BP_tDwl_uBat[8] = { 50U, 60U, 80U, 100U, 119U, 140U, 160U,
  180U };                             /* battery voltage */

/*const volatile*/ uint8_T BP_tFlwUp_uBat[8] = { 63U, 84U, 105U, 115U, 125U, 147U,
  157U, 178U };                       /* battery voltage */

/*const volatile*/ uint8_T BP_tdLcEnAcl_Tm[8] = { 8U, 20U, 32U, 48U, 64U, 80U, 96U,
  104U };                             /* engine temperature  */

/*const volatile*/ uint8_T BP_tdLcSys_N[7] = { 10U, 13U, 17U, 23U, 33U, 53U, 83U };/* Break point of lock time for p-offset after lambda sensor voltage jump  */

/*const volatile*/ uint8_T CUR_NDsr_Tm[9] = { 220U, 200U, 180U, 170U, 160U, 150U,
  140U, 140U, 140U };                 /* nominal engine speed for idle, dependent on engine temperature */

/*const volatile*/ uint8_T CUR_tFlwUp_uBat[8] = { 70U, 53U, 46U, 42U, 40U, 35U, 33U,
  30U };                              /* Follow-up ignition dwell time */

/*const volatile*/ uint8_T CUR_tdLcEnAcl_Tm[8] = { 30U, 30U, 30U, 25U, 20U, 15U, 0U,
  0U };                               /* delay time for activation LC after accelerations  */

/*const volatile*/ uint8_T CUR_tdLcEnDcl_Tm[8] = { 30U, 30U, 30U, 25U, 20U, 15U, 0U,
  0U };                               /*  delay time for activation LC after decelerations  */

/*const volatile*/ uint8_T CUR_tdLcSys_N[7] = { 35U, 30U, 28U, 25U, 18U, 9U, 5U };/* lock time for p-offset after lambda sensor voltage jump  */

/*const volatile*/ uint8_T MAP_nFlwUp_N_Tm[64] = { 2U, 2U, 2U, 2U, 2U, 2U, 1U, 0U,
  2U, 2U, 2U, 2U, 2U, 1U, 0U, 0U, 2U, 2U, 2U, 2U, 1U, 0U, 0U, 0U, 2U, 2U, 2U, 2U,
  1U, 0U, 0U, 0U, 2U, 2U, 2U, 2U, 1U, 0U, 0U, 0U, 2U, 2U, 2U, 2U, 1U, 0U, 0U, 0U,
  1U, 1U, 1U, 1U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };/* characteristic map,  Number of follow-up sparks, dependent on engine speed and engine coolant temperature */

/*const volatile*/ uint8_T MAP_tDwl_uBat_N[64] = { 179U, 179U, 179U, 58U, 42U, 36U,
  28U, 32U, 179U, 179U, 179U, 58U, 42U, 36U, 28U, 32U, 179U, 179U, 179U, 58U,
  42U, 36U, 28U, 32U, 179U, 179U, 179U, 58U, 42U, 36U, 28U, 32U, 179U, 179U,
  179U, 58U, 42U, 36U, 28U, 32U, 179U, 179U, 179U, 58U, 42U, 36U, 28U, 32U, 179U,
  179U, 179U, 58U, 42U, 36U, 28U, 32U, 179U, 179U, 179U, 58U, 42U, 36U, 28U, 32U
};                                    /* characteristic map,  dwell time, dependent on engine speed and battery voltage */

/*const volatile*/ uint16_T VAL_DiamWhlDrv = 515U;/* number of teeth of the driven wheel speed sensing  */
/*const volatile*/ uint16_T VAL_DiamWhlNonDrv = 515U;/* number of teeth of the driven wheel speed sensing  */
/*const volatile*/ uint8_T VAL_LdDclLcEn = 80U;/* Upper load-threshold for trigger of LC off during transient decelerations  */
/*const volatile*/ uint16_T VAL_LdIdlGrLow = 853U;/* Load upper threshold to detect gear engaged in idle */
/*const volatile*/ uint16_T VAL_LdIdlGrUp = 1280U;/* Load upper threshold to detect gear engaged in idle */
/*const volatile*/ uint8_T VAL_LsbPwrHtMn = 80U;/* minimal normalised heating-power-diagnosis sensor pre catalyst */
/*const volatile*/ uint8_T VAL_NidlDsrGr = 70U;/* idle speed desired for gear engaged */
/*const volatile*/ uint8_T VAL_NidlLdGrMax = 250U;/* idle speed max for gear engaged */
/*const volatile*/ uint8_T VAL_NmnFlwUp = 27U;/* Engine speed lower limit for follow-up ignitions */
/*const volatile*/ uint16_T VAL_NmnVspErr = 25U;/* error detection vehicle speed signal / minimum threshold for engine speed  */
/*const volatile*/ uint16_T VAL_NmnVspErr1 = 67U;/* Detection of error for vehicle speed / minimum threshold  */
/*const volatile*/ uint8_T VAL_TmIdlGr = 64U;/* Engine temperature to enable gear idle speed control */
/*const volatile*/ uint8_T VAL_TmVspDg = 84U;/* motor temperature threshold for release of vehicle speed diagnosis  */
/*const volatile*/ uint8_T VAL_VspErrLd = 0U;/* Detection error of speed signal due to realtive load signal  */
/*const volatile*/ uint8_T VAL_VspMn = 1U; /* Detection of driving-standing  */
/*const volatile*/ uint8_T VAL_VspMnDg = 16U;/* vehicle speed threshold; fault detection vhehicle speed signal  */
/*const volatile*/ uint8_T VAL_VspMnDg1 = 0U;/* Vehicle speed threshold for error detection  */
/*const volatile*/ uint8_T VAL_dNDsrFlwUpMx = 80U;/* Offset to determine the upper limit of target speed */
/*const volatile*/ uint8_T VAL_dNFlwUpInh = 3U;/* Engine speed follow-up inhibition band */
/*const volatile*/ uint8_T VAL_fNDsrFlwUp = 243U;/* factor for desired engine-speed correction */
/*const volatile*/ uint8_T VAL_nTeethWhl = 8U;/* number of teeth of the wheel speed sensing  */
/*const volatile*/ uint8_T VAL_tBrkFlwUp = 8U;/* break time between every 2 follow-up ignitions */
/*const volatile*/ uint8_T VAL_tDwlMn = 20U;/* minumin dwell time */
/*const volatile*/ uint8_T VAL_tcNDsrFil = 20U;/* characteristic value, time constant for filtering of reference speed at start */
/*const volatile*/ uint16_T VAL_tcVspFil = 8U;/* Lower threshold of vehicle speed  */
/*const volatile*/ uint8_T VAL_tdDashPotIacSol = 10U;/* Time delay to open the idle solenoid for dashpot */
/*const volatile*/ uint8_T VAL_tdLsbSigErr = 3U;/* Time for the deactiv.of interf. peaks outside of range for det.of signal interr */
/*const volatile*/ uint16_T VAL_tdVspErr = 84U;/* error detection tachometer signal / time for interrogation  */
/*const volatile*/ uint8_T VAL_tuLsbSuppr = 5U;/* Time of inter. suppress. f. switching off single funct.:sensor downstr. the cat */

#define STOP_SECTION_r20msRom
#include "pragma.h"
#define START_SECTION_r50msRam
#include "pragma.h"

/* Definition for custom storage class: Ram */
boolean_T B_CldReSta;                  /* Condition cold re-start */
boolean_T B_OilEn;                     /* Oil pump enabled  */
boolean_T B_ReSta;                     /* condition for re-start */
uint32_T LPK_MapAvg_U16;               /* LowPassFilter K-type, Averaged MAP signal */
uint32_T LPT_fVeRaw;                   /* LowPassFilter, factor volumetric efficiency */
uint16_T UD_VolPmpWoSta;               /* volume of fuel for pump lead without engine start */
uint16_T fPrs2Ld;                      /* factor converting pressure to load  */

#define STOP_SECTION_r50msRam
#include "pragma.h"
#define START_SECTION_r50msRom
#include "pragma.h"

/* Definition for custom storage class: Rom */
/*const volatile*/ uint16_T BP_fAlt_N[8] = { 4800U, 6600U, 10000U, 16000U, 20000U,
  24000U, 28000U, 32000U };           /* input<N>, break point, engine speed, for altitude factor */

/*const volatile*/ uint16_T BP_fAlt_Pam[8] = { 10240U, 15360U, 17920U, 20480U,
  21760U, 23040U, 24832U, 26880U };   /* input<Map>, break point, baro pressure, for altitude factor */

/*const volatile*/ uint8_T BP_fLc_Ld6[6] = { 13U, 27U, 40U, 60U, 80U, 100U };/* input<Ld_b>, break points, load for factor lambda control  */

/*const volatile*/ uint8_T BP_fLc_N6[7] = { 13U, 25U, 33U, 42U, 50U, 67U, 83U };/* input<N_b>, Break points, engine speed for factor lambda control */

/*const volatile*/ uint16_T BP_fVe_Map[16] = { 7680U, 8960U, 10240U, 11008U, 11776U,
  12800U, 14080U, 15360U, 16640U, 17920U, 19200U, 20480U, 21760U, 23040U, 24832U,
  26880U };                           /* input<Map>, break point, manifold absolute pressure, for Volumatric Efficiency factor */

/*const volatile*/ uint16_T BP_fVe_N[12] = { 4800U, 5600U, 6600U, 8000U, 10000U,
  12000U, 14000U, 16000U, 20000U, 24000U, 28000U, 32000U };/* input<N>, break point, engine speed, for Volumatric Efficiency factor */

/*const volatile*/ uint8_T BP_tEngOffReSta_TmOff[8] = { 7U, 15U, 22U, 33U, 48U, 76U,
  102U, 120U };                       /* break points,engine coolant temperature at engine stop */

/*const volatile*/ uint8_T CUR_tEngOffReSta_TmOff[8] = { 183U, 105U, 66U, 40U, 40U,
  40U, 20U, 20U };                    /* threshold engine-off timer for re-start */

/*const volatile*/ uint16_T MAP_fAlt_N_Pam[64] = { 12595U, 12595U, 12595U, 12595U,
  12595U, 12595U, 12595U, 12595U, 12606U, 12606U, 12606U, 12606U, 12606U, 12606U,
  12606U, 12606U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U, 13571U,
  13443U, 13443U, 13443U, 13443U, 13443U, 13443U, 13443U, 13443U, 14746U, 14746U,
  14746U, 14746U, 14746U, 14746U, 14746U, 14746U, 15565U, 15565U, 15565U, 15565U,
  15565U, 15565U, 15565U, 15565U, 15892U, 15892U, 15892U, 15892U, 15892U, 15892U,
  15892U, 15892U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U, 16384U
};                                    /* Factor altitude for load, dependent on baro pressure and engine speed */

/*const volatile*/ uint8_T MAP_fLcIBas_N_Ld[42] = { 7U, 12U, 14U, 21U, 31U, 39U, 43U,
  11U, 14U, 21U, 27U, 38U, 43U, 50U, 13U, 18U, 32U, 37U, 47U, 53U, 63U, 17U, 24U,
  36U, 45U, 55U, 62U, 72U, 18U, 27U, 39U, 52U, 66U, 74U, 78U, 20U, 30U, 42U, 55U,
  69U, 77U, 80U };                    /* input-X <BP_fLc_N6>,input-Y <BP_fLc_Ld6>,characteristic map,  factor lambda control I gain, basic value */

/*const volatile*/ uint8_T MAP_fLcPBas_N_Ld[42] = { 28U, 30U, 44U, 47U, 48U, 48U,
  48U, 34U, 35U, 45U, 47U, 48U, 48U, 48U, 35U, 40U, 47U, 47U, 48U, 48U, 48U, 37U,
  44U, 48U, 48U, 49U, 49U, 49U, 40U, 44U, 48U, 50U, 51U, 51U, 51U, 43U, 47U, 48U,
  50U, 51U, 52U, 52U };               /* input-X <BP_fLc_N6>,input-Y <BP_fLc_Ld6>,characteristic map,  factor lambda control P gain, basic value */

/*const volatile*/ uint16_T MAP_fVe_Map_N[192] = { 22284U, 22284U, 21806U, 18367U,
  19762U, 21220U, 18416U, 19675U, 17096U, 17925U, 20286U, 21988U, 20095U, 20095U,
  20072U, 19424U, 21426U, 21690U, 19790U, 19807U, 18865U, 19789U, 20405U, 20985U,
  21060U, 21060U, 21060U, 21566U, 23554U, 24335U, 27188U, 25041U, 27004U, 25247U,
  26177U, 26323U, 22665U, 22665U, 22665U, 21834U, 23703U, 26064U, 27424U, 25858U,
  29951U, 28471U, 28006U, 28006U, 21201U, 21201U, 23949U, 23264U, 25120U, 27578U,
  27726U, 28282U, 30962U, 30602U, 28312U, 29596U, 22607U, 22607U, 24419U, 23874U,
  25431U, 27771U, 27201U, 29818U, 30637U, 32638U, 30819U, 27316U, 24364U, 24364U,
  25402U, 24857U, 26561U, 28265U, 28651U, 29328U, 31746U, 34353U, 32742U, 29739U,
  24048U, 26121U, 27123U, 26394U, 28035U, 29675U, 29441U, 28646U, 32542U, 33667U,
  32928U, 31214U, 25189U, 26627U, 27454U, 24102U, 27894U, 29436U, 26347U, 31183U,
  33612U, 36563U, 31994U, 31421U, 25212U, 25448U, 27272U, 27713U, 31237U, 30872U,
  28998U, 28915U, 31595U, 35244U, 32905U, 33227U, 27141U, 27141U, 28672U, 27577U,
  30424U, 31515U, 28759U, 27912U, 31906U, 38809U, 38339U, 34932U, 26886U, 26886U,
  27486U, 25920U, 28474U, 30515U, 28019U, 27554U, 30827U, 38591U, 38245U, 35379U,
  25273U, 25273U, 25684U, 25553U, 27910U, 29958U, 28865U, 26741U, 30702U, 38074U,
  37849U, 33546U, 24472U, 24472U, 25756U, 24070U, 26556U, 29139U, 27629U, 26753U,
  29851U, 36674U, 36568U, 32962U, 22972U, 22972U, 22974U, 22324U, 24595U, 26866U,
  26112U, 24997U, 28281U, 33574U, 34676U, 30540U, 22972U, 22972U, 22974U, 22324U,
  24595U, 26866U, 25681U, 24847U, 27616U, 33406U, 34503U, 30387U };/* Factor Volumatric Efficiency, dependent on pressure and engine speed */

/*const volatile*/ int8_T MAP_tdLcBas_N_Ld[42] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0 };                    /* input-X <BP_fLc_N6>,input-Y <BP_fLc_Ld6>,characteristic map,  time delay lambda control switching, basic value */

/*const volatile*/ uint16_T VAL_RatPmp = 4U;/* Supply flow rate of fuel pump */
/*const volatile*/ uint8_T VAL_TmCldSta = 72U;/* engine temp. for cold-start */
/*const volatile*/ uint16_T VAL_fPrs2LdNrm = 19661U;/* factor pressure to load conversion, normalized */
/*const volatile*/ uint16_T VAL_tcfVeRaw = 10U;/* time constant for low pass filtering of volumetric efficiency  */
/*const volatile*/ uint16_T VAL_vFlSupPmp = 300U;/* Volume flow for pump lead time  */

#define STOP_SECTION_r50msRom
#include "pragma.h"

/* Block signals (auto storage) */
BlockIO_Controller global_Controller_B;

/* Block states (auto storage) */
D_Work_Controller global_Controller_DWork;

/* Declare variables for internal data of system '<S1113>/LC_r10ms' */
#define START_SECTION_SlowRam
#include "pragma.h"

rtDW_LC_r10ms global_LC_r10ms_DW;

extern ConstBlockIO_Controller global_Controller_ConstB;
extern const ConstParam_Controller global_Controller_ConstP;

#define STOP_SECTION_SlowRam
#include "pragma.h"

/* Output and update for function-call system: '<S13>/ini' */
#define START_SECTION_InitCode
#include "pragma.h"

void SWADP_ini(void)
{
  /* local block i/o variables */
  uint8_T local_FixPtBitwiseOperator;
  B_FMemClr = 0U;
  B_CatWm = 0U;
  B_CatHt = 0U;
  dIgaWmp = 0;
  Gr = 1U;
  FlPg = 0;
  IsIacErr = 0U;
  B_DgPgv = 0U;
  MafPgv_b = 0U;
  EfcCah = 200U;
  MafPgv = 0U;
  TqiLsd = MAX_uint16_T;
  MafNrmIdc = 0U;

  /*  */

  /* Bitwise Block: '<S1464>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_IGA) & ((((uint8_T)1U)));
  USR_BitField.B_IgaApp = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U : 0U);
  B_CatHtFst = 0U;
  tdLcCatPur = 0;
  fFlPgAct = 32U;
  E_Pg = 0U;
  B_Pg = 0U;
  B_PgAirLcRst = 0U;
  fLcMPg = 32768U;
  B_Brk = 0U;
  B_FlAdPha = 1U;
  B_FlAdpDis = 0U;
  B_TstReq = 0U;
  B_TstFlSyDg = 0U;
  E_FlSyDg = 0U;

  /*  */

  /* Bitwise Block: '<S1465>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_LSB) & ((((uint8_T)1U)));
  USR_BitField.IsLsbHtApp = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U :
    0U);

  /*  */

  /* Bitwise Block: '<S1466>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_LSB) & ((((uint8_T)2U)));
  USR_BitField.IsLsbDgUsr = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U :
    0U);

  /*  */

  /* Bitwise Block: '<S1467>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_LSB) & ((((uint8_T)4U)));

  {
    uint8_T temp_tmp;
    USR_BitField.IsLcUsr = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U :
      0U);
    if (tEngOff > 255U) {
      temp_tmp = MAX_uint8_T;
    } else {
      temp_tmp = (uint8_T)tEngOff;
    }

    tEngOff_b = temp_tmp;
  }

  /*  */

  /* Bitwise Block: '<S1468>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_IGA) & ((((uint8_T)2U)));
  USR_BitField.IsIgaBas = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U : 0U);

  /*  */

  /* Bitwise Block: '<S1469>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator = (CV_IGA) & ((((uint8_T)4U)));
  USR_BitField.IsIgaPre = (boolean_T)(local_FixPtBitwiseOperator != 0U ? 1U : 0U);
  LamCatHt = 4096U;
  LamCatPur = 4096U;
  LamCmpProt = 4096U;
  LamAstWmp = 4096U;
  B_Lsd = 0U;
  IgaVmx = 80;
  tAfrApp = VAL_tAfrApp;
  if (B_Pwf) {
    Err_CrankSensing_Flag = 0U;
    Err_Spark_Flag = 0U;
    Err_Fuel_Flag = 0U;
  }
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S622>/ini' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSMAFTP_ini(void)
{
  /* user code (Update function Body) */
  /* System '<S622>/ini' */
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1171>/ini' */
#define START_SECTION_r200msCode
#include "pragma.h"

void LCAD_ini(void)
{
  /* user code (Update function Body) */
  /* System '<S1171>/ini' */
  if (B_Pwf) {
    fLcAdLo = 32768;
    fLcAdUp = 32768;
    fLcAd = 32768;
    OfsLcAdSyn= 0;
    OfsLcAd= 0;
  }

  INK_LCAD_dfLcM1 = ((uint32_T)fLcAdLo << 16U);
  INK_LCAD_dfLcM2 = ((uint32_T)fLcAdUp << 16U);
  INK_LCAD_dfLcM4 = ((int32_T)OfsLcAdSyn << 16U);
}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Start for function-call system: '<S1262>/ini2' */
#define START_SECTION_InitCode
#include "pragma.h"

void LCADWB_ini_Start(void)
{
  /* blocks with infinite sample periods */
  //======= 2015-5-26 œ»≤ª”√
  
  /*
  {
    int16_T temp_yDimIdx;
    int16_T temp_yDimIdx_0;
    for (temp_yDimIdx_0 = 0; (int32_T)temp_yDimIdx_0 < 1L; temp_yDimIdx_0++) {
      for (temp_yDimIdx = 0; (int32_T)temp_yDimIdx < 1L; temp_yDimIdx++) {
        fLamAdTab[13] = 32768U;
      }
    }

    for (temp_yDimIdx = 0; (int32_T)temp_yDimIdx < 1L; temp_yDimIdx++) {
      for (temp_yDimIdx_0 = 0; (int32_T)temp_yDimIdx_0 < 1L; temp_yDimIdx_0++) {
        fLamAdTab_an[17] = 32768U;
      }
    }

    for (temp_yDimIdx_0 = 0; (int32_T)temp_yDimIdx_0 < 1L; temp_yDimIdx_0++) {
      RAM_SelfLearnHistory[1] = 128U;
    }
    
    isAutoTune = (boolean_T)1U;
  }*/
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S798>/ini' */
#define START_SECTION_InitCode
#include "pragma.h"

void OCFOFRSM_ini(void)
{
  /* local block i/o variables */
  int16_T local_shift_c;
  int16_T local_INT_ret;

  {
    int16_T temp_max;
    int8_T temp_tmp;
    if (VAL_dNFofL > 127U) {
      temp_tmp = MAX_int8_T;
    } else {
      temp_tmp = (int8_T)VAL_dNFofL;
    }

    temp_max = (temp_tmp << 8U);
    if (VAL_dNFofH > 127U) {
      temp_tmp = MAX_int8_T;
    } else {
      temp_tmp = (int8_T)VAL_dNFofH;
    }

    local_shift_c = (temp_tmp << 8U);
    temp_max = rt_MAX(temp_max, local_shift_c);
    INTK_OCFOFRSM_S16 = rt_MIN(21760, temp_max);
    local_INT_ret = INTK_OCFOFRSM_S16;
  }

  /*  */
  local_INT_ret = IntegratorK_S8( local_INT_ret,
    global_Controller_ConstB.IN_Phy2Hex_b, VAL_NgFofHysDec);
  RSFF_OCFOFRSM2 = 0U;
  RSFF_OCFOFRSM1 = 0U;
  RSFF_OCFOFRSM3 = 0U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S876>/ini' */
#define START_SECTION_r10msCode
#include "pragma.h"

void PWPUMP_ini(void)
{
  /* local block i/o variables */
  uint8_T local_FixPtBitwiseOperator_k;
  UD_B_PWPumpPrimeEn = 1U;

  /*  */

  /* Bitwise Block: '<S886>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator_k = (CV_PWPUMP) & ((((uint8_T)1U)));
  B_PWPumpExist = (boolean_T)(local_FixPtBitwiseOperator_k != 0U ? 1U : 0U);
  Ctr_PWPumpPrime_10ms = 0U;
}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S548>/ini' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SERVO_ini(void)
{
  /*  */
  isServo = VAL_tServoCtrlCycle || VAL_tOnServoCtrl_Err;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Start for function-call system: '<S1488>/sm_task_ini' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_ini_Start(void)
{
  LCADWB_ini_Start();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1488>/sm_task_ini' */
void tasks_ini(void)
{
  /*  */
  SWADP_ini();
  CSMAFTP_ini();
  SERVO_ini();
  OCFOFRSM_ini();
  PWPUMP_ini();
  LCAD_ini();
}

/* Output and update for function-call system: '<S649>/iniSyn' */
#define START_SECTION_InitSynCode
#include "pragma.h"

void CSIMM_iniSyn(void)
{
  fLd2MafSyn = VAL_vEng;

  /* user code (Update function Body) */
  /* System '<S649>/iniSyn' */
  // UD_CSIMM_LdMod = 4267U;
  UD_CSIMM_Ld = 4267U;

  // Accum_CSIMM_PimMod_S32 = 849740058L;
  //PimMx = 25933U;
  fPrs2Ld = 21565U;

  //fIntImMod = 12448U;
  Ld_b = 133U;
  LdMod = 4267U;
  Ld = 4267U;
  Pim= Pam;
  PimMod= Pam;
  Pim_b= (uint8_T)(Pim>>8);
}

#define STOP_SECTION_InitSynCode
#include "pragma.h"

/* Output and update for function-call system: '<S740>/iniSyn' */
#define START_SECTION_r50msCode
#include "pragma.h"

void FLSTA_iniSyn(void)
{
  /* local block i/o variables */
  boolean_T local_S;
  if (B_HotSta) {
    local_S = 1U;
  } else {
    local_S = GenFast_BitField.RSFF_FISTA_HotSta;
  }

  GenFast_BitField.RSFF_FISTA_HotSta = local_S;
}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Start for function-call system: '<S13>/iniSyn' */
#define START_SECTION_InitCode
#include "pragma.h"

void SWADP_iniSyn_Start(void)
{
  /* blocks with infinite sample periods */
  Current_Timer = 0UL;
  Last_Falling_Edge_Timer = 0UL;
  Last_Rising_Edge_Timer = 0UL;
  Last_Rising_Edge_Timer_Bak = 0UL;
  Max_Map_Record_index = 0U;
  Min_Map_Record_index = 0U;
  Max_Map_Record = 0U;
  Min_Map_Record = 0U;
  Last_Period_Min_Map_Record = 0U;
  Err_Calibration_Flag = 0U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S13>/iniSyn' */
#define START_SECTION_InitCode
#include "pragma.h"

void SWADP_iniSyn(void)
{
  /* local block i/o variables */
  uint16_T local_LookupTable2D;
  uint16_T local_LookupTable2D1;
  uint16_T local_LookupTable2D3;
  uint16_T local_CUR_WetFl_Ldp;
  uint8_T local_LookupTable1;
  uint8_T local_CUR_fWmp_Tm;
  int8_T local_LookupTable2D2;
  uint8_T local_CUR_fWmp_Tm1;
  IGNC_Delta_IgaOut = 0;
  Fuel_Pulse1_In = 0U;
  dNIdcIgaBand = VAL_dNIdcIgaBand;

  /* Lookup Block: '<S1480>/Lookup Table1'
   * About '<S1480>/Lookup Table1 :'
   * Lookup Block: '<S1480>/Lookup Table1'
   * Input0  Data Type:  Integer        U8
   * Output0 Data Type:  Integer        U8
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U8_U8( &(local_LookupTable1), (&(CUR_Customer_Inf[0])), ((uint8_T)1U),
               (&(CUR_Customer_Index[0])), 17U);

  /* Lookup Block: '<S1480>/CUR_WetFl_Ldp'
   * About '<S1480>/CUR_WetFl_Ldp :'
   * Lookup Block: '<S1480>/CUR_WetFl_Ldp'
   * Input0  Data Type:  Fixed Point    U16  2^-6  FSlope 1.5
   * Output0 Data Type:  Fixed Point    U16  2^-3  FSlope 1.5
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U16_U16( &(local_CUR_WetFl_Ldp), (&(RAM_CUR_Wf_Ldp[0])), 853U, (&(BP_Wf_Ldp
    [0])), 17U);

  /* Lookup Block: '<S1480>/CUR_fWmp_Tm'
   * About '<S1480>/CUR_fWmp_Tm :'
   * Lookup Block: '<S1480>/CUR_fWmp_Tm'
   * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
   * Output0 Data Type:  Fixed Point    U8  2^-7
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U8_U8( &(local_CUR_fWmp_Tm), (&(RAM_CUR_fWmp_Tm[0])), ((uint8_T)104U),
               (&(BP_fWmp_Tm[0])), 11U);

  /* Lookup Block: '<S1480>/CUR_fWmp_Tm1'
   * About '<S1480>/CUR_fWmp_Tm1 :'
   * Lookup Block: '<S1480>/CUR_fWmp_Tm1'
   * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
   * Output0 Data Type:  Fixed Point    U8  2^-5
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U8_U8( &(local_CUR_fWmp_Tm1), (&(RAM_CUR_fAst_TmSta[0])), ((uint8_T)104U),
               (&(BP_fAst_TmSta[0])), 11U);

  /* Lookup2D Block: '<S1480>/Lookup Table (2-D)1'
   * About '<S1480>/Lookup Table (2-D)1 :'
   * Lookup2D Block: '<S1480>/Lookup Table (2-D)1'
   * Input0  Data Type:  Fixed Point    U16  2^-2
   * Input1  Data Type:  Fixed Point    U16  2^-5  FSlope 1.25
   * Output0 Data Type:  Fixed Point    U16  2^-15
   * Lookup Method: Linear_Endpoint
   *
   * Row Data    parameter uses the same data type and scaling as Input0
   * Column Data parameter uses the same data type and scaling as Input1
   * Table Data  parameter uses the same data type and scaling as Output0


   */
  Look2D_U16_U16_U16( &(local_LookupTable2D1), (&(RAM_MAP_fVe_Map_N[0])), 8000U,
                     (&(BP_fVe_N[0])), 11U, 12800U, (&(BP_fVe_Map[0])), 15U);

  /* Lookup2D Block: '<S1480>/Lookup Table (2-D)'
   * About '<S1480>/Lookup Table (2-D) :'
   * Lookup2D Block: '<S1480>/Lookup Table (2-D)'
   * Input0  Data Type:  Fixed Point    U16  2^-10  FSlope 1.5625
   * Input1  Data Type:  Fixed Point    U16  2^-2
   * Output0 Data Type:  Fixed Point    U16  2^-6  FSlope 1.5
   * Lookup Method: Linear_Endpoint
   *
   * Row Data    parameter uses the same data type and scaling as Input0
   * Column Data parameter uses the same data type and scaling as Input1
   * Table Data  parameter uses the same data type and scaling as Output0


   */
  Look2D_U16_U16_U16( &(local_LookupTable2D), (&(RAM_MAP_LdTp_Tps_N[0])), 0U,
                     (&(BP_LdTp_Tps[0])), 15U, 8000U, (&(BP_LdTp_N[0])), 11U);

  /* Lookup2D Block: '<S1480>/Lookup Table (2-D)2'
   * About '<S1480>/Lookup Table (2-D)2 :'
   * Lookup2D Block: '<S1480>/Lookup Table (2-D)2'
   * Input0  Data Type:  Fixed Point    U8  2^5  FSlope 1.875
   * Input1  Data Type:  Fixed Point    U8  2^-1  FSlope 1.5
   * Output0 Data Type:  Fixed Point    S8  2^-1  FSlope 1.5
   * Lookup Method: Linear_Endpoint
   *
   * Row Data    parameter uses the same data type and scaling as Input0
   * Column Data parameter uses the same data type and scaling as Input1
   * Table Data  parameter uses the same data type and scaling as Output0


   */
  Look2D_S8_U8_U8( &(local_LookupTable2D2), (&(RAM_MAP_Iga_N_Ld[0])), ((uint8_T)17U),
                  (&(BP_Iga_N[0])), 15U, ((uint8_T)27U), (&(BP_Iga_Ld[0])), 10U);

  /* Lookup2D Block: '<S1480>/Lookup Table (2-D)3'
   * About '<S1480>/Lookup Table (2-D)3 :'
   * Lookup2D Block: '<S1480>/Lookup Table (2-D)3'
   * Input0  Data Type:  Fixed Point    U16  2^-2
   * Input1  Data Type:  Fixed Point    U16  2^-5  FSlope 1.25
   * Output0 Data Type:  Fixed Point    U16  2^-14
   * Lookup Method: Linear_Endpoint
   *
   * Row Data    parameter uses the same data type and scaling as Input0
   * Column Data parameter uses the same data type and scaling as Input1
   * Table Data  parameter uses the same data type and scaling as Output0


   */
  Look2D_U16_U16_U16( &(local_LookupTable2D3), (&(MAP_fAlt_N_Pam[0])), 8000U,
                     (&(BP_fAlt_N[0])), 7U, 25933U, (&(BP_fAlt_Pam[0])), 7U);
  isLLDCal = ((VAL_UseMapLowestForLd || VAL_NmaxFastSynByMapDrop ||
               VAL_uMapDropIntkMin || VAL_uMapDropVerifyInSyn || VAL_KickStartEn||
               VAL_tSegMin_KickStartEn || VAL_tInjIdleEst || VAL_tInj2CSplitLow ||
               VAL_tInj2CSplitUp || VAL_dInjAngGap2TdcAdj || VAL_tInjBrkMin ||
               VAL_dIgaGap2TdcAdj || VAL_CDI_pulse_width || VAL_FreqWg ||
               VAL_Map_Sensor_Location_Y_Manifold) || ((VAL_nTeethTot != 0U) ||
               (VAL_nTeethMiss != 0U) || (VAL_ToothTDC != 0U) ||
    (VAL_OfsTDC2ToothEdge != 0) || (VAL_RM0_tooth != 0U) || (VAL_RM2_tooth != 0U)
    || VAL_ToothDetByRiseEdge || (VAL_toothDebncTime != 0U) ||
    (VAL_MaxErrTeethPerCyc != 0U) || (VAL_toothMapDropStart != 0U) ||
    (VAL_toothIntkVlvClos != 0U) || (VAL_tooth_level_verify_counter != 0U) ||
    (VAL_tooth_level_verify_interval != 0U) ||
    (VAL_tooth_level_verify_counter_success != 0U) || (VAL_tooth_high_time_max
    != 0UL) || (VAL_tooth_high_time_min != 0U) || (VAL_tooth_low_time_max != 0UL)
    || (VAL_tooth_low_time_min != 0U) || (VAL_toothMapDropEnd != 0U)) ||
              ((VAL_Phase_Detector != 0U) || (VAL_toothCamRisingEdge != 0U) ||
               (VAL_toothCamFallingEdge != 0U) || (VAL_CamToothLevel != 0U) ||
               (VAL_cntCamToothLevelDebounce != 0U) || (VAL_CKP_Pulse_Polarity
    != 0U) || (VAL_Ign1_Per_360Deg != 0U) || (VAL_nTeethWheel != 0U) ||
               (VAL_nTeethBtw2Tdcs != 0U) || VAL_ignore_second_tooth_enable ||
               (VAL_ignore_second_tooth_x_apart != 0U) ||
               VAL_use_second_tooth_enable || (VAL_use_second_tooth_x_apart !=
    0U) || (VAL_N_low_use_second_tooth != 0U)) || ((VAL_tAftRunMx != 0U) ||
    (VAL_tEngOffMx != 0U) || (VAL_dIgaIdcMax != 0) || (VAL_dIgaIdcMin != 0) ||
    (VAL_tInjPick != 0U) || (VAL_tInjHoldOn != 0U) || (VAL_tInjHoldOff != 0U) ||
               (VAL_nInjPerCyl != 0U) || (VAL_ECU_Passwd != 0UL) ||
    (VAL_stepper_position_max != 0U) || (VAL_stepper_position_min != 0U) ||
    (VAL_stepper_position_delta != 0U) || (VAL_stepper_position_ctrl_max != 0) ||
               (VAL_stepper_position_ctrl_min != 0)) ||
              ((VAL_V2_450_N1_Start_Tooth || VAL_V2_450_N2_Start_Tooth ||
                VAL_V2_450_DeltaTooth || VAL_RM3_tooth || VAL_RM4_tooth ||
                VAL_ToothTDC2 || VAL_ToothTDC3 || VAL_ToothTDC4 ||
                VAL_Number_Of_Fuel_Channels_Per_Cylinder ||
                VAL_Number_Of_Spark_Channels || VAL_Blind_spark_delay_time ||
                VAL_IgaOut_Init_Value || VAL_Blind_Inj_Times ||
                VAL_McDashpotInitValue || VAL_McDashpot_DeltaDecrements ||
                VAL_McDashpot_TpsCondition || VAL_McDashpot_NCondition ||
                VAL_Customer_Counter || VAL_dTpsTpBlip_Min ||
                VAL_dtInjTpBlip_Min || VAL_dtInjTpBlip_Max || VAL_NTpBlip_Max ||
                VAL_SelfLearnTabEn || VAL_SLM_dTpsStableMin ||
                VAL_SLM_dNStableMin || VAL_SLM_dFactorStableMin ||
                VAL_SLM_StableCounterGoal || VAL_SLM_AN_N2LdRaw ||
                VAL_SLM_AN_Tps2LdRaw || VAL_SLM_PN_Map2LdRaw ||
                VAL_SLM_PN_N2LdRaw || VAL_dIgaMn_Nidl || VAL_ddIgaMn_Nidl ||
                VAL_dNidlUp_IgaMn || VAL_NidlUp_IgaMn) || ((VAL_tIgaMn_Nidl !=
    0U) || (VAL_dIgaRmp_Nidl != 0) || (VAL_MPIDC_PGain != 0) ||
    (VAL_MPIDC_TConst != 0) || (VAL_MPIDC_Delay != 0U) || (VAL_MPIDC_P_Part_Min
    != 0) || (VAL_MPIDC_P_Part_Max != 0) || (VAL_MPIDC_PID_Min != 0U) ||
    (VAL_MPIDC_PID_Max != 0U) || (VAL_MPIDC_D_Part_Min != 0) ||
    (VAL_MPIDC_D_Part_Max != 0) || (VAL_MPIDC_DGain != 0) ||
    (VAL_MPIDC_dNmin_Ipart != 0) || (CV_LampOutSelect != 0U)) ||
               ((VAL_CAN0_BaudRate != 0U) || (VAL_GapDetector != 0U) ||
                (VAL_rTooth_P1_P != 0U) || (VAL_rTooth_P2_P != 0U) ||
                (VAL_rTooth_P1_P3 != 0U) || (VAL_rTooth_P2_P3 != 0U) ||
                (VAL_ServoPWMPeriod != 0U) || (VAL_ServoPWMHighLevelMx != 0U) ||
                (VAL_ServoPWMHighLevelMn != 0U) || (VAL_ServoNoiseWidthMx != 0U)))
              || (((VAL_UAVCAN_RxID != 0UL) || (VAL_CCP_RxID != 0UL) ||
                   (VAL_WBO2_CAN_RxID != 0UL)) || (local_LookupTable1 ||
    local_CUR_WetFl_Ldp || local_CUR_fWmp_Tm || RAM_VAL_fFlApp ||
    local_CUR_fWmp_Tm1) || (local_LookupTable2D1 || local_LookupTable2D ||
    local_LookupTable2D2 || local_LookupTable2D3)));
  ALM_lsuTemp_FromCAN = 42496U;
  ALM_lsuDTC_FromCAN = 0U;
  ALM_lsuO2_FromCAN = 6554;
  ALM_lsuHtDtcy_FromCAN = 6554U;

  /* user code (Update function Body) */
  /* System '<S13>/iniSyn' */
  Fl = 0;
  FlTrsCr = 0;
  tInj0 = 0;
  nInj = 0;
  nInj_b = 0;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S845>/iniSyn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FL2TI_iniSyn(void)
{
  /* local block i/o variables */
  uint16_T local_Product2;

  {
    uint32_T temp_tmp;
    uint16_T temp_tmp_0;
    local_Product2 = VAL_vEng;
    temp_tmp = div_u32((uint32_T)VAL_StoicAFR << 14U, 15053UL);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = (((uint32_T)VAL_Qstat * (uint32_T)temp_tmp_0) >> 14);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = (((uint32_T)temp_tmp_0 * (uint32_T)VAL_fQstatCr) >> 14);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = div_u32((uint32_T)local_Product2 << 13U, (uint32_T)temp_tmp_0);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    fFl2TiStat = temp_tmp_0;
    temp_tmp = div_u32((uint32_T)VAL_StoicAFR2 << 14U, 15053UL);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = (((uint32_T)VAL_Qstat2 * (uint32_T)temp_tmp_0) >> 14);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = (((uint32_T)temp_tmp_0 * (uint32_T)VAL_fQstatCr2) >> 14);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    temp_tmp = div_u32((uint32_T)local_Product2 << 13U, (uint32_T)temp_tmp_0);
    if (temp_tmp > 65535UL) {
      temp_tmp_0 = MAX_uint16_T;
    } else {
      temp_tmp_0 = (uint16_T)temp_tmp;
    }

    fFl2TiStat2 = temp_tmp_0;
  }
}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S750>/iniSyn' */
#define START_SECTION_r50msCode
#include "pragma.h"

void FLAST_iniSyn(void)
{
  UD_fWmp1 = MAX_uint8_T;
  UD_B_WmpEnd = 0U;
  ER_B_Syn_Ast = 0U;
}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Start for function-call system: '<S1490>/sm_task_iniSyn' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_iniSyn_Start(void)
{
  SWADP_iniSyn_Start();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1490>/sm_task_iniSyn' */
void tasks_iniSyn(void)
{
  /*  */
  SWADP_iniSyn();
  CSIMM_iniSyn();
  FLSTA_iniSyn();
  FLAST_iniSyn();
  FL2TI_iniSyn();
}

/* Output and update for function-call system: '<S182>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void CSN_ini2(void)
{
  /* user code (Update function Body) */
  /* System '<S182>/ini2' */
  B_NMn= 1;
  B_N= 0;
  tSeg_l= 4294967295;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S292>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSTPS_ini2(void)
{
  {
    uint16_T temp_tmp;
    uint32_T temp_tmp_0;
    if (E_Tps || B_Pwf) {
      temp_tmp = VAL_uTpsWot - VAL_duTpsWot;
      if (temp_tmp > VAL_uTpsWot) {
        temp_tmp = 0U;
      }

      temp_tmp_0 = (((uint32_T)temp_tmp * (uint32_T)4096U) >> 8);
      if (temp_tmp_0 > 65535UL) {
        temp_tmp = MAX_uint16_T;
      } else {
        temp_tmp = (uint16_T)temp_tmp_0;
      }

      TpsWotIni = temp_tmp;
      temp_tmp_0 = (uint32_T)VAL_uTpsIdl + (uint32_T)VAL_duTpsIdl;
      if (temp_tmp_0 > 65535UL) {
        temp_tmp = MAX_uint16_T;
      } else {
        temp_tmp = (uint16_T)temp_tmp_0;
      }

      temp_tmp_0 = (((uint32_T)temp_tmp * (uint32_T)4096U) >> 8);
      if (temp_tmp_0 > 65535UL) {
        temp_tmp = MAX_uint16_T;
      } else {
        temp_tmp = (uint16_T)temp_tmp_0;
      }

      TpsIdlIni = temp_tmp;
    }

    TOnD_uTpsHeal = VAL_tdTpsHeal;

    /* user code (Update function Body) */
    /* System '<S292>/ini2' */
    TpsRaw = (uint16_T)(((uint32_T)uTps * (uint32_T)4096) >> 8);
    if (B_Pwf || E_Tps) {
      TpsWot = TpsWotIni;
      TpsIdl = TpsIdlIni;
    }

    LPT_TpsWOT_U32 = (uint32_T)TpsWot<<16;
    LPT_SSTPS1_U32= (uint32_T)TpsIdl<<16;
    UD_SSTPS_TpsIdlOld = TpsIdl;
    UD_SSTPS_TpsIdl = TpsIdl;
    TppIdlOldMn = TpsIdl;
    UD_TpsWot = TpsWot;
    UD_TpsWotOld = TpsWot;
    TpsWotOldMx = TpsWot;
  }
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S249>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSMAP_ini2(void)
{
  /* local block i/o variables */
  uint8_T local_FixPtBitwiseOperator_e;
  if (((uMap > VAL_uMapMx) || (uMap < VAL_uPamMn)) == 0) {
    MapIni = (uint16_T)((int16_T)(((uint32_T)(uMap << 4U) * (uint32_T)
      VAL_PmapGrd) >> 15) + VAL_PmapOfs);
  } else {
    MapIni = 25933U;
  }

  /*  */

  /* Bitwise Block: '<S254>/FixPt Bitwise Operator'
   * AND
   */
  local_FixPtBitwiseOperator_e = (CV_SSMAP) & ((((uint8_T)16U)));

  /*  */
  isMap2Cyl = (!(boolean_T)(local_FixPtBitwiseOperator_e != 0U ? 1U : 0U)) ||
    VAL_duMapDrp2CylSyn;
  TOnD_uMapHeal = VAL_tdMapHeal;

  /* user code (Update function Body) */
  /* System '<S249>/ini2' */
  Map= MapIni;
  Map_b= MapIni>>8;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S352>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSTM_ini2(void)
{
  /* local block i/o variables */
  uint16_T local_LPT_Out;

  /* Lookup Block: '<S353>/Lookup Table1'
   * About '<S353>/Lookup Table1 :'
   * Lookup Block: '<S353>/Lookup Table1'
   * Input0  Data Type:  Fixed Point    U16  2^-10  FSlope 1.25
   * Output0 Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U8_U16( &(Tmini), (&(CUR_Tm_uTm[0])), uTm, (&(BP_Tm_uTm[0])), 17U);

  /* Output and update for atomic system: '<S353>/LPT_W_IV_E' */
  LPT_SSTM_TmBfFil = ((uint16_T)Tmini << 8U);
  local_LPT_Out = LPT_SSTM_TmBfFil;

  /*  */
  local_LPT_Out = LowPassT_U8( local_LPT_Out, Tmini, ((uint8_T)25U));
  TOfD_SSTM_Heal = VAL_tdTmHeal;

  /* user code (Update function Body) */
  /* System '<S352>/ini2' */
  Tm= Tmini;
  TmSta= Tmini;
  TmLin = Tmini;
  TOnD_SSTM1= VAL_tdTmErr;
  TOnD_SSTM_B_TmBak= VAL_tdTmErr;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S400>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSTA_ini2(void)
{
  /* Lookup Block: '<S401>/Lookup Table'
   * About '<S401>/Lookup Table :'
   * Lookup Block: '<S401>/Lookup Table'
   * Input0  Data Type:  Fixed Point    U16  2^-10  FSlope 1.25
   * Output0 Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_U8_U16( &(Taini), (&(CUR_Ta_uTa[0])), uTa, (&(BP_Ta_uTa[0])), 13U);
  TOfD_SSTA_Heal = VAL_tdTaHeal;

  /* user code (Update function Body) */
  /* System '<S400>/ini2' */
  TOnD_SSTA_StaEnd= VAL_tdAstTaDg;
  TOnD_SSTA1= VAL_tdTaErrIdl;
  TOnD_SSTA2= VAL_tdTaDg;
  TOnD_SSTA3= VAL_tdTaDg;
  Ta= Taini;
  LPT_SSTA1 = (uint16_T) Taini<<8;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S437>/ini2' */
#define START_SECTION_InitCode
#include "pragma.h"

void SSUB_ini2(void)
{
  if ((uint8_T)(UbAdc >> 4) < VAL_UbMnAdc) {
    UbAdcIni = VAL_UbAdcBak;
  } else {
    UbAdcIni = UbAdc;
  }

  TOfD_SSUB_Heal = VAL_tdUbHeal;

  /* user code (Update function Body) */
  /* System '<S437>/ini2' */
  Ub_b= UbAdcIni>>4;
  B_UbNpl = (UbAdc < VAL_UbMnAdc);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S566>/ini2' */
void CSFTM_ini2(void)
{
  {
    /* user code (Update function Header) */
    /* System '<S566>/ini2' */
    uint16_T local_Add3;
    uint32_T temp_tmp;
    uint16_T temp_tmp_0;

    /* user code (Update function Body) */
    /* System '<S566>/ini2' */
    LPT_CSFTM_TmFlt = Tm<<8;
    LPT_CSFTM_TmEndMod = Tm<<8;
    TinvMod = Tm;
    local_Add3 = ((uint16_T)TinvMod + 364U) - 64U;
    temp_tmp = (uint32_T)local_Add3;
    fTcmb = (uint16_T)((uint32_T)(uint16_T)(temp_tmp == (uint32_T)0 ?
      MAX_uint32_T : (uint32_T)(23855104UL / temp_tmp)) );
    fTcmb_b = (uint8_T)(fTcmb >> 8);
    fTim = (uint8_T)(0 ? MAX_uint32_T : (uint32_T)(((uint32_T)(((uint16_T)Ta +
      364U) - 64U) << 5U) / 91UL));
    temp_tmp_0 = ((uint16_T)Ta + 364U) - 64U;
    fTbtp = (uint8_T)(temp_tmp_0 == (uint16_T)0 ? MAX_uint16_T : (uint16_T)
                      (46592U / temp_tmp_0));
  }
}

/* Output and update for function-call system: '<S649>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void CSIMM_ini2(void)
{
  /* local block i/o variables */
  uint32_T local_LPT_Out_n;

  /* Output and update for atomic system: '<S650>/LPT_W_IV' */
  LPT_fVeRaw = 2147483648UL;
  local_LPT_Out_n = LPT_fVeRaw;

  /*  */
  local_LPT_Out_n = LowPassT_U16( local_LPT_Out_n, 32768U, VAL_tcfVeRaw);

  /* user code (Update function Body) */
  /* System '<S649>/ini2' */
  Pim= Pam;
  PimMod= Pam;
  Pim_b= (uint8_T)(Pim>>8);
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S575>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void CSPAM_ini2(void)
{
  Count_CSPAM_PamAdp = 0U;
  TOfD_CSPAM_Heal = VAL_tdPamHeal;
  CSPAM_BitField.RSFF_CSPAM_DisPamAdpSta = 1U;

  {
    /* user code (Update function Header) */
    /* System '<S575>/ini2' */

    /* user code (Update function Body) */
    /* System '<S575>/ini2' */
    B_AltAdp= TRUE;
    if (E_Map) {
      LPT_CSPAM_Pam_U32= ((uint32_T)VAL_PamSubErr)<<24;
    } else {
      if (B_Pwf) {
        LPT_CSPAM_Pam_U32= ((uint32_T)Map)<<16;
      } else {
        LPT_CSPAM_Pam_U32= ((uint32_T)Pam)<<16;
      }
    }

    Pam= (uint16_T)(LPT_CSPAM_Pam_U32>>16);
    Pam_b= (uint8_T)(Pam >> 8);
    Pbtp= Pam;
    Pbtp_b= Pam_b;
    fAlt= (uint16_T)((((uint32_T)Pam << 14U)/25933));
    fPbtp= fAlt;
    fAlt_b= (uint8_T)(fAlt>>8);
    fPbtp_b= fAlt_b;
  }
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S922>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void IGSTA_ini2(void)
{
  /* Lookup Block: '<S923>/CUR_IgaSta_TmSta'
   * About '<S923>/CUR_IgaSta_TmSta :'
   * Lookup Block: '<S923>/CUR_IgaSta_TmSta'
   * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
   * Output0 Data Type:  Fixed Point    S8  2^-1  FSlope 1.5
   * Lookup Method: Linear_Endpoint
   *
   * XData parameter uses the same data type and scaling as Input0
   * YData parameter uses the same data type and scaling as Output0


   */
  LookUp_S8_U8( &(IgaStaIni), (&(CUR_IgaSta_TmSta[0])), TmSta,
               (&(BP_IgaSta_TmSta[0])), 5U);

  /* user code (Update function Body) */
  /* System '<S922>/ini2' */
  IgaSta = IgaStaIni;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S953>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void ESTM_ini2(void)
{
  /* user code (Update function Body) */
  /* System '<S953>/ini2' */
  if (B_Pwf) {
    tSokEstm = 65535;
    B_LsbDewLst = 0;
    TexBfCatOff = (uint8_T)(((uint16_T)Ta * 205U) >> 10);
    TcatMainOff = TexBfCatOff;
    nDewNotLsb = 6;
  }

  UD_tSok1 = tSokEstm;
  nDewNotLsbOld = nDewNotLsb;
  UD_TaTam = Ta;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S1293>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void DSM_ini2(void)
{
  /* local block i/o variables */
  uint16_T local_DSRead_e;
  uint16_T local_DSRead_f;
  uint16_T local_DSRead_m;
  uint16_T local_DSRead_go;
  uint16_T local_DSRead_mt;
  uint16_T local_DSRead_gl;
  uint16_T local_DSRead_b;
  uint16_T local_DSRead_k;
  uint16_T local_DSRead_k3;
  uint16_T local_DSRead_o;
  uint16_T local_DSRead_a;
  uint16_T local_DSRead_gy;
  if (B_Pwf) {
    FcmTps = 512U;
    FcmMap = 256U;
    FcmTilt = 3072U;
    FcmPam = 2816U;
    FcmTa = 1024U;
    FcmCrk = 768U;
    FcmUb = 1536U;
    FcmTm = 1280U;
    FcmLsb = 2048U;
    FcmBaro = 2560U;
    FcmLsu = 1792U;
    FcmLsb2 = 2304U;
  }

  /* Output and update for enable system: '<S1294>/FCM1' */
  local_DSRead_gy = FcmTps;
  FcmTps = (~((~local_DSRead_gy) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM2' */
  local_DSRead_k = FcmMap;
  FcmMap = (~((~local_DSRead_k) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM11' */
  local_DSRead_o = FcmBaro;
  FcmBaro = (~((~local_DSRead_o) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM12' */
  local_DSRead_k3 = FcmLsu;
  FcmLsu = (~((~local_DSRead_k3) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM3' */
  local_DSRead_b = FcmTm;
  FcmTm = (~((~local_DSRead_b) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM4' */
  local_DSRead_gl = FcmUb;
  FcmUb = (~((~local_DSRead_gl) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM5' */
  local_DSRead_mt = FcmTa;
  FcmTa = (~((~local_DSRead_mt) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM6' */
  local_DSRead_go = FcmPam;
  FcmPam = (~((~local_DSRead_go) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM7' */
  local_DSRead_m = FcmLsb;
  FcmLsb = (~((~local_DSRead_m) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM8' */
  local_DSRead_f = FcmTilt;
  FcmTilt = (~((~local_DSRead_f) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM9' */
  local_DSRead_e = FcmLsb2;
  FcmLsb2 = (~((~local_DSRead_e) | (2U)));

  /* Output and update for enable system: '<S1294>/FCM10' */
  local_DSRead_a = FcmCrk;
  FcmCrk = (~((~local_DSRead_a) | (2U)));
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S488>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSFLAM_ini2(void)
{
  /* user code (Update function Body) */
  /* System '<S488>/ini2' */
  fLamDrv = 65536>>4;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S85>/ini2' */
void IDCSTP_ini2(void)
{
  /* local block i/o variables */
  uint16_T local_IndexVector;
  uint16_T local_LookupTable2D_h;
  uint16_T local_Product_h;
  uint16_T local_LookupTable1_g;
  boolean_T local_step_con;
  boolean_T local_RSFF_DSRead_l;
  boolean_T local_S_a;
  boolean_T local_DataStoreRead1_g;
  boolean_T local_RSFF_Q;
  uint8_T local_LookupTable2D2_g;
  B_StpDgInhLow = (Ub_b <= VAL_UbStepMn);
  B_StepOff = (Ub_b >= VAL_UbStepMx);
  B_AfrIni = TRUE;
  if (B_Pwf) {
    StepPosDsr = 0U;
    IDCSTP_BitField.RSFF_IDCSTP_StpLrn = 1U;
    B_StepLrn = 1U;
  } else {
    B_StepPrePos = TRUE;
    if (!B_StepLrn) {
      if (B_StepLrn) {
        StepPosDsr = 0U;
      } else {
        /* Output and update for action system: '<S97>/ELSE_IsCalStepDsr_Ini' */
        local_DataStoreRead1_g = B_StepPosMx;
        local_RSFF_DSRead_l = IDCSTP_BitField.RSFF_IDCSTP_StpCon;
        if (B_NMn) {
          local_RSFF_Q = 0U;
        } else {
          /* Lookup Block: '<S102>/Lookup Table1'
           * About '<S102>/Lookup Table1 :'
           * Lookup Block: '<S102>/Lookup Table1'
           * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
           * Output0 Data Type:  Fixed Point    U16  2^-2
           * Lookup Method: Linear_Endpoint
           *
           * XData parameter uses the same data type and scaling as Input0
           * YData parameter uses the same data type and scaling as Output0


           */
          LookUp_U16_U8( &(local_LookupTable1_g), (&(CUR_NDsrStepPos_Tm[0])), Tm,
                        (&(BP_NDsrStepPos_Tm[0])), 5U);
          if (N >= local_LookupTable1_g) {
            local_S_a = 1U;
          } else {
            local_S_a = local_RSFF_DSRead_l;
          }

          local_RSFF_Q = local_S_a;
        }

        IDCSTP_BitField.RSFF_IDCSTP_StpCon = local_RSFF_Q;
        local_step_con = ((!local_RSFF_Q) || B_Afr || B_StepPrePos);

        /* Lookup2D Block: '<S99>/Lookup Table (2-D)'
         * About '<S99>/Lookup Table (2-D) :'
         * Lookup2D Block: '<S99>/Lookup Table (2-D)'
         * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
         * Input1  Data Type:  Fixed Point    U16  2^-2
         * Output0 Data Type:  Integer        U16
         * Lookup Method: Linear_Endpoint
         *
         * Row Data    parameter uses the same data type and scaling as Input0
         * Column Data parameter uses the same data type and scaling as Input1
         * Table Data  parameter uses the same data type and scaling as Output0


         */
        Look2D_U16_U8_U16( &(local_LookupTable2D_h), (&(MAP_StepPrePos_Tm_N[0])),
                          Tm, (&(BP_StepPrePos_Tm[0])), 14U, N,
                          (&(BP_StepPrePos_N[0])), 1U);

        /* Lookup2D Block: '<S99>/Lookup Table (2-D)2'
         * About '<S99>/Lookup Table (2-D)2 :'
         * Lookup2D Block: '<S99>/Lookup Table (2-D)2'
         * Input0  Data Type:  Fixed Point    U8  FSlope 1.25  Bias -40
         * Input1  Data Type:  Fixed Point    U8  2^-6
         * Output0 Data Type:  Fixed Point    U8  2^-7
         * Lookup Method: Linear_Endpoint
         *
         * Row Data    parameter uses the same data type and scaling as Input0
         * Column Data parameter uses the same data type and scaling as Input1
         * Table Data  parameter uses the same data type and scaling as Output0


         */
        Look2D_U8_U8_U8( &(local_LookupTable2D2_g), (&(MAP_fStepPos_Ta_fAlt[0])),
                        Ta, (&(BP_fStepPos_Ta[0])), 5U, fAlt_b,
                        (&(BP_fStepPos_fAlt[0])), 5U);

        {
          uint32_T temp_tmp;
          temp_tmp = (((uint32_T)local_LookupTable2D_h * (uint32_T)
                       local_LookupTable2D2_g) >> 7);
          if (temp_tmp > 65535UL) {
            local_IndexVector = MAX_uint16_T;
          } else {
            local_IndexVector = (uint16_T)temp_tmp;
          }

          if (local_step_con == 0) {
          }

          if (local_DataStoreRead1_g == 0) {
            if (B_StepPosMn == 0) {
              local_Product_h = local_IndexVector;
            } else {
              local_Product_h = VAL_StepPosMn;
            }
          } else {
            local_Product_h = VAL_StepPosMx;
          }

          StepPosDsr = local_Product_h;
          B_StepPosMx = (local_IndexVector >= VAL_StepPosMx);
          B_StepPosMn = (local_IndexVector <= VAL_StepPosMn);
        }
      }
    } else {
      if ((!B_StepLrnAfr) && (!B_StepLrnEndAfr)) {
        StepPosDsr = 0U;
        IDCSTP_BitField.RSFF_IDCSTP_StpLrn = 1U;
      } else {
        B_StepLrn = FALSE;
      }
    }
  }
}

/* Output and update for function-call system: '<S213>/ini2' */
#define START_SECTION_Ini2Code
#include "pragma.h"

void SSBARO_ini2(void)
{
  /* local block i/o variables */
  uint32_T local_LPT_Out_d;
  if (((uBaro > VAL_uBaroMx) || (uBaro < VAL_uBaroMn)) == 0) {
    BaroIni = (uint16_T)((int16_T)(((uint32_T)(uBaro << 4U) * (uint32_T)
      VAL_BaroSlope) >> 15) + VAL_BaroOfs);
  } else {
    BaroIni = 25933U;
  }

  /* Output and update for atomic system: '<S214>/LPT_W_IV' */
  LPT_Baro_U32 = ((uint32_T)BaroIni << 16U);
  local_LPT_Out_d = LPT_Baro_U32;

  /*  */
  local_LPT_Out_d = LowPassT_U16( local_LPT_Out_d, BaroIni, VAL_tBaroFil);
  TOnD_uBaroHeal = VAL_tdBaroHeal;

  /* user code (Update function Body) */
  /* System '<S213>/ini2' */
  Baro= BaroIni;
  Baro_b= BaroIni>>8;
}

#define STOP_SECTION_Ini2Code
#include "pragma.h"

/* Output and update for function-call system: '<S740>/ini2' */
#define START_SECTION_InitCode
#include "pragma.h"

void FLSTA_ini2(void)
{
  /* user code (Update function Body) */
  /* System '<S740>/ini2' */
  fFlSta = 2048;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1489>/sm_task_ini2' */
void tasks_ini2(void)
{
  /*  */
  DSM_ini2();
  CSN_ini2();
  SSTPS_ini2();
  SSMAP_ini2();
  SSTM_ini2();
  SSTA_ini2();
  SSUB_ini2();
  SSFLAM_ini2();
  SSBARO_ini2();
  CSPAM_ini2();
  CSFTM_ini2();
  IDCSTP_ini2();
  CSIMM_ini2();
  FLSTA_ini2();
  IGSTA_ini2();
  ESTM_ini2();
}

/* Start for function-call system: '<S750>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void FLAST_syn_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S753>/fnswl_w' */
  fAstWmp = 4096U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S750>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FLAST_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Start for function-call system: '<S843>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSFL_syn_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S844>/Output2' */
  fPreCtl = 1024U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S843>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void CSFL_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Start for function-call system: '<S845>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void FL2TI_syn_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S845>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FL2TI_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S870>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FlANG_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S935>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void IGOUT_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Start for function-call system: '<S649>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSIMM_syn_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S649>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void CSIMM_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S13>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void SWADP_syn(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S249>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void SSMAP_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S182>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void CSN_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Start for function-call system: '<S683>/syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSLDP_syn_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S683>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void CSLDP_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S772>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FLTRS_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S861>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void OFINJ_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S797>/syn' */
#define START_SECTION_r10msCode
#include "pragma.h"

void FLRSM_syn(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S897>/syn' */
#define START_SECTION_SynCode
#include "pragma.h"

void FLECO_syn(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Start for function-call system: '<S1491>/sm_tasks_syn' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_syn_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1491>/sm_tasks_syn' */
void tasks_syn(void)
{}

/* Output and update for function-call system: '<S249>/r1ms' */
#define START_SECTION_r1msCode
#include "pragma.h"

void SSMAP_r1ms(void)
{}

#define STOP_SECTION_r1msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1484>/sm_tasks_r1ms' */
void tasks_1ms(void)
{
  /*  */
  SSMAP_r1ms();
}

/* Output and update for function-call system: '<S182>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void CSN_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S292>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void SSTPS_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S437>/r10ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void SSUB_10ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S728>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void OCSTA_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S875>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void OFPMP_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S920>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGGRU_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S928>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGMIN_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S925>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGKNP_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S935>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGOUT_10ms(void)
{
  /* local block i/o variables */
  boolean_T local_S_e;
  if (!B_Fof) {
    B_IgaMin = 0U;
  } else {
    if (B_Fof) {
      local_S_e = 1U;
    } else {
      local_S_e = GenFast_BitField.RSFF_IGO_Fof;
    }

    B_IgaMin = local_S_e;
  }

  GenFast_BitField.RSFF_IGO_Fof = B_IgaMin;
}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Start for function-call system: '<S622>/r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSMAFTP_10ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S625>/Output5' */
  LdTp = 4267U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S622>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void CSMAFTP_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S617>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void CSTPP_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Start for function-call system: '<S683>/r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSLDP_10ms_Start(void)
{
  /* Start for enable system: '<S684>/S2 calculates predicted air flow into the intake manifold' */

  /* virtual outports code */

  /* (Virtual) Outport Block: '<S687>/Output2' */
  LdTpPrd = 4267U;

  /* virtual outports code */

  /* (Virtual) Outport Block: '<S684>/Output5' */
  LdTpPrd = 4267U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S683>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void CSLDP_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S772>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void FLTRS_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1293>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void DSM_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S953>/r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void ESTM_10ms(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S991>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void LSH_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Functions for block: '<S1115>/LC_SM' */
static void Controller_LC_active(void );
static void Controller_LC_active(void )
{}

/* Initial conditions for atomic system: '<S1115>/LC_SM' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_SM_Init(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for atomic system: '<S1115>/LC_SM' */
#define START_SECTION_r10msCode
#include "pragma.h"

void LC_SM(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Initial conditions for function-call system: '<S1113>/LC_r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_r10ms_Init(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Start for function-call system: '<S1113>/LC_r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_r10ms_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1113>/LC_r10ms' */
#define START_SECTION_SlowCode
#include "pragma.h"

void LC_r10ms(void)
{}

#define STOP_SECTION_SlowCode
#include "pragma.h"

/* Output and update for function-call system: '<S1086>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void LCEN_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S13>/_r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void SWADP_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S20>/r10ms' */
void LADRV_r10ms(void)
{}

/* Start for function-call system: '<S29>/r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LAMCO_r10ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S30>/Output4' */
  LamDsr = 4096U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S29>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void LAMCO_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S64>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGCOO_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S932>/r10ms' */
#define START_SECTION_SynCode
#include "pragma.h"

void IGOUT1_10ms(void)
{}

#define STOP_SECTION_SynCode
#include "pragma.h"

/* Output and update for function-call system: '<S38>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGPRE_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S48>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGNMX_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S55>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGFOF_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S798>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void OCFOFRSM_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Start for function-call system: '<S649>/r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSIMM_10ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S652>/Output3' */
  fPrs2Ld = 21565U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S649>/r10ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void CSIMM_10ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Output and update for function-call system: '<S42>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void IGASR_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S67>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void BPC_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S249>/r10ms' */
#define START_SECTION_r1msCode
#include "pragma.h"

void SSMAP_r10ms(void)
{}

#define STOP_SECTION_r1msCode
#include "pragma.h"

/* Output and update for function-call system: '<S85>/r10ms' */
void IDCSTP_r10ms(void)
{}

/* Output and update for function-call system: '<S163>/r10ms' */
void IACSOL_r10ms(void)
{}

/* Output and update for function-call system: '<S876>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void PWPUMP_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S575>/r10ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void CSPAM_10ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Output and update for function-call system: '<S529>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void OILP_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S539>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void OILP2_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S548>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void SERVO_r10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Initial conditions for function-call system: '<S1483>/sm_tasks_r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_10ms_Init(void)
{
  LC_r10ms_Init();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Start for function-call system: '<S1483>/sm_tasks_r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_10ms_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1483>/sm_tasks_r10ms' */
void tasks_10ms(void)
{}

/* Output and update for function-call system: '<S942>/r20ms' */
#define START_SECTION_r20msCode
#include "pragma.h"

void IGDWL_20ms(void)
{}

#define STOP_SECTION_r20msCode
#include "pragma.h"

/* Start for function-call system: '<S147>/r20ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void IDCND_r20ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S149>/Output1' */
  Nstat = ((uint8_T)200U);

  /* (Virtual) Outport Block: '<S149>/Output6' */
  NDsrIdc = ((uint8_T)140U);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S147>/r20ms' */
#define START_SECTION_r20msCode
#include "pragma.h"

void IDCND_r20ms(void)
{}

#define STOP_SECTION_r20msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1005>/r20ms' */
#define START_SECTION_r20msCode
#include "pragma.h"

void DLSB_r20ms(void)
{}

#define STOP_SECTION_r20msCode
#include "pragma.h"

/* Output and update for function-call system: '<S488>/r10ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void SSFLAM_10ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Start for function-call system: '<S472>/r20ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void SSVSP_r20ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S473>/Out6' */
  B_VspNul = TRUE;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S472>/r20ms' */
#define START_SECTION_r20msCode
#include "pragma.h"

void SSVSP_r20ms(void)
{}

#define STOP_SECTION_r20msCode
#include "pragma.h"

/* Start for function-call system: '<S1211>/r20ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void SSWO2_r20ms_Start(void)
{
  /* Start for enable system: '<S1212>/calculate Lambda actrual value' */

  /* virtual outports code */

  /* (Virtual) Outport Block: '<S1214>/TimDlyInj3' */
  LamWO2 = 4096U;

  /* virtual outports code */

  /* (Virtual) Outport Block: '<S1212>/TimDlyInj3' */
  LamWO2 = 4096U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1211>/r20ms' */
#define START_SECTION_r1msCode
#include "pragma.h"

void SSWO2_r20ms(void)
{}

#define STOP_SECTION_r1msCode
#include "pragma.h"

/* Start for function-call system: '<S1262>/r20ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LCADWB_r20ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S1265>/Out4' */
  fLc = 32768U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1262>/r20ms' */
#define START_SECTION_r20msCode
#include "pragma.h"

void LCADWB_r20ms(void)
{}

#define STOP_SECTION_r20msCode
#include "pragma.h"

/* Start for function-call system: '<S1486>/sm_tasks_r20ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_20ms_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1486>/sm_tasks_r20ms' */
void tasks_20ms(void)
{}

/* Start for function-call system: '<S740>/r50ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void FLSTA_r50ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S743>/fFlSta' */
  fFlSta = 2048U;
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S740>/r50ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void FLSTA_r50ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Output and update for function-call system: '<S875>/r50ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void OFPMP_50ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Start for function-call system: '<S1113>/LC_r50ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_r50ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S1116>/fTiCr2' */
  fLcIBas = ((uint8_T)4U);

  /* (Virtual) Outport Block: '<S1116>/fTiCr1' */
  fLcPBas = ((uint8_T)20U);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1113>/LC_r50ms' */
#define START_SECTION_SlowCode
#include "pragma.h"

void LC_r50ms(void)
{}

#define STOP_SECTION_SlowCode
#include "pragma.h"

/* Output and update for function-call system: '<S861>/r50ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void OFINJ_r50ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Output and update for function-call system: '<S488>/r50ms' */
#define START_SECTION_r50msCode
#include "pragma.h"

void SSFLAM_r50ms(void)
{}

#define STOP_SECTION_r50msCode
#include "pragma.h"

/* Start for function-call system: '<S1487>/sm_tasks_r50ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_50ms_Start(void)
{
  FLSTA_r50ms_Start();
  LC_r50ms_Start();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1487>/sm_tasks_r50ms' */
void tasks_50ms(void)
{}

/* Output and update for function-call system: '<S292>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void SSTPS_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S352>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void SSTM_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S400>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void SSTA_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S437>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void SSUB_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S728>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void OCSTA_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S922>/r10ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void IGSTA_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Start for function-call system: '<S566>/r100ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void CSFTM_100ms_Start(void)
{}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S566>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void CSFTM_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S772>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void FLTRS_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S991>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void LSH_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1005>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void DLSB_r100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Start for function-call system: '<S1113>/LC_r100ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_r100ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S1114>/TimDlyInj' */
  ffLcI = ((uint8_T)64U);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1113>/LC_r100ms' */
#define START_SECTION_SlowCode
#include "pragma.h"

void LC_r100ms(void)
{}

#define STOP_SECTION_SlowCode
#include "pragma.h"

/* Output and update for function-call system: '<S1086>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void LCEN_100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1165>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void LCADEN_r100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1262>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void LCADWB_r100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S876>/r100ms' */
#define START_SECTION_r10msCode
#include "pragma.h"

void PWPUMP_r100ms(void)
{}

#define STOP_SECTION_r10msCode
#include "pragma.h"

/* Output and update for function-call system: '<S798>/r100ms' */
#define START_SECTION_r100msCode
#include "pragma.h"

void OCFOFRSM_r100ms(void)
{}

#define STOP_SECTION_r100msCode
#include "pragma.h"

/* Output and update for function-call system: '<S213>/r100ms' */
#define START_SECTION_r1msCode
#include "pragma.h"

void SSBARO_r100ms(void)
{}

#define STOP_SECTION_r1msCode
#include "pragma.h"

/* Start for function-call system: '<S1482>/sm_tasks_r100ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_100ms_Start(void)
{
  CSFTM_100ms_Start();
  LC_r100ms_Start();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1482>/sm_tasks_r100ms' */
void tasks_100ms(void)
{}

/* Output and update for function-call system: '<S750>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void FLAST_200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Start for function-call system: '<S925>/r200ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void IGKNP_200ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S927>/Out2' */
  fIgaAlt = ((uint8_T)255U);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S925>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void IGKNP_200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Output and update for function-call system: '<S928>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void IGMIN_200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Output and update for function-call system: '<S953>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void ESTM_200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Start for function-call system: '<S147>/r200ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void IDCND_r200ms_Start(void)
{
  /* virtual outports code */

  /* (Virtual) Outport Block: '<S148>/Output1' */
  NdsrIdcTm = ((uint8_T)80U);
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S147>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void IDCND_r200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1171>/r200ms' */
#define START_SECTION_r200msCode
#include "pragma.h"

void LCAD_r200ms(void)
{}

#define STOP_SECTION_r200msCode
#include "pragma.h"

/* Start for function-call system: '<S1485>/sm_tasks_r200ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void tasks_200ms_Start(void)
{
  IGKNP_200ms_Start();
  IDCND_r200ms_Start();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Output and update for function-call system: '<S1485>/sm_tasks_r200ms' */
void tasks_200ms(void)
{}

/* Output and update for function-call system: '<S352>/r1000ms' */
#define START_SECTION_r1000msCode
#include "pragma.h"

void SSTM_1000ms(void)
{}

#define STOP_SECTION_r1000msCode
#include "pragma.h"

/* Output and update for function-call system: '<S400>/r1000ms' */
#define START_SECTION_r1000msCode
#include "pragma.h"

void SSTA_1000ms(void)
{}

#define STOP_SECTION_r1000msCode
#include "pragma.h"

/* Output and update for function-call system: '<S575>/r1000ms' */
#define START_SECTION_r1000msCode
#include "pragma.h"

void CSPAM_1000ms(void)
{}

#define STOP_SECTION_r1000msCode
#include "pragma.h"

/* Output and update for function-call system: '<S622>/r1000ms' */
#define START_SECTION_r1000msCode
#include "pragma.h"

void CSMAFTP_1000ms(void)
{}

#define STOP_SECTION_r1000msCode
#include "pragma.h"

/* Output and update for function-call system: '<S897>/r1s' */
#define START_SECTION_r1000msCode
#include "pragma.h"

void FLECO_r1s(void)
{}

#define STOP_SECTION_r1000msCode
#include "pragma.h"

/* Output and update for function-call system: '<S1481>/sm_tasks_r1000ms' */
void tasks_1000ms(void)
{}

/* Model step function */
void Controller_step(void)
{
  /* local block i/o variables */
  uint16_T local_PeriodSync;

  /* Output and update for atomic system: '<S1>/scheduler' */

  /* Output and update for atomic system: '<S4>/Scheduler' */
  {
    uint32_T temp_tmp;
    temp_tmp = (uint32_T)Nraw;
    local_PeriodSync = (uint16_T)(temp_tmp == (uint32_T)0 ? MAX_uint32_T :
      (uint32_T)(120000UL / temp_tmp));

    /*  */
    if (global_Controller_DWork._task_trigger_generator.temp_is_active_c10_Scheduler_li
         == 0) {
      global_Controller_DWork._task_trigger_generator.temp_is_active_c10_Scheduler_li
         = 1U;
      global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt = 0UL;
      global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib =
        (uint8_T)Controller_IN_DELAY;
    } else {
      switch
        (global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
         ) {
       case Controller_IN_AFTEER_RUN:
        if (global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt >=
            ((uint32_T)5000UL)) {
          global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
             = (uint8_T)Controller_IN_POWEROFF;
        } else {
          global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt++;
          if (global_Controller_DWork._task_trigger_generator.temp_Task1msCnt >=
              Controller_PERIOD_1ms) {
            tasks_1ms();
            global_Controller_DWork._task_trigger_generator.temp_Task1msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task1msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task2msCnt >=
              Controller_PERIOD_2ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task2msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task2msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task5msCnt >=
              Controller_PERIOD_5ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task5msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task5msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task10msCnt >=
              Controller_PERIOD_10ms) {
            tasks_10ms();
            global_Controller_DWork._task_trigger_generator.temp_Task10msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task10msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task20msCnt >=
              Controller_PERIOD_20ms) {
            tasks_20ms();
            global_Controller_DWork._task_trigger_generator.temp_Task20msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task20msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task50msCnt >=
              Controller_PERIOD_50ms) {
            tasks_50ms();
            global_Controller_DWork._task_trigger_generator.temp_Task50msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task50msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task100msCnt >=
              Controller_PERIOD_100ms) {
            tasks_100ms();
            global_Controller_DWork._task_trigger_generator.temp_Task100msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task100msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task200msCnt >=
              Controller_PERIOD_200ms) {
            tasks_200ms();
            global_Controller_DWork._task_trigger_generator.temp_Task200msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task200msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task500msCnt >=
              Controller_PERIOD_500ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task500msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task500msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt>=
              Controller_PERIOD_1000ms) {
            tasks_1000ms();
            global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt++;
          }
        }

        break;

       case Controller_IN_DELAY:
        if (global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt >=
            ((uint32_T)5UL)) {
          global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
             = (uint8_T)Controller_IN_POWERUP;
          global_Controller_B.IsKeyOn = Controller_true_n;
          tasks_ini();
          tasks_iniSyn();
          global_Controller_B.IsIni2 = Controller_true_n;
          tasks_ini2();
        } else {
          global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt++;
        }

        break;

       case Controller_IN_POWEROFF:
        global_Controller_B.IsAftRun = Controller_false_l;
        break;

       case Controller_IN_POWERUP:
        global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
           = (uint8_T)Controller_IN_RUN;

        /*  initializations  */
        global_Controller_B.IsIni2 = Controller_false_l;
        global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt = 1UL;
        global_Controller_B.IsSync = Controller_false_l;
        global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_SyncCnt = 1U;
        tasks_1ms();
        tasks_10ms();
        tasks_20ms();
        tasks_50ms();
        tasks_100ms();
        tasks_200ms();
        tasks_1000ms();
        global_Controller_DWork._task_trigger_generator.temp_Task1msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task2msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task5msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task10msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task20msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task50msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task100msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task200msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task500msCnt = 1U;
        global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt = 1U;
        break;

       case Controller_IN_RUN:
        if (global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt >=
            ((uint32_T)50000UL)) {
          global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
             = (uint8_T)Controller_IN_AFTEER_RUN;

          /*  initializations  */
          global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt = 1UL;
          global_Controller_B.IsSync = Controller_false_l;
          global_Controller_B.IsKeyOn = Controller_false_l;
          global_Controller_B.IsAftRun = Controller_true_n;
          global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_SyncCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task1msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task2msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task5msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task10msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task20msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task50msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task100msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task200msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task500msCnt = 1U;
          global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt =
            1U;
        } else {
          global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt++;
          if (!global_Controller_B.IsSync) {
            if (global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt
                 >= local_PeriodSync) {
              global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt =
                1U;
              global_Controller_B.IsSync = Controller_true_n;
              global_Controller_B.nInjSim = 1U;
              global_Controller_B.IsIgnSyn = Controller_true_n;
            } else {
              global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt
                ++;
            }
          }

          if (global_Controller_DWork._task_trigger_generator.temp_SyncCnt >=
              local_PeriodSync) {
            tasks_syn();
            global_Controller_DWork._task_trigger_generator.temp_SyncCnt = 1U;

            /* nInj++; */
          } else {
            global_Controller_DWork._task_trigger_generator.temp_SyncCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task1msCnt >=
              Controller_PERIOD_1ms) {
            tasks_1ms();
            global_Controller_DWork._task_trigger_generator.temp_Task1msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task1msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task2msCnt >=
              Controller_PERIOD_2ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task2msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task2msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task5msCnt >=
              Controller_PERIOD_5ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task5msCnt = 1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task5msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task10msCnt >=
              Controller_PERIOD_10ms) {
            tasks_10ms();
            global_Controller_DWork._task_trigger_generator.temp_Task10msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task10msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task20msCnt >=
              Controller_PERIOD_20ms) {
            tasks_20ms();
            global_Controller_DWork._task_trigger_generator.temp_Task20msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task20msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task50msCnt >=
              Controller_PERIOD_50ms) {
            tasks_50ms();
            global_Controller_DWork._task_trigger_generator.temp_Task50msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task50msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task100msCnt >=
              Controller_PERIOD_100ms) {
            tasks_100ms();
            global_Controller_DWork._task_trigger_generator.temp_Task100msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task100msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task200msCnt >=
              Controller_PERIOD_200ms) {
            tasks_200ms();
            global_Controller_DWork._task_trigger_generator.temp_Task200msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task200msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task500msCnt >=
              Controller_PERIOD_500ms) {
            global_Controller_DWork._task_trigger_generator.temp_Task500msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task500msCnt++;
          }

          if (global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt>=
              Controller_PERIOD_1000ms) {
            tasks_1000ms();
            global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt =
              1U;
          } else {
            global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt++;
          }
        }

        break;

       default:
        global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt = 0UL;
        global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib
           = (uint8_T)Controller_IN_DELAY;
        break;
      }
    }
  }
}

/* Initialize for function-call system: '<S1113>/LC_r10ms' */
#define START_SECTION_InitCode
#include "pragma.h"

void LC_r10ms_initialize(void)
{
  (void) memset((char_T *) &global_LC_r10ms_DW,0,
                sizeof(rtDW_LC_r10ms));
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* Model initialize function */
#define START_SECTION_InitCode
#include "pragma.h"

void Controller_initialize(void)
{
  /* Registration code */

  /* block I/O */
  (void) memset(((void *) &global_Controller_B),0,
                sizeof(BlockIO_Controller));

  /* states (dwork) */
  (void) memset((char_T *) &global_Controller_DWork,0,
                sizeof(D_Work_Controller));

  /* exported global states */
  INT_IntMafLcFof = 0;
  UD_LCAD_fLcAdLo = 0U;
  UD_LCAD_fLcAdUp = 0U;
  UD_LCAD_OfsLcAdSyn = 0;

  /* Initialize subsystem data */
  LC_r10ms_initialize();

  /* Start for atomic system: '<S1>/scheduler' */

  /* Start for atomic system: '<S4>/Scheduler' */
  tasks_ini_Start();
  tasks_iniSyn_Start();
  tasks_syn_Start();
  tasks_10ms_Start();
  tasks_20ms_Start();
  tasks_50ms_Start();
  tasks_100ms_Start();
  tasks_200ms_Start();
  LPT_LamWO2_U32 = 268435456UL;
  UD_LC_fLcM = 32768U;
  UD_LC_fLc = 32768U;
  UD_LC_fLcJmp = 32768U;
  UD_LC_dfLcJmp = 32768U;
  LPT_ffLcI_U16 = 1073741824UL;
  TOnD_LSH2 = 5U;
  Timer_HLS_OnTime_U16 = 5U;
  TexBfCat_UD = 10U;
  TcatMain_UD = 10U;
  UD_TaTam = 32U;
  dIgaCtrEtm = 1U;
  LPT_FlTrsSub_U32 = 34952000UL;
  UD_CSLDP_LdPrd = 4267U;
  UD_CSIMM_Map2 = 25933U;
  UD_CSIMM_PimMod = 25933U;
  UD_CSIMM_Pmap = 25933U;
  UD_Ld_idle3 = 4267U;
  UD_Ld_idle2 = 4267U;
  UD_Ld_idle1 = 4267U;
  UD_CSIMM_Ld2 = 4267U;
  UD_CSIMM_Ld = 4267U;
  UD_CSIMM_Ld1 = 4267U;
  INT_fLdTpCr_U32 = 1073741824UL;
  LPT_CSPAM_Pam_U32 = 1726711071UL;
  LPT_SSTM_TmBfFil = 24917U;
  UD_SSTPS_TpsIdlOld = 13107U;
  UD_SSTPS_TpsIdl = 13107U;
  LPT_SSTPS1_U32 = 858993459UL;
  UD_TpsWotOld = 13107U;
  UD_TpsWot = 13107U;
  LPT_TpsWOT_U32 = 858993459UL;
  LPT_Baro_U32 = 12UL;
  LPT_LamDrv_U32 = 268435456UL;

  /* blocks with infinite sample periods */
  B_Tilt = 0U;
  NIdcCatHt = 60U;
  B_StepDgE = 0U;
  MafNrmIdcDsr = 0U;
  B_TherOff = 0U;

  /* Initial conditions for atomic system: '<S1>/scheduler' */

  /* Initial conditions for atomic system: '<S4>/Scheduler' */

  /* Initialize code for chart: '<S1492>/_task_trigger_generator' */
  global_Controller_DWork._task_trigger_generator.temp_is_active_c10_Scheduler_li
     = 0U;
  global_Controller_DWork._task_trigger_generator.temp_is_c10_Scheduler_lib = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task1msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task2msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task20msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task50msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task100msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task200msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task500msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task1000msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task5msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_Task10msCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_SyncCnt = 0U;
  global_Controller_DWork._task_trigger_generator.temp_BaseRateCnt = 0UL;
  global_Controller_DWork._task_trigger_generator.temp_FirstSyncCnt = 0U;
  global_Controller_B.IsIgnSyn = 0U;
  global_Controller_B.nInjSim = 0U;
  global_Controller_B.IsKeyOn = 0U;
  global_Controller_B.IsSync = 0U;
  global_Controller_B.IsIni2 = 0U;
  global_Controller_B.IsAftRun = 0U;
  tasks_10ms_Init();
}

#define STOP_SECTION_InitCode
#include "pragma.h"

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
