/* hashtab, uses chaining */

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>

#include "utils.h"

struct hash_node {
    char *key;
    struct location_node *loc_list; /* list of locations key is found in */

    struct hash_node *next;         /* pointer to next node in chain */
};

struct hashtab {
    struct hash_node **table;      /* dynamic array of pointers to nodes */

    size_t table_sz;
    size_t table_cap;             /* number of available buckets in the table */
};

/* initialize a hash table
 * allocate the table member to starting capacity
 * returns a hashtab structure */
struct hashtab create_hash();

/* TODO: ...... */
/* Returns true if a new key was inserted,
 * false if an existing key was updated. */
bool hash_insert(struct hashtab *htab, const char *key, const char *file, unsigned line);

/* free all memory allocated to tab and its members */
void hash_clear(struct hashtab *htab);

/* hash: return the hash value associated with key:
 * TODO: explore different hash functions!!!! and actually test their output metrics */
size_t hash(struct hashtab *tab, const char *key);

/* initialize an empty hashtable to starting capacity */
#define START_TAB_CAP 10
struct hashtab create_tab();

/* hash_get: look for node corresponding to key in the table,
 * returns a pointer to the node if exists in the hash table,
 * else NULL */
struct hash_node *hash_get(struct hashtab *tab, const char *key);

/* Initialize a hash node. Allocates memory for a struct hash_node, and assigns default values to all members.
 * returns pointer to allocated memory, or NULL if failure */
struct hash_node *create_hash_node();

#define LOAD_FACTOR 1.5
/* resize: double hash table capacity if insert is equal or greater than the load factor */
void hash_resize(struct hashtab *tab);


#endif
