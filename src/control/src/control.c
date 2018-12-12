#include <control.h>
#include <stdio.h>
#include<bcm2835.h>

#define led_off   i2c_writeByte(0x10 | i2c_readByte())
#define led_on  i2c_writeByte(0xEF & i2c_readByte())

char PRESSKEY = 20;
unsigned char i;

void i2c_writeByte(char byte)
{
	char buf[] = {byte};
	bcm2835_i2c_write(buf,1);
}
char i2c_readByte()
{
	char buf[1];
	bcm2835_i2c_read(buf,1);
	return buf[0];
}

int key_init(){
	if (!bcm2835_init())return 1;
	bcm2835_gpio_fsel(PRESSKEY, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PRESSKEY, BCM2835_GPIO_PUD_UP);
	printf("Key Test Program!!!!\n");	
	
}

int key_run(){
	char value;
	// i2c_writeByte(0x0F | i2c_readByte());
	// value = i2c_readByte() | 0xF0;
	// printf("%c\n", i2c_readByte());
	if(bcm2835_gpio_lev(PRESSKEY) == 0)
	{  
		printf ("KEY PRESS\n") ;
		// while(bcm2835_gpio_lev(PRESSKEY) == 0)
		// 	bcm2835_delay(10);
		return 1;
	}

	else if(value != 0xFF)
	{
		//if (!bcm2835_init())return 1;  
		bcm2835_i2c_begin(); 
		bcm2835_i2c_setSlaveAddress(0x20);  
	    bcm2835_i2c_set_baudrate(10000);  
		switch(value)
		{	
			case 0xFE:
				printf("left\n");break;	
			case 0xFD:
				printf("up\n");	break;
			case 0xFB:
				printf("dowm\n");break;	
			case 0xF7:
				printf("right\n");break;
			default :
				printf("unknow\n");
		}
		while(value != 0xFF)
		{
			i2c_writeByte(0x0F | i2c_readByte());
			value = i2c_readByte() | 0xF0;
			bcm2835_delay(10);
		}
	}
	return 0;
}

void key_end(){
	bcm2835_close();
}