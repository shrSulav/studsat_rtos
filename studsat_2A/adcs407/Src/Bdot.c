#include "Bdot.h"
#include "magnetometer.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h"

//#define Bg  40000        //Bdot Gain 
//#define g2t 10e-4       //Gauss to Tesla multiplication factor
const float32_t Bg = 40000.0;
//const float32_t g2t = 0.0001;
const float32_t g2t = 1;
//float32_t magnm_gauss_new,magnm_gauss_new[1],magnm_gauss_new[2];
extern float32_t magnm_gauss_new[3];
//float32_t magnm_gauss_old[0],magnm_gauss_old[1],magnm_gauss_old[2];
extern float32_t magnm_gauss_old[3];
float32_t Bdot_x,Bdot_y,Bdot_z;
float32_t Mx,My,Mz;
float32_t Tx,Ty,Tz;

float32_t I_x,I_y,I_z;

extern uint8_t pwm_tx,pwm_ty,pwm_tz;

extern UART_HandleTypeDef huart3;


void bdot (void)
{
	/*
	read_magnm_data(magnm_gauss_old);
	//magnm_data_parse(data);
	
	magnm_gauss_old[0] = magnm_gauss_new[0]; 
  	magnm_gauss_old[1] = magnm_gauss_new[1];
	magnm_gauss_old[2] = magnm_gauss_new[2];
	
	HAL_Delay(200);
	
	read_magnm_data(magnm_gauss_new);
	*/
	
	//Bdot rate calculation 
	Bdot_x = 5*(magnm_gauss_old[0]*g2t - magnm_gauss_new[0]*g2t);
	Bdot_y = 5*(magnm_gauss_old[1]*g2t - magnm_gauss_new[1]*g2t);
	Bdot_z = 5*(magnm_gauss_old[2]*g2t - magnm_gauss_new[2]*g2t);
	
	//Magnetic Moments Calculation 
	Mx = - Bg * Bdot_x;
	My = - Bg * Bdot_y;
	Mz = - Bg * Bdot_z;
	
	//Tumbling Torque Calculation 
	Tx = (My*magnm_gauss_new[2]*g2t)-(Mz*magnm_gauss_new[1]*g2t);
	Ty = (Mz*magnm_gauss_new[0]*g2t)-(Mx*magnm_gauss_new[2]*g2t);
	Tz = (Mx*magnm_gauss_new[1]*g2t)-(My*magnm_gauss_new[0]*g2t);	
	

  /*  !!!! WORK IN PROGRESS !!!! */
	
	/*
	Have to add code for current calculation and driving the coils
	
	Formulas for implementation :
	
	I_x = Tx/(nA_x*magnm_gauss_new[0]*g2t);
	I_y = Ty/(nA_y*magnm_gauss_new[1]*g2t);
	I_z = Tz/(nA_z*magnm_gauss_new[2]*g2t);
	
	Coils are driven using the functions in torquer.c   
	
	*/
		
}

