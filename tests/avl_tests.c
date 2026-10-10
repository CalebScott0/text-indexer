#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"



/* TODO: ALSO USE THIS WITH REAL INPUT, i.e. stuff that isn't one character long */
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
 *  -> maybe use something like a to_string function!! also useful for the program...
 */

bool avl_validate(struct tree_node *root);
bool test_is_bst();
bool test_is_balanced_heights();

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
    test_is_balanced_heights();

    /* all four rotations both with the minimum rotation size
     * and the 'maximum' number of nodes involved in any full rotation process */

    /*********************
     *  trees of size 3  *
     *********************/
    tree_insert(&test_tree, "a", "", 0);  
    tree_insert(&test_tree, "b", "", 0);  
    tree_insert(&test_tree, "c", "", 0);  
    assert(avl_validate(test_tree.root));
    tree_clear(&test_tree);

    tree_insert(&test_tree, "c", "", 0);  
    tree_insert(&test_tree, "b", "", 0);  
    tree_insert(&test_tree, "a", "", 0);  
    assert(avl_validate(test_tree.root));
    tree_clear(&test_tree);

    tree_insert(&test_tree, "a", "", 0);  
    tree_insert(&test_tree, "c", "", 0);  
    tree_insert(&test_tree, "b", "", 0);  
    assert(avl_validate(test_tree.root));
    tree_clear(&test_tree);

    tree_insert(&test_tree, "c", "", 0);  
    tree_insert(&test_tree, "a", "", 0);  
    tree_insert(&test_tree, "b", "", 0);  
    assert(avl_validate(test_tree.root));
    tree_clear(&test_tree);

    /************************
     *  Max Size Rotations  *
     ************************/

    /* Left Right Rotation */
    tree_insert(&test_tree, "m", "", 0);  
    tree_insert(&test_tree, "h", "", 0);  
    tree_insert(&test_tree, "z", "", 0);  
    tree_insert(&test_tree, "d", "", 0);  
    tree_insert(&test_tree, "k", "", 0);  
    tree_insert(&test_tree, "i", "", 0);  
    assert(avl_validate(test_tree.root));
    assert(test_tree.root->key[0] == 'k');
    tree_clear(&test_tree);

    /* Right Rotation */
    tree_insert(&test_tree, "m", "", 0);  
    tree_insert(&test_tree, "h", "", 0);  
    tree_insert(&test_tree, "z", "", 0);  
    tree_insert(&test_tree, "d", "", 0);  
    tree_insert(&test_tree, "k", "", 0);  
    tree_insert(&test_tree, "g", "", 0);  
    assert(avl_validate(test_tree.root));
    assert(test_tree.root->key[0] == 'h');
    tree_clear(&test_tree);

    /* Right Left Rotation */
    tree_insert(&test_tree, "b", "", 0);  
    tree_insert(&test_tree, "a", "", 0);  
    tree_insert(&test_tree, "m", "", 0);  
    tree_insert(&test_tree, "g", "", 0);  
    tree_insert(&test_tree, "s", "", 0);  
    tree_insert(&test_tree, "k", "", 0);  
    assert(avl_validate(test_tree.root));
    assert(test_tree.root->key[0] == 'g');
    tree_clear(&test_tree);

    /*  Left Rotation */
    tree_insert(&test_tree, "b", "", 0);  
    tree_insert(&test_tree, "a", "", 0);  
    tree_insert(&test_tree, "m", "", 0);  
    tree_insert(&test_tree, "g", "", 0);  
    tree_insert(&test_tree, "s", "", 0);  
    tree_insert(&test_tree, "t", "", 0);  
    assert(test_tree.root->key[0] == 'm');
    assert(avl_validate(test_tree.root));

    /* Chained Inserts continue off the above rotated */
    tree_insert(&test_tree, "v", "", 0);  
    tree_insert(&test_tree, "d", "", 0);  
    tree_insert(&test_tree, "k", "", 0);  
    tree_insert(&test_tree, "j", "", 0);  
    tree_insert(&test_tree, "h", "", 0);  
    tree_insert(&test_tree, "r", "", 0);  
    tree_insert(&test_tree, "p", "", 0);  
    assert(avl_validate(test_tree.root));

    /*TODO: Search */

    tree_clear(&test_tree);
    printf("\n✅ Passed\n");

    return 0;
}

