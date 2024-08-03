#ifndef dArray_h
#define dArray_h

#include "common.h"

// memory tools, mostly just calling reallocate()
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type *)reallocate(pointer, sizeof(type) * (oldCount),                       \
                     sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

typedef enum {
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
} dArray;

// dArray
void initdArray(dArray *darray);
void freedArray(dArray *darray);
void writedArray(dArray *darray, uint8_t byte);

// memory
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
