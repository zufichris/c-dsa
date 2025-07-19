#include "array.h"
#include <assert.h>
#include <stdio.h>

void test_array_create() {
  printf("=================Create Array Test===================\n");
  Array array;

  printf("-with invalid capacity\n");
  assert(arrayCreate(&array, -1) == ARRAY_INVALID_CAPACITY);
  assert(arrayCreate(&array, 0) == ARRAY_INVALID_CAPACITY);

  printf("-with null pointer\n");
  assert(arrayCreate(NULL, 10) == ARRAY_NULL);

  printf("-with capacity 100\n");
  assert(arrayCreate(&array, 100) == ARRAY_SUCCESS);
  assert(array.capacity == 100);
  assert(array.length == 0);
  assert(array.data != NULL);

  arrayDestroy(&array);
  printf("Create tests passed!\n\n");
}

void test_array_destroy() {
  printf("=================Destroy Array Test==================\n");
  Array array;

  printf("-destroy null pointer\n");
  assert(arrayDestroy(NULL) == ARRAY_NULL);

  printf("-destroy valid array\n");
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);
  assert(arrayDestroy(&array) == ARRAY_SUCCESS);

  printf("Destroy tests passed!\n\n");
}

void test_array_insert() {
  printf("=================Insert Test=========================\n");
  Array array;
  assert(arrayCreate(&array, 5) == ARRAY_SUCCESS);

  printf("-insert into null array\n");
  assert(arrayInsert(NULL, 10) == ARRAY_NULL);

  printf("-insert values 1,2,3,4,5\n");
  assert(arrayInsert(&array, 1) == ARRAY_SUCCESS);
  assert(array.length == 1);
  assert(arrayInsert(&array, 2) == ARRAY_SUCCESS);
  assert(arrayInsert(&array, 3) == ARRAY_SUCCESS);
  assert(arrayInsert(&array, 4) == ARRAY_SUCCESS);
  assert(arrayInsert(&array, 5) == ARRAY_SUCCESS);
  assert(array.length == 5);

  printf("-insert when array is full\n");
  assert(arrayInsert(&array, 6) == ARRAY_FULL);
  assert(array.length == 5);

  arrayDestroy(&array);
  printf("Insert tests passed!\n\n");
}

