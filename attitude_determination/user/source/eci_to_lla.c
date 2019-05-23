
/* Include Files */
#include "eci_to_lla.h"
#include "struct_def.h"
/* Function Definitions */

/*
 * ECI2LLA.m
 *  usage: ENU = ECI2LLA(ECI)
 *  Inputs:
 *     ECI is a matrix of row vectors of form [ time x y z]
 *       x, y, and z are in meters
 *               time in seconds from GMT (Zulu time)
 *  Output:
 *    LLA is a matrix of row vectors of form [time lat lon HAE]
 *      lat, lon are in degrees
 *            HAE in meters
 * Arguments    : const float ECI[4]
 *                float *time
 *                float *lat
 *                float *lon
 *                float *HAE
 * Return Type  : void
 */

float32_t eci_to_lla_time, eci_to_lla_lat,eci_to_lla_lon,eci_to_lla_hae;
gpsData eci2lla;

void eci_to_lla(const float32_t time,const float32_t x,const float32_t y,const float32_t z,)
{
  float32_t theta;
  float32_t b_ECI[3];
  float32_t fv0[9];
  uint32_t` i0;
  static const signed char iv0[3] = { 0, 0, 1 };

  float32_t Pose[3];
  uint32_t i1;
  float32_t rxy;
  float32_t b_long;
  float32_t r;
  float32_t phi;
  float32_t lambda;
  float32_t x;
  float32_t alpha;
  float32_t del;
  float32_t H;
  float32_t Rn1;
  float32_t Rn2;

  /*  constants */
  /* WGS84=[6378.137 0.081819190842622] */
  /*  first eccentricity of the earth */
  /*  earth rotation rate in radians per second */
  /*  earth flattening factor */
  /* f = ecc2flat([6378.137 0.081819190842622]); */
  /*  length of earth semimajor axis in meters */
  /*  loop to convert from ECI to ENU */
  /*  rotate earth from GMT     */
  theta = 7.29211606E-5F * time;

  /*  coordinate transform (rotation matrix) from ECI to ECEF    */
  /*  Convert from ECI to ECEF  */
  b_ECI[0] = x;
  b_ECI[1] = y;
  b_ECI[2] = z;
  fv0[0] = cos(theta);
  fv0[3] = sin(theta);
  fv0[6] = 0.0F;
  fv0[1] = -sinf(theta);
  fv0[4] = cosf(theta);
  fv0[7] = 0.0F;
  for (i0 = 0; i0 < 3; i0++) {
    fv0[2 + 3 * i0] = iv0[i0];
  }

  for (i0 = 0; i0 < 3; i0++) {
    Pose[i0] = 0.0F;
    for (i1 = 0; i1 < 3; i1++) {
      Pose[i0] += fv0[i0 + 3 * i1] * b_ECI[i1];
    }
  }

  /*  x component in ECEF (meters) */
  /*  y component in ECEF (meters) */
  /*  z component in ECEF (meters) */
  /*  routines taken from WS-21231/1 Appendix 1 */
  rxy = sqrtf(Pose[0] * Pose[0] + Pose[1] * Pose[1]);
  if (Pose[1] < 0.0F) {
    b_long = -acos(Pose[0] / rxy);
  } else {
    b_long = acos(Pose[0] / rxy);
  }

  r = sqrtf((Pose[0] * Pose[0] + Pose[1] * Pose[1]) + Pose[2] * Pose[2]);
  phi = asinf(Pose[2] / r);
  lambda = acosf(rxy / r);
  x = sinf(phi);
  alpha = 6.378137E+6F / sqrtf(1.0F + 0.00669432292F * (x * x) / 0.993305683F);
  x = cosf(lambda);
  del = 0.00669432292F * sinf(phi) * cosf(lambda) / (1.0F -
    0.00669432292F * (x * x));
  H = (r - alpha) * (1.0F - del * (alpha * del / r) / 2.0F);
  x = sinf(atanf(Pose[2] / (0.993305624F * rxy)));
  Rn1 = 6.378137E+6F / sqrtf(1.0F - 0.00669438F * (x * x));
  x = sinf(atanf(Pose[2] * (Rn1 + H) / ((Rn1 * 0.993305624F + H) * rxy)));
  Rn2 = 6.378137E+6F / sqrtf(1.0F - 0.00669438F * (x * x));

  /*  Form output matrix */
  eci_to_lla_time = ECI[0];
  eci_to_lla_lat = atanf(Pose[2] * (Rn2 + H) / ((Rn2 * 0.993305624F + H) * rxy)) *
    180.0F / 3.14159274F;
  eci_to_lla_lon = b_long * 180.0F / 3.14159274F;
  eci_to_lla_hae = H;

  eci2lla.lat_f32 = eci_to_lla_lat;
  eci2lla.long_f32 = eci_to_lla_lon;
  eci2lla.alt_f32 = eci_to_lla_hae;
}

/*
 * File trailer for eci2LLA.c
 *
 * [EOF]
 */
