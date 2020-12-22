#line 1 "C:/Users/Sahil/Desktop/PIC Project/keypad/source_code/keypad.c"
#line 1 "c:/users/sahil/desktop/pic project/keypad/source_code/types.h"



 typedef unsigned char u8;
 typedef signed char s8;
 typedef unsigned int u16;
 typedef signed int s16;
 typedef unsigned long u32;
 typedef signed long s32;
#line 32 "C:/Users/Sahil/Desktop/PIC Project/keypad/source_code/keypad.c"
char colscan(void)
{
 return( RC4_bit | RC5_bit | RC6_bit | RC7_bit );
}

void init_rows(void)
{
  RC0_bit = RC1_bit = RC2_bit = RC3_bit =1;
}

void init_cols(void)
{
  RC4_bit = RC5_bit = RC6_bit = RC7_bit =0;
}

void keyscan()
{
 init_cols();
 init_rows();
 PortB=0x00;PortA=0x00;
 if(colscan())
 {

  RC0_bit =1; RC1_bit = RC2_bit = RC3_bit =0;
 if(colscan())
 {
 if( RC4_bit ==1) {  RA0_bit =1;} delay_ms(100);
 if( RC5_bit ==1) {  RA1_bit =1;} delay_ms(100);
 if( RC6_bit ==1) {  RA2_bit =1;} delay_ms(100);
 if( RC7_bit ==1) {  RA3_bit =1;} delay_ms(100);
 }

  RC1_bit =1; RC0_bit = RC2_bit = RC3_bit =0;
 if(colscan())
 {
 if( RC4_bit ==1) { RA4_bit =1;} delay_ms(100);
 if( RC5_bit ==1) { RA5_bit =1;} delay_ms(100);
 if( RC6_bit ==1) { RA6_bit =1;} delay_ms(100);
 if( RC7_bit ==1) { RA7_bit =1;} delay_ms(100);
 }
  RC2_bit =1; RC0_bit = RC1_bit = RC3_bit =0;
 if(colscan())
 {
 if( RC4_bit ==1) { RB0_bit =1;} delay_ms(100);
 if( RC5_bit ==1) { RB1_bit =1;} delay_ms(100);
 if( RC6_bit ==1) { RB2_bit =1;} delay_ms(100);
 if( RC7_bit ==1) { RB3_bit =1;} delay_ms(100);
 }
  RC3_bit =1; RC0_bit = RC2_bit = RC1_bit =0;
 if(colscan())
 {
 if( RC4_bit ==1) { RB4_bit =1;} delay_ms(100);
 if( RC5_bit ==1) { RB5_bit =1;} delay_ms(100);
 if( RC6_bit ==1) { RB6_bit =1;} delay_ms(100);
 if( RC7_bit ==1) { RB7_bit =1;} delay_ms(100);
 }
}

}
