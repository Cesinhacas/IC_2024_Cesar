/*
 * atitude.c
 *
 *  Created on: Aug 11, 2025
 *      Author: labt5
 */

#include "atitude.h"

void cria_triad(double *v1, double *v2, double *r1, double *r2, double *r3)
{
	double vec_prod[3];
	vec_prod[0] = v1[1]*v2[2] - v1[2]*v2[1];
	vec_prod[1] = v1[2]*v2[0] - v1[0]*v2[2];
	vec_prod[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double norm = sqrt(vec_prod[0]*vec_prod[0] + vec_prod[1]*vec_prod[1] + vec_prod[2]*vec_prod[2]);

	r3[0] = v1[1]*vec_prod[2] - v1[2]*vec_prod[1];
	r3[1] = v1[2]*vec_prod[0] - v1[0]*vec_prod[2];
	r3[2] = v1[0]*vec_prod[1] - v1[1]*vec_prod[0];

	for(uint8_t i = 0; i < 3; i++)
	{
		r1[i] = v1[i];
		r2[i] = vec_prod[i]/norm;
		r3[i] /= norm;
	}
}

void vet2mat(double *r1, double *r2, double *r3, double M[3][3])
{
	for(uint8_t i = 0; i < 3; i++)
	  {
		  M[0][i] = r1[i];
		  M[1][i] = r2[i];
		  M[2][i] = r3[i];
	  }
}

void atitude_determination(double Mref[3][3], double Mobs[3][3], double atitude[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			atitude[i][j] = 0;
	        for (int k = 0; k < 3; k++)
	        {
	        	atitude[i][j] += Mobs[i][k] * Mref[j][k];
	        }
	     }
	  }
}

void send_atitude(double atitude[3][3])
{
	uint8_t data_to_send[50];

	sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[0][0], atitude[0][1], atitude[0][2]);
	HAL_UART_Transmit(&huart2, data_to_send, strlen((char*)data_to_send), 100);

	sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[1][0], atitude[1][1], atitude[1][2]);
	HAL_UART_Transmit(&huart2, data_to_send, strlen((char*)data_to_send), 100);

	sprintf((char*)data_to_send, "%f, %f, %f\n", atitude[2][0], atitude[2][1], atitude[2][2]);
	HAL_UART_Transmit(&huart2, data_to_send, strlen((char*)data_to_send), 100);
}
