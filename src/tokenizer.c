#include <stdbool.h>
#include <stdio.h>

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

static void initScanner(const char *source) {
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
void parseString(const char *source) {

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
