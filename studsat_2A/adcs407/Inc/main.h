/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TPS_TORQUES_X_E_D_Pin GPIO_PIN_3
#define TPS_TORQUES_X_E_D_GPIO_Port GPIOE
#define TPS_TORQUES_X_FAULT_Pin GPIO_PIN_4
#define TPS_TORQUES_X_FAULT_GPIO_Port GPIOE
#define TPS_REACTION_WHEEL_E_D_Pin GPIO_PIN_5
#define TPS_REACTION_WHEEL_E_D_GPIO_Port GPIOE
#define TPS_REACTION_WHEEL_FAULT_Pin GPIO_PIN_6
#define TPS_REACTION_WHEEL_FAULT_GPIO_Port GPIOE
#define TPS_REACTION_WHEEL_E_DC13_Pin GPIO_PIN_13
#define TPS_REACTION_WHEEL_E_DC13_GPIO_Port GPIOC
#define TPS_REACTION_WHEEL_FAULTC14_Pin GPIO_PIN_14
#define TPS_REACTION_WHEEL_FAULTC14_GPIO_Port GPIOC
#define IPC_TX_Pin GPIO_PIN_0
#define IPC_TX_GPIO_Port GPIOA
#define IPC_RX_Pin GPIO_PIN_1
#define IPC_RX_GPIO_Port GPIOA
#define TORQUER_COIL_PWM_2_Pin GPIO_PIN_2
#define TORQUER_COIL_PWM_2_GPIO_Port GPIOA
#define TORQUER_COIL_PWM_3_Pin GPIO_PIN_3
#define TORQUER_COIL_PWM_3_GPIO_Port GPIOA
#define REACTION_WHEEL_RPM_1_Pin GPIO_PIN_4
#define REACTION_WHEEL_RPM_1_GPIO_Port GPIOA
#define REACTION_WHEEL_RPM_2_Pin GPIO_PIN_5
#define REACTION_WHEEL_RPM_2_GPIO_Port GPIOA
#define REACTION_WHEEL_RPM_3_Pin GPIO_PIN_6
#define REACTION_WHEEL_RPM_3_GPIO_Port GPIOA
#define REACTION_WHEEL_RPM_4_Pin GPIO_PIN_7
#define REACTION_WHEEL_RPM_4_GPIO_Port GPIOA
#define REACTION_WHEEL_PWM_1_Pin GPIO_PIN_9
#define REACTION_WHEEL_PWM_1_GPIO_Port GPIOE
#define REACTION_WHEEL_PWM_2_Pin GPIO_PIN_11
#define REACTION_WHEEL_PWM_2_GPIO_Port GPIOE
#define REACTION_WHEEL_PWM_3_Pin GPIO_PIN_13
#define REACTION_WHEEL_PWM_3_GPIO_Port GPIOE
#define REACTION_WHEEL_PWM_4_Pin GPIO_PIN_14
#define REACTION_WHEEL_PWM_4_GPIO_Port GPIOE
#define EPS_CURRENT_SENSOR_SCL_Pin GPIO_PIN_10
#define EPS_CURRENT_SENSOR_SCL_GPIO_Port GPIOB
#define EPS_CURRENT_SENSOR_SDA_Pin GPIO_PIN_11
#define EPS_CURRENT_SENSOR_SDA_GPIO_Port GPIOB
#define MAGNETOMETER_TX_Pin GPIO_PIN_8
#define MAGNETOMETER_TX_GPIO_Port GPIOD
#define MAGNETOMETER_RX_Pin GPIO_PIN_9
#define MAGNETOMETER_RX_GPIO_Port GPIOD
#define Check_Out_Port_TX_Pin GPIO_PIN_6
#define Check_Out_Port_TX_GPIO_Port GPIOC
#define Check_Out_Port_RX_Pin GPIO_PIN_7
#define Check_Out_Port_RX_GPIO_Port GPIOC
#define TORQUER_COIL_PWM_1_Pin GPIO_PIN_15
#define TORQUER_COIL_PWM_1_GPIO_Port GPIOA
#define TPS_TORQUER_Z_E_D_Pin GPIO_PIN_4
#define TPS_TORQUER_Z_E_D_GPIO_Port GPIOB
#define TPS_TORQUER_Z_FAULT_Pin GPIO_PIN_5
#define TPS_TORQUER_Z_FAULT_GPIO_Port GPIOB
#define GYRO_SCL_Pin GPIO_PIN_8
#define GYRO_SCL_GPIO_Port GPIOB
#define GYRO_SDA_Pin GPIO_PIN_9
#define GYRO_SDA_GPIO_Port GPIOB
#define TPS_TORQUER_Y_E_D_Pin GPIO_PIN_0
#define TPS_TORQUER_Y_E_D_GPIO_Port GPIOE
#define TPS_TORQUER_Y_FAULT_Pin GPIO_PIN_1
#define TPS_TORQUER_Y_FAULT_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
