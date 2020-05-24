#include <lpc17xx.h>
#include "lcd.h"	
	
int main(void)
{
	unsigned char str[20]="ABCD";
		unsigned char str1[20]="CDAC";
	init_lcd();
	send_cmd(0x80);
	user_string(str);
	send_cmd(0xc0);
	user_string(str1);
}