#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"
#include "../include/hash.h"
#include "../include/token.h"

#define MAXTOKEN 100

/* TODO: Don't forget list of exlcusion words,
 *  i.e. (stop words??) but whatever words are basic and not informant */

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
    return 0;
}
