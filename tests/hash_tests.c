#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/hash.h"


int main()
{
    /* empty table */
    struct hashtab test_tab = create_tab();
    assert(test_tab.table != NULL);
    assert(test_tab.table_cap == START_TAB_CAP);
    assert(test_tab.table_sz == 0);

    /* one key */
    /* check this one explicitly, 
     * and then use hash_get() for the rest, except for sz and capcity */
    hash_insert(&test_tab, "key1", "", 0);
    struct hash_node *node = test_tab.table[hash(&test_tab, "key1")];
    assert(strcmp(node->key, "key1") == 0);
    assert(node->next == NULL);
    assert(node->loc_list != NULL);
    assert(test_tab.table_sz == 1);


    /* collisions/multiple keys in same bucket */
    /* WARNING: for now the hash function hashes any key containing the same characters to
     * the same value, so "key1" and "1key" hash to the same value */

    hash_clear(&test_tab);

    //duplicate key
    //resizing
    //search
    //destruction

    printf("\n✅ Passed\n");

    return 0;
}
