#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <sensor_data.h>

void monitor(sensor_data **data, int len);
int oled_init();
void oled_run();
void oled_end();
#endif
