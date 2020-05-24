#include <LPC214X.H>

#define PRESCALE 60000

void init(void);
void delay_ms_Reset_on_Match(unsigned int milliseconds);
void delay_ms_Stop_on_Match(unsigned int milliseconds);

int main()
{
	IO1DIR=0xffffffff;
	IO0DIR=0xffffffff;
	init();
	while(1)
	{
		IO1SET=0x02000000;
		IO0SET=0x80000000;
		delay_ms_Reset_on_Match(1000);
		IO1CLR=0x02000000;
		IO0CLR=0x80000000;
		delay_ms_Stop_on_Match(1000);
	}
}
void init()
{ 
	 VPBDIV=0x01;
	 T1CTCR=0x00;
	 T1PR=PRESCALE-1;
	 T1TCR=0x02;
}
void delay_ms_Reset_on_Match(unsigned int milliseconds)
{
	T1MCR=(1<<4);
	T1MR1=milliseconds;
	T1TCR=0x01;
	while(T1TC!=milliseconds);  
}

void delay_ms_Stop_on_Match(unsigned int milliseconds)
{
	T1MCR=(1<<5);
	T1MR1=milliseconds;
	T1TCR=0x01;
	while(T1TC!=milliseconds);
	//T1TCR=0x02;
}	