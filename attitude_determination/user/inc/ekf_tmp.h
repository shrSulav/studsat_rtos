
/* ************************************************** 

This file includes variable declarations for temporary
variables used in prefilter and attitude filter.

Include this file in filters.h

Do not include this file in ekf_tmp.c

**************************************************** */



#ifndef EKF_TMP_H
	#define EKF_TMP_H

#include "arm_math.h"

extern arm_matrix_instance_f32 Fx;
extern arm_matrix_instance_f32 Hxbar;
extern arm_matrix_instance_f32 FP;
extern arm_matrix_instance_f32 FT;
extern arm_matrix_instance_f32 FPFT;
extern arm_matrix_instance_f32 Pbar;
extern arm_matrix_instance_f32 PbarHT;
extern arm_matrix_instance_f32 HT;
extern arm_matrix_instance_f32 HPbarHT;
extern arm_matrix_instance_f32 deno;
extern arm_matrix_instance_f32 denoinv;
extern arm_matrix_instance_f32 corr;
extern arm_matrix_instance_f32 K;
extern arm_matrix_instance_f32 KH;
extern arm_matrix_instance_f32 I;
extern arm_matrix_instance_f32 IKH;
extern arm_matrix_instance_f32 xbar;
extern arm_matrix_instance_f32 y;
extern arm_matrix_instance_f32 residue;


void pf_ekf_tmp_init(void);


extern arm_matrix_instance_f32 Fx_att;
extern arm_matrix_instance_f32 Hxbar_att;
extern arm_matrix_instance_f32 FP_att;
extern arm_matrix_instance_f32 FT_att;
extern arm_matrix_instance_f32 FPFT_att;
extern arm_matrix_instance_f32 Pbar_att;
extern arm_matrix_instance_f32 PbarHT_att;
extern arm_matrix_instance_f32 HT_att;
extern arm_matrix_instance_f32 HPbarHT_att;
extern arm_matrix_instance_f32 deno_att;
extern arm_matrix_instance_f32 denoinv_att;
extern arm_matrix_instance_f32 corr_att;
extern arm_matrix_instance_f32 K_att;
extern arm_matrix_instance_f32 KH_att;
extern arm_matrix_instance_f32 I_att;
extern arm_matrix_instance_f32 IKH_att;
extern arm_matrix_instance_f32 xbar_att;
extern arm_matrix_instance_f32 y_att;
extern arm_matrix_instance_f32 residue_att;

void att_ekf_tmp_init(void);
	
#endif
