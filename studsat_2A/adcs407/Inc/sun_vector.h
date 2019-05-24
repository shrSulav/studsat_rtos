/*************************************************
HOW TO USE THIS DRIVER

1. Initialize the date vector
		uint32_t date[6];
		date[0] : year
		date[1] : month
		date[2] : day
		date[3] : hh
		date[4] : mm
		date[5] : ss
		
2. Initialize array for sun vector
		float32_t sun_vec
		
2. call the function
		sun_vector(date, sun_vec)
***************************************************/

#ifndef SUN_VECTOR_H
	#define SUN_VECTOR_H
#include "arm_math.h"
#include "gps.h"

void sun_vector_ref(const Date date, const Time time, float32_t sun_vec[3]);
float32_t findjd(const Date date, const Time time);
void sun_vector_body(float32_t* sunvec_body);
#endif
