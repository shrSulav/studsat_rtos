#include "filters.h"
#include "ekf_tmp.h"
#include "ekf_init.h"
#include "arm_math.h"
#include "ekf_var.h"

/* 
***************************

//predict

xbar = F*x+w
y = H*xbar+v
Pbar=(F*P)+(P*F')+Q

//update
K=Pbar*H'/(H*Pbar*H' + R)
resid = mag - y
xup = xbar + K*resid
Pup = (eye(size(K,1))-K*H)*Pbar
xOut = xup

********************************
*/

void prefilter(
			arm_matrix_instance_f32* readings,
			arm_matrix_instance_f32* x,
			arm_matrix_instance_f32* P
			)
{
	//xbar = F*x + w
	arm_mat_mult_f32(&F_pf,x,&Fx);
	arm_mat_add_f32(&Fx, &w_pf, &xbar);
	
	//Pbar = (F*P*F') + Q
	arm_mat_mult_f32(&F_pf,P, &FP);
	arm_mat_trans_f32(&F_pf, &FT);
	arm_mat_mult_f32(&FP,&FT,&FPFT);
	arm_mat_add_f32(&FPFT, &Q_pf, &Pbar);
	
	//y = H*xbar + v
	arm_mat_mult_f32(&H_pf,&xbar,&Hxbar);
	arm_mat_add_f32(&Hxbar, &v_pf, &y);
	
	//K = Pbar*H' / (H*Pbar*H' + R)
	arm_mat_trans_f32(&H_pf,&HT);
	arm_mat_mult_f32(&Pbar,&HT,&PbarHT);
	arm_mat_mult_f32(&H_pf, &PbarHT, &HPbarHT);
	arm_mat_add_f32(&HPbarHT, &R_pf, &deno);
	arm_mat_inverse_f32(&deno, &denoinv);
	arm_mat_mult_f32(&PbarHT, &denoinv, &K);
	
	//x_new = xbar + K*resid
	arm_mat_sub_f32(readings, &y, &residue);
	arm_mat_mult_f32(&K, &residue, &corr);
	arm_mat_add_f32(&xbar, &corr, x);
	
	//Pup = (eye(size(K,1))-K*H)*Pbar
	arm_mat_mult_f32(&K,&H_pf, &KH);
	arm_mat_sub_f32(&I,&KH,&IKH);
	arm_mat_mult_f32(&IKH,&Pbar,P);
}


