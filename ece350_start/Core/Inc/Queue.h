#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    void *data;
    int head;
    int tail;
    int max_size;
    int size;
} Queue;

Queue create_queue(int max_size);
void enqueue(Queue queue, voiditem);
void* dequeue(Queue queue);
int is_empty(Queuequeue);
int is_full(Queue *queue);

#endif // QUEUE_H