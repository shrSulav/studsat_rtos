
#include "gps.h"

gps_value gps_input = {0.01,'N',0.01,'E',680000,{2015,5,31},{1,35,3}} ;
float32_t magnm_ref[3];
float32_t sunvec_ref[3];

float32_t magnm_gauss_new[3];
float32_t magnm_gauss_old[3];
float32_t sunvec_body[3];
float32_t ang_velocity[3];
