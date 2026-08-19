/* interface for an AVL tree,
 * each node stores a char * key, and a list of values */

#include <stddef.h>

#ifndef AVL_H
#define AVL_H

/* TODO: make this name more generic? i.e. like just a vector or something
 * - Move struct definitions back to source file? (makes them opaque)
 *  - currently moved here for testing to make life easier */
struct location_list {
    /* TODO: char **filenames; */
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

/* insert: If the key does not exist in node's tree, insert a new node,
 *         else possibly append value to the lines vector in locations
 *  - node:  root of the tree in which to attempt the insert
 *  - key:   c-string key to insert
 *  - value: value to possibly append to lines member in locations 
 *
 *  returns: pointer to node after insert operations
 */ 
struct t_node *insert(struct t_node *node, const char *key, unsigned value);

/* free all allocated memory */
void clear(struct t_node *node);

/* return the height of the node */
 /* TODO: keep this here or move back to source file after tests ? */
int get_height(struct t_node *__n);


#endif
