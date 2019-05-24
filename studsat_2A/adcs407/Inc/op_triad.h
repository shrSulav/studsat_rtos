/*

HOW TO USE THIS
1. initialize the variables by calling the function
	optimized_triad_init();

2. update the values
	float32_t r1[3], r2[3], b1[3], b2[3];
	float32_t sigma1, sigma2;
	
	r1, r2 : reference vectors
	b1, b2 : body vectors

3. call the function
	optimized_triad(arm_matrix_instance* att);
	
	In this case att : A_mat

	i.e. optimized_triad(&A_mat);
*/

#ifndef OP_TRIAD_H
	#define OP_TRIAD_H

#include "arm_math.h"

void get_attitude(void);

void vector_update( float32_t magnm_ref[3], 
										float32_t sunvector_ref[3], 
										float32_t magnm_body[3], 
										float32_t sunvector_body[3] );

void optimized_triad_init(void);


#endif
