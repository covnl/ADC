/*
 * File: Controller_types.h
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Mon Jun 15 15:15:07 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Mon Jun 15 15:15:09 2015
 */
#ifndef _RTW_HEADER_Controller_types_h_
#define _RTW_HEADER_Controller_types_h_
#ifndef _CSC13_LC_LIB_CHARTSTRUCT_
#define _CSC13_LC_LIB_CHARTSTRUCT_

typedef struct {
  uint8_T temp_is_LC_active;
  uint8_T temp_is_active_c13_LC_lib;
  uint8_T temp_is_c13_LC_lib;
} CSc13_LC_lib_ChartStruct;

#endif                                 /* _CSC13_LC_LIB_CHARTSTRUCT_ */

#ifndef _CSC14_LC_LIB_CHARTSTRUCT_
#define _CSC14_LC_LIB_CHARTSTRUCT_

typedef struct {
  uint8_T temp_is_active_c14_LC_lib;
  uint8_T temp_is_active_fLcM_state;
  uint8_T temp_is_fLcM_state;
} CSc14_LC_lib_ChartStruct;

#endif                                 /* _CSC14_LC_LIB_CHARTSTRUCT_ */

#ifndef _CSC10_SCHEDULER_LIB_CHARTSTRUCT_
#define _CSC10_SCHEDULER_LIB_CHARTSTRUCT_

typedef struct {
  uint32_T temp_BaseRateCnt;
  uint16_T temp_FirstSyncCnt;
  uint16_T temp_SyncCnt;
  uint16_T temp_Task1000msCnt;
  uint16_T temp_Task100msCnt;
  uint16_T temp_Task10msCnt;
  uint16_T temp_Task1msCnt;
  uint16_T temp_Task200msCnt;
  uint16_T temp_Task20msCnt;
  uint16_T temp_Task2msCnt;
  uint16_T temp_Task500msCnt;
  uint16_T temp_Task50msCnt;
  uint16_T temp_Task5msCnt;
  uint8_T temp_is_active_c10_Scheduler_li;
  uint8_T temp_is_c10_Scheduler_lib;
} CSc10_Scheduler_lib_ChartStruct;

#endif                                 /* _CSC10_SCHEDULER_LIB_CHARTSTRUCT_ */

/* Type definition for custom storage class: FastBitField */
struct CSN_BitField_tag {
  uint_T E_CrkLoc : 1;                 /* local error flag for MAP sensor */
  uint_T Z_CrkLoc : 1;                 /* local cycle flag for MAP sensor */
  uint_T RSFF_CrkErr : 1;
  uint_T RSFF_CrkCyc : 1;
  uint_T ER_CSN_B_Syn : 1;
};

struct DLSV_BitField_tag {
  uint_T B_LsbHtRdy : 1;               /* lambda sensor before-cat heating ready */
  uint_T B_LsbErrMx : 1;               /* condition: lambda sensor max error */
  uint_T B_LsbErrMn : 1;               /* condition: lambda sensor min error */
  uint_T B_LsbErr : 1;                 /* condition: lambda sensor error */
  uint_T B_LsbOpnGnd : 1;
  uint_T B_uLsbScRst : 1;              /* lambda sensor short circuit error reset */
  uint_T RSFF_DLSV_B_LsbWirBrkPoss : 1;
  uint_T RSFF_DLSV2 : 1;
  uint_T RSFF_DLSV_B_LsbScNotRdy : 1;
  uint_T RSFF_DLSV_B_LsbAmpLm : 1;
  uint_T RSFF_DLSV_B_LsbLeakUb : 1;
  uint_T RSFF_DLSV_B_LsbRdy : 1;
  uint_T RSFF_DLSV_B_LsbHtEn : 1;
};

struct FIRSM_BitField_tag {
  uint_T UD_FIRSM_DSB_nfFlRsm : 1;
  uint_T RSFF_FIRSM_B_Fof : 1;
  uint_T EF_FIRSM_B_Fof : 1;
};

