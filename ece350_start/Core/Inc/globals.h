#include "Queue.h"
#include "main.h"
#include <stdbool.h>
#include <stdatomic.h>

extern TCB* current_task;
extern Queue* task_queue;
extern int initialized = 0;
extern int first_run = 1;

extern _Atomic(int) TID_taken[15] = {0};      // size of the array is defined by max tasks in main.c; 0 if not taken, 1 if taken