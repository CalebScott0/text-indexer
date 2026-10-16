#include "../include/avl.h"
#include "../include/hash.h"

enum dt_type { TREE, HASH };

struct index {
    enum dt_type type;
    struct hashtab *hash;
    struct tree *tree;
};

// 
// bool index_insert(struct index *idx, const char *key, const char *file, unsigned line)
// {
    // if (idx->type == TREE)
        // return tree_insert(&idx->tree, key, file, line);
// 
    // return hash_insert(&idx->hash, key, file, line);
// }
// 
// /* TODO: bool return and create_* function should handle error from memory allocation? */
//bool index_init(struct index *idx, const char *type)
//{

//}
// 
// void index_clear(struct index *idx)
// {
    // if (idx->type == TREE)
        // tree_clear(&idx->tree);
        // free(idx->tree);
    // else
        // hash_clear(&idx->hash);
        // free(idx->hash);
// }
// 
// /* TODO: this needs to be more modular,
 // * i.e. this should be in the src file of the data type,
 // * retrieve object of index type and return ? */
// void index_print(struct index *idx, const char *key)
// {
    // struct location_node *locnode = NULL;
    // if (idx->type == TREE)
    // {
        // struct tree_node *tnode = avl_get(&idx->tree, key);
        // if (tnode)
            // locnode = tnode->loc_list;
    // }
    // else
    // {
        // struct hash_node *hnode = hash_get(&idx->hash, key);
        // if (hnode)
            // locnode = hnode->loc_list;
    // }
// 
    // if (locnode)
    // {
        // printf("\n%s\n", key);
        // while (locnode)
        // {
            // /* TODO: use string formatting func here or in a to_string function */
            // printf("  %s: ", locnode->filename);
            // printf("%u", locnode->lines[0]);
            // for (size_t i = 1; i < locnode->size; ++i)
                // printf(", %u", locnode->lines[i]);
            // putchar(10);
            // locnode = locnode->next;
        // }
    // }
    // else
        // fprintf(stderr, "\nError: %s is not in the index\n", key);
// 
// }
// 
