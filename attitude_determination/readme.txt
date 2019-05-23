
/********** How to use this? **********/


/******************* Function Calls ********************/
1. call the functions in the following order

init_pf();
init_att();
pf_ekf_tmp_init();
att_ekf_tmp_init();

prefilter(&readings_pf, &x_pf, &P_pf);
igrf(gps);
att_filter(&readings_pf, &x_pf, &P_pf);

/****************************************************/


/******************** Explanation ***********************/

2. Explanation

init_pf()

	This function initializes the matrices required for PREFILTER.

init_att()
	
	This function initializes the matrices required for ATTITUDE FILTER.

pf_ekf_tmp_init()

	This function initializes the temporary matrices required for 	PREFILTER.

att_ekf_tmp_init()
	
	This function initializes the temporary matrices required for ATTITUDE 	FILTER.

prefilter()
	
	This function takes as input the readings from sensors, the states and 	covariance matrix P and provides as output the new states.

	readings : the 3 magnetometer readings : 3x1 matrix
	x : { {B} , {B_dot}, {B_dot_dot} }; : 9x1 matrix
	P : diag([10^4 10^4 10^4 10^6 10^6 10^6 10^6 10^6 10^6]); : 9x9 matrix

igrf()
	This function calculates the magnetic field from earth's reference 	based on gps data.

	gps : {latitude, longitude, altitude,{ {year, month, date}, hh,mm,ss} }

att_filter()
	
	readings : { {B} , {B_dot} }; : 6x1 matrix
	x : {q0, q1, q2, q3, wx, wy, wz }; : 7x1 matrix
	P: diag([1*10^-3 1*10^-3 1*10^-3 1*10^-3 1*10^-4 1*10^-4 1*10^-4]); : 7x7 matrix

/***************************************************************************************************/
