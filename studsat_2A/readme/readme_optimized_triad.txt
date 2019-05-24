/* **********************************************************

HOW TO USE THIS
1. initialize the variables by calling the function
	optimized_triad_init();

2. update the values
	float32_t r1[3], r2[3], b1[3], b2[3];
	float32_t sigma1, sigma2;
	
	r1, r2 : reference vectors
	b1, b2 : body vectors

	b1 : obtained from magnetometer readings
	b2 : obtained from sun sensor
	r1 : obtained from IGRF code
	r2 : obtained from sun vector code

3. call the function
	optimized_triad(arm_matrix_instance* att);
	
	In this case att : A_mat

	i.e. optimized_triad(&A_mat);

NOTE:
The variables are defined in op_triad.c.

extern float32_t r1[3],r2[3],b1[3],b2[3];
extern float32_t sigma1, sigma2;
extern arm_matrix_instance_f32 A_mat;

So for accessing the use of extern keyword is necessary.

************************************************************** */