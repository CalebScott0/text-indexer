#include "../include/avl.h"

/* TODO: move these back to the source file ? */

#define MAX(A, B) ( (A) > (B)  ? (A) : (B) )

/* create, and initialize a new tree node,
 * allocates memory for the node itself,
 * as well as memory for the initial capacity of locations.lines,
 * return pointer to new allocated node, or NULL if failure */
struct tree_node *create_node();

/* attempt to push a value to the end of node's line's member
 * possibly resizes lines as well */
void push_back_line(struct location_node *node, unsigned value);

/* str_dup returns identical allocated duplicate of __s,
 * or NULL on failure */
char *str_dup(const char *__s);

/* return the balance factor of the node */
int balance_factor(struct tree_node *__n);

/* apply a left rotation to node, adjusts its height,
 * returns the new subtree root (node->right) */
struct tree_node *left_rot(struct tree_node *node);

/* apply a right rotation to node, adjusts its height
 * returns the new subtree root (node->left) */
struct tree_node *right_rot(struct tree_node *node);

/* return the height of the node */
int get_height(struct tree_node *__n);

#define STARTCAP 5
/* initialize a location node, allocates memory for the node,
 * filename, and for the starting capacity of lines.
 * also adds lineno to lines */
struct location_node *create_loc(const char *file, unsigned lineno);
