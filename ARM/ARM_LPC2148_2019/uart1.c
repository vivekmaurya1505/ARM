#include <LPC214X.h>

char data[20]="abcd\r\n";
char received[20];
void tx_string(char data[]);
void init_uart(void);
void rx_string(char data[]);




void init_uart(void)
{
	PINSEL0=(1<<18)|(1<<16);  //uart tx rx select
	U1LCR=(0x80)|(0x03);    // 8 bit data tx and dlab enable 
	U1DLL=0xB7;             // baud rate
	U1LCR=0x03;             //disbling dlab
	U1FDR=0xF1;             //calculations
	U1IER = 0x01;           //interrupt enable rx
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


int main(void)
{
	VPBDIV=0x02;
	init_uart();

	{
		tx_string(data);
		rx_string(received);
		tx_string(received);
	}
}
