#ifndef vm_h
#define vm_h

#include "dArray.h"
// #include "table.h"
// #include "value.h"

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

#define STACK_MAX 256
typedef struct {
  DArray *token_bag;
  uint8_t *ip;
} VM;

InterpretResult interpret(char *source);
/* void push(Value value); */
/* Value pop(); */

#endif
