//Header file for ekf_init.c file

/* ************************************************** 

This file includes matrix declarations used in
prefilter, attitude filter and igrf code

Include this file wherever the matrices are used.

Do not include this in ekf_init.c

**************************************************** */

#ifndef EKF_INIT_H
	#define EKF_INIT_H
	
#include "arm_math.h"

extern arm_matrix_instance_f32 F_pf; //9x9
extern arm_matrix_instance_f32 H_pf; //3x9
extern arm_matrix_instance_f32 Q_pf; //9x9
extern arm_matrix_instance_f32 R_pf; //3x3
extern arm_matrix_instance_f32 v_pf; //3x1
extern arm_matrix_instance_f32 w_pf; //9x1

extern arm_matrix_instance_f32 Q_att; //9x9
extern arm_matrix_instance_f32 R_att; //3x3
extern arm_matrix_instance_f32 v_att; //3x1
extern arm_matrix_instance_f32 w_att; //9x1
extern arm_matrix_instance_f32 F_att; //7x7
extern arm_matrix_instance_f32 H_att; //6x7

//IGRF matrices
extern arm_matrix_instance_f32 Bi;
extern arm_matrix_instance_f32 Bi_dot;	//3x1
extern arm_matrix_instance_f32 Bi_dot_tmp;	//3x1
extern arm_matrix_instance_f32 sat_vel; //3x1
extern arm_matrix_instance_f32 deltaBi; //3x3


// function prototypes
void init_pf(void);
void init_att(void);
void init_igrf(void);

#endif
