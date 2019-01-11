/*
 * File: Controller_private.h
 *
 * Real-Time Workshop code generated for Simulink model Controller.
 *
 * Model version                        : 1.0.1
 * Real-Time Workshop file version      : 6.5  (R2006b)  03-Aug-2006
 * Real-Time Workshop file generated on : Mon Jun 15 15:15:07 2015
 * TLC version                          : 6.5 (Aug  3 2006)
 * C source code generated on           : Mon Jun 15 15:15:09 2015
 */
#ifndef _RTW_HEADER_Controller_private_h_
#define _RTW_HEADER_Controller_private_h_
#include "rtwtypes.h"
#  include "rtlibsrc.h"
#define CALL_EVENT                     (MAX_uint8_T)
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file.
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I16L32N16F0
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I16L32N16F0 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

void BINARYSEARCH_U8( uint_T *piLeft, uint_T *piRght, uint8_T u, const uint8_T
                     *pData, uint_T iHi);
void INTERPOLATE_U8_U8( uint8_T *pY, uint8_T yL, uint8_T yR, uint8_T x, uint8_T
  xL, uint8_T xR);
void LookUp_U8_U8( uint8_T *pY, const uint8_T *pYData, uint8_T u, const uint8_T
                  *pUData, uint_T iHi);
void BINARYSEARCH_U16( uint_T *piLeft, uint_T *piRght, uint16_T u, const
                      uint16_T *pData, uint_T iHi);
void INTERPOLATE_U16_U16( uint16_T *pY, uint16_T yL, uint16_T yR, uint16_T x,
  uint16_T xL, uint16_T xR);
void LookUp_U16_U16( uint16_T *pY, const uint16_T *pYData, uint16_T u, const
                    uint16_T *pUData, uint_T iHi);
void Look2D_U16_U16_U16( uint16_T *pY, const uint16_T *pYData, uint16_T u0,
  const uint16_T *pU0Data, uint_T iHiU0, uint16_T u1, const uint16_T *pU1Data,
  uint_T iHiU1);
void INTERPOLATE_S8_U8( int8_T *pY, int8_T yL, int8_T yR, uint8_T x, uint8_T xL,
  uint8_T xR);
void Look2D_S8_U8_U8( int8_T *pY, const int8_T *pYData, uint8_T u0, const
                     uint8_T *pU0Data, uint_T iHiU0, uint8_T u1, const uint8_T
                     *pU1Data, uint_T iHiU1);
void INTERPOLATE_U8_U16( uint8_T *pY, uint8_T yL, uint8_T yR, uint16_T x,
  uint16_T xL, uint16_T xR);
void LookUp_U8_U16( uint8_T *pY, const uint8_T *pYData, uint16_T u, const
                   uint16_T *pUData, uint_T iHi);
void LookUp_S8_U8( int8_T *pY, const int8_T *pYData, uint8_T u, const uint8_T
                  *pUData, uint_T iHi);
void INTERPOLATE_U16_U8( uint16_T *pY, uint16_T yL, uint16_T yR, uint8_T x,
  uint8_T xL, uint8_T xR);
void LookUp_U16_U8( uint16_T *pY, const uint16_T *pYData, uint8_T u, const
                   uint8_T *pUData, uint_T iHi);
void Look2D_U16_U8_U16( uint16_T *pY, const uint16_T *pYData, uint8_T u0, const
  uint8_T *pU0Data, uint_T iHiU0, uint16_T u1, const uint16_T *pU1Data, uint_T
  iHiU1);
void Look2D_U8_U8_U8( uint8_T *pY, const uint8_T *pYData, uint8_T u0, const
                     uint8_T *pU0Data, uint_T iHiU0, uint8_T u1, const uint8_T
                     *pU1Data, uint_T iHiU1);
void BINARYSEARCH_S8( uint_T *piLeft, uint_T *piRght, int8_T u, const int8_T
                     *pData, uint_T iHi);
void INTERPOLATE_U8_S8( uint8_T *pY, uint8_T yL, uint8_T yR, int8_T x, int8_T xL,
  int8_T xR);
void LookUp_U8_S8( uint8_T *pY, const uint8_T *pYData, int8_T u, const int8_T
                  *pUData, uint_T iHi);
void BINARYSEARCH_S16( uint_T *piLeft, uint_T *piRght, int16_T u, const int16_T
                      *pData, uint_T iHi);
void INTERPOLATE_U16_S16( uint16_T *pY, uint16_T yL, uint16_T yR, int16_T x,
  int16_T xL, int16_T xR);
void LookUp_U16_S16( uint16_T *pY, const uint16_T *pYData, int16_T u, const
                    int16_T *pUData, uint_T iHi);
