#include <LPC214X.H>

void spi_data(unsigned char data);
int main()
{
int i, j,k;
VPBDIV=0x04;
PINSEL0|=(1<<8)|(1<<12);  	//8=CLOCK  12= MOSI
IO0DIR|=(1<<7);							// STCP ON 7th	 PIN	
//IO0DIR = 0x80000000;
S0SPCR=(1<<5)|(1<<7)|(1<<11);		//11=8 bit data 5= mster 7=serial interrupt enable 
S0SPCCR=0x0E;                   //set clock freq
IO0SET|=(1<<7);                 //set (st_cp) 

while(1)
{
	spi_data(0xaa);					
	for(i=0;i<10000;i++){
			for(j=0;j<100;j++);
	}
	k=S0SPDR;											//move (empty) data reg so that next data can be loaded
	k=S0SPSR;                     //clear the status reg to clear transmission complt flag,so that next transmisssion can be done
	spi_data(0x55);               //sending data
	for(i=0;i<10000;i++){
			for(j=0;j<100;j++);
	}
	k=S0SPDR;                   //move (empty) data reg so that next data can be loaded
	k=S0SPSR;                //clear the status reg to clear transmission complt flag,so that next transmisssion can be done
}
}

void spi_data(unsigned char data)
{ 
int i;
IO0CLR|=(1<<7);           
S0SPDR=data;
IO0SET|=(1<<7);

}
