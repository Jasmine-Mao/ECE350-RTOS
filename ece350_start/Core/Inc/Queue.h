#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Node structure for the linked list
typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

// Define the structure for the queue
typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
    int max_size;
} Queue;

Queue* create_queue(int max_size);
void enqueue(Queue *queue, void *item);
void* dequeue(Queue *queue);
bool is_empty(Queue *queue);
bool is_full(Queue *queue);
void free_queue(Queue *queue);

#endif // QUEUE_H
