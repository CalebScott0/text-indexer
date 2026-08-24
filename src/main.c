#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"
#include "../include/hash.h"

int main()
{
    struct hashtab tab = create_tab();
    insert(&tab, "the", "file1", 1);
    insert(&tab, "performance", "file1", 2);
    insert(&tab, "of", "file1", 2);

    insert(&tab, "the", "file2", 1);
    insert(&tab, "hash", "file2", 1);
    insert(&tab, "table", "file2", 1);
    insert(&tab, "deteriorates", "file2", 2);
    insert(&tab, "relation", "file2", 2);
    insert(&tab, "to", "file2", 2);

    insert(&tab, "the", "file3", 1);
    insert(&tab, "load", "file3", 1);
    insert(&tab, "factor", "file3", 1);
    insert(&tab, "in", "file3", 2);
    insert(&tab, "the", "file3", 2);

    insert(&tab, "start", "file3", 3);
    insert(&tab, "begin", "file3", 3);
    insert(&tab, "end", "file3", 4);
    insert(&tab, "middle", "file3", 4);

    return 0;
}
