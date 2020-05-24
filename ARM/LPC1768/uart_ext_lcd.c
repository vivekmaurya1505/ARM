#include <LPC17xx.h>
#include "lcd.h"
#include "system_LPC17xx.h"
char RX();
void TX(unsigned char *);
unsigned char ch[100];
unsigned char str[20]="aaaa";
unsigned char str1[20]="bbbb";


int main(void)
{
		init_lcd();
	
	//uart=================================================================
	SystemInit();
	LPC_SC->PCLKSEL1 |=(0<<18)|(0<<19);				//pclk=cclk/4 =100M/4 =25M
	LPC_PINCON->PINSEL0 |=(1<<1)|(1<<3);   //tx rx 
	LPC_SC->PCONP |=(1<<25);							//power on uart 3
	
	LPC_UART3->LCR=0x00000083; 				//dlab=1, data length 8 bit
	LPC_UART3->DLL=162;				        //25M/(16 x 9600)
	LPC_UART3->DLM=0x00000000;
	LPC_UART3->LCR=0x00000003;
	LPC_UART3->FDR |=(1<<4);				
	//lcd===========
  LPC_GPIO2->FIODIR|=(1<<9);
	LPC_GPIO2->FIODIR|=(1<<11);
	LPC_PINCON->PINSEL4 |= (1<<24);
	LPC_SC->EXTMODE |=(0<<2);
	LPC_SC->EXTPOLAR |=(0<<2);
	NVIC_EnableIRQ(EINT2_IRQn);
	//==================
	
	while(1)
	{
		int i=0;
		do
		{
			ch[i]=RX();
			i++;
		}while(ch[i-1]!='\r');
		ch[i-1]='\0';
		
		i=0;
	}	
	
}

//===uart=====

char RX()
{
	while(!(LPC_UART3->LSR & 0x01));
	return LPC_UART3->RBR;
}
void TX(unsigned char *ch)
{
	while(!(LPC_UART3->LSR & 0x20));
	LPC_UART3->THR=*ch;
}
//=======ext_int======
void EINT2_IRQHandler(void)
{
	static int k=0;
	int i;
	LPC_SC->EXTINT |=(1<<2);
	
	if(k==0){
	   k=1;	
		while(ch[i])
		{
			TX(&ch[i]);
			i++;
		}	
		
	user_string(ch);
		for(int i=0;i<10;i++);
 
	}
	if(k==1){
		for(int i=0;i<10;i++);
	}
}