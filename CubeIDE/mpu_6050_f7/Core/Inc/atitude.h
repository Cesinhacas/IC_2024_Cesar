/*
 * atitude.h
 *
 *  Created on: Aug 11, 2025
 *      Author: labt5
 */

#ifndef INC_ATITUDE_H_
#define INC_ATITUDE_H_

#include "stm32f7xx_hal.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

void cria_triad(double *v1, double *v2, double *r1, double *r2, double *r3);
void vet2mat(double *r1, double *r2, double *r3, double M[3][3]);
void atitude_determination(double Mref[3][3], double Mobs[3][3], double atitude[3][3]);
void send_atitude(double atitude[3][3]);

#endif /* INC_ATITUDE_H_ */
