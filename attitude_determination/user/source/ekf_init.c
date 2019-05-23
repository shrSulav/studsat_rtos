#include "arm_math.h"
#include "ekf_var.h"


//prefilter matrices
arm_matrix_instance_f32 F_pf; //9x9
arm_matrix_instance_f32 H_pf; //3x9
arm_matrix_instance_f32 Q_pf; //9x9
arm_matrix_instance_f32 R_pf; //3x3
arm_matrix_instance_f32 v_pf; //3x1
arm_matrix_instance_f32 w_pf; //9x1
arm_matrix_instance_f32 x_pf; //9x1
arm_matrix_instance_f32 readings_pf; //3x1
arm_matrix_instance_f32 P_pf; //9x9


//att_filter matrices
arm_matrix_instance_f32 F_att; //7x7
arm_matrix_instance_f32 H_att; //6x7
arm_matrix_instance_f32 Q_att; //7x7
arm_matrix_instance_f32 R_att; //6x6
arm_matrix_instance_f32 v_att; //6x1
arm_matrix_instance_f32 w_att; //7x1
arm_matrix_instance_f32 x_att; //7x1
arm_matrix_instance_f32 readings_att; //6x1
arm_matrix_instance_f32 P_att; //7x7	

//IGRF matrices
arm_matrix_instance_f32 Bi;
arm_matrix_instance_f32 Bi_dot;
arm_matrix_instance_f32 Bi_dot_tmp;
arm_matrix_instance_f32 sat_vel; //3x1
arm_matrix_instance_f32 deltaBi; //3x3
arm_matrix_instance_f32 Bi_delT; //3x1

void init_pf(void)
{
	uint32_t srcRows, srcColumns;
	arm_matrix_instance_f32 Rtmp_pf, Ptmp_pf;
	
	srcRows = 9; 
    srcColumns = 9; 
	arm_mat_init_f32(&F_pf, srcRows, srcColumns, (float32_t *)F_pf_f32);
	
	srcRows = 3; 
    srcColumns = 9; 
	arm_mat_init_f32(&H_pf, srcRows, srcColumns, (float32_t *)H_pf_f32);
	
	srcRows = 9; 
    srcColumns = 9; 
	arm_mat_init_f32(&Q_pf, srcRows, srcColumns, (float32_t *)Q_pf_f32);
	
	srcRows = 3; 
    srcColumns = 3; 
	arm_mat_init_f32(&Rtmp_pf, srcRows, srcColumns, (float32_t *)R_pf_f32);
	arm_mat_init_f32(&R_pf, srcRows, srcColumns, (float32_t *)R_pf_f32);
	arm_mat_scale_f32(&Rtmp_pf, powf(10,-9), &R_pf);
	
	srcRows = 9; 
    srcColumns = 1; 
	arm_mat_init_f32(&v_pf, srcRows, srcColumns, (float32_t *)v_pf_f32);
	
	srcRows = 9; 
    srcColumns = 1; 
	arm_mat_init_f32(&w_pf, srcRows, srcColumns, (float32_t *)w_pf_f32);

	srcRows = 9; 
    srcColumns = 1; 
	arm_mat_init_f32(&x_pf, srcRows, srcColumns, x_pf_f32);

	srcRows = 3; 
    srcColumns = 1; 
	arm_mat_init_f32(&readings_pf, srcRows, srcColumns, readings_pf_f32);

	srcRows = 9; 
    srcColumns = 9; 
	arm_mat_init_f32(&P_pf, srcRows, srcColumns, P_pf_f32);
	arm_mat_init_f32(&Ptmp_pf, srcRows, srcColumns, P_pf_f32);
	arm_mat_scale_f32(&Ptmp_pf,powf(10,4),&P_pf);

}

void init_att(void)
{
	uint32_t srcRows, srcColumns;
	arm_matrix_instance_f32 Qtmp_att, Ptmp_att;
	
	srcRows = 7; 
    srcColumns = 7; 
	arm_mat_init_f32(&F_att, srcRows, srcColumns, (float32_t *)F_att_f32);
	
	srcRows = 6; 
    srcColumns = 7; 
	arm_mat_init_f32(&H_att, srcRows, srcColumns, (float32_t *)H_att_f32);
	
	srcRows = 7; 
    srcColumns = 7;
	arm_mat_init_f32(&Q_att, srcRows, srcColumns, (float32_t *)Q_att_f32);
	arm_mat_init_f32(&Qtmp_att, srcRows, srcColumns, (float32_t *)Q_att_f32);
	arm_mat_scale_f32(&Qtmp_att, powf(10,-5), &Q_att);
	
	srcRows = 6; 
    srcColumns = 6; 
	arm_mat_init_f32(&R_att, srcRows, srcColumns, (float32_t *)R_att_f32);
	
	srcRows = 6; 
    srcColumns = 1; 
	arm_mat_init_f32(&v_att, srcRows, srcColumns, (float32_t *)v_att_f32);
	
	srcRows = 7; 
    srcColumns = 1; 
	arm_mat_init_f32(&w_att, srcRows, srcColumns, (float32_t *)w_att_f32);

	srcRows = 7; 
    srcColumns = 1; 
	arm_mat_init_f32(&x_att, srcRows, srcColumns, x_att_f32);

	srcRows = 6; 
    srcColumns = 1; 
	arm_mat_init_f32(&readings_att, srcRows, srcColumns, readings_att_f32);

	srcRows = 7; 
    srcColumns = 7; 
	arm_mat_init_f32(&P_att, srcRows, srcColumns, P_att_f32);
	arm_mat_init_f32(&Ptmp_att, srcRows, srcColumns, P_att_f32);
	arm_mat_scale_f32(&Ptmp_att,powf(10,-4),&P_att);

}

void init_igrf(void)
{
	uint32_t srcRows, srcColumns;
	
	srcRows = 3; 
    srcColumns = 1;

    arm_mat_init_f32(&Bi, srcRows, srcColumns, Bi_f32);

	arm_mat_init_f32(&Bi_dot, srcRows, srcColumns, Bi_dot_f32);
	
	arm_mat_init_f32(&Bi_dot_tmp, srcRows, srcColumns, Bi_dot_tmp_f32);
	
	arm_mat_init_f32(&sat_vel, srcRows, srcColumns, sat_vel_f32);

	arm_mat_init_f32(&Bi_delT, srcRows, srcColumns, Bi_delT_f32);

	srcRows = 3;
	srcColumns = 3;
	arm_mat_init_f32( &deltaBi, srcRows, srcColumns, deltaBi_f32);
	
}
