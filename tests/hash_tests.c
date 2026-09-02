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

    assert(hash_insert(&test_tab, "1key", "", 0));
    assert(test_tab.table_sz == 2);

    /* this should be true, we insert new keys into the bucket as the head of the list */
    node = hash_get(&test_tab, "1key");
    assert(strcmp(node->key, "1key") == 0);
    assert(strcmp(node->next->key, "key1") == 0);

    //duplicate key
    //resizing
    //search
    //destruction

    /* TODO: make sure ASAN/LSAN also works on mac */
    hash_clear(&test_tab);

    printf("\n✅ Passed\n");

    return 0;
}
