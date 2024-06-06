#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

void osKernelInit(int max_tasks);
int osKernelStart();
int osTaskInfo(task_t tid, TCB* task_copy);
task_t osGetTID(void);
void osTaskExit(void);
task_t osCreateTask(void (*task_func)(void*), void *args, uint32_t *stack, uint16_t stack_size);
void osYield(void);

int is_empty();
int enqueue(TCB *current_task);

#endif // KERNEL_H
