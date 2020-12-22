#line 1 "C:/Users/Sahil/Desktop/fish_tank/flash/flash.c"
char i = 0;
unsigned int addr, data_, dataAR[4][4] = {{0x3FAA+0, 0x3FAA+1, 0x3FAA+2, 0x3FAA+3},
 {0x3FAA+4, 0x3FAA+5, 0x3FAA+6, 0x3FAA+7},
 {0x3FAA+8, 0x3FAA+9, 0x3FAA+10, 0x3FAA+11},
 {0x3FAA+12, 0x3FAA+13, 0x3FAA+14, 0x3FAA+15}};

void main() {
 ANSELA = 0;
 ANSELB = 0;
 ANSELC=0;
 C1ON_bit = 0;
 C2ON_bit = 0;
 PORTB = 0;
 TRISB = 0;
 PORTC = 0;
 TRISC = 0;
 Delay_ms(500);









 addr = 0x0430;
 for (i = 0; i < 4; i++){
 Delay_ms(100);
 FLASH_Write(addr+i*4, dataAR[i]);
 }
 Delay_ms(500);

 addr = 0x0430;
 for (i = 0; i < 16; i++){
 data_ = FLASH_Read(addr++);
 Delay_us(10);
 PORTB = data_;
 PORTC = data_ >> 8;
 Delay_ms(500);
 }
}
