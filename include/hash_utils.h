#include "hash.h"

/* hash: return the hash value associated with key:
 * TODO: explore different hash functions!!!! and actually test their output metrics */
size_t hash(struct hashtab *tab, char *key);


/* initialize an empty hashtable to starting capacity */
#define START_TAB_CAP 10
struct hashtab create_tab();

