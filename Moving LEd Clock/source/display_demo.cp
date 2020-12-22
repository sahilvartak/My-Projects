#line 1 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source/display_demo.c"
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source/types.h"



typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef unsigned int uint16_t;
typedef signed int sint16_t;
typedef unsigned long uint32_t;
typedef unsigned long sint32_t;
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source/matrix_disp_driving.h"
#line 1 "c:/users/sahil/desktop/pic project/digital clock/source/types.h"
#line 5 "c:/users/sahil/desktop/pic project/digital clock/source/matrix_disp_driving.h"
extern void shift_out_byte(uint8_t byte_to_send);
extern void shift_out_data_to_unit(uint8_t num_of_unit, uint8_t ADDR, uint8_t DATA);
extern void loadBufferLong(uint8_t ascii);
extern uint8_t bit_read(uint8_t variable, uint8_t bit_num);
extern void set_char_5x7_on_XY(sint8_t x_offset, sint8_t y_offset, uint8_t character);
extern void clear_videoMem_1();
extern void print_disp_memory_1();
extern void set_bode_to_videoMem(uint8_t x, uint8_t y);
extern void print_string(sint8_t clean_video_mem, sint8_t x_offset, sint8_t y_offset,uint8_t *string);
extern void RUNNING_TEXT(sint8_t disp_points,sint16_t step_delay_time, uint8_t *text);
extern uint16_t check_string_lenght(uint8_t *string);
#line 13 "C:/Users/Sahil/Desktop/PIC Project/digital clock/source/display_demo.c"
extern uint8_t a,VIDEO_MEM_1[8][6];
const uint8_t hello_text[] = "hello";
uint8_t text[205]="HELLO";
extern const uint8_t font5x7[];

void display_run()
{
 uint8_t i;

 clear_videoMem_1();
 print_disp_memory_1();
 for(a=1;a<9;a++)
 {
 for(i=1;i<49;i++)
 {
 set_bode_to_videoMem(i,a);
 print_disp_memory_1();
 delay_us(100);
 }
 }
 clear_videoMem_1();
}




void display_demo1()
{
 uint16_t i,j,k;
 sint8_t l;

 clear_videoMem_1();

 while(1)
 {

 for(i=1;i<9;i++)
 {
 set_char_5x7_on_XY(0,0,'1');
 set_char_5x7_on_XY(4,0,'2');
 set_char_5x7_on_XY(11,0,':');
 set_char_5x7_on_XY(15,0,'2');
 set_char_5x7_on_XY(21,0,'3');
 set_char_5x7_on_XY(28,0,':');
 set_char_5x7_on_XY(32,0,'3');
 set_char_5x7_on_XY(38,i,'4');
 set_char_5x7_on_XY(38,i-8,'5');
 print_disp_memory_1();
 delay_ms(50);
 clear_videoMem_1();
 }
 delay_ms(2000);

 }

 while(1)
 {
 for(l=-80;l<48;l++)
 { print_string(1,l,0,"SAHIL VARTAK");
 delay_ms(1);
 }
 }

}
