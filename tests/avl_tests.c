#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"

/* Functions to check structure
 * i.e. functions that run through the whole tree? 
 * 1. BST Value structure 
 * 2. Balanced
 * 3. Heights are correct? 
 *
 * Edge Cases:
 * - Small Trees
 *   - 3 elements, leftright / rightleft rotate and regular
 * - Max Element Trees
 * - Sorted input, unsorted input etc, and then size for test of runtime, graph it!
 *
 *
 *
 *  -> maybe use something like a to_string function!! also useful for the program...
 */

/* TODO: ALSO USE THIS WITH REAL INPUT, i.e. stuff that isn't one character long */

/* TODO: CHANGE TO MATCH NEW TOP LEVEL STRUCT FORMAT */

bool avl_validate(struct tree_node *root);
bool test_is_bst();

int main()
{
    /* empty tree */
    struct tree test_tree = create_tree();
    assert(test_tree.root == NULL);

    /* one node */
    assert(tree_insert(&test_tree, "key", "file1", 1));
    struct tree_node *root = test_tree.root;
    assert(root->height == 0);
    assert(root->left == NULL && root->right == NULL);
    assert(strcmp(root->key, "key") == 0);
    /* we test location separately, but make sure we assign the list */
    assert(root->loc_list->lines[0] == 1);
    assert(strcmp(root->loc_list->filename, "file1") == 0);

    /* duplicate key */
    tree_insert(&test_tree, "key", "file1", 2);
    assert(root->height == 0);
    assert(root->left == NULL && root->right == NULL);
    assert(strcmp(root->key, "key") == 0);
    assert(root->loc_list->lines[0] == 1);
    assert(root->loc_list->lines[1] == 2);
    struct location_node *old_head = root->loc_list;

    /* same key new file */
    tree_insert(&test_tree, "key", "new_file", 4);
    assert(root->height == 0);
    assert(root->left == NULL && root->right == NULL);
    assert(strcmp(root->key, "key") == 0);
    assert(strcmp(root->loc_list->filename, "new_file") == 0);
    assert(root->loc_list->lines[0] == 4);
    assert(root->loc_list->next == old_head);
    tree_clear(&test_tree);

    /* avl property tests */
    test_is_bst();

    /* all four rotations both with the minimum rotation size
     * and the 'maximum' number of nodes involved in any full rotation process */

    /*********************
     *  trees of size 3  *
     *********************/
    /* Left(a) */
    tree_insert(&test_tree, "a", "", 0);
    tree_insert(&test_tree, "b", "", 0);
    tree_insert(&test_tree, "c", "", 0);
    tree_clear(&test_tree);

    

    /************************
     *  Max Size Rotations  *
     ************************/

    /*********************
     *  Chained Inserts  *
     *  i.e. one insert breaks, and keep inserting to more breaks, etc 
     *********************/

    //multiple rotations
    //search
    //deletion (if implementing it)
    //destruction
    printf("\n✅ Passed\n");

    return 0;
}

bool avl_validate(struct tree_node *root)
{
    if (root == NULL)
        return true;


    bool is_bst(struct tree_node *, char **);
    bool valid_heights(struct tree_node *, int *);
    bool is_balanced(struct tree_node *);

    int height;

    char *pkey = NULL;
    return is_bst(root, &pkey) &&
           valid_heights(root, &height) &&
           is_balanced(root);
}

/* inorder visits in increasing order, store previous to check the next node,
 * prev as ptr to ptr to char allows us to retain the pointer through recursive backtrack */

bool is_bst(struct tree_node *root, char **prev)
{
    if (root == NULL)
        return true;

    /* if any left subtree is invalid, tree is invalid */
    if (!is_bst(root->left, prev))
        return false;

    /* stricly increasing order, check if we have stored a prev key yet */
    if (*prev != NULL && strcmp(root->key, *prev) <= 0)
        return false;

    /* store for next node check */
    *prev = root->key;

    return is_bst(root->right, prev);
}

/* TODO: combine valid_heights and is_balanced, avoids mulitple of the same recursive traversals */
bool valid_heights(struct tree_node *root, int *height)
{
    if (!root)
    {
        *height = -1;   /* define a null node to be a height of -1 */
        return true;
    }

    int height_l;
    int height_r;
    
    if (valid_heights(root->left, &height_l) && valid_heights(root->right, &height_r))
    {
        int max_child = (height_l > height_r) ? height_l : height_r;
        *height = 1 + max_child;
        return root->height == *height; 
    }

    return false;
}

/* since we validate the heights of each node first,
 * we can use them here */
bool is_balanced(struct tree_node *root)
{
    if (!root)
        return true;

    if (is_balanced(root->left) && is_balanced(root->right))
    {
        int bf = abs(get_height(root->left) - get_height(root->right));
        return bf <= 1; /* return true if balance */
    }
    else
        return false; /* a subtree is broken */
}

bool test_is_bst()
{
    /* empty tree */
    struct tree test_tree = create_tree();
    struct tree_node **root = &test_tree.root;
    char *pkey = NULL;

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* one node */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* valid: root + left */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");
    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("a");

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* valid: root + right */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");
    (*root)->right = create_tree_node();
    (*root)->right->key = str_dup("c");

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* valid: three-node tree */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");

    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("a");

    (*root)->right = create_tree_node();
    (*root)->right->key = str_dup("c");

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* invalid: left child > root */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");
    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("c");

    assert(!is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* invalid: right child < root */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");
    (*root)->right = create_tree_node();
    (*root)->right->key = str_dup("a");

    assert(!is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* invalid: duplicate key */
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("b");
    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("b");

    assert(!is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /*
     * invalid: deep violation
     *
     *       c
     *      / \
     *     b   d
     *        /
     *       a
     *
     */
    test_tree = create_tree();
    root = &test_tree.root;
    pkey = NULL;

    *root = create_tree_node();
    (*root)->key = str_dup("c");

    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("b");

    (*root)->right = create_tree_node();
    (*root)->right->key = str_dup("d");

    (*root)->right->left = create_tree_node();
    (*root)->right->left->key = str_dup("a");

    assert(!is_bst(*root, &pkey));
    tree_clear(&test_tree);
    return true;
}
