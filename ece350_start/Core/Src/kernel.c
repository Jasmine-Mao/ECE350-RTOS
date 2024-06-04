#include "kernel.h"
#include "Queue.h"
#include <stdlib.h>

Queue *ready_queue;
task_control_block *current_task;

void osKernelInit(int max_tasks) {
    ready_queue = create_queue(max_tasks);
    current_task = NULL;
}

void osKernelStart(void) {
    current_task = (task_control_block*)dequeue(ready_queue);
    if (current_task) {
        current_task->state = 0; // Running state
        // Set PSP and start the first task (usually done in assembly)
        __set_PSP(current_task->stack_high);
        osYield(); // Start the first task
    }
}

task_control_block* osTaskInfo(task_t tid) {
    QueueNode *node = ready_queue->front;
    while (node) {
        task_control_block *task = (task_control_block*)node->data;
        if (task->tid == tid) {
            return task;
        }
        node = node->next;
    }
    return NULL; // Task not found
}

task_t osGetTID(void) {
    if (current_task) {
        return current_task->tid;
    }
    return -1; // No current task
}

void osTaskExit(void) {
    if (current_task) {
        current_task->state = 2; // Mark task as exited
        osYield(); // Yield to the next task
    }
}

task_t osCreateTask(void (*task_func)(void*), void *args, uint32_t *stack, uint16_t stack_size) {
    static task_t next_tid = 0; // Static variable to keep track of task IDs
    task_control_block *new_task = (task_control_block*)malloc(sizeof(task_control_block));
    if (!new_task) {
        return -1; // Memory allocation failed
    }
    new_task->ptask = task_func;
    new_task->stack_high = (uint32_t)stack + stack_size;
    new_task->stack_size = stack_size;
    new_task->state = 1; // Ready state
    new_task->stack_pointer = (uint32_t*)stack;
    new_task->tid = next_tid++; // Assign task ID and increment for next task
    new_task->next = NULL;

    // Initialize stack frame for task function
    uint32_t *sp = new_task->stack_pointer;
    *(--sp) = (1U << 24);             // xPSR
    *(--sp) = (uint32_t)task_func;    // PC
    *(--sp) = 0x0000000EU;            // LR (return address)
    for (int i = 0; i < 13; i++) {    // R0-R12
        *(--sp) = 0x0000000AU;        // R0-R12
    }
    new_task->stack_pointer = sp;

    enqueue(ready_queue, new_task);
    return new_task->tid;
}

void osYield(void) {
    __asm volatile (
        "MRS R0, PSP\n"
        "STMDB R0!, {R4-R11}\n"
        "LDR R1, =current_task\n"
        "LDR R1, [R1]\n"
        "STR R0, [R1]\n"

        "BL scheduler\n"

        "LDR R1, =current_task\n"
        "LDR R1, [R1]\n"
        "LDR R0, [R1]\n"
        "LDMIA R0!, {R4-R11}\n"
        "MSR PSP, R0\n"
        "MOV LR, #0xFFFFFFFD\n"
        "BX LR\n"
    );
}

void scheduler(void) {
    if (current_task && current_task->state == 0) {
        current_task->state = 1;
        enqueue(ready_queue, current_task);
    }

    if (is_empty(ready_queue)) {
        current_task = NULL;
    } else {
        current_task = (task_control_block*)dequeue(ready_queue);
        if (current_task) {
            current_task->state = 0;
        }
    }
}

void PendSV_Handler(void) {
    __asm volatile (
        "MRS R0, PSP\n"
        "STMDB R0!, {R4-R11}\n"
        "LDR R1, =current_task\n"
        "LDR R1, [R1]\n"
        "CBZ R1, no_task\n"
        "STR R0, [R1]\n"
        "BL scheduler\n"
        "LDR R1, =current_task\n"
        "LDR R1, [R1]\n"
        "CBZ R1, no_task\n"
        "LDR R0, [R1]\n"
        "LDMIA R0!, {R4-R11}\n"
        "MSR PSP, R0\n"
        "MOV LR, #0xFFFFFFFD\n"
        "BX LR\n"
        "no_task:\n"
        "B idle_task\n"
    );
}

void idle_task(void) {
    while (1) {
        // Idle behavior, such as low-power mode
    }
}
