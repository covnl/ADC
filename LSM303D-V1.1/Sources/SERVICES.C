#include "SERVICES.H"

uint32 LowPassT_U16(uint32 memory, uint16 in, uint16 T)
{
  uint32 dy, xs = (uint32)in<<16, temp = memory;

  if (T == 0) T = 1;			   /* avoid dividing by 0 */
  if (xs != temp)
  {
     if(xs > temp)
     {
        dy = (xs - temp) / T;
		if (dy == 0) dy = 1;
        temp += dy;
	 }
	 else
	 {
        dy = (temp - xs) / T;
		if (dy == 0) dy = 1;
        temp -= dy;
	 }
  }
  return temp;
}

sint32 LowPassT_S16(sint32 memory, sint16 in, uint16 T)
{
  sint32 xs = (uint32)in<<16, temp = memory;
  uint32 dy;

  if (T == 0) T = 1;			   /* avoid dividing by 0 */
  if (xs != temp)
  {
     if(xs > temp)
     {
        dy = (uint32)(xs - temp) / T;
		if (dy == 0) dy = 1;
        temp += (sint32)dy;
	 }
	 else
	 {
        dy = (uint32)(temp - xs) / T;
		if (dy == 0) dy = 1;
        temp -= (sint32)dy;
	 }
  }
  return temp;
}

uint16 LowPassT_U8(uint16 memory, uint8 in, uint8 T)
{
  uint32 dy, xs = (uint16)in<<8, temp = memory;

  if (T == 0) T = 1;			   /* avoid dividing by 0 */
  if (xs != temp)
  {
     if(xs > temp)
     {
        dy = (xs - temp) / T;
		    if (dy == 0) dy = 1;
        temp += dy;
	   }
	   else
	   {
        dy = (temp - xs) / T;
		    if (dy == 0) dy = 1;
        temp -= dy;
	   }
  }
  return temp;
}


sint16 LowPassT_S8(sint16 memory, sint8 in, uint8 T)
{
  sint32 xs = (uint16)in<<8, temp = memory;
  uint32 dy;

  if (T == 0) T = 1;			   /* avoid dividing by 0 */
  if (xs != temp)
  {
     if(xs > temp)
     {
        dy = (uint32)(xs - temp) / T;
		if (dy == 0) dy = 1;
        temp += (sint32)dy;
	 }
	 else
	 {
        dy = (uint32)(temp - xs) / T;
		if (dy == 0) dy = 1;
        temp -= (sint32)dy;
	 }
  }
  return temp;
}

sint32 LowPassK_S16(sint32 memory, sint16 in, uint16 K)
{
   sint32 temp = memory;
   temp += ((sint32)in - (temp>>16))* K;
   return temp;
}

sint16 LowPassK_S8(sint16 memory, sint8 in, uint8 K)
{
   sint32 temp = memory;
   temp += ((sint32)in - (temp>>8))* K;
   return (sint16)temp;
}

uint32 LowPassK_U16(uint32 memory, uint16 in, uint16 K)
{
   uint32 temp = memory>>16;

   if (in >= temp)
      temp = memory + (in - temp) * K;
   else
      temp = memory - (temp - in) * K;

   return temp;
}

uint16 LowPassK_U8(uint16 memory, uint8 in, uint8 K)
{
   uint32 temp = memory>>8;

   if (in >= temp)
      temp = memory + (in - temp) * K;
   else
      temp = memory - (temp - in) * K;

   return (uint16)temp;
}

/*Integrator*/
/*------------------------------------------------------------*/

uint32 IntegratorT_S16U16(uint32 memory, sint16 in, uint16 T)
{
	uint32 x = memory, y, z;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
    if (in < 0){ 
        y = ((uint32)(-in)<<16) / T;
        if(x > y) z = x - y;	
        else z = 0;			        /* avoid underflow */
	}  
	else{
		y = ((uint32)in<<16) / T;
	        z = x + y;
		if(z < x) z = MAXUINT32;	/* avoid overflow */
	}
	return z;
}

uint16 IntegratorT_S8U8(uint16 memory, sint8 in, uint8 T)
{
	uint32 x = memory, y, z;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
    if (in < 0){ 
        y = ((uint32)(-in)<<8) / T;
        if(x > y) z = x - y;	
        else z = 0;			        /* avoid underflow */
	}  
	else{
		y = ((uint32)in<<8) / T;
	        z = x + y;					/*no overflow*/
	}
	return (uint16)z;
}

uint32 IntegratorT_U16(uint32 memory, uint16 in, uint16 T)
{
	uint32 x, y, z;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
	x = memory;
	y = (((uint32)in<<16) / T);
	z = x + y;
    if (z < x)
        z = MAXUINT32;				/* avoid overflow */
	return z;
}


uint16 IntegratorT_U8(uint16 memory, uint8 in, uint8 T)
{
	uint32 temp = memory;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
	temp += (((uint32)in<<8) / T);	/*no overflow*/
	return (uint16)temp;
}

sint32 IntegratorT_S16(sint32 memory, sint16 in, uint16 T)
{
	sint32 x, y, z;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
	x = memory;
	y = (((sint32)in<<16) / T);
	z = x + y;
	if (x < 0)
	{
		if (z > y) z = MINSINT32; /* avoid underflow */
	}
	else
	{
		if (z < y) z = MAXSINT32;	/* avoid overflow */
	}
	return z;
}

sint16 IntegratorT_S8(sint16 memory, sint8 in, uint8 T)
{
	sint32 temp = memory;
	if (T == 0) T = 1;			   /* avoid dividing by 0 */
	temp += (((sint32)in<<8) / T);	  /*no overflow*/
	return (sint16)temp;
}

/*------------------------------------------------------------*/
/*IntegratorK */
uint32 IntegratorK_S16U16(uint32 memory, sint16 in, uint16 K)
{
   uint32 temp = memory;
   	if (in < 0)
		temp = temp - (uint32)(-in) * K;
	else
		temp = temp + (uint32)in * K;
   return temp;
}

uint16 IntegratorK_S8U8(uint16 memory, sint8 in, uint8 K)
{
   uint32 temp = memory;
   	if (in < 0)
		temp = temp - (uint32)(-in) * K;
	else
		temp = temp + (uint32)in * K;
   return (uint16)temp;
}

sint32 IntegratorK_S16(sint32 memory, sint16 in, uint16 K)
{
   sint32 temp = memory;
   temp += (sint32)in * K;
   return temp;
}

sint16 IntegratorK_S8(sint16 memory, sint8 in, uint8 K)
{
   sint32 temp = memory;
   temp += (sint32)in * K;
   return (sint16)temp;
}

uint32 IntegratorK_U16(uint32 memory, uint16 in, uint16 K)
{
   uint32 temp = memory;
   temp += (uint32)in * K;
   return temp;
}

uint16 IntegratorK_U8(uint16 memory, uint8 in, uint8 K)
{
   uint32 temp = memory;
   temp += (uint32)in * K;
   return (uint16)temp;
}


