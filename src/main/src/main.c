#include <stdio.h>
#include <stdlib.h>
#include <bmp180.h>
#include <ads1256.h>
#include <bcm2835.h>
#include <monitor.h>
#include <logger.h>
#include <sensor_data.h>
#include <control.h>
#include <string.h>

#define SENSOR_BMP180
//#define SENSOR_ADS1256

int main(){
	int *view = NULL;
	int i = 0;
	int result = 0;
	int menu = 0, key = 0;
	int notice = 0;
	oled_init();
	key_init();
	view = getView();
	/* Data Storage Preparation */
	int nData = 3;
	sensor_data **data = NULL;
	data = (sensor_data *)malloc(sizeof(sensor_data*) * nData);
	for(i = 0 ; i < nData ; i++) {
		data[i] = sensor_data_init();
	}

	/* Initialize */
#ifdef SENSOR_BMP180
	if(!bmp180_begin()) return 1;
#endif
#ifdef SENSOR_ADS1256
	if(!ads1256_begin()) return 1;
#endif

	while(1){
		bcm2835_i2c_setSlaveAddress(0x77);  
    	bcm2835_i2c_set_baudrate(10000);
		/* Sensing */
#ifdef SENSOR_BMP180
		sensor_data_set(data[0], "temp", SENSOR_DATA_TYPE_DOUBLE, read_temperature(), "C");
		sensor_data_set(data[1], "press", SENSOR_DATA_TYPE_DOUBLE, read_pressure()/100.0, "Pa");
		sensor_data_set(data[2], "alti", SENSOR_DATA_TYPE_DOUBLE, read_altitude(), "h");
#endif
#ifdef SENSOR_ADS1256
		while((ADS1256_Scan() == 0));
		for (i = 0; i < nData; i++)
		{
			sensor_data_set(data[i], "???", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(i) /1670.0, "mV");
		}
#endif
		/* Control */
		checkControl(&menu, &key);

		/* Monitor */
		monitor(data, nData);
		oled_run(data, menu, key, *view);
		fprintf(stdout, "\n");  
		
		/* Check */
		notice = checkValue(data, *view, menu);
		if(*view == 0) noticeWarning(notice);

		/* Logging */
		result = logging("data/data_corpus.dat", data, nData, notice, menu);
		if(result) {
			fprintf(stderr, "File is not written.\n");
			return 1;
		}
		
		/* Timer */
		bsp_DelayUS(100000);
		bcm2835_delay(200);
	}

	/* Clean-up */
	for(i = 0 ; i < nData ; i++) {
		sensor_data_deinit(&data[i]);
	}
	free(data);
#ifdef SENSOR_BMP180
	bmp180_end();
	oled_end();
#endif
#ifdef SENSOR_ADS1256
	ads1256_end();
#endif

	return 0;
}
