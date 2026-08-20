/* hashtab, uses chaining */

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>


struct location_list {
    /* TODO: char *filename;,
     * implement multiple files after single file works on both data structures */
    unsigned *lines;

    size_t size;
    size_t capacity;
};

struct node {
    char *key;
    struct location_list locations;

    struct node *next; /* pointer to next node in chain */
};

// TODO: REMBMER THE LOAD FACTOR!!!! For chaining.....
struct hashtab {
    struct node **table; /* dynamic array of pointers to nodes */

    size_t table_sz;
    size_t table_cap;
};

/* initialize a hash table
 * allocate the table member to starting capacity
 * returns a hashtab structure */
struct hashtab create_tab();

bool insert(struct hashtab *tab, char *key, unsigned val);


#endif
