#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "rxn_wheels.h"
#include "magnetometer.h"

float32_t Dt_f32[12];
float32_t T_f32[4];
float32_t w[4];
float32_t w1[4];//in rad per second 
float32_t curr_rpm[4];
float32_t rpm[4];

extern ADC_HandleTypeDef hadc1;
//extern DMA_HandleTypeDef hdma_adc1
extern TIM_HandleTypeDef htim1;

uint8_t adc_read[4] ;//= {109,109,109,109};

void get_init_rpm(void);
void set_const_rpm(void);
void set_rpm(uint8_t mtr,uint32_t rpm);
void set_dir_cw(uint8_t mtr);
void set_dir_ccw(uint8_t mtr);
void mtr_start(void);
void compute_torque_dist(void); 
void compute_rpm_change(void);

void rxn_wheels_init(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);

	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_read,4);
}

void rxn_wheels_on(void)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);
	get_init_rpm();    
	set_const_rpm();		
	compute_torque_dist();
	compute_rpm_change();
}

void set_const_rpm(void)
{	
	set_dir_cw(mtr1);
	set_dir_cw(mtr2);
	set_dir_cw(mtr3);
	set_dir_cw(mtr4);
	TIM1->CCR1 = map (rpm_const,0,rpm_max,0,1000);
	TIM1->CCR2 = map (rpm_const,0,rpm_max,0,1000);
	TIM1->CCR3 = map (rpm_const,0,rpm_max,0,1000);
	TIM1->CCR4 = map (rpm_const,0,rpm_max,0,1000);			
}

void set_rpm(uint8_t mtr,uint32_t rpm)
{
	switch(mtr)
	{
		case 1 : {TIM1->CCR1 = map (rpm,0,rpm_max,0,1000);break;}
		case 2 : {TIM1->CCR2 = map (rpm,0,rpm_max,0,1000);break;}
		case 3 : {TIM1->CCR3 = map (rpm,0,rpm_max,0,1000);break;}
		case 4 : {TIM1->CCR4 = map (rpm,0,rpm_max,0,1000);break;}
	}
}

void set_dir_cw(uint8_t mtr)
{
	switch(mtr)
	{
		case 1 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_RESET);break;}
		case 2 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);break;}
		case 3 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);break;}
		case 4 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);break;}
	}
}
void set_dir_ccw(uint8_t mtr)
{
	switch(mtr)
	{
		case 1 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_SET);break;}
		case 2 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET);break;}
		case 3 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET);break;}
		case 4 : {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);break;}
	}
}

void mtr_start(void)
{
	//Start mtr1 (with CW or CCW Enabled)
		if (w[0]>=0)
		{ //Enable CW 
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_RESET);			
			set_rpm(mtr1,w[0]);
		}
		else if (w[0]<0)
		{//Enable CCW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_SET);			
			set_rpm(mtr1,fabs(w[0]));
		}
		
		//Start mtr2 (with CW or CCW Enabled)
		if (w[1]>=0)
		{//Enable CW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);			
			set_rpm(mtr2,w[1]);
		}
		else if (w[1]<0)
		{//Enable CCW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET);			
			set_rpm(mtr2,fabs(w[1]));
		}
		
		//Start mtr3 (with CW or CCW Enabled)
		if (w[2]>=0)
		{//Enable CW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);			
			set_rpm(mtr3,w[2]);
		}
		else if (w[2]<0)
		{//Enable CCW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET);			
			set_rpm(mtr3,fabs(w[2]));
		}
		
		//Start mtr4 (with CW or CCW Enabled)
		if (w[3]>=0)
		{//Enable CW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);			
			set_rpm(mtr4,w[3]);
		}
		else if (w[3]<0)
		{//Enable CCW
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);			
			set_rpm(mtr4,fabs(w[3]));
		}
		
//verify
for(int i=0;i<4;i++)		
{
	rpm[i] = fabsf(w[i]);
}
	
}

void get_init_rpm()
{	
	for(uint8_t i=0;i<4;i++)
	{
		w1[i] = map(adc_read[i],0,255,0,rpm_max)*rpm2rad_p_sec;
		curr_rpm[i] = map(adc_read[i],0,255,0,rpm_max);
	}		
}	

void compute_torque_dist()
{
	float32_t D_f32[12] = {arm_cos_f32((19.471*d2r)),-arm_cos_f32(19.471*d2r)*arm_cos_f32(60*d2r),-arm_cos_f32(19.471*d2r)*arm_cos_f32(60*d2r),0,0,arm_cos_f32(19.471*d2r)*arm_cos_f32(30*d2r),-arm_cos_f32(19.471*d2r)*arm_cos_f32(30*d2r),0,-arm_sin_f32(19.471*d2r),-arm_sin_f32(19.471*d2r),-arm_sin_f32(19.471*d2r),1};
	float32_t Txyz_f32[3] = {Tx,Ty,Tz};			
	
	arm_matrix_instance_f32 D;
	arm_matrix_instance_f32 Txyz;
	arm_matrix_instance_f32 Dt;
	arm_matrix_instance_f32 T;
	
	arm_mat_init_f32(&D,3,4,(float32_t *)D_f32);
	arm_mat_init_f32(&Txyz,3,1,(float32_t *)Txyz_f32);
	arm_mat_init_f32(&Dt,4,3,(float32_t *)Dt_f32);
	arm_mat_init_f32(&T,4,1,(float32_t *)T_f32);
	
	arm_mat_trans_f32(&D,&Dt);
	arm_mat_mult_f32(&Dt,&Txyz,&T);			
}	

void compute_rpm_change()
{	
	for(uint8_t i=0;i<4;i++)
	{
		w[i] = ((T_f32[i]*(t/Is))+w1[i])*rad_p_sec2rpm;
	}
}	

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	long i=t*42016806;
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
  //Interupt Routine
	get_init_rpm();    
	
	compute_torque_dist();
	compute_rpm_change();
	mtr_start();		
	
	while(i)
	{
		i--;
	}	
}
