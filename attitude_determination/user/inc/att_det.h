

#ifndef ATT_DET_H
	#define ATT_DET_H
	
#include "ekf_var.h"
#include "ekf_init.h"

#include "magnetometer.h"
#include "gps.h"
#include "igrf.h"
#include "prefilter.h"
#include "att_filter.h"
	
void att_det(void);
	
#endif