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

    /*********************
     *    Basic Insert   *
     *********************/

    /* one key */
    assert(hash_insert(&test_tab, "key1", "file1", 0));

    struct hash_node *node = test_tab.table[hash(&test_tab, "key1")];

    assert(node != NULL);
    assert(strcmp(node->key, "key1") == 0);
    assert(node->next == NULL);
    assert(node->loc_list != NULL);
    assert(strcmp(node->loc_list->filename, "file1") == 0);
    assert(node->loc_list->lines[0] == 0);
    assert(test_tab.table_sz == 1);

    /*********************
     *     Collisions    *
     *********************/

    /*
     * The current hash function hashes keys containing
     * the same characters to the same bucket.
     *
     * "key1" and "1key" should collide.
     */
    assert(hash(&test_tab, "key1") == hash(&test_tab, "1key"));

    assert(hash_insert(&test_tab, "1key", "file1", 0));
    assert(test_tab.table_sz == 2);

    /* new keys are inserted at the head of a bucket */
    node = hash_get(&test_tab, "1key");

    assert(node != NULL);
    assert(strcmp(node->key, "1key") == 0);
    assert(node->next != NULL);
    assert(strcmp(node->next->key, "key1") == 0);

    /* collision must not corrupt the existing key */
    node = hash_get(&test_tab, "key1");

    assert(node != NULL);
    assert(strcmp(node->key, "key1") == 0);
    assert(node->loc_list->lines[0] == 0);

    /*********************
     *   Duplicate Keys  *
     *********************/

    /* same key, same file, new line */
    assert(!hash_insert(&test_tab, "1key", "file1", 5));
    assert(test_tab.table_sz == 2);

    node = hash_get(&test_tab, "1key");

    assert(node != NULL);
    assert(strcmp(node->key, "1key") == 0);
    assert(node->loc_list->lines[0] == 0);
    assert(node->loc_list->lines[1] == 5);
    assert(node->loc_list->next == NULL);

    /* same key, new file */
    assert(!hash_insert(&test_tab, "1key", "file2", 10));
    assert(test_tab.table_sz == 2);

    node = hash_get(&test_tab, "1key");

    assert(node != NULL);
    assert(strcmp(node->loc_list->filename, "file2") == 0);
    assert(node->loc_list->lines[0] == 10);

    /* previous file remains in location list */
    assert(node->loc_list->next != NULL);
    assert(strcmp(node->loc_list->next->filename, "file1") == 0);
    assert(node->loc_list->next->lines[0] == 0);
    assert(node->loc_list->next->lines[1] == 5);
    assert(node->loc_list->next->next == NULL);

    /*********************
     *      Resizing     *
     *********************/

    size_t old_cap = test_tab.table_cap;
    size_t old_sz = test_tab.table_sz;

    char key[64];

    size_t num_keys = old_cap * 4 + 1;

    for (size_t i = 0; i < num_keys; i++)
    {
        snprintf(key, sizeof(key), "test_key_%zu", i);

        assert(hash_insert(&test_tab, key, "file1", 0));
        assert(test_tab.table_sz == old_sz + i + 1);
    }

    assert(test_tab.table_cap > old_cap);
    assert(test_tab.table_sz == old_sz + num_keys);

    /* original keys must survive resizing */
    node = hash_get(&test_tab, "key1");
    assert(node != NULL);
    assert(strcmp(node->key, "key1") == 0);
    assert(node->loc_list->lines[0] == 0);

    node = hash_get(&test_tab, "1key");
    assert(node != NULL);
    assert(strcmp(node->key, "1key") == 0);
    assert(strcmp(node->loc_list->filename, "file2") == 0);
    assert(node->loc_list->lines[0] == 10);
    assert(strcmp(node->loc_list->next->filename, "file1") == 0);
    assert(node->loc_list->next->lines[0] == 0);
    assert(node->loc_list->next->lines[1] == 5);

    /* verify every generated key after resizing */
    for (size_t i = 0; i < num_keys; i++)
    {
        snprintf(key, sizeof(key), "test_key_%zu", i);

        node = hash_get(&test_tab, key);

        assert(node != NULL);
        assert(strcmp(node->key, key) == 0);
        assert(strcmp(node->loc_list->filename, "file1") == 0);
        assert(node->loc_list->lines[0] == 0);
    }

    /* duplicate insert after resizing */
    assert(!hash_insert(&test_tab, "key1", "file1", 20));
    assert(test_tab.table_sz == old_sz + num_keys);

    node = hash_get(&test_tab, "key1");

    assert(node != NULL);
    assert(node->loc_list->lines[0] == 0);
    assert(node->loc_list->lines[1] == 20);

    /*********************
     *      Cleanup      *
     *********************/

    hash_clear(&test_tab);

    printf("\n✅ Passed\n");

    return 0;
}
