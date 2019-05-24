
#include "gps.h"
#include "arm_math.h"

extern gps_value gps_input;
extern float32_t magnm_ref[3];
extern arm_matrix_instance_f32 A_mat;
extern float32_t sunvec_ref[3];
extern float32_t magnm_gauss_new[3];
extern float32_t magnm_gauss_old[3];
extern float32_t sunvec_body[3];
extern float32_t ang_velocity[3];
