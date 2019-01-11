#ifndef _TYPES_H
#define _TYPES_H

/* Type for boolean values */
typedef unsigned char  bool;

/* Types for bitfields */
typedef unsigned char  bit8;
typedef unsigned short bit16;
typedef unsigned long  bit32;

/* These types are also declared in the ERCOS header file e_stddef.h */
typedef unsigned char  uint8;
typedef signed char    sint8;
typedef unsigned int   uint16;
typedef signed short   sint16;
typedef unsigned long  uint32;
typedef signed long    sint32;
typedef float          real32;
typedef double         real64;

#ifndef __E_TARTYP_H
/* These types are also declared in the ERCOS header file e_tartyp.h */
typedef unsigned long long uint64;
typedef signed long long   sint64;
#endif /* __E_TARTYP_H */

/* These types are included only for compatibility, they shouldn't be used any more! */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

//#define 	FALSE		0x00u			/* logic 0 with 8bit unsigned*/
//#define 	TRUE		0x01u			/* logic 0 with 8bit unsigned*/

/* limits of data types */ 
#define MAXUINT8        (0xffu)
#define MAXSINT8        (0x7f)
#define MINSINT8        (-(0x80))
#define MAXUINT16       (0xffffu)
#define MAXSINT16       (0x7fff)
#define MINSINT16       (-(0x8000))
#define MAXUINT32       (0xfffffffful)
#define MAXSINT32       (0x7fffffffl)
#define MINSINT32       (-(0x80000000l))
#define MAXREAL32       (3.40282347E38F)
#define MINREAL32       (1.17549435E-38F)
#define MAXREAL64       (1.7976931348623157E308)
#define MINREAL64       (2.2250738585072016E-308)

#endif
