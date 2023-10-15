#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <string.h>

typedef struct { size_t size, capacity; } _array;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define array(T) T *
#define arr_data(arr) (((_array *) arr) - 1) 
#define arr_new(T, ...) ({                                 \
    T tmp[] = { __VA_ARGS__ };                             \
    _array *ptr = malloc(sizeof(_array) + max(8*sizeof(T), sizeof(tmp))); \
    *ptr = (_array) { sizeof(tmp) / sizeof(T), max(8*sizeof(T), sizeof(tmp)) / sizeof(T) }; \
    (T *) memcpy(++ptr, tmp, sizeof(tmp));                 \
})
#define arr_fill(T, val, len) ({                           \
    _array *ptr = malloc(sizeof(_array) + len * sizeof(T));\
    ptr->size = ptr->capacity = len;                       \
    for (size_t i = 0; i < len; ++i)                       \
        ((T *) (ptr + 1))[i] = val;                        \
    (T *) ++ptr;                                           \
})
#define each(item, arr) (typeof(arr) item = arr; item != &arr[len(arr)]; ++item)
#define reversed(item, arr)  (typeof(arr) item = &arr[len(arr)-1]; item != arr - 1; --item)
#define len(arr) ({ arr_data(arr)->size; })
#define cap(arr) ({ arr_data(arr)->capacity; })
#define arr_resize(arr, new_capacity) do {                 \
    arr_data(arr)->capacity = new_capacity;                \
    _array *tmp = realloc(arr_data(arr), sizeof(_array) + cap(arr) * sizeof(*arr)); \
    arr = (typeof(arr)) (++tmp);                           \
} while (0)
#define arr_insert(arr, i, elem) do {                      \
    len(arr) == cap(arr) ? arr_resize(arr, cap(arr)*2) : 0;\
    memmove(arr+(i)+1, arr+(i), (arr_data(arr)->size++ - (i)) * sizeof(*arr)); \
    arr[i] = elem;                                         \
} while (0)
#define arr_push(arr, elem) arr_insert(arr, (len(arr)-1), elem)
#define arr_pop(arr) ({ arr[--arr_data(arr)->size]; })
#define arr_remove_at(arr, i) memmove(arr+(i), arr+(i+1), (--arr_data(arr)->size - (i)) * sizeof(*arr))
#define arr_dest(arr) free(arr_data(arr))
#define arr_qsort(arr, cmp) qsort(arr, len(arr), sizeof(*arr), cmp)
#define arr_bsearch(arr, key, cmp) bsearch(key, arr, len(arr), cmp)
#endif  /* ARRAY_H */
