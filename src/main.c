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


/* move this into seperate module when done, just testing stuff out */
bool insert(
        bool (* inserter)(void *, const char *, const char *, unsigned),
            void *type, char *key, char *file, unsigned lin)
{
    return (*inserter)(type, key, file, lin);
}

enum { TREE, HASH };

int main(int argc, char *argv[])
{
    char s[MAXTOKEN];
    //if (argc < 2)
    //{
        ///* TODO: help usage function */
        //return 1;
    //}
    

    //char structure = -1;
    //if (strcmp(argv[1], "tree") == 0)
    //{
        //structure = TREE;
    //}
    //else if (strcmp(argv[1], "hash") == 0)
    //{
        //structure = HASH;
    //}
    //else
    //{
        //return 1;
    //}
    
    struct tree my_tree = create_tree();
    struct hashtab my_hash = create_tab();

    char *x[] = { "hello", "world", "are", "you", "zebra", NULL };

    //while (gettoken(s, MAXTOKEN) != EOF)
    for (char **p = x; *p != NULL; ++p)
    {
        insert(&tree_insert, &my_tree, *p, "", 0);
        /* if (isalpha(s[0]))
        {
            if (structure == TREE)
                insert(&tree_insert, &my_tree, "key", "", 0);
        }
        */
    }

    return 0;
}
