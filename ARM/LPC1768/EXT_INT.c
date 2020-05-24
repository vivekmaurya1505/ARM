#include "lpc17xx.h"
//#include "system_LPC17xx.h"

int main(void)
{
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
	LPC_SC->EXTINT |=(1<<2);
	LPC_GPIO2->FIOCLR|=(1<<9);
	LPC_GPIO2->FIOCLR|=(1<<11);
}