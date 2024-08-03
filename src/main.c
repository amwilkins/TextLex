#include "common.h"
#include "dArray.h"
#include "input.h"

int main(int argc, const char *argv[]) {
  dArray array;
  initdArray(&array);

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    printf("ERROR: Please supply 1 file\n");
    exit(64);
  }

  return 0;
}
