#include <stdio.h>
#include <ctype.h>
#include "../include/token.h"

int gettoken(char *s, int lim)
{
    int c;
    while (isspace(c = getch()))
        ;

    /* TODO: do we only want alpha characters at the start ?
     * - this is what we can check on input to determine if we want to insert a token or not,
     *   i.e. test if return is an alpha character */
    if (!isalpha(c))
    {
        *s = '\0';
        return c;
    }

    /* allow apostrophes dashes in words, also allow underscores (great artist btw)?? */
    for (*s++ = c; --lim > 0 && (isalpha(c = getch()) || c == '\'' || c == '-'); )
        *s++ = c;

    ungetch(c);
    *s = '\0';
    return s[0];
}

void ungetch(int c)
{
    if (pbuf < buf + BUFSIZE)
        *pbuf++ = c;
    else
        fprintf(stderr, "Error: ungetch() - bufffer full");
}

char getch()
{
    return pbuf != buf ? *--pbuf : getchar();
}

