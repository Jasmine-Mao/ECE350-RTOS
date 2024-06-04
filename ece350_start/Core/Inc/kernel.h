#ifndef KERNEL_H
#define KERNEL_H

#include "task_control_block.h"

void osKernelInit(int max_tasks);
void osKernelStart(void);
task_control_block* osTaskInfo(task_t tid);
task_t osGetTID(void);
void osTaskExit(void);
task_t osCreateTask(void (*task_func)(void*), void *args, uint32_t *stack, uint16_t stack_size);
void osYield(void);

#endif // KERNEL_H
