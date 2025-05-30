/*
 * calib.h
 *
 *  Created on: Jan 22, 2025
 *      Author: labt5
 */

#ifndef INC_CALIB_H_
#define INC_CALIB_H_

#include "stm32f7xx_hal.h"

#define N 9
#define tam 1112

void ETS(double *mx, double *my, double *mz, double *p);
uint8_t NLLS(double *mx, double *my, double *mz, double *p);

void inverter_matriz(double matriz[N][N], double inversa[N][N]);

#endif /* INC_CALIB_H_ */
