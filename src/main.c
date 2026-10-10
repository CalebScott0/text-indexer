#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"
#include "../include/hash.h"
#include "../include/token.h"

#define MAXTOKEN 100

/* TODO: Don't forget list of exlcusion words,
 *  i.e. (stop words??) but whatever words are basic and not informant 
 *  --------------------------------
 *  for index wrapper functionality:
 *  you don't necessarily need void * ??
 *  if you use an enum/function pointers to distinguish the backend.*/


enum dt_type { TREE, HASH };

struct index {
    enum dt_type type;
    struct tree *tree;
    struct hashtab *hash;
};

bool index_insert(struct index *idx, const char *key, const char *file, unsigned line)
{
    if (idx->type == TREE)
        return tree_insert(idx->tree, key, file, line);

    return hash_insert(idx->hash, key, file, line);
}

void print_tree(struct tree_node *node)
{
    if (!node) return;
    printf("%s\n", node->key);
    print_tree(node->left);
    print_tree(node->right);
}

int main(int argc, char *argv[])
{
    struct index my_index;
    my_index.type = TREE;
    my_index.tree = (struct tree *) malloc (sizeof (struct tree));
    *my_index.tree = create_tree();

    char s[MAXTOKEN];
    //if (argc < 2)
    //{
        ///* TODO: help usage function */
        //return 1;
    //}
    
    while (gettoken(s, MAXTOKEN) != EOF)
    {
        if (isalpha(s[0]))
        {
            index_insert(&my_index, s, "file", 0);
        }
    }

    print_tree(my_index.tree->root);
    tree_clear(my_index.tree);
    free(my_index.tree);

    return 0;
}
