#include "array.h"
#include <stdio.h>
#include <stdlib.h>

#define handleError(status, func_name, context)                                \
  do {                                                                         \
    if (status != ARRAY_SUCCESS) {                                             \
      arrayHandleError(status, func_name, context);                            \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
  } while (0)

int main() {
  printf("Creating array of capacity 100\n");
  Array array;
  ArrayStatus status;

  status = arrayCreate(&array, 100);
  handleError(status, "arrayCreate", " failed to initialize array");

  status = arrayInsert(&array, 4);
  handleError(status, "arrayInsert", " inserting value 4");

  status = arrayInsert(&array, 10);
  handleError(status, "arrayInsert", " inserting value 10");

  arrayPrint(&array);

  int value;
  status = arrayGet(&array, 0, &value);
  if (status == ARRAY_SUCCESS) {
    printf("Value at index 0: %d\n", value);
  } else {
    arrayHandleError(status, "arrayGet", " getting index 0");
  }

  for (int i = 0; i < 98; i++) {
    char context[32];
    snprintf(context, sizeof(context), " inserting value %d at iteration %d",
             i + 11, i);
    status = arrayInsert(&array, i + 11);
    handleError(status, "arrayInsert", context);
  }

  status = arraySort(&array, SORT_ASC);
  handleError(status, "arraySort", " sorting array");
  arrayPrint(&array);

  int index;
  arrayFind(&array, 4, &index);
  if (status == ARRAY_SUCCESS) {
    printf("Found value 4 at index %d\n", index);
  } else {
    arrayHandleError(status, "arrayFind", " finding value 4");
  }

  status = arrayDestroy(&array);
  handleError(status, "arrayDestroy", " destroying array");

  printf("Program completed successfully\n");
  return EXIT_SUCCESS;
}
