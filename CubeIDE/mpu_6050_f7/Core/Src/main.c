/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mpu_6050.h"
#include "hmc5883.h"
#include "atitude.h"
#include <stdio.h>
#include <string.h>
#include "calib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define NUM_LAT         32          /* faixas em elevação (-90°..+90°)  */
#define NUM_LON         36          /* faixas em azimute  (0°..360°)    */
#define TOTAL_GOMOS     (NUM_LAT * NUM_LON)

MPU_t sensor_data_accel;
HMC_t sensor_data_mag;

uint8_t occ_m[1152] = {0};
uint16_t m_cont = 0;
uint8_t occ_a[1152] = {0};
uint16_t a_cont = 0;
float mx_buf[TOTAL_GOMOS] = {0}, my_buf[TOTAL_GOMOS] = {0}, mz_buf[TOTAL_GOMOS] = {0};
float ax_buf[TOTAL_GOMOS] = {0}, ay_buf[TOTAL_GOMOS] = {0}, az_buf[TOTAL_GOMOS] = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// Preenchimento dos buffers
float norm(float* vet, float* unit)
{
	float n = sqrt(vet[0]*vet[0] + vet[1]*vet[1] + vet[2]*vet[2]);

	unit[0] = vet[0]/n;
	unit[1] = vet[1]/n;
	unit[2] = vet[2]/n;

	return n;
}

uint16_t sphere_index_from_unit(const float u[3])
{
    float phi   = atan2f(u[1], u[0]);  // [-pi, +pi]
    float theta = asinf(u[2]);         // [-pi/2, +pi/2]

    float lon_f = (phi + (float)3.1415) / (2.0f * (float)3.1415);
    float lat_f = (theta + (float)1.57079) / (float)3.1415;

    if (lon_f >= 1.0f) lon_f = nextafterf(1.0f, 0.0f);
    if (lat_f >= 1.0f) lat_f = nextafterf(1.0f, 0.0f);

    int lon_idx = (int)(lon_f * NUM_LON);
    int lat_idx = (int)(lat_f * NUM_LAT);

    if (lon_idx < 0) lon_idx = 0; else if (lon_idx >= NUM_LON) lon_idx = NUM_LON - 1;
    if (lat_idx < 0) lat_idx = 0; else if (lat_idx >= NUM_LAT) lat_idx = NUM_LAT - 1;

    return (uint16_t)(lat_idx * NUM_LON + lon_idx);
}

