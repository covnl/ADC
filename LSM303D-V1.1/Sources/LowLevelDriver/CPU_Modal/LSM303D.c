#include "typedefs.h"
 
#define Buf_SIZE  10   //������� 10������
 
int16_t  lastAx;
int16_t  lastAy;
int16_t  lastAz;
int16_t  lastMx;
int16_t  lastMy;
int16_t  lastMz;          

//INT32  int32_tsum;
//INT32  sum;
static int16_t  LSM303_FIFO[6][Buf_SIZE];
static uint8_t Wr_IndexAcc = 0,Wr_IndexMag = 0;
//�����Ʊ궨ֵ
static int16_t Mag_Offset_X = 0;
static int16_t Mag_Offset_Y = 0;
static int16_t Mag_Offset_Z = 0;

static int16_t Acc_Offset_X = -135;
static int16_t Acc_Offset_Y = -250;
static int16_t Acc_Offset_Z = +500;
 
static int  Mag_Scale_X = 1.0f;
static int  Mag_Scale_Y = 1.0f;
static int  Mag_Scale_Z = 1.0f;
                                    
//��ǰ�ų������ֵ����Сֵ
int16_t  Mag_maxx=0;
int16_t  Mag_maxy=0;
int16_t  Mag_maxz=0;
int16_t  Mag_minx=-0;
int16_t  Mag_miny=-0;
int16_t  Mag_minz=-0;

unsigned char Mag_calib=0; //��ʼ����ɱ�־


extern  INT16 VAL_Acc_offset_X;
extern  INT16 VAL_Acc_offset_Y;
extern  INT16 VAL_Acc_offset_Z;



void LSM303D_delay(UINT16 LSM303D_delay)
{
    while(LSM303D_delay--); 
}
 
 
//���һ���µ�ֵ�� �¶ȶ��� �����˲�
static void LSM303_NewValAcc(int16_t* buf,int16_t val) {
 
  buf[Wr_IndexAcc] = val;
 
}
 
//���һ���µ�ֵ�� �¶ȶ��� �����˲�
static void LSM303_NewValMag(int16_t* buf,int16_t val) {
 
  buf[Wr_IndexMag] = val;
 
}
 
static int16_t LSM303_GetAvg(int16_t* buf)
{
 
    int i;
    int32_t sum = 0;
    for(i=0;i<Buf_SIZE;i++)
    sum += buf[i];
    sum = sum / Buf_SIZE;
    return (int16_t)sum;
 
} 


void  write_reg (UINT8 reg , UINT8 data)
{   
    LSM303D_delay(50);
    LSM303D_CS = LOW;
    LSM303D_delay(50);
    SPI_Write(0x7F&reg);   
    LSM303D_delay(50);
    SPI_Write(data);
    LSM303D_delay(50);
    LSM303D_CS = HIGH;
    LSM303D_delay(50);
  
}



void  read_reg (UINT8 reg,UINT8 size , UINT8 *addr)
{
    UINT8 data = 0;
    UINT8 i;
    LSM303D_delay(50);
    LSM303D_CS = LOW;
    LSM303D_delay(50);
    if(size<=1) 
    {
        SPI_Write(0x80|reg);
    }
    else
    {
        SPI_Write(0xC0|reg);
    }
    
    LSM303D_delay(50);
    SPI_Read();
    for(i=0;i<size;i++)
    {

        LSM303D_delay(50);
        *addr = SPI_Read();
        addr++; 
    }
    LSM303D_delay(50);
    LSM303D_CS = HIGH;
    //return data;
}

 // Accelerometer 
 // anti-alias filter bandwidth 194Hz
 // AFS = 0 (+/- 2 g full scale)
                  

void LSM303_Initial(void)
{
 
    int16_t temp[3];
    int i;
 
  // Accelerometer
      // anti-alias filter bandwidth 194Hz
      // AFS = 0 (+/- 2 g full scale)
    write_reg(CTRL2, 0x48);
 
    // AODR = 1001 (800 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
    write_reg(CTRL1, 0x97);
    
  // Magnetometer
    // M_RES = 11 (high resolution mode); M_ODR = 101 (100 Hz ODR)
    write_reg(CTRL5, 0x74);
 
    // 0x20 = 0b00100000
    // MFS = 01 (+/- 4 gauss full scale)
    write_reg(CTRL6, 0x20);
 
    // MLP = 0 (low power mode off); MD = 00 (continuous-conversion mode)
    write_reg(CTRL7, 0x00);
 
    Acc_Offset_X = VAL_Acc_offset_X;
    Acc_Offset_Y = VAL_Acc_offset_Y;
    Acc_Offset_Z = VAL_Acc_offset_Z;
}
 
//��ȡ���ٶ�����
 
