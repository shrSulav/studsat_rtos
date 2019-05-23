
/* **************************************

0) Initialize EKF

1) Get magnetometer readings
2) Make a matrix of it to give it to prefilter
3) Call prefilter( ... );

4) Get latitude, longitude , altitude and date from GPS
5) Make a structure of it to give it to igrf code
6) Call igrf( ... );

7) Take magnetometer readings and its derivative from prefilter
8) Make a matrix of it to give it to attitude filter
9) Take magnetometer readings and its derivative from igrf code
10) Make a matrix of it to give it to attitude filter
11) Call att_filter( ... ); 

Note:
	gps and Bb structures are global structures


***************************************** */


#include "final_func.h"

void initialize_ekf( void )
{
	init_pf();
	init_att();
	pf_ekf_tmp_init();
	att_ekf_tmp_init();
	b_grad_init();
}

void determine_attitude( void )
{
	// Get magnetometer values
	magnetometer(); // updates Bbx, Bby and Bbz

	readings_pf_f32[0] = Bbx ;
	readings_pf_f32[1] = Bby ;
	readings_pf_f32[2] = Bbz ;

	prefilter(&readings_pf,&x_pf,&P_pf);

	gps = get_gps_values(); // gps is a structure with lat, long, alt and date
	igrf(gps, Bi_f32);

	readings_att_f32[0] = x_pf_f32[0] ;
	readings_att_f32[1] = x_pf_f32[1] ;
	readings_att_f32[2] = x_pf_f32[2] ;
	readings_att_f32[3] = x_pf_f32[3] ;
	readings_att_f32[4] = x_pf_f32[4] ;
	readings_att_f32[5] = x_pf_f32[5] ;

	igrf_derivative();

	att_filter(&readings_att,&x_att,&P_att);


}
/*
% estimation of initial derivative of IGRF magnetic field vector
    igrfmag=[25185;25184;-250];
    deltaB=[igrfmag(1,1) igrfmag(1,1) igrfmag(1,1);
            igrfmag(2,1) igrfmag(2,1) igrfmag(2,1);
            igrfmag(3,1) igrfmag(3,1) igrfmag(3,1)];
    V=[7.3;7.3;7.3];
    DerivatB1=deltaB*V;
    DerivatB=DerivatB1+igrfmag;
    z=[igrfmag(1,1);
       igrfmag(2,1);
       igrfmag(3,1);
       DerivatB(1,1);
       DerivatB(2,1);
       DerivatB(3,1)];
*/

/*
void mag_derivative ( void )
{

}
*/

void igrf_derivative ( void )
{
	/*
	deltaBi_f32[0] = deltaBi_f32[1] = deltaBi_f32[2] = Bi_f32[0];
	deltaBi_f32[3] = deltaBi_f32[4] = deltaBi_f32[5] = Bi_f32[1];
	deltaBi_f32[6] = deltaBi_f32[7] = deltaBi_f32[8] = Bi_f32[2];
	*/
	orb_to_eci(oev, sat_pos_f32, sat_vel_f32);
	b_grad();
	arm_mat_mult(&deltaBi, &sat_vel, &Bi_dot_tmp);
	arm_mat_add(&Bi_dot_tmp, &Bi_delT, &Bi_dot);


	igrfmag[0] = Bi_f32[0];
	igrfmag[1] = Bi_f32[1];
	igrfmag[2] = Bi_f32[2];
	igrfmag[3] = Bi_dot_f32[0];
	igrfmag[4] = Bi_dot_f32[1];
	igrfmag[5] = Bi_dot_f32[2];

}
