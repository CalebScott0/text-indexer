#include <stdio.h>
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
    assert(hash_insert(&test_tab, "key1", "", 0));
    assert(test_tab.table_sz == 1);

    //collisions/multiple keys in same bucket
    //duplicate key
    //resizing
    //search
    //destruction

    /* TODO: make sure ASAN/LSAN also works on mac */
    hash_clear(&test_tab);

    printf("\n✅ Passed\n");

    return 0;
}
