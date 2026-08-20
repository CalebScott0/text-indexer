#include "../include/avl.h"

/* TODO: move these back to the source file ? */

#define MAX(A, B) ( (A) > (B)  ? (A) : (B) )

/* create, and initialize a new tree node,
 * allocates memory for the node itself,
 * as well as memory for the initial capacity of locations.lines,
 * return pointer to new allocated node, or NULL if failure */
struct t_node *create_node();

/* attempt to push a value to the end of node's member location's lines
 * possibly resizes lines as well */
void push_back_line(struct t_node *node, unsigned value);

/* str_dup returns identical allocated duplicate of __s,
 * or NULL on failure */
char *str_dup(const char *__s);

/* return the balance factor of the node */
int balance_factor(struct t_node *__n);

/* apply a left rotation to node, adjusts its height,
 * returns the new subtree root (node->right) */
struct t_node *left_rot(struct t_node *node);

/* apply a right rotation to node, adjusts its height
 * returns the new subtree root (node->left) */
struct t_node *right_rot(struct t_node *node);

/* return the height of the node */
int get_height(struct t_node *__n);

