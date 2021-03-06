#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
#include <bcm2835.h>
#include <string.h>
#include <sensor_data.h>

#define UP 4
#define DOWN 5

char value[10]={'0','1','2','3','4','5','6','7','8','9'};
int minValue[3] = {0,0,0};
int maxValue[3] = {0,0,0};
int isRunning[3] = {0,0,0};
int beforeMenu = 0;

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

void oled_run(sensor_data** data, int menu, int key, int view){
//void oled_run(char* temp, char* press, char* alti, char* selectedValue, int menu, int view){
	char* selectedValue = malloc(40 * sizeof(char));
	if(view != 0)
		sprintf(selectedValue, "%s", data[menu]->unit);
	else{
		sprintf(selectedValue, "%.2f %s", data[menu]->value, data[menu]->unit);
	}
	
	int selectedMenu[3] = {1,1,1};
	selectedMenu[menu] = 0;
	char* min = malloc(40 * sizeof(char));
	char* max = malloc(40 * sizeof(char));

	if(view == 0){
		if(key == DOWN){
			minValue[menu] = 0;
			maxValue[menu] = 0;
		}
		SSD1306_string(0, 52, data[0]->name, 12, selectedMenu[0]); 
		SSD1306_string(46, 52, data[1]->name, 12, selectedMenu[1]); 
		SSD1306_string(98, 52, data[2]->name, 12, selectedMenu[2]);
		displayValue(selectedValue, 0);
	}
	else if(view == 1){
		if(isRunning[menu] == 0){
			isRunning[menu] = 1;
			if(menu == 0)
				minValue[menu] = (int)(data[0]->value);
			else if(menu == 1)
				minValue[menu] = (int)(data[1]->value);
			else if(menu == 2)
				minValue[menu] = (int)(data[2]->value);
		}
		if(key == UP) minValue[menu]++;
		else if(key == DOWN) minValue[menu]--;
		char* Description = malloc(40 * sizeof(char));
		sprintf(Description, "%s", "Min Value");
		sprintf(min, "%d%s", minValue[menu], selectedValue);
		SSD1306_string(0, 16, Description, 12, 1);
		
		displayValue(min, 12);
	}
	else if(view == 2){
		if(isRunning[menu] == 1){
			isRunning[menu] = 0;
			if(menu == 0)
				maxValue[menu] = minValue[menu] + 1;
			else if(menu == 1)
				maxValue[menu] = minValue[menu] + 1;
			else if(menu == 2)
				maxValue[menu] = minValue[menu] + 1;
		}
		if(key == UP) maxValue[menu]++;
		else if(key == DOWN && maxValue[menu] >= minValue[menu] + 1) maxValue[menu]--;
		char* Description = malloc(40 * sizeof(char));
		sprintf(Description, "%s", "Max Value");
		sprintf(max, "%d%s", maxValue[menu], selectedValue);
		SSD1306_string(0, 16, Description, 12, 1);
		
		displayValue(max, 12);
	}

	sprintf(min, "%s%d", "Min : ", minValue[menu]);
	sprintf(max, "%s%d", "Max : ", maxValue[menu]);
	SSD1306_string(0, 2, min, 12, 1);
	SSD1306_string(65, 2, max, 12, 1);

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

int checkValue(sensor_data** data, int view, int menu){
	if(view == 0){
		if(beforeMenu != menu){
			beforeMenu = menu;
			return 0;
		}
		if(minValue[menu] != 0){
			if(data[menu]->value < minValue[menu] || data[menu]->value > maxValue[menu]){
				return 1;	
			}
		}
	}
}

// int* getMinValue(){
// 	return &minValue;
// }

// int* getMaxValue(){
// 	return &maxValue;
// }

// void setMinValue(int val, int menu){
// 	minValue[menu] = val;
// }

// void setMaxValue(int val, int menu){
// 	maxValue[menu] = val;
// }