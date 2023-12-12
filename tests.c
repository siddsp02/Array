#include "array.h"
#include <assert.h>

// Number of elements in a local stack array.
#define LEN(A) (sizeof(A) / sizeof(A[0]))
#define assert_array_equals(arr, elems) assert(len(arr) == LEN(elems) && memcmp(arr, elems, sizeof(elems)) == 0)


int main() {
    size_t i;
    array(int) arr;

    // Test creation.
    arr = arr_new(int, 1, 2, 3, 4, 5);
    
    // Values should be equal.
    assert_array_equals(arr, ((int[]){1, 2, 3, 4, 5}));

    // Popping values should remove from back.
    assert(arr_pop(arr) == 5);
    assert(arr_pop(arr) == 4);

    // Check that values were properly removed from array.
    assert_array_equals(arr, ((int[]){1, 2, 3}));

    // Check that removing at a middle index works.
    arr_remove_at(arr, 1);
    assert_array_equals(arr, ((int[]){1, 3}));

    // Test element insertion.
    arr_insert(arr, 1, 2);
    assert_array_equals(arr, ((int[]){1, 2, 3}));

    // Test appending/pushing elements more than initial capacity.
    for (i = 0; i < 10; ++i)
        arr_push(arr, i + 4);

    assert_array_equals(arr, ((int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}));

    // Test removing multiple elements from the front of the array.
    for (i = 0; i < 10; ++i)
        arr_remove_at(arr, 0);
    
    assert_array_equals(arr, ((int[]){11, 12, 13}));

    arr_free(arr);

    arr = arr_fill(int, -1, 10);
    assert_array_equals(arr, ((int[]){[0 ... 9] = -1}));

    for (i = 0; i < 10; ++i)
        arr[i] = 10 - i;
    
    // Test sorting.
    assert_array_equals(arr, ((int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    sort(arr);
    assert_array_equals(arr, ((int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    
    // Test binary search.
    int *x = binarysearch(arr, 3);
    assert((x - arr) == 2);

    arr_free(arr);
}