bool avl_validate(struct tree_node *root)
{
    if (root == NULL)
        return true;

    bool is_bst(struct tree_node *, char **);
    bool balanced_heights(struct tree_node *, int *);

    int height;
    char *pkey = NULL;

    return is_bst(root, &pkey) && balanced_heights(root, &height);
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

/* combined checks for balanced tree and correct heights of nodes */
bool balanced_heights(struct tree_node *root, int *height)
{
    if (!root)
    {
        *height = -1;   /* null node height -1 */
        return true;
    }

    int height_l, height_r;
    
    if (balanced_heights(root->left, &height_l) && balanced_heights(root->right, &height_r))
    {
        int max_child = (height_l > height_r) ? height_l : height_r;
        *height = 1 + max_child;
        int balance_factor = abs(get_height(root->left) - get_height(root->right));
        /* return true if balanced, and the correct height */
        return root->height == *height && balance_factor <= 1;
    }

    return false;
}

bool test_is_bst()
{
    /* empty tree */
    struct tree test_tree = create_tree();
    /* pointer to pointer, since test_tree.root is initialized to NULL
     * if we were to create a tree node on root as just a pointer, this
     * would no longer be the same pointer as our test_tree.root */
    struct tree_node **root = &test_tree.root;
    /* this is just used for the prev char in the recursion backtrack */
    char *pkey = NULL; 

    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    /* one node */
    pkey = NULL;
    *root = create_tree_node();
    (*root)->key = str_dup("b");
    assert(is_bst(*root, &pkey));
    
    pkey = NULL;
    /* valid: root + left */
    (*root)->left = create_tree_node();
    (*root)->left->key = str_dup("a");
    assert(is_bst(*root, &pkey));
    tree_clear(&test_tree);

    pkey = NULL;
    /* valid: root + right */
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

    /* invalid: deep violation */
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

bool test_is_balanced_heights()
{
    int height;
    struct tree test_tree = create_tree();
    struct tree_node **root = &test_tree.root;

    /* empty tree */
    assert(balanced_heights(*root, &height));

    /* single node */
    *root = create_tree_node();
    assert(balanced_heights(*root, &height));

    /* incorrect root height */
    (*root)->height = 2;
    assert(!balanced_heights(*root, &height));
    (*root)->height = 0;

    /* one left child */
    (*root)->height = 1;
    (*root)->left = create_tree_node();
    assert(balanced_heights(*root, &height));

    /* incorrect left child height */
    (*root)->left->height = 1;
    assert(!balanced_heights(*root, &height));
    (*root)->left->height = 0;


    /* one right child */
    (*root)->right = create_tree_node();
    assert(balanced_heights(*root, &height));

    /* incorrect right child height */
    (*root)->right->height = 1;
    assert(!balanced_heights(*root, &height));
    (*root)->right->height = 0;

    /* Deeper tree: */
    (*root)->height = 2;
    (*root)->right->height = 1;
    (*root)->right->right = create_tree_node();
    assert(balanced_heights(*root, &height));

    /* incorrect deep leaf height */
    (*root)->right->right->height = 2;
    assert(!balanced_heights(*root, &height));
    (*root)->right->right->height = 0;

    /* incorrect intermediary height */
    (*root)->right->height = 3;
    assert(!balanced_heights(*root, &height));
    (*root)->right->height = 1;
    free((*root)->right->right);
    (*root)->right->right = NULL;

    /* Deep left leaf: */
    (*root)->right->left = create_tree_node();
    assert(balanced_heights(*root, &height));
    /* incorrect deep leaf height */
    (*root)->right->left->height = 1;
    assert(!balanced_heights(*root, &height));
    (*root)->right->left->height = 0;

    /********************************
     *        Unbalanced trees      *
     ********************************/

    /* Unbalanced left-heavy tree: */
    tree_clear(&test_tree);
    test_tree = create_tree();
    root = &test_tree.root;
    *root = create_tree_node();
    (*root)->height = 2;
    (*root)->left = create_tree_node();
    (*root)->left->height = 1;
    (*root)->left->left = create_tree_node();
    (*root)->left->left->height = 0;
    assert(!balanced_heights(*root, &height));

    /* Unbalanced right-heavy tree: */
    tree_clear(&test_tree);
    test_tree = create_tree();
    root = &test_tree.root;
    *root = create_tree_node();
    (*root)->height = 2;
    (*root)->right = create_tree_node();
    (*root)->right->height = 1;
    (*root)->right->right = create_tree_node();
    (*root)->right->right->height = 0;
    assert(!balanced_heights(*root, &height));

    /* Unbalanced deeper subtree: */
    tree_clear(&test_tree);
    test_tree = create_tree();
    root = &test_tree.root;
    *root = create_tree_node();
    (*root)->height = 3;
    (*root)->left = create_tree_node();
    (*root)->left->height = 2;
    (*root)->left->right = create_tree_node();
    (*root)->left->right->height = 1;
    (*root)->left->right->left = create_tree_node();
    (*root)->left->right->left->height = 0;
    (*root)->right = create_tree_node();
    (*root)->right->height = 0;
    assert(balanced_heights(*root, &height) == false);

    /* Balanced tree with multiple levels: */
    tree_clear(&test_tree);
    test_tree = create_tree();
    root = &test_tree.root;
    *root = create_tree_node();
    (*root)->height = 2;
    (*root)->left = create_tree_node();
    (*root)->left->height = 1;
    (*root)->right = create_tree_node();
    (*root)->right->height = 1;
    (*root)->left->left = create_tree_node();
    (*root)->left->right = create_tree_node();
    (*root)->right->left = create_tree_node();
    (*root)->right->right = create_tree_node();
    assert(balanced_heights(*root, &height) == true);

    tree_clear(&test_tree);

    return true;
}
