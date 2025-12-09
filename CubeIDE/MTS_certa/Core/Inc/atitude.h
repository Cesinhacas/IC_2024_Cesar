/*
 * atitude.h
 *
 *  Created on: Nov 27, 2025
 *      Author: labt5
 */

#ifndef INC_ATITUDE_H_
#define INC_ATITUDE_H_

#include "stm32f7xx_hal.h"


void TRIAD(double *v1_ref, double *v2_ref, double *v1_obs, double *v2_obs, double *q, double sig1, double sig2, double R[3][3]);
void cria_triad(double *v1, double *v2, double *r1, double *r2, double *r3);

#endif /* INC_ATITUDE_H_ */
