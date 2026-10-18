#include <ctype.h>
#include "../include/token.h"

int gettoken(char *s, int lim, FILE *file)
{
    int c;
    /* save newline for line count within files */
    while ((c = getch(file)) == ' ' || c == '\t')
        ;

    /* TODO: do we only want alpha characters at the start ?
     * - this is what we can check on input to determine if we want to insert a token or not,
     *   i.e. test if return is an alpha character */
    if (!isalpha(c))
    {
        *s = '\0';
        return c;
    }

    /* allow apostrophes and dashes in words, also allow underscores */
    for (*s++ = tolower(c); --lim > 0 && (isalpha(c = getch(file)) || c == '\'' || c == '-'); )
        *s++ = tolower(c);

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

char getch(FILE *file)
{
    return pbuf != buf ? *--pbuf : getc(file);
}

