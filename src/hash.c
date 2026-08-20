
#include "../include/hash.h"
#include <stdlib.h>

/* hash: return the hash value associated with key */
size_t hash(char *key);

#define STARTING_CAP 10

struct hashtab create_tab()
{
    struct hashtab ret;
    ret.table = (struct node **) malloc(sizeof(struct node *) * STARTING_CAP);
    for (int i = 0; i < STARTING_CAP; ++i)
        ret.table[i] = NULL;

    ret.table_cap = STARTING_CAP;
    ret.table_sz = 0;
    return ret;
}
