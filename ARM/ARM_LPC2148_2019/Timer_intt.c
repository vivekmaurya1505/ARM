#include <LPC214X.H>
#define PRESCALE 60000

void timer_irq(void) __irq;
void timer_match_init();
void interrupt_init();

void timer_match_init()
{
	T1MCR=(1<<3);
	T1MR1=100;
	T1PR = PRESCALE-1;
}
void interrupt_init()
{
	VICIntEnable|=(1<<5);
	VICVectCntl1=0x20|5;
	VICVectAddr1=(unsigned)timer_irq;
}

int main(void)
{
	IO1DIR|=(1<<25);
	timer_match_init();
	interrupt_init();
	T1TC=0x00;
	T1CTCR=0x00;
	T1TCR=(1<<0);
	while(1);
}

void timer_irq(void) __irq
{
	static int i=0;
	T1IR|=(1<<0);

	if(i==0)
	{
		i=1;
		IO1CLR=(1<<25);
	} 
	else
	{
		i=0;
		IO1SET=(1<<25);
	}
	T1TC=0x00;
	VICVectAddr=0x00;
}
