#include <sensor_data.h>
#include <stdio.h>
#include <time.h>
time_t now;
struct tm *timenow;

int logging(char *path, sensor_data **data, int len, int notice, int menu) {
	if(notice == 1){
		int i;
		FILE *file = fopen(path, "a");
		time(&now);
		timenow = localtime(&now);
		fprintf(file, "%d-%d-%d %d:%d:%d ",timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday, timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
		fprintf(file, "%.2f%s", data[menu]->value, data[menu]->unit);
		fprintf(file, "\n");
		fclose(file);
	}	
	return 0;
}
