/*

Input :
	float32_t time
	float32_t x
	float32_t y
	float32_t z

Output: (all the 4 are global variables)
	float32_t eci_to_lla_time
	float32_t eci_to_lla_lat
	float32_t eci_to_lla_lon
	float32_t eci_to_lla_hae

*/


#ifndef ECI_TO_LLA_H
	#define ECI_TO_LLA_H

#include "stdint.h"

void eci_to_lla(const float32_t time,const float32_t x,const float32_t y,const float32_t z,);

#endif