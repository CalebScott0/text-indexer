#include <ctype.h>
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

void print_tree(struct tree_node *node)
{
    if (!node) return;
    printf("%s\n", node->key);
    print_tree(node->left);
    print_tree(node->right);
}

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    sleep(2);

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

    int count = 0;
    while (argc >= 0)
    {
        FILE *infile = fopen(*argv, "r");
        /* TODO: error handling on file open */
        if (!infile) {
            ++argv;
            --argc;
            continue;
        };

        int c;
        while ((c = gettoken(s, MAXTOKEN, infile)) != EOF)
            /* TODO: NEED TO COUNT LINES */
        {
            if (isalpha(s[0]))
            {
                if (index_insert(&my_index, s, *argv, 0))
                {
                    ++count;
                }
            }
        }

        fclose(infile);
        ++argv;
        --argc;
    }

    printf("num inserted = %d\n", count);
    index_clear(&my_index);

    return 0;
}
