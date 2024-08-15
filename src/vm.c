#include "vm.h"
#include "dArray.h"
#include "parser.h"

VM initVM(DArray *token_bag) {
  VM vm;
  vm.token_bag = token_bag;
  return vm;
}

InterpretResult run() { return INTERPRET_OK; }

InterpretResult interpret(char *source) {
  DArray token_bag;
  initDArray(&token_bag);

  VM vm = initVM(&token_bag);

  // fill the chunk with instructions
  if (!parse(source, &token_bag)) {
    freeDArray(&token_bag);
    printf("Failed to parse\n");
  }
  InterpretResult result = run();

  freeDArray(&token_bag);

  return result;
}
