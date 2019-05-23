
/* *********************************************************

This header file contains declarations of constant arrays
for EKF (both prefilter and attitude filter)

*********************************************************** */


//Prefilter variables

#ifndef EKF_VAR_H
	#define EKF_VAR_H
	
	#include "arm_math.h"
	#include "struct_def.h"
	
extern const float32_t F_pf_f32[81]; //9x9 state transition matrix
								
extern const float32_t H_pf_f32[27]; //3x9 sensor matrix

extern const float32_t Q_pf_f32[81]; // 9x9 process covariance matrix

extern const float32_t R_pf_f32[9]; // 3x3 sensor-noise covariance matrix
								
extern const float32_t w_pf_f32[9]; //9x1 matrix

extern const float32_t v_pf_f32[3]; //3x1 matrix

extern float32_t x_pf_f32[9]; //9x1 state matrix

extern float32_t readings_pf_f32[6]; //6x1 readings matrix

extern float32_t P_pf_f32[49];	//7x7 covariance matrix


//Attitude-filter variable
extern float32_t F_att_f32[49]; //7x7 matrix

extern float32_t H_att_f32[42]; //6x7 matrix

extern float32_t Q_att_f32[49]; //7x7 matrix

extern const float32_t R_att_f32[36]; //6x6 matrix
								
extern const float32_t w_att_f32[7]; //7x1 process-noise matrix

extern const float32_t v_att_f32[6]; //6x1 sensor-noise matrix

extern float32_t x_att_f32[9]; //9x1 state matrix

extern float32_t readings_att_f32[6]; //6x1 readings matrix

extern float32_t P_att_f32[49];	//7x7 covariance matrix


extern const float32_t Ix; //moment-of-inertia about x-axis

extern const float32_t Iy; //moment-of-inertia about y-axis

extern const float32_t Iz; //moment-of-inertia about z-axis

extern float32_t Sx;
extern float32_t Sy;
extern float32_t Sz;

extern float32_t w[3];
extern float32_t q[4],qc[4];
extern float32_t igrfmag[6];


//igrf
extern float32_t Bi_f32[3]; // 3x1

extern float32_t Bi_dot_f32[3]; // 3x1

extern float32_t Bi_dot_tmp_f32[3]; // 3x1

extern float32_t sat_vel_f32[3]; //3x1

extern float32_t deltaBi_f32[9]; // 3x3

extern float32_t Bi_delT_f32[3]; //3x1

extern float32_t theta_x, theta_y, theta_z;
#endif
