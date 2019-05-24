/* ******* HOW TO USE THIS DRIVER ************** */

/*

1. include the files igrf.c and igrf_data.c

2. include the header file igrf.h

3. define a structure gps_value

4. call the function igrf(gps_value gps)

Eg.

gps_value gps_dummy = {13.1,'N',77.6,'E',0.915,{2017,1,24},{0,0,0}} ; //'05-31-1994 01:35:3'

float32_t magnm_field[3];

igrf(gps_dummy, magnm_field);

*/

/*

Inputs : gps_value structure
	latitude : in degrees (+ve for NORTH)
	longitude : in degrees (+ve for EAST)
	altitude : in km (mean sea level)
	date : year month date
	time : hh mm yy
	
Outputs : magnetic field vector in NED frame
		[Bx By Bz]

*/



#ifndef IGRF_H
	#define IGRF_H

#include "gps.h"
#include "arm_math.h"

void igrf(gps_value gps, float32_t magnm_field[3]); // takes gps data and computes magnetic field values

#endif
