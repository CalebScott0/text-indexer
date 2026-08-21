/* hashtab, uses chaining */

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

struct hash_node {
    char *key;
    struct location_node *loc_list; /* list of locations key is found in */

    struct hash_node *next; /* pointer to next node in chain */
};

// TODO: REMBMER THE LOAD FACTOR!!!! For chaining.....
struct hashtab {
    struct hash_node **table;    /* dynamic array of pointers to nodes */

    size_t table_sz;
    size_t table_cap;
};

/* initialize a hash table
 * allocate the table member to starting capacity
 * returns a hashtab structure */
struct hashtab create_tab();

/* ...... */
bool insert(struct hashtab *table, const char *file, const char *key, unsigned line);


#endif
