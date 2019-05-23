
/* *******************************************************

determine_attitude( ):
	It is the final function.
	Calling this function would give the quaternion values. 

******************************************************* */

#ifndef FINAL_FUNC_H
	#define FINAL_FUNC_H

#include "ekf_var.h"	// variable definition for prefilter and attitude filter
#include "ekf_init.h"	// 
#include "igrf.h"		// function definition for igrf code
#include "filters.h"	// function definition for prefilter and attitude filter
#include "struct_def.h" // structure definition for gps data
#include "arm_math.h"	// math functions
#include "b_grad.h"

extern float32_t Bbx,Bby,Bbz; //defined in magnetometer
extern float32_t Bix, Biy, Biz;		//defined in igrf_data.c

void initialize_ekf( void );
void determine_attitude ( void );
void igrf_derivative ( void );

#endif
