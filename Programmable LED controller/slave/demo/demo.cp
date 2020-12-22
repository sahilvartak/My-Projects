#line 1 "C:/Users/Sahil/Desktop/fish_tank/slave/demo/demo.c"
#line 15 "C:/Users/Sahil/Desktop/fish_tank/slave/demo/demo.c"
const Addy = 0xD2;
const Delay_Time = 250;



unsigned short j;
unsigned short rxbuffer;
unsigned short tx_data;

void Init(){
 ADCON1 = 0;
 TRISA = 0;
 TRISB = 0;
 TRISC = 0xFF;
 SSPADD = Addy;
 SSPCON = 0x36;
 PIE1.SSPIF = 1;
 INTCON = 0xC0;


 INTCON.GIE = 1;
 INTCON.PEIE = 1;
 PIE1.SSPIE = 1;
 PIE1.TMR1IE = 1;
 PIR1.TMR1IF = 0;
 PIR1.SSPIF = 0;
}

void interrupt(){

 if (PIR1.SSPIF == 1){
 PIR1.SSPIF = 0;


 if (SSPSTAT.R_W == 1){
 SSPBUF = tx_data;
 SSPCON.CKP = 1;
 j = SSPBUF;
 return;
 }
 if (SSPSTAT.BF == 0){
 j = SSPBUF;
 return;
 }


 if (SSPSTAT.D_A == 1){
 rxbuffer = SSPBUF;
 j = SSPBUF;
 return;
 }
 }
 j = SSPBUF;
}

void main(){
 Init();
 while(1){

 PORTB = rxbuffer;
 tx_data = PORTC;
 Delay_ms(Delay_Time);
 }
}
