#include "stdlib.h"
#include "string.h"

#include "../include/utils.h"

void push_back_line(struct location_node *node, unsigned value)
{
    if (node == NULL) return;

    size_t *sz = &node->size;
    size_t *cap = &node->capacity;
    unsigned *plines = node->lines;

    if (*sz == *cap)   /* resize */
    {
        /* TODO: error handling?, try out realloc??! */
        unsigned *new_lines =
            (unsigned *) malloc(sizeof(unsigned) * (*cap << 1));
        for (size_t i = 0; i < *cap; ++i)
            new_lines[i] = plines[i];

        free(plines);
        node->lines = new_lines;
        plines = node->lines;
        *cap <<= 1;
    }

    /* we only want unique line numbers */
    if (*sz > 0 && plines[*sz - 1] != value)
        plines[(*sz)++] = value;
}

char *str_dup(const char *__s)
{
    char *w = (char *) malloc(strlen(__s) + 1);
    if (w)
        strcpy(w, __s);
    return w;
}

struct location_node *create_loc(const char *file, unsigned lineno)
{
    struct location_node *node =
        (struct location_node *) malloc(sizeof(struct location_node));
    if (node)
    {
        node->filename = str_dup(file);
        node->next = NULL;
        node->size = 0;
        node->lines = 
            (unsigned *) malloc(sizeof(unsigned) * (node->capacity = STARTCAP));
        node->lines[node->size++] = lineno;
    }
    
    return node;
}

void clear_loc_list(struct location_node *node)
{
    if (node == NULL) return;

    struct location_node *prev = node;
    struct location_node *curr = node->next;

    for (; curr != NULL; curr = curr->next)
    {
        free(prev->filename);
        free(prev->lines);
        free(prev);
        prev = curr;
    }

    /* prev points to last element in list */
    free(prev->filename);
    free(prev->lines);
    free(prev);
}

