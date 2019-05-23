
/* ***************************************************

This file contains function prototypes for filters.c

***************************************************** */

#ifndef FILTERS_H
	#define FILTERS_H

#include "arm_math.h"
#include "ekf_var.h"
#include "ekf_tmp.h"

void prefilter(arm_matrix_instance_f32* readings,
			arm_matrix_instance_f32* x,
			arm_matrix_instance_f32* P);

void att_filter(arm_matrix_instance_f32* readings,
			arm_matrix_instance_f32* x,
			arm_matrix_instance_f32* P);
	
#endif
