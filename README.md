# About dynamic_load

`dynamic_load` is a public domain single header C/C++ library to dynamically load libraries at runtime.

## Quick Start

Just include the header in your project and you're ready to go.

To create the implementation in a file, simply define `DYNAMIC_LOAD_IMPLEMENTATION` before the `#include` like this:

```c
#define DYNAMIC_LOAD_IMPLEMENTATION
#include "dynamic_load.h"
```

## Documentation

### Example

For a full example see [example.c](example.c) and the library it loads: [test_lib.c](test_lib.c).

### dyn_open

`dyn_open` opens a library and returns its handle or `NULL` on error.

```c
void *lib = dyn_open("test_lib.so");

if (lib) {
    // [do something with it and close the handle afterwards]
} else {
    // [error handling]
}
```

### dyn_sym

`dyn_sym` looks up and returns the address of a symbol (variable or function) in the library supplied by the handle or `NULL` if it was not found.

```c
// [open handle]

int *lib_var = dyn_sym(lib, "test_var");

if (lib_var) {
    // [do something with it, e.g. print it]
    fprintf(stdout, "var is %d\n", *lib_var);
} else {
    // [error handling]
}

// HINT: use a typedef for functions
typedef int (*test_add_t)(int, int);

test_add_t lib_add = (test_add_t) dyn_sym(lib, "test_add");

if (lib_add) {
    // [call the function and do stuff with it]
} else {
    // [error handling]
}
```

### dyn_close

`dyn_close` closes a previously opened handle to a library.

```c
// [open library and do stuff with it]

dyn_close(lib);
```