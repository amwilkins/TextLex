#include <stdlib.h>

#include "dArray.h"

// Create the dynamic array
void initDArray(DArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->code = NULL;
}

void freeDArray(DArray *array) {
  // Free the array
  FREE_ARRAY(uint8_t, array->code, array->capacity);
  // Reinitialize the array to zero out it's values
  initDArray(array);
}

// Write to the array
void writeDArray(DArray *darray, uint8_t byte) {
  // If the array is full, double the size
  if (darray->capacity < darray->count + 1) {
    int oldCapacity = darray->capacity;
    darray->capacity = GROW_CAPACITY(oldCapacity);
    darray->code =
        GROW_ARRAY(uint8_t, darray->code, oldCapacity, darray->capacity);
  }
  // Write the byte
  darray->code[darray->count] = byte;
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
