
/* ********** HOW TO USE THIS DRIVER ****************

1. define a gps_value struct variable and initialize it

	gps_value gps_dummy = {0.01,'N',0.01,'E',680000,{2015,5,31},{1,35,3}} ;

2. call the function
	
	gps_dummy = GetGPSValues();

**************************************************** */


#ifndef GPS_H
	#define GPS_H
	
#include "stdint.h"
#include "arm_math.h"

typedef struct{
	uint32_t year;
	uint8_t month;
	uint8_t day;
}Date;

typedef struct{ 
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
}Time;


typedef struct gps_value{
	float32_t latitude_f32; //positive for north
	char latitude_NS;
	float32_t longitude_f32; //positive for east
	char longitude_EW;
	float32_t altitude_f32;
	Date date;
	Time time;
}gps_value;

gps_value GetGPSValues(void);

#endif

