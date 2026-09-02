#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/*  TODO: make this name more generic? i.e. like just a vector or something
* - Move struct definitions back to source file? (makes them opaque)
*  - currently moved here for testing to make life easier */

/* TODO: - Make into the other structure with just left / right, wrap those in a pay load...*/
struct location_node {
    char *filename;
    unsigned *lines;

    size_t size;
    size_t capacity;

    struct location_node *next;
};

/* initialize a location node, allocates memory for the node,
 * filename, and for the starting cap of lines. also adds lineno to lines */

/* TODO: make starting capacity an argument??, no macro here,
 *  redo the tests */
#define STARTCAP 5
struct location_node *create_loc(const char *file, unsigned lineno);

/* free all memory associated with a linked list of location nodes */
void clear_loc_list(struct location_node *node);

/* attempt to push a value to the end of node's line's member
 * possibly resizes lines as well */
void push_back_line(struct location_node *node, unsigned value);

/* str_dup returns identical allocated duplicate of __s,
 * or NULL on failure */
char *str_dup(const char *__s);

#endif
