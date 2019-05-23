// test-bench for attitude filter
#include "main.h"

void Delay(__IO uint32_t nCount);
void cortexm4f_enable_fpu(void);

/*
q=[0.28222;0.56443;0.18814;0.75258];
    qc=[0.28222;-0.56443;-0.18814;-0.75258];
    w=[2.2;5.2;3.3];

	mag=[0.2148;0.0410;-0.4536;0.088;0.00280;-0.2370];

	P = diag([1*10^-3 1*10^-3 1*10^-3 1*10^-3 1*10^-4 1*10^-4 1*10^-4]);
	igrfmag=[25185;25184;-250;20000;23000;-100];
*/
float32_t x_f32[7]={0.28222,0.56443,0.18814,0.75258,2.2,5.2,3.3};
float32_t readings_f32[6]={0.2148,0.0410,-0.4536,0.088,0.00280,-0.2370};
float32_t P_f32[49] = { 10,0,0,0,0,0,0,
					0,10,0,0,0,0,0,
					0,0,10,0,0,0,0,
					0,0,0,10,0,0,0,
					0,0,0,0,1,0,0,
					0,0,0,0,0,1,0,
					0,0,0,0,0,0,1, };

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

	arm_mat_init_f32(&x,7,1,x_f32);
	arm_mat_init_f32(&readings,6,1,readings_f32);
	arm_mat_init_f32(&P,7,7,P_f32);
	arm_mat_init_f32(&Ptmp,7,7,P_f32);
	arm_mat_scale_f32(&Ptmp,powf(10,-4),&P);

	init_pf();
	init_att();
	pf_ekf_tmp_init();
	att_ekf_tmp_init();
	//igrfmag=[25185;25184;-250;20000;23000;-100];
	
	igrfmag[0] = 25185;
	igrfmag[1] = 25184;
	igrfmag[2] = -250;
	igrfmag[3] = 20000;
	igrfmag[4] = 23000;
	igrfmag[5] = -100;

	att_filter(&readings,&x,&P);

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
