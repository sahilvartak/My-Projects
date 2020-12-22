#include "types.h"

char rozborka[150];

char lenghs_print[205];
extern char a;

// block of definitions

#define LOAD_OUT_LO RC0_bit=0;;
#define LOAD_OUT_HI RC0_bit=1;;
#define NUMBER_OF_LAST_MAX7219 6
#define LED RB0_bit

//*********************** MAX7219 definition ******************************
//setup number of chip attached to the board
#define NUMBER_OF_LAST_MAX7219 5                                                        // ��slo posledn� jednotky budi�e (jednotky jsou ��slov�ny 0, 1, 2,....)

//define registers
#define MAX7219_REGNOOP 0x00                                        // nebude provedena ��dn� operace
#define MAX7219_REGROW1 0x01                                        // z�pis dat na prvn� ��dek
#define MAX7219_REGROW2 0x02                                        // z�pis dat na druh� ��dek
#define MAX7219_REGROW3 0x03                                        // z�pis dat na t�et� ��dek
#define MAX7219_REGROW4 0x04                                        // z�pis dat na �tvrt� ��dek
#define MAX7219_REGROW5 0x05                                        // z�pis dat na p�t� ��dek
#define MAX7219_REGROW6 0x06                                        // z�pis dat na �est� ��dek
#define MAX7219_REGROW7 0x07                                        // z�pis dat na sedm� ��dek
#define MAX7219_REGROW8 0x08                                        // z�pis dat na osm� ��dek
#define MAX7219_REGDECODE 0x09                                        // nastaven� zp�sobu dek�dov�n� informace pro v�stupy digit� (0x00 - no decode, v�ce datasheet str. 7)
#define MAX7219_REGINTENSITY 0x0A                                // nastaven� intenzity zobrazen�
#define MAX7219_REGSCANLIMIT 0x0B                                // po�et obsluhovan�ch digit� (pro osm digit� se prov�d� volba 0x07)
#define MAX7219_REGSHUTDOWN 0x0C                                // vypnut� zobrazen� (nastaven� LSB datov�mi bity, 0 = shutdown mode, 1 = normal oper mode)
#define MAX7219_REGTEST 0x0F                                        // spu�t�n� testovac� funkce dipleje (v�echny body budou rozsv�ceny)
//**********************************************************************************************************************************************************






//videopam� 1 pro zobrazen� na �est matic
uint8_t VIDEO_MEM_1 [8][6]={0};

//videopam� 2 pro zobrazen� na �est matic
uint8_t VIDEO_MEM_2 [8][6]={0};
        
//pomocn� buffer prom�nn� pro na�ten� znaku z progmem pam�ti
unsigned long bufferLong [14] = {0};

