# Arrays in C

## Introduction
An array is a contiguous block of memory storing elements of the same type.

## Implementation
This repo implements a dynamic array with a fixed capacity. Key functions:
- `array_create`: Allocates the array.
- `array_insert`: Adds an element.
- `array_get`: Retrieves an element.

## Usage Example
```c
Array *arr = array_create(5);
array_insert(arr, 10);
printf("%d\n", array_get(arr, 0)); // Outputs: 10
array_destroy(arr);
