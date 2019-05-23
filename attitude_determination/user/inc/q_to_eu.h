
/* *********************************************************************

q_to_eu ( ) :
	This function converts quaternions 
	to Euler angles.

********************************************************************* */
#ifndef Q_TO_EU_H
	#define Q_TO_EU_H
	
	#include "math.h"
	#include "arm_math.h"
	#include "ekf_var.h"
	
	extern float32_t x_f32[7];
	
	void q_to_eu(void);
	
#endif
