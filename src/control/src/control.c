#include <control.h>
#include <stdio.h>
#include<bcm2835.h>

#define beep_on  i2c_writeByte(0x7F & i2c_readByte())
#define beep_off i2c_writeByte(0x80 | i2c_readByte())
#define led_off   i2c_writeByte(0x10 | i2c_readByte())
#define led_on  i2c_writeByte(0xEF & i2c_readByte())

int SELECTED_VIEW = 0;
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
	if (!bcm2835_init()) return 1;
	bcm2835_gpio_fsel(PRESSKEY, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PRESSKEY, BCM2835_GPIO_PUD_UP);
	bcm2835_i2c_setSlaveAddress(0x20);  
    bcm2835_i2c_set_baudrate(10000);  
	printf("Key Test Program!!!!\n");	
	
}

int key_run(){
	char value;
	if(bcm2835_gpio_lev(PRESSKEY) == 0)
	{  
		printf ("KEY PRESS\n") ;
		return 1;
	}
	else {
		bcm2835_i2c_setSlaveAddress(0x20);  
	    bcm2835_i2c_set_baudrate(10000);  
		bcm2835_delay(100);
		i2c_writeByte(0x0F | i2c_readByte());
		value = i2c_readByte() | 0xF0;
		if(value != 0xFF)
		{
			switch(value)
			{	
				case 0xFE:
					printf("left\n");
					return 2;
				case 0xF7:
					printf("right\n");
					return 3;
				case 0xFD:
					printf("up\n");
					return 4;
				case 0xFB:
					printf("down\n");
					return 5;
				default :
					printf("unknow\n");
			}
		}
	}
	bcm2835_i2c_setSlaveAddress(0x77);  
    bcm2835_i2c_set_baudrate(10000);

	return 0;
}

void key_end(){
	bcm2835_close();
}

void checkControl(int *menu, int *key){
	*key = key_run();
	if(*key == 1){
		SELECTED_VIEW = (SELECTED_VIEW+1) % 3;
	}
	else if(*key == 2){		// left
		if(SELECTED_VIEW == 0)
			*menu = (*menu+2) % 3;
	}	
	else if(*key == 3){		// right
		if(SELECTED_VIEW == 0)
			*menu = (*menu+1) % 3;
	}
	else if(*key == 4){		// up
		
	}
	else if(*key == 5){		// down
		
	}
}

void noticeWarning(int notice){
	if(notice == 1){
		bcm2835_i2c_setSlaveAddress(0x20);  
	    bcm2835_i2c_set_baudrate(10000);  
		bcm2835_delay(100);
		led_on;
		bcm2835_i2c_setSlaveAddress(0x77);  
    	bcm2835_i2c_set_baudrate(10000);
	}
}

int* getView(){
	return &SELECTED_VIEW;
}