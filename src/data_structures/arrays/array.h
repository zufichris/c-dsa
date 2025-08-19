#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  int *data;
  int capacity;
  int length;
} Array;

typedef enum {
  ARRAY_SUCCESS = 0,
  ARRAY_NULL = 1,
  ARRAY_OUT_OF_BOUNDS = 2,
  ARRAY_FULL = 3,
  ARRAY_MEMORY = 4,
  ARRAY_INVALID_CAPACITY = 5,
  ARRAY_NOTFOUND = 6
} ArrayStatus;

typedef enum { SORT_DESC = -1, SORT_ASC = 1 } SortDir;

ArrayStatus arrayCreate(Array *, int capacity);
ArrayStatus arrayDestroy(Array *);
ArrayStatus arrayInsert(Array *, int value);
ArrayStatus arrayDelete(Array *, int index);
ArrayStatus arraySet(Array *, int value, int index);
ArrayStatus arrayGet(Array *, int index, int *out_value);
int arrayFind(Array *, int value, int *index);
ArrayStatus arraySort(Array *, SortDir);
void arrayPrint(Array *);
ArrayStatus arrayResize(Array *, int new_capacity);
void arrayHandleError(ArrayStatus status, const char *func_name,
                      const char *context);

#endif // !ARRAY_H
