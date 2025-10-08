/*
 * mpu_6050.c
 *
 *  Created on: Feb 14, 2025
 *      Author: labt5
 */
#include "mpu_6050.h"
#include <math.h>

void config_mpu6050(I2C_HandleTypeDef *h)
{
	uint8_t data;
	data = 0;
	HAL_I2C_Mem_Write(h, mpu_6050_add, config_reg_mpu, 1, &data, 1, 10);
	HAL_I2C_Mem_Write(h, mpu_6050_add, pwr_mng1_mpu, 1, &data, 1, 10);
	data = 0x18;
	HAL_I2C_Mem_Write(h, mpu_6050_add, config_accel_reg_mpu, 1, &data, 1, 10); //0x08 => Configura para 4G de range
	data = 0x08;
	HAL_I2C_Mem_Write(h, mpu_6050_add, config_gyro_reg_mpu, 1, &data, 1, 10); //0x08 => Configura para 500°/s
	data = 0x07;
	HAL_I2C_Mem_Write(h, mpu_6050_add, sample_div_reg_mpu, 1, &data, 1, 10);
}

void read_mpu6050(I2C_HandleTypeDef *h, MPU_t *Data)
{
	HAL_I2C_Mem_Read(h, mpu_6050_add, accel_xout_h, 1, Data->accel_data_nude, 6, 50);
	//HAL_I2C_Mem_Read(h, mpu_6050_add, gyro_zout_h, 1, Data->gyro_data_nude, 2, 25);

	/*
	DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);*/

	Data->accel_x_nude = (int16_t)((Data->accel_data_nude[0] << 8) | Data->accel_data_nude[1]);
	Data->accel_y_nude = (int16_t)((Data->accel_data_nude[2] << 8) | Data->accel_data_nude[3]);
	Data->accel_z_nude = (int16_t)((Data->accel_data_nude[4] << 8) | Data->accel_data_nude[5]);

	//Data->gyro_z_nude = (int16_t)((Data->gyro_data_nude[0] << 8) | Data->gyro_data_nude[1]);

	Data->accel_x = ((double)Data->accel_x_nude)/2048;
	Data->accel_y = ((double)Data->accel_y_nude)/2048;
	Data->accel_z = ((double)Data->accel_z_nude)/2048;

	Data->accel_x_calib = (Data->accel_x - q[3])/q[0];
	Data->accel_y_calib = ((Data->accel_y - q[4])/q[1] - Data->accel_x_calib * sin(q[6]))/cos(q[6]);
	Data->accel_z_calib = (Data->accel_z - q[5])/q[2] - Data->accel_x_calib * sin(q[7]) * cos(q[9]) - Data->accel_y_calib * sin(q[8])/(cos(q[7]) * cos(q[8]));

	//Data->gyro_z = ((double)Data->gyro_z_nude)/65.5;
}
