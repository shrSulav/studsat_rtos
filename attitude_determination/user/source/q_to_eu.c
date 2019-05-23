
//Convert quaternions to Euler angles
/*
		Angles(1,1)=atan2(2*(q2*q3)-2*q0*q1,2*q0^2+2*q3^2-1)*180/pi;
    Angles(2,1)=-asind(2*q1*q3+2*q0*q2);
    Angles(3,1)=atan2(2*q1*q2-2*q0*q3,2*q0^2+2*q1^2-1)*180/pi;
*/

#include "q_to_eu.h"

void q_to_eu(void)
{
	float32_t q0, q1, q2, q3;
	float32_t y_val, x_val,val;
	q0 = x_f32[0];
	q1 = x_f32[1];
	q2 = x_f32[2];
	q3 = x_f32[3];

	y_val = (2*(q2*q3)-2*q0*q1);
	x_val = (2 * powf(q0,2) + 2*powf(q3,2)-1);
	//val = y_val / x_val;
	theta_x = atan2f( y_val, x_val );
	theta_x = theta_x * 180 / PI;		// find theta_x here

	//y_val = (2*(q2*q3)-2*q0*q1);
	//x_val = (2*q0^2+2*q3^2-1);
	val = 2*q1*q3 + 2*q0*q2;
	theta_y = asinf( val );
	theta_y = theta_y * 180 / PI;		// find theta_y here

	y_val = (2*q1*q2-2*q0*q3);
	x_val = 2*powf(q0,2) + 2 * powf(q1,2) -1;
	//val = y_val / x_val;
	theta_z = atan2f( y_val, x_val );
	theta_z = theta_z * 180 / PI;		// find theta_z here
}
