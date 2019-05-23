// test-bench for prefilter
#include "stm32f4_discovery.h"
#include "arm_math.h"
#include "ekf_var.h"
#include "ekf_init.h"
#include "ekf_tmp.h"
#include "filters.h"
#include "igrf.h"

void Delay(__IO uint32_t nCount);
void cortexm4f_enable_fpu(void);

float32_t days;
gpsData gps = {70, 50, 680000,{{2015,5,31},1,35,3}} ; //'05-31-1994 01:35:3'
//datetime default_date = {{2015,1,1},0,0,0};
int main(void)
{
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

	//days = e_time(gps.date_gps.date,default_date.date);
	igrf(gps);

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