void att_filter(
			arm_matrix_instance_f32* readings,
			arm_matrix_instance_f32* x,
			arm_matrix_instance_f32* P
			)
{	
	float32_t* ptr_x = x->pData;
	
	float32_t ex,ey,ez;
	
	float32_t* ptr_xbar = xbar_att.pData;
	
	q[0] = *ptr_x;
	q[1] = *(ptr_x+1);
	q[2] = *(ptr_x+2);
	q[3] = *(ptr_x+3);
	
	qc[0] = q[0];
	qc[1] = -q[1];
	qc[2] = -q[2];
	qc[3] = -q[3];
	
	w[0] = *(ptr_x + 4);
	w[1] = *(ptr_x + 5);
	w[2] = *(ptr_x + 6);
	/*
	F_att_f32[49]= { 0, -0.5*w[1], -0.5*w[2], -0.5*w[3], -0.5*q[2], -0.5*q[3], -0.5*q[4],
		0.5*w[1], 0 0.5*w[3], -0.5*w[2], 0.5*q[1], -0.5*q[4], 0.5*q[3],
   0.5*w[2], -0.5*w[3], 0, 0.5*w[1], 0.5*q[4], -0.5*q[1], -0.5*q[2],
   0.5*w[3], 0.5*w[2], -0.5*w[1], 0, -0.5*q[3], 0.5*q[2], 0.5*q[1],
   0, 0, 0, 0, 0, Sx*w[3], Sx*w[2],
   0, 0, 0, 0, Sy*w[3], 0, Sy*w[1],
	0, 0, 0, 0, Sz*w[2], Sz*w[1], 0};
	*/
	  F_att_f32[0] = 0.0F;
  F_att_f32[1] = -0.5F * w[0];
  F_att_f32[2] = -0.5F * w[1];
  F_att_f32[3] = -0.5F * w[2];
  F_att_f32[4] = -0.5F * q[1];
  F_att_f32[5] = -0.5F * q[2];
  F_att_f32[6] = -0.5F * q[3];
  F_att_f32[7] = 0.5F * w[0];
  F_att_f32[8] = 0.0F;
  F_att_f32[9] = 0.5F * w[2];
  F_att_f32[10] = -0.5F * w[1];
  F_att_f32[11] = 0.5F * q[0];
  F_att_f32[12] = -0.5F * q[3];
  F_att_f32[13] = 0.5F * q[2];
  F_att_f32[14] = 0.5F * w[1];
  F_att_f32[15] = -0.5F * w[2];
  F_att_f32[16] = 0.0F;
  F_att_f32[17] = 0.5F * w[0];
  F_att_f32[18] = 0.5F * q[3];
  F_att_f32[19] = -0.5F * q[0];
  F_att_f32[20] = -0.5F * q[1];
  F_att_f32[21] = 0.5F * w[2];
  F_att_f32[22] = 0.5F * w[1];
  F_att_f32[23] = -0.5F * w[0];
  F_att_f32[24] = 0.0F;
  F_att_f32[25] = -0.5F * q[2];
  F_att_f32[26] = 0.5F * q[1];
  F_att_f32[27] = 0.5F * q[0];
  F_att_f32[28] = 0.0F;
  F_att_f32[29] = 0.0F;
  F_att_f32[30] = 0.0F;
  F_att_f32[31] = 0.0F;
  F_att_f32[32] = 0.0F;
  F_att_f32[33] = Sx * w[2];
  F_att_f32[34] = Sx * w[1];
  F_att_f32[35] = 0.0F;
  F_att_f32[36] = 0.0F;
  F_att_f32[37] = 0.0F;
  F_att_f32[38] = 0.0F;
  F_att_f32[39] = Sy * w[2];
  F_att_f32[40] = 0.0F;
  F_att_f32[41] = Sy * w[0];
  F_att_f32[42] = 0.0F;
  F_att_f32[43] = 0.0F;
  F_att_f32[44] = 0.0F;
  F_att_f32[45] = 0.0F;
  F_att_f32[46] = Sz * w[1];
  F_att_f32[47] = Sz * w[0];
  F_att_f32[48] = 0.0F;
  
	//xbar = F*x + w
	arm_mat_mult_f32(&F_att,x,&Fx_att);
	arm_mat_add_f32(&Fx_att, &w_att, &xbar_att);
	
	ex = (*(ptr_xbar+1))*qc[1]*igrfmag[0]+ (*(ptr_xbar+2))*qc[1]*igrfmag[1]+ (*(ptr_xbar+3))*qc[1]*igrfmag[2];
	ey = (*(ptr_xbar+1))*qc[2]*igrfmag[0]+ (*(ptr_xbar+2))*qc[2]*igrfmag[1]+ (*(ptr_xbar+3))*qc[2]*igrfmag[2];
	ez = (*(ptr_xbar+1))*qc[3]*igrfmag[0]+ (*(ptr_xbar+2))*qc[3]*igrfmag[1]+ (*(ptr_xbar+3))*qc[3]*igrfmag[2];
	
	H_att_f32[0] = 0.0F;
  H_att_f32[1] = qc[1] * igrfmag[0];
  H_att_f32[2] = qc[1] * igrfmag[1];
  H_att_f32[3] = qc[1] * igrfmag[2];
  H_att_f32[4] = 0.0F;
  H_att_f32[5] = 0.0F;
  H_att_f32[6] = 0.0F;
  H_att_f32[7] = 0.0F;
  H_att_f32[8] = qc[2] * igrfmag[0];
  H_att_f32[9] = qc[2] * igrfmag[1];
  H_att_f32[10] = qc[2] * igrfmag[2];
  H_att_f32[11] = 0.0F;
  H_att_f32[12] = 0.0F;
  H_att_f32[13] = 0.0F;
  H_att_f32[14] = 0.0F;
  H_att_f32[15] = qc[3] * igrfmag[0];
  H_att_f32[16] = qc[3] * igrfmag[1];
  H_att_f32[17] = qc[3] * igrfmag[2];
  H_att_f32[18] = 0.0F;
  H_att_f32[19] = 0.0F;
  H_att_f32[20] = 0.0F;
  H_att_f32[21] = 0.0F;
  H_att_f32[22] = qc[1] * igrfmag[3];
  H_att_f32[23] = qc[1] * igrfmag[4];
  H_att_f32[24] = qc[1] * igrfmag[5];
  H_att_f32[25] = ex;
  H_att_f32[26] = ex;
  H_att_f32[27] = ex;
  H_att_f32[28] = 0.0F;
  H_att_f32[29] = qc[2] * igrfmag[3];
  H_att_f32[30] = qc[2] * igrfmag[4];
  H_att_f32[31] = qc[2] * igrfmag[5];
  H_att_f32[32] = ey;
  H_att_f32[33] = ey;
  H_att_f32[34] = ey;
  H_att_f32[35] = 0.0F;
  H_att_f32[36] = qc[3] * igrfmag[3];
  H_att_f32[37] = qc[3] * igrfmag[4];
  H_att_f32[38] = qc[3] * igrfmag[5];
  H_att_f32[39] = ez;
  H_att_f32[40] = ez;
  H_att_f32[41] = ez;
	
	//Pbar = (F*P*F') + Q
	arm_mat_mult_f32(&F_att,P, &FP_att);
	arm_mat_trans_f32(&F_att, &FT_att);
	arm_mat_mult_f32(&FP_att,&FT_att,&FPFT_att);
	arm_mat_add_f32(&FPFT_att, &Q_att, &Pbar_att);
	
	//y = H*xbar + v
	arm_mat_mult_f32(&H_att,&xbar_att,&Hxbar_att);
	arm_mat_add_f32(&Hxbar_att, &v_att, &y_att);
	
	//K = Pbar*H' / (H*Pbar*H' + R)
	arm_mat_trans_f32(&H_att,&HT_att);
	arm_mat_mult_f32(&Pbar_att,&HT_att,&PbarHT_att);
	arm_mat_mult_f32(&H_att, &PbarHT_att, &HPbarHT_att);
	arm_mat_add_f32(&HPbarHT_att, &R_att, &deno_att);
	arm_mat_inverse_f32(&deno_att, &denoinv_att);
	arm_mat_mult_f32(&PbarHT_att, &denoinv_att, &K_att);
	
	//x_new = xbar + K*resid
	arm_mat_sub_f32(readings, &y_att, &residue_att);
	arm_mat_mult_f32(&K_att, &residue_att, &corr_att);
	arm_mat_add_f32(&xbar_att, &corr_att, x);
	
	//Pup = (eye(size(K,1))-K*H)*Pbar
	arm_mat_mult_f32(&K_att,&H_att, &KH_att);
	arm_mat_sub_f32(&I_att,&KH_att,&IKH_att);
	arm_mat_mult_f32(&IKH_att,&Pbar_att,P);
}
