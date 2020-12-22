#line 1 "C:/Users/Sahil/Desktop/PIC Project/keypad/source_code/main.c"
#line 1 "c:/users/sahil/desktop/pic project/keypad/source_code/types.h"



 typedef unsigned char u8;
 typedef signed char s8;
 typedef unsigned int u16;
 typedef signed int s16;
 typedef unsigned long u32;
 typedef signed long s32;
#line 2 "C:/Users/Sahil/Desktop/PIC Project/keypad/source_code/main.c"
extern void keyscan();
void init_uc()
{
 TRISA=0x00;
 TRISB=0x00;
 TRISC=0xF0;
 ANSEL=0x00;
 ANSELH=0x00;
}

main()
{
 init_uc();

 while(1)
 {
 keyscan();


 PORTA=0x00;PORTB=0x00;
 }
}
