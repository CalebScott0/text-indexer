#include <stdio.h>

/* TODO: this probably could just be one char tbh,
 * and maybe just put this in the source file?
 * also when to use extern?? */
#define BUFSIZE 10

static char buf[BUFSIZE];
static char *pbuf = buf;

/* get the next token from input,
 * if token exceeds lim - 1, NO input is stored,
 * return first char stored in s, or a single non alpha character */
int gettoken(char *s, int lim, FILE *file);

void ungetch(int c);
char getch();
