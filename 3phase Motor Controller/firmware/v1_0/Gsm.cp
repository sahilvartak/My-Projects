#line 1 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/Gsm.c"
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
#line 4 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/Gsm.c"
char AT[]="AT";
char noecho[]="ATE0";
char mode_text[]="AT+CMGF=1";
char char_mode[]="AT+CSCS=\"GSM\"";
char param[]="AT+CSMP=17,167,0,0";
char mobile_no[]="AT+CMGS=\"+92090078601\"";
char terminator=0x1A;
char mesg[]="welcome to microcontrollerslab.com";

void send_to_modem(char *s)
 {
 while(*s)
 Soft_UART_Write(*s++);
 Soft_UART_Write(0X0D);
 }
 void send_to_modem1(char *s)
 {
 while(*s)
 Soft_UART_Write(*s++);
 }
 void send_sms()
 {

send_to_modem1(mesg);
 delay_ms(100);
 Soft_UART_Write(terminator);
 delay_ms(1000);
 }


void gsm_init()
{
 send_to_modem(AT);
 delay_ms(2000);
 send_to_modem(noecho);
 delay_ms(2000);
 send_to_modem(mode_text);
 delay_ms(2000);
 send_to_modem(mobile_no);
 delay_ms(2000);

}
