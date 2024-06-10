#include "stm32f4xx_it.h"
#include "common.h"
#include "main.h"
#include "kernel.h"
#include <stdio.h>
U32 *MSP_INIT_VAL;
//= *(U32**)0x0;
// ^gets set when kernel init runs
TCB *current_task;
int initialized = 0;
int first_run = 1;
int task_counter = 0;
int current_tid_index = 0;	// indexer for what task is currently running

TCB task_queue[MAX_TASKS] = { NULL };

int get_stack_address(TCB *task) {
	for (int i = 1; i < MAX_TASKS; i++) {
		if (task_queue[i].starting_address == NULL //if the task is not initialized
				&& task_queue[i].state == 0) { //if the task is dormant
			if (task_counter == 0) { //if this is the first task
				task->starting_address = (int) MSP_INIT_VAL - MAIN_STACK_SIZE; //set the starting address to the main stack, subtract the stack size
			} else {
				task->starting_address = task_queue[i - 1].starting_address //set the starting address to the previous task's starting address
						- task->stack_size; //subtract the stack size
			}
			task->stack_high = task->starting_address; //set the stack high to the starting address
			task->state = 1; //set the state to ready
			*(--task->stack_high) = 1 << 24; //This is xPSR, setting the chip to Thumb mode
			*(--task->stack_high) = (uint32_t) (task->ptask); //the function name
			for (int i = 0; i < 14; i++) 
				*(--task->stack_high) = 0xA; //An arbitrary number, repeat
			task_queue[i] = *task; //copy the task to the task queue
			return RTX_OK;
		} else if (task_queue[i].state == 0 //if the task is dormant
				&& task_queue[i].stack_size >= task->stack_size) { //reusing the stack
			task->stack_size = task_queue[i].stack_size; //set the stack size to the previous task's stack size
			task->state = 1; //set the state to ready
			task->starting_address = task_queue[i].starting_address; //set the starting address to the previous task's starting address
			task->stack_high = task_queue[i].starting_address; //set the stack high to the starting address
			*(--task->stack_high) = 1 << 24; //This is xPSR, setting the chip to Thumb mode
			*(--task->stack_high) = (uint32_t) (task->ptask); //the function name
			for (int i = 0; i < 14; i++)
				*(--task->stack_high) = 0xA; //An arbitrary number, repeat this 14 times in total
			task_queue[i] = *task;
			return RTX_OK;
		}
	}
	return RTX_ERR;
}

void assign_TID(TCB *task) { //assigns a task ID to the task
	for (int i = 1; i < 16; i++) {
		if (task_queue[i].state == 0) {
			task->tid = i;
			return;
		}
	}
}

int is_empty() { //checks if the task queue is empty
	for (int i = 1; i < 16; i++) {
		if (task_queue[i].state != 0)
			return 0;
	}
	return 1;
}

TCB* find_TCB(task_t tid_input) { //finds the TCB with the given TID [REDUNDANT]
	for (int i = 1; i < MAX_TASKS; i++) {
		if (task_queue[i].tid == tid_input)
			return &task_queue[i];
	}
	return NULL;
}

void scheduler() {
	if (!is_empty()) { //if the task queue is not empty
		if (current_task != NULL && current_task->state) { //if the current task is not null and has a state
			task_queue[current_task->tid].state = 1; //set the current task to ready
			task_queue[current_task->tid].stack_high = __get_PSP(); //set the stack high to the process stack pointer
		}
		int start_index = current_tid_index; // Save the starting index
		do {
			current_tid_index = (current_tid_index + 1) % MAX_TASKS; // Increment the index

			if (current_tid_index == 0) { //If we reach null task, skip it
				current_tid_index = 1;
			}
			if (task_queue[current_tid_index].state == 1) { //If the task is available/ready
				task_queue[current_tid_index].state = 2; //Set the task to running
				current_task = &task_queue[current_tid_index]; // Same as old scheduler
				__set_PSP(current_task->stack_high); // Set the PSP to the stack high
				// should be able to return from here after the svc call
				return;
			}
		} while (current_tid_index != start_index); // Loop until we come back to the start index so we don't do infinite loop
	}
}

int osKernelStart() {
	if (first_run && initialized) { //if this is the first run and the kernel is initialized
		first_run = 0; //set first run to false
		__asm("SVC #2"); //call case 2 which is just scheduler and load new task
		return RTX_OK;
	} else
		return RTX_ERR;
}

void osKernelInit() {
	MSP_INIT_VAL = *(U32**) 0x0; //set the MSP_INIT_VAL to the value at address 0
	current_task = NULL; //set the current task to null
	initialized = 1; //set initialized to true
}

int osTaskInfo(task_t TID, TCB *task_copy) {
	if (TID < 0 || TID >= MAX_TASKS || !task_counter) //if the TID is invalid or TID greater than the max tasks or no tasks
		return RTX_ERR;
	for (int i = 1; i < MAX_TASKS; i++) { //iterate through the task queue
		if (task_queue[i].tid == TID) { //if the TID matches, copy the task info
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

task_t osGetTID(void) {
	if (!first_run && initialized) //if this is not the first run and the kernel is initialized
		return current_task->tid; //return the current task's TID
	else
		return 0;
}

int osTaskExit(void) {
	if (!first_run && initialized) { //if this is not the first run and the kernel is initialized
		task_queue[current_task->tid].state = 0; //set the current task to dormant
		task_counter--; //decrement the task counter
		__asm("SVC #2"); //call case 2 which is just scheduler and load new task
		return RTX_OK;
	} else
		return RTX_ERR;
}

int osCreateTask(TCB *task) {
	if (task != NULL && task_counter < MAX_TASKS
			&& task->stack_size >= STACK_SIZE
			&& task->stack_size <= MAX_STACK_SIZE) {// the stacksize of the given task has double the size of the specified stack size from common.h
		assign_TID(task); //assign a TID to the task
		get_stack_address(task); //get the stack address for the task
		task_counter++; //increment the task counter
		return RTX_OK;
	} else
		return RTX_ERR;
}

void osYield(void) {
	if (!first_run && initialized)
		__asm("SVC #1"); //call case 1 which is to enter PendSV which is store, scheduler and load
}