// standard ascii 5x7 font
// defines ascii characters 0x20-0x7F (32-127)
const unsigned char font5x7[] = {      //Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,3,                //Space (Char 0x20)
    0x80,0x80,0x80,0x80,0x00,0x00,0x80,2,                //!
    0xA0,0xA0,0xA0,0x00,0x00,0x00,0x00,4,                //"
    0x50,0x50,0xF8,0x50,0xF8,0x50,0x50,6,                //#
    0x20,0x78,0xA0,0x70,0x28,0xF0,0x20,6,                //$
    0xC0,0xC8,0x10,0x20,0x40,0x98,0x18,6,                //%
    0x60,0x90,0xA0,0x40,0xA8,0x90,0x68,6,                //&
    0xC0,0x40,0x80,0x00,0x00,0x00,0x00,3,                //'
    0x20,0x40,0x80,0x80,0x80,0x40,0x20,4,                //( 
    0x80,0x40,0x20,0x20,0x20,0x40,0x80,4,                //)
    0x00,0x20,0xA8,0x70,0xA8,0x20,0x00,6,                //*
    0x00,0x20,0x20,0xF8,0x20,0x20,0x00,6,                //+
        0x00,0x00,0x00,0x00,0xC0,0x40,0x80,3,                //,
    0x00,0x00,0x00,0xF8,0x00,0x00,0x00,6,                //-
    0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,3,                //.
    0x00,0x08,0x10,0x20,0x40,0x80,0x00,6,                ///
    0x70,0x88,0x98,0xA8,0xC8,0x88,0x70,6,                //0
        0x40,0xC0,0x40,0x40,0x40,0x40,0xE0,4,                //1
        0x70,0x88,0x08,0x10,0x20,0x40,0xF8,6,                //2
        0xF8,0x10,0x20,0x10,0x08,0x88,0x70,6,                //3
        0x10,0x30,0x50,0x90,0xF8,0x10,0x10,6,                //4
        0xF8,0x80,0xF0,0x08,0x08,0x88,0x70,6,                //5
        0x30,0x40,0x80,0xF0,0x88,0x88,0x70,6,                //6
        0xF8,0x88,0x08,0x10,0x20,0x20,0x20,6,                //7
        0x70,0x88,0x88,0x70,0x88,0x88,0x70,6,                //8
        0x70,0x88,0x88,0x78,0x08,0x10,0x60,6,                //9
        0x00,0xC0,0xC0,0x00,0xC0,0xC0,0x00,3,                //:
        0x00,0xC0,0xC0,0x00,0xC0,0x40,0x80,3,                //;
        0x10,0x20,0x40,0x80,0x40,0x20,0x10,5,                //<
        0x00,0x00,0xF8,0x00,0xF8,0x00,0x00,6,                //=
        0x80,0x40,0x20,0x10,0x20,0x40,0x80,5,                //>
        0x70,0x88,0x08,0x10,0x20,0x00,0x20,6,                //?
        0x70,0x88,0x08,0x68,0xA8,0xA8,0x70,6,                //@ 
        0x70,0x88,0x88,0x88,0xF8,0x88,0x88,6,                //A
        0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0,6,                //B
        0x70,0x88,0x80,0x80,0x80,0x88,0x70,6,                //C
        0xE0,0x90,0x88,0x88,0x88,0x90,0xE0,6,                //D
        0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8,6,                //E
        0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,6,                //F
        0x70,0x88,0x80,0xB8,0x88,0x88,0x70,6,                //G
        0x88,0x88,0x88,0xF8,0x88,0x88,0x88,6,                //H
        0xE0,0x40,0x40,0x40,0x40,0x40,0xE0,4,                //I
        0x38,0x10,0x10,0x10,0x10,0x90,0x60,6,                //J
        0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,6,                //K
        0x80,0x80,0x80,0x80,0x80,0x80,0xF8,6,                //L
        0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88,6,                //M
        0x88,0x88,0xC8,0xA8,0x98,0x88,0x88,6,                //N
        0x70,0x88,0x88,0x88,0x88,0x88,0x70,6,                //O
        0xF0,0x88,0x88,0xF0,0x80,0x80,0x80,6,                //P
        0x70,0x88,0x88,0x88,0xA8,0x90,0x68,6,                //Q
        0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,6,                //R
        0x78,0x80,0x80,0x70,0x08,0x08,0xF0,6,                //S
        0xF8,0x20,0x20,0x20,0x20,0x20,0x20,6,                //T
        0x88,0x88,0x88,0x88,0x88,0x88,0x70,6,                //U
        0x88,0x88,0x88,0x88,0x88,0x50,0x20,6,                //V
        0x88,0x88,0x88,0xA8,0xA8,0xA8,0x50,6,                //W
        0x88,0x88,0x50,0x20,0x50,0x88,0x88,6,                //X
        0x88,0x88,0x88,0x50,0x20,0x20,0x20,6,                //Y
        0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,6,                //Z
        0xE0,0x80,0x80,0x80,0x80,0x80,0xE0,4,                //[
        0x00,0x80,0x40,0x20,0x10,0x08,0x00,6,                // \ (Back slash)
        0xE0,0x20,0x20,0x20,0x20,0x20,0xE0,4,                //]
        0x20,0x50,0x88,0x00,0x00,0x00,0x00,6,                //^
        0x00,0x00,0x00,0x00,0x00,0x00,0xF8,6,                //_
        0x80,0x40,0x20,0x00,0x00,0x00,0x00,4,                //`
        0x00,0x00,0x70,0x08,0x78,0x88,0x78,6,                //a
        0x80,0x80,0xB0,0xC8,0x88,0x88,0xF0,6,                //b
        0x00,0x00,0x70,0x88,0x80,0x88,0x70,6,                //c
        0x08,0x08,0x68,0x98,0x88,0x88,0x78,6,                //d
        0x00,0x00,0x70,0x88,0xF8,0x80,0x70,6,                //e
        0x30,0x48,0x40,0xE0,0x40,0x40,0x40,6,                //f
        0x00,0x78,0x88,0x88,0x78,0x08,0x70,6,                //g
        0x80,0x80,0xB0,0xC8,0x88,0x88,0x88,6,                //h
        0x40,0x00,0xC0,0x40,0x40,0x40,0xE0,4,                //i
        0x10,0x00,0x30,0x10,0x10,0x90,0x60,5,                //j
        0x80,0x80,0x90,0xA0,0xC0,0xA0,0x90,5,                //k
        0xC0,0x40,0x40,0x40,0x40,0x40,0xE0,4,                //l
        0x00,0x00,0xD0,0xA8,0xA8,0x88,0x88,6,                //m
        0x00,0x00,0xB0,0xC8,0x88,0x88,0x88,6,                //n
        0x00,0x00,0x70,0x88,0x88,0x88,0x70,6,                //o
        0x00,0x00,0xF0,0x88,0xF0,0x80,0x80,6,                //p
        0x00,0x00,0x68,0x98,0x78,0x08,0x08,6,                //q
        0x00,0x00,0xB0,0xC8,0x80,0x80,0x80,6,                //r
        0x00,0x00,0x70,0x80,0x70,0x08,0xF0,6,                //s
        0x40,0x40,0xE0,0x40,0x40,0x48,0x30,6,                //t
        0x00,0x00,0x88,0x88,0x88,0x98,0x68,6,                //u
        0x00,0x00,0x88,0x88,0x88,0x50,0x20,6,                //v
        0x00,0x00,0x88,0xA8,0xA8,0xA8,0x50,6,                //w
        0x00,0x00,0x88,0x50,0x20,0x50,0x88,6,                //x
        0x00,0x00,0x88,0x88,0x78,0x08,0x70,6,                //y
        0x00,0x00,0xF8,0x10,0x20,0x40,0xF8,6,                //z
        0x20,0x40,0x40,0x80,0x40,0x40,0x20,4,                //{
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,2,                //|
        0x80,0x40,0x40,0x20,0x40,0x40,0x80,4,                //}
        0x00,0x00,0x00,0x68,0x90,0x00,0x00,6,                //~
        0x60,0x90,0x90,0x60,0x00,0x00,0x00,5                //�

};


