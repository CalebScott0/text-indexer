/* implementation of an AVL tree */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"
#include "../include/avl_utils.h"

struct tree create_tree()
{
    struct tree ret = { .root = NULL };
    return ret;
}

bool tree_insert(struct tree *t, const char *key, unsigned val)
{
    struct t_node *__insert(struct t_node *, const char *, unsigned, bool *);
    bool is_insert = false;
    t->root = __insert(t->root, key, val, &is_insert);

    return is_insert;
}

struct t_node *__insert(struct t_node *node, const char *key, unsigned value, bool *ins)
{
    if (node == NULL)
    {
        node = create_node();
        if (node)
        {
            *ins = true;
            node->locations.lines[node->locations.size++] = value;
            /* TODO: this might just be ptr assignment,
             * if allocate during the tokenization */
            node->key = str_dup(key);
        }
        return node;
    }

    /* TODO: to do iteratively, you would need probably a parent pointer
     * to update the heights or bf of all ancestor nodes
     * recursively, if balanced correctly, still runs in logn,
     * 1,000,000 nodes is still only ~ 20 levels,
     * and you can update all ancestor nodes on the backtrack */

    int cond;
    if ((cond = strcmp(key, node->key)) == 0)
    {
        push_back_line(node, value);
        /* TODO: any value in returning node here ?
         * trace through execution quickly */
    }
    else if (cond > 0) /* right */
    {
        node->right = __insert(node->right, key, value, ins);
    }
    else    /* left */
    {
        node->left = __insert(node->left, key, value, ins);
    }

    /* AVL tree is balanced if balance factor is {-1, 0, 1} 
     * we check each node on the backtrace - only nodes in the insert path can become unbalanced
     * we can check the value of the key against node key to
     * determine the rotations if unbalanced */
    int8_t balance_factor = get_height(node->left) - get_height(node->right);

    if (balance_factor < -1 && strcmp(key, node->right->key) > 0) 
    {
        // returning the node returned by rotation functions assign it back up to its parent in back trace
        return left_rot(node);
    }
    else if (balance_factor < -1 && strcmp(key, node->right->key) < 0)
    {
        node->right = right_rot(node->right);
        /* this node never gets recalculated below these conditions, do that now */
        node->right->height = 1 + MAX(get_height(node->right->left), get_height(node->right->right));
        return left_rot(node);
    }
    else if (balance_factor > 1 && strcmp(key, node->left->key) < 0) 
    {
        return right_rot(node);
    }
    else if (balance_factor > 1 && strcmp(key, node->left->key) > 0)
    {
        node->left = left_rot(node->left);
        /* this node never gets recalculated below these conditions, do that now */
        node->left->height = 1 + MAX(get_height(node->left->left), get_height(node->left->right));
        return right_rot(node);
    }

    node->height = 1 + MAX(get_height(node->left), get_height(node->right));

    return node;
}


void tree_clear(struct tree *t)
{
    void __clear(struct t_node *);
    __clear(t->root);
}

void __clear(struct t_node *node)
{
    if (node == NULL) return;
    __clear(node->left);
    __clear(node->right);

    free(node->locations.lines);
    free(node->key);
    free(node);
}

struct t_node *left_rot(struct t_node *root)
{
    struct t_node *new_root = root->right;

    root->right = new_root->left;
    new_root->left = root;
    root->height -= 1;

    return new_root;
}

struct t_node *right_rot(struct t_node *root)
{
    struct t_node *new_root = root->left;

    root->left = new_root->right;
    new_root->right = root;
    root->height -= 1;

    return new_root;
}

/* push_back_line: attempts to insert a new value to the end of the lines array in
 * the locations member struct of node */
void push_back_line(struct t_node *node, unsigned value)
{
    if (node == NULL) return;

    size_t *sz = &node->locations.size;
    size_t *cap = &node->locations.capacity;
    unsigned *plines = node->locations.lines;

    if (sz == cap)   /* resize */
    {
        unsigned *new_lines =  /* TODO: error handling?, try out realloc! */
            (unsigned *) malloc(sizeof(unsigned) * (*cap << 1));
        for (size_t i = 0; i < *cap; ++i)
            new_lines[i] = plines[i];

        free(plines);
        node->locations.lines = new_lines;
        *cap <<= 1;
    }

    /* we only want unique line numbers */
    if (*sz > 0 && plines[*sz - 1] != value)
        plines[(*sz)++] = value;
}

#define STARTCAP 10

struct t_node *create_node()
{
    struct t_node *node = 
        (struct t_node *) malloc(sizeof(struct t_node));
    if (node)
    {
        node->height = 0;
        node->key = NULL;
        node->left = node->right = NULL;
        node->locations.lines = NULL;
        node->locations.size = 0;
        node->locations.capacity = STARTCAP;
        node->locations.lines =
            (unsigned *) malloc(sizeof(unsigned) * STARTCAP);
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

int get_height(struct t_node *__n)
{
    return (__n != NULL) ? __n->height : -1;
}
