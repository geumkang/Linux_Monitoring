#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
#include <bcm2835.h>
#include <string.h>
#include <sensor_data.h>
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
void oled_run(sensor_data* data, int menu, int view){
//void oled_run(char* temp, char* press, char* alti, char* selectedValue, int menu, int view){
	printf("%s\n", data[0]->unit);
	printf("%s%d~~\n", "view : ", view);
	int selectedMenu[3] = {1,1,1};
	selectedMenu[menu] = 0;
	char* min = malloc(40 * sizeof(char));
	char* max = malloc(40 * sizeof(char));
	sprintf(min, "%s%d", "Min : ", minValue);
	sprintf(max, "%s%d", "Max : ", maxValue);
	SSD1306_string(0, 2, min, 12, 1);
	SSD1306_string(60, 2, max, 12, 1);
	
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
		sprintf(min, "%d%s", minValue, selectedValue);
		SSD1306_string(0, 16, Description, 12, 1);
		
		displayValue(min, 12);
	}
	else if(view == 2){
		printf("%s %d\n", "버튼 : ", menu);
		if(maxValue == 0){
			if(menu == 0)
				maxValue = minValue + 1;
			else if(menu == 1)
				maxValue = minValue + 1;
			else if(menu == 2)
				maxValue = minValue + 1;
		}
		if(menu == UP) maxValue++;
		else if(menu == DOWN && maxValue >= minValue + 1) maxValue--;
		char* Description = malloc(40 * sizeof(char));
		sprintf(Description, "%s", "Max Value");
		sprintf(max, "%d%s", maxValue, selectedValue);
		SSD1306_string(0, 16, Description, 12, 1);
		
		displayValue(max, 12);
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

void setMinValue(int val){
	minValue = val;
}

void setMaxValue(int val){
	maxValue = val;
}