int16_T TuneParamCast_S16_U8_SL8_SAT(uint8_T B);
void Look2D_U16_U8_U8( uint16_T *pY, const uint16_T *pYData, uint8_T u0, const
                      uint8_T *pU0Data, uint_T iHiU0, uint8_T u1, const uint8_T
                      *pU1Data, uint_T iHiU1);
void BINARYSEARCH_U8_iL( uint_T *piLeft, uint8_T u, const uint8_T *pData, uint_T
  iHi);
void INTERPOLATE_S8_U16( int8_T *pY, int8_T yL, int8_T yR, uint16_T x, uint16_T
  xL, uint16_T xR);
void LookUp_S8_U16( int8_T *pY, const int8_T *pYData, uint16_T u, const uint16_T
                   *pUData, uint_T iHi);
uint32_T div_u32(uint32_T numerator, uint32_T denominator);
uint32_T div_repeat_u32_sat(uint32_T numerator, uint32_T denominator, uint16_T
  nRepeatSub);
void mul_wide_u32(uint32_T in0, uint32_T in2, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo);
uint32_T mul_u32_u32_u32_sat(uint32_T a, uint32_T b);
uint16_T div_u16(uint16_T numerator, uint16_T denominator);
uint16_T div_u16_SR(uint16_T numerator, uint16_T denominator, uint16_T
                    nShiftRight);
int16_T div_s16_sat_floor(int16_T numerator, int16_T denominator);
int8_T div_s8s16_floor(int16_T numerator, int16_T denominator);
int16_T div_s16_floor(int16_T numerator, int16_T denominator);
int32_T div_s32_floor(int32_T numerator, int32_T denominator);
int8_T div_s8s32_floor(int32_T numerator, int32_T denominator);
uint8_T plook_u8u16u16n15_binca_f(uint16_T u, const uint16_T *const bp, uint32_T
  maxIndex, uint16_T *fraction);
uint16_T intrp1d_u16u8u16n15_lca_f(uint8_T bpIndex, uint16_T frac, const
  uint16_T *const table, uint32_T maxIndex);
uint16_T intrp2d_u16u8u16n15_lca_f(const uint8_T *const bpIndex, const uint16_T *
  const frac, const uint16_T *const table, uint32_T stride, const uint32_T *
  const maxIndex);
uint8_T plook_u8u8u16n15_binca_f(uint8_T u, const uint8_T *const bp, uint32_T
  maxIndex, uint16_T *fraction);
uint8_T intrp2d_u8u8u16n15_lca_f(const uint8_T *const bpIndex, const uint16_T *
  const frac, const uint8_T *const table, uint32_T stride, const uint32_T *const
  maxIndex);
int8_T intrp2d_s8u8u16n15_lca_f(const uint8_T *const bpIndex, const uint16_T *
  const frac, const int8_T *const table, uint32_T stride, const uint32_T *const
  maxIndex);
uint8_T intrp1d_u8u8u16n15_lca_f(uint8_T bpIndex, uint16_T frac, const uint8_T *
  const table, uint32_T maxIndex);
uint8_T plook_u8u16_bincka(uint16_T u, const uint16_T *const bp, uint32_T
  maxIndex);
uint8_T binsearch_u8u16(uint16_T u, const uint16_T *const bp, uint32_T
  startIndex, uint32_T maxIndex);
uint8_T binsearch_u8u8(uint8_T u, const uint8_T *const bp, uint32_T startIndex,
  uint32_T maxIndex);
