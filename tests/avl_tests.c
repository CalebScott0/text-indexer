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
 * also have to check lines array.. 
 *  and that the lines array resizes properly with values and capacity
 */

/* TODO: ALSO USE THIS WITH REAL INPUT, i.e. stuff that isn't one character long */
bool avl_validate(struct t_node *root);
bool test_is_bst();

int main()
{
    assert(test_is_bst());
    struct t_node *root = NULL;

    /*********************
     *  trees of size 3  *
     *********************/

    /* left_rotate(a) after "c" insert */
    root = insert(root, "a", 12);
    root = insert(root, "b", 12);
    root = insert(root, "c", 12);
    assert(avl_validate(root));
    clear(root);
    root = NULL;

    /* right_rotate(c) after "a" insert */
    root = insert(root, "c", 12);
    root = insert(root, "b", 12);
    root = insert(root, "a", 12);
    assert(avl_validate(root));
    clear(root);
    root = NULL;

    /* right_rotate(c) -> left_rotate(a) */
    root = insert(root, "a", 12); 
    root = insert(root, "c", 12); 
    root = insert(root, "b", 12); 
    assert(avl_validate(root));
    clear(root);
    root = NULL;

    /* left_rotate(a) -> right_rotate(b) */
    root = insert(root, "c", 12); 
    root = insert(root, "a", 12); 
    root = insert(root, "b", 12); 
    assert(avl_validate(root));
    clear(root);
    root = NULL;

    /*********************
     *    Bigger Trees   *
     *********************/

    /* left_rotate(b) -> right_rotate(e) */
    root = insert(root,"e", 12);
    root = insert(root,"g", 12);
    root = insert(root,"b", 12);
    root = insert(root,"a", 12);
    root = insert(root,"d", 12);
    root = insert(root,"c", 12);
    assert(avl_validate(root));
    clear(root);
    root = NULL;



    /*********************
     *  Chained Inserts  *
     *  i.e. one insert breaks, and keep inserting to more breaks, etc 
     *********************/

    printf("✅ Passed");

    return 0;
}

bool avl_validate(struct t_node *root)
{
    if (root == NULL)
        return true;

    bool is_bst(struct t_node *);
    bool valid_heights(struct t_node *, int *);
    bool is_balanced(struct t_node *);

    int height;

    return is_bst(root) &&
           valid_heights(root, &height) &&
           is_balanced(root);
}

/* we assume root to exist */
/* TODO: optionally can change to accept a null root,
 * if the args passed in from avl_validate 
 * follow the minimum / maximum value check
 * where the first char of min string is '\0'
 * and the first char of the max string is (char) ('z' + 1)
 *      which here we use the fact that our keys are tokens (words)
 *      and must start with an alpha char?
 */
bool is_bst(struct t_node *root)
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

bool valid_heights(struct t_node *root, int *height)
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
bool is_balanced(struct t_node *root)
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
    struct t_node *root = NULL;
    root = insert(root, "b", 1);
    root = insert(root, "c", 1);
    //root->right->right = create_node()

    if (!is_bst(root))
    {
        clear(root);
        return false;
    }

    clear(root);

    return true;
}
