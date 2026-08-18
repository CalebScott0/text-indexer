#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"

int main()
{
    /* initialize ptr to NULL */
    t_node *tree = NULL;
    tree = insert(tree, "hello", 1);
    tree = insert(tree, "all", 2);
    tree = insert(tree, "zebra", 9);

    printf("Hello\n");
    
    return 0;
}
