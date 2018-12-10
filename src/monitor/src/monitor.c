#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
#include <bcm2835.h>

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

void oled_run(char* data){
	time(&now);
	timenow = localtime(&now);

	SSD1306_bitmap(0, 2, Singal816, 16, 8); 
	SSD1306_bitmap(24, 2,Bluetooth88, 8, 8); 
	SSD1306_bitmap(40, 2, Msg816, 16, 8); 
	SSD1306_bitmap(64, 2, GPRS88, 8, 8); 
	SSD1306_bitmap(90, 2, Alarm88, 8, 8); 
	SSD1306_bitmap(112, 2, Bat816, 16, 8); 

	SSD1306_string(0, 52, str, 12, 0); 
	SSD1306_string(52, 52, "MENU", 12, 0); 
	SSD1306_string(98, 52, "PHONE", 12, 0);

	SSD1306_char3216(0,16, value[timenow->tm_hour/10]);
	SSD1306_char3216(16,16, value[timenow->tm_hour%10]);
	SSD1306_char3216(32,16, ':');
	SSD1306_char3216(48,16, value[timenow->tm_min/10]);
	SSD1306_char3216(64,16, value[timenow->tm_min%10]);
	SSD1306_char3216(80,16, ':');
	SSD1306_char3216(96,16, value[timenow->tm_sec/10]);
	SSD1306_char3216(112,16, value[timenow->tm_sec%10]);
	
	SSD1306_display();
}

void oled_end(){
	bcm2835_spi_end();
	bcm2835_close();
}
