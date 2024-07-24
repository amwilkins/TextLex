#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

// read execute print loop
static void repl() {
  // limited line size
  char line[1024];

  // forever
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    parseString(line);
  }
}

// read the file from a path
static char *readFile(const char *path) {
  FILE *file;
  char *buffer;

  file = fopen(path, "rb");

  // if file is null, handle the error
  if (!file) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(1);
  }

  // get size of file
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  // allocate memory for the file
  buffer = (char *)malloc(fileSize + 1);
  if (!buffer) {
    fprintf(stderr, "failed to allocate memory for file\n");
    fclose(file);
    exit(1);
  }
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

  // null termination
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

// read file into memory and interpret
static void runFile(const char *path) {
  char *source = readFile(path);
  parseString(source);
  free(source);
}

int main(int argc, const char *argv[]) {
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
