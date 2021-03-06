
#include "igrf.h"
#include "gps.h"
#include "math.h"
#include "arm_math.h"
#include "stdio.h"
#include "igrf_data.h"
#include "e_time.h"
	
#define N 0
#define M 1
#define VALI 2
#define SVI 3

extern float32_t igrfh[IGRF_ROW][IGRF_COL];
extern float32_t igrfg[IGRF_ROW][IGRF_COL];

float32_t g[IGRF_ROW][IGRF_ROW + 1];
float32_t h[IGRF_ROW][IGRF_ROW + 1];

uint32_t days;

void igrf(gps_value gps, float32_t magnm_field[3])
{
	float32_t cos_theta, sin_theta, x, y, rho, r, phi,ra;
	float32_t P10,P11,f,cd,sd,oldcos,dP10,dP11,a,b;
	float32_t P2,dP2, P20,dP20,K;
	float32_t Bx, By, Bz;
	float32_t Bx1, By1, Bz1;
	float32_t Br, Bt, Bp;
	uint32_t N_val;
	uint32_t m,n,p;
	Date default_date = {2015,1,1};
	//Time default_time = {0,0,0};
	

	//Check for latitude singularity
	if((gps.latitude_f32 >= -0.000001f) && (gps.latitude_f32 <= 0.000001f))
		gps.latitude_f32 = 0.000001f;
	else if((gps.latitude_f32 >= 179.999999f) && (gps.latitude_f32 <= 180.000001f))
		gps.latitude_f32 = 179.999999f;

	cos_theta = cosf((90 - gps.latitude_f32)*PI/180);
	sin_theta = sinf((90 - gps.latitude_f32)*PI/180);
	
	ra = 6378.137; f = 1/298.257223563; b = ra*(1 - f);
    //rho = hypot(ra*sin_theta, b*cos_theta);
	
	x = powf(ra*sin_theta, 2);
	y = powf(b*cos_theta, 2);
	rho = sqrtf(x+y);
    r = sqrtf( powf(gps.altitude_f32,2) + 2*gps.altitude_f32*rho +(powf(ra,4)*powf(sin_theta,2) + powf(b,4)*powf(cos_theta,2)) / powf(rho,2) );
	cd = (gps.altitude_f32 + rho) / r;
	sd = (powf(ra,2) - powf(b,2)) / rho * cos_theta*sin_theta/r;
	oldcos = cos_theta;
    cos_theta = cos_theta*cd - sin_theta*sd;
		sin_theta = sin_theta*cd + oldcos*sd;

	phi = gps.longitude_f32*PI/180;

	a = 6371.2; //Reference radius used in IGRF

	/*
	program to calculate no. of days from gps datestring
	*/
	days = e_time(gps.date,default_date);
	//printf("days = %d\n",days);
	//days = 150;

	
	/*
	N=max(gn); //N = 104
g=zeros(N,N+1);
h=zeros(N,N+1);
for x=1:length(gn) //for(x=0; x<104; x++)
    g(gn(x),gm(x)+1) = gvali(x) + gsvi(x)*days/365;
    h(hn(x),hm(x)+1) = hvali(x) + hsvi(x)*days/365;
end
*/

	N_val = IGRF_ROW;

	for(p=0; p<N_val; p++)
	{
		int i=0,j=0;

		i = (int)igrfh[p][N];
		j = (int)igrfh[p][M] + 1;

		h[i][j] = igrfh[p][VALI] + igrfh[p][SVI] * days/365;

		i = (int)igrfg[p][N];
		j = (int)igrfg[p][M] + 1;

		g[i][j] = igrfg[p][VALI] + igrfg[p][SVI] * days/365;

	}


	//***************
	P11=1;
	P10=P11;
	dP11=0;
	dP10=dP11;

	for(m = 0; m< N_val; m++)
	{
		for(n=1; n<N_val ; n++) //n=1:N
		{
			if (m<=n)
			{
            // Calculate Legendre polynomials and derivatives recursively
				if (n==m)
				{
					P2 = sin_theta*P11;
					dP2 = sin_theta*dP11 + cos_theta*P11;
					P11=P2; P10=P11; P20=0;
					dP11=dP2; dP10=dP11; dP20=0;
				}
				else if (n==1)
				{
					P2 = cos_theta*P10;
					dP2 = cos_theta*dP10 - sin_theta*P10;
					P20=P10; P10=P2;
					dP20=dP10; dP10=dP2;
				}
				else
				{
					K = (pow(n-1,2)-m*m) / ((2*n-1)*(2*n-3));//((n-1)^2-m^2)/((2*n-1)*(2*n-3));
					P2 = cos_theta*P10 - K*P20;
					dP2 = cos_theta*dP10 - sin_theta*P10 - K*dP20;
					P20=P10; P10=P2;
					dP20=dP10; dP10=dP2;
				}
				//Calculate Br, Bt, and Bp

				Br = Br + powf((a/r),(n+2))*(n+1)*((g[n][m+1]*cosf(m*phi) + h[n][m+1]*sinf(m*phi))*P2);

				Bt = Bt + powf((a/r),(n+2))*((g[n][m+1]*cosf(m*phi) + h[n][m+1]*sinf(m*phi))*dP2);

				Bp = Bp + powf((a/r),(n+2))*(m*(-g[n][m+1]*sinf(m*phi) + h[n][m+1]*cosf(m*phi))* P2);

			}
		}
	}
	Bt =-Bt;
	Bp= -(Bp/(sin_theta));
	
	// NED in geocentric co-ordinates
	Bx = -Bt;
	By = Bp;
	Bz = -Br;
	
	// NED in geodetic co-ordinates
	Bx1 = Bx*cd + Bz*sd;
	By1 = By;
	Bz1 = Bz*cd - Bx*sd;
	
	
	magnm_field[0] = Bx1;
	magnm_field[1] = By1;
	magnm_field[2] = Bz1;

}