struct GenFast_BitField_tag {
  uint_T RSFF_IGO_Fof : 1;             /* flip flop, calculator the condition retard ignition angle */
  uint_T ER_B_KeyOn_Odo : 1;           /* Edge rising of Key On event for Odo-Meter  */
  uint_T RSFF_FITRS_TrsPst : 1;        /* RSFlip-Flop, Enable condition transient contr. after cranking  */
  uint_T RSFF_FISTA_HotSta : 1;        /* RS-FlipFlop,to decide the hot start condition  */
  uint_T UD_B_dLdPrd : 1;              /* unit delay state, delta of relatvie air charge predicted */
  uint_T UD_B_InsInj : 1;              /* unit delay state, delta of relatvie air charge predicted */
  uint_T RSFF_idleOut_InsInj : 1;      /* RSFlipFlop for set condition of load prediction after start */
  uint_T EF_B_InsInj : 1;              /* unit delay state, Edge Falling instant injection */
  uint_T EF_B_Idl_InsInj : 1;          /* unit delay state, Edge Falling idle */
  uint_T RSFF_CSLDP_LdPrdAst : 1;      /* RSFlipFlop for set condition of load prediction after start */
  uint_T Hysteresis_CSMAFTP_S16mx : 1; /* hysteresis for diagnosis fMafAdpMx */
  uint_T Hysteresis_CSMAFTP_S16mn : 1; /* hysteresis for diagnosis fMafAdpMn */
  uint_T ER_B_OilEn2 : 1;              /* Edge rising,oil pump enable  */
  uint_T ER_B_OilEn : 1;               /* Edge rising,oil pump enable  */
  uint_T ER_B_InjPreSta : 1;           /* Edge Rising, flag synchronization, for first fuel injection skip  */
  uint_T ER_B_MapAvg : 1;
  uint_T Hyst_Ld_B_IdlGr : 1;          /* hysteresis for gear detection based on load */
  uint_T RSFF_TQFOFRSM_Fil : 1;        /* RS-trigger, condition: low pass filter for transition to or from fuel cut-off active? */
  uint_T ER_TQFOFRSM_Fil : 1;          /* edge-raised trigger, condition: low pass filter for transition to or from fuel cut-off active? */
  uint_T Hysteresis_TQFOF_TqiDsr_S16 : 1;/* Hysteresis, torque for fuel cut off? */
  uint_T RSFF_TQNMX_Nmx : 1;           /* RS-trigger,  for maximum engine speed  ? */
};

struct IDCSTP_BitField_tag {
  uint_T B_StepPrePos_tmp : 1;         /* flag,  */
  uint_T B_StepDg_EnAfr : 1;           /* EdgeRise, for enable afterrun maximum stepper position diag */
  uint_T B_IdcStpIni_tmp : 1;          /* flag,  */
  uint_T RSFF_IDCSTP_AfrStepLrnStp : 1;/* RSFF, for afterrun stepper learning stop */
  uint_T ER_IDCSTP_AfrPrePos : 1;      /* EdgeRise, for afterrun preposition  */
  uint_T ER_IDCSTP_IdcStpAfr : 1;      /* EdgeRise, for enable afterrun maximum stepper position detection  */
  uint_T RSFF_IDCSTP_StpPrePos : 1;    /* RSFF, for set stepper pre_position */
  uint_T ER_IDCSTP_StepDgE : 1;        /* EdgeRise,  */
  uint_T ER_IDCSTP_StpIni : 1;         /* EdgeRise, for initialization maximum stepper position detection  */
  uint_T RSFF_IDCSTP_StpCon : 1;       /* RSFF, for idle speed control */
  uint_T RSFF_IDCSTP_StpLrn : 1;       /* RSFF, for set stepper learning */
};

struct LCEN_BitField_tag {
  uint_T Hyst_LcEnTm3 : 1;
  uint_T Hyst_LcEnTm2 : 1;
  uint_T Hyst_LcEnTm1 : 1;
  uint_T RSFF_B_TaStaLow : 1;
};

struct LC_BitField_tag {
  uint_T UD_LC_B_LaJmp_Stat : 1;
  uint_T ER_B_LcBlkEn : 1;             /* data store memory edge rising of B_LcBlkEn */
};

struct LSH_BitField_tag {
  uint_T UD_LSH1 : 1;
  uint_T ER_LSH_B_HtOffDly : 1;
  uint_T ER_B_tdHsAst : 1;             /* state of old singal B_tdHtASt */
};

