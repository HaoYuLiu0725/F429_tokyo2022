/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * @project		: F429_tokyo2022
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <main.hpp>
#include <robot.h>
#include <rosserial.h>
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
Robot robot;
Speed received_vel;
Speed odom_vel;
double target_wheel_w[4] = {0};
double LPF_output[4] = {0};
int32_t CNT_diff[4] = {0};
double OMEGA[4] = {0};
double duty[4] = {0};
/*for encoder test to get PID value*/
//double omega[1000];
//int x = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void motor_PID_test(int motor){
	robot.pid[motor].setSetpoint(target_wheel_w[motor]);	//set PID target
	CNT_diff[motor] = robot.encoder_[motor].readDelta();	//read encoder counter difference
	OMEGA[motor] = robot.diff_to_omega(CNT_diff[motor]);	//from counter difference to omega
	robot.pid[motor].setFeedback(OMEGA[motor]);				//set PID feedback
	duty[motor] = robot.pid[motor].clacOutput();			//calculate duty cycle
	robot.motor_[motor].writeDuty(duty[motor]);				//write duty cycle to VNH5019
}

void speed_init(){
	received_vel.vx = 0;
	received_vel.vy = 0;
	received_vel.w  = 0;
	odom_vel.vx = 0;
	odom_vel.vy = 0;
	odom_vel.w	= 0;
}

void get_odom_vel(){
	odom_vel.vx = robot.kn_.robot_speed.vx_;
	odom_vel.vy = robot.kn_.robot_speed.vy_;
	odom_vel.w  = robot.kn_.robot_speed.w_;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim7) {	/* HIGH FREQ EVENT : 1kHz*/
		robot.kn_.inverseKinematic(received_vel.vx, received_vel.vy, received_vel.w); //from target robot speed to 4 wheel's omega
		for (int i = 0; i < 4; i++){
			target_wheel_w[i] = robot.kn_.wheel_speed_[i]; 			//get target wheel speed
//			LPF_output[i] = robot.LPF_.update(target_wheel_w[i]);	//Low Pass Filter
			robot.pid[i].setSetpoint(target_wheel_w[i]); 			//set PID target
			CNT_diff[i] = robot.encoder_[i].readDelta();			//read encoder counter difference
			OMEGA[i] = robot.diff_to_omega(CNT_diff[i]);			//from counter difference to omega
			robot.pid[i].setFeedback(OMEGA[i]);						//set PID feedback
			duty[i] = robot.pid[i].clacOutput();					//calculate duty cycle
			robot.motor_[i].writeDuty(duty[i]);						//write duty cycle to VNH
		}
		robot.kn_.forwardKinematic(OMEGA[0], OMEGA[1], OMEGA[2], OMEGA[3]);
		get_odom_vel();
		odom_store();
	}
	else if(htim == &htim6){	/* odometry publish FREQ : 100Hz*/
		odom_store();
		odom_pub();
	}
}
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

  speed_init(); //********* for manual test **********
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM12_Init();
  MX_TIM9_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM7_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  robot.init();
  rosserial_setup();
   while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	   // UART test:
//	   uint8_t num = 10;
//	   HAL_UART_Transmit(&huart1, &num, 1, 2);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
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
