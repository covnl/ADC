#ifndef __IMU_H
#define __IMU_H
 
//#include "common.h"
 
#define PI  M_PI

#define M_PI  (float)3.1415926535
 

void IMU_Init(void); //��ʼ��
void IMU_Get_Pitch_Roll_Acc_r10ms(void); //������̬  ��Ҫ���ڵ���
//uint32_t micros(void);//��ȡϵͳ�ϵ���ʱ��  ��λ us
 
#endif
 