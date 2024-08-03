#include "input.h"
#include "parser.h"
#include "tokenizer.h"

// read execute print loop
void repl() {
  // limited line size
  char line[1024];

  // forever
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    parse(line);
  }
}

// read the file from a path
char *readFile(const char *path) {
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
void runFile(const char *path) {
  char *source = readFile(path);
  parse(source);
  free(source);
}
