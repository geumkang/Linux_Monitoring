#include <monitor.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"
char value[10]={'0','1','2','3','4','5','6','7','8','9'};

void monitor(sensor_data **data, int len){
	int i = 0;
	for(i = 0 ; i < len ; i++) {
		fprintf(stdout, "%s: %0.2f %s\n", data[i]->name, data[i]->value, data[i]->unit);
	}
}
