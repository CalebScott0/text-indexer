/* interface for an AVL tree,
 * each node stores a char * key, and a vector of locations the key appears,
 * where a location is a filename, and the lines that the key appears in in that file */

#ifndef AVL_H
#define AVL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "utils.h"

 /*TODO: fix up parameters and member var names, i.e. const? and pick a naming convention */
struct tree_node {
    char *key;
    struct location_node *loc_list;  /* list of locations */

    uint8_t height;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree {
    struct tree_node *root;
};

/* create_tree: initialize an empty tree 
 * TODO: other alternative is to create and pass by ptr for both this and hash*/
 struct tree create_tree();

/* tree_insert: If the key does not exist in node's tree, insert a new node,
 *  else, append the 
 *  - tree:  a tree structure
 *  - key:   c-string key to insert
 *  - file:  name of the file key appears in
 *  - lineno: line number of the file key appears in 
 *  returns: true if and only if a new node was inserted
 */ 
bool tree_insert(struct tree *t, const char *key, const char *file, unsigned lineno);

/* avl_get: search for the node containing key,
 * return a pointer to the node if found, else NULL */
struct tree_node *avl_get(const struct tree *t, const char *key);

/* free all allocated memory */
void tree_clear(struct tree *t);

/* Initialize a tree node. Allocates memory for a struct tree_node, and assigns default values to all members.
 * returns pointer to allocated memory, or NULL if failure */
struct tree_node *create_tree_node();

/* apply a left rotation to node, adjusts its height,
 * returns the new subtree root (node->right) */
struct tree_node *left_rot(struct tree_node *node);

/* apply a right rotation to node, adjusts its height
 * returns the new subtree root (node->left) */
struct tree_node *right_rot(struct tree_node *node);

/* return the height of the node */
int get_height(struct tree_node *__n);

#endif
