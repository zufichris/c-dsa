#include "array.h"
#include <stdio.h>

int main() {
    Array *arr = array_create(3);
    if (!arr) {
        printf("Failed to create array\n");
        return 1;
    }
    array_insert(arr, 10);
    array_insert(arr, 20);
    array_insert(arr, 30);
    if (arr->size != 3) {
        printf("Insert failed: size = %d, expected 3\n", arr->size);
        array_destroy(arr);
        return 1;
    }
    if (array_get(arr, 0) != 10 || array_get(arr, 1) != 20 || array_get(arr, 2) != 30) {
        printf("Get failed\n");
        array_destroy(arr);
        return 1;
    }
    if (array_get(arr, 3) != -1) {
        printf("Out-of-bounds check failed\n");
        array_destroy(arr);
        return 1;
    }
    printf("All tests passed!\n");
    array_destroy(arr);
    return 0;
}
