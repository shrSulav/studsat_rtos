#include "arm_math.h"
#include "math.h"
#include "op_triad.h"

#define TRIAD_VECTOR_SIZE 3

// FUNCTION PROTOTYPES begin **********************************************************************
void triad_vec(float32_t *ref_vec_1, float32_t *ref_vec_2, float32_t *body_vec_1, float32_t *body_vec_2);
void triad_mat(arm_matrix_instance_f32 *t1r,
				arm_matrix_instance_f32 *t2r,
				arm_matrix_instance_f32 *t3r,
				arm_matrix_instance_f32 *t1b,
				arm_matrix_instance_f32 *t2b,
				arm_matrix_instance_f32 *t3b,
				arm_matrix_instance_f32 *att);

void optimized_triad(arm_matrix_instance_f32 *att);

void cross_product(const float32_t *, const float32_t *, float32_t *, uint8_t);
// FUNCTION PROTOTYPES END ************************************************************

// GLOBAL VARIABLES DECLARATION ***************************************************
float32_t r1[TRIAD_VECTOR_SIZE],r2[TRIAD_VECTOR_SIZE];
float32_t b1[TRIAD_VECTOR_SIZE],b2[TRIAD_VECTOR_SIZE];
float32_t s1,s2;

float32_t t1b[TRIAD_VECTOR_SIZE];
float32_t t2b[TRIAD_VECTOR_SIZE];
float32_t t3b[TRIAD_VECTOR_SIZE];

float32_t t1r[TRIAD_VECTOR_SIZE];
float32_t t2r[TRIAD_VECTOR_SIZE];
float32_t t3r[TRIAD_VECTOR_SIZE];

float32_t v1_norm;
float32_t v1_norm_inv;
float32_t t1b_v2_cross[TRIAD_VECTOR_SIZE];
float32_t t1b_v2_cross_norm;
float32_t t1b_v2_cross_norm_inv;
float32_t t1b_t2b_cross[TRIAD_VECTOR_SIZE];
float32_t t1b_t2b_cross_norm;
float32_t t1b_t2b_cross_norm_inv;

float32_t r1_norm;
float32_t r1_norm_inv;
float32_t t1r_r2_cross[TRIAD_VECTOR_SIZE];
float32_t t1r_r2_cross_norm;
float32_t t1r_r2_cross_norm_inv;
float32_t t1r_t2r_cross[TRIAD_VECTOR_SIZE];
float32_t t1r_t2r_cross_norm;
float32_t t1r_t2r_cross_norm_inv;

float32_t t1[9], t2[9],t3[9], t1_t2[9];
float32_t attitude1[9], attitude2[9],attitude[9],attitude_dash[9];
float32_t A1_scaled[9], A2_scaled[9];
float32_t sigma1, sigma2;

arm_matrix_instance_f32 ref_vec_1_mat, ref_vec_2_mat, body_vec_1_mat, body_vec_2_mat;
arm_matrix_instance_f32 t1b_mat,t2b_mat,t1r_mat,t2r_mat, t3b_mat, t3r_mat; //3x1
arm_matrix_instance_f32 t1_mat,t2_mat,t3_mat, t1_t2_mat; //3x3
arm_matrix_instance_f32 A1_scaled_mat, A2_scaled_mat; //3x3
arm_matrix_instance_f32 A1_mat,A2_mat,A_mat; //3x3
arm_matrix_instance_f32 A_dash_mat; //3x3

//GLOBAL VARIABLES DECLARATION END **************************************************************

