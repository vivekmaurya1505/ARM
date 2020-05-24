#include <LPC214X.h>

void delay(unsigned int x){
	
	for(int i=0;i<x;i++){
		for(unsigned int j=0;j<30000;j++);
	}
	
}


char data[20]="transmitted data";
char rx[20];
int i=0;
int j=0;
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
	j=1;
}

void rx_string()
{ 
	
	while(rx[j]!=0x0D);
	rx[j-1]='\0';
	U1THR='\r';
	U1THR='\n';
	tx_string(rx);
	
  U1IER=0x00;
  
}
	


void uart_int(void)__irq
 { if(j==0)
    {
			U1THR=data[i++];	
		
      			
		}
		if(j==1){
				IO0SET=0x80000000;//LED ON
		delay(10);
		IO0CLR=0x80000000;//LED OFF
		delay(10);
		
		IO1SET=0x02000000;// BUZZER ON
		delay(10);
		IO1CLR=0x02000000;// BUZZER OFF
		delay(10);
		}
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
	
	PINSEL0=0X00000000;  
	PINSEL1=0X00000000;
	
	IO0DIR=(1<<31);
	IO0DIR=0x80000000;//(1<<31);   //LED
	IO1DIR|=0x02000000;//(1<<25);   //BUZZER
	
	
	VPBDIV=0x02;
	init_uart();
	intr_init();

	{
		tx_string(data);
		
		while(1);
		
	}
}
