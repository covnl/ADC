

extern uint16_T Tps; 
extern uint16_T Map;
extern uint16_T N; 
extern boolean_T B_StaEnd;
extern uint16_T BP_LdTp_N[12];
extern uint16_T BP_LdTp_Tps[16];
extern uint16_T fLamAdTab_an[192];
extern uint16_T BP_fVe_N[12];
extern uint16_T BP_fVe_Map[16];
extern uint16_T fLamAdTab[192];
extern uint16_T Ld;
extern uint16_T fLamAdIn;
extern uint16_T fAirDenTp;
extern uint16_T RAM_SelfLearnHistory[20];
extern int16_T VAL_SLM_dTpsStableMin;
extern uint16_T VAL_SLM_dNStableMin;
extern uint16_T VAL_SLM_dFactorStableMin;
extern uint16_T VAL_SLM_StableCounterGoal;
extern uint16_T VAL_SLM_AN_N2LdRaw;
extern uint16_T VAL_SLM_AN_Tps2LdRaw;
extern uint16_T VAL_SLM_PN_Map2LdRaw;
extern uint16_T VAL_SLM_PN_N2LdRaw;
extern uint8_T RAM_VAL_fFlApp;
extern uint8_T B_fLamAd;
extern uint16_T fAlt; 
extern uint16_T fTcmb;
extern uint16_T fPreCtl;
extern boolean_T IsfLamAdOut;
extern UINT16 MAP_fVe_Map_N[192];
extern UINT16 MAP_LdTp_Tps_N[192]; 
extern UINT16 VAL_fPrs2LdNrm;
extern UINT16 *Ram_Ptr;

#define SYSTEM_TPS                      Tps
#define SYSTEM_N                        N
#define SYSTEM_MAP                      Map
#define SYSTEM_START_END                B_StaEnd
#define SYSTEM_AN_N_AXIS                BP_LdTp_N
#define SYSTEM_AN_TPS_AXIS              BP_LdTp_Tps
#define SYSTEM_AN_N_AXIS_SIZE           12
#define SYSTEM_AN_TPS_AXIS_SIZE         16
#define SYSTEM_PN_N_AXIS                BP_fVe_N
#define SYSTEM_PN_MAP_AXIS              BP_fVe_Map
#define SYSTEM_PN_MAP_AXIS_SIZE         16
#define SYSTEM_PN_N_AXIS_SIZE           12
#define SYSTEM_LOAD_FACTOR              fLamAdIn
#define SYSTEM_ENABLE_AUTO_TUNING       B_fLamAd
#define SYSTEM_ADJUST_OUT_OF_RANGE      IsfLamAdOut
#define SLM_AN_Ld_Table                 fLamAdTab_an
#define SLM_PN_Ld_Table                 fLamAdTab
#define SLM_TPS_STABLE_CHANGE_MIN       VAL_SLM_dTpsStableMin
#define SLM_N_STABLE_CHANGE_MIN         VAL_SLM_dNStableMin
#define SLM_LOAD_FACTOR_STABLE_CHANGE_MIN       VAL_SLM_dFactorStableMin
#define SLM_StableCounter_Goal          VAL_SLM_StableCounterGoal
#define SLM_N_Input                     N
#define SLM_Tps_Input                   Tps
#define SLM_Map_Input                   Map
#define SLM_Ld_Input                    (uint16_T)((uint32_T)Ld*32768U/fTcmb*16384U/fAlt*fPreCtl/1024U)
#define SLM_AN_N_AXIS_TO_LD             VAL_SLM_AN_N2LdRaw
#define SLM_AN_TPS_AXIS_TO_LD           VAL_SLM_AN_Tps2LdRaw
#define SLM_PN_MAP_AXIS_TO_LD           VAL_SLM_PN_Map2LdRaw
#define SLM_PN_N_AXIS_TO_LD             VAL_SLM_PN_N2LdRaw
#define SLM_LearnedHistory              RAM_SelfLearnHistory

void SLM_20ms(void);
void SLM_init(void);
void SLM_100ms(void);
void Convert_fVe_To_Ld(void);
void Convert_Ld_To_fVe(void);
void SelfLearningTabInit(UINT8 Status);