#line 1 "C:/Users/Sahil/Desktop/PIC Project/fish_tank/slave/Slave.c"



const Addy = 0xD2;
const Delay_Time = 250;



unsigned short j,pos=0;
unsigned short rxbuff[2];
unsigned short tx_data;

void Init(){
 ADCON1 = 0;
 TRISA = 0;
 TRISC = 0x03;
 SSPADD = Addy;
 SSPCON = 0x36;
 INTCON = 0xC0;
 INTCON.GIE = 1;
 INTCON.PEIE = 1;
 PIE1.SSP1IE = 1;
 PIE1.TMR1IE = 1;
 PIR1.TMR1IF = 0;
 PIR1.SSP1IF = 0;
}
void PWM_init()
{
 PWM1_Init(500);
 PWM2_Init(500);
 PWM3_Init(500);
 PWM1_Start();
 PWM2_Start();
 PWM3_Start();
}

void interrupt(){

 if (PIR1.SSP1IF == 1){

 PIR1.SSP1IF = 0;


 if ((SSPSTAT>>2)&1 == 1){
 SSPBUF = tx_data;
 SSPCON.CKP = 1;
 j = SSPBUF;
 return;
 }
 if (SSPSTAT&1 == 0){
 j = SSPBUF;
 return;
 }


 if ((SSPSTAT>>5)&1 == 1){
 rxbuff[pos] = SSPBUF;
 pos++;
 if(pos>1) pos=0;
 j = SSPBUF;
 return;
 }
 }
 j = SSPBUF;
}

void main()
{

 Init();
 PWM_init();

 while(1)
 {
 if(rxbuff[0]==1){PWM1_Set_Duty(rxbuff[1]*100);}
 else if(rxbuff[0]==2){ PWM2_Set_Duty(rxbuff[1]*100);}
 else if(rxbuff[0]==3){ PWM3_Set_Duty(rxbuff[1]*100);}

 }
}
