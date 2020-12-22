#line 1 "C:/Users/Sahil/Desktop/PIC Project/seven_seg_clock/source/seven_seg_clock.c"
#line 12 "C:/Users/Sahil/Desktop/PIC Project/seven_seg_clock/source/seven_seg_clock.c"
void ssrOut(unsigned char);
void pulseCS(void);
void init_MAX7219(void);
void writeMAX7219(char, char);

void delay_ms(int);
void init_18F2250(void);


extern void _startup( void );
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
#line 24 "C:/Users/Sahil/Desktop/PIC Project/seven_seg_clock/source/seven_seg_clock.c"
void _reset( void )
{
 _asm goto _startup _endasm
}
#pragma code
#line 31 "C:/Users/Sahil/Desktop/PIC Project/seven_seg_clock/source/seven_seg_clock.c"
int i, j, digit, count;

void main()
{
 init_18F2550();
 init_MAX7219();
 count = 9999;

 for (i=0; i<=count; i++) {
 j = i;

 digit = j % 10;
 writeMAX7219(1, digit);

 j = j / 10;
 digit = j % 10;
 writeMAX7219(2, digit);

 j = j / 10;
 digit = j % 10;
 writeMAX7219(3, digit);

 j = j / 10;
 digit = j % 10;
 writeMAX7219(4, digit);
 delay_ms(200);
 }
}





void ssrOut(unsigned char val) {
 int j;
 for(j=1; j<=8; j++) {
 unsigned char temp = val & 0x80;
 if (temp == 0x80)  PORTBbits.RB6  =  1 ;
 else  PORTBbits.RB6  =  0 ;
  PORTBbits.RB7  =  1 ;
  Delay10TCYx (20);
  PORTBbits.RB7  =  0 ;
 val = val << 1;
 }
}

void writeMAX7219(char address, char data) {
 if ((address < 1) || (address > 8)) return;
 ssrOut(address);
 ssrOut(data);
 pulseCS();
}


void pulseCS(void)
 {
  PORTBbits.RB5  =  1 ;
 delay_ms(1);
  PORTBbits.RB5  =  0 ;
}


void init_MAX7219(void)
{
  PORTBbits.RB5  =  0 ;

 ssrOut(0x09);

 ssrOut(0xFF);
 pulseCS();


 ssrOut(0x0A);
 ssrOut(0x0D);
 pulseCS();


 ssrOut(0x0B);

 ssrOut(0x03);
 pulseCS();



 for(i=1; i<=8; i++)
 {
 ssrOut(i);
 ssrOut(0x00);
 pulseCS();
 }


 ssrOut(0x0C);

 ssrOut(0x01);
 pulseCS();

}


void delay_ms(int i)
{
 long int j;
 for(j=0;j<i;j++)
 {
 Delay1KTCYx(12);
 }
}


void init_18F2250(void) {

 ADCON1=0x0F;

 CMCON=7;

 TRISB=0;

 PORTB=0;

 TRISA=0X30;

 TRISC=0X0F;

 INTCON2bits.RBPU=0;
}
