/* ******* HOW TO USE THIS DRIVER ************** */

/*

1. include the files igrf.c and igrf_data.c

2. include the header file igrf.h

3. define a structure gps_value

4. call the function igrf(gps_value gps)

Eg.

gps_value gps_dummy = {13.1,'N',77.6,'E',0.915,{2017,1,24},{0,0,0}} ; //'05-31-1994 01:35:3'

mag_field test_field;

test_field = igrf(gps_dummy);

*/

/*

Inputs : gps_value structure
	latitude : in degrees (+ve for NORTH)
	longitude : in degrees (+ve for EAST)
	altitude : in km (mean sea level)
	date : year month date
	time : hh mm yy
	
Outputs : magnetic field vector in NED geodetic frame
	[Bx By Bz]

*/