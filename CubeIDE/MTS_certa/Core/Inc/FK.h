/*
 * FK.h
 *
 *  Created on: Nov 27, 2025
 *      Author: labt5
 */

#ifndef INC_FK_H_
#define INC_FK_H_

#include "stm32f7xx_hal.h"

void inverter_matriz(double matriz[3][3], double inversa[3][3]);
void FK_prop(double *u_gyro, double Dt, double PT_est[6][6], double *x_est, double *x_prop, double PT_prop[6][6]);
void FK_estimador(double *x_prop, double PT_prop[6][6], double *q_obs, double R[3][3], uint8_t iteracao, double *x_est, double PT_est[6][6], double P_est[7][7]);
void prepara();


#endif /* INC_FK_H_ */
