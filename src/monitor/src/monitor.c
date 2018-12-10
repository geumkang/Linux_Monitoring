#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
#include <bcm2835.h>
#include <string.h>

char value[10]={'0','1','2','3','4','5','6','7','8','9'};
time_t now;
struct tm *timenow;

void monitor(sensor_data **data, int len){
	int i = 0;
	for(i = 0 ; i < len ; i++) {
		fprintf(stdout, "%s: %0.2f %s\n", data[i]->name, data[i]->value, data[i]->unit);
	}
}

int oled_init(){
	if(!bcm2835_init()) return 1;
	printf("OLED Test Program !!!\n");

	SSD1306_begin();
	SSD1306_bitmap(0,0,waveshare,128,64);
	SSD1306_display();
	bcm2835_delay(2000);
	SSD1306_clear();
}

void oled_run(char* temp, char* press, char* alti, char* selectedValue){
	time(&now);
	timenow = localtime(&now);

	SSD1306_bitmap(0, 2, Singal816, 16, 8); 
	SSD1306_bitmap(24, 2,Bluetooth88, 8, 8); 
	SSD1306_bitmap(40, 2, Msg816, 16, 8); 
	SSD1306_bitmap(64, 2, GPRS88, 8, 8); 
	SSD1306_bitmap(90, 2, Alarm88, 8, 8); 
	SSD1306_bitmap(112, 2, Bat816, 16, 8); 

	SSD1306_string(0, 52, temp, 12, 0); 
	SSD1306_string(52, 52, press, 12, 0); 
	SSD1306_string(98, 52, alti, 12, 0);

	int i = 0;
	int pos = 16
	for(i = 0; i < strlen(selectedValue); i++){
		SSD1306_char3216(0,pos, selectedValue[i]);	
		pos += 16;
	}
	
	SSD1306_display();
}

void oled_end(){
	bcm2835_spi_end();
	bcm2835_close();
}
