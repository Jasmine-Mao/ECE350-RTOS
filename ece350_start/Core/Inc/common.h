/*
 * common.h
 *
 *  Created on: Jan 5, 2024
 *      Author: nexususer
 *
 *      NOTE: If you feel that there are common
 *      C functions corresponding to this
 *      header, then any C functions you write must go into a corresponding c file that you create in the Core->Src folder
 */
#include <stdatomic.h>
#include "kernel.h"

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

typedef unsigned int U32;
typedef unsigned short U16;
typedef char U8;
typedef unsigned int task_t;


#define MAX_STACK_SIZE 0x4000
#define MAIN_STACK_SIZE 0x400
#define THREAD_STACK_SIZE 0x400

#define TID_NULL 0 //predefined Task ID for the NULL task
#define MAX_TASKS 16 //maximum number of tasks in the system1
#define STACK_SIZE 0x200 //min. size of each task’s stack
#define DORMANT 0 //state of terminated task
#define READY 1 //state of task that can be scheduled but is not running
#define RUNNING 2 //state of running task
#define RTX_ERR -1 //error code for RTX functions
#define RTX_OK 0 //success code for RTX functions

typedef struct task_control_block{
  void (*ptask)(void* args); //entry address
  U32 *stack_high; //starting address of stack (high address)
  task_t tid; //task ID
  U8 state; //task's state
  U16 stack_size; //stack size. Must be a multiple of 8
  //your own fields at the end
  task_t next;	// stores the tid of the next task
} TCB;

typedef struct state_and_address_info{
	int occupied;
	U32* stack_address;
	U16 stack_size;
} STATE_ADDRESS_INFO;



#endif /* INC_COMMON_H_ */
