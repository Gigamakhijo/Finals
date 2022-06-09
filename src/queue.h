#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct Queue Queue;

Queue *new_queue(void);
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void free_queue(Queue *Queue);

size_t q_len(Queue *queue);

#endif
