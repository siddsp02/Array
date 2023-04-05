/* Flexible dynamic array implementation in C. The following code is my own. */

#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t size, elem_size, capacity;
    void *data;
} array;

#define arr_new(type) (array) {                                 \
    .elem_size = sizeof(type),                                  \
    .capacity = 8,                                              \
    .data = malloc(8 * sizeof(type)),                           \
}
#define arr_fill(type, val, len) ({                             \
    array ret = {                                               \
        .size = len,                                            \
        .elem_size = sizeof(type),                              \
        .capacity = len,                                        \
        .data = malloc(len * sizeof(type)),                     \
    };                                                          \
    for (size_t i = 0; i < len; ++i)                            \
        ((type *) ret.data)[i] = val;                           \
    ret;                                                        \
})
#define arr_resize(arr, new_capacity) do {                      \
    (arr)->capacity = new_capacity;                             \
    (arr)->data = realloc((arr)->data, (arr)->capacity * (arr)->elem_size); \
} while (0)
#define arr_push(arr, elem) do {                                \
    if ((arr)->capacity == (arr)->size)                         \
        arr_resize(arr, (arr)->capacity * 2);                   \
    ((typeof(elem) *) (arr)->data)[(arr)->size++] = elem;       \
} while (0)
// Make sure to dereference when popping (e.g. int x = *(int *) arr_pop(arr)).
#define arr_pop(arr) (((char *) (arr)->data) + --(arr)->size * (arr)->elem_size)
#define arr_insert(arr, i, elem) do {                           \
    if ((arr)->capacity == (arr)->size)                         \
        arr_resize(arr, (arr)->capacity * 2);                   \
    memmove(((typeof(elem) *) (arr)->data) + i + 1, ((typeof(elem) *) (arr)->data) + i, ((arr)->size++ - i) * sizeof(elem)); \
    ((typeof(elem) *) (arr)->data)[i] = elem;                   \
} while (0)
#define arr_remove_at(arr, i) memmove(((char *) (arr)->data) + (i) * (arr)->elem_size, ((char *) (arr)->data) + ((i)+1) * (arr)->elem_size, (--(arr)->size - (i)) * (arr)->elem_size)
#define arr_dest(arr) free((arr)->data)
#define arr_qsort(arr, cmp) qsort((arr)->data, (arr)->size, (arr)->elem_size, cmp)
#define arr_bsearch(arr, key, cmp) bsearch(key, (arr)->data, (arr)->size, (arr)->elem_size, cmp)
#endif  /* ARRAY_H */
