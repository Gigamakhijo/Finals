#include "queue.h"

#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *prev;
  struct Node *next;
} Node;

struct Queue {
  Node *head;
  Node *tail;
  size_t length;
};

Node *new_node(void *data) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

void free_node(Node *node) {
  free(node->data);
  free(node);
}

Queue *new_queue(void) {
  Queue *queue = malloc(sizeof(Queue));

  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;

  return queue;
}

void enqueue(Queue *queue, void *data) {
  Node *node = new_node(data);

  // connect to  queue
  if (queue->length == 0) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    node->prev = queue->tail->next;
    queue->tail = node;
  }
  // update length
  queue->length++;
}

void *dequeue(Queue *queue) {
  Node *head = queue->head;
  void *data = head->data;

  if (head->next == NULL) {
    queue->head = NULL;
    queue->tail = NULL;
  } else {
    queue->head = head->next;
    queue->head->prev = NULL;
  }

  free(head);

  queue->length--;

  return data;
}

void free_queue(Queue *queue) {
  void *data;
  while (queue->length > 0) {
    data = dequeue(queue);
    free(data);
  }

  free(queue);
}

size_t q_len(Queue *queue) { return queue->length; }
