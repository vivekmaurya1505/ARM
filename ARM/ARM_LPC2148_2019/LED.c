#include<lpc214x.h>

void delay(unsigned int x){
	
	for(int i=0;i<x;i++){
		for(unsigned int j=0;j<30000;j++);
	}
	
}

int main(){

	PINSEL0=0X00000000;  
	PINSEL1=0X00000000;
	
	IO0DIR=(1<<31);
	IO0DIR=0x80000000;//(1<<31);   //LED
	IO1DIR|=0x02000000;//(1<<25);   //BUZZER
	
	while(1){
		
		IO0SET=0x80000000;//LED ON
		delay(10);
		IO0CLR=0x80000000;//LED OFF
		delay(10);
		
		IO1SET=0x02000000;// BUZZER ON
		delay(10);
		IO1CLR=0x02000000;// BUZZER OFF
		delay(10);
		
		
		
		
	}
	
}
