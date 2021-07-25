
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node {
    struct node *next, *left, *right;
    char *str;
    int freq;
} node;

void print_table(node **table);
void sort_list(node *node);
void swap(node **a, node **b);
void print_node(node n);
void print_list(node *n);

node *append_node(node *head, node *n);

void print_node(node n)
{
    if (strcmp(n.str, "\n") == 0)
        printf("%d\t\\n", n.freq);
    else if (strcmp(n.str, " ") == 0)
        printf("%d\tspace", n.freq);
    else
        printf("%d\t%s", n.freq, n.str);
}

void print_list(node *n)
{
    while (n != NULL)
    {
        printf("\n");
        print_node(*n);
        n = n->next;
    }
    printf("\n\n");
}

int len(node *n)
{
    int length = 0;
    node *t = n;
    while (t != NULL)
    {
        length += 1;
        t = t->next;
    }
    return length;
}

node *append_node(node *head, node *n)
{
    node *t;

    // If the node we want to append doesn't exist return
    if (n == NULL)
        return NULL;

    // If the list we want to append to is empty,
    // append to it by setting the new head and return.
    t = head;
    if (head == NULL)
        return n;

    // Iterate until the last node in the list,
    // and then set the new last node.
    while (t->next != NULL)
        t = t->next;

    t->next = n;

    return head;
}

node *make_node(char *s)
{
    node *n = (node *) malloc(sizeof(node));

    if (n == NULL)
    {
        fprintf(stderr, "Memory failure at make_node(), exiting...");
    }
    else
    {
        n->next = NULL, n->left = NULL, n->right = NULL;
        n->freq = 1;

        n->str = (char *) malloc((strlen(s) + 1) * sizeof(char));
        strcpy(n->str, s);
    }

    return n;
}

node *copy_list(node *list)
{
    node *new_list, *temp = list;
    while (temp != NULL)
    {
        new_list = append_node(new_list, make_node(temp->str));
        temp = temp->next;
    }
    return new_list;
}

void swap(node **a, node **b)
{
    node temp = **a;
    **a = **b;
    **b = temp;
}

// Convert linked list to an array, sort, then convert back.
void sort_list(node *head)
{
    int length;
    int i = 0, j, min;

    // Find the length of the list
    length = len(head);
    node **array = (node **) malloc(length * sizeof(node *));

    // Copy list into array
    node *t = head;
    while (t != NULL)
    {
        array[i++] = t;
        t = t->next;
    }

    // Run selection sort on the array
    for (i = 0; i < length - 1; i++)
    {
        min = i;
        for (j = i + 1; j < length; j++)
            if (array[j]->freq < array[min]->freq)
                min = j;

        swap(&array[min], &array[i]);
    }

    // Link the pointers in proper order
    for (i = 0; i < length-1; i++)
    {
        array[i]->next = array[i+1];
    }
    array[length-1]->next = NULL;
}

// The table is a linked-list structure, which is useful as
// the procedure for turning a table into a huffman tree is done
// with the use of a queue.
node *make_table(FILE *in)
{
    node *head = NULL;
    char *str = (char *) malloc(2 * sizeof(char));
    char c;

    while ((c = fgetc(in)) != EOF)
    {
        node *t = head;

        // Traverse through the list until the matching
        // character is found or the end is reached.
        
        while (t != NULL && t->str[0] != c)
            t = t->next; 
   

        // If the end was reached without finding a match,
        // add a new node for that character.
        *str = c;
        *(str + 1) = '\0';
        if (t == NULL)
            head = append_node(head, make_node(str));
        else
            t->freq += 1;
    }

    return head;
}

