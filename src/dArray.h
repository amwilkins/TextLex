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
  OP_INTEGER,
  OP_DOUBLE,
  OP_STRING,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  size_t element_size;
  void *code;
} DArray;

// DArray
void initDArray(DArray *darray, size_t element_size);
void freeDArray(DArray *darray);
void writeDArray(DArray *darray, void *element);

// memory
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
