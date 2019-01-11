/* IMU.c file
编写者：lisn3188
网址：www.chiplab7.com
作者E-mail：lisn3188@163.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2012-06-25
测试： 本程序已在第七实验室的[Captain 飞控板]上完成测试
 
占用STM32 资源：
1. 使用Tim7定时器 产生us级的系统时间
 
功能：
姿态解算 IMU
将传感器的输出值进行姿态解算。得到目标载体的俯仰角和横滚角 和航向角
------------------------------------
 */
 
#include "typedefs.h"
#include "math.h"

float   pitch_offset;
float   roll_offset;
int16_t Roll_Angle_Output;
int16_t Pitch_Angle_Output;
extern INT16  VAL_Pitch_offset ;
extern INT16  VAL_Roll_offset ;




float g_xz;
float g_yz;
float g_xyz;
uint16  g_output; 
int16_t Facc;
int16_t X_acc;
int16_t  INT_g_xz;
int16_t  INT_g_yz;
int16_t  INT_g_xyz;
float  x,y,z;
UINT16 Acc_g;
int16_t gravity_X;
  
extern  UINT16 VAL_Acc_g;

 
void IMU_Init(void) 
{
    pitch_offset = (float)VAL_Pitch_offset / 100;
    roll_offset = (float)VAL_Roll_offset / 100;
    Acc_g = VAL_Acc_g;
}
 
void IMU_Get_Pitch_Roll_Acc_r10ms (void)
{
    int16_t AccBuffer[3];
    float temp;
    float roll_temp;
    float pitch_temp;
    float roll;
    float pitch;
    float PitchAng_output_temp;
    float RollAng_output_temp;
    
    float fSinPitch;
    float fNormAcc;    
    float alpha;
    
    LSM303_readAcc(&AccBuffer[0]);
    
    ///x轴为倾斜角，y轴为横滚角， x轴正向为车头方向
    
    x = AccBuffer[0];
    y = AccBuffer[1];
    z = AccBuffer[2];
    
    if(y == 0) y = 1;
    temp =  z / y;
    temp = 0 - temp;
    roll_temp = atan(temp);
    
    if(x == 0) x = 1;
    temp = z / x;
    temp = 0 - temp;    
    pitch_temp= atan(temp);
                                                  
    if(AccBuffer[1] > 0)
    {
        roll = -( roll_temp * 180 / PI + 90);
    } 
    else
    {
        roll = -( roll_temp * 180 / PI - 90); 
    }
    
    if(AccBuffer[0] < 0)
    {
        pitch = (pitch_temp * 180 / PI - 90);
    
    }
    else
    {
        pitch = (pitch_temp *180 / PI + 90);
    }
    
    if(pitch_offset>0)
    {
        if((pitch - pitch_offset)<-180)
        {
            PitchAng_output_temp = 360+(pitch - pitch_offset);
        } 
        else
        {
            PitchAng_output_temp = pitch - pitch_offset ;    
        }     
    } 
    else 
    {   
        if((pitch - pitch_offset)>180)
        {
            PitchAng_output_temp = -360+(pitch - pitch_offset);
        } 
        else
        {
            PitchAng_output_temp = pitch - pitch_offset ;
        }
    }
  
    if(roll_offset>0)
    {
        if((roll - roll_offset)<-180)
        {
            RollAng_output_temp = 360+(roll - roll_offset);
        } 
        else
        {         
            RollAng_output_temp = roll - roll_offset ;    
        }     
    } 
    else 
    { 
        if(roll - roll_offset>180)
        {
            RollAng_output_temp = -360+(roll - roll_offset);
        } 
        else
        {
            RollAng_output_temp = roll - roll_offset ;
        }
    }
   
    Roll_Angle_Output = (int16_t)(RollAng_output_temp*100);
     
    Pitch_Angle_Output = (int16_t)(PitchAng_output_temp*100);
   
   
     
    g_xz=sqrt(((double)x*x)+((double)z*z));
    g_yz=sqrt(((double)y*y)+((double)z*z));
    g_xyz=sqrt(((double)x*x)+((double)y*y)+((double)z*z));
    
    g_output = (uint16)g_xyz;
    
    INT_g_xz = (int16_t)g_xz;
    INT_g_yz = (int16_t)g_yz;
    INT_g_xyz = (int16_t)g_xyz;
               
    //fNormAcc =(float) sqrt(((float)AccBuffer[0]*AccBuffer[0])+((float)AccBuffer[1]*AccBuffer[1])+((float)AccBuffer[2]*AccBuffer[2]));
       
    //fSinPitch = ((float)AccBuffer[1])/fNormAcc;           
      
    
   /*    if( PitchAng_output >= 0)
       { 
         Facc= (int16_t)(y - g*fSinPitch);
       }
        
       else
       {
          Facc=  (int16_t)(g*fSinPitch - y);
       }
     //deviation_acc=y - init_y;
                                          
      
      Y_acc = (int32_t)Facc * 9800 / g;    */
   
    /* if( PitchAng_output >= 0)
     {

      if(sqrt(y)>=sqrt(g*fSinPitch)) 
      {
        Facc = g*fSinPitch - y;
      }
       else
       {
          Facc= g*fSinPitch - y;
       }

      }

      
      else
       {
         if(sqrt(y)>=sqrt(g*fSinPitch))
         {
           Facc = g*fSinPitch - y;
         }
         
          else
       {
          Facc= g*fSinPitch - y;
       }        
         
       }  */
       
       
      // Facc = (int16_t)(Acc_g*fSinPitch - y);
      // Y_acc = (int32_t)Facc * 980 / Acc_g;
                 
      
      alpha = 0.8;
      
      /*gravity_Y = alpha*gravity_Y + (1 - alpha)*y; 
      
      Facc = y - gravity_Y ;
      
      Y_acc = (int32_t)Facc * 980 / Acc_g;*/
      
      gravity_X = alpha*gravity_X + (1 - alpha)*x; 
      
      Facc = x - gravity_X ;
      
      X_acc = (int32_t)Facc * 980 / Acc_g;
 }
  
  

