#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <sensor_data.h>

void monitor(sensor_data **data, int len);
int oled_init();
void oled_run(sensor_data** data, int menu, int key, int view);
//void oled_run(char* temp, char* press, char* alti, char* selectedValue, int menu, int view);
void oled_end();
void displayValue(char* selectedValue, int addY);
int checkValue(sensor_data** data, int view, int menu);
// int* getMinValue();
// int* getMaxValue();
// void setMinValue(int val);
// void setMaxValue(int val);
#endif
