#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <sensor_data.h>

void monitor(sensor_data **data, int len);
int oled_init();
void oled_run(char* temp, char* press, char* alti, char* selectedValue, int menu, int* view);
void oled_end();
#endif
