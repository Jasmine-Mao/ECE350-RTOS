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
#include "Queue.h"
#include "main.h"
#ifndef INC_COMMON_H_
#define INC_COMMON_H_

typedef struct task_control_block{
  void (*ptask)(void* args); //entry address
  U32 stack_high; //starting address of stack (high address)
  task_t tid; //task ID
  U8 state; //task's state
  U16 stack_size; //stack size. Must be a multiple of 8
  //your own fields at the end
} TCB;

extern TCB* current_task;
extern Queue* task_queue;
extern int initialized = 0;
extern int first_run = 1;

extern _Atomic(int) TID_taken[15] = {0};      // size of the array is defined by max tasks in main.c; 0 if not taken, 1 if taken

#endif /* INC_COMMON_H_ */
