// test_lib
// $: gcc -shared -o test_lib.so test_lib.c

int test_var = 9;

int test_add(int a, int b) {
    return a + b;
}