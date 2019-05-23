
/* **********************************************

This header file includes structure definitions for 
	gpsData used by igrf code
	Bb used by magnetometer code 

********************************************** */

#ifndef STRUCT_DET_H
	#define STRUCT_DET_H
	
	#include "stdint.h"
	#include "arm_math.h"
	
typedef struct{
	uint32_t year;
	uint8_t month;
	uint8_t day;
}Date;

typedef struct{
	Date date; 
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
}datetime;

typedef struct {
	float32_t lat_f32;
	float32_t long_f32;
	float32_t alti;
	datetime date_gps;
}gpsData;

typedef struct {
	float32_t Bbx;
	float32_t Bby;
	float32_t Bbz;
} Bb;
	
#endif
