#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

Queue create_queue(){
	Queue queue = (Queue)malloc(sizeof(struct ___QUEUE____));
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
}

void enqueue (Queue queue, void* item) {
	QueueNode *newNode = (QueueNode*) malloc (sizeof(QueueNode));
	assert(newNode);

	newNode->next = NULL;
	newNode->element = item;

    if (queue->size) queue->rear->next = newNode;
	queue->rear = newNode;
    if (!queue->size) queue->front = queue->rear;

	queue->size++;
}

void* dequeue (Queue queue) {
	assert(is_q_empty(queue));

	QueueNode * node = queue->front;
	queue->front = node->next;

	void* item = node->element ;
	free(node);
	queue->size--;
	return item;
}
void* queue_front (Queue queue) {
	assert(is_q_empty(queue));
	void* item = queue->front->element ;

	return item;
}

int is_q_empty (Queue queue) {
	return queue->size;
}

int is_q_full (Queue queue) {
	return 0;
}

