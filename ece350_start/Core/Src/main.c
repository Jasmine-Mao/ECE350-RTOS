\/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include <stdio.h> //You are permitted to use this library, but currently only printf is implemented. Anything else is up to you!

#define TID_NULL 0 //predefined Task ID for the NULL task
#define MAX_TASKS 16 //maximum number of tasks in the system
#define STACK_SIZE 0x200 //min. size of each task’s stack
#define DORMANT 0 //state of terminated task
#define READY 1 //state of task that can be scheduled but is not running
#define RUNNING 2 //state of running task 

typedef unsigned int U32;
typedef unsigned short U16;
typedef char U8;
typedef unsigned int task_t;

MAX_STACK_SIZE = 0x4000;
MAIN_STACK_SIZE = 0x400;
THREAD_STACK_SIZE = 0x400;


uint32_t* MSP_INIT_VAL = *(uint32_t**)0x0;
printf("MSP Init is: %p\r\n",MSP_INIT_VAL); //note the %p to print a



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  current_task
  /* MCU Configuration: Don't change this or the whole chip won't work!*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* MCU Configuration is now complete. Start writing your code below this line */

  SVC_Handler();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  printf("Hello, world!\r\n");
    printf("Hello, world!\r\n");
	  printf("MSP Init is: %p\r\n",MSP_INIT_VAL);
	  //MSP Init is: 0x20018000

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

