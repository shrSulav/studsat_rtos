
/*This source file contains definitions of constant variables for EKF (both prefilter and attitude filter)*/



//#include "ekf_var.h"

#include "math.h"
#include "arm_math.h"

// **************** Prefilter variables ************************************************************

//9x9 state transition matrix
const float32_t F_pf_f32[81] = { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0  };

//3x9 sensor matrix
const float32_t H_pf_f32[27] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 	 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 	 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0  };

// 9x9 process covariance matrix
const float32_t Q_pf_f32[81] = { 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1 };

// 3x3 sensor-noise covariance matrix
float32_t R_pf_f32[9] = {1.0, 0.0, 0.0,
						 0.0, 1.0, 0.0,
						 0.0, 0.0, 1.0};
//9x1 matrix
const float32_t w_pf_f32[9] = { 0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.009 }; 

const float32_t v_pf_f32[3] ={ 0.001, 0.0165, 0.002 }; //3x1 

float32_t x_pf_f32[9]; //9x1 state matrix

float32_t readings_pf_f32[3]; //3x1 readings matrix

float32_t P_pf_f32[81] = {  1,0,0,0,0,0,0,0,0,
							0,1,0,0,0,0,0,0,0,
							0,0,1,0,0,0,0,0,0,
							0,0,0,100,0,0,0,0,0,
							0,0,0,0,100,0,0,0,0,
							0,0,0,0,0,100,0,0,0,
							0,0,0,0,0,0,100,0,0,
							0,0,0,0,0,0,0,100,0,
							0,0,0,0,0,0,0,0,100 };	//9x9 covariance matrix




// ******** Attitude-filter variable *****************************************************8
const float32_t Ix=0.035; //moment-of-inertia about x-axis
const float32_t Iy=0.03; //moment-of-inertia about y-axis
const float32_t Iz=0.03; //moment-of-inertia about z-axis

float32_t Sx=(Iy-Ix)/Ix;
float32_t Sy=(Iz-Ix)/Iy;
float32_t Sz=(Ix-Iy)/Iz;

float_t F_att_f32[49];

float32_t H_att_f32[42] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
							0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
							0.0, 0.0, 0.0, 0.0, 0.0, 1.0}; //6x7 matrix
float32_t Q_att_f32[49] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
							0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
							0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
							0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}; //7x7matrix

const float32_t R_att_f32[36] = {80.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 80.0, 0.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 80.0, 0.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 160.0, 0.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 160.0, 0.0,
								 0.0, 0.0, 0.0, 0.0, 0.0, 160.0 }; //6x6 matrix
								
const float32_t w_att_f32[7]={ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; //7x1 process-noise matrix

const float32_t v_att_f32[6] ={ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; //6x1 sensor-noise matrix


float32_t w[3];
float32_t q[4],qc[4];


float32_t x_att_f32[9]; //9x1 state matrix

float32_t readings_att_f32[6]; //6x1 readings matrix


float32_t P_att_f32[49] = { 10,0,0,0,0,0,0, 
							0,10,0,0,0,0,0,
							0,0,10,0,0,0,0,
							0,0,0,10,0,0,0,
							0,0,0,0,1,0,0,
							0,0,0,0,0,1,0,
							0,0,0,0,0,0,1, }; //7x7 covariance matrix

// ********************** IGRF variables *************************//

//float32_t igrfmag[6];
float32_t igrfmag[6];

float32_t Bi_f32[3]; // 3x1

float32_t Bi_dot_tmp_f32[3]; //3x1

float32_t Bi_dot_f32[3]; // 3x1

float32_t sat_vel_f32[3]; //3x1

float32_t sat_pos_f32[3]; //3x1

float32_t deltaBi_f32[9]; //3x3

float32_t Bi_delT_f32[3]; //3x1

/*
typedef struct{
	uint32_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hh;
	uint8_t mm;
	uint8_t ss;
}datetime;


typedef struct {
	float32_t lat_f32;
	float32_t long_f32;
	float32_t alti;
	datetime date_gps;
}gpsData;
*/

float32_t theta_x, theta_y, theta_z; //Used in q_to_eu ( ) 
