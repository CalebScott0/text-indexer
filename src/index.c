#include "../include/index.h"
#include <stdio.h>

void init_index(struct index *idx, enum dt_type type)
{
    if (!idx || type != TREE || type != HASH)
        return;

    idx->type = type;
    idx->file_count = 0;
    idx->word_count = 0;
    if (type == TREE)
    {
        idx->ctx.tree = create_tree();
    }
    else
    {
        idx->ctx.hash = create_hash();
    }
}

bool index_insert(struct index *idx, const char *key, const char *filename, unsigned line)
{
    if (!idx) return false;

    if (idx->type == TREE)
    {
        return tree_insert(&idx->ctx.tree, key, filename, line);
    }

    return hash_insert(&idx->ctx.hash, key, filename, line);
}

void index_print(struct index *idx, const char *key)
{
    struct location_node *loc_node = NULL;
    if (idx->type == TREE)
    {
        struct tree_node *tnode = tree_get(&idx->ctx.tree, key);
        if (tnode)
        {
            loc_node = tnode->loc_list;

        }
    }
    else
    {
        struct hash_node *hnode = hash_get(&idx->ctx.hash, key);
        if (hnode)
        {
            loc_node = hnode->loc_list;
        }
    }

    if (!loc_node)
    {
        fprintf(stderr, "\n%s was not found in the index\n", key);
        return;
    }

    char buffer[1024];
    int cx = 0;
    while (loc_node)
    {
        cx += snprintf(buffer, 1024, "  %s: %u", loc_node->filename, loc_node->lines[0]);
        for (size_t i = 1; i < loc_node->size; ++i)
        {
            if (cx >= 1024)
            {
                printf("ERROR!!!!! RAN OUT OF SPACE\n");
                return;
            }
            else
            {
                snprintf(buffer + cx, 1024 - cx, ", %u", loc_node->lines[i]);
            }
        }
        loc_node = loc_node->next;
    }
}

void index_clear(struct index *idx)
{
    if (idx->type == TREE)
    {
        tree_clear(&idx->ctx.tree);
    }
    else
    {
        hash_clear(&idx->ctx.hash);
    }
}

