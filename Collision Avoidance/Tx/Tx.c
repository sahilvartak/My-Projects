#include<reg51.h>

sbit Encoder1=P3^0;
sbit Encoder2=P3^1;
sbit Encoder3=P3^2;
sbit Encoder4=P3^3;

sbit forward=P1^0;
sbit reverse=P1^1;
sbit left=P1^2;
sbit right=P1^3;
sbit fan=P1^4;


void main(void)
{
	P3=0xFF;
	P1=0xFF;
	while(1)
	{
	
	
	if(forward==0)
	{
		Encoder1=0;
		Encoder3=0;
		Encoder2=1;
		Encoder4=1;
	}
	
	if(reverse==0)
	{
		Encoder2=0;
		Encoder4=0;
		Encoder1=1;
		Encoder3=1;
	}
	
	if(right==0)
	{
		Encoder1=0;
		Encoder4=0;
		Encoder2=1;
		Encoder3=1;
	}
	
	if(left==0)
	{
		Encoder3=0;
		Encoder2=0;
		Encoder1=1;
		Encoder4=1;
	}
	
	if(fan==0)
	{
		Encoder3=1;
		Encoder2=1;
		Encoder1=1;
		Encoder4=0;
	}
	if(forward==1 && left==1 && right==1 && reverse==1 && fan==1)
	{
		Encoder3=1;
		Encoder2=1;
		Encoder1=1;
		Encoder4=1;
	}
}
}