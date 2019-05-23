

/* *******************************************************

This file includes function definition of 

	e_time :

	input arguements
		variables of type struct Date

	output arguements
		number of days between the two dates

*********************************************************** */

#ifndef E_TIME_H
	#define E_TIME_H

#include "stdint.h"
#include "struct_def.h"

float32_t e_time(Date dt1, Date dt2);

#endif
