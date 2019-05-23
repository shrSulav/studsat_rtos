/*
 * File: orb2eci.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 10-Oct-2016 12:06:38
 */

/* Include Files */
#include "orb_to_eci.h"
#include "math.h"

/* Function Definitions */

/*
 * convert classical orbital elements to eci state vector
 * Arguments    : 
 *                const float oev[6]
 *                double r[3]
 *                double v[3]
 * Return Type  : void
 */
void orb_to_eci(const float32_t oev[6], float32_t r[3], float32_t v[3])
{
  static float32_t mu = 398600.436233; //earth gravitational constant (km**3/sec**2)

  float32_t slr;
  float32_t rm;
  float32_t arglat;
  float32_t sarglat;
  float32_t carglat;
  float32_t c4;
  float32_t c5;
  float32_t c6;
  float32_t sinc;
  float32_t cinc;
  float32_t sraan;
  float32_t craan;

  /*  input */
  /*   mu     = gravitational constant (km**3/sec**2) */
  /*   oev(1) = semimajor axis (kilometers) */
  /*   oev(2) = orbital eccentricity (non-dimensional) */
  /*            (0 <= eccentricity < 1) */
  /*   oev(3) = orbital inclination (radians) */
  /*            (0 <= inclination <= pi) */
  /*   oev(4) = argument of perigee (radians) */
  /*            (0 <= argument of perigee <= 2 pi) */
  /*   oev(5) = right ascension of ascending node (radians) */
  /*            (0 <= raan <= 2 pi) */
  /*   oev(6) = true anomaly (radians) */
  /*            (0 <= true anomaly <= 2 pi) */
  /*  output */
  /*   r = eci position vector (kilometers) */
  /*   v = eci velocity vector (kilometers/second) */
  /*  Orbital Mechanics with MATLAB */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  unload orbital elements array */
  
  slr = oev[0] * (1.0F - oev[1] * oev[1]);
  rm = slr / (1.0F + oev[1] * cosf(oev[5]));
  arglat = oev[3] + oev[5];
  sarglat = sinf(arglat);
  carglat = cosf(arglat);
  c4 = sqrtf(mu / slr);
  c5 = oev[1] * cosf(oev[3]) + carglat;
  c6 = oev[1] * sinf(oev[3]) + sarglat;
  sinc = sinf(oev[2]);
  cinc = cosf(oev[2]);
  sraan = sinf(oev[4]);
  craan = cosf(oev[4]);

  /*  position vector */
  r[0] = rm * (craan * carglat - sraan * cinc * sarglat);
  r[1] = rm * (sraan * carglat + cinc * sarglat * craan);
  r[2] = rm * sinc * sarglat;

  /*  velocity vector */
  v[0] = -c4 * (craan * c6 + sraan * cinc * c5);
  v[1] = -c4 * (sraan * c6 - craan * cinc * c5);
  v[2] = c4 * c5 * sinc;
}

/*
 * File trailer for orb2eci.c
 *
 * [EOF]
 */
