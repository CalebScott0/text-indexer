#include "hash.h"

/* hash: return the hash value associated with key:
 * TODO: explore different hash functions!!!! and actually test their output metrics */
size_t hash(struct hashtab *table, const char *key);

/* initialize an empty hashtable to starting capacity */
#define START_TAB_CAP 10
struct hashtab create_tab();

/* hash_get: look for node corresponding to key in the table,
 * returns a pointer to the node if exists in the hash table,
 * else NULL */
struct hash_node *hash_get(struct hashtab *table, const char *key);

/* Initialize a hash node. Allocates memory for a struct hash_node, and assigns default values to all members.
 * returns pointer to allocated memory, or NULL if failure */

struct hash_node *create_hash_node();