void LSM303_readAcc(int16_t *acc)
{ 
    u8 buf[6];
    int16_t temp[3];
    
    LSM303_CSL();
    read_reg (0x28,6,buf);
    LSM303_CSH();
    temp[0] = -(int16_t)(buf[1] << 8 | buf[0]);  //Ax
    temp[1] = -(int16_t)(buf[3] << 8 | buf[2]);  //Ay
    temp[2] = (int16_t)(buf[5] << 8 | buf[4]);  //Az
    
    temp[0] -= Acc_Offset_X;
    temp[1] -= Acc_Offset_Y;
    temp[2] -= Acc_Offset_Z;
    
    LSM303_NewValAcc(&LSM303_FIFO[0][0],temp[0]);
    LSM303_NewValAcc(&LSM303_FIFO[1][0],temp[1]);
    LSM303_NewValAcc(&LSM303_FIFO[2][0],temp[2]);
    
    acc[0] = LSM303_GetAvg(&LSM303_FIFO[0][0]);  //Ax
    acc[1] = LSM303_GetAvg(&LSM303_FIFO[1][0]);  //Ay
    acc[2] = LSM303_GetAvg(&LSM303_FIFO[2][0]);  //Az
    
    //LSM303_NewValAcc(&LSM303_FIFO[0][0],acc[0]);
    //LSM303_NewValAcc(&LSM303_FIFO[1][0],acc[1]);
    //LSM303_NewValAcc(&LSM303_FIFO[2][0],acc[2]);
    
    Wr_IndexAcc = (Wr_IndexAcc + 1) % Buf_SIZE;
    lastAx = acc[0];
    lastAy = acc[1];
    lastAz = acc[2];
}
 
//��ȡ����������
void LSM303_readMag(int16_t *Mag)

{
 
    u8 buf[6];
    int16_t temp[3];
    LSM303_CSL();
    read_reg(0x08,6,buf);
    //SPI3_readRegs(D_OUT_X_L_M|0x40,6,buf);
    LSM303_CSH();
    temp[0] = -(int16_t)(buf[1] << 8 | buf[0]); //Mx
    temp[1] = -(int16_t)(buf[3] << 8 | buf[2]); //My
    temp[2] = (int16_t)(buf[5] << 8 | buf[4]);  //Mz
    LSM303_NewValMag(&LSM303_FIFO[3][0],temp[0]);
    LSM303_NewValMag(&LSM303_FIFO[4][0],temp[1]);
    LSM303_NewValMag(&LSM303_FIFO[5][0],temp[2]);
    Wr_IndexMag = (Wr_IndexMag + 1) % Buf_SIZE;
    Mag[0] = (LSM303_GetAvg(&LSM303_FIFO[3][0])-Mag_Offset_X)*Mag_Scale_X;  //Mx
    Mag[1] = (LSM303_GetAvg(&LSM303_FIFO[4][0])-Mag_Offset_Y)*Mag_Scale_Y;  //My
    Mag[2] = (LSM303_GetAvg(&LSM303_FIFO[5][0])-Mag_Offset_Z)*Mag_Scale_Z;  //Mz
    lastMx = Mag[0];
    lastMy = Mag[1];
    lastMz = Mag[2];
    if(Mag_calib)
    {
        //У����Ч�Ļ� �ɼ��궨ֵ
        if(Mag_minx>Mag[0])Mag_minx=(int16_t)Mag[0];
        if(Mag_miny>Mag[1])Mag_miny=(int16_t)Mag[1];
        if(Mag_minz>Mag[2])Mag_minz=(int16_t)Mag[2];
         
        if(Mag_maxx<Mag[0])Mag_maxx=(int16_t)Mag[0];
        if(Mag_maxy<Mag[1])Mag_maxy=(int16_t)Mag[1];
        if(Mag_maxz<Mag[2])Mag_maxz=(int16_t)Mag[2];
     
    }
 
}
 
/**************************ʵ�ֺ���********************************************
*����ԭ��:  void MagL_Start_Calib(void)
*��������:   ��������Ʊ궨
���������    
���������  ��
*******************************************************************************/
void LSM303_Start_Calib(void)
{
 
Mag_calib=1;//��ʼ�궨
Mag_maxx=0;//��ԭ���ı궨ֵ���
Mag_maxy=0;
Mag_maxz=0;
Mag_minx=-0;
Mag_miny=-0;
Mag_minz=-0;
 
}
 
/**************************ʵ�ֺ���********************************************
*����ԭ��:  void MagL_Save_Calib(void)
*��������:  ��������Ʊ궨ֵ ��Flash
���������    
���������  ��
*******************************************************************************/
/*void LSM303_Save_Calib(void){
 
//�������Ʊ궨ֵд�� Flash ����
Config.Magnetic_offset_X = Mag_Offset_X = (Mag_maxx+Mag_minx)/2;
Config.Magnetic_offset_Y = Mag_Offset_Y = (Mag_maxy+Mag_miny)/2;
Config.Magnetic_offset_Z = Mag_Offset_Z = (Mag_maxz+Mag_minz)/2;
 
Config.Magnetic_Scale_X = Mag_Scale_X = 1.0f;
Config.Magnetic_Scale_Y = Mag_Scale_Y = 1.0f;
Config.Magnetic_Scale_Z = Mag_Scale_Z = 1.0f;
 
AT45DB_Write_config(); //д��AT45DB ���棬�´��ϵ��ȡʹ��
Mag_calib=0; //�����궨
 
 
}//MagL_Save_Calib()*/ 
 
//------------------End of File----------------------------