#line 1 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/APP.c"
#line 1 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/app.h"
#line 1 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/types.h"



typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned int uint16;
typedef signed int int16;
typedef unsigned long uint32;
typedef signed long int32;
#line 1 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/tmr0.h"
#line 1 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/types.h"
#line 8 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/tmr0.h"
extern void TMR0_Reload(void);
extern void TMR0_ISR(void);
extern void TMR0_CallBack_One_Sec(void);
extern void TMR0_CallBack_Half_Sec(void);
extern void TMR0_Initialize(void);
#line 20 "g:/repository/rnd/projects/motor_pump/firmware/v1_0/app.h"
extern void check_cond(void);
extern void exe_cond(void);
extern void sys_init(void);
extern void Uart_Send(void);
#line 3 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/APP.c"
extern volatile uint8 one_min;
volatile uint8 ML_Status = 0,u_ip_r = 0,u_ip_g = 0,u_ip_b = 0;


void interrupt()
{
 asm CLRWDT ;
 if(TMR0IE_bit == 1 && TMR0IF_bit == 1)
 {
 TMR0_ISR();
 }

}

void reset_all()
{
  PORTC.RC5  = 0;
  PORTC.RC4  = 0;
  PORTC.RC3  = 0;
}

void Input_SW()
{
 if( PORTC.RC2 )
 {
 u_ip_r++;
 if(u_ip_r >  20 )
 {
 ML_Status |= 0x01;
 u_ip_r =  20 ;
 }

 }
 else
 {
 u_ip_r = 0;
 ML_Status &= 0xFE;
 }


 if( PORTC.RC1 )
 {
 u_ip_g++;
 if(u_ip_g >  20 )
 {
 ML_Status |= 0x02;
 u_ip_g =  20 ;
 }

 }
 else
 {
 u_ip_g = 0;
 ML_Status &= 0xFD;
 }


 if( PORTC.RC0 )
 {
 u_ip_b++;
 if(u_ip_b >  20 )
 {
 ML_Status |= 0x04;
 u_ip_b =  20 ;
 }

 }
 else
 {
 u_ip_b = 0;
 ML_Status &= 0xFB;
 }


}

void Uart_Send(char* msg)
{
 while(*msg)
 Soft_UART_Write(*msg++);
 Soft_UART_Write(0x0D);
}


char* recv_mess()
{

}

void Send_mess()
{

}


void Check_cond()
{

}



void sys_init()
{
 OSCCON = 0x72;

 PORTA = 0x00;
 LATA = 0x00;
 ANSELA = 0x00;
 TRISA = 0x00;

 PORTC = 0x00;
 ANSELC = 0x00;
 LATC = 0x00;
 TRISC = 0x07;

 reset_all();

 WDTCON = 0x17;
 TMR0_Initialize();

 Soft_UART_Init(&PORTA, 5, 4, 9600, 0);

 GIE_bit = 1;
}

void main()
{
 sys_init();

 while(1)
 {
 if(one_min % 2 == 0)
 {
 Input_SW();
 }
 if(one_min % 30 == 0)
 {
 Check_Cond();
 }
 }
}