struct OCSTA_BitField_tag {
  uint_T UD_OCSTA_Sta : 1;             /* unit delay state, condition for start */
  uint_T UD_OCSTA_StaEnd : 1;          /* unit delay state, condition start end */
  uint_T RSFF_OCSTA_B_Sta : 1;         /* RSFlip-flop,condition for start */
  uint_T RSFF_OCSTA_B_StaEnd : 1;      /* RSFlip-flop,condition end of start */
  uint_T ER_OCSTA_B_StaU : 1;          /* Edge rising,condition for start */
  uint_T EF_OCSTA_B_StaD : 1;          /* Edge falling,condition for start */
  uint_T ER_IACSOL_B_Idl : 1;          /* Edge rising,condition idling */
};

struct OFPMP_BitField_tag {
  uint_T ER_OFPEN_B_FuelEn : 1;        /* edge rising   */
};

struct SSBARO_BitField_tag {
  uint_T B_BaroBak : 1;                /* condition backup value for BARO sensor */
  uint_T E_BaroLoc : 1;                /* local error flag for BARO sensor */
  uint_T Z_BaroLoc : 1;                /* local cycle flag for BARO sensor */
  uint_T RSFF_SSBARO1 : 1;
  uint_T RSFF_SSBARO2 : 1;
};

struct SSMAP_BitField_tag {
  uint_T B_MapBak : 1;                 /* condition backup value for MAP sensor */
  uint_T E_MapLoc : 1;                 /* local error flag for MAP sensor */
  uint_T Z_MapLoc : 1;                 /* local cycle flag for MAP sensor */
  uint_T RSFF_SSMAP1 : 1;
  uint_T RSFF_SSMAP2 : 1;
};

/* Type definition for custom storage class: SlowBitField */
struct CSPAM_BitField_tag {
  uint_T Z_PamAdp : 1;                 /* cycle flag: ambient pressure adaptation */
  uint_T B_MxAltAdp : 1;               /* Condition: max-error ambient pressure adaptation */
  uint_T B_MnAltAdp : 1;               /* Condition: min-error ambient pressure adaptation */
  uint_T E_PamAdp : 1;                 /* error flag: ambient pressure adaptation */
  uint_T RSFF_CSPAM_MxAltAdp : 1;      /* RS flip flop,set and reset B_MxAltAdp  */
  uint_T RSFF_CSPAM_MnAltAdp : 1;      /* RS flip flop, set and reset B_MnAltAdp */
  uint_T RSFF_CSPAM_PamAdp : 1;        /* RS flip flop, set and reset E_PamAdp */
  uint_T RSFF_CSPAM_DisPamAdpSta : 1;  /* RS flip flop, for reset B_PamAdp */
};

struct ESTM_BitField_tag {
  uint_T B_LsbDewSet : 1;              /* Flag start-value tabgmst, tkatmst calculated */
  uint_T B_StaEstm_EF : 1;             /* Flag start-value tabgmst, tkatmst calculated */
  uint_T B_EstmEn_ER : 1;              /* Flag start-value tabgmst, tkatmst calculated */
  uint_T UD_IsStaEnd : 1;              /* condition temperature upstream catalyst exceeds dew-point */
  uint_T RSFF_ESTM1 : 1;               /* RS-Flip-Flop, Is Dew-Point-End After Cat? */
  uint_T EF_ESTM : 1;                  /* Edge-Falling, B_Sta? */
  uint_T ER_ESTM0 : 1;                 /* Edge-Rising, B_EstmSt? */
  uint_T ER_ESTM : 1;                  /* Edge-Falling, B_Sta? */
  uint_T UD_IsLsbDew : 1;              /* condition temperature upstream catalyst exceeds dew-point */
  uint_T ER_ESTM2 : 1;                 /* Edge-Rising, B_StaEnd */
  uint_T ER_ESTM3 : 1;                 /* Edge-Rising, B_StaEnd */
  uint_T EF_ESTM1 : 1;                 /* Edge-Falling, B_StaEnd? */
};

struct GenSlow_BitField_tag {
  uint_T ER_B_KeyON_EOL : 1;
  uint_T ER_SSTPS_B_Pwf : 1;
  uint_T EF_SSTPS_B_Sta : 1;
  uint_T ER_WOT_B_Pwf : 1;
};

struct SSPot_BitField_tag {
  uint_T B_PotBak : 1;                 /* condition backup value for  Pot */
  uint_T E_PotLoc : 1;                 /* error condition of Pot */
  uint_T Z_PotLoc : 1;                 /* diagnosis completed of Pot */
  uint_T RSFF_SSPot1 : 1;
  uint_T RSFF_SSPot2 : 1;
};