void add_reading(float mx, float my, float mz,
                 float ax, float ay, float az)
{
	uint8_t flag_a = 1, flag_m = 1;
    float m[3] = {mx, my, mz}, a[3] = {ax, ay, az};


    float u[3];
    if (norm(a, u) > 1.1)
    {
    	flag_a = 0;
    }
    uint16_t idx = sphere_index_from_unit(u);

    if (occ_a[idx] == 1)
    {
    	flag_a = 0;
    }

    if(flag_a ==1)
	{
		ax_buf[idx] = sensor_data_accel.accel_x;
		ay_buf[idx] = sensor_data_accel.accel_y;
		az_buf[idx] = sensor_data_accel.accel_z;

		occ_a[idx] = 1;
		a_cont ++;
	}

    norm(m, u);
	idx = sphere_index_from_unit(u);

	if (occ_m[idx] == 1)
	{
		flag_m = 0;
	}

	if(flag_m == 1)
	{
		mx_buf[idx] = sensor_data_mag.mag_x;
		my_buf[idx] = sensor_data_mag.mag_y;
		mz_buf[idx] = sensor_data_mag.mag_z;

		occ_m[idx] = 1;
		m_cont ++;
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t read[3] = {0};
//uint8_t who_I_am = 0;
uint8_t send[100] = {0};

uint8_t rx_data = 0;
uint8_t flag = 0;

double atitude[3][3];
double qua[4] = {0};

double v1[3] = {-0.107014, -0.158543, -0.090733}, v2[3] = {-0.017578, 0.031250, -1.036133};
double r1[3], r2[3], r3[3];
double Mref[3][3];

double w1[3], w2[3];
double s1[3], s2[3], s3[3];
double Mobs[3][3];

extern float mx_buf[1152], my_buf[1152], mz_buf[1152];
extern uint16_t a_cont, m_cont;

float p[9] = {1.009117353060959, 1.004116713879909, 0.922329558591251, -0.107366293055073, -0.214647257415079, 0.080163780683231, 0.010354797723851, -0.011935359803336, -0.004283295682346};
//float p[9] = {1.002704862343891, 1.007353828162894, 0.937386308228489, -0.117514288311261, -0.220090092807972, 0.073853367281422, 0.032440451405157, -0.018389446079523, -0.004882156264793};
float q[9] = {1.008005571427566, 0.998467621630478, 1.006259699083444, 0.024907087483453, -0.005376705308910, -0.021881232306800, 0.008676745628079, -0.002854314441100, 0.008449724038157};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  config_mpu6050(&hi2c2);
  config_mpu6050(&hi2c2);
  //HAL_I2C_Mem_Read(&hi2c2, mpu_6050_add, who_am_i_mpu, 1, &who_I_am, 1, 10);

  HAL_I2C_Mem_Read(&hi2c2, mpu_6050_add, pwr_mng1_mpu, 1, read, 1, 10);
  HAL_I2C_Mem_Read(&hi2c2, mpu_6050_add, sample_div_reg_mpu, 1, &read[1], 1, 10);
  HAL_I2C_Mem_Read(&hi2c2, mpu_6050_add, config_reg_mpu, 1, &read[2], 1, 10);

  read_id_hmc(&hi2c2);
  config_hmc(&hi2c2);

  HAL_Delay(2000);

  read_mpu6050(&hi2c2, &sensor_data_accel);
  read_hmc(&hi2c2, &sensor_data_mag);

  float norm = sqrtf(sensor_data_mag.mag_x_calib*sensor_data_mag.mag_x_calib + sensor_data_mag.mag_y_calib*sensor_data_mag.mag_y_calib + sensor_data_mag.mag_z_calib*sensor_data_mag.mag_z_calib);
  v1[0] = sensor_data_mag.mag_x_calib/norm;
  v1[1] = sensor_data_mag.mag_y_calib/norm;
  v1[2] = sensor_data_mag.mag_z_calib/norm;

  norm = sqrt(sensor_data_accel.accel_x*sensor_data_accel.accel_x + sensor_data_accel.accel_y*sensor_data_accel.accel_y + sensor_data_accel.accel_z*sensor_data_accel.accel_z);
  v2[0] = sensor_data_accel.accel_x/norm;
  v2[1] = sensor_data_accel.accel_y/norm;
  v2[2] = sensor_data_accel.accel_z/norm;


  cria_triad(v1, v2, r1, r2, r3);
  vet2mat(r1, r2, r3, Mref);

  //HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	read_mpu6050(&hi2c2, &sensor_data_accel);
	read_hmc(&hi2c2, &sensor_data_mag);

	norm = sqrt(sensor_data_mag.mag_x_calib*sensor_data_mag.mag_x_calib + sensor_data_mag.mag_y_calib*sensor_data_mag.mag_y_calib + sensor_data_mag.mag_z_calib*sensor_data_mag.mag_z_calib);
	w1[0] = sensor_data_mag.mag_x_calib/norm;
	w1[1] = sensor_data_mag.mag_y_calib/norm;
	w1[2] = sensor_data_mag.mag_z_calib/norm;

	norm = sqrt(sensor_data_accel.accel_x*sensor_data_accel.accel_x + sensor_data_accel.accel_y*sensor_data_accel.accel_y + sensor_data_accel.accel_z*sensor_data_accel.accel_z);
	w2[0] = sensor_data_accel.accel_x/norm;
	w2[1] = sensor_data_accel.accel_y/norm;
	w2[2] = sensor_data_accel.accel_z/norm;

	cria_triad(w1, w2, s1, s2, s3);
	vet2mat(s1, s2, s3, Mobs);
	atitude_determination(Mref, Mobs, atitude);

	HAL_UART_Receive(&huart2, &rx_data, 1, 100);

	if(rx_data == 'd')
	{
		rx_data = 0;
		flag = 1;
	}
	if(rx_data == 'c')
	{
		rx_data = 0;
		flag = 2;
	}
	if(rx_data == 'g')
	{
		rx_data = 0;
		flag = 3;
	}
	if(rx_data == '@')
	{
		rx_data = 0;
		flag = 4;
	}
	if(rx_data == 'p')
	{
		rx_data = 0;
		flag = 5;
	}
	if(rx_data == 'm')
	{
		rx_data = 0;
		flag = 6;
	}
	if(rx_data == 'a')
	{
		rx_data = 0;
		flag = 7;
	}

	if(flag == 2)
	{
		HAL_TIM_Base_Stop_IT(&htim2);
		//ETS(mx_buf, my_buf, mz_buf, p);
		for(uint8_t i = 0; i < 10; i++)
		{
			sprintf((char*)send, "%f\n", p[i]);
			HAL_UART_Transmit(&huart2, send, strlen((char*)send), 1);
		}
		flag = 0;
		//HAL_TIM_Base_Start_IT(&htim2);
	}
	if(flag == 3)
	{
		sprintf((char*)send, "%d\n\r", m_cont);
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 1);
		flag = 0;
	}
	if(flag == 4)
	{
		//HAL_TIM_Base_Start_IT(&htim2);
		flag = 0;
		//sprintf((char*)send, "%d %d %d %d %d %d", sensor_data_mag.mag_x_nude, sensor_data_mag.mag_y_nude, sensor_data_mag.mag_z_nude, sensor_data_accel.accel_x_nude, sensor_data_accel.accel_y_nude, sensor_data_accel.accel_z_nude);
		//HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);

		mat2quaternion(atitude, qua);
		sprintf((char*)send, "%f, %f, %f, %f\n\r", qua[0], qua[1], qua[2], qua[3]);
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);
	}
	if(flag == 5)
	{
		HAL_TIM_Base_Stop_IT(&htim2);
		flag = 0;
	}
	if(flag == 6)
	{
		HAL_TIM_Base_Stop_IT(&htim2);
		sprintf((char*)send, "%d\n\r", m_cont);
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 1);

		for(uint16_t i = 0; i < TOTAL_GOMOS; i++)
		{
			sprintf((char*)send, "%f, %f, %f\n\r", mx_buf[i], my_buf[i], mz_buf[i]);
			HAL_UART_Transmit(&huart2, send, strlen((char*)send), 20);
		}

		sprintf((char*)send, "Fim da trasmissão dos dados\n\r");
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 50);

		flag = 0;
	}
	if(flag == 7)
	{
		HAL_TIM_Base_Stop_IT(&htim2);
		sprintf((char*)send, "%d\n\r", a_cont);
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 1);

		for(uint16_t i = 0; i < TOTAL_GOMOS; i++)
		{
			sprintf((char*)send, "%f, %f, %f\n\r", ax_buf[i], ay_buf[i], az_buf[i]);
			HAL_UART_Transmit(&huart2, send, strlen((char*)send), 20);
		}

		sprintf((char*)send, "Fim da trasmissão dos dados\n\r");
		HAL_UART_Transmit(&huart2, send, strlen((char*)send), 50);

		flag = 0;
	}

	//Implementar o envia dado do mag e o envia dado do accel
	//Implementar o start do TIM.

	if(flag == 1)
	{
		send_atitude(atitude);

		//Código para determinação de atitude
		/*w1[0] = sensor_data_mag.mag_x;
		w1[1] = sensor_data_mag.mag_y;
		w1[2] = sensor_data_mag.mag_z;

		w2[0] = sensor_data_accel.accel_x;
		w2[1] = sensor_data_accel.accel_y;
		w2[2] = sensor_data_accel.accel_z;

		cria_triad(w1, w2, s1, s2, s3);
		vet2mat(s1, s2, s3, Mobs);
		atitude_determination(Mref, Mobs, atitude);

		send_atitude(atitude);*/
		flag = 0;
	}

	if(m_cont >= 1152)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	}
	if(a_cont >= 1152)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	read_mpu6050(&hi2c2, &sensor_data_accel);
	read_hmc(&hi2c2, &sensor_data_mag);

	add_reading(sensor_data_mag.mag_x_calib, sensor_data_mag.mag_y_calib, sensor_data_mag.mag_z_calib, sensor_data_accel.accel_x_calib, sensor_data_accel.accel_y_calib, sensor_data_accel.accel_z_calib);
	/*double norm = sqrt(sensor_data_mag.mag_x_calib*sensor_data_mag.mag_x_calib + sensor_data_mag.mag_y_calib*sensor_data_mag.mag_y_calib + sensor_data_mag.mag_z_calib*sensor_data_mag.mag_z_calib);
	w1[0] = sensor_data_mag.mag_x_calib/norm;
	w1[1] = sensor_data_mag.mag_y_calib/norm;
	w1[2] = sensor_data_mag.mag_z_calib/norm;

	w2[0] = sensor_data_accel.accel_x;
	w2[1] = sensor_data_accel.accel_y;
	w2[2] = sensor_data_accel.accel_z;

	cria_triad(w1, w2, s1, s2, s3);
	vet2mat(s1, s2, s3, Mobs);
	atitude_determination(Mref, Mobs, atitude);

	send_atitude(atitude);*/

	//mat2quaternion(atitude, qua);
	//sprintf((char*)send, "%f, %f, %f, %f\n\r", qua[0], qua[1], qua[2], qua[3]);
	//HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);



	sprintf((char*)send, "%f, %f, %f\n\r", sensor_data_accel.accel_x, sensor_data_accel.accel_y, sensor_data_accel.accel_z);
	HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);

	//sprintf((char*)send, "%f, %f, %f\n\r", sensor_data_mag.mag_x_calib, sensor_data_mag.mag_y_calib, sensor_data_mag.mag_z_calib);
	//HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);

	sprintf((char*)send, "%f, %f, %f\n\r", sensor_data_mag.mag_x, sensor_data_mag.mag_y, sensor_data_mag.mag_z);
	HAL_UART_Transmit(&huart2, send, strlen((char*)send), 100);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rx_data == '$')
	{
		flag = 1;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
