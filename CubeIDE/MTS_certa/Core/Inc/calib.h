/*
 * calib.h
 *
 *  Created on: Jan 22, 2025
 *      Author: labt5
 */

#ifndef INC_CALIB_H_
#define INC_CALIB_H_

#include "stm32f7xx_hal.h"

#define N 				9
#define tam 			1152

extern uint8_t occ_m[1152], m_cont;
extern uint8_t occ_a[1152], a_cont;
extern float mx_buf, my_buf, mz_buf;
extern float ax_buf, ay_buf, az_buf;

void ETS(float *mx, float *my, float *mz, float *p);
uint8_t NLLS(float *mx, float *my, float *mz, float *p);

void inverter_matriz(float matriz[N][N], float inversa[N][N]);

float norm(float* vet, float* unit);
uint16_t sphere_index_from_unit(const float u[3]);
void add_reading(float mx, float my, float mz, float ax, float ay, float az);

#endif /* INC_CALIB_H_ */
