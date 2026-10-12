#include <stdio.h>
#include <ctype.h>
#include "../include/token.h"

/* TODO: extern in .h? */
static unsigned line_count = 1;

int gettoken(char *s, int lim, FILE *infile)
{
    int c;

    /* we want to keep newline for line tracking */
    while ((c = getch(infile)) == ' ' ||  c == '\t')
        ;

    if (c == '\n')
    {
        ++line_count;
        /* continue with getting the next real token */
        c = getch(infile);
    }

    /* TODO: do we only want alpha characters at the start ?
     * - this is what we can check on input to determine if we want to insert a token or not,
     *   i.e. test on if return is an alpha character */
    if (!isalpha(c))
    {
        *s = '\0';
        return c;
    }

    /* allow apostrophes dashes in words, also allow underscores */
    /* TODO: for now everything is lower case */
    for (*s++ = tolower(c); --lim > 0 && (isalpha(c = getch(infile)) || c == '\'' || c == '-'); )
        *s++ = tolower(c);

    ungetch(c);
    *s = '\0';
    return s[0];
}

unsigned get_line_count()
{
    return line_count;
}

void reset_line_count()
{
    line_count = 1;
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

