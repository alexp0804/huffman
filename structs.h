
typedef struct node {
    struct node *next, *left, *right;
    char str[8];
    int freq;
} node;

typedef struct queue {
    node *front;
    int size;
} queue;

node* make_node(char *str);
void append_node(node *head, node *n);
int length(node *head);

node* peek(queue *q);
void enqueue(queue *q, node *n);
node *dequeue(queue *q);
void swap(node *a, node *b);
void sort(queue *q);

