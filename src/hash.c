
#include "../include/hash.h"
#include "../include/hash_utils.h"

#include <stdlib.h>
#include <string.h>

/* for now this is the hash function implemented in K&R */
size_t hash(struct hashtab *table, const char *key)
{
    size_t hashval = 0;
    while (*key != '\0')
    {
        hashval = *key++ + 31 * hashval;
    }
    return hashval % table->table_cap;
}

bool insert(struct hashtab *table, const char *key, const char *file, unsigned line)
{
    struct hash_node *pn;
    /* key not in table */
    if ((pn = hash_get(table, key)) == NULL)
    {
        // create a new hash node, and loc_node point to it with hash[hashval], make head...
        /* TODO: MAYBE RESIZE */
        return true;
    }
    /* key exists in table for all below */
    /* since we access files sequentially, last file added to locations list is most recent,
     * check if we have seen this key in this file before */
    else if (strcmp(pn->loc_list->filename, file) == 0)
    {
        push_back_line(pn->loc_list, line);
    }
    else
    {
        /* new location node, make it the head of location list */
        struct location_node *loc_node = create_loc(file, line);
        loc_node->next = pn->loc_list;
        pn->loc_list = loc_node;
    }

    /* TODO: MAYBE RESIZE!! */

    return false;
}

struct hash_node *hash_get(struct hashtab *table, const char *key)
{
    if (table->table == NULL) return NULL;

    unsigned hash_v = hash(table, key);
    /* walk the list of hash nodes looking for key */
    for (struct hash_node *pn = table->table[hash_v]; pn != NULL; pn = pn->next)
    {
        if(strcmp(pn->key, key) == 0)
            return pn;
    }

    return NULL;
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

