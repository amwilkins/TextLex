#include <stdlib.h>

#include "dArray.h"

// Create the dynamic array
void initdArray(dArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->code = NULL;
}

void freedArray(dArray *array) {
  // Free the array
  FREE_ARRAY(uint8_t, array->code, array->capacity);
  // Reinitialize the array to zero out it's values
  initdArray(array);
}

// Write to the array
void writedArray(dArray *darray, uint8_t byte) {
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
  // Remove the dArray if newSize is 0
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
