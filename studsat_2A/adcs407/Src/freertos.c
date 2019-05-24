/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "mod_inc.h"
#include "g_var.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId detumbleHandle;
osThreadId gyro_checkHandle;
osThreadId att_detHandle;
osThreadId att_controlHandle;
osThreadId gps_dataHandle;
osThreadId magnm_dataHandle;
osThreadId sun_sensorHandle;
osThreadId ipcHandle;

osSemaphoreId binSemGPSHandle;
osSemaphoreId binSemMagnmHandle;
osSemaphoreId binSemSunSensorHandle;
osSemaphoreId binSemDetumbleHandle;
osSemaphoreId binSemGyroHandle;
osSemaphoreId binSemAttDetHandle;
osSemaphoreId binSemAttControlHandle;
osSemaphoreId binSemIPCHandle;

/* USER CODE BEGIN Variables */
uint8_t counter;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void taskDetumble(void const * argument);
void taskGyro(void const * argument);
void taskAttDet(void const * argument);
void taskAttControl(void const * argument);
void taskGPS(void const * argument);
void taskMagnm(void const * argument);
void taskSunSense(void const * argument);
void taskIPC(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
//void taskTest(void const * argument);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of binSemGPS */
  osSemaphoreDef(binSemGPS);
  binSemGPSHandle = osSemaphoreCreate(osSemaphore(binSemGPS), 1);

  /* definition and creation of binSemMagnm */
  osSemaphoreDef(binSemMagnm);
  binSemMagnmHandle = osSemaphoreCreate(osSemaphore(binSemMagnm), 1);

  /* definition and creation of binSemSunSensor */
  osSemaphoreDef(binSemSunSensor);
  binSemSunSensorHandle = osSemaphoreCreate(osSemaphore(binSemSunSensor), 1);

  /* definition and creation of binSemDetumble */
  osSemaphoreDef(binSemDetumble);
  binSemDetumbleHandle = osSemaphoreCreate(osSemaphore(binSemDetumble), 1);

  /* definition and creation of binSemGyro */
  osSemaphoreDef(binSemGyro);
  binSemGyroHandle = osSemaphoreCreate(osSemaphore(binSemGyro), 1);

  /* definition and creation of binSemAttDet */
  osSemaphoreDef(binSemAttDet);
  binSemAttDetHandle = osSemaphoreCreate(osSemaphore(binSemAttDet), 1);

  /* definition and creation of binSemAttControl */
  osSemaphoreDef(binSemAttControl);
  binSemAttControlHandle = osSemaphoreCreate(osSemaphore(binSemAttControl), 1);

  /* definition and creation of binSemIPC */
  osSemaphoreDef(binSemIPC);
  binSemIPCHandle = osSemaphoreCreate(osSemaphore(binSemIPC), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	//printf("\nInitializing the ADCS system...");
	//osDelay(5);
	osSemaphoreWait(binSemIPCHandle,osWaitForever);
	osSemaphoreWait(binSemAttDetHandle,osWaitForever);
	osSemaphoreWait(binSemAttControlHandle,osWaitForever);
	osSemaphoreWait(binSemDetumbleHandle,osWaitForever);
	osSemaphoreWait(binSemGPSHandle,osWaitForever);
	osSemaphoreWait(binSemMagnmHandle,osWaitForever);
	osSemaphoreWait(binSemSunSensorHandle,osWaitForever);
	osSemaphoreWait(binSemGyroHandle,osWaitForever);
	
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of detumble */
  osThreadDef(detumble, taskDetumble, osPriorityNormal, 0, 128);
  detumbleHandle = osThreadCreate(osThread(detumble), NULL);

  /* definition and creation of gyro_check */
  osThreadDef(gyro_check, taskGyro, osPriorityRealtime, 0, 128);
	//osThreadDef(gyro_check, taskGyro, osPriorityRealtime, 0, 256);
  gyro_checkHandle = osThreadCreate(osThread(gyro_check), NULL);

  /* definition and creation of att_det */
  osThreadDef(att_det, taskAttDet, osPriorityNormal, 0, 256);
  att_detHandle = osThreadCreate(osThread(att_det), NULL);

  /* definition and creation of att_control */
  osThreadDef(att_control, taskAttControl, osPriorityRealtime, 0, 128);
  att_controlHandle = osThreadCreate(osThread(att_control), NULL);

  /* definition and creation of gps_data */
  osThreadDef(gps_data, taskGPS, osPriorityAboveNormal, 0, 128);
  gps_dataHandle = osThreadCreate(osThread(gps_data), NULL);

  /* definition and creation of magnm_data */
  osThreadDef(magnm_data, taskMagnm, osPriorityAboveNormal, 0, 128);
  magnm_dataHandle = osThreadCreate(osThread(magnm_data), NULL);

  /* definition and creation of sun_sensor */
  osThreadDef(sun_sensor, taskSunSense, osPriorityAboveNormal, 0, 128);
  sun_sensorHandle = osThreadCreate(osThread(sun_sensor), NULL);

  /* definition and creation of ipc */
  osThreadDef(ipc, taskIPC, osPriorityHigh, 0, 128);
  ipcHandle = osThreadCreate(osThread(ipc), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	//osSemaphoreRelease(binSemGyroHandle);
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
		//printf("\ntask default : Hello ...");
  }
  /* USER CODE END StartDefaultTask */
}

/* taskDetumble function */
void taskDetumble(void const * argument)
{
  /* USER CODE BEGIN taskDetumble */
  /* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemDetumbleHandle,osWaitForever);

		read_magnm_data(magnm_gauss_new);
		//printf("\nMagnetic Field = %f %f %f", magnm_gauss_new[0],magnm_gauss_new[1],magnm_gauss_new[2]);
		
		magnm_gauss_old[0] = magnm_gauss_new[0];
		magnm_gauss_old[1] = magnm_gauss_new[1];
		magnm_gauss_old[2] = magnm_gauss_new[2];
		
		read_magnm_data(magnm_gauss_new);
		//printf("\nMagnetic Field = %f %f %f", magnm_gauss_new[0],magnm_gauss_new[1],magnm_gauss_new[2]);
		
		//bdot();
		osSemaphoreRelease(binSemGyroHandle);
		//actuate
  }
  /* USER CODE END taskDetumble */
}

/* taskGyro function */
void taskGyro(void const * argument)
{
  /* USER CODE BEGIN taskGyro */
  osSemaphoreRelease(binSemGyroHandle);
	/* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemGyroHandle,osWaitForever);
		//call gyro function

		ang_velocity[0] = 2.0f;
		ang_velocity[1] = 2.0f;
		ang_velocity[2] = 2.0f;
		
		//printf("\nAngular Velocity = %f %f %f ", ang_velocity[0],ang_velocity[1],ang_velocity[2]);
		
		if((ang_velocity[0] > 3.0f) || 
			 (ang_velocity[1] > 3.0f) || 
			 (ang_velocity[2] > 3.0f) )
		{
			osSemaphoreRelease(binSemDetumbleHandle);	
		}
		else
		{
			osSemaphoreRelease(binSemAttDetHandle);
		}
  }
  /* USER CODE END taskGyro */
}

/* taskAttDet function */
void taskAttDet(void const * argument)
{
  /* USER CODE BEGIN taskAttDet */
	optimized_triad_init();
	gps_value gps_dummy = {13.1,'N',77.6,'E',0.915,{2017,1,24},{1,35,3}} ;
	/* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemAttDetHandle,osWaitForever);
		// get magnetometer readings
		// get sunsensor readings
		// get gps readings
		// get ref. magnetic field values (IGRF)
		// get ref. sun vector values
		// get attitude using optimized TRIAD
		
		gps_input = GetGPSValues();
		printf("\nlatitude = %f \nlongitude = %f \naltitude = %f", gps_input.latitude_f32,gps_input.longitude_f32, gps_input.altitude_f32);
		
		read_magnm_data(magnm_gauss_new);
		printf("\nMagnetic Field = %f %f %f", magnm_gauss_new[0],magnm_gauss_new[1],magnm_gauss_new[2]);
		
		sun_vector_body(sunvec_body);
		//printf("\nSun Sensor = %f %f %f",sunvec_body[0],sunvec_body[1],sunvec_body[2]);
		
		igrf(gps_dummy,magnm_ref);
		//igrf(gps_input,magnm_ref);
//		printf("\nBx_igrf = %f", magnm_ref[0]);
//		printf("\nBy_igrf = %f", magnm_ref[1]);
//		printf("\nBz_igrf = %f", magnm_ref[2]);
//		
		//sun_vector(gps_input.date, gps_input.time, sunvec_ref);
		sun_vector_ref(gps_dummy.date, gps_dummy.time, sunvec_ref);
//		printf("\nSun Vector = %f",sunvec_ref[0]);
//		printf("\nSun Vector = %f",sunvec_ref[1]);
//		printf("\nSun Vector = %f",sunvec_ref[2]);
		
		vector_update(magnm_ref, sunvec_ref, magnm_gauss_new, sunvec_body);
		get_attitude();
		osSemaphoreRelease(binSemAttControlHandle);
  }
  /* USER CODE END taskAttDet */
}

/* taskAttControl function */
void taskAttControl(void const * argument)
{
  /* USER CODE BEGIN taskAttControl */
	rxn_wheels_init();
	/* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemAttControlHandle,osWaitForever);
		
		//actuation code
		//rxn_wheels_on();
		
		osSemaphoreRelease(binSemGyroHandle);
  }
  /* USER CODE END taskAttControl */
}

/* taskGPS function */
void taskGPS(void const * argument)
{
  /* USER CODE BEGIN taskGPS */
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait(binSemGPSHandle,osWaitForever);
		gps_input = GetGPSValues();
  }
  /* USER CODE END taskGPS */
}

/* taskMagnm function */
void taskMagnm(void const * argument)
{
  /* USER CODE BEGIN taskMagnm */
	/* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemMagnmHandle,osWaitForever);
		read_magnm_data(magnm_gauss_new);
  }
  /* USER CODE END taskMagnm */
}

/* taskSunSense function */
void taskSunSense(void const * argument)
{
  /* USER CODE BEGIN taskSunSense */
	/* Infinite loop */
  for(;;)
  {
    //osDelay(1);
		osSemaphoreWait(binSemSunSensorHandle,osWaitForever);

		sunvec_body[0] = 5.0;
		sunvec_body[1] = 6.0;
		sunvec_body[2] = 7.0;
		
		//printf("\nSun Vector = %f %f %f",sunvec_body[0],sunvec_body[1],sunvec_body[2]);

  }
  /* USER CODE END taskSunSense */
}

/* taskIPC function */
void taskIPC(void const * argument)
{
  /* USER CODE BEGIN taskIPC */
	/* Infinite loop */
  for(;;)
  {
		//osDelay(1);
		osSemaphoreWait(binSemIPCHandle,osWaitForever);
		//printf("task IPC : Hello ...");
  }
  /* USER CODE END taskIPC */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
