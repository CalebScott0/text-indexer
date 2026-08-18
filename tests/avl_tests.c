#include <assert.h>
#include <stdio.h>

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

int main()
{
    t_node *root = NULL;

    /*********************
     *  trees of size 3  *
     *********************/

    /* left_rotate(a) after "c" insert */
    root = insert(root, "a", 12);
    root = insert(root, "b", 12);
    root = insert(root, "c", 12);
    clear(root);
    root = NULL;

    /* right_rotate(c) after "a" insert */
    root = insert(root, "c", 12);
    root = insert(root, "b", 12);
    root = insert(root, "a", 12);
    clear(root);
    root = NULL;

    /* right_rotate(c) -> left_rotate(a) */
    root = insert(root, "a", 12); 
    root = insert(root, "c", 12); 
    root = insert(root, "b", 12); 
    clear(root);
    root = NULL;

    /* left_rotate(a) -> right_rotate(b) */
    root = insert(root, "c", 12); 
    root = insert(root, "a", 12); 
    root = insert(root, "b", 12); 
    clear(root);
    root = NULL;

    /*********************
     *    Bigger Trees   *
     *********************/

    // REMEMBER you only need to test what is being changed

    return 0;
}
