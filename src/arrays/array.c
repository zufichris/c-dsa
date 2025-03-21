#include "array.h"
#include <stdlib.h>

Array* array_create(int capacity) {
    Array *arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    arr->data = (int*)malloc(capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

void array_destroy(Array *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

int array_insert(Array *arr, int value) {
    if (!arr || arr->size >= arr->capacity) return -1; // Error: full or null
    arr->data[arr->size] = value;
    arr->size++;
    return 0; // Success
}

int array_get(Array *arr, int index) {
    if (!arr || index < 0 || index >= arr->size) return -1; // Error: invalid
    return arr->data[index];
}
