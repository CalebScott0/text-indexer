/* interface for an AVL tree,
 * each node stores a char * key, and a vector of locations the key appears,
 * where a location is a filename, and the lines that the key appears in in that file */

#ifndef AVL_H
#define AVL_H

#include <stddef.h>
#include <stdbool.h>

/* TODO: make a class called tree that houses the root of a tree ?? */

/* TODO: make this name more generic? i.e. like just a vector or something
 * - Move struct definitions back to source file? (makes them opaque)
 *  - currently moved here for testing to make life easier */
struct location_node {
    /* TODO: char *filename; */
    unsigned *lines;

    size_t size;
    size_t capacity;
};

struct t_node {
    char *key;
    /* TODO: with multiple files added in, this will have to be a vector,
     * or you can make location_node a linked list
     * for now get both working with just one file input */
    struct location_node locations;

    int height;     /* PERF: make this a one bit field that stores balance
                        factor instead ? */
    struct t_node *left;
    struct t_node *right;
};

struct tree {
    struct t_node *root;
};

/* create_tree: initialize an empty tree 
 * TODO: other alternative is to create and pass by ptr for both this and hash*/
 struct tree create_tree();

/* tree_insert: If the key does not exist in node's tree, insert a new node,
 *         else possibly append value to the lines vector in locations
 *  - tree: a tree structure
 *  - key:   c-string key to insert
 *  - value: value to possibly append to lines member in locations 
 *  returns: true if and only if a new node was inserted
 */ 
bool tree_insert(struct tree *t, const char *key, unsigned val);

/* TODO: void *for get ? for fct pointer? 
    get: needs to search for the key, and if found return a void ? pointer to lines, and the sz of lines?
    other idea is return a pointer to the node, void? */

/* free all allocated memory */
void tree_clear(struct tree *t);

#endif
