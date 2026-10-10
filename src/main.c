#include <ctype.h>
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

int main(int argc, char *argv[])
{
    char s[MAXTOKEN];

    struct tree my_tree = create_tree();
    while (gettoken(s, MAXTOKEN) != EOF)
    {
        if (isalpha(s[0]))
        {
            printf("%s\n", s);
            tree_insert(&my_tree, s, "", 0);
        }
    }

    tree_clear(&my_tree);

    return 0;
}
