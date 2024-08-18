#ifndef vm_h
#define vm_h

#include "dArray.h"
// #include "table.h"
#include "value.h"

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

#define STACK_MAX 256
typedef struct {
  DArray *token_bag;
  char *ip;
  int tos;
  int iStack[STACK_MAX]; // integers
  Value stack[STACK_MAX];
  Value *stack_top;
} VM;

VM initVM(DArray *token_bag);
void freeVM(VM *vm);

InterpretResult interpret(char *source);
void push(VM *vm, Value *value);
Value pop(VM *vm);

#endif
