#include <LPC214X.h>

char data[20];

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

void tx_string(char data[])
{
	int i=0;
	while(data[i]!='\0')
	{
		putchar(data[i]);
		i++;
	}
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
}


void uart_int(void)__irq
 {

		static int i=0;
		
		if(i==0)
		{
			i=1;
			tx_string("Welcome to DESD\n\n\r");
			rx_string(data);
		}
		else
		{
			i=0;
			
			tx_string(data);
		}
		VICVectAddr=0x00;
 }

void intr_init(void)
 {
		
	 VICIntEnable=0x80; //
	 VICVectCntl0=0x20|0x07;
	 VICVectAddr0=(unsigned)uart_int;
	 U1IIR= 0x04;
 }

int main(void)
{
	VPBDIV=0x02;
	init_uart();
	intr_init();
	while(1)
	{
		rx_string(data);
		tx_string(data);
	}
}