//obsluha matice

void shift_out_byte(uint8_t byte_to_send)
{      
       SPI1_Write(byte_to_send);
       // SPID.DATA = byte_to_send;                                        // adresa 15
       // while(!(SPID.STATUS & 0x80));                // wait for transmit complete
}

// odesl�n� s�riov�ch dat po SPI
void shift_out_data_to_unit(uint8_t num_of_unit, uint8_t ADDR, uint8_t DATA)
{
        uint8_t i = 0;
        
        LOAD_OUT_LO                                                                        // inicializace, nastaven� bitu proveden� z�pisu na nulu
        
        if(num_of_unit < NUMBER_OF_LAST_MAX7219)                        // o�et�en� pro p��pad, kdy komunikovan� jednotka nen� na konci �ady
        {
                for (i = num_of_unit; i < (NUMBER_OF_LAST_MAX7219); i++)
                {
                        shift_out_byte(MAX7219_REGNOOP); // odesl�n� nulov�ho adresn�ho bajtu pro budi�e, kter� jsou za komunikovan�m
                        shift_out_byte(MAX7219_REGNOOP); // odesl�n� nulov�ho datov�ho bajtu pro budi�e, kter� jsou za komunikovan�m
                }
        }
        
        // zasl�n� dat na po�adovanou jednotku
        shift_out_byte(ADDR);                                // odesl�n� adresn�ho bajtu na po�adovanou jednotku
        shift_out_byte(DATA);                                // odesl�n� datov�ho bajtu na po�adovanou jednotku
        
        // zasl�n� pr�zdn�ch bajt� na jednotky p�ed adresovanou
        
        for (i=0; i < num_of_unit; i++)
        {
                shift_out_byte(MAX7219_REGNOOP); // odesl�n� nulov�ho adresn�ho bajtu pro budi�e, kter� jsou za komunikovan�m
                shift_out_byte(MAX7219_REGNOOP); // odesl�n� nulov�ho datov�ho bajtu pro budi�e, kter� jsou za komunikovan�m
        }
        
        LOAD_OUT_HI
        //        _delay_us(1);
        LOAD_OUT_LO
}

