/*
 * calib.h
 *
 *  Created on: Jan 22, 2025
 *      Author: labt5
 */

#ifndef INC_CALIB_H_
#define INC_CALIB_H_

#define N 9
#define tam 572

void ETS(float *mx, float *my, float *mz, float *p);
int NLLS(float *mx, float *my, float *mz, float *p);

void inverter_matriz(float matriz[N][N], float inversa[N][N]);

#endif /* INC_CALIB_H_ */
