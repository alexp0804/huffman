
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "list.h"


typedef struct queue {
    node *head;
    int size;
} queue;

queue *make_queue(node *head);
void enqueue(queue *q, node *n);
node *dequeue(queue *q);
int peek(queue *q);

queue *make_queue(node *head)
{
    queue *q = (queue *) calloc(1, sizeof(queue));    
    q->head = head;
    q->size = len(head);
    return q;
}

void enqueue(queue *q, node *n)
{
    node *t = q->head;

    // Empty queue case
    if (t == NULL)
    {
        q->head = n, n->next = NULL;
        q->size = 1;
        return;
    }

    // Reach the end of the queue, add the node onto the end.
    while (t->next != NULL)
        t = t->next;

    // Append the node, double check that the last node points to NULL.
    t->next = n, n->next = NULL;
    q->size += 1;
}

node *dequeue(queue *q)
{
    node *ret_node;

    // Empty queue case.
    if (q->head == NULL)
        return NULL;

    // Capture the head, move the head pointer first, break any links
    // and decrease size
    ret_node = q->head;    
    q->head = q->head->next;
    ret_node->next = NULL;

    q->size -= 1;

    return ret_node;
}

int peek(queue *q)
{
    if (q == NULL || q->head == NULL)
        return INT_MAX;

    return q->head->freq;
}

