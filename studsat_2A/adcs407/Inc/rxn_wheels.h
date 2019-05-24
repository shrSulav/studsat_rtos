#ifndef RXN_WHEELS_H
	#define RXN_WHEELS_H

#define d2r 0.017453292    //PI/180
#define rpm2rad_p_sec PI/30
#define rad_p_sec2rpm 30/PI

#define rpm_max 7000
#define rpm_const 3000

#define mtr1 1
#define mtr2 2
#define mtr3 3
#define mtr4 4

#define Tx 14.59e-6
#define Ty 114.59e-6
#define Tz 214.59e-6

#define Is 2.554e-6    //inertia of flywheel = 2.17e-6 kg_m2  ; inertia of rotor = 3.84e-7 kg_m2
#define t 2.5

void rxn_wheels_init(void);
void rxn_wheels_on(void);

#endif