// funkce pro na�ten� znaku z progmem
void loadBufferLong(int ascii)
{
       uint32_t c;
       uint8_t count,x;
        for(a = 0; a < 14; a++)                // vy�i�t�n� bufferu
        {
                bufferLong [a] = 0;
        }

        if (ascii >= 0x20 && ascii <=0x7f)
        {
                for (a=0;a<8;a++)
                {                      // Loop 7 times for a 5x7 font
                        c = font5x7[(((ascii - 0x20) * 8) + a)];     // Index into character table to get row data
                        //unsigned long x = bufferLong [a*2];     // Load current scroll buffer
                        //x = x | c;                              // OR the new character onto end of current
                        bufferLong [a] = c;                   // Store in buffer
                }
                
                count = font5x7[(((ascii - 0x20) * 8) + 7)];     // Index into character table for kerning data
                for (x=0; x<count;x++){
                        //                rotateBufferLong();
                        //                printBufferLong();
                        //                _delay_ms(500);
                }
        }
}

// ov��en� hodnoty zadan�ho bitu prom�nn�
uint8_t bit_read(uint8_t variable, uint8_t bit_num)
{
        if(variable & (1<<bit_num))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

//Funkce pro vlo�en� znaku 5x7 do videopam�ti 1
int set_char_5x7_on_XY(int x_offset, int y_offset, char character)
{
        uint8_t font_lenght = bufferLong[7];        // vy�ten� ���ky fontu v pixelech
        int pixel_to_start_draw = x_offset;
        int pixel_to_end_draw = (x_offset-1) + font_lenght;
        uint8_t bit_to_read;
        
        int start_row = y_offset;
        int end_row = y_offset + 7;
        int act_row,row,x_pos;                                        // aktu�ln� ��dek �ten� znaku z pam�ti v r�mci vykreslov�n�

        //fonty jsou v rozm�ru 5x7 bod�, tedy sedm bod� je ��dek. P�i vykreslov�n� do videopam�ti je y_offsetem ��dek, od kter�ho se (v p��pad� vykreslov�n� mimo rozsah videopam�ti v z�porn�ch sou�adnic�ch)
        //vykresluje p��slu�n� znak, p�i�em� ��dkov�n� se po��t� od v�choz� sou�adnice a inkrementuje do velikosti 7 (vertik�ln� rozm�r znakov� sady).
        
        loadBufferLong(character);

        for(row=start_row; row<end_row;row++)                                // pro��t�n� jednotliv�ch ��dk� (pro vykreslen� v��ky p�sma 7 ��dk�)
        {


                
                bit_to_read = 7;
                
                
                for(x_pos = x_offset; x_pos < 48; x_pos++)                //cyklus postupn� prob�hne cel� ��dek pam�ti
                {
                        if (x_pos<(0))
                        {
                                bit_to_read--;
                        }
                        
                        
                        if(((-1)<x_pos)&&(x_pos<8))                //kreslen� do pam�ov�ho prostoru prvn� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][0] |= (1<<(7 - x_pos));

                                        }
                                        else
                                        {
                                                VIDEO_MEM_1[row][0] &= ~(1<<(7 - x_pos));
                                        }
                                        
                                        bit_to_read--;
                                }
                        }
                        
                        if((x_pos>7)&&(x_pos<16))                //kreslen� do pam�ov�ho prostoru druh� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][1] |= (1<<(7 - (x_pos-8)));

                                        }
                                        
                                        bit_to_read--;
                                }
                        }
                        
                        if((x_pos>15)&&(x_pos<24))                //kreslen� do pam�ov�ho prostoru t�et� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][2] |= (1<<(7 - (x_pos-16)));

                                        }
                                        
                                        bit_to_read--;
                                }
                        }
                        
                        if((x_pos>23)&&(x_pos<32))                //kreslen� do pam�ov�ho prostoru �tvrt� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][3] |= (1<<(7 - (x_pos-24)));

                                        }
                                        
                                        bit_to_read--;
                                }
                        }
                        
                        if((x_pos>31)&&(x_pos<40))                //kreslen� do pam�ov�ho prostoru p�t� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][4] |= (1<<(7 - (x_pos-32)));

                                        }
                                        
                                        bit_to_read--;
                                }
                        }

                        if((x_pos>39)&&(x_pos<48))                //kreslen� do pam�ov�ho prostoru p�t� matice
                        {
                                if((x_pos > (pixel_to_start_draw - 1)) && (x_pos<pixel_to_end_draw))                //pozice pro za��tek kreslen�
                                {
                                        
                                        if ((bit_read(bufferLong[act_row],bit_to_read)))        //jestli�e je hodnota bitu "1", ulo�� se postupn� tento stav do videopam�ti
                                        {
                                                VIDEO_MEM_1[row][5] |= (1<<(7 - (x_pos-40)));

                                        }
                                        
                                        bit_to_read--;
                                }
                        }





                }
                
                act_row++;
                
        }
        
        return font_lenght;
}

