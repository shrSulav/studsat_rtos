/**
  ******************************************************************************
  * @file    MCU_2_Final/gps.c 
  * @author  Karthik R
  * @version V1.0.0
  * @date    25-April-2016
  * @brief   C file to implement Inter Processor Communication btw CDHS and ADCs 
	*					 Controllers using UART4
  ******************************************************************************
  * @attention
	*		VCC						- VCC
	*		GND 					- GND
	*		USART2_Tx(PA2)	- Rx
	*		USART2_Rx(PA3)	- Tx
	*	UART @ 9600bps
  * ******************************************************************************  
  */ 

#include "gps.h"
#include "stdint.h" 
#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "ITM_Port.h"

//#include "ipc.h"

//----------------------------------------------------------------//
// void GetGPSValues(void)
//
// Description :
// This Function is used to read the GPS string from the GPS Module
// and to send the same to the CDHs Controller via IPC.
//---------------------------------------------------------------//

extern UART_HandleTypeDef huart2; //defined in main.c
char latt_int_hh[11],latt_int_dd[11],latt_int_mm[11],long_int_dd[11],long_int_mm[11],gps_date[3];
	char varData[80];
	char varData_gga[15][10],varData_rmc[15][10];
	char gps_flag[6];
		char c,val;
	uint8_t j=0,i=0,p=0,q=0;
 uint8_t iter=0,comp_val,status_gga,status_rmc;
 
//gps_value GetGPSValues(void)
//{
//	gps_value GPS = {13.1,'N',76.7,'E',680000,{2015,5,31},{1,35,3}} ;;

//	return GPS;
//}

gps_value GetGPSValues(void)
{
	status_gga=0; 
	status_rmc=0;
	gps_value GPS;
	HAL_StatusTypeDef magnm_status;
	uint8_t flag='0';
	const char gga_tag[]="GPGGA";
	const char rmc_tag[]="GPRMC";
	gps_flag[5]='\0';
	float32_t lat_dd, lat_mm;	//for conversion from latitude string to number
 	float32_t long_dd, long_mm;	//for conversion from longitude string to number
	
	while(status_gga==0 || status_rmc==0 )
	{
	
		//******************* read from GPS ***************************//
		while(flag!='x')
		{
			magnm_status = HAL_UART_Receive(&huart2, (uint8_t *)&c, (uint16_t)sizeof(c),1000); // Collect Char.
			//if(magnm_status == HAL_OK)
			{
				if(c=='$')
					{flag = '1', j =0;}
				else if(c=='\r' && flag == '1')
					{varData[j] = '\0'; j++; flag ='x';}
				else if(flag == '1')
					{varData[j] = c; j++;}
			}
		}
		//****************** read from GPS complete **************************//
		strncpy(gps_flag, varData,5);
		if(strcmp(gps_flag,gga_tag)==0)
		{
			//if(varData[44] != '0')
			{
				status_gga = 1;
				//printf("GGA Data acquired\n");
				for(i=0,p=0,q=0; varData[i]!='\0'; i++)
				{
					if(varData[i]!=',')
					{
						varData_gga[p][q] = varData[i];
						q++;
					}
					else
					{
						varData_gga[p][q] = '\0';
						p++;
						q=0;
					}
				}
	
				//UTC hh
				latt_int_hh[0] = varData_gga[1][0];
				latt_int_hh[1] = varData_gga[1][1];
				latt_int_hh[2] = '\0';
				GPS.time.hh = atoi(latt_int_hh);
				//UTC mm
				latt_int_hh[0] = varData_gga[1][2];
				latt_int_hh[1] = varData_gga[1][3];
				latt_int_hh[2] = '\0';
				GPS.time.mm = atoi(latt_int_hh);
				//UTC ss
				latt_int_hh[0] = varData_gga[1][4];
				latt_int_hh[1] = varData_gga[1][5];
				latt_int_hh[3] = varData_gga[1][6];
				latt_int_hh[4] = varData_gga[1][7];
				latt_int_hh[5] = varData_gga[1][8];
				latt_int_hh[6] = varData_gga[1][9];
				latt_int_hh[7] = '\0';
				GPS.time.ss = atof(latt_int_hh);
			
				//Latitude
				latt_int_dd[0] = varData_gga[2][0];
				latt_int_dd[1] = varData_gga[2][1];
				latt_int_dd[2] = '\0';
				lat_dd = atof(latt_int_dd);
				latt_int_dd[0] = varData_gga[2][2];
				latt_int_dd[1] = varData_gga[2][3];
				latt_int_dd[3] = varData_gga[2][4];
				latt_int_dd[4] = varData_gga[2][5];
				latt_int_dd[5] = varData_gga[2][6];
				latt_int_dd[6] = varData_gga[2][7];
				latt_int_dd[7] = '\0';
				lat_mm = atof(latt_int_dd);
				GPS.latitude_f32 = lat_dd + lat_mm/60 ;
				GPS.latitude_NS = varData_gga[3][0];
	
				//Longitude
				long_int_dd[0] = varData_gga[4][0];
				long_int_dd[1] = varData_gga[4][1];
				long_int_dd[2] = varData_gga[4][2];
				long_int_dd[3] = '\0';
				long_dd = atof(long_int_dd);
				long_int_mm[0] = varData_gga[4][3];
				long_int_mm[1] = varData_gga[4][4];
				long_int_mm[2] = varData_gga[4][5];
				long_int_mm[3] = varData_gga[4][6];
				long_int_mm[4] = varData_gga[4][7];
				long_int_mm[5] = varData_gga[4][8];
				long_int_mm[6] = varData_gga[4][9];
				long_int_mm[7] = '\0';
				long_mm = atof(long_int_mm);
				GPS.longitude_f32 = long_dd + long_mm/60 ;
				GPS.longitude_EW = varData_gga[5][0];
				GPS.altitude_f32 = atof(varData_gga[9]);
			
				if (status_rmc==0)
					flag = '0';
			}
		}
		
		else if(strcmp(gps_flag, rmc_tag) == 0)
		{
			//if(varData[17]=='A')
			{
				status_rmc=1;
				//printf("RMC Data acquired\n");
				for(i=0,p=0,q=0; varData[i]!='\0'; i++)
				{
					if(varData[i]!=',')
					{
						varData_rmc[p][q] = varData[i];
						q++;
					}
					else
					{
						varData_rmc[p][q] = '\0';
						p++;
						q=0;
					}
				}
			
			gps_date[0] = varData_rmc[9][0];
			gps_date[1] = varData_rmc[9][1];
			gps_date[2] = '\0';
			GPS.date.day = atoi(gps_date);
			
			gps_date[0] = varData_rmc[9][2];
			gps_date[1] = varData_rmc[9][3];
			gps_date[2] = '\0';
			GPS.date.month = atoi(gps_date);
			
			gps_date[0] = varData_rmc[9][4];
			gps_date[1] = varData_rmc[9][5];
			gps_date[2] = '\0';
			GPS.date.year = atoi(gps_date);
		}
		
		if (status_gga==0)
				flag='0';
		}
		
		else
		{
			flag = '0';
		}
	}

	return GPS;
}
