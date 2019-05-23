// test-bench for prefilter
#include "stm32f4_discovery.h"
#include "arm_math.h"
#include "ekf_var.h"
#include "ekf_init.h"
#include "ekf_tmp.h"
#include "filters.h"
 
void Delay(__IO uint32_t nCount);
void cortexm4f_enable_fpu(void);

float32_t x_f32[9]={0.534,0.5678, 0.3456,0.543,0.52,0.35,0,0,0};
float32_t readings_f32[3]={0.567,0.745,-0.498};
float32_t P_f32[81] = { 1,0,0,0,0,0,0,0,0,
					0,1,0,0,0,0,0,0,0,
					0,0,1,0,0,0,0,0,0,
					0,0,0,100,0,0,0,0,0,
					0,0,0,0,100,0,0,0,0,
					0,0,0,0,0,100,0,0,0,
					0,0,0,0,0,0,100,0,0,
					0,0,0,0,0,0,0,100,0,
					0,0,0,0,0,0,0,0,100 };

arm_matrix_instance_f32 x;
arm_matrix_instance_f32 readings;
arm_matrix_instance_f32 P;

int main(void)
{
	arm_matrix_instance_f32 Ptmp;
	cortexm4f_enable_fpu();
	/* Initialize LEDs mounted on STM32F4-Discovery board */
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);
	/* Generate software interrupt: simulate a rising edge applied on EXTI0 line */
  //EXTI_GenerateSWInterrupt(EXTI_Line0);
	
	
	arm_mat_init_f32(&x,9,1,x_f32);
	arm_mat_init_f32(&readings,3,1,readings_f32);
	arm_mat_init_f32(&P,9,9,P_f32);
	arm_mat_init_f32(&Ptmp,9,9,P_f32);
	arm_mat_scale_f32(&Ptmp,powf(10,4),&P);
	
	init_pf();
	init_att();
	pf_ekf_tmp_init();
	att_ekf_tmp_init();
	
	prefilter(&readings,&x,&P);

  while (1)
  {
		STM_EVAL_LEDToggle(LED6);
		Delay(0xFFFFFF);
  }
}


void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

void cortexm4f_enable_fpu() {
    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
