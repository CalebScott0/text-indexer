#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/avl.h"
#include "../include/hash.h"
#include "../include/token.h"

#define MAXTOKEN 100

/* TODO:
 *  - Don't forget list of exlcusion words,
 *  i.e. (stop words??) but whatever words are basic and not informant 
 *  - move index functionality to separate files? 
 *  --------------------------------
 *  for index wrapper functionality:
 *  if you use an enum/function pointers to distinguish the backend.
 *
 *  */

enum dt_type { TREE, HASH };

struct index {
    enum dt_type type;
    struct tree tree;
    struct hashtab hash;
};

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

bool index_insert(struct index *idx, const char *key, const char *file, unsigned line)
{
    if (idx->type == TREE)
        return tree_insert(&idx->tree, key, file, line);

    return hash_insert(&idx->hash, key, file, line);
}

/* TODO: bool return and create_* function should handle error from memory allocation? */
void index_init(struct index *idx)
{
    if (idx->type == TREE)
        idx->tree = create_tree();
    else
        idx->hash = create_tab();
}

void index_clear(struct index *idx)
{
    if (idx->type == TREE)
        tree_clear(&idx->tree);
    else
        hash_clear(&idx->hash);
}

/* TODO: this needs to be more modular,
 * i.e. this should be in the src file of the data type,
 * retrieve object of index type and return ? */
void index_print(struct index *idx, const char *key)
{
    if (idx->type == TREE)
        return; /* TODO: */

    struct hash_node *hnode = hash_get(&idx->hash, key);
    if (hnode)
    {
        printf("\n%s\n", key);
        struct location_node *locnode = hnode->loc_list;
        while (locnode)
        {
            /* TODO: use string formatting func here or in a to_string function */
            printf("  %s: ", locnode->filename);
            printf("%u", locnode->lines[0]);
            for (size_t i = 1; i < locnode->size; ++i)
                printf(", %u", locnode->lines[i]);
            putchar(10);
            locnode = locnode->next;
        }
    }
    else
        fprintf(stderr, "\nError: %s is not in the index\n", key);

}

void print_tree(struct tree_node *node)
{
    if (!node) return;
    printf("%s\n", node->key);
    print_tree(node->left);
    print_tree(node->right);
}

int main(int argc, char *argv[])
{
    char s[MAXTOKEN];
    if (argc < 2)
    {
        /* TODO: help usage function
         * - if no files given allow for stdin (just have to pass it to gettoken) ?
         */
        return 1;
    }

    struct index my_index = {
        .type = (strcmp(argv[1], "tree") == 0) ? TREE : HASH
    };

    index_init(&my_index);

    argv += 2; /* first filename */
    argc -= 3; /* count - 1 of given filenames */

    unsigned word_count = 0;
    printf("\nCreating the index...\n");
    /* TODO: render bar for loading */

    unsigned file_count = 0;
    while (argc >= 0)
    {
        FILE *infile = fopen(*argv, "r");
        /* TODO: error handling on file open */
        if (!infile) 
        {
            ++argv;
            --argc;
            continue;
        };
        ++file_count;

        int c;
        while ((c = gettoken(s, MAXTOKEN, infile)) != EOF)
            /* TODO: NEED TO COUNT LINES */
        {
            // if (isalpha(s[0]) && !is_stop(s))
            if (isalpha(s[0]))
            {
                if (index_insert(&my_index, s, *argv, get_line_count()))
                {
                    ++word_count;
                }
                else
                {
                    // TODO:
                    ;
                }
            }
        }

        fclose(infile);
        reset_line_count();
        ++argv;
        --argc;
    }

    printf("\nIndexed %u distinct words across %u files\n", word_count, file_count);
    printf("\nSearch for a word in the index - use 'quit!' to exit.\n");

    char input[100];
    while (true)
    {
        printf("\n> ");
        scanf("%s", input);
        if (strcmp(input, "quit!") == 0)
            break;
        index_print(&my_index, input);
    }

    index_clear(&my_index);

    return 0;
}