void SWADP_ini(void);
void CSMAFTP_ini(void);
void LCAD_ini(void);
void LCADWB_ini_Start(void);
void LCADWB_ini(void);
void OCFOFRSM_ini(void);
void PWPUMP_ini(void);
void SERVO_ini(void);
void tasks_ini_Start(void);
void tasks_ini(void);
void CSIMM_iniSyn(void);
void FLSTA_iniSyn(void);
void SWADP_iniSyn_Start(void);
void SWADP_iniSyn(void);
void FL2TI_iniSyn(void);
void FLAST_iniSyn(void);
void tasks_iniSyn_Start(void);
void tasks_iniSyn(void);
void CSN_ini2(void);
void SSTPS_ini2(void);
void SSMAP_ini2(void);
void SSTM_ini2(void);
void SSTA_ini2(void);
void SSUB_ini2(void);
void CSFTM_ini2(void);
void CSIMM_ini2(void);
void CSPAM_ini2(void);
void IGSTA_ini2(void);
void ESTM_ini2(void);
void DSM_ini2(void);
void SSFLAM_ini2(void);
void IDCSTP_ini2(void);
void SSBARO_ini2(void);
void FLSTA_ini2(void);
void tasks_ini2(void);
void FLAST_syn_Start(void);
void FLAST_syn(void);
void CSFL_syn_Start(void);
void CSFL_syn(void);
void FL2TI_syn_Start(void);
void FL2TI_syn(void);
void FlANG_syn(void);
void IGOUT_syn(void);
void CSIMM_syn_Start(void);
void CSIMM_syn(void);
void SWADP_syn(void);
void SSMAP_syn(void);
void CSN_syn(void);
void CSLDP_syn_Start(void);
void CSLDP_syn(void);
void FLTRS_syn(void);
void OFINJ_syn(void);
void FLRSM_syn(void);
void FLECO_syn(void);
void tasks_syn_Start(void);
void tasks_syn(void);
void SSMAP_r1ms(void);
void tasks_1ms(void);
void CSN_10ms(void);
void SSTPS_10ms(void);
void SSUB_10ms(void);
void OCSTA_r10ms(void);
void OFPMP_10ms(void);
void IGGRU_10ms(void);
void IGMIN_10ms(void);
void IGKNP_10ms(void);
void IGOUT_10ms(void);
void CSMAFTP_10ms_Start(void);
void CSMAFTP_10ms(void);
void CSTPP_10ms(void);
void CSLDP_10ms_Start(void);
void CSLDP_10ms(void);
void FLTRS_10ms(void);
void DSM_10ms(void);
void ESTM_10ms(void);
void LSH_10ms(void);
void LC_SM_Init(void);
void LC_SM(void);
void LC_r10ms_Init(void);
void LC_r10ms_Start(void);
void LC_r10ms(void);
void LCEN_10ms(void);
void SWADP_r10ms(void);
void LADRV_r10ms(void);
void LAMCO_r10ms_Start(void);
void LAMCO_r10ms(void);
void IGCOO_r10ms(void);
void IGOUT1_10ms(void);
void IGPRE_r10ms(void);
void IGNMX_r10ms(void);
void IGFOF_r10ms(void);
void OCFOFRSM_r10ms(void);
void CSIMM_10ms_Start(void);
void CSIMM_10ms(void);
void IGASR_r10ms(void);
void BPC_r10ms(void);
void SSMAP_r10ms(void);
void IDCSTP_r10ms(void);
void IACSOL_r10ms(void);
void PWPUMP_r10ms(void);
void CSPAM_10ms(void);
void OILP_r10ms(void);
void OILP2_r10ms(void);
void SERVO_r10ms(void);
void tasks_10ms_Init(void);
void tasks_10ms_Start(void);
void tasks_10ms(void);
void IGDWL_20ms(void);
void IDCND_r20ms_Start(void);
void IDCND_r20ms(void);
void DLSB_r20ms(void);
void SSFLAM_10ms(void);
void SSVSP_r20ms_Start(void);
void SSVSP_r20ms(void);
void SSWO2_r20ms_Start(void);
void SSWO2_r20ms(void);
void LCADWB_r20ms_Start(void);
void LCADWB_r20ms(void);
void tasks_20ms_Start(void);
void tasks_20ms(void);
void FLSTA_r50ms_Start(void);
void FLSTA_r50ms(void);
void OFPMP_50ms(void);
void LC_r50ms_Start(void);
void LC_r50ms(void);
void OFINJ_r50ms(void);
void SSFLAM_r50ms(void);
void tasks_50ms_Start(void);
void tasks_50ms(void);
void SSTPS_100ms(void);
void SSTM_100ms(void);
void SSTA_100ms(void);
void SSUB_100ms(void);
void OCSTA_100ms(void);
void IGSTA_100ms(void);
void CSFTM_100ms_Start(void);
void CSFTM_100ms(void);
void FLTRS_100ms(void);
void LSH_100ms(void);
void DLSB_r100ms(void);
void LC_r100ms_Start(void);
void LC_r100ms(void);
void LCEN_100ms(void);
void LCADEN_r100ms(void);
void LCADWB_r100ms(void);
void PWPUMP_r100ms(void);
void OCFOFRSM_r100ms(void);
void SSBARO_r100ms(void);
void tasks_100ms_Start(void);
void tasks_100ms(void);
void FLAST_200ms(void);
void IGKNP_200ms_Start(void);
void IGKNP_200ms(void);
void IGMIN_200ms(void);
void ESTM_200ms(void);
void IDCND_r200ms_Start(void);
void IDCND_r200ms(void);
void LCAD_r200ms(void);
void tasks_200ms_Start(void);
void tasks_200ms(void);
void SSTM_1000ms(void);
void SSTA_1000ms(void);
void CSPAM_1000ms(void);
void CSMAFTP_1000ms(void);
void FLECO_r1s(void);
void tasks_1000ms(void);



#endif                                 /* _RTW_HEADER_Controller_private_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
