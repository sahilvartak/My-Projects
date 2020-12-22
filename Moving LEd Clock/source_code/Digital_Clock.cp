#line 1 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source_code/Digital_Clock.c"
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source_code/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source_code/i2c.h"
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source_code/types.h"
#line 4 "c:/users/sahil/desktop/pic project/digital clock/source_code/i2c.h"
 extern void write_I2C(uint8_t sa_addr,uint16_t buf_addr,uint8_t dat);
 extern uint8_t read_I2C(uint8_t sa_addr,uint16_t buff_add);
 extern void Check_time(void);
#line 13 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source_code/Digital_Clock.c"
uint8_t sec,p_sec,mins,p_mins,hrs,p_hrs,day,date,p_date,month,p_month,year,p_year;
const uint8_t num_dat[][7]= {{0x70,0x88,0xC8,0xA8,0x98,0x88,0x70}, {0x20,0x30,0x20,0x20,0x20,0x20,0xF8},
 {0x70,0x88,0x80,0x40,0x20,0x10,0xF8}, {0xF8,0x40,0x20,0x40,0x80,0x88,0x70},
 {0x40,0x60,0x50,0x48,0xF8,0x40,0x40}, {0xF8,0x08,0x78,0x80,0x80,0x88,0x70},
 {0x60,0x10,0x08,0x78,0x88,0x88,0x70}, {0xF8,0x80,0x40,0x20,0x10,0x10,0x10},
 {0x70,0x88,0x88,0x70,0x88,0x88,0x70}, {0x70,0x88,0x88,0xF0,0x80,0x40,0x30}};
const uint8_t c5_c0[][7]={{0xF8,0x08,0x78,0x80,0x80,0x88,0x70},{0x70,0x88,0xC8,0xA8,0x98,0x88,0x70}};
uint8_t dat,i,j,m;
uint8_t k;


void display_time()
{
 for(j=0;j<10;j++)
 {
  RA0_bit =1; RA1_bit =0;
 for(k=0;k<7;k++)
 {
 dat=0x01;
 dat=dat<<k;
 PortB=~dat;
 PortD=~num_dat[(sec>>4)&0x0F][k]; delay_ms(1);
 }

  RA0_bit =0; RA1_bit =1;
 for(k=0;k<7;k++)
 {
 dat=0x01;
 dat=dat<<k;
 PortB=~dat;
 PortD=~num_dat[sec&0x0F][k];delay_ms(1);
 }
 }


}

void change_time()
{

 for(m=0;m<7;m++)
 {
 Check_time();
 for(j=0;j<10;j++)
 {
  RA0_bit =1; RA1_bit =0;
 for(k=0;k<7;k++)
 {
 dat=0x01;
 dat=dat<<k;
 PortB=~dat;
 if(((p_sec>>4)&0x0F==5)||p_sec<10){PortD=~c5_c0[0][k+m]; delay_ms(1);}
 else{PortD=~num_dat[((p_sec>>4)&0x0F)-1][k+m]; delay_ms(1);}

 }

  RA0_bit =0; RA1_bit =1;
 for(k=0;k<7;k++)
 {
 dat=0x01;
 dat=dat<<k;
 PortB=~dat;
 PortD=~num_dat[sec&0x0F][k];delay_ms(1);
 }
 }
 }
}
void init_uc()
{
 ADCON1=0x06;
 TRISB=0x00;
 TRISD=0x00;
 TRISA=0x00;



}

void main()
{
 init_uc();
 Check_time();
 while(1)
 {
 display_time();
 Check_time();
 if(((p_sec>>4)&0x0f)!=((sec>>4)&0x0f))
 change_time();
 }
}