void test_array_get() {
  printf("=================Get Test============================\n");
  Array array;
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);

  int out_value;

  printf("-get from null array\n");
  assert(arrayGet(NULL, 0, &out_value) == ARRAY_NULL);

  printf("-get with null output pointer\n");
  assert(arrayGet(&array, 0, NULL) == ARRAY_NULL);

  printf("-get from empty array\n");
  assert(arrayGet(&array, 0, &out_value) == ARRAY_OUT_OF_BOUNDS);

  arrayInsert(&array, 10);
  arrayInsert(&array, 20);
  arrayInsert(&array, 30);

  printf("-get valid indices\n");
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 10);
  assert(arrayGet(&array, 1, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 20);
  assert(arrayGet(&array, 2, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 30);

  printf("-get out of bounds indices\n");
  assert(arrayGet(&array, -1, &out_value) == ARRAY_OUT_OF_BOUNDS);
  assert(arrayGet(&array, 3, &out_value) == ARRAY_OUT_OF_BOUNDS);
  assert(arrayGet(&array, 100, &out_value) == ARRAY_OUT_OF_BOUNDS);

  arrayDestroy(&array);
  printf("Get tests passed!\n\n");
}

void test_array_set() {
  printf("=================Set Test============================\n");
  Array array;
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);

  printf("-set in null array\n");
  assert(arraySet(NULL, 100, 0) == ARRAY_NULL);

  printf("-set in empty array\n");
  assert(arraySet(&array, 100, 0) == ARRAY_OUT_OF_BOUNDS);

  arrayInsert(&array, 10);
  arrayInsert(&array, 20);
  arrayInsert(&array, 30);

  printf("-set valid indices\n");
  assert(arraySet(&array, 100, 0) == ARRAY_SUCCESS);
  assert(arraySet(&array, 200, 1) == ARRAY_SUCCESS);
  assert(arraySet(&array, 300, 2) == ARRAY_SUCCESS);

  int out_value;
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 100);
  assert(arrayGet(&array, 1, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 200);
  assert(arrayGet(&array, 2, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 300);

  printf("-set out of bounds\n");
  assert(arraySet(&array, 999, -1) == ARRAY_OUT_OF_BOUNDS);
  assert(arraySet(&array, 999, 3) == ARRAY_OUT_OF_BOUNDS);

  arrayDestroy(&array);
  printf("Set tests passed!\n\n");
}

void test_array_delete() {
  printf("=================Delete Test=========================\n");
  Array array;
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);

  printf("-delete from null array\n");
  assert(arrayDelete(NULL, 0) == ARRAY_NULL);

  printf("-delete from empty array\n");
  assert(arrayDelete(&array, 0) == ARRAY_OUT_OF_BOUNDS);

  arrayInsert(&array, 10);
  arrayInsert(&array, 20);
  arrayInsert(&array, 30);
  arrayInsert(&array, 40);
  arrayInsert(&array, 50);

  printf("-delete middle element (index 2)\n");
  assert(arrayDelete(&array, 2) == ARRAY_SUCCESS);
  assert(array.length == 4);

  int out_value;
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 10);
  assert(arrayGet(&array, 1, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 20);
  assert(arrayGet(&array, 2, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 40);
  assert(arrayGet(&array, 3, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 50);

  printf("-delete first element\n");
  assert(arrayDelete(&array, 0) == ARRAY_SUCCESS);
  assert(array.length == 3);
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 20);

  printf("-delete last element\n");
  assert(arrayDelete(&array, 2) == ARRAY_SUCCESS);
  assert(array.length == 2);

  printf("-delete out of bounds\n");
  assert(arrayDelete(&array, -1) == ARRAY_OUT_OF_BOUNDS);
  assert(arrayDelete(&array, 2) == ARRAY_OUT_OF_BOUNDS);

  arrayDestroy(&array);
  printf("Delete tests passed!\n\n");
}

void test_array_find() {
  printf("=================Find Test===========================\n");
  Array array;
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);

  int index;

  printf("-find in null array\n");
  assert(arrayFind(NULL, 10, &index) == 0);

  printf("-find with null index pointer\n");
  assert(arrayFind(&array, 10, NULL) == 0);

  printf("-find in empty array\n");
  assert(arrayFind(&array, 10, &index) == 0);

  // Insert values: 10, 20, 30, 20, 40
  arrayInsert(&array, 10);
  arrayInsert(&array, 20);
  arrayInsert(&array, 30);
  arrayInsert(&array, 20);
  arrayInsert(&array, 40);

  printf("-find existing values\n");
  assert(arrayFind(&array, 10, &index) == 1);
  assert(index == 0);
  assert(arrayFind(&array, 20, &index) == 1); // Should find first occurrence
  assert(index == 1);
  assert(arrayFind(&array, 30, &index) == 1);
  assert(index == 2);
  assert(arrayFind(&array, 40, &index) == 1);
  assert(index == 4);

  printf("-find non-existing value\n");
  assert(arrayFind(&array, 100, &index) == 0);

  arrayDestroy(&array);
  printf("Find tests passed!\n\n");
}

