/* TODO: this probably could just be one char tbh */
#define BUFSIZE 100

static char buf[BUFSIZE];
static char *pbuf = buf;

int gettoken(char *s, int lim);

void ungetch(int c);
char getch();
