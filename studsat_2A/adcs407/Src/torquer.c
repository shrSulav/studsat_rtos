#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "torquer.h"
#include "magnetometer.h"

/*(No of turns)*(Coil Area) */
#define nA_x // (* To be defined)
#define nA_y // (* To be defined)
#define nA_z // (* To be defined)

#define COIL_X 1
#define COIL_Y 2
#define COIL_Z 3

extern TIM_HandleTypeDef htim2;

uint8_t pwm_tx,pwm_ty,pwm_tz;

extern float32_t I_x,I_y,I_z;
/*
Description : 
Parameters : coil -> Selects the coil x or y or z 
									-> (can have 'COIL_X','COIL_Y','COIL_Z')
										
             pwm  -> PWM value to drive the respective coil
	                -> (a value ranging from 0 to 100)					 
*/


void Torquer_Update_PWM (void)
{
  pwm_tx = map(I_x,0,1.2,0,100)	;
	pwm_ty = map(I_y,0,1.2,0,100)	;
	pwm_tz = map(I_z,0,1.2,0,100)	;
}

void Torquer_Start(uint8_t coil,uint8_t pwm)	
{
	switch(coil)
	{
		case 1 : {
							HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
							htim2.Instance->CCR1 = pwm;
						 }
		
		case 2 : {
							HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
							htim2.Instance->CCR3 = pwm;
						 }
		
		case 3 : {
							HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
							htim2.Instance->CCR4 = pwm;
						 }
	}
	
}


/*
Parameters : coil -> Selects the coil x or y or z to be "Turned OFF"
                  -> (can have 'COIL_X','COIL_Y','COIL_Z')
*/

void Torquer_Stop(uint8_t coil)	
{
	switch(coil)
	{
		case 1 : {
							HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
						 }
		
		case 2 : {
							HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);
						 }
		
		case 3 : {
							HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_4);
						 }
	}
	
}
