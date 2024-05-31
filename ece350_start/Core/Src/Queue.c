#include "Queue.h"
#include <stdlib.h>

Queue* create_queue(int max_size) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (void**)malloc(sizeof(void*) * max_size);
    queue->head = 0;
    queue->tail = 0;
    queue->max_size = max_size;
    queue->size = 0;
    return queue;
}

void enqueue(Queue *queue, void *item) {
    if (is_full(queue)) {
        return; // Queue is full
    }
    queue->data[queue->tail] = item;
    queue->tail = (queue->tail + 1) % queue->max_size;
    queue->size++;
}

void* dequeue(Queue *queue) {
    if (is_empty(queue)) {
        return NULL; // Queue is empty
    }
    void *item = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->max_size;
    queue->size--;
    return item;
}

bool is_empty(Queue *queue) {
    return queue->size == 0;
}

bool is_full(Queue *queue) {
    return queue->size == queue->max_size;
}

void free_queue(Queue *queue) {
    free(queue->data);
    free(queue);
}
