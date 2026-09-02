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

int main()
{
    char s[MAXTOKEN];
    while (gettoken(s, MAXTOKEN) != EOF)
    {
        if (isalpha(s[0]))
        {
            printf("%s\n", s);
        }
    }

    /* avl_get(const struct tree *t, const char *key) */
    /* hash_get(struct hashtab *tab, const char *key) */

    return 0;
}
