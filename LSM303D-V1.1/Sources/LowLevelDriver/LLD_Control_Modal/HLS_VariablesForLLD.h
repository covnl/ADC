


extern UINT16 VAL_tEngOffMx;
extern UINT16 VAL_StepPosMx;
extern UINT16 VAL_StepPosMn; 
extern UINT32 VAL_ECU_Passwd; 
extern UINT8  CV_DSM;
extern UINT8  CV_LSB;
extern UINT8  CV_LampOutSelect;
extern UINT8  CUR_Customer_Inf[];
extern UINT16 VAL_Customer_Counter;
extern UINT8  CV_APP;
extern UINT16 VAL_FreqWg;
extern UINT32 VAL_CCP_RxID;
extern UINT32 VAL_UAVCAN_RxID;
extern UINT32 VAL_WBO2_CAN_RxID;
extern UINT16 MAP_LdTp_Tps_N[];
extern UINT16 MAP_fVe_Map_N[];
extern INT8   MAP_Iga_N_Ld[];
extern UINT8  CUR_fWmp_Tm[];
extern UINT8  CUR_fAst_TmSta[];                   
extern UINT16 CUR_Wf_Ldp[];
extern UINT16 MAP_fAlt_N_Pam[];
extern UINT8  VAL_fFlApp;
extern UINT16 RAM_MAP_LdTp_Tps_N[];
extern UINT16 RAM_MAP_fVe_Map_N[];
extern INT8   RAM_MAP_Iga_N_Ld[];
extern UINT8  RAM_CUR_fWmp_Tm[];
extern UINT8  RAM_CUR_fAst_TmSta[];                   
extern UINT16 RAM_CUR_Wf_Ldp[];
extern UINT16 RAM_MAP_fAlt_N_Pam[];
extern UINT8  RAM_VAL_fFlApp;



extern UINT16 DcWg;
extern UINT8  B_Pmp;
extern UINT16 Nraw;
extern UINT8  B_PWPumpExist;
extern UINT16 OilPmpOpenCnt;
extern UINT16 OilPmpOpenCnt2;
extern UINT16 tOnServoCtrl;
extern UINT8  cntEolTst;
extern UINT8  IsChaoBan;
extern UINT8  B_Pwf;  
extern UINT8  B_IdlRdy;    
extern UINT16 StepPosDsr;
extern UINT16 StepPos;
extern UINT8  B_StaEnd;
extern UINT8  B_StepLrn;
extern UINT8  B_KeyOn;
extern UINT16 tEngOff;//stop time
extern UINT16 tAfrApp ; 
extern UINT16 tOilOn;
extern UINT16 tOilCyc;
extern UINT16 tOilOn2;
extern UINT16 tOilCyc2;
extern UINT8  B_ClrAll;
extern UINT16 uTa;
extern UINT16 uTm;
extern UINT16 uMap;
extern UINT16 uTps; 
extern UINT16 UbAdc;
extern UINT16 uPot;
extern UINT16 uBaro;
extern UINT16 uLsb;
extern UINT8  B_LsbHtEn;    
extern UINT8  B_Mil;
extern UINT16 UbAdc;
extern UINT16 tAfrApp ;
extern UINT8  B_Nup0;
extern UINT8  B_Kill;
extern UINT16 ALM_Lambda_FromCAN;
extern UINT16 ALM_lsuTemp_FromCAN;
extern UINT16 ALM_lsuDTC_FromCAN;
extern INT16  ALM_lsuO2_FromCAN;
extern UINT16 ALM_lsuHtDtcy_FromCAN;
extern UINT16 Baro;
extern UINT16 TPS;
extern UINT16 MAP;
extern UINT16 RPM;
extern UINT16 UbAdc;
extern UINT8  ECT;
extern UINT8  IAT;
extern UINT16 O2S;
extern INT8 SPARK;
extern UINT16 FUELPW1;
extern UINT16 FUELPW2;
extern UINT16 N;
extern UINT16 dmFuel;
extern UINT16 dmFuelKgPH;    
extern UINT16 mFuel_1g;
extern UINT16 vFuelL;
extern UINT16 FcmAirInj1;
extern UINT16 FcmAirInj2;
extern UINT16 FcmAirInj3;
extern UINT16 FcmAirInj4;
extern UINT16 FcmAps;
extern UINT16 FcmCrk; 
extern UINT16 FcmIgn1;
extern UINT16 FcmIgn2;
extern UINT16 FcmIgn3;
extern UINT16 FcmIgn4;
extern UINT16 FcmInj1;
extern UINT16 FcmInj2;
extern UINT16 FcmInj3;
extern UINT16 FcmInj4;
extern UINT16 FcmLsb;
extern UINT16 FcmLsb2;
extern UINT16 FcmMap;
extern UINT16 FcmNtrl;
extern UINT16 FcmOil;
extern UINT16 FcmPam;
extern UINT16 FcmPgv;
extern UINT16 FcmPot;
extern UINT16 FcmPump;
extern UINT16 FcmTa; 
extern UINT16 FcmTilt;
extern UINT16 FcmTm;
extern UINT16 FcmTps;
extern UINT16 FcmTps2;
extern UINT16 FcmUb;  
extern UINT16 FcmBaro;
extern UINT8  E_Pgv;
extern UINT8  E_Pot;
extern UINT8  E_Tps2;
extern UINT8  E_Pam;
extern UINT8  E_Tilt;
extern UINT8  E_Crk;
extern UINT8  E_Map;
extern UINT8  E_Lsb;
extern UINT8  E_Lsb2;
extern UINT8  E_Ta;
extern UINT8  E_Tm;
extern UINT8  E_Baro;
extern UINT8  E_Tps;
extern UINT8  E_Ub;   
extern UINT16 TpsIdlUp;
extern UINT16 TpsIdl; 
extern UINT8 B_IacSol;
extern UINT8 B_AsrEn;
extern UINT8 B_Syn;
extern UINT8 B_Passwd;
extern UINT16 Ld;
extern UINT16 tInj0;
extern UINT16 tInj1;
extern INT8   IgaOut;
extern UINT8  tDwl;
extern UINT16 Map;
extern UINT8  Tm;
extern UINT8  Ta;
extern UINT8  B_CrkErr;
extern UINT8  VAL_CAN0_BaudRate;
extern UINT16 tOnServoPwmIn;
extern UINT8 tCyclePump;
extern UINT8 DutyPump;
extern UINT16 uServoIn;




