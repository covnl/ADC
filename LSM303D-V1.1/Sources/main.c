/*******************************************************************************/
/**
  \mainpage
  
  \n Copyright (c) 2009 COMPANY_XXX
  \n COMPANY_Confidential_Proprietary
  
  \brief        Small Engine Control System
  \author       COMPANY_XXX
  \project      SEMS
  \version      0.2
  \date         November/2008   
*/
/*                                                                             */
/*******************************************************************************/

#include "typedefs.h"           

extern UINT8 *pu8SCI_Receive_Data_ptr;
extern Receive_Com asc0_CommunicationBuf;




/*-- Main Code ----------------------------------------------------------------*/
void main(void)
{ 
    /* Initialize auxiliary variables */             
    Powerup_Interface();
    //===================== 2011-9-16解决第一次刷写完后联机失败的问题
    pu8SCI_Receive_Data_ptr = &(asc0_CommunicationBuf.b_receive[0]);
    /*-- While Power-savings mode is NOT requested --*/
    for(;;)
    {
       /* Execute Multi-thread round robin task scheduler */
        vfnTask_Scheduler();   
    }
}
/*******************************************************************************/
