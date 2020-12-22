#line 1 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/EEPROM.c"
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
#line 8 "C:/Users/Sahil/Desktop/PIC Project/motor_counter/source code/EEPROM.c"
extern u8 sec,mins,hrs,day,date,month,year,pattern;
extern u8 pre_intensity[7],cur_intensity[7];
extern const u8 patt[4][16];

void sel_patt()
{
 s8 i=0;
 while(!ENTER);
 while(ENTER)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,6,"PATTERN");
 Lcd_Out(2,1,patt[i]);
 Lcd_Chr(1,16,'^');
 Lcd_Chr(2,16,'v');
 while(UP&&DOWN&&ENTER&&MENU);
 if(!UP){ i++; while(!UP); }
 else if(!DOWN){ i--;while(!DOWN);}
 else if(!MENU) break;
 if(i<0) i=6;
 if(i>6) i=0;
 }
 while(!MENU);
 pattern=i;

}




void save_data(u8 tim)
{
 u8 flag=0,j,val[4],row=0,col=0;
 s8 inten[7];
 u16 addr;
 Lcd_Cmd(_LCD_CLEAR);
 lcd_out(1,1,"W:");
 lcd_out(1,7,"B:");
 lcd_out(1,13,"U:");
 lcd_out(2,1,"V:");
 lcd_out(2,7,"G:");
 lcd_out(2,13,"R:");

 if(pattern==1) addr=0x0000;
 else if(pattern==2) addr=0x00A9;
 else if(pattern==3) addr=0x0152;
 else if(pattern==4) addr=0x01FB;
 else if(pattern==5) addr=0x0202;
 else if(pattern==6) addr=0x0209;




 for(j=0;j<7;j++)
 {
 if(pattern<=3)
 inten[j]=read_I2C(0xA0,(addr+(7*tim)+j));
 else
 inten[j]=read_I2C(0XA0,(addr+j));

 if(j==0) PWM1_Set_Duty(inten[j]*100);
 else if(j==1) PWM2_Set_Duty(inten[j]*100);
 else if(j==2) PWM3_Set_Duty(inten[j]*100);
 else if(j==3) PWM4_Set_Duty(inten[j]*100);
 else if(j==4) write_I2C(0xD2,0x01,inten[j]);
 else if(j==5) write_I2C(0xD2,0x02,inten[j]);
 }

 ByteToStr(inten[0]*10,val); lcd_out(1,3,val+1);
 ByteToStr(inten[1]*10,val); lcd_out(1,9,val+1);
 ByteToStr(inten[2]*10,val); lcd_out(1,15,val+1);
 ByteToStr(inten[3]*10,val); lcd_out(2,3,val+1);
 ByteToStr(inten[4]*10,val); lcd_out(2,9,val+1);
 ByteToStr(inten[5]*10,val); lcd_out(2,15,val+1);

 lcd_cmd(_LCD_UNDERLINE_ON);
 for(j=0;j<6;j++)
 {
 if(j==0){row=1 ; col=3;}
 else if(j==1){row=1; col=9;}
 else if(j==2){row=1 ; col=15;}
 else if(j==3){row=2 ; col=3;}
 else if(j==4){row=2; col=9;}
 else if(j==5){row=2; col=15;}
 while(ENTER)
 {
 if(!UP)
 {
 inten[j]++;
 if(inten[j]>9) inten[j]=0;
 ByteToStr((inten[j])*10,val);
 lcd_out(row,col,val+1);
 flag=1;
 while(!UP);
 }
 else if(!DOWN)
 {
 inten[j]--;
 if(inten[j]<0) inten[j]=9;
 ByteToStr((inten[j])*10,val);
 lcd_out(row,col,val+1);
 flag=1;
 while(!DOWN);
 }
 else if(!MENU) break;
 if(flag==1)
 {
 flag=0;
 if(j==0) PWM1_Set_Duty(inten[j]*100);
 else if(j==1) PWM2_Set_Duty(inten[j]*100);
 else if(j==2) PWM3_Set_Duty(inten[j]*100);
 else if(j==3) PWM4_Set_Duty(inten[j]*100);
 else if(j==4) write_I2C(0xD2,0x01,inten[j]);
 else if(j==5) write_I2C(0xD2,0x02,inten[j]);
 }
 }
 while(!ENTER);
 while(!MENU);
 if(pattern<=3)
 write_I2C(0xA0,(addr+(7*tim)+j),inten[j]);
 else
 write_I2C(0xA0,(addr+j),inten[j]);

 }
 lcd_cmd(_LCD_CURSOR_OFF);
}
