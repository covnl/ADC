
#ifndef _SERVICES_H_
#define _SERVICES_H_
//#include "tmwtypes.h"
#include "ctypes.H"

extern uint32 LowPassT_U16(uint32 memory, uint16 in, uint16 T);
extern sint32 LowPassT_S16(sint32 memory, sint16 in, uint16 T);
extern uint16 LowPassT_U8(uint16 memory, uint8 in, uint8 T);
extern sint16 LowPassT_S8(sint16 memory, sint8 in, uint8 T);

extern uint32 LowPassK_U16(uint32 memory, uint16 in, uint16 K);
extern sint32 LowPassK_S16(sint32 memory, sint16 in, uint16 K);
extern uint16 LowPassK_U8(uint16 memory, uint8 in, uint8 K);
extern sint16 LowPassK_S8(sint16 memory, sint8 in, uint8 K);

extern uint32 IntegratorT_S16U16(uint32 memory, sint16 in, uint16 T);
extern uint32 IntegratorT_U16(uint32 memory, uint16 in, uint16 T);
extern sint32 IntegratorT_S16(sint32 memory, sint16 in, uint16 T);
extern uint16 IntegratorT_S8U8(uint16 memory, sint8 in, uint8 T);
extern uint16 IntegratorT_U8(uint16 memory, uint8 in, uint8 T);
extern sint16 IntegratorT_S8(sint16 memory, sint8 in, uint8 T);

extern uint32 IntegratorK_S16U16(uint32 memory, sint16 in, uint16 K);
extern uint32 IntegratorK_U16(uint32 memory, uint16 in, uint16 K);
extern sint32 IntegratorK_S16(sint32 memory, sint16 in, uint16 K);
extern uint16 IntegratorK_S8U8(uint16 memory, sint8 in, uint8 K);
extern uint16 IntegratorK_U8(uint16 memory, uint8 in, uint8 K);
extern sint16 IntegratorK_S8(sint16 memory, sint8 in, uint8 K);

#endif /* _SERVICES_H_ */
