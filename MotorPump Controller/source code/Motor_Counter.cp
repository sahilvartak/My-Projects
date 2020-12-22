#line 1 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/Motor_Counter.c"
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
#line 1 "c:/users/sahil/desktop/pic project/motor_counter/source code/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 1 "c:/users/sahil/desktop/pic project/motor_counter/source code/i2c.h"
#line 1 "c:/users/sahil/desktop/pic project/motor_counter/source code/types.h"
#line 4 "c:/users/sahil/desktop/pic project/motor_counter/source code/i2c.h"
 extern void write_I2C(uint8_t sa_addr,uint16_t buf_addr,uint8_t dat);
 extern uint8_t read_I2C(uint8_t sa_addr,uint16_t buff_add);
 extern void Check_time(void);
#line 6 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/Motor_Counter.c"
const code uint8_t stop[]="STOP",start[]="START",pause[]="PAUSE";
uint8_t sec,p_sec,mins,p_mins,hrs,p_hrs,day,date,p_date,month,p_month,year,p_year;
extern const code char logo[];




void init_mcu()
{
 unsigned char i;
 TRISA=0x00;
 TRISB=0x01;
 TRISC=0x00;
 ANSEL = 0;
 ANSELH = 0;
}

void init_lcd()
{
 uint8_t i,temp[4];
 display_on();
 set_start_line(0);
 picture(&logo[0]);
 for(i=20;i>0;i--)
 delay(6500);
 clr_lcd();

 lcd_puts1(0,0,"*****SV-CORP****");
 lcd_puts2(0,1,"DATE:-"); lcd_puts2(42,1,":"); lcd_puts2(59,1,":"); lcd_puts2(65,1,"20");
 lcd_puts2(0,2,"TIME:-"); lcd_puts2(42,2,":"); lcd_puts2(59,2,":");

 lcd_puts2(0,4,"MOTOR:-"); lcd_puts2(37,4,"00");
 lcd_puts2(64,4,"ROT:-"); lcd_puts2(91,4,"00");
 lcd_puts2(0,5,"COMP:-"); lcd_puts2(32,5,"00");
 lcd_puts2(64,5,"REM:-"); lcd_puts2(91,5,"00");
 lcd_puts2(0,7,"STATUS:-"); lcd_puts2_const(42,7,stop);

}

void main()
{
 unsigned char i;
 init_mcu();
 init_lcd();
 while(1)
 Check_time();

}
