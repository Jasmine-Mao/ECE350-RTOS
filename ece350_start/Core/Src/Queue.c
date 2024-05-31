#include "Queue.h"
#include <stdlib.h>

Queue* create_queue(int max_size) {
    Queue queue = (Queue)malloc(sizeof(Queue));
    queue->data = (void*)malloc(sizeof(void) * max_size);
    queue->head = 0;
    queue->tail = 0;
    queue->max_size = max_size;
    queue->size = 0;
    return queue;
}

void enqueue(Queue queue, voiditem) {
    if (is_full(queue)) {
        return; // Queue is full
    }
    queue->data[queue->tail] = item;
    queue->tail = (queue->tail + 1) % queue->max_size;
    queue->size++;
}

void* dequeue(Queue queue) {
    if (is_empty(queue)) {
        return NULL; // Queue is empty
    }
    voiditem = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->max_size;
    queue->size--;
    return item;
}

int is_empty(Queue queue) {
    return queue->size == 0;
}

int is_full(Queuequeue) {
    return queue->size == queue->max_size;
}
or
q.h:
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct QueueNode {
    void data;
    struct QueueNodenext;
} QueueNode;

typedef struct {
    QueueNode front;
    QueueNoderear;
    int size;
    int max_size;
} Queue;

Queue* create_queue(int max_size);
void enqueue(Queue queue, voiditem);
void* dequeue(Queue queue);
bool is_empty(Queuequeue);
bool is_full(Queue queue);
void free_queue(Queuequeue);

#endif // QUEUE_H
q.c:
#include "queue.h"
#include <stdlib.h>

Queue* create_queue(int max_size) {
    Queue queue = (Queue)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    queue->max_size = max_size;
    return queue;
}

void enqueue(Queue queue, voiditem) {
    if (is_full(queue)) {
        return; // Queue is full
    }
    QueueNode new_node = (QueueNode)malloc(sizeof(QueueNode));
    new_node->data = item;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

void* dequeue(Queue queue) {
    if (is_empty(queue)) {
        return NULL; // Queue is empty
    }
    QueueNodetemp = queue->front;
    void item = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return item;
}

bool is_empty(Queuequeue) {
    return queue->size == 0;
}

bool is_full(Queue queue) {
    return queue->size == queue->max_size;
}

void free_queue(Queuequeue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}