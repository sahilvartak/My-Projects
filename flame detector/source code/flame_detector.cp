#line 1 "C:/Users/Sahil/Desktop/PIC Project/flame detector/source code/flame_detector.c"
#line 1 "c:/users/sahil/desktop/pic project/flame detector/source code/types.h"


 typedef unsigned char u8;
 typedef signed char s8;
 typedef unsigned int u16;
 typedef signed int s16;
 typedef signed long s32;
 typedef unsigned long u32;
#line 17 "C:/Users/Sahil/Desktop/PIC Project/flame detector/source code/flame_detector.c"
u16 adc_value;
u8 cor_pos;
void Stop()
{
  RC0_bit =0; RC1_bit =0;
  RC2_bit =0; RC3_bit =0;
}
void Rotate()
{

  RC0_bit =0; RC1_bit =1;
  RC2_bit =1; RC3_bit =0;
}

void Forward()
{
  RA4_bit =0;
  RC5_bit =1;
  RC0_bit =1; RC1_bit =0;
  RC2_bit =1; RC3_bit =0;
 delay_ms(200);
  RC5_bit =0;
  RA4_bit =1;

}
void main()
{
 u16 i;

 TRISA = 0x01;
 TRISC=0x00;
 ANSEL = 0x01;
 CMCON=0;
  RC5_bit =0;
 while(1)
 {

 adc_value = ADC_Read(0);

 if(adc_value> 200  && adc_value< 950 )
 {
  RC4_bit =0; Forward(); Rotate();delay_ms(5);
 }

 else if(adc_value< 200 )
 {
 Stop();  RC4_bit =1; delay_ms(5000);
 for(i=0;i<20;i++){ RC5_bit =1;  RA4_bit =1; delay_ms(1000);  RC5_bit =0;  RA4_bit =0; delay_ms(500);}
 for(i=0;i<1024;i++){ RA4_bit =1; delay_ms(1000);  RA4_bit =0; delay_ms(500);}
 }

 else
 {
  RC4_bit =0;
 Rotate();
 }
 }
}
