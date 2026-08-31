#include <stdio.h>
#include <assert.h>

#include "../include/hash.h"


int main()
{
    //empty table
    struct hashtab test_tab = create_tab();
    assert(test_tab.table != NULL);
    assert(test_tab.table_cap == START_TAB_CAP);
    assert(test_tab.table_sz == 0);

    hash_clear(&test_tab);


    //one key
    //collisions/multiple keys in same bucket
    //duplicate key
    //resizing
    //search
    //destruction

    printf("\n✅ Passed\n");

    return 0;
}
