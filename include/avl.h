/* interface for an AVL tree,
 * each node stores a char * key, and a vector of locations the key appears,
 * where a location is a filename, and the lines that the key appears in in that file */

#ifndef AVL_H
#define AVL_H

#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

struct tree_node {
    char *key;
    struct location_node *loc_list;  /* list of locations */

    int height;     /* PERF: make this a one bit field that stores balance
                        factor instead ? */
    struct tree_node *left;
    struct tree_node *right;
};

struct tree {
    struct tree_node *root;
};

/* create_tree: initialize an empty tree 
 * TODO: other alternative is to create and pass by ptr for both this and hash*/
 struct tree create_tree();

/* tree_insert: If the key does not exist in node's tree, insert a new node,
 *  else, append the 
 *  - tree:  a tree structure
 *  - key:   c-string key to insert
 *  - file:  name of the file key appears in
 *  - lineno: line number of the file key appears in 
 *  returns: true if and only if a new node was inserted
 */ 
bool tree_insert(struct tree *t, const char *key, const char *file, unsigned lineno);

/* TODO: void *for get ? for fct pointer? 
    get: needs to search for the key, and if found return a void ? pointer to lines, and the sz of lines?
    other idea is return a pointer to the node, void? */

/* free all allocated memory */
void tree_clear(struct tree *t);

#endif