void triad_vec(float32_t *ref_vec_1, float32_t *ref_vec_2, 
								float32_t *body_vec_1, float32_t *body_vec_2)
{

//t1b=v1./norm(v1);
arm_dot_prod_f32(body_vec_1,body_vec_1,TRIAD_VECTOR_SIZE,&v1_norm);
v1_norm = sqrtf(v1_norm);
v1_norm_inv = 1/v1_norm;
arm_scale_f32(body_vec_1,v1_norm_inv,t1b,TRIAD_VECTOR_SIZE);

//t2b=cross(t1b,v2)./norm(cross(t1b,v2));
cross_product(t1b, body_vec_2,t1b_v2_cross,TRIAD_VECTOR_SIZE);
arm_dot_prod_f32(t1b_v2_cross,t1b_v2_cross,TRIAD_VECTOR_SIZE,&t1b_v2_cross_norm);
t1b_v2_cross_norm = sqrtf(t1b_v2_cross_norm);
t1b_v2_cross_norm_inv = 1/t1b_v2_cross_norm;
arm_scale_f32(t1b_v2_cross,t1b_v2_cross_norm_inv,t2b,TRIAD_VECTOR_SIZE);

//t3b=cross(t1b,t2b)./norm(cross(t1b,t2b));
cross_product(t1b, t2b, t1b_t2b_cross,TRIAD_VECTOR_SIZE);
arm_dot_prod_f32(t1b_t2b_cross,t1b_t2b_cross,TRIAD_VECTOR_SIZE,&t1b_t2b_cross_norm);
t1b_t2b_cross_norm = sqrtf(t1b_t2b_cross_norm);
t1b_t2b_cross_norm_inv = 1/t1b_t2b_cross_norm;
arm_scale_f32(t1b_t2b_cross,t1b_t2b_cross_norm_inv,t3b,TRIAD_VECTOR_SIZE);

//reference triad .**************
//t1r=r1./norm(r1);
arm_dot_prod_f32(ref_vec_1,ref_vec_1,TRIAD_VECTOR_SIZE,&r1_norm);
r1_norm = sqrtf(r1_norm);
r1_norm_inv = 1/r1_norm;
arm_scale_f32(ref_vec_1,r1_norm_inv,t1r,TRIAD_VECTOR_SIZE);

//t2b=cross(t1r,r2)./norm(cross(t1r,r2));
cross_product(t1r, ref_vec_2,t1r_r2_cross,(uint8_t)TRIAD_VECTOR_SIZE);
arm_dot_prod_f32(t1r_r2_cross,t1r_r2_cross,TRIAD_VECTOR_SIZE,&t1r_r2_cross_norm);
t1r_r2_cross_norm = sqrtf(t1r_r2_cross_norm);
t1r_r2_cross_norm_inv = 1/t1r_r2_cross_norm;
arm_scale_f32(t1r_r2_cross,t1r_r2_cross_norm_inv,t2r,TRIAD_VECTOR_SIZE);

//t3r=cross(t1r,t2r)./norm(cross(t1r,t2r));
cross_product(t1r, t2r, t1r_t2r_cross,TRIAD_VECTOR_SIZE);
arm_dot_prod_f32(t1r_t2r_cross,t1r_t2r_cross,TRIAD_VECTOR_SIZE,&t1r_t2r_cross_norm);
t1r_t2r_cross_norm = sqrtf(t1r_t2r_cross_norm);
t1r_t2r_cross_norm_inv = 1/t1r_t2r_cross_norm;
arm_scale_f32(t1r_t2r_cross,t1r_t2r_cross_norm_inv,t3r,TRIAD_VECTOR_SIZE);

}

void triad_mat(arm_matrix_instance_f32 *t1r,
							arm_matrix_instance_f32 *t2r,
							arm_matrix_instance_f32 *t3r,
							arm_matrix_instance_f32 *t1b,
							arm_matrix_instance_f32 *t2b,
							arm_matrix_instance_f32 *t3b,
							arm_matrix_instance_f32 *att)

{
	arm_mat_mult_f32(t1b, t1r, &t1_mat);
	arm_mat_mult_f32(t2b, t2r, &t2_mat);
	arm_mat_mult_f32(t3b, t3r, &t3_mat);
	arm_mat_add_f32(&t1_mat,&t2_mat,&t1_t2_mat);
	arm_mat_add_f32(&t1_t2_mat,&t3_mat,att); 

}


void optimized_triad(arm_matrix_instance_f32 *att)
{
	float32_t sigma1_sq, sigma2_sq;
	float32_t sc1, sc2;
	
	triad_vec(r1,r2,b1,b2);
	triad_mat(&t1r_mat,&t2r_mat, &t3r_mat, &t1b_mat, &t2b_mat, &t3b_mat,&A1_mat);
	triad_vec(r2,r1,b2,b1);
	triad_mat(&t1r_mat,&t2r_mat, &t3r_mat, &t1b_mat, &t2b_mat, &t3b_mat,&A2_mat);
	
	sigma1_sq = powf(sigma1,2);
	sigma2_sq = powf(sigma2,2);

	sc1 = sigma2_sq/(sigma1_sq + sigma2_sq);
	sc2 = sigma1_sq/(sigma1_sq + sigma2_sq);

	arm_mat_scale_f32(&A1_mat,sc1,&A1_scaled_mat);
	arm_mat_scale_f32(&A2_mat,sc2,&A2_scaled_mat);
	arm_mat_add_f32(&A1_scaled_mat,&A2_scaled_mat, &A_dash_mat);
	arm_mat_scale_f32(&A_dash_mat,1.0, att);
	
	arm_mat_inverse_f32(&A_dash_mat, &A1_mat);
	arm_mat_trans_f32(&A1_mat, &A2_mat);
	arm_mat_add_f32(att,&A2_mat,&A1_scaled_mat);
	arm_mat_scale_f32(&A1_scaled_mat,0.5, att);
}

