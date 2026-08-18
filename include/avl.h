/* interface for an AVL tree,
 * each node stores a char * key, and a list of values */

#ifndef AVL_H
#define AVL_H

/* a tnode structure */
typedef struct t_node t_node;


/* insert: ... */ 
t_node *insert(t_node *node, const char *key, unsigned value);

/* free all allocated memory */
void clear(t_node *node);

#endif
