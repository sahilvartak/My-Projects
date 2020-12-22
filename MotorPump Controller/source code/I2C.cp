#line 1 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/I2C.c"
#line 1 "c:/users/sahil/desktop/pic project/motor_counter/source code/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 1 "c:/users/sahil/desktop/pic project/motor_counter/source code/glcd.h"




extern void ctrl_off();
extern void delay(unsigned int j);
extern void display_on();
extern void display_off();
extern void set_column(unsigned char y);
extern void set_page(unsigned char x);
extern void set_start_line(unsigned char l);
extern void lcd_data(const unsigned char *value,unsigned int limit);
extern void lcd_puts1(unsigned char y,unsigned char x,unsigned char *str);
extern void lcd_puts2(unsigned char y,unsigned char x,unsigned char *str);
extern void lcd_puts2_const(unsigned char y,unsigned char x,const unsigned char *str);
extern void picture(const unsigned char * val);
extern void clr_lcd();
extern void init_lcd();
#line 4 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/I2C.c"
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
 p_sec=sec;p_mins=mins;p_hrs=hrs;p_date=date;p_month=month;p_year=year;
 sec=Bcd2Dec(read_I2C(0xD0,0x00));
 delay_ms(10);
 mins=Bcd2Dec(read_I2C(0xD0,0x01));
 delay_ms(10);
 hrs=Bcd2Dec(read_I2C(0XD0,0x02));
 delay_ms(10);
 date=Bcd2Dec(read_I2C(0XD0,0x04));
 delay_ms(10);
 month=Bcd2Dec(read_I2C(0XD0,0x05));
 delay_ms(10);
 year=Bcd2Dec(read_I2C(0XD0,0x06));
 delay_ms(10);

 if(p_date!=date){ByteToStr(date,temp); lcd_puts2(30,1,temp+1); if(date<10) lcd_puts2(30,1,"0");}
 if(p_month!=month){ByteToStr(month,temp); lcd_puts2(47,1,temp+1); if(month<10) lcd_puts2(47,1,"0");}
 if(p_year!=year){ByteToStr(year,temp); lcd_puts2(75,1,temp+1);}

 if(p_hrs!=hrs){ByteToStr(hrs,temp); lcd_puts2(30,2,temp+1); if(hrs<10) lcd_puts2(30,2,"0");}
 if(p_mins!=mins){ByteToStr(mins,temp); lcd_puts2(47,2,temp+1); if(mins<10) lcd_puts2(47,2,"0");}
 if(p_sec!=sec){ByteToStr(sec,temp); lcd_puts2(65,2,temp+1); if(sec<10) lcd_puts2(65,2,"0");}

}
