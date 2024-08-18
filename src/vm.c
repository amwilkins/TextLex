#include "vm.h"
#include "dArray.h"
#include "parser.h"
#include "value.h"

VM initVM(DArray *token_bag) {
  VM vm;
  vm.token_bag = token_bag;
  vm.stack_top = vm.stack;
  vm.tos = -1;
  return vm;
}

void freeVM(VM *vm) { vm->token_bag = NULL; }

void push(VM *vm, Value *value) {
  vm->stack_top = value;
  vm->stack_top++;
  }

Value pop(VM *vm) {
  vm->stack_top--;
  return *vm->stack_top;
}

/* void pushInt(VM *vm, int i) { */
/*   vm->stack_top = value; */
/*   vm->stack_top++; */
/*   } */
/**/
/* Value popInt(VM *vm) { */
/*   vm->stack_top--; */
/*   return *vm->stack_top; */
/* } */

void printValue(Value value){
  printf("%g",value);
}


/* InterpretResult run(VM *vm) {  */
/*   printf("Code: &d\n", vm->ip); */
/*   for (;true;printf("loop")){ */
/*     vm->tos++; */
/*     uint8_t instruction; */
/*     switch (instruction = ){ */
/*       case OP_INTEGER:{ */
/*         int i = vm->iStack[vm->tos]; */
/*         printf("[ %i ]\n", i); */
/*         break; */
/*       } */
/*       case OP_STRING: { */
/*         break; */
/*       } */
/**/
/*       case OP_RETURN: { */
/*         return INTERPRET_OK; */
/*       }   */
/*     } */
/*   } */


  /* // debug code */
  /* printf("          "); */
  /* for (Value *slot = vm->stack; slot < vm->stack_top; slot++) { */
  /**/
  /*   printf("Stack value: "); */
  /*   printValue(*slot); */
  /* } */
  /* print("\n"); */


  /* return INTERPRET_OK; } */

InterpretResult interpret(char *source) {
  DArray token_bag;
  initDArray(&token_bag);

  VM vm = initVM(&token_bag);
  // fill the chunk with instructions
  if (!parse(source, &token_bag)) {
    freeDArray(&token_bag);
    printf("Failed to parse\n");
    return INTERPRET_COMPILE_ERROR;
  }

  /* InterpretResult result = run(&vm); */
  /**/
  /* freeDArray(&token_bag); */
  //freeVM(&vm);

  return INTERPRET_OK;
}
