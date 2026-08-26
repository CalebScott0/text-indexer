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
bool is_balanced(struct tree_node *root);
bool valid_heights(struct tree_node *root, int *height);
/* TODO: */
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

    /* all four rotations both with the minimum rotation size
     * and the 'maximum' number of nodes involved in any full rotation process */

    /*********************
     *  trees of size 3  *
     *********************/

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

    bool is_bst(struct tree_node *);
    bool valid_heights(struct tree_node *, int *);
    bool is_balanced(struct tree_node *);

    int height;

    return is_bst(root) &&
           valid_heights(root, &height) &&
           is_balanced(root);
}

/* TODO: optionally can change to accept a null root,
 * if the args passed in from avl_validate 
 * follow the minimum / maximum value check
 * where the first char of min string is '\0'
 * and the first char of the max string is (char) ('z' + 1)
 *      which here we use the fact that our keys are tokens (words)
 *      and must start with an alpha char?
 */
/* we assume root to exist */
bool is_bst(struct tree_node *root)
{
    if (!root->left && !root->right)
        return true;

    if (root->left && strcmp(root->key, root->left->key) < 0) 
        return false; /* root < left */

    if (root->right && strcmp(root->key, root->right->key) > 0) 
        return false; /* root > right */

    bool is_right = root->right ? is_bst(root->right) : true;
    bool is_left = root->left ? is_bst(root->left) : true;

    return is_right && is_left;
}

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

/* TODO: TEST THE ABOVE 3 FUNCTIONS for checks lol, gotta test the tests */
bool test_is_bst()
{
    return false;
}
