#include "att_det.h"

//initialize prefilter and attitude_filter before using att_det

//init_pf();	//initialize prefilter
//init_att(); //initialize attitude-filter

void att_det(void)
{
	magnetometer(); //get Bb from magnetometer
	gps();	//get lat-long-altitude-date from gps
	igrf(); //get Bi from igrf
	prefilter(); //determine Bb and Bb_dot
	att_filter(); //determine attitude and angular rates [quaternions,omega]
}
