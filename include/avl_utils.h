#include "../include/avl.h"

/* TODO: move these back to the source file ? */

#define MAX(A, B) ( (A) > (B)  ? (A) : (B) )

/* Initialize a tree node. Allocates memory for a struct tree_node, and assigns default values to all members.
 * returns pointer to allocated memory, or NULL if failure */
struct tree_node *create_tree_node();

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