struct SSTA_BitField_tag {
  uint_T B_TaMxLoc : 1;                /* fault type: maximum value of intake air temperature exceeded */
  uint_T B_TaMnLoc : 1;                /* fault type: minimum value of intake air temperature */
  uint_T B_TaBak : 1;                  /* condition backup value for intake air temperature */
  uint_T B_TaIdl : 1;
  uint_T B_AstTa : 1;                  /* is call mean fun */
  uint_T Z_TaLoc : 1;                  /* cycle flag: intake air temperature */
  uint_T E_TaLoc : 1;                  /* error flag: intake air temperature */
  uint_T RSFF_SSTA1 : 1;
  uint_T RSFF_SSTA_B_TaBakSet : 1;
};

struct SSTM_BitField_tag {
  uint_T B_TmMnLoc : 1;                /* fault type: minimum value of  Engine coolant temperature Tm */
  uint_T B_TmMxLoc : 1;                /* fault type: maximum value of  Engine coolant temperature Tm exceeded  */
  uint_T B_TmBak : 1;                  /* condition backup value for  Engine coolant temperature */
  uint_T E_TmLoc : 1;                  /* error flag:  Engine coolant temperature */
  uint_T Z_TmLoc : 1;                  /* cycle flag:  Engine coolant temperature */
  uint_T ER_SSTM2 : 1;
  uint_T RSFF_SSTM1 : 1;
  uint_T RSFF_SSTM3 : 1;
  uint_T ER_SSTM_B_Sta2 : 1;
  uint_T ER_SSTM_B_Sta1 : 1;
  uint_T EF_SSTM_B_Sta : 1;
};

struct SSTPS_BitField_tag {
  uint_T B_TpsOutRng : 1;              /* condition TPS sensor voltage out of range */
  uint_T E_TpsLoc : 1;                 /* error condition of TPS */
  uint_T Z_TpsLoc : 1;                 /* diagnosis completed of TPS */
  uint_T RSFF_SSTPS1 : 1;
  uint_T RSFF_SSTPS2 : 1;
};

struct SSUB_BitField_tag {
  uint_T B_UbMxLoc : 1;                /* fault type: maximum value battery voltage (onboard) exceeded  */
  uint_T B_UbMnLoc : 1;                /* fault type: minimum value of battery voltage (onboard)  */
  uint_T Z_UbLoc : 1;                  /* cycle flag: power supply voltage Ub  */
  uint_T E_UbLoc : 1;                  /* error flag: power supply voltage  */
  uint_T RSFF_SSUB2 : 1;
  uint_T RSFF_SSUB1 : 1;
};

struct SSVSP_BitField_tag {
  uint_T B_VspSig : 1;                 /* Condition missing signal vehicle speed  */
  uint_T B_VspNpl : 1;                 /* Error typ: Vehicle speed not plausible  */
  uint_T Z_Vsp : 1;                    /* cycle flag: vehicle speed signal  */
  uint_T RSFF_SSVSP2 : 1;
  uint_T RSFF_SSVSP1 : 1;
};

struct SSWO2_BitField_tag {
  uint_T E_LsuLoc2 : 1;                /* error condition of TPS */
  uint_T Z_LsuLoc2 : 1;                /* diagnosis completed of TPS */
  uint_T E_LsuLoc : 1;                 /* error condition of TPS */
  uint_T Z_LsuLoc : 1;                 /* diagnosis completed of TPS */
  uint_T RSFF_SSWO2_3 : 1;
  uint_T RSFF_SSWO2_4 : 1;
  uint_T RSFF_SSWO2_1 : 1;
  uint_T RSFF_SSWO2_2 : 1;
};

struct USR_BitField_tag {
  uint_T B_IgaApp : 1;                 /* Ignition angle manually set for application purpose */
  uint_T IsLsbHtApp : 1;               /* Is lambda sensor (before cat) heater available? */
  uint_T IsLsbDgUsr : 1;               /* Is lambda sensor (before cat) diagnosis user defined available? */
  uint_T IsLcUsr : 1;                  /* Is lambda control user defined available? */
  uint_T IsIgaBas : 1;                 /* Is ignition basic angle to be used? */
  uint_T IsIgaPre : 1;                 /* Ignition angle use predefined */
};

#endif                                 /* _RTW_HEADER_Controller_types_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
