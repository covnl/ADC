/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2011 Freescale Semiconductor
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_bdm.c
*
* @brief  FreeMASTER BDM communication routines
*
* @version 1.1.1.0
* 
* @date Mar-21-2011
* 
*******************************************************************************/

#include "freemaster.h"
#include "freemaster_private.h"
#include "freemaster_protocol.h"

#if FMSTR_USE_BDM
/*******************************************************************************
*
* @brief    API: Main "Polling" call from the application main loop
*
*******************************************************************************/

void FMSTR_Poll(void)
{ 
;
}

#else /* FMSTR_USE_BDM */

/*lint -efile(766, freemaster_protocol.h) include file is not used in this case */

#endif /* FMSTR_USE_BDM */

