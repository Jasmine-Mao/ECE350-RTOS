/* USER CODE BEGIN Header */
/**
    ******************************************************************************
    * @file        stm32f4xx_it.c
    * @brief     Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*                     Cortex-M4 Processor Interruption and Exception Handlers                    */
/******************************************************************************/
/**
    * @brief This function handles Non maskable interrupt.
    */
void NMI_Handler(void)
{
    /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

    /* USER CODE END NonMaskableInt_IRQn 0 */
    /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
    while (1)
    {
    }
    /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
    * @brief This function handles Hard fault interrupt.
    */
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}

/**
    * @brief This function handles Memory management fault.
    */
void MemManage_Handler(void)
{
    /* USER CODE BEGIN MemoryManagement_IRQn 0 */

    /* USER CODE END MemoryManagement_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
        /* USER CODE END W1_MemoryManagement_IRQn 0 */
    }
}

/**
    * @brief This function handles Pre-fetch fault, memory access fault.
    */
void BusFault_Handler(void)
{
    /* USER CODE BEGIN BusFault_IRQn 0 */

    /* USER CODE END BusFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_BusFault_IRQn 0 */
        /* USER CODE END W1_BusFault_IRQn 0 */
    }
}

/**
    * @brief This function handles Undefined instruction or illegal state.
    */
void UsageFault_Handler(void)
{
    /* USER CODE BEGIN UsageFault_IRQn 0 */

    /* USER CODE END UsageFault_IRQn 0 */
    while (1)
    {
        /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
        /* USER CODE END W1_UsageFault_IRQn 0 */
    }
}

/**
    * @brief This function handles System service call via SWI instruction.
    */
void SVC_Handler(void)
{
    __asm(
        ".global SVC_Handler_Main\n"
        "TST lr, #4\n"
        "ITE EQ\n"
        "MRSEQ r0, MSP\n"
        "MRSNE r0, PSP\n"
        "B SVC_Handler_Main\n"
    ) ;
}

void SVC_Handler_Main( unsigned int *svc_args )
{
    unsigned int svc_number;

    /*
    * Stack contains:
    * r0, r1, r2, r3, r12, r14, the return address and xPSR
    * First argument (r0) is svc_args[0]
    */
    svc_number = ( ( char * )svc_args[ 6 ] )[ -2 ] ;
    switch( svc_number )
    {
        case 0:    /* EnablePrivilegedMode */
            __set_CONTROL( __get_CONTROL( ) & ~CONTROL_nPRIV_Msk ) ;    // this shouldnt give us problems according to the ta, follow up if issues happen
            break;
        case 1:
            // case to enter pend_sv
            SCB->ICSR |= 1<<28; //control register bit for a PendSV interrupt
            __asm("isb");
            break;
        case 2:
        	// case when the current running task doesn't need to be stored
            __asm(
                "MRS R0, PSP\n"
                "LDMIA R0!, {R4, R11}\n"
                "MSR PSP, R0\n"
                "MOV LR, 0xFFFFFFFD\n"
                "BX LR\n"
            );
        break;
        default:        /* unknown SVC */
        // add different svc cases for the different things we need to handle
            break;
    }
}

/**
    * @brief This function handles Debug monitor.
    */
void DebugMon_Handler(void)
{
    /* USER CODE BEGIN DebugMonitor_IRQn 0 */

    /* USER CODE END DebugMonitor_IRQn 0 */
    /* USER CODE BEGIN DebugMonitor_IRQn 1 */

    /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
    * @brief This function handles Pendable request for system service.
    */
//void PendSV_Handler(void)
//{
//    /* USER CODE BEGIN PendSV_IRQn 0 */
//
//    /* USER CODE END PendSV_IRQn 0 */
//    /* USER CODE BEGIN PendSV_IRQn 1 */
//
//    /* USER CODE END PendSV_IRQn 1 */
//}

/**
    * @brief This function handles System tick timer.
    */
void SysTick_Handler(void)
{
    /* USER CODE BEGIN SysTick_IRQn 0 */

    /* USER CODE END SysTick_IRQn 0 */
    HAL_IncTick();
    /* USER CODE BEGIN SysTick_IRQn 1 */

    /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                                                        */
/* Add here the Interrupt Handlers for the used peripherals.                                    */
/* For the available peripheral interrupt handler names,                                            */
/* please refer to the startup file (startup_stm32f4xx.s).                                        */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
