#include "../../utils/common.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>

#define handleError(status, func_name, context)                                \
  do {                                                                         \
    if ((status) != ARRAY_SUCCESS) {                                           \
      arrayHandleError((status), (func_name), (context));                      \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
  } while (0)

int main() {
  printSeparator("Array Demo");

  printf("Step 1: Creating array of capacity 10\n");
  Array array;
  ArrayStatus status = arrayCreate(&array, 10);
  handleError(status, "arrayCreate", "failed to initialize array");

  printSeparator("Initial Insertions");
  int initial_values[] = {4, 10, 2, 7};
  for (int i = 0; i < 4; i++) {
    status = arrayInsert(&array, initial_values[i]);
    handleError(status, "arrayInsert", "inserting initial values");
  }
  arrayPrint(&array);

  printSeparator("Bulk Insertion");
  for (int i = 0; i < 6; i++) { // Fill up to capacity 10
    int value = 20 + i * 2;
    status = arrayInsert(&array, value);
    handleError(status, "arrayInsert", "bulk insert");
  }
  arrayPrint(&array);

  printSeparator("Get and Update Value");
  int value;
  status = arrayGet(&array, 2, &value);
  if (status == ARRAY_SUCCESS)
    printf("Value at index 2: %d\n", value);

  status = arraySet(&array, 2, 99);
  if (status == ARRAY_SUCCESS)
    printf("Updated index 2 to 99\n");
  arrayPrint(&array);

  printSeparator("Find Value");
  int index;
  status = arrayFind(&array, 99, &index);
  if (status == ARRAY_SUCCESS)
    printf("Found value 99 at index %d\n", index);
  else
    arrayHandleError(status, "arrayFind", "finding value 99");

  printSeparator("Remove Value");
  status = arrayDelete(&array, 2);
  if (status == ARRAY_SUCCESS)
    printf("Removed value at index 2\n");
  arrayPrint(&array);

  printSeparator("Sorting Array Ascending");
  status = arraySort(&array, SORT_ASC);
  handleError(status, "arraySort", "sorting ascending");
  arrayPrint(&array);

  printSeparator("Sorting Array Descending");
  status = arraySort(&array, SORT_DESC);
  handleError(status, "arraySort", "sorting descending");
  arrayPrint(&array);

  printSeparator("Destroy Array");
  status = arrayDestroy(&array);
  handleError(status, "arrayDestroy", "destroying array");

  printf("Program completed successfully\n");
  return EXIT_SUCCESS;
}
