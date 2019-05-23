#include "arm_math.h"

//prefilter temporary variables
float32_t Fx_f32[9]; //9x1
float32_t Hxbar_f32[3]; //3x1
float32_t FP_f32[81]; //9x9
float32_t FT_f32[81]; //9x9
float32_t FPFT_f32[81]; //9x9
float32_t HT_f32[27]; //9x3
float32_t Pbar_f32[81]; //9x9
float32_t PbarHT_f32[27]; //9x3
float32_t HPbarHT_f32[9]; //3x3
float32_t deno_f32[9]; //3x3
float32_t denoinv_f32[9]; //3x3
float32_t corr_f32[9]; //9x1
float32_t K_f32[27]; //9x3
float32_t KH_f32[81]; //9x9
float32_t IKH_f32[81]; //9x9
	
float32_t xbar_f32[9]; //9x1
float32_t y_f32[3]; //3x1
float32_t residue_f32[3]; //3x1
	
float32_t I_f32[81] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
							 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0  }; //9x9 identity matrix

arm_matrix_instance_f32 Fx;
arm_matrix_instance_f32 Hxbar;
arm_matrix_instance_f32 FP;
arm_matrix_instance_f32 FT;
arm_matrix_instance_f32 FPFT;
arm_matrix_instance_f32 Pbar;
arm_matrix_instance_f32 PbarHT;
arm_matrix_instance_f32 HT;
arm_matrix_instance_f32 HPbarHT;
arm_matrix_instance_f32 deno;
arm_matrix_instance_f32 denoinv;
arm_matrix_instance_f32 corr;
arm_matrix_instance_f32 K;
arm_matrix_instance_f32 KH;
arm_matrix_instance_f32 I;
arm_matrix_instance_f32 IKH;
arm_matrix_instance_f32 xbar;
arm_matrix_instance_f32 y;
arm_matrix_instance_f32 residue;


//att_filter temporary variables

float32_t att_Fx_f32[7]; //7x1
float32_t att_Hxbar_f32[6]; //6x1
float32_t att_FP_f32[49]; //7x7
float32_t att_FT_f32[49]; //7x7
float32_t att_FPFT_f32[49]; //7x7
float32_t att_HT_f32[42]; //7x6
float32_t att_Pbar_f32[49]; //7x7
float32_t att_PbarHT_f32[42]; //7x6
float32_t att_HPbarHT_f32[36]; //6x6
float32_t att_deno_f32[36]; //6x6
float32_t att_denoinv_f32[36]; //6x6
float32_t att_corr_f32[7]; //7x1
float32_t att_K_f32[42];
float32_t att_KH_f32[49]; //7x7
float32_t att_IKH_f32[49]; //7x7

float32_t att_xbar_f32[7]; //7x1
float32_t att_y_f32[6]; //6x1
float32_t att_residue_f32[6]; //6x1

float32_t att_I_f32[49] = { 1,0,0,0,0,0,0,
														0,1,0,0,0,0,0,
														0,0,1,0,0,0,0,
														0,0,0,1,0,0,0,
														0,0,0,0,1,0,0,
														0,0,0,0,0,1,0,
														0,0,0,0,0,0,1}; //7x7 identity matrix

arm_matrix_instance_f32 Fx_att;
arm_matrix_instance_f32 Hxbar_att;
arm_matrix_instance_f32 FP_att;
arm_matrix_instance_f32 FT_att;
arm_matrix_instance_f32 FPFT_att;
arm_matrix_instance_f32 Pbar_att;
arm_matrix_instance_f32 PbarHT_att;
arm_matrix_instance_f32 HT_att;
arm_matrix_instance_f32 HPbarHT_att;
arm_matrix_instance_f32 deno_att;
arm_matrix_instance_f32 denoinv_att;
arm_matrix_instance_f32 corr_att;
arm_matrix_instance_f32 K_att;
arm_matrix_instance_f32 KH_att;
arm_matrix_instance_f32 I_att;
arm_matrix_instance_f32 IKH_att;
arm_matrix_instance_f32 xbar_att;
arm_matrix_instance_f32 y_att;
arm_matrix_instance_f32 residue_att;

void pf_ekf_tmp_init()
{			
uint32_t srcRows, srcColumns;		
srcRows = 9;
srcColumns = 1;
arm_mat_init_f32(&Fx, srcRows, srcColumns, Fx_f32);
	
srcRows = 3; 
srcColumns = 1; 
arm_mat_init_f32(&Hxbar, srcRows, srcColumns, Hxbar_f32);
	
srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&FP, srcRows, srcColumns, FP_f32);
	
srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&FT, srcRows, srcColumns, FT_f32);
	
srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&FPFT, srcRows, srcColumns, FPFT_f32);

srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&Pbar, srcRows, srcColumns, Pbar_f32);
	
srcRows = 9; 
srcColumns = 3; 
arm_mat_init_f32(&HT, srcRows, srcColumns, HT_f32);
	
srcRows = 9; 
srcColumns = 3; 
arm_mat_init_f32(&PbarHT, srcRows, srcColumns, PbarHT_f32);

srcRows = 3; 
srcColumns = 3; 
arm_mat_init_f32(&HPbarHT, srcRows, srcColumns, HPbarHT_f32);

srcRows = 3; 
srcColumns = 3; 
arm_mat_init_f32(&deno, srcRows, srcColumns, deno_f32);

srcRows = 3; 
srcColumns = 3; 
arm_mat_init_f32(&denoinv, srcRows, srcColumns, denoinv_f32);

srcRows = 9; 
srcColumns = 1; 
arm_mat_init_f32(&corr, srcRows, srcColumns, corr_f32);

srcRows = 9; 
srcColumns = 3; 
arm_mat_init_f32(&K, srcRows, srcColumns, K_f32);


srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&KH, srcRows, srcColumns, KH_f32);

srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&I, srcRows, srcColumns, I_f32);

srcRows = 9; 
srcColumns = 9; 
arm_mat_init_f32(&IKH, srcRows, srcColumns, IKH_f32);

srcRows = 9; 
srcColumns = 1; 
arm_mat_init_f32(&xbar, srcRows, srcColumns, xbar_f32);

srcRows = 3; 
srcColumns = 1; 
arm_mat_init_f32(&y, srcRows, srcColumns, y_f32);

srcRows = 3; 
srcColumns = 1; 
arm_mat_init_f32(&residue, srcRows, srcColumns, residue_f32);
}


void att_ekf_tmp_init()
{
uint32_t srcRows, srcColumns;
srcRows = 7;
srcColumns = 1;
arm_mat_init_f32(&Fx_att, srcRows, srcColumns, att_Fx_f32);

srcRows = 6;
srcColumns = 1;
arm_mat_init_f32(&Hxbar_att, srcRows, srcColumns, att_Hxbar_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&FP_att, srcRows, srcColumns, att_FP_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&FT_att, srcRows, srcColumns, att_FT_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&FPFT_att, srcRows, srcColumns, att_FPFT_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&Pbar_att, srcRows, srcColumns, att_Pbar_f32);

srcRows = 7;
srcColumns = 6;
arm_mat_init_f32(&HT_att, srcRows, srcColumns, att_HT_f32);

srcRows = 7;
srcColumns = 6;
arm_mat_init_f32(&PbarHT_att, srcRows, srcColumns, att_PbarHT_f32);

srcRows = 6;
srcColumns = 6;
arm_mat_init_f32(&HPbarHT_att, srcRows, srcColumns, att_HPbarHT_f32);

srcRows = 6;
srcColumns = 6;
arm_mat_init_f32(&deno_att, srcRows, srcColumns, att_deno_f32);

srcRows = 6;
srcColumns = 6;
arm_mat_init_f32(&denoinv_att, srcRows, srcColumns, att_denoinv_f32);

srcRows = 7;
srcColumns = 1;
arm_mat_init_f32(&corr_att, srcRows, srcColumns, att_corr_f32);

srcRows = 7; 
srcColumns = 6; 
arm_mat_init_f32(&K_att, srcRows, srcColumns, att_K_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&KH_att, srcRows, srcColumns, att_KH_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&I_att, srcRows, srcColumns, att_I_f32);

srcRows = 7;
srcColumns = 7;
arm_mat_init_f32(&IKH_att, srcRows, srcColumns, att_IKH_f32);

srcRows = 7;
srcColumns = 1;
arm_mat_init_f32(&xbar_att, srcRows, srcColumns, att_xbar_f32);

srcRows = 6;
srcColumns = 1;
arm_mat_init_f32(&y_att, srcRows, srcColumns, att_y_f32);

srcRows = 6;
srcColumns = 1;
arm_mat_init_f32(&residue_att, srcRows, srcColumns, att_residue_f32);
}
