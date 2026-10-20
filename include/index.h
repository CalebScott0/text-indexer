#include "../include/avl.h"
#include "../include/hash.h"

enum dt_type { TREE, HASH };

struct index {
    enum dt_type type;

    union {
        struct hashtab hash;
        struct tree tree;
    } ctx;

    size_t word_count; 
    size_t file_count;
};

/* init_index: Takes a pointer to a struct TODO: */
void init_index(struct index *idx, enum dt_type type);

bool index_insert(struct index *idx, const char *key,
                  const char *filename, unsigned line);

bool index_add_file(struct index *idx, const char *filename);

void index_print(struct index *idx, const char *key);

void index_clear(struct index *idx);

