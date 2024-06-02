#include "common.h"
#include <stdlib.h>

Queue* create_queue(int max_size) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    queue->max_size = max_size;
    return queue;
}

void enqueue(Queue *queue, void *item) {
    if (is_full(queue)) {
        return; // Queue is full
    }
    QueueNode *new_node = (QueueNode*)malloc(sizeof(QueueNode));
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

void* dequeue(Queue *queue) {
    if (is_empty(queue)) {
        return NULL; // Queue is empty
    }
    QueueNode *temp = queue->front;
    void *item = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
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
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
