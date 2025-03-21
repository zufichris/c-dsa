#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int *data;    // Pointer to the array data
    int size;     // Current number of elements
    int capacity; // Maximum number of elements
} Array;

// Function prototypes
Array* array_create(int capacity);
void array_destroy(Array *arr);
int array_insert(Array *arr, int value);
int array_get(Array *arr, int index);

#endif
