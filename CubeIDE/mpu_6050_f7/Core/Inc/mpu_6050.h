/*
 * mpu_6050.h
 *
 *  Created on: Feb 14, 2025
 *      Author: labt5
 */

#ifndef INC_MPU_6050_H_
#define INC_MPU_6050_H_

#include "stm32f7xx_hal.h"

extern float q[9];

#define mpu_6050_add 0xD0 //write = 0
#define who_am_i_mpu 0x75

#define config_reg_mpu 0x1A
#define config_accel_reg_mpu 0x1C
#define config_gyro_reg_mpu 0x1B

#define pwr_mng1_mpu 0x6B
#define sample_div_reg_mpu 0x19

#define accel_xout_h 0x3B
#define gyro_zout_h 0x47

#define mst_ctrl_mpu 0x24

typedef struct
{
	uint8_t accel_data_nude[6];

	int16_t accel_x_nude;
	int16_t accel_y_nude;
	int16_t accel_z_nude;

	double accel_x;
	double accel_y;
	double accel_z;

	double accel_x_calib;
	double accel_y_calib;
	double accel_z_calib;

	/*uint8_t gyro_data_nude[6];

	int16_t gyro_x_nude;
	int16_t gyro_y_nude;
	int16_t gyro_z_nude;

	double gyro_x;
	double gyro_y;
	double gyro_z;*/

}MPU_t;


void config_mpu6050(I2C_HandleTypeDef *h);
void read_mpu6050(I2C_HandleTypeDef *h, MPU_t *Data);

#endif /* INC_MPU_6050_H_ */
