
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"


node *make_table(FILE *in);
node *encode(node *table);
void trim_leaves(node *root);

void inorder(node *tree);
int count_leaves(node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;

    return count_leaves(root->left) + count_leaves(root->right);
}



int main(int argc, char **argv)
{
    char *in_file_name, *txt_substring;
    char *file_type = ".txt";
    node *table, *tree;
    FILE *fp_in;

    // Process command line input. The file name should be given.
    if (argc != 2)
    {
        fprintf(stderr, "Incorrect argument count, try again.\n");
        fprintf(stderr, "Must be in format: \"huff file_name.txt\"\n");
        exit(-1);
    }
    else
    {
        // Input file must be a .txt file.
        // Here we assign a null terminator at the
        // end of the ".txt" sub-string to avoid any possible exploits.
        in_file_name = argv[1];

        // Pointer to the beginning of the ".txt" sub-string.
        txt_substring = strstr(in_file_name, file_type);
        if (txt_substring == NULL)
        {
            fprintf(stderr, "Input file must be a %s file, try again.\n", file_type);
            exit(-1);
        }
        // Character immediately following the .txt
        // substring is set to null terminator.
        *(txt_substring + strlen(file_type)) = '\0';
    }

    // The given file is now known to be in the proper format.
    // Open the file with read only.
    fp_in = fopen(in_file_name, "r");


    // Read through the file, counting frequency of every character.
    table = make_table(fp_in);

    if (table == NULL)
        exit(-1);

    sort_list(table);
    print_list(table);

    tree = encode(table);
    // Ensure leaf nodes contain only a single character long string.
    trim_leaves(tree);
    printf("%d\n", count_leaves(tree));
    inorder(tree);


    fclose(fp_in);
    return 0;
}

void trim_leaves(node *root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        root->str[1] = '\0';
    }

    trim_leaves(root->left);
    trim_leaves(root->right);
}

void inorder(node *tree)
{
    if (tree == NULL)
        return;

    inorder(tree->left);
    if (tree->left == NULL && tree->right == NULL)
    {
        for (int i = 0; i < strlen(tree->str); i++)
        {
            if (tree->str[i] == '\n')
                printf("\\n");
            else if (tree->str[i] == ' ')
                printf("space");
            else
                printf("%c", tree->str[i]);
        }
        printf("\n");
    }
    inorder(tree->right);
}

node *encode(node *table)
{
    queue *q1 = make_queue(table);
    queue *q2 = make_queue(NULL);

    while (q1->size + q2->size > 1)
    {
        node *n1 = (peek(q1) < peek(q2)) ? dequeue(q1) : dequeue(q2);
        node *n2 = (peek(q1) < peek(q2)) ? dequeue(q1) : dequeue(q2);

        node *new = make_node(strcat(n1->str, n2->str));
        new->left = n1;
        new->right = n2;
        new->freq = n1->freq + n2->freq;
        enqueue(q2, new);
    }


    return (peek(q1) == INT_MAX) ? dequeue(q2) : dequeue(q1);
}

