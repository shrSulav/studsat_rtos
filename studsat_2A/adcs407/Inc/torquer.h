#ifndef TORQUER_H
#define TORQUER_H

#include "stm32f4xx_hal.h"

// Function Prototypes
void Torquer_Start(uint8_t coil,uint8_t pwm);
void Torquer_Stop(uint8_t coil);
	
#endif
/***************************** EOF *****************************/
