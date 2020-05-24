#include <LPC214X.H>
//==========================uart=====================
char data[20]="abcd\r\n";
char received[20];
void tx_string(char data[]);
void init_uart(void);
void rx_string(char data[]);




void init_uart(void)
{
	PINSEL0=(1<<18)|(1<<16);
	U1LCR=(0x80)|(0x03);
	U1DLL=0xB7;
	U1LCR=0x03;
	U1FDR=0xF1;
	U1IER = 0x01;
}

void putchar(int ch)
{
	while(!(U1LSR & 0x20));
	(U1THR=ch);
}

int getchar()
{
	while(!(U1LSR & 0x01));
	return U1RBR;
}

void rx_string(char data[])
{
	int i=0;
	do
	{
	data[i]=getchar();
	}
	while(data[i++]!=0x0D);
	data[i-1]='\0';
	tx_string("\r\n");
}
void tx_string(char data[])
{
	int i=0;
	while(data[i]!='\0')
	{
		putchar(data[i]);
		i++;
	}
	
}

//===================================================

//==========================EXTINT===================
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
			tx_string(data);
		
	}
	else
	{
		i=0;
		IO1SET=(1<<25);
	}
	EXTINT |= (1<<2);			// EINT2 flag is (interrupt) cleared
	VICVectAddr = 0x00;			// vector address cleared
}

void int_init()
{
	VICIntEnable = (1<<16);		//when EINT2 generates it goes to IRQ
	VICVectCntl0 = 0x20 | 0x10;		// extint2 set on highest priority(0)      0x10 is 16 and it is EXT interrupt ....slot is reserved for the ext interrupt
	VICVectAddr0 = (unsigned)External_int;  //know where to jump
}
//==============================================================
int main(void)     
{
	VPBDIV=0x02;
	init_uart();
	ext_int();
	int_init();
	

//	rx_string(received);
//  tx_string(received);
	
	while(1);
}
