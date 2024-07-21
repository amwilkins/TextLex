/*
 * 2024-07-21
 * This is a basic tokenizer to play around with.
 * It takes either a text file or repl input
 * Returns newline separated tokens.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// token struct
typedef struct {
  const char *start;
  int length;
} Token;

// create a scanner struct
typedef struct {
  const char *start;
  const char *current;
} Scanner;

Scanner scanner;

void initScanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
}

// check for end of file
static bool isAtEnd() { return *scanner.current == '\0'; }

// return NEXT character
static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

// return current scanner
static char peek() { return *scanner.current; }

// move head scanner forward
static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

// make a token struct
static Token makeToken() {
  Token token;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  return token;
}

// is the scanner at a number
bool isDigit(char c) { return c >= '0' && c <= '9'; }

// is the scanner at a letter
static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// return a full word
static Token word() {
  while (isAlpha(peek()))
    advance();
  return makeToken();
}

static Token number() {
  while (isDigit(peek()))
    advance();
  // find decimal point
  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();
  }
  return makeToken();
}

// skip whitespace
static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    default:
      return;
    }
  }
}

// scan a token
Token scanToken() {
  skipWhitespace();
  scanner.start = scanner.current;
  char c = advance();

  if (isAtEnd())
    return makeToken();

  // return word
  if (isAlpha(c))
    return word();

  // return single digits
  if (isDigit(c)) {
    return number();
  }

  // single non-alphanumeric character
  return makeToken();
}

// interpret an array of characters
static void interpret(const char *source) {

  // destructively write an output file
  FILE *out;
  remove("output.txt");
  out = fopen("output.txt", "a");

  initScanner(source);
  for (;;) {
    if (*scanner.current == '\0')
      break;

    Token token = scanToken();

    printf("%.*s\n", token.length, token.start);

    // append to output file
    fprintf(out, "%.*s\n", token.length, token.start);
  }
}

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
    interpret(line);
  }
}

// read the file from a path
static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");

  // if file is null, handle the error
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  // get size of file
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  // allocate memory for the file
  char *buffer = (char *)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

// read file into memory and interpret
static void runFile(const char *path) {
  char *source = readFile(path);
  interpret(source);
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
