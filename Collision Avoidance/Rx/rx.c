#include<reg51.h>
sbit decoder1 = P3^0;
sbit decoder2 = P3^1;
sbit decoder3 = P3^2;
sbit decoder4 = P3^3;

void main(void)
{
	P3=0xFF;
	P1=0x00;
	while(1)
	{
		if(decoder1==0 && decoder2==1 && decoder3==0 && decoder4==1)
		{
			P1=0x0A;
		}
		
		if(decoder1==1 && decoder2==0 && decoder3==1 && decoder4==0)
		{
			P1=0x05;
		}
		
			if(decoder1==0 && decoder2==1 && decoder3==1 && decoder4==0)
		{
			P1=0x09;
		}
		
			if(decoder1==1 && decoder2==0 && decoder3==0 && decoder4==1)
		{
			P1=0x06;
		}
		
			if(decoder1==1 && decoder2==1 && decoder3==1 && decoder4==0)
		{
			P1=0x10;
		}
		
		if(decoder1==1 && decoder2==1 && decoder3==1 && decoder4==1)
		{
			P1=0x00;
		}
	}
}