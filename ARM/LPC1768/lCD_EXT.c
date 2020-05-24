#include "lpc17xx.h"
#include "lcd.h"
//#include "system_LPC17xx.h"
unsigned char str[20]="aaaa";
unsigned char str1[20]="bbbb";

int main(void)
{
	
	
		init_lcd();
	 
 
	//SystemInit();
	
	LPC_GPIO2->FIODIR|=(1<<9);
	LPC_GPIO2->FIODIR|=(1<<11);
	LPC_PINCON->PINSEL4 |= (1<<24);
	LPC_SC->EXTMODE |=(0<<2);
	LPC_SC->EXTPOLAR |=(0<<2);
	NVIC_EnableIRQ(EINT2_IRQn);
	while(1)
	{
		LPC_GPIO2->FIOSET|=(1<<9);
		LPC_GPIO2->FIOSET|=(1<<11);
	}	
}	

void EINT2_IRQHandler(void)
{
	static int i=0;
	LPC_SC->EXTINT |=(1<<2);
	
	if(i==0){
	 i=1;
	LPC_GPIO2->FIOCLR|=(1<<9);
	LPC_GPIO2->FIOCLR|=(1<<11);
	user_string(str);
  send_cmd(0xc0);
	user_string(str1);
	}
	if(i==1){
		for(int i=0;i<10;i++);
	}
}