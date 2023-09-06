/* dynamic_load: v1.2.1 by Marc Specht

    no warranty implied; use at your own risk

    Do this:
        #define DYNAMIC_LOAD_IMPLEMENTATION
    before you include this file in *one* C or C++ file to create the implementation.

    // i.e. it should look like this:
    #include ...
    #include ...
    #include ...
    #define DYNAMIC_LOAD_IMPLEMENTATION
    #include "dynamic_load.h"

NOTES
    Please note that you'll have to link to '-ldl' on Linux.

LICENSE

    See end of file for license information.

REVISION HISTORY:

    v1.2.1 (2023-09-06) Add notes for linux to header
    v1.2   (2023-08-17) Add documentation to header
    v1.1   (2023-07-30) Add typedef for the library handle
    v1.0   (2023-07-30) First release

*/

#ifndef _DYNAMIC_LOAD_H
#define _DYNAMIC_LOAD_H

// DOCUMENTATION
//
// Functions
//
// dyn_open
//  opens a library and returns its handle or 'NULL' on error
//
// dyn_sym
//  looks up and returns the address of a symbol (variable or function) or 'NULL' if it was not found
//
// dyn_close
//  closes a previously opened handle to a library
//
// Tip
//
// Use a typedef for functions e.g.:
//
// typedef int (*test_add_t)(int, int);
// test_add_t lib_add = (test_add_t) dyn_sym(lib, "test_add");
//

////////////////////////////////////
//
// dynamic_load includes
//

#ifdef _WIN32
    #include <windows.h> // LoadLibrary, GetProcAddress, FreeLibrary
#endif // _WIN32

#ifdef linux
    #include <dlfcn.h> // dlopen, dlsym, dlclose
#endif // linux

////////////////////////////////////
//
// dynamic_load interface
//

typedef void *DLHANDLE;

DLHANDLE dyn_open(const char *filename);
void *dyn_sym(DLHANDLE dyn_handle, const char *symbol);
int dyn_close(DLHANDLE dyn_handle);

#endif // _DYNAMIC_LOAD_H

#ifdef DYNAMIC_LOAD_IMPLEMENTATION

DLHANDLE dyn_open(const char *filename) {
    #ifdef _WIN32
        return LoadLibraryA(filename);
    #endif // _WIN32

    #ifdef linux
        // TODO: is there a way to put no flag? is this flag a good default?
        return dlopen(filename, RTLD_NOW);
    #endif // linux
}

void *dyn_sym(DLHANDLE dyn_handle, const char *symbol) {
    #ifdef _WIN32
        return (void*) GetProcAddress((HMODULE) dyn_handle, symbol);
    #endif // _WIN32
    
    #ifdef linux
        return dlsym(dyn_handle, symbol);
    #endif // linux
}

int dyn_close(DLHANDLE dyn_handle) {
    #ifdef _WIN32
        return FreeLibrary((HMODULE) dyn_handle);
    #endif // _WIN32
    
    #ifdef linux
        return dlclose(dyn_handle);
    #endif // linux
}

#endif // DYNAMIC_LOAD_IMPLEMENTATION

/*
-------------------------------------------------------------------------------
License
-------------------------------------------------------------------------------
Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------------------------------------------------------------------------------
*/
