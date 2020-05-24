#include <LPC214X.H>

void spi_data(unsigned char data);



int main()
{
int i, j,k;
VPBDIV=0x04;
PINSEL0|=(1<<8)|(1<<12);
IO0DIR|=(1<<7);
//IO0DIR = 0x80000000;
S0SPCR=(1<<5)|(1<<7)|(1<<11);
S0SPCCR=0x0E;
IO0SET|=(1<<7);

while(1)
{
spi_data(0xaa);
for(i=0;i<10000;i++)
{
for(j=0;j<100;j++)
{
}
}
k=S0SPDR;
k=S0SPSR;
spi_data(0x55);
for(i=0;i<10000;i++)
{
for(j=0;j<100;j++)
{
}
}
k=S0SPDR;
k=S0SPSR;
}
}

void spi_data(unsigned char data)
{ int i;
IO0CLR|=(1<<7);
S0SPDR=data;
IO0SET|=(1<<7);

}
