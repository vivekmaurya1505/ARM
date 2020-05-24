#include <LPC214X.H>

void ext_int()
{
	IO1DIR= (1<<25);  //buzzer as output
	VPBDIV = 0x00;    //no prescaling
	PINSEL0 = (1<<31);  // making pin p0.15 as EXINT2 
	EXTMODE = (1<<2);	//making EINT2 as edge sensitive	
	EXTPOLAR = (1<<2);  //rising edge sensitive
	EXTINT = (1<<2);    // DOUBT ????? EINT2 interrupt enabled
}

void External_int(void)__irq
{
	static int i=0;
	
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
	EXTINT |= (1<<2);			// EINT2 interrupt cleared
	VICVectAddr = 0x00;			// vector address cleared
}

void int_init()
{
	VICIntEnable = (1<<16);		//when EINT2 generates it goes to IRQ
	VICVectCntl0 = 0x20 | 0x10;		// extint2 set on highest priority(0)      0x10 is 16 and it is EXT interrupt ....slot is reserved for the ext interrupt
	VICVectAddr0 = (unsigned)External_int;  //know where to jump
}

int main(void)     
{
	ext_int();
	int_init();
	while(1);
}
