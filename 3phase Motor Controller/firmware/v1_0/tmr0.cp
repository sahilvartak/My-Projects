#line 1 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/tmr0.c"
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
#line 3 "G:/Repository/RnD/Projects/motor_pump/firmware/v1_0/tmr0.c"
volatile uint16 one_sec=0;
volatile uint8 one_min=1;


void TMR0_Initialize(void)
{

 OPTION_REG = 0x17;
 TMR0 =  0xF8 ;
 TMR0IF_bit = 0;
 TMR0IE_bit = 1;
}

void TMR0_ISR(void)
{
 TMR0 =  0xF8 ;
 TMR0IF_bit = 0;

 one_sec++;
 if(one_sec>1047)
 {
 one_sec=0;
 one_min++;
 if(one_min > 60)
 {
 one_min=1;
 }

 }
}
