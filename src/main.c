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
        printf("\nResults for %s:\n", key);
        struct location_node *locnode = hnode->loc_list;
        while (locnode)
        {
            /* TODO: use string formatting func here or in a to_string function */
            printf("File: %s\n", locnode->filename);
            printf("Lines: ");
            for (size_t i = 0; i < locnode->size; ++i)
                printf("%u ", locnode->lines[i]);
            printf("\n---------------------\n");
            locnode = locnode->next;
        }
    }
    else
        fprintf(stderr, "Error: %s is not in the index\n", key);

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

    int count = 0;
    printf("Creating the index...\n");
    while (argc >= 0)
    {
        FILE *infile = fopen(*argv, "r");
        /* TODO: error handling on file open */
        if (!infile) {
            ++argv;
            --argc;
            continue;
        };

        unsigned line_count = 0;
        int c;


        while ((c = gettoken(s, MAXTOKEN, infile)) != EOF)
            /* TODO: NEED TO COUNT LINES */
        {
            if (c == '\n')
                ++line_count;
            else if (isalpha(s[0]))
            {
                if (index_insert(&my_index, s, *argv, line_count))
                {
                    /* Todo: delete this after timing stuff */
                    ++count;
                }
            }
        }

        char input[100];
        while (strcmp(input, "q") != 0)
        {
            printf("Enter a word to search for in the index: ");
            scanf("%s", input);
            printf("%s\n", input);
            index_print(&my_index, input);
        }

        fclose(infile);
        ++argv;
        --argc;
    }

    printf("num inserted = %d\n", count);
    index_clear(&my_index);

    return 0;
}
