
#include "../include/hash.h"
#include "../include/hash_utils.h"

#include <stdlib.h>

/* for now this is the hash function implemented in K&R */
size_t hash(struct hashtab *tab, char *key)
{
    size_t hashval = 0;
    while (*key != '\0')
    {
        hashval = *key++ + 31 * hashval;
    }
    return hashval % tab->table_cap;
}
bool insert(struct hashtab *tab, const char *key, const char *file, unsigned val)
{
    /* - find the hash value
     * - find the node in the bucket matching the key
     * - check if the last file pushed to locations list is file argument,
     *   - if so, push val to the end of lines
     *   - else, create a new location node, make it the head of the list
     * - CHECK LOAD FACTOR FOR RESIZE
     */

    return 0 & 1;
}

struct hashtab create_tab()
{
    struct hashtab ret;
    ret.table = (struct hash_node **) malloc(sizeof(struct hash_node *) * START_TAB_CAP);
    if (ret.table)
    {
        for (int i = 0; i < START_TAB_CAP; ++i)
            ret.table[i] = NULL;

        ret.table_cap = START_TAB_CAP;
        ret.table_sz = 0;
    }
    return ret;
}

