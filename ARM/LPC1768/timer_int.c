#include "lpc17xx.h"
#include "system_LPC17xx.h"
 void timer_init();
 void	timer_delay();

int main(void)
{
	SystemInit();
	
	LPC_SC->PCONP|=(1<<1);      //to give power(clk) to timer0 
	LPC_SC->PCLKSEL0|=(1<<2);   // pclk=clk

	
	LPC_GPIO2->FIODIR |= (1<<11);      //buzzer as output
	LPC_GPIO2->FIOCLR|= (1<<11);
  timer_init();
	
	/* start timer */
while(1){	
	
	LPC_GPIO2->FIOCLR|= (1<<11);
	timer_delay();
	LPC_GPIO2->FIOSET|= (1<<11);
	timer_delay();
	
	}
	
}



void timer_init(){
	LPC_TIM0->CTCR=0X00;
	LPC_TIM0->PR = 5000000;
	LPC_TIM0->MR0 = 1;
	LPC_TIM0->MCR |= (1<<1); //Reset on MR0
	LPC_TIM0->TCR |= (1<<1);// reset timer 
                       
}

void timer_delay(){
		LPC_TIM0->TCR=0x02;   //reset timer
		LPC_TIM0->TCR=0x01;    //enable timer
	while((LPC_TIM0->TC!=LPC_TIM0->MR0));

}