void test_array_sort() {
  printf("=================Sort Test===========================\n");
  Array array;
  assert(arrayCreate(&array, 10) == ARRAY_SUCCESS);

  printf("-sort null array\n");
  assert(arraySort(NULL, SORT_ASC) == ARRAY_NULL);

  printf("-sort empty array\n");
  assert(arraySort(&array, SORT_ASC) == ARRAY_SUCCESS);

  arrayInsert(&array, 30);
  arrayInsert(&array, 10);
  arrayInsert(&array, 50);
  arrayInsert(&array, 20);
  arrayInsert(&array, 40);

  printf("-sort ascending\n");
  assert(arraySort(&array, SORT_ASC) == ARRAY_SUCCESS);

  int out_value;
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 10);
  assert(arrayGet(&array, 1, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 20);
  assert(arrayGet(&array, 2, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 30);
  assert(arrayGet(&array, 3, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 40);
  assert(arrayGet(&array, 4, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 50);

  printf("-sort descending\n");
  assert(arraySort(&array, SORT_DESC) == ARRAY_SUCCESS);

  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 50);
  assert(arrayGet(&array, 1, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 40);
  assert(arrayGet(&array, 2, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 30);
  assert(arrayGet(&array, 3, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 20);
  assert(arrayGet(&array, 4, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 10);

  arrayDestroy(&array);
  printf("Sort tests passed!\n\n");
}

void test_array_resize() {
  printf("=================Resize Test=========================\n");
  Array array;
  assert(arrayCreate(&array, 5) == ARRAY_SUCCESS);

  printf("-resize null array\n");
  assert(arrayResize(NULL, 10) == ARRAY_NULL);

  printf("-resize with invalid capacity\n");
  assert(arrayResize(&array, -1) == ARRAY_INVALID_CAPACITY);
  assert(arrayResize(&array, 0) == ARRAY_INVALID_CAPACITY);

  arrayInsert(&array, 1);
  arrayInsert(&array, 2);
  arrayInsert(&array, 3);
  arrayInsert(&array, 4);
  arrayInsert(&array, 5);

  printf("-resize to larger capacity\n");
  assert(arrayResize(&array, 10) == ARRAY_SUCCESS);
  assert(array.capacity == 10);
  assert(array.length == 5);

  int out_value;
  for (int i = 0; i < 5; i++) {
    assert(arrayGet(&array, i, &out_value) == ARRAY_SUCCESS);
    assert(out_value == i + 1);
  }

  printf("-resize to smaller capacity (but larger than current length)\n");
  assert(arrayResize(&array, 7) == ARRAY_SUCCESS);
  assert(array.capacity == 7);
  assert(array.length == 5);

  printf("-resize to capacity smaller than current length\n");
  assert(arrayResize(&array, 3) == ARRAY_SUCCESS);
  assert(array.capacity == 3);
  assert(array.length == 3); // Should truncate

  for (int i = 0; i < 3; i++) {
    assert(arrayGet(&array, i, &out_value) == ARRAY_SUCCESS);
    assert(out_value == i + 1);
  }

  arrayDestroy(&array);
  printf("Resize tests passed!\n\n");
}

void test_edge_cases() {
  printf("=================Edge Cases Test====================\n");
  Array array;

  printf("-single element array operations\n");
  assert(arrayCreate(&array, 1) == ARRAY_SUCCESS);
  assert(arrayInsert(&array, 42) == ARRAY_SUCCESS);

  int out_value;
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 42);

  assert(arraySet(&array, 99, 0) == ARRAY_SUCCESS);
  assert(arrayGet(&array, 0, &out_value) == ARRAY_SUCCESS);
  assert(out_value == 99);

  assert(arrayDelete(&array, 0) == ARRAY_SUCCESS);
  assert(array.length == 0);

  arrayDestroy(&array);

  printf("-large capacity array\n");
  assert(arrayCreate(&array, 1000) == ARRAY_SUCCESS);
  assert(array.capacity == 1000);
  assert(array.length == 0);

  for (int i = 0; i < 100; i++) {
    assert(arrayInsert(&array, i * 2) == ARRAY_SUCCESS);
  }
  assert(array.length == 100);

  for (int i = 0; i < 100; i++) {
    assert(arrayGet(&array, i, &out_value) == ARRAY_SUCCESS);
    assert(out_value == i * 2);
  }

  arrayDestroy(&array);
  printf("Edge cases tests passed!\n\n");
}

int main() {
  printf("Starting comprehensive array tests...\n\n");

  test_array_create();
  test_array_destroy();
  test_array_insert();
  test_array_get();
  test_array_set();
  test_array_delete();
  //test_array_find();
  //test_array_sort();
  test_array_resize();
  test_edge_cases();

  printf("===========================================\n");
  printf("ALL TESTS PASSED!\n");
  printf("===========================================\n");

  return 0;
}
