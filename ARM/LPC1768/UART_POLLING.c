#include <LPC17xx.h>
#include "system_LPC17xx.h"
char RX();
void TX(char *);
char ch[100];


int main(void)
{
	SystemInit();
	LPC_SC->PCLKSEL1 |=(0<<18)|(0<<19);				//pclk=cclk/4 =100M/4 =25M
	LPC_PINCON->PINSEL0 |=(1<<1)|(1<<3);   //tx rx 
	LPC_SC->PCONP |=(1<<25);							//power on uart 3
	
	LPC_UART3->LCR=0x00000083; 				//dlab=1, data length 8 bit
	LPC_UART3->DLL=162;				        //25M/(16 x 9600)
	LPC_UART3->DLM=0x00000000;
	LPC_UART3->LCR=0x00000003;
	LPC_UART3->FDR |=(1<<4);					//mulval =1
					//DLAB=0
////	while(1)
////{	
////	for(int j=0;ch[j]!='\r';j++){
////				ch[j]=RX();
////	}
////	
////		for(int i=0;ch[i]!='\0';i++){
////	       TX(&ch[i]);
////		
////		}
////		
////		return 0;
////}
////}
//// void TX(char *ch){
////	 
////	 while(!(LPC_UART3->LSR & 0x20)){}
////	LPC_UART3->THR=*ch;
////  }
//// 
////	char RX()
////{
////	while(!(LPC_UART3->LSR & 0x01));
////	return LPC_UART3->RBR;
////}
	while(1)
	{	
		int i=0;
		do
		{
			ch[i]=RX();
			i++;
		}while(ch[i-1]!='\r');
		ch[i]='\n';
		ch[i+1]='\0';
		i=0;
		
		while(ch[i])
		{
			TX(&ch[i]);
			i++;
		}	
	}	
	return 0;

}
char RX()
{
	while(!(LPC_UART3->LSR & 0x01));
	return LPC_UART3->RBR;
}
void TX(char *ch)
{
	while(!(LPC_UART3->LSR & 0x20));
	LPC_UART3->THR=*ch;
}
