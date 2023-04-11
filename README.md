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

array primes(uint64_t n) {
    uint64_t i, j;
    bool sieve[n];        // Use a VLA for the sieve.
    array ret;
    memset(sieve, 1, n);  // Set all values to 'true'.
    memset(sieve, 0, 2);  // 0 and 1 are not prime.
    for (i = 2; i < sqrt(n); ++i)
        if (sieve[i])
            for (j = i * i; j < n; j += i)
                sieve[j] = 0;
    ret = arr_new(uint64_t);
    for (i = 0; i < n; ++i)
        if (sieve[i])
            arr_push(&ret, i);
    return ret;
}

int main() {
    size_t i;
    array arr = primes(10000);
    /* Explicit casting is needed since the
       data field is a void pointer. */
    for (i = 0; i < arr.size; ++i)
        printf("%llu\n", ((uint64_t *) arr.data)[i]);
    arr_dest(&arr); // Free array from memory.
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
I plan on updating this and showing more examples in the future. For now, this is one example of a program.