void get_attitude(void)
{
	//read from magnetometer
	//read from sunsensor
	//get igrf magnetic field values
	//get vector from sun vector model
	optimized_triad(&A_mat);
}

void optimized_triad_init(void)
{
	uint8_t srcRows, srcColumns;

	srcRows = 3; 
	srcColumns = 1; 
	
	arm_mat_init_f32(&ref_vec_1_mat, srcRows, srcColumns, (float32_t *)r1); 
	arm_mat_init_f32(&ref_vec_2_mat, srcColumns, srcRows, (float32_t *)r2); 
	arm_mat_init_f32(&body_vec_1_mat, srcRows, srcColumns, (float32_t *)b1); 
	arm_mat_init_f32(&body_vec_2_mat, srcColumns, srcRows, (float32_t *)b2); 
	
	arm_mat_init_f32(&t1b_mat, srcRows, srcColumns, (float32_t *)t1b); 
	arm_mat_init_f32(&t1r_mat, srcColumns, srcRows, (float32_t *)t1r); 
	arm_mat_init_f32(&t2b_mat, srcRows, srcColumns, (float32_t *)t2b); 
	arm_mat_init_f32(&t2r_mat, srcColumns, srcRows, (float32_t *)t2r); 
	arm_mat_init_f32(&t3b_mat, srcRows, srcColumns, (float32_t *)t3b); 
	arm_mat_init_f32(&t3r_mat, srcColumns, srcRows, (float32_t *)t3r);

	srcRows = 3; 
	srcColumns = 3; 
	arm_mat_init_f32(&t1_mat, srcRows, srcColumns, (float32_t *)t1); 
	arm_mat_init_f32(&t2_mat, srcRows, srcColumns, (float32_t *)t2);
	arm_mat_init_f32(&t3_mat, srcRows, srcColumns, (float32_t *)t3);
	arm_mat_init_f32(&t1_t2_mat, srcRows, srcColumns, (float32_t *)t1_t2);
	arm_mat_init_f32(&A1_mat, srcRows, srcColumns, (float32_t *)attitude1);
	arm_mat_init_f32(&A2_mat, srcRows, srcColumns, (float32_t *)attitude2);
	arm_mat_init_f32(&A1_scaled_mat, srcRows, srcColumns, (float32_t *)A1_scaled);
	arm_mat_init_f32(&A2_scaled_mat, srcRows, srcColumns, (float32_t *)A2_scaled);
	arm_mat_init_f32(&A_mat, srcRows, srcColumns, (float32_t *)attitude);
	arm_mat_init_f32((arm_matrix_instance_f32 *)&A_dash_mat, srcRows, srcColumns, (float32_t *)attitude_dash);

}

void vector_update( float32_t magnm_ref[3], 
										float32_t sunvector_ref[3], 
										float32_t magnm_body[3], 
										float32_t sunvector_body[3] )
{
	r1[0] = magnm_ref[0];
	r1[1] = magnm_ref[1];
	r1[2] = magnm_ref[2];
	
	r2[0] = sunvector_ref[0];
	r2[1] = sunvector_ref[1];
	r2[2] = sunvector_ref[2];

	b1[0] = magnm_body[0];
	b1[1] = magnm_body[1];
	b1[2] = magnm_body[2];
	
	b2[0] = sunvector_body[0];
	b2[1] = sunvector_body[1];
	b2[2] = sunvector_body[2];
}

//void vector_update( float32_t magnm_ref[3], 
//										float32_t sunvector_ref[3], 
//										float32_t magnm_body[3], 
//										float32_t sunvector_body[3] )
//{
//	r1[0] = 1.0;
//	r1[1] = 2.0;
//	r1[2] = 3.0;
//	r2[0] = 4.0;
//	r2[1] = 5.0;
//	r2[2] = 6.0;
//	
//	b1[0] = 7.0;
//	b1[1] = 8.0;
//	b1[2] = 9.0;
//	b2[0] = 1.0;
//	b2[1] = 4.0;
//	b2[2] = 7.0;
//	
//	sigma1 = 0.5;
//	sigma2 = 0.3;
//}

void cross_product(const float32_t *a, const float32_t *b, float32_t *c,uint8_t vector_size)
{
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
}