#define HLS_ServoCtlCyclePWM01_InitVal   40000
#define HLS_GearPmpCyclePWM45_InitVal    512
#define HLS_VAL_tEngOffMx        VAL_tEngOffMx
#define HLS_VAL_StepPosMx        VAL_StepPosMx
#define HLS_VAL_StepPosMn        VAL_StepPosMn 
#define HLS_VAL_ECU_Passwd       VAL_ECU_Passwd 
#define HLS_CV_DSM               CV_DSM
#define HLS_CV_LSB               CV_LSB
#define HLS_CV_LampOutSelect     CV_LampOutSelect
#define HLS_VAL_ServoCtlOut_En   1
#define HLS_VAL_Customer_Counter VAL_Customer_Counter
#define HLS_CUR_Customer_Inf     CUR_Customer_Inf
#define HLS_CV_APP               CV_APP
#define HLS_VAL_FreqWg           VAL_FreqWg
#define HLS_PWMDTY01_IniValue    0
//#define HLS_CCP_RxID             VAL_CCP_RxID
//#define HLS_UAVCAN_RxID          VAL_UAVCAN_RxID
//#define HLS_WBO2_CAN_RxID        VAL_WBO2_CAN_RxID


#define HLS_DcWg                 DcWg
#define HLS_B_Pmp                B_Pmp
#define HLS_Nraw                 Nraw
#define HLS_B_PWPumpExist        B_PWPumpExist
#define HLS_OilPmpOpenCnt        OilPmpOpenCnt
#define HLS_OilPmpOpenCnt2       OilPmpOpenCnt2
#define HLS_OnTime_ServoCtlOutPWM tOnServoCtrl
#define HLS_cntEolTst            cntEolTst
#define HLS_IsChaoBan            IsChaoBan
#define HLS_B_Pwf                B_Pwf  
#define HLS_B_IdlRdy             B_IdlRdy    
#define HLS_StepPosDsr           StepPosDsr
#define HLS_StepPos              StepPos
#define HLS_B_StaEnd             B_StaEnd
#define HLS_B_StepLrn            B_StepLrn
#define HLS_B_KeyOn              B_KeyOn
#define HLS_tEngOff              tEngOff
#define HLS_tAfrApp              tAfrApp
#define HLS_tOilOn               tOilOn
#define HLS_tOilCyc              tOilCyc
#define HLS_tOilOn2              tOilOn2
#define HLS_tOilCyc2             tOilCyc2
#define HLS_B_ClrAll             B_ClrAll
#define HLS_AD_CH6               uTa
#define HLS_AD_CH7               uTm
#define HLS_AD_CH3               uMap
#define HLS_AD_CH4               uTps 
#define HLS_AD_CH5               UbAdc
#define HLS_BatteryVol           UbAdc
#define HLS_AD_CH8               uPot
#define HLS_AD_CH0               uBaro
#define HLS_AD_CH2               uLsb
#define HLS_B_LsbHtEn            B_LsbHtEn
#define HLS_B_Mil                B_Mil
#define HLS_tAfrApp              tAfrApp
#define HLS_B_Nup0               B_Nup0
#define HLS_B_Kill               B_Kill
#define HLS_ALM_Lambda_FromCAN   ALM_Lambda_FromCAN
#define HLS_LamTemp_FromCAN      ALM_lsuTemp_FromCAN
#define HLS_LamDTC_FromCAN       ALM_lsuDTC_FromCAN
#define HLS_LamO2_FromCAN        ALM_lsuO2_FromCAN
#define HLS_LamHtDtcy_FromCAN    ALM_lsuHtDtcy_FromCAN
#define HLS_Baro                 Baro
#define HLS_TPS                  TPS
#define HLS_MAP                  MAP
#define HLS_RPM                  RPM
#define HLS_ECT                  ECT
#define HLS_IAT                  IAT
#define HLS_EngineSpeed          N
#define HLS_B_StaEnd             B_StaEnd
#define HLS_dmFuel               dmFuel
#define HLS_dmFuelKgPH           dmFuelKgPH
#define HLS_mFuel_1g             mFuel_1g
#define HLS_vFuelL               vFuelL
#define HLS_FcmAirInj1           FcmAirInj1
#define HLS_FcmAirInj2           FcmAirInj2
#define HLS_FcmAirInj3           FcmAirInj3
#define HLS_FcmAirInj4           FcmAirInj4
#define HLS_FcmAps               FcmAps
#define HLS_FcmCrk               FcmCrk 
#define HLS_FcmIgn1              FcmIgn1
#define HLS_FcmIgn2              FcmIgn2
#define HLS_FcmIgn3              FcmIgn3
#define HLS_FcmIgn4              FcmIgn4
#define HLS_FcmInj1              FcmInj1
#define HLS_FcmInj2              FcmInj2
#define HLS_FcmInj3              FcmInj3
#define HLS_FcmInj4              FcmInj4
#define HLS_FcmLsb               FcmLsb
#define HLS_FcmLsb2              FcmLsb2
#define HLS_FcmMap               FcmMap
#define HLS_FcmNtrl              FcmNtrl
#define HLS_FcmOil               FcmOil
#define HLS_FcmPam               FcmPam
#define HLS_FcmPgv               FcmPgv
#define HLS_FcmPot               FcmPot
#define HLS_FcmPump              FcmPump
#define HLS_FcmTa                FcmTa
#define HLS_FcmTilt              FcmTilt
#define HLS_FcmTm                FcmTm
#define HLS_FcmTps               FcmTps
#define HLS_FcmTps2              FcmTps2
#define HLS_FcmUb                FcmUb
#define HLS_FcmBaro              FcmBaro
#define HLS_E_Pgv                E_Pgv
#define HLS_E_Pot                E_Pot
#define HLS_E_Tps2               E_Tps2
#define HLS_E_Pam                E_Pam
#define HLS_E_Tilt               E_Tilt
#define HLS_E_Crk                E_Crk
#define HLS_E_Map                E_Map
#define HLS_E_Lsb                E_Lsb
#define HLS_E_Lsb2               E_Lsb2
#define HLS_E_Ta                 E_Ta
#define HLS_E_Tm                 E_Tm
#define HLS_E_Baro               E_Baro
#define HLS_E_Tps                E_Tps
#define HLS_E_Ub                 E_Ub  
#define HLS_TpsIdlUp             TpsIdlUp
#define HLS_TpsIdl               TpsIdl  
#define HLS_GearPmpOut_duty      ((UINT16)tCyclePump * DutyPump)>>5
#define HLS_GearPmpOut_freq      (UINT16)tCyclePump<<3
#define HLS_B_IacSol             B_IacSol
#define HLS_B_AsrEn              B_AsrEn
#define HLS_B_Syn                B_Syn
#define HLS_O2S                  O2S
#define HLS_SPARK                SPARK
#define HLS_FUELPW1              FUELPW1
#define HLS_FUELPW2              FUELPW2
#define HLS_B_Passwd             B_Passwd
#define HLS_Load                 Ld
#define HLS_tInj0                tInj0
#define HLS_tInj1                tInj1
#define HLS_IgaOut               IgaOut
#define HLS_tDwl                 tDwl
#define HLS_Map                  Map
#define HLS_Tm                   Tm
#define HLS_Ta                   Ta
#define HLS_B_CrkErr             B_CrkErr
#define HLS_uServoIn             uServoIn
