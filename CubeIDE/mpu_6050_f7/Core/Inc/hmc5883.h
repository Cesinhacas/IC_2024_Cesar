/*
 * hmc5883.h
 *
 *  Created on: Aug 11, 2025
 *      Author: labt5
 */

#ifndef INC_HMC5883_H_
#define INC_HMC5883_H_

#include "stm32f7xx_hal.h"

#define hmc_addr		0x3C

#define hmc_x_high		0x03
#define hmc_conf_a		0x00 //Oversample; Data Output Rate; Measurement Mode
#define hmc_conf_b		0x01 //Configura o ganho
#define	hmc_mode_reg	0x02
#define hmc_status_reg	0x09 //RDY; LOCK
#define hmc_id_a		0x0A //Deve ser 0x48 ou 72
#define hmc_id_b		0x0B //Deve ser 0x34 ou 52
#define hmc_id_c		0x0C //Deve ser 0x33 ou 51

typedef struct
{
	uint8_t mag_data_nude[6];

	int16_t mag_x_nude;
	int16_t mag_y_nude;
	int16_t mag_z_nude;

	double mag_x;
	double mag_y;
	double mag_z;
}HMC_t;

void config_hmc(I2C_HandleTypeDef *h);
void read_hmc(I2C_HandleTypeDef *h, HMC_t *Data);
void read_id_hmc(I2C_HandleTypeDef *h);

#endif /* INC_HMC5883_H_ */
