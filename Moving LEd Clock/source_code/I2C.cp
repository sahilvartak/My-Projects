#line 1 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source_code/I2C.c"
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source_code/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 3 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source_code/I2C.c"
sbit Soft_I2C_Scl at RC3_bit;
sbit Soft_I2C_Sda at RC4_bit;
sbit Soft_I2C_Scl_Direction at TRISC3_bit;
sbit Soft_I2C_Sda_Direction at TRISC4_bit;

extern uint8_t sec,p_sec,mins,p_mins,hrs,p_hrs,day,date,p_date,month,p_month,year,p_year;


void write_I2C(uint8_t sa_addr,uint16_t buf_addr,uint8_t dat)
{
 Soft_I2C_Start();
 Soft_I2C_Write(sa_addr | ((buf_addr>>7)&0x0E));
 Soft_I2C_Write((uint8_t)buf_addr&0xFF);
 Soft_I2C_Write(dat);
 Soft_I2C_Stop();
 Delay_ms(10);
}
uint8_t read_I2C(uint8_t sa_addr,uint16_t buf_addr)
{
 uint8_t buf=0;
 Soft_I2C_Start();
 Soft_I2C_Write(sa_addr | ((buf_addr>>7)&0x0E));
 Soft_I2C_Write((uint8_t)buf_addr&0xFF);
 Soft_I2C_Start();
 Soft_I2C_write(sa_addr|1);
 buf=Soft_I2C_Read(0);
 Soft_I2C_Stop();
 return buf;
}

void Check_time(void)
{
 uint8_t temp[4];
 p_sec=sec;
 sec=read_I2C(0xD0,0x00);
 delay_ms(10);
#line 58 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source_code/I2C.c"
}