// funkce pro vy�i�t�n� videopam�ti 1
void clear_videoMem_1()
{
       int row,x;
        for (row = 0; row<8;row++)
        {
                for (x = 0; x < 6; x++)
                {
                        VIDEO_MEM_1 [row][x]=0x00;
                }

        }
}

// vykreslen� videopam�ti 1 na maticov� display
void print_disp_memory_1()                                // vykreslen� video pam�ti po ��dc�ch
{
       int i;
        LOAD_OUT_LO                                                                        // inicializace, nastaven� bitu proveden� z�pisu na nulu
        for(a=0; a<8 ; a++)                                // p�ep�n�n� ��dk� matic (��dek 0 - 7)
        {
                for(i=0;i<6;i++)                        // postupn� odesl�n� dat ��dk� pro v�echny matice po SPI (i = 0: data ��dku p�t� matice, odes�l� se po�ad�m LSB first)
                {
                        if(a==0)
                        {
                                shift_out_byte(MAX7219_REGROW1);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==1)
                        {
                                shift_out_byte(MAX7219_REGROW2);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==2)
                        {
                                shift_out_byte(MAX7219_REGROW3);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==3)
                        {
                                shift_out_byte(MAX7219_REGROW4);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==4)
                        {
                                shift_out_byte(MAX7219_REGROW5);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==5)
                        {
                                shift_out_byte(MAX7219_REGROW6);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==6)
                        {
                                shift_out_byte(MAX7219_REGROW7);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                        if(a==7)
                        {
                                shift_out_byte(MAX7219_REGROW8);
                                shift_out_byte(VIDEO_MEM_1[a][5-i]); // (5-i) - nejd��ve se odes�laj� data matice �.6 v prvn� iteraci
                        }
                }
                
                LOAD_OUT_HI                                                                        // inicializace, nastaven� bitu proveden� z�pisu na log 1
                LOAD_OUT_LO                                                                        // inicializace, nastaven� bitu proveden� z�pisu na nulu
        }

/*
        for(int a=0; a < 8; a++)                        // vykreslen� ��dk� prvn� matice
        {
                set_row_on_chip(0,a+1,displayMemory[a*2]);                        // vykreslen� ��dk� matice 1
                set_row_on_chip(1,a+1,displayMemory[(a*2)+1]);                // vykreslen� ��dk� matice 2        
        }
*/
}


void set_bode_to_videoMem(uint8_t x, uint8_t y)
{
        if(x<9)                //bod bude kreslen na prvn� matici
        {
                VIDEO_MEM_1[y-1][0] |= (1<<(7-(x-1)));
        }
        
        if((x>8) && (x<17))        // bod bude kreslen na druh� matici
        {
                VIDEO_MEM_1[y-1][1] |= (1<<(7-(x-9)));
        }
        
        if((x>16) && (x<25))        // bod bude kreslen na t�et� matici
        {
                VIDEO_MEM_1[y-1][2] |= (1<<(7-(x-17)));
        }

        if((x>24) && (x<33))        // bod bude kreslen na �tvrtou matici
        {
                VIDEO_MEM_1[y-1][3] |= (1<<(7-(x-25)));
        }
        
        if((x>32) && (x<41))        // bod bude kreslen na �tvrtou matici
        {
                VIDEO_MEM_1[y-1][4] |= (1<<(7-(x-33)));
        }
        if((x>40) && (x<49))        // bod bude kreslen na �tvrtou matici
        {
                VIDEO_MEM_1[y-1][5] |= (1<<(7-(x-41)));
        }        
}

int check_string_lenght(char *string)

/*****************************************************
Funkce vrac� ���ku zadan�ho �et�zce v pixelech dle pou�it� znakov� sady,
konkr�tn� pozici na ose "x", na kter� by p�i vykreslen� na maticov�m dipleji
byla pozice, na kter� vykreslen� skon�� - na dal�� pozici m��e b�t ve videopam�ti
vykreslen dal�� znak.

jestli�e je �daj = 4, a znak by byl um�st�n na sou�adnici x_offset = 0, pak p��slu�n�
znak nebo znaky budou kon�it na sou�adnici x = 4
******************************************************/

{
        int string_on_display_lenght = 0;
        
        while (*string)                //v r�mci cyklu je prov�d�no �ten� cel�ho pole, jeho� kone�n� pozice pro vykreslen� m� b�t zji�t�na
        {
                loadBufferLong(*string);
                string_on_display_lenght = string_on_display_lenght + bufferLong[7];        // nejd��ve je zji�t�na bitov� d�lka zpracov�van�ho znaku �et�zce
                
                *string++;
        }

        return string_on_display_lenght;
        
}



void print_string(uint8_t clean_video_mem, int x_offset, int y_offset, char *string)
{
        uint8_t font_lenght;                // prom�nn�, do kter� je na�tena d�lka aktu�ln�ho znaku
        //int last_char_lenght;

        int act_char_position;                // pozice aktu�ln� zpracov�van�ho znaku


        // vykreslov�n� textov�ho �et�zce je zalo�eno na simult�ln�m vykreslov�n� znak�, kter� jsou za sebou v �et�zci obsa�eny, p�i�em� je dan� znak nejprve na�ten z pam�ti
        // spole�n� s bitovou ���kou znaku. Pouze v p��pad�, kdy ��st znaku zasahuje do vykreslovan� plochy ohrani�en� offsetem na ose x, sou�adnic� 0px a 39px (pro danou
        // aplikaci je p�edpokl�dan� ���ka zobrazovac� plochy 40 bod�), je provedeno vykreslov�n� do video pam�ti, kter� je po kone�n�m zpracov�n� zasl�na k zobrazen�
        // na maticov� display. Funkce je ur�ena pro posuvn� zobrazen� textov�ho �et�zce, kter� svou d�lkou (po�tem znak�) p�esahuje zobrazovac� mo�nosti (po�et vodorovn�ch
        // bod�) maticov�ho displaye.


        act_char_position = x_offset;
  
  
  
  
        
        if(clean_video_mem==1)
        {
                clear_videoMem_1();                
        }
        
                        //videoMem[2][0]=0xf0;


                while (*string)                //v r�mci cyklu je prov�d�no �ten� cel�ho pole, kter� m� b�t zobrazeno
                {
                        loadBufferLong(*string);
                        font_lenght = bufferLong[7];        // nejd��ve je zji�t�na bitov� d�lka zpracov�van�ho znaku �et�zce
                        
                        
                        if((act_char_position+font_lenght)>(-1))                // jestli�e posledn� bod znaku vykreslen� od aktu�ln� pozice zasahuje do zobrazovan� oblasti, je zavol�na funkce vykreslen� znaku do videopam�ti
                        {
                                set_char_5x7_on_XY(act_char_position,y_offset,*string);
                                //new_char_position = new_char_position + last_char_lenght;                                
                        }


                        if (act_char_position > 47)                //jestli�e je po��tek nov� vykreslovan�ho znaku za zobrazovac� plochou maticov�ho displeje, vykreslov�n� bude p�eru�eno
                        {
                                break;
                        }
                        
                        *string++;
                        act_char_position = act_char_position + font_lenght;        //po proveden� rozhodovac�ch, p��padn� vykreslovac�ch krok� je nav��en ukazatel na dal�� pozici p��padn�ho n�sleduj�c�ho znaku
                }

        print_disp_memory_1();
}


void RUNNING_TEXT(int disp_points,int step_delay_time, char *text)
{

        
        //Ondrej Blazek, www.ondrashova-automatizace.webnode.cz
        
        int string_lenght,i;                        // d�lka zobrazovan�ho textu v bodech na ose x
        
        string_lenght = check_string_lenght(text);
        
        //snprintf(rozborka,20,"Delka retezce: %d\n",string_lenght);
        //uart_puts(rozborka);
        
        
        //uart_puts(lenghs_print);
        
        
        for (i = (disp_points + 1);i>(disp_points - string_lenght-disp_points);i--)
        {
                LED = 1;
                print_string(1,i,0,text);

                LED = 1;
                for(i=0;i<step_delay_time;i++)
                {
                        delay_ms(1);
                }

        }
        
}