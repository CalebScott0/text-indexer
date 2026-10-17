#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/token.h"
#include "../include/index.h"

#define MAXTOKEN 100

/* TODO: if you use an enum/function pointers to distinguish the backend.
 */

/* WARNING: This will slow down runtime when parsing input files when parsing input files */
bool is_stop(const char *key)
{
    static char *stop_list[] = {
        "a",
        "about",
        "all",
        "an",
        "and",
        "as",
        "at",
        "be",
        "but",
        "by",
        "do",
        "for",
        "from",
        "get",
        "go",
        "have",
        "he",
        "her",
        "his",
        "i",
        "if",
        "in",
        "it",
        "my",
        "not",
        "of",
        "on",
        "one",
        "or",
        "out",
        "say",
        "she",
        "so",
        "that",
        "the",
        "their",
        "there",
        "they",
        "this",
        "to",
        "up",
        "we",
        "what",
        "when",
        "which",
        "who",
        "will",
        "with",
        "would",
        "you"
    };

    /* binary search */
    char **begin = stop_list;
    char **end = &stop_list[0x32];
    char **middle = NULL;
    int cond;

    while (begin < end)
    {
        middle = begin + ((end - begin) >> 1);
        if ((cond = strcmp(*middle, key)) == 0)
            return true;
        if (cond > 0) /* key < middle */
            end = middle;
        else
            begin = middle + 1;
    }

    return false;
}

int main(int argc, char *argv[])
{
    char s[MAXTOKEN];
    char *type_arg = argv[1];
    if (argc < 3 || (strcmp(type_arg, "tree") && strcmp(type_arg, "hash")))
    {
        fprintf(stderr, "\nusage: %s [tree|hash] <filename>....\n", argv[0]);
        /* TODO: if no files given allow for stdin (just have to pass it to gettoken) ?
         */
        return 1;
    }

    struct index idx;
    init_index(&idx, (strcmp(argv[1], "tree") == 0) ? TREE : HASH);

    argv += 2; /* first filename */
    argc -= 3; /* count - 1 of given filenames */

    printf("\nCreating the index...\n");
    /* TODO: render bar for loading */

    while (argc >= 0)
    {
        /* TODO: use gprof to see how long you actually spend in the insert function of each data type,
         * to try and take out the file opening and closing time and all other noise */

        FILE *infile = fopen(*argv, "r");

        /* TODO: error handling on file open */
        if (!infile) 
        {
            fprintf(stderr, "ERROR: unable to open %s\n", *argv);
            ++argv;
            --argc;
            continue;
        };

        ++idx.file_count;

        unsigned line_count = 1;
        int c;
        while ((c = gettoken(s, MAXTOKEN, infile)) != EOF)
            /* TODO: NEED TO COUNT LINES */
        {
            if (c == '\n')
                ++line_count;

            // if (isalpha(s[0]))
            if (isalpha(s[0]) && !is_stop(s))
            {
                if (index_insert(&idx, s, *argv, line_count))
                {
                     ++idx.word_count;
                }
                else
                {
                     // TODO:
                    // ;
                }
            }
        }
 
        fclose(infile);
        ++argv;
        --argc;
    }

    printf("\nIndexed %zu distinct words across %zu files\n", idx.word_count, idx.file_count);

    printf("\nSearch for a word in the index - use 'quit!' to exit.\n");

    char input[100];
    while (true)
    {
        printf("\n> ");
        scanf("%s", input);
        if (strcmp(input, "quit!") == 0)
            break;
        index_print(&idx, input);
    }

    index_clear(&idx);

    return 0;
}
