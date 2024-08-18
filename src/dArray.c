#include <stdlib.h>

#include "dArray.h"
#include "parser.h"

// Create the dynamic array
void initDArray(DArray *array, size_t element_size) {
  array->capacity = 0;
  array->count = 0;
  array->element_size = element_size;
  array->code = NULL;
}

void freeDArray(DArray *array) {
  size_t element_size = sizeof(array->element_size);
  // Free the array
  reallocate(array->code, sizeof(array->element_size) * (array->capacity), 0);
  // Reinitialize the array to zero out it's values
  initDArray(array, element_size);
}

// Write to the array
void writeDArray(DArray *darray, void *element) {
  // If the array is full, double the size
  if (darray->capacity < darray->count + 1) {
    int oldCapacity = darray->capacity;
    darray->capacity = (oldCapacity) < 8 ? 8 : (oldCapacity) * 2;
    darray->code = reallocate(darray->code, oldCapacity * darray->element_size,
                              darray->capacity * darray->element_size);
  }

  // Determine the type to cast to
  size_t type_size = darray->element_size;

  // Cast as proper type
  // Add more types as needed
  if (type_size == sizeof(int)) {
    ((int *)darray->code)[darray->count] = *(int *)element;
  } else if (type_size == sizeof(double)) {
    ((double *)darray->code)[darray->count] = *(double *)element;
  } else if (type_size == sizeof(char)) {
    ((char *)darray->code)[darray->count] = *(char *)element;
  } else if (type_size == sizeof(Token)) {
    ((Token *)darray->code)[darray->count] = *(Token *)element;
  }
  darray->count++;
}

// Grow the array
void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  // Remove the DArray if newSize is 0
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, newSize);

  // Out of memory error
  if (result == NULL)
    exit(1);
  return result;
}
