/*
 * hmc5883.c
 *
 *  Created on: Aug 11, 2025
 *      Author: labt5
 */
#include "hmc5883.h"

void config_hmc(I2C_HandleTypeDef *h)
{
	uint8_t data;
	data = 0x78;
	HAL_I2C_Mem_Write(h, hmc_addr, hmc_conf_a, 1, &data, 1, 10); //0x18 => OSR = 1; Data Rate = 75 Hz; Measurement Mode = continuous
	data = 0x00;
	HAL_I2C_Mem_Write(h, hmc_addr, hmc_conf_b, 1, &data, 1, 10); //0x00 => Sensor Field Range = + ou - 0.88 Ga
	data = 0x00;
	HAL_I2C_Mem_Write(h, hmc_addr, hmc_mode_reg, 1, &data, 1, 10); //0x00 => Continuous mode
}

void read_id_hmc(I2C_HandleTypeDef *h)
{
	uint8_t id[3] = {0};
	HAL_I2C_Mem_Read(h, hmc_addr, hmc_id_a, 1, id, 3, 50);
	id[3] = 0;
}

void read_hmc(I2C_HandleTypeDef *h, HMC_t *Data)
{
	HAL_I2C_Mem_Read(h, hmc_addr, hmc_x_high, 1, Data->mag_data_nude, 6, 50);


	Data->mag_x_nude = (int16_t)((Data->mag_data_nude[0] << 8) | Data->mag_data_nude[1]);
	Data->mag_z_nude = (int16_t)((Data->mag_data_nude[2] << 8) | Data->mag_data_nude[3]);
	Data->mag_y_nude = (int16_t)((Data->mag_data_nude[4] << 8) | Data->mag_data_nude[5]);

	Data->mag_x = ((double)Data->mag_x_nude)/1370;
	Data->mag_y = ((double)Data->mag_y_nude)/1370;
	Data->mag_z = ((double)Data->mag_z_nude)/1370;

	Data->mag_x_calib = (Data->mag_x - p[3])/p[0];
	Data->mag_y_calib = ((Data->mag_y - p[4])/p[1] - Data->mag_x_calib * sin(p[6]))/cos(p[6]);
	Data->mag_z_calib = (Data->mag_z - p[5])/p[2] - Data->mag_x_calib * sin(p[7]) * cos(p[9]) - Data->mag_y_calib * sin(p[8])/(cos(p[7]) * cos(p[8]));
}
