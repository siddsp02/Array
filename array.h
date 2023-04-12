#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <string.h>

typedef struct { size_t size, capacity; } _array;

#define array(T) T *
#define arr_data(arr) ((_array *) (arr) - 1) 
#define arr_new(T) ({                                      \
    char *ptr = malloc(sizeof(_array) + 8 * sizeof(T));    \
    ptr += sizeof(_array);                                 \
    arr_data(ptr)->size = 0;                               \
    arr_data(ptr)->capacity = 8;                           \
    (T *) ptr;                                             \
})
#define arr_fill(T, val, len) ({\
    char *ptr = malloc(sizeof(_array) + len * sizeof(T));  \
    ptr += sizeof(_array);                                 \
    arr_data(ptr)->size = 0;                               \
    arr_data(ptr)->capacity = len;                         \
    for (size_t i = 0; i < len; ++i)                       \
        ptr[i] = val;                                      \
    (T *) ptr;                                             \
})
#define len(arr) ({ arr_data(arr)->size; })
#define arr_cap(arr) ({ arr_data(arr)->capacity; })
#define arr_resize(arr, new_capacity) do {                 \
    arr_data(arr)->capacity = new_capacity;                \
    _array *tmp = realloc(arr_data(arr), sizeof(_array) + new_capacity * sizeof(*arr)); \
    arr = (typeof(arr)) (((char *) tmp) + sizeof(_array)); \
} while (0)
#define arr_push(arr, elem) do {                           \
    if (arr_cap(arr) == len(arr))                          \
        arr_resize(arr, arr_cap(arr) * 2);                 \
    arr[arr_data(arr)->size++] = elem;                     \
} while (0)
#define arr_pop(arr) ({ arr[--arr_data(arr)->size]; })
#define arr_insert(arr, i, elem) do {                      \
    if (arr_cap(arr) == len(arr))                          \
        arr_resize(arr, arr_cap(arr) * 2);                 \
    memmove(arr + i + 1, arr + i, (arr_data(arr)->size++ - i) * sizeof(*arr)); \
    arr[i] = elem;                                         \
} while (0)
#define arr_remove_at(arr, i) memmove(arr + (i), arr + (i+1), (--arr_data(arr)->size - (i)) * sizeof(*arr))
#define arr_dest(arr) free(arr_data(arr))
#define arr_qsort(arr, cmp) qsort(arr, arr_len(arr), sizeof(*arr), cmp)
#define arr_bsearch(arr, key, cmp) bsearch(key, arr, arr_size(arr), cmp)
#endif  /* ARRAY_H */
