#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
#include <bcm2835.h>
#include <string.h>

#define UP 100
#define DOWN 200

char value[10]={'0','1','2','3','4','5','6','7','8','9'};
int minValue = 0;
int maxValue = 0;

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

void oled_run(char* temp, char* press, char* alti, char* selectedValue, int menu, int view){
	printf("%d~~\n", view);
	int selectedMenu[3] = {1,1,1};
	selectedMenu[menu] = 0;

	SSD1306_bitmap(0, 2, Singal816, 16, 8); 
	SSD1306_bitmap(24, 2,Bluetooth88, 8, 8); 
	SSD1306_bitmap(40, 2, Msg816, 16, 8); 
	SSD1306_bitmap(64, 2, GPRS88, 8, 8); 
	SSD1306_bitmap(90, 2, Alarm88, 8, 8); 
	SSD1306_bitmap(112, 2, Bat816, 16, 8); 
	
	if(view == 0){
		SSD1306_string(0, 52, temp, 12, selectedMenu[0]); 
		SSD1306_string(46, 52, press, 12, selectedMenu[1]); 
		SSD1306_string(98, 52, alti, 12, selectedMenu[2]);
		displayValue(selectedValue, 0);
	}
	else if(view == 1){
		printf("%s %d\n", "버튼 : ", menu);
		if(minValue == 0){
			if(menu == 0)
				minValue = 35;
			else if(menu == 1)
				minValue = 1016;
			else if(menu == 2)
				minValue = 15;
		}
		if(menu == UP) minValue++;
		else if(menu == DOWN) minValue--;
		char* Description = malloc(40 * sizeof(char));
		sprintf(Description, "%s", "Min Value");
		SSD1306_string(0, 16, Description, 12, 1);
		char* min = malloc(40 * sizeof(char));
		sprintf(min, "%d%s", minValue, currentValue);
		displayValue(min, 12);
	}
	
	SSD1306_display();
}

void oled_end(){
	bcm2835_spi_end();
	bcm2835_close();
}

void displayValue(char* selectedValue, int addY){
	int i = 0;
	int pos = 0;
	int size;
	if(strlen(selectedValue) > 10) size = 10;
	else size = strlen(selectedValue);
	for(i = 0; i < size; i++){
		if(selectedValue[i] == '.'){
			SSD1306_char(pos, 32 + addY, selectedValue[i], 16, 1);
			pos += 2;
		}
		else if(selectedValue[i] == ' '){

		}
		else{ 
			SSD1306_char3216(pos, 16 + addY, selectedValue[i]);	
			pos += 16;
		}		
	}
}

int* getMinValue(){
	return &minValue;
}

int* getMaxValue(){
	return &maxValue;
}