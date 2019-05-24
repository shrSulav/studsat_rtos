#define PI 3.14159265358979

#include "sun_vector.h"
#include "arm_math.h"
#include "math.h"
#include "g_var.h"

const Date set_date = {2015,3,20};
const Time set_time = {22,40,0};

void sun_vector_ref(const Date date, const Time time, float32_t sun_vec[3])
{
  float32_t givenjd, setjd, days;
  float32_t azimuth, elevation;
  float32_t sunVector[3];
  float32_t sunVector_norm,sunVector_norm_inv;

  givenjd = findjd(date, time);
  setjd = findjd(set_date,set_time);
  days = setjd - givenjd;
  azimuth=((float64_t)days * 2.0 * PI)/365.25;
	elevation=((23.44 * 3.14)/180.0)*sinf(azimuth);

  sunVector[0] = cosf(elevation);
  sunVector[1] = tanf(azimuth);
  sunVector[2] = sinf(elevation);

  arm_dot_prod_f32(sunVector, sunVector, 3, &sunVector_norm);
  sunVector_norm = sqrtf(sunVector_norm);
  sunVector_norm_inv = 1/sunVector_norm;
  arm_scale_f32(sunVector, sunVector_norm_inv, sun_vec,3);
  
}


/*
 * Arguments    : Date date, Time time
 * Return Type  : float32_t

date.year : year
date.month : month
date.day : day
time.hh : hour
time.mm : minutes
time.ss : seconds

 */
float32_t findjd(const Date date, const Time time)
{
int32_t a, y, m;
uint32_t lpy1, lpy2, lpy3, jdnm;
float32_t hh,mm,ss;
int32_t jdn;
float32_t jd;

a = ( 14 - date.month ) / 12;
y = date.year + 4800 - a;
m = date.month + 12*a - 3;
	

lpy1 = y/4;
	
lpy2 = y/100;
lpy3 = y/400;
jdnm = ( 153 * m + 2 ) / 5;

jdn = date.day + jdnm + 365*y + lpy1 - lpy2 + lpy3 - 32045;

	hh = ((float32_t)time.hh - 12.0f) / 24.0f;
	mm = (time.mm/1440.0);
	ss = (time.ss/86400.0);
	//jd = (float32_t)jdn + ((time.hh - 12) / 24.0) + 
    //      (time.mm/1440.0) + (time.ss/86400.0);
jd = (float32_t)jdn + hh + mm + ss;

return jd;

}

void sun_vector_body(float32_t* sunvec_body)
{
		sunvec_body[0] = 5.0;
		sunvec_body[1] = 6.0;
		sunvec_body[2] = 7.0;
}
