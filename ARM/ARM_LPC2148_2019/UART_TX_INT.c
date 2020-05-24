#include <LPC214X.h>

char data[20]="transmitted data";
char rx[20];
int i=0;


void init_uart(void)
{
	PINSEL0=(1<<18)|(1<<16);
	U1LCR=(0x80)|(0x03);
	U1DLL=0xB7;
	U1LCR=0x03;
	U1FDR=0xF1;
	U1IER = 0x03;
}


void tx_string(char data[])
{ 	U1THR=' ';
	while(data[i]!='\0')
	{ 
	
	}
	U1IER=0x01;
}

void uart_int(void)__irq
 { 
		U1THR=data[i++];	
	  VICVectAddr=0x00;
	 	VICIntEnable=0x00; 
 }

void intr_init(void)
 {
		
	 VICIntEnable=0x80; 
	 VICVectCntl0=0x20|0x07;
	 VICVectAddr0=(unsigned)uart_int;
	 U1IIR= (0x040)|(0x020);
	 
	 
 }

int main(void)
{
	VPBDIV=0x02;
	init_uart();
	intr_init();

	

	{
		tx_string(data);
		
		while(1);
		
	}
}
