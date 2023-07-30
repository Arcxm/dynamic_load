#include <stdio.h>

#define DYNAMIC_LOAD_IMPLEMENTATION
#include "dynamic_load.h"

typedef int (*test_add_t)(int, int);

int main(void) {
    // Open library handle
    void *lib = dyn_open("test_lib.so");

    if (lib) {
        // Please note that I have skipped checking the 2 symbols against 'NULL' for simplicity
        int *test_var = dyn_sym(lib, "test_var");
        test_add_t test_add = dyn_sym(lib, "test_add");

        int result = test_add(*test_var, 100);
        fprintf(stdout, "%d + 100 = %d\n", *test_var, result);

        // We're done, close the handle to the library
        dyn_close(lib);
    } else {
        fprintf(stderr, "Could not load library!\n");
    }
}
