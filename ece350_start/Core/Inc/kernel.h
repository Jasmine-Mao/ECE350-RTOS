#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

void osKernelInit(void);
int osKernelStart(void);
int osTaskInfo(task_t TID, TCB* task_copy);
task_t getTID (void);
int osTaskExit(void);


int osCreateTask(TCB* task);
void osYield(void);

int is_empty();
int enqueue(TCB *current_task);

#endif // KERNEL_H
