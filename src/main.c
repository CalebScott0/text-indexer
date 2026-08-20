#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"
#include "../include/hash.h"

int main()
{
    struct tree tree = create_tree();
    tree_insert(&tree, "a", 1);
    tree_insert(&tree, "b", 1);
    tree_insert(&tree, "c", 1);
    tree_insert(&tree, "d", 1);

    return 0;
}
