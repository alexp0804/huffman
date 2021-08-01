
#include <string.h>
#include <stdio.h>
#include "structs.h"

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

