#ifndef QUEUE_H
#define QUEUE_H

typedef struct ___QUEUE_NODE____{
    void *element;
    struct ___QUEUE_NODE____ *next;
} QueueNode;

struct ___QUEUE____{
    QueueNode *front;
    QueueNode *rear;
    size_t size;
};
typedef struct ___QUEUE____ * Queue ;

Queue create_queue();
void enqueue (Queue queue, void* item);
void* dequeue (Queue queue);
void* queue_front (Queue queue);

int is_q_empty (Queue queue);
int is_q_full (Queue queue);

#endif //QUEUE_H
