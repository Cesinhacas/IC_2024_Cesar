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
#define tam 278

//extern float Ht_H[N][N], Ht_e[N], inv[N][N], mul_mat[N][tam];

void ETS(float *mx, float *my, float *mz, float *p);
uint8_t NLLS(float *mx, float *my, float *mz, float *p);

void inverter_matriz(float matriz[N][N], float inversa[N][N]);

#endif /* INC_CALIB_H_ */
