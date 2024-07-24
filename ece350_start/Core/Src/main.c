#include "main.h"
#include <stdio.h>
#include "common.h"
#include "k_task.h"
#include "k_mem.h"

#define  ARM_CM_DEMCR      (*(uint32_t *)0xE000EDFC)
#define  ARM_CM_DWT_CTRL   (*(uint32_t *)0xE0001000)
#define  ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)

int i_test = 0;

int i_test2 = 0;


void TaskA(void *) {
   while(1){
      printf("%d, %d\r\n", i_test, i_test2);
      osPeriodYield();
   }
}

void TaskB(void *) {
   while(1){
      i_test = i_test + 1;
      osPeriodYield();
   }
}

void TaskC(void *) {
   while(1){
      i_test2 = i_test2 + 1;
      osPeriodYield();
   }
}



int main(void)
{

  /* MCU Configuration: Don't change this or the whole chip won't work!*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* MCU Configuration is now complete. Start writing your code below this line */

  	osKernelInit();
  	k_mem_init();

  	TCB st_mytask;
  st_mytask.stack_size = STACK_SIZE;
  st_mytask.ptask = &TaskA;
  osCreateDeadlineTask(4, &st_mytask);

  st_mytask.ptask = &TaskB;
  osCreateDeadlineTask(4, &st_mytask); 

  st_mytask.ptask = &TaskC;
  osCreateDeadlineTask(12, &st_mytask);

  	osKernelStart();


/*
//Compiler's version-------------------
  //measure time to allocate N block
  for (int i = 0; i < N; i ++){
	  timestamps[i] = ARM_CM_DWT_CYCCNT;
	  p_temp = (U32*)malloc(4);
  }
  timestamps[N] = ARM_CM_DWT_CYCCNT;
  //print total clock ticks as well as ticks per iteration
  printf("malloc time: %lu\r\n", timestamps[N] - timestamps[0]);
  printf("Time per iteration:\r\n");
  for (int i = 0; i < N; i ++){
	  printf("%u, ", timestamps[i+1] - timestamps[i]);
  }
  printf("\r\n\r\n");
*/

  printf("back to main\r\n");
  while (1);
 }

