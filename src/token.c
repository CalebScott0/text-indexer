#include <stdio.h>
#include <ctype.h>
#include "../include/token.h"

int gettoken(char *s, int lim, FILE *infile)
{
    int c;
    while (isspace(c = getch(infile)))
        ;

    /* TODO: do we only want alpha characters at the start ?
     * - this is what we can check on input to determine if we want to insert a token or not,
     *   i.e. test on if return is an alpha character */
    if (!isalpha(c))
    {
        *s = '\0';
        return c;
    }

    /* allow apostrophes dashes in words, also allow underscores */
    for (*s++ = c; --lim > 0 && (isalpha(c = getch(infile)) || c == '\'' || c == '-'); )
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

char getch(FILE *infile)
{
    return pbuf != buf ? *--pbuf : fgetc(infile);
}

