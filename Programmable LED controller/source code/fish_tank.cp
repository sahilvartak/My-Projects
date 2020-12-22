#line 1 "C:/Users/Sahil/Desktop/PIC Project/fish_tank/source code/fish_tank.c"
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/types.h"


 typedef unsigned char u8;
 typedef signed char s8;
 typedef unsigned int u16;
 typedef signed int s16;
 typedef signed long s32;
 typedef unsigned long u32;
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/i2c.h"
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/types.h"
#line 4 "c:/users/sahil/desktop/pic project/fish_tank/source code/i2c.h"
 extern void write_I2C(u8 sa_addr,u16 buf_addr,u8 dat);
 extern u8 read_I2C(u8 sa_addr,u16 buff_add);
 extern void Check_time(void);
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/lcd.h"


 extern void Init_disp();
 extern void Display_Time();
 extern void Transform_Time();
 extern void init_lcd();
 extern void menu_fnc();
 extern void config_Time(u8,u8);
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/button.h"
#line 1 "c:/users/sahil/desktop/pic project/fish_tank/source code/pwm.h"


 extern void Init_PWM();
 extern void Set_Intensity();
 extern void modify_pwm_ch();
#line 7 "C:/Users/Sahil/Desktop/PIC Project/fish_tank/source code/fish_tank.c"
u8 pattern=0,prev_hrs=0,prev_min=0,hrs=0,mins=0,sec=0,day=0,date=0,month=0,year=0;
u8 pre_intensity[7]={0},cur_intensity[7]={0};
void main()
{
 ANSELA = 0;
 ANSELB = 0;
 ANSELC=0;
 TRISA=0x33;
 TRISB=TRISC=0x00;
 LATA=LATB=LATC=0x00;
 Soft_I2C_Init();
 pattern=read_I2C(0xA0,0x0210);
 if(pattern>6) pattern==0;
 Init_PWM();
 Check_time();
 init_lcd();
 Display_Time();
 set_Intensity();
 prev_hrs=hrs;prev_min=mins;
 while(1)
 {

 if(! PORTA.RA0 )
 {
 menu_fnc();
 write_I2C(0xA0,0x0210,pattern);
 Check_time();
 init_lcd();
 Display_Time();
 set_Intensity();
 }
 if(prev_min!=mins){init_lcd(); Display_Time();}
 if(prev_hrs!=hrs){init_lcd(); Display_Time(); set_Intensity(); }
 Check_time();
 }
}
