#ifndef __IMU_H
#define __IMU_H
 
//#include "common.h"
 
#define PI  M_PI

#define M_PI  (float)3.1415926535
 

void IMU_Init(void); //初始化
void IMU_Get_Pitch_Roll_Acc_r10ms(void); //更新姿态  需要定期调用
//uint32_t micros(void);//读取系统上电后的时间  单位 us
 
#endif
 