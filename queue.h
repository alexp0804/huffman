
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "structs.h"

// Given a string to represent, this function should return a newly allocated node
// containing that string after properly setting all of the node fields.
node* make_node(char *str)
{
    node *n = (node *) malloc(sizeof(node));
    if (n == NULL) return NULL;
    
    n->left = NULL, n->right = NULL, n->next = NULL;
    strcpy(n->str, str);
    n->freq = 1;

    return n;    
}

// Given a node in a linked list and a node that wants to be added, 
// this function should append it to the end of the list.
void append_node(node *head, node *n)
{
    node *t = head;

    if (head == NULL || n == NULL) return;

    while (t->next != NULL)
        t = t->next;

    t->next = n;
    n->next = NULL;
}

// Given a head node in a linked list, this function
// should count the number of nodes the list contains.
int length(node *head)
{
    node *t = head;
    int count = 0;

    while (head != NULL)
    {
        t = t->next;
        count++;
    }

    return count; 
}

// Given a queue, this function should return the node in front of the queue.
node* peek(queue *q)
{
    if (q == NULL || q->front == NULL) return NULL;
    return q->front;
}

// Given a queue, this function should enqueue the given node into the back of the queue
void enqueue(queue *q, node *n)
{
    node *t;
    if (q == NULL || n == NULL) return;

    t = q->front;

    while (t != NULL && t->next != NULL)
        t = t->next;

    t->next = n;
    q->size++;
}

// Given a queue, this function should return the 
// first element and change the queue accordingly.
node *dequeue(queue *q)
{
    if (q == NULL || q->front == NULL) return NULL;

    node *n = q->front;
    q->front = q->front->next;

    // Break link from return node to list.
    n->next = NULL;
    q->size--;

    return n;
}

void swap(node *a, node *b)
{
    node temp = *a;
    *a = *b;
    *b = temp;
}

// Given a queue, sort it by frequency (ascending).
void sort(queue *q)
{
    node *array, *t;
    int i = 0, j = 0, len = 0, min;

    if (q == NULL || q->front == NULL) return;

    // Copy queue information into an array
    t = q->front;
    array = (node *) malloc(sizeof(node) * (len = length(t)));
    while (t != NULL)
    {
        *(array + i++) = *t;
        t = t->next;
    }

    // Selection sort
    for (i = 0; i < len - 1; i++)
    {
        min = i;

        for (j = i + 1; j < len; j++)
        {
            if ((*(array + j)).freq < (*(array + min)).freq)
            {
                min = j;
            }
        }
        swap(array + min, array + i);
    }

    // Set the next pointers correctly
    for (i = 0; i < len - 1; i++)
    {
        (*(array + i)).next = array + i + 1; 
    }
    (*(array + len)).next = NULL;
}
