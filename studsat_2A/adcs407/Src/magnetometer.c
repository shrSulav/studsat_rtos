#include "magnetometer.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h" 

/* ************************************************** */
void magnm_data_parse(char* data, float32_t magnm_gauss[3]);

/* ************************************************** */

extern UART_HandleTypeDef huart3;

char data[28];// = "- 1,940    5,173  - 2,121  ";//test data
extern const float32_t Bg;
extern const float32_t g2t;

/*************************************** Magnetometer_Commands ***************************************************/

/*
	Send a single character via USART3
*/
void send(char c)
{
	HAL_UART_Transmit(&huart3,(uint8_t *) &c,1,50);
}

/*
	Enable Write to magnetometer
*/
void write_EN(void)
{
	send('*');
	send('9');
	send('9');
	send('w');
	send('e');
	send(13);
}

/*
	Output Readings in BCD ASCII Format (Default)
	Call write_EN() before calling this function
*/
void ASCII_On(void)
{
	send('*');
	send('9');
	send('9');
	send('a');
	send(13);
}

/*
	Output Readings in Signed 16-bit Bianary Format
	Call write_EN() before calling this function
*/
void Binary_On(void)
{
	send('*');
	send('9');
	send('9');
	send('b');
	send(13);
}

/*
	Polled – Output a Single Sample (Default)
	DO NOT call write_EN() before calling this function
*/
void single_op(void)
{
	send('*');
	send('9');
	send('9');
	send('p');
	send(13);
}

/*
	Continuous – Output Readings at Sample Rate
	DO NOT call write_EN() before calling this function
*/
void continuous_op(void)
{
	send('*');
	send('9');
	send('9');
	send('c');
	send(13);
}

/*
	Stops Continuous Readings	
	DO NOT call write_EN() before calling this function
*/
void stop_con_op(void)
{
	send(27);
}

/*
	Set BAUD Rate to 9600 
	Call write_EN() before calling this function
*/
void set_baud_9600(void)
{
	send('*');
	send('9');
	send('9');
	send('!');
	send('b');
	send('r');
	send('=');
	send('s');
	send(13);
}

/*	
	Set BAUD Rate to 19200 
	Call write_EN() before calling this function
*/
void set_baud_19200(void)
{
	send('*');
	send('9');
	send('9');
	send('!');
	send('b');
	send('r');
	send('=');
	send('f');
	send(13);
}

/*
	Change All Command Parameter Settings to Factory Default Values	
	Call write_EN() before calling this function
*/
void set_factory_default(void)
{
	send('*');
	send('9');
	send('9');
	send('d');
	send(13);
}

/*
	This writes all parameter settings to EEPROM. These values will be automatically restored upon power-up. 
	Call write_EN() before calling this function
*/
void store_parameters(void)
{
	send('*');
	send('9');
	send('9');
	send('s');
	send('p');
	send(13);
}

/*
	Change All Command Parameter Settings to the Last User Stored Values in the EEPROM
	Call write_EN() before calling this function
*/
void restore_settings(void)
{
	send('*');
	send('9');
	send('9');
	send('r');
	send('s');
	send('t');
	send(13);
}


void read_magnm_data (float32_t magnm_gauss[3])
{ 
	char data[28];
//	magnm_gauss[0] = 0.03;
//	magnm_gauss[1] = 0.04;
//	magnm_gauss[2] = 0.07;
	single_op();
  HAL_Delay(20);
	HAL_UART_Receive(&huart3,(uint8_t *)data,28,50);
	
  magnm_data_parse(data, magnm_gauss);
}

/******************** Magnetometer Data Parser *************************************/
void magnm_data_parse(char *data, float32_t magnm_gauss[3])
{
float32_t x,y,z; //parsed data to be mapped
	
char data_mod[25];
	
uint8_t i=0,j=0;

//data[27] = 13;//testing 
	
//remove comma's and repalce spaces with zero's store in a different string
while(i != 28)
{
 if((data[i]==' ')&&((i!=7)&&(i!=8)&&(i!=16)&&(i!=17)&&(i!=25)&&(i!=26)))
  {
   data_mod[j]='0';
   j++;
  }

 else if(data[i]!=',')
 {
  data_mod[j]=data[i];
  j++;
 }

i++;
}


//reading x,y,z data from formatted string 
sscanf(data_mod,"%f  %f  %f",&x,&y,&z);

//mapping x,y,z data to mag field values in Tesla
magnm_gauss[0] = map(x,-30000.0,30000.0,-2.0,2.0)*g2t;
magnm_gauss[1] = map(y,-30000.0,30000.0,-2.0,2.0)*g2t;
magnm_gauss[2] = map(z,-30000.0,30000.0,-2.0,2.0)*g2t;

}


float32_t map (float32_t x,float32_t in_min,float32_t in_max,float32_t out_min,float32_t out_max)
{
 return ((x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min);
}


/********************************************** EOF ***********************************************************/
