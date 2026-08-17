/* implementation of an AVL tree */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"

#define max(A, B) ( (A) > (B)  ? (A) : (B) )

struct location_list {
    /* TODO: char *filenames; */
    unsigned *lines;

    size_t size;
    size_t capacity;
};

struct t_node {
    char *key;
    struct location_list locations;

    int height;     /* PERF: make this a one bit field that stores balance
                        factor instead ? */

    struct t_node *left;
    struct t_node *right;
};

/*
 * create, and initialize a new tree node,
 * allocates memory for the node itself,
 * as well as memory for the initial capacity of locations.lines,
 * return pointer to new allocated node, or NULL if failure
 */
struct t_node *create_node();
/*
 * attempt to push avalue to the end of root's member location's lines
 * possibly resizes lines as well 
 */
void push_back_line(struct t_node *root, unsigned value);
/*
 * str_dup returns identical allocated duplicate of __s,
 * or NULL on failure
 */
char *str_dup(const char *__s);

int get_height(struct t_node *n)
{
    return (n != NULL) ? n->height : -1;
}


struct t_node *insert(struct t_node *root, const char *key, unsigned value)
{
    if (root == NULL)
    {
        root = create_node();
        root->locations.lines[root->locations.size++] = value;

        root->key = str_dup(key); /* TODO: error handling at all necessary ? */

        return root;
    }
    /* FIXME: to do iteratively, you would need probably a parent pointer
     * to update the heights or bf of all ancestor nodes
     * recursively, if balanced correctly, still runs in logn,
     * 1,000,000 nodes is still only ~ 20 levels,
     * and you can update all ancestor nodes on the backtrack */
    int cond;
    if ((cond = strcmp(key, root->key)) == 0)
    {
        push_back_line(root, value);
        /* TODO: any value in returning root here ?
         * trace through execution quickly */
    }
    else if (cond > 0) /* right */
    {
        root->right = insert(root->right, key, value);
    }
    else    /* left */
    {
        root->left = insert(root->left, key, value);
    }
    
    /* TODO: get balance,
     * when to change height?, Remember you also need to update height even
     *  if no rotations are made.. */

    /* 4 cases for broken node */

    return root;
}

/* push_back_line: attempts to insert a new value to the end of the lines array in
 * the locations member struct of node */
void push_back_line(struct t_node *root, unsigned value)
{
    if (root == NULL) return;

    size_t *sz = &root->locations.size;
    size_t *cap = &root->locations.capacity;
    unsigned *plines = root->locations.lines;

    if (sz == cap)   /* resize */
    {
        unsigned *new_l = (unsigned *) malloc(sizeof(unsigned) * (*cap << 1));
        for (size_t i = 0; i < *cap; ++i)
            new_l[i] = plines[i];

        free(plines);
        root->locations.lines = new_l;
        *cap <<= 1;
    }

    /* we only want unique line numbers */
    if (*sz > 0 && plines[*sz - 1] != value)
        plines[(*sz)++] = value;
}

#define STARTCAP 10

struct t_node *create_node()
{
    struct t_node *node = (struct t_node *) malloc(sizeof(struct t_node));
    if (node) /* TODO: error handling at all necessary ? */
    {
        node->height = 0;
        node->key = NULL;
        node->left = node->right = NULL;
        node->locations.lines = NULL;
        node->locations.size = 0;
        node->locations.capacity = STARTCAP;
        node->locations.lines = (unsigned *) malloc(sizeof(unsigned) * STARTCAP);
    }
    return node;
}

char *str_dup(const char *__s)
{
    char *w = (char *) malloc(strlen(__s) + 1);
    if (w)
        strcpy(w, __s);
    return w;
}
