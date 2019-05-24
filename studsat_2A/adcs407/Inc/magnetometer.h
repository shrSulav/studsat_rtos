#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include "arm_math.h"
// Function Prototypes
void send(char c);
void send_ENTER(void);
void write_EN(void);
void ASCII_On(void);
void Binary_On(void);
void single_op(void);
void continuous_op(void);
void stop_con_op(void);
void set_baud_9600(void);
void set_baud_19200(void);
void set_factory_default(void);
void store_parameters(void);
void restore_settings(void);

float map (float x,float in_min,float in_max,float out_min,float out_max);
//void magnm_data_parse(char *data);
void read_magnm_data (float32_t magnm_gauss[3]);


#endif
/***************************** EOF *****************************/

