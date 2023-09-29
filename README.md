# Array

Flexible dynamic arrays and array functions.
This was a dynamic array implementation in C which I did in less than 60 lines of code for fun.
There are a lot of issues with this, but it's cool to see how many tricks there are in the C
language for writing less code :)

# Examples

Here is an example of using an array for finding all prime numbers less than 10,000.

```C
#include "array.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

array(int) primes(int n) {
    int i, j;
    bool sieve[n];        // Use a VLA for the sieve.
    array(int) ret;
    memset(sieve, 1, n);  // Set all values to 'true'.
    memset(sieve, 0, 2);  // 0 and 1 are not prime.
    for (i = 2; i < sqrt(n); ++i)
        if (sieve[i])
            for (j = i * i; j < n; j += i)
                sieve[j] = 0;
    ret = arr_new(int);
    for (i = 0; i < n; ++i)
        if (sieve[i])
            arr_push(ret, i);
    return ret;
}

int main() {
    size_t i;
    array(int) arr = primes(10000);
    // Use a for-each loop to loop over elements.
    for each(item, arr)
        printf("%d\n", *item);
    arr_dest(arr); // Free array from memory.
    return 0;
}
```
When running this, we get the following output:
```
2
3
5
...
9973
```
Dynamic arrays can also be initialized with 0 or more elements similar to a primitive array in C.
This includes initializes indices and even ranges of indices to specified values.

```C
#include "array.h"
#include <stdio.h>

/* A program that creates an array of the fibonacci numbers. */

int main() {
    size_t i;
    /* Arguments to the right of the type are the same as
       array initializer values. 
       As an example:
       
       array(int) arr = arr_new(int, 0, 1);  // First and second fibonacci numbers are 0 and 1.
       
       is equivalent to
       
       int arr[] = {0, 1};  */
    array(int) arr = arr_new(int, 0, 1);
    for (i = 1; i < 10; ++i)
        arr_push(arr, arr[i] + arr[i-1]);
    for each(item, arr)
        printf("%d ", *item);
    return 0;
}
```
Since `arr_new(T, ...)` is variadic in nature, you can also initialize an empty array
by just using `arr_new(T)`, where T is the element type of the array.

`arr_new(T, ...)` also allows setting ranges and indices to specified values. If you
want to create a dynamic array of ints with 10 initial values, each of them being -1,
you would just have to call `arr_new(int, [0 ... 0] = -1)`.
