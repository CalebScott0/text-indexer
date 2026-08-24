
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

bool insert(struct hashtab *tab, const char *key, const char *file, unsigned line)
{
    struct hash_node *pn;
    /* key not in table */
    if ((pn = hash_get(tab, key)) == NULL)
    {
        // create a new hash node, and loc_node point to it with hash[hashval], make head...
        unsigned hashval = hash(tab, key);
        struct hash_node *new_node = create_hash_node();
        new_node->loc_list = create_loc(file, line);
        new_node->key = str_dup(key);
        new_node->next = tab->table[hashval];
        tab->table[hashval] = new_node;
        tab->table_sz++;

        if ((double) tab->table_sz / tab->table_cap >= LOAD_FACTOR)
        {
            hash_resize(tab);
        }

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

    
    return false;
}

void hash_resize(struct hashtab *table)
{
    /* TODO: error checks? on arg and malloc below? */

    /* initialize new table with double capacity */
    struct hash_node **new_table = 
        (struct hash_node **) malloc(sizeof(struct hash_node *) * 2 * table->table_cap);
    for (int i = 0; i < table->table_cap << 1; ++i)
        new_table[i] = NULL;

    for (int i = 0; i < table->table_cap; ++i)
    {
        /* rehash each node of a chain, when we place into the new table,
         * follow the same format of making each insertion the new head of that chain */
        struct hash_node *curr = table->table[i];
        while (curr)
        {
            struct hash_node *temp = curr->next;
            unsigned hashval = hash(table, curr->key);
            curr->next = new_table[hashval];
            new_table[hashval] = curr;
            curr = temp;
        }
    }
    free(table->table);
    table->table = new_table;
    table->table_cap <<= 1;
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

struct hash_node *create_hash_node()
{
    struct hash_node *node =
        (struct hash_node *) malloc (sizeof(struct hash_node));
    if (node)
    {
        node->key = NULL;
        node->loc_list = NULL;
        node->next = NULL;
    }

    return node;
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

