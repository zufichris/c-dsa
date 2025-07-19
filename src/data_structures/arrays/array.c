#include "array.h"
#include <stdio.h>
#include <stdlib.h>

ArrayStatus arrayCreate(Array *array, int capacity) {
  if (array == NULL) {
    return ARRAY_NULL;
  }
  *array = (Array){0};
  if (capacity <= 0)
    return ARRAY_INVALID_CAPACITY;

  array->data = malloc(capacity * sizeof(int));
  if (array->data == NULL)
    return ARRAY_MEMORY;

  array->capacity = capacity;
  array->length = 0;
  return ARRAY_SUCCESS;
}

ArrayStatus arrayDestroy(Array *array) {
  if (array == NULL)
    return ARRAY_NULL;
  free(array->data);
  array->data = NULL;
  array->length = 0;
  array->capacity = 0;
  return ARRAY_SUCCESS;
}

ArrayStatus arrayInsert(Array *array, int value) {
  if (array == NULL || array->data == NULL)
    return ARRAY_NULL;
  if (array->length >= array->capacity)
    return ARRAY_FULL;
  array->data[array->length++] = value;
  return ARRAY_SUCCESS;
}

ArrayStatus arrayDelete(Array *array, int index) {
  if (array == NULL || array->data == NULL)
    return ARRAY_NULL;
  if (index < 0 || index >= array->length)
    return ARRAY_OUT_OF_BOUNDS;
  for (int i = index; i < array->length - 1; i++)
    array->data[i] = array->data[i + 1];
  array->length--;
  return ARRAY_SUCCESS;
}

ArrayStatus arraySet(Array *array, int value, int index) {
  if (array == NULL || array->data == NULL)
    return ARRAY_NULL;
  if (index < 0 || index >= array->length)
    return ARRAY_OUT_OF_BOUNDS;
  array->data[index] = value;
  return ARRAY_SUCCESS;
}

ArrayStatus arrayGet(Array *array, int index, int *out_value) {
  if (array == NULL || array->data == NULL || out_value == NULL)
    return ARRAY_NULL;
  if (index < 0 || index >= array->length)
    return ARRAY_OUT_OF_BOUNDS;
  *out_value = array->data[index];
  return ARRAY_SUCCESS;
}

int arrayFind(Array *array, int value, int *index) { return 0; }

ArrayStatus arraySort(Array *array, SortDir sort_dir) { return ARRAY_SUCCESS; }

ArrayStatus arrayResize(Array *array, int new_capacity) {
  if (array == NULL) {
    return ARRAY_NULL;
  }
  if (new_capacity <= 0)
    return ARRAY_INVALID_CAPACITY;
  int *new_data = realloc(array->data, new_capacity * sizeof(int));
  if (new_data == NULL)
    return ARRAY_MEMORY;
  array->data = new_data;
  array->capacity = new_capacity;
  if (array->length > new_capacity)
    array->length = new_capacity;
  return ARRAY_SUCCESS;
}

void arrayPrint(Array *array) {
  if (array == NULL || array->data == NULL) {
    printf("invalid array\n");
    return;
  }
  for (int i = 0; i < array->length; i++)
    printf("[%d]\n", array->data[i]);
  printf("\n");
}

void arrayHandleError(ArrayStatus status, const char *func_name,
                      const char *context) {
  if (status == ARRAY_SUCCESS) {
    return;
  }
  fprintf(stderr, "Error in %s: ", func_name);
  switch (status) {
  case ARRAY_NULL:
    fprintf(stderr, "Array is NULL or not initialized%s\n",
            context ? context : "");
    break;
  case ARRAY_OUT_OF_BOUNDS:
    fprintf(stderr, "Index out of bounds%s\n", context ? context : "");
    break;
  case ARRAY_FULL:
    fprintf(stderr, "Array is full%s\n", context ? context : "");
    break;
  case ARRAY_MEMORY:
    fprintf(stderr, "Memory allocation failed%s\n", context ? context : "");
    break;
  case ARRAY_INVALID_CAPACITY:
    fprintf(stderr, "Invalid capacity (must be >= 1)%s\n",
            context ? context : "");
    break;
  default:
    fprintf(stderr, "Unexpected error%s\n", context ? context : "");
    break;
  }
}
