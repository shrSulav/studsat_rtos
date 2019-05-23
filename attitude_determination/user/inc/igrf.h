
/* *************************************************************

igrf( ):
	This function takes gps data and calculates
	magnetic field Bi in inertial frame.

*************************************************************** */

#ifndef IGRF_H
	#define IGRF_H

#include "math.h"
#include "ekf_var.h"
#include "stdio.h"
#include "struct_def.h"
#include "igrf_data.h"
#include "e_time.h"
	
#define N 0
#define M 1
#define VALI 2
#define SVI 3

extern float32_t Bix, Biy, Biz;
extern float32_t igrfh[IGRF_ROW][IGRF_COL];
extern float32_t igrfg[IGRF_ROW][IGRF_COL];
extern float32_t g[IGRF_ROW][IGRF_ROW + 1];
extern float32_t h[IGRF_ROW][IGRF_ROW + 1];
extern float32_t days;

void igrf(gpsData gps, float32_t B[]); // takes gps data and computes magnetic field values
	
#endif
