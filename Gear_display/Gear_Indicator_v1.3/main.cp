#line 1 "C:/Users/Sahil/Desktop/PIC Project/Gear_display/Gear_Indicator_v1.3/main.c"
#line 1 "c:/users/sahil/desktop/pic project/gear_display/gear_indicator_v1.3/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 13 "C:/Users/Sahil/Desktop/PIC Project/Gear_display/Gear_Indicator_v1.3/main.c"
uint8_t Gear;

void ShowDigit(uint8_t Digit)
{
 uint8_t i;

 PORTC |= (1 <<  0 );
 PORTC &= ~(1 <<  0 );

 for (i = 0; i < Digit; i++)
 {
 PORTC |= (1 <<  1 );
 PORTC &= ~(1 <<  1 );
 }
}

void Init()
{
 uint8_t i;
 ANSEL=0x00;
 TRISC = 0xFC;

 PORTC &= ~(1 <<  0 );



 ShowDigit(0);
 delay_ms(500);

 for (i = 1; i < 10; i++)
 {
 ShowDigit(i);
 delay_ms(100);
 }

 ShowDigit(0);
 delay_ms(500);

 Gear = EEPROM_Read(0);
 ShowDigit(Gear);
}

int Released(uint8_t Bit)
{
 if (Bit==1)
 {
 delay_ms( 50 );
 return 1;
 }

 return 0;
}

int main(void)
{
 Init();

 while(1)
 {
 if (Released( RC2_bit )) Gear = 0;
 if (Released( RC3_bit ))
 {
 if ((Gear > 0) && (Gear <  5 )) Gear++;
 if (Gear == 0) Gear = 2;
 if ( RC2_bit ==1) Gear = 0;
 }

 if (Released( RC4_bit ))
 {
 if (Gear > 1) Gear--;
 if (Gear == 0) Gear = 1;
 if ( RC2_bit ==1) Gear = 0;
 }

 ShowDigit(Gear);
 EEPROM_Write(0,Gear);
 delay_ms( 250 );
 }
}
