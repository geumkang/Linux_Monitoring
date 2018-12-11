#include <control.h>
#include <stdio.h>
#include<bcm2835.h>

char PRESSKEY = 20;
unsigned char i;

int key_init(){
	if (!bcm2835_init())return 1;
	bcm2835_gpio_fsel(PRESSKEY, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PRESSKEY, BCM2835_GPIO_PUD_UP);
	printf("Key Test Program!!!!\n");	
	
}

int key_run(){
	
	if(bcm2835_gpio_lev(PRESSKEY) == 0)
	{  
		printf ("KEY PRESS\n") ;
		return 1;
	}
	else return 0;
}

void key_end(){
	bcm2835_close();
}