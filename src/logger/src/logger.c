#include <sensor_data.h>
#include <stdio.h>
#include <time.h>
time_t now;
struct tm *timenow;

int logging(char *path, sensor_data **data, int len) {
	int i;
	FILE *file = fopen(path, "a");
	time(&now);
	timenow = localtime(&now);
	for(i = 0 ; i < len ; i++) {
		fprintf(file, "%s-%s-%s ",timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
		fprintf(file, "%.2f", data[i]->value);
		if(i < len-1) fprintf(file, ",");
	}
	fprintf(file, "\n");
	fclose(file);

	return 0;
}
