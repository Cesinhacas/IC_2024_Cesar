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
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "calib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
union calib_t{
	uint8_t inteiro[4];
	float flutuante;
};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float mx[tam] = {0}, my[tam] = {0}, mz[tam] = {0};
union calib_t mx_[tam] = {0}, my_[tam] = {0}, mz_[tam] = {0};
float Ht_H[N][N], Ht_e[N], inv[N][N], mul_mat[N][tam];
float p1[9] = {0}, p0[9] = {0};
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
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  union calib_t param[9], time;
  uint32_t start_time = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10));
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);

	  for(uint16_t i = 0; i<=tam; i++)
	  {
		  HAL_SPI_Receive(&hspi2, mx_[i].inteiro, 4, 1000);
	  }
	  for(uint16_t i = 0; i<=tam; i++)
	  {
		  HAL_SPI_Receive(&hspi2, my_[i].inteiro, 4, 1000);
	  }
	  for(uint16_t i = 0; i<=tam; i++)
	  {
		  HAL_SPI_Receive(&hspi2, mz_[i].inteiro, 4, 1000);
	  }
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);

	  for(uint16_t i = 0; i<=tam; i++)
	  {
		  mx[i] = mx_[i].flutuante;
		  my[i] = my_[i].flutuante;
		  mz[i] = mz_[i].flutuante;
	  }

	  /*start_time = HAL_GetTick();
	  ETS(mx, my, mz, p1);
	  time.flutuante = HAL_GetTick() - start_time;*/

	  start_time = HAL_GetTick();
	  passos_NLLS = NLLS(mx, my, mz, p1);
	  time.flutuante = HAL_GetTick() - start_time;



	  for(uint8_t i = 0; i < 10; i++)
	  {
		  param[i].flutuante = p1[i];
	  }

	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);

	  for(uint8_t i = 0; i < 10; i++)
	  {
		  HAL_SPI_Transmit(&hspi2, param[i].inteiro, 4, HAL_MAX_DELAY);
	  }
	  HAL_SPI_Transmit(&hspi2, time.inteiro, 4, HAL_MAX_DELAY);
	  HAL_SPI_Transmit(&hspi2, &passos_NLLS, 1, HAL_MAX_DELAY);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
