
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"

node *make_table(FILE *in);
node *encode(node *table);
void trim_leaves(node *root);
void gen_dictionary(node *root, char *code, char **dictionary);

void inorder(node *root)
{
    if (!root) return;
    inorder(root->left);
    print_node(*root);
    inorder(root->right);
}

void postorder(node *root)
{
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    print_node(*root);
}

int main(int argc, char **argv)
{
    char *in_file_name, *txt_substring;
    char *file_type = ".txt";
    char code[14];
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
    // trim_leaves(tree);

    printf("\nInorder Traversal: \n");
    inorder(tree);
// 
    // printf("\n\nPostorder Traversal: \n");
    // postorder(tree);
    // printf("\n");


    // Create a dictionary using the huffman tree to map each character to a code.
    // A traversal to the left results in a 0, a traversal to the right results in a 1.

    // char **dictionary = (char **) malloc(sizeof(char *) * 128);
    // if (dictionary == NULL)
    // {
        // fprintf(stderr, "Memory failure in main(), exiting...");
        // exit(-1);
    // }
// 
    // printf("Before calling gen_dictionary()\n");
    // fflush(stdout);
    // gen_dictionary(tree, code, dictionary);
    // printf("After calling gen_dictionary()\n");
    // fflush(stdout);
    // for (int i = 0; i < 128; i++)
    // {
        // printf("%s: %c\n", dictionary[i], i);
    // }
// 
    fclose(fp_in);
    return 0;
}

void gen_dictionary(node *root, char *code, char **dictionary)
{
    if (root == NULL)
        return;

    printf("%s\n", code);
    // If a leaf node is reached, copy the code into the index associated with that node.
    if (root->right == NULL && root->left == NULL)
    {
        dictionary[root->str[0]] = malloc(sizeof(char) * (strlen(code) + 1));
        strcpy(dictionary[root->str[0]], code);
        return;
    }

    // Do the same for the left and right sides of the tree, passing the code properly.
    gen_dictionary(root->left, strcat(code, "0"), dictionary);
    gen_dictionary(root->right, strcat(code, "1"), dictionary);
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

// Ensure that all leaf nodes contain only a single character.
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

// Uses the algorithm involving two queues as described by 
// https://en.wikipedia.org/wiki/Huffman_coding#Compression
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

