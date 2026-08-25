#include "../include/utils.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/* TODO: random values for testing ?? not just here?? */

int main()
{
    /* creating a location */
    struct location_node *test_loc = create_loc("file1", 1);
    assert(test_loc->capacity == STARTCAP);
    assert(test_loc->size == 1);
    assert(test_loc->next == NULL);
    /* adding the first line */
    assert(test_loc->lines[0] == 1);
    assert(strcmp(test_loc->filename, "file1") == 0);
    /* test clear on list size 1 */
    clear_loc_list(test_loc);

    /* adding multiple lines */
    /* dynamic resizing */
    test_loc = create_loc("file1", 1);
    size_t i;
    for (i = 1; i <= 5; ++i)
        push_back_line(test_loc, i);
    for (i = 1; i <= 5; ++i)
        assert(test_loc->lines[i-1] == i);

    push_back_line(test_loc, 6);
    assert(test_loc->capacity == 10);
    assert(test_loc->size == 6);
    assert(test_loc->next == NULL);
    for (i = 1; i <= 6; ++i)
        assert(test_loc->lines[i-1] == i);

    for (i = 7; i <= 21; ++i)
        push_back_line(test_loc, i);
    assert(test_loc->capacity == 40);
    assert(test_loc->size == 21);
    assert(test_loc->next == NULL);
    for (i = 1; i <= 21; ++i)
        assert(test_loc->lines[i-1] == i);
    clear_loc_list(test_loc);

    /* TODO: checking whether a filename exists?
     *  don't need to test clear on a list, that will happen in the tree/hash */

    printf("\n✅ Passed\n");
    return 0;
}
