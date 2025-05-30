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
#include "fatfs.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "calib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



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
double mx[1112] = {0}, my[1112] = {0}, mz[1112] = {0};
double p1[9] = {0}, p0[9] = {0};
uint8_t passos_NLLS = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  char file_read[20] = {0};
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
  MX_FATFS_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  uint32_t start_time = 0;
  uint16_t file_cont = 1;
  double ETS_time = 0, NLLS_time = 0;

  FATFS fs;
  FRESULT res;

  // Monta o sistema de arquivos na unidade lógica "0:"
  res = f_mount(&fs, "0:", 1);
  if (res != FR_OK) {
      printf("Falha ao montar o sistema de arquivos: %d\n", res);
      Error_Handler(); // ou retorne um erro
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if(file_cont >= 3001)
	{
		return 1;
	}

	sprintf(file_read, "0:/DATA/run%d.txt", file_cont);  // Prefixo de volume (0:) é comum no FatFs

	FIL fil;
	FRESULT res;

	res = f_open(&fil, file_read, FA_READ);
	if (res != FR_OK)
	{
		return 1;
	}

	char line[61340];
	UINT br; // Bytes lidos

	double *linhas[] = {mx, my, mz};  // Vetor de ponteiros para facilitar o acesso

	for (int i = 0; i < 3; i++)
	{
		// lê uma linha completa (até '\n' ou fim do buffer)
		int line_pos = 0;
		char ch;
		do {
			res = f_read(&fil, &ch, 1, &br);
			if (res != FR_OK || br == 0) {
				return 1;
			}
			line[line_pos++] = ch;
		} while (ch != '\n' && line_pos < sizeof(line)-1);
		line[line_pos] = '\0';

		char *token = strtok(line, ",");
		int j = 0;

		while (token != NULL && j < 1112)
		{
			linhas[i][j] = strtof(token, NULL);
			token = strtok(NULL, ",");
			j++;
		}

		if (j != 1112)
		{
			return 1;
		}
	}

	f_close(&fil);

	start_time = HAL_GetTick();
	ETS(mx, my, mz, p1);
	ETS_time = HAL_GetTick() - start_time;

	start_time = HAL_GetTick();
	passos_NLLS = NLLS(mx, my, mz, p0);
	NLLS_time = HAL_GetTick() - start_time;


	sprintf(file_read, "0:/RES/run%d.txt", file_cont);
	res = f_open(&fil, file_read, FA_WRITE | FA_CREATE_ALWAYS);
	if (res != FR_OK)
	{
		return 1;
	}

	char out_line[128];
	UINT bw;

	for (int i = 0; i < 9; i++) {
		sprintf(out_line, "%f, %f\n", p1[i], p0[i]);
		f_write(&fil, out_line, strlen(out_line), &bw);
	}

	sprintf(out_line, "%f, %f\n", ETS_time, NLLS_time);
	f_write(&fil, out_line, strlen(out_line), &bw);

	sprintf(out_line, "0, %u\n", passos_NLLS);
	f_write(&fil, out_line, strlen(out_line), &bw);

	f_close(&fil);

	file_cont++;
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
