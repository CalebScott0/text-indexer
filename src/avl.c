/* implementation of an AVL tree */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"
#include "../include/utils.h"

#define MAX(A, B) ( (A) > (B)  ? (A) : (B) )

struct tree create_tree()
{
    struct tree ret = { .root = NULL };
    return ret;
}

struct tree_node *avl_get(const struct tree *t, const char *key)
{
    struct tree_node *curr = t->root;

    while (curr)
    {
        int cond = strcmp(key, curr->key);
        if (cond == 0)
        {
            return curr;
        }
        curr = (cond < 0) ? curr->left : curr->right;
    }
    
    return NULL;
}

bool tree_insert(struct tree *t , const char *key, const char *file, unsigned lineno)
{
    struct tree_node *__insert(struct tree_node *, const char *, const char *, unsigned, bool *);
    bool is_insert = false;

    t->root = __insert(t->root, key, file, lineno, &is_insert);

    return is_insert;
}

struct tree_node *__insert(struct tree_node *node,
                        const char *key,
                        const char *file,
                        unsigned lineno,
                        bool *ins)
{
    if (node == NULL)
    {
        node = create_tree_node();
        if (node)
        {
            *ins = true;
            node->loc_list = create_loc(file, lineno);
            node->key = str_dup(key);
        }
        return node;
    }

    int cond;
    if ((cond = strcmp(key, node->key)) == 0)
    {
        /* files are processed sequentially, if we always make a new location_node
         *  the head of the list, last file we found the key in will be the first
         *  location_node in this current tree node */
        if (strcmp(node->loc_list->filename, file) == 0)
        {
            push_back_line(node->loc_list, lineno);
        }
        else
        {
            struct location_node *new = create_loc(file, lineno);

            /* make new the head of loc_list */
            new->next = node->loc_list; 
            node->loc_list = new;
        }
        /* TODO: any value in returning node here ?
         * trace through execution quickly */
    }
    else if (cond > 0) /* right */
    {
        node->right = __insert(node->right, key, file, lineno, ins);
    }
    else    /* left */
    {
        node->left = __insert(node->left, key, file, lineno, ins);
    }

    /* AVL tree is balanced if balance factor is {-1, 0, 1} 
     * we check each node on the backtrace - only nodes in the insert path can become unbalanced
     * we can check the value of the key against node key to
     * determine the rotations if unbalanced */
    int8_t balance_factor = get_height(node->left) - get_height(node->right);

    if (balance_factor < -1 && (cond = strcmp(key, node->right->key)) > 0) 
    {
        // returning the node returned by rotation functions assign it back up to its parent in back trace
        return left_rot(node);
    }
    else if (balance_factor < -1 && cond < 0)
    {
        node->right = right_rot(node->right);
        /* this node never gets recalculated below these conditions, do that now */
        node->right->height = 1 + MAX(get_height(node->right->left), get_height(node->right->right));
        return left_rot(node);
    }
    else if (balance_factor > 1 && (cond = strcmp(key, node->left->key)) < 0) 
    {
        return right_rot(node);
    }
    else if (balance_factor > 1 && cond > 0)
    {
        node->left = left_rot(node->left);
        /* this node never gets recalculated below these conditions, do that now */
        node->left->height = 1 + MAX(get_height(node->left->left), get_height(node->left->right));
        return right_rot(node);
    }

    node->height = 1 + MAX(get_height(node->left), get_height(node->right));

    return node;
}

struct tree_node *left_rot(struct tree_node *root)
{
    struct tree_node *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root->height -= 1;

    return new_root;
}

struct tree_node *right_rot(struct tree_node *root)
{
    struct tree_node *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root->height -= 1;

    return new_root;
}

void tree_clear(struct tree *t)
{
    void __clear(struct tree_node *);
    __clear(t->root);
    t->root = NULL;
}

void __clear(struct tree_node *node)
{
    if (node == NULL) return;
    __clear(node->left);
    __clear(node->right);

    clear_loc_list(node->loc_list);
    free(node->key);

    free(node);
}

struct tree_node *create_tree_node()
{
    struct tree_node *node = 
        (struct tree_node *) malloc(sizeof(struct tree_node));
    if (node)
    {
        node->height = 0;
        node->key = NULL;
        node->left = node->right = NULL;
        node->loc_list = NULL;
    }
    return node;
}

int get_height(struct tree_node *__n)
{
    return (__n != NULL) ? __n->height : -1;
}
