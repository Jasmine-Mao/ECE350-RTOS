/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "Queue.h"
#include "globals.h"
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
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/

void scheduler(){
  if(!is_empty(task_queue)){
    current_task = dequeue(task_queue);
    __set_PSP(*current_task->stack_high);
  }
}

void osKernelInit(void){
  //initialize variables
  initialized = 1;
  osKernelStart();
  return;
}

int osKernelStart(void){
  if (first_run && initialized){
    first_run = 0;
    SVC_Handler();
  }
  else return RTX_ERR;
}

int osTaskInfo(task_t TID, TCB* task_copy){
  TCB* temp = task_queue.search(TID);
  if (temp != NULL){
    task_copy->info = temp->info;
    return RTX_OK;
  }
  else return RTX_ERR;
}

task_t getTID (void){
  if (!first_run && initialized) return current_task->TID;
  else return 0;
}

int osTaskExit(void){
  
}


int osCreateTask(TCB* task){

}
void osYield(void){

}












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
    case 0:  /* EnablePrivilegedMode */
      __set_CONTROL( __get_CONTROL( ) & ~CONTROL_nPRIV_Msk ) ;  // this shouldnt give us problems according to the ta, follow up if issues happen
      break;
    case 1:
      // everytime we need a new system call, add a new case to handle the new thingy
      _ICSR |= 1<<28; //control register bit for a PendSV interrupt
      __asm("isb");
      // gets us to the pend svc thing which does the actual context switching
    // make a new case for when we are running the vcery first task ever
    // delete the storing stuff cuz there's nothing to store if nothing is running
    // this is what kernal start should be doing        
      break;
    case 2:
      // call scheduler to get the next task (first taslk)
      __asm(
        "MRS R0, PSP\n"             // move into R0 the PSP
        "LDMIA R0! {R4, R11}\n"     // store r4 to r11 into the memory spaces above r0
        "MSR PSP, R0\n"
        "MOV LR, 0xFFFFFFFD\n"
        "BX LR\n"
      );
    break;
    default:    /* unknown SVC */
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
void PendSV_Handler(void)
{
  printf("I'm here :D\n");
  __asm(
    "MRS R0, PSP\n"             // store into R0 the program stack pointer
    "STMDB R0! {R4, R11}\n"     // store r4 to r11 into the memory spaces above r0
    "MSR PSP, R0\n"             // move the value in R0 into the PSP
    "B scheduler\n"             // branch to the scheduler function
    "MRS R0, PSP\n"             // move into R0 the PSP
    "LDMIA R0! {R4, R11}\n"     // load r4 to r11 from the memory spaces above r0
    "MSR PSP, R0\n"             // move the value in R0 into the PSP
    "MOV LR, 0xFFFFFFFD\n"      //move the magic number into LR
    "BX LR\n"                   // branch to LR
  );
}

// void first_task_handler(void){
//   printf("setting up the first task\n");
//   __asm(


//   );
// }

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
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
