#include "b_grad.h"
#include "eci_to_lla.h"
#include "arm_math.h"
#include "struct_def.h"

// create a 3x3 b_grad matrix

/*
inputs :
	(x,y,z) ECI co-ordinates

outputs :
	B_Gradient matrix of 3x3 size 
*/

//float32_t dox_plus[3], doy_plus[3], doz_plus[3], dox_minus[3], doy_minus[3], doz_minus[3];

extern gpsData eci2lla;
extern float32_t deltaBi_f32[9];
extern arm_matrix_instance_f32 Bi_delT;
extern float32_t sat_pos_f32[3];
extern float32_t sat_vel_f32[3];

float32_t Bi_tmp_plus_f32[3]; //3x1
float32_t Bi_tmp_minus_f32[3]; //3x1
float32_t Bi_tmp_f32[3]; //3x1
float32_t Bi_tmp_del_f32[3]; //3x1

arm_matrix_instance_f32 Bi_tmp_plus;
arm_matrix_instance_f32 Bi_tmp_minus;
arm_matrix_instance_f32 Bi_tmp;
arm_matrix_instance_f32 Bi_tmp_del;

 //reciprocal of time diff in seconds of the successive samples

void b_grad_init(void)
{
	uint32_t srcRows, srcColumns;
	srcRows = 3;
	srcColumns = 1;
	arm_mat_init_f32(&Bi_tmp_plus, srcRows, srcColumns, Bi_tmp_plus_f32);
	arm_mat_init_f32(&Bi_tmp_minus, srcRows, srcColumns, Bi_tmp_minus_f32);
	arm_mat_init_f32(&Bi_tmp, srcRows, srcColumns, Bi_tmp_f32);
	arm_mat_init_f32(&Bi_tmp_del, srcRows, srcColumns, Bi_tmp_del_f32);
}

void b_grad(void)
{
	static const float32_t delx = 75000;
	static const float32_t dely = 75000;
	static const float32_t delz = 75000; //in metres
	static const float32_t delT = 0.1; //in seconds
	static const float32_t h_inv = 1/delT;
	/*
	dox_plus = x + [delx,0,0];
	doy_plus = x + [0,dely,0];
	doz_plus = x + [0,0,delz];
	
	dox_minus = x - [delx,0,0];
	doy_minus = x - [0,dely,0];
	doz_minus = x - [0,0,delz];
	*/
	/*
	dox_plus[0] = eci_x + delx;
	dox_plus[1] = eci_y;
	dox_plus[2] = eci_z;

	
	doy_plus[0] = eci_x;
	doy_plus[1] = eci_y + delz;
	doy_plus[2] = eci_z;
	
	dox_plus[0] = eci_x + delx;
	dox_plus[1] = eci_y;
	dox_plus[2] = eci_z;
*/
	//********* 1st column of deltaBi matrix ****************//

	eci_to_lla(time, sat_pos_f32[0] + delx , sat_pos_f32[1], sat_pos_f32[2]); // (t, x + delx, y, z)
	igrf(eci2lla, Bi_tmp_plus_f32); //igrf function call

	eci_to_lla(time, sat_pos_f32[0] - delx, sat_pos_f32[1], sat_pos_f32[2]); // (t, x - delx, y, z)
	igrf(eci2lla, Bi_tmp_minus_f32); //igrf function call

	arm_mat_sub_f32(&Bi_tmp_plus, &Bi_tmp_minus, &Bi_tmp);
	arm_mat_scale_f32(&Bi_tmp, h_inv, &Bi_tmp_del);

	deltaBi_f32[0] = Bi_tmp_del_f32[0];
	deltaBi_f32[3] = Bi_tmp_del_f32[1];
	deltaBi_f32[6] = Bi_tmp_del_f32[2];

	//********* 2nd column of deltaBi matrix ****************//

	eci_to_lla(time, sat_pos_f32[0], sat_pos_f32[1] + dely, sat_pos_f32[2]); // (t, x, y + dely , z)
	igrf(eci2lla, Bi_tmp_plus_f32); //igrf function call

	eci_to_lla(time, sat_pos_f32[0], sat_pos_f32[1] - dely, sat_pos_f32[2]); // (t, x, y - dely , z)
	igrf(eci2lla, Bi_tmp_minus_f32); //igrf function call
	arm_mat_sub_f32(&Bi_tmp_plus, &Bi_tmp_minus, &Bi_tmp);
	arm_mat_scale_f32(&Bi_tmp, h_inv, &Bi_tmp_del);

	deltaBi_f32[1] = Bi_tmp_del_f32[0];
	deltaBi_f32[4] = Bi_tmp_del_f32[1];
	deltaBi_f32[7] = Bi_tmp_del_f32[2];

	//********* 3rd column of deltaBi matrix ****************//

	eci_to_lla(time, sat_pos_f32[0], sat_pos_f32[1], sat_pos_f32[2] + delz); // (t, x, y , z + delz)
	igrf(eci2lla, Bi_tmp_plus_f32); //igrf function call

	eci_to_lla(time, sat_pos_f32[0], sat_pos_f32[1], sat_pos_f32[2] - delz); // (x, y, z - delz)
	igrf(eci2lla, Bi_tmp_minus_f32); //igrf function call

	arm_mat_sub_f32(&Bi_tmp_plus, &Bi_tmp_minus, &Bi_tmp);
	arm_mat_scale_f32(&Bi_tmp, h_inv, &Bi_tmp_del);

	deltaBi_f32[2] = Bi_tmp_del_f32[0];
	deltaBi_f32[5] = Bi_tmp_del_f32[1];
	deltaBi_f32[8] = Bi_tmp_del_f32[2];

	//********* Partial Derivative of B wrt time ****************//

	eci_to_lla(time + delT, sat_pos_f32[0], sat_pos_f32[1], sat_pos_f32[2]); // (t + delT, x, y, z)
	igrf(eci2lla, Bi_tmp_plus_f32); //igrf function call

	eci_to_lla(time - delT, sat_pos_f32[0], sat_pos_f32[1], sat_pos_f32[2]); // (t - delT, x, y, z)
	igrf(eci2lla, Bi_tmp_minus_f32); //igrf function call

	arm_mat_sub_f32(&Bi_tmp_plus, &Bi_tmp_minus, &Bi_tmp);
	arm_mat_scale_f32(&Bi_tmp, h_inv, &Bi_delT);

}