#ifndef TASK_CONTROL_BLOCK_H
#define TASK_CONTROL_BLOCK_H

#include <stdint.h>

typedef uint32_t task_t;

typedef struct task_control_block {
    void (*ptask)(void* args);  // Entry address
    uint32_t stack_high;        // Starting address of stack (high address)
    task_t tid;                 // Task ID
    uint8_t state;              // Task's state
    uint16_t stack_size;        // Stack size. Must be a multiple of 8
    uint32_t *stack_pointer;    // Current stack pointer
    struct task_control_block *next; // Pointer to next TCB (for linked list)
} task_control_block;

#endif // TASK_CONTROL_BLOCK_H
