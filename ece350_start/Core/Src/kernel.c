#include "stm32f4xx_it.h"
#include "common.h"
#include "main.h"
#include "kernel.h"
#include <stdio.h>
U32* MSP_INIT_VAL;
//= *(U32**)0x0;
// ^gets set when kernel init runs
TCB* current_task;
int initialized = 0;
int first_run = 1;
int task_counter = 0;
int current_tid_index = 0;	// indexer for what task is currently running

TCB task_queue[MAX_TASKS] = {NULL};

int get_stack_address(TCB* task){
	for(int i = 1; i < MAX_TASKS; i++){
		if(task_queue[i].stack_high == NULL && task_queue[i].state == 0){
			// if the address has not yet been set
			if(task_counter == 0){
				// the very first thread
				task->stack_high = (int)MSP_INIT_VAL - task->stack_size;
			}
			else{
				// look at the previous thread and make calculations that way
				task->stack_high = task_queue[i - 1].stack_high - task->stack_size;
			}
			// set t\state here
			task->state = 1;
			task_queue[i] = *task;
			return RTX_OK;
		}
		else if(task_queue[i].state == 0 && task_queue[i].stack_size >= task->stack_size){
			// if the address and size have already been set
			task->stack_size = task_queue[i].stack_size;
			task->state = 1;
			task_queue[i] = *task;
			return RTX_OK;
		}
	}
	return RTX_ERR;
}

void assign_TID(TCB* task){
  // iterate through the atomic array
  for(int i = 1; i < 16; i++){
    if(task_queue[i].state == 0){
      task->tid = i;
      return;
    }
  }
}

int is_empty(){
	for (int i = 0; i < 16; i++){
		if (task_queue[i].state != 0) return 0;
	}
	return 1;
}

TCB * find_TCB(task_t tid_input){
	for (int i = 1; i < MAX_TASKS; i++) {
		if (task_queue[i].tid == tid_input)
			return &task_queue[i];
	}
	printf("uh oh!");
	return NULL;
}

void scheduler() {
    if (!is_empty()) {
        int start_index = current_tid_index; // Save the starting index
        do {
            current_tid_index = (current_tid_index + 1) % MAX_TASKS; // Increment the index

            if (current_tid_index == 0) { //If we reach null task, skip it
                current_tid_index = 1;
            }
            if (task_queue[current_task->tid].state == 1) { //If the task is available/ready
                current_task = &task_queue[current_tid_index]; // Same as old scheduler
                __set_PSP(*current_task->stack_high); // please check referencing/defrencing here  and aboveI have no clue
                return;
            }
        } while (current_tid_index != start_index); // Loop until we come back to the start index so we don't do infinite loop
    }
}


int osKernelStart(){
  if (first_run && initialized){
    first_run = 0;
    __asm("SVC #0");
    printf("kernel start finished ok!\r\n");
    return RTX_OK;
  }
  else {
	  printf("panic: start failed\r\n");

	  return RTX_ERR;
  }
}

void osKernelInit(){
  printf("inside kernelinit!\r\n");
  //initialize variables
  MSP_INIT_VAL = *(U32**)0x0;
  current_task = NULL;

  initialized = 1;
  osKernelStart();
}

int osTaskInfo(task_t TID, TCB* task_copy){
  if (TID < 0 || TID >= MAX_TASKS) { //check if the TID is valid
      return RTX_ERR;
  }
  for (int i = 1; i < MAX_TASKS; i++){
	  printf("%x\n", task_queue[i].tid);
	  if(task_queue[i].tid == TID){ //if the TID matches, copy the task info
			task_copy->next = task_queue[i].next;		//address of the task copy pointer now points to the found TCB
			task_copy->ptask = task_queue[i].ptask;
			task_copy->stack_high = task_queue[i].stack_high;
			task_copy->stack_size = task_queue[i].stack_size;
			task_copy->state = task_queue[i].state;
			task_copy->tid = task_queue[i].tid;
			return RTX_OK;
		  }
  }
  return RTX_ERR;
}

task_t osGetTID (void){
  if (!first_run && initialized){
    return current_task->tid;
  }
  else return RTX_ERR;
}



int osTaskExit(void){
  if (!first_run && initialized){
    current_task->state = DORMANT;
    task_queue[current_task->tid].state = 0;
    scheduler();
    return RTX_OK;
  }
  else return RTX_ERR;
}


int osCreateTask(TCB* task){
if (task != NULL && task_counter < MAX_TASKS && task->stack_size >= STACK_SIZE && task->stack_size <= MAX_STACK_SIZE){	// the stacksize of the given task has double the size of the specified stack size from common.h
 assign_TID(task);
 get_stack_address(task);
 *(--task->stack_high) = 1<<24; //This is xPSR, setting the chip to Thumb mode
 *(--task->stack_high) = (uint32_t)(task->ptask); //the function name
 for (int i = 0; i < 14; i++) *(--task->stack_high) = 0xA; //An arbitrary number, repeat this 14 times in total

 task_counter++;
 return RTX_OK;
}
else return RTX_ERR;
}

void osYield(void){
  //tentative
  if (!first_run && initialized){
	  __asm("SVC #1");
  }
  else printf("panic: yield failed\r\n");

}
