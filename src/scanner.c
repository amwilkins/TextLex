#include <stdbool.h>

#include "scanner.h"

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
bool isAtEnd() { return *scanner.current == '\0'; }

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

// check if next character creates an expected token
static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*scanner.current != expected)
    return false;
  scanner.current++;
  return true;
}

// make a token struct
rawToken makeRawToken() {
  rawToken token;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.isAtEnd = false;
  return token;
}

// is the scanner at a number
bool isDigit(char c) { return c >= '0' && c <= '9'; }

// is the scanner at a letter
static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
         c == '-';
}

// words can have numbers, as long as they start with a letter
// Could make it so numbers could start as well, but for now it's fine
static rawToken word() {
  while (isAlpha(peek()) || isDigit(peek()))
    advance();
  return makeRawToken();
}

// return a full number
static rawToken number() {
  while (isDigit(peek()))
    advance();
  // find decimal point
  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();
  }
  return makeRawToken();
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
    case '/':
      if (peekNext() == '/') {
        // A comment goes until the end of the line.
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static rawToken end() {
  rawToken token;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.isAtEnd = true;
  return token;
}

static rawToken newline() {
  rawToken token;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.isAtEnd = false;
  return makeRawToken();
}

// scan for a string
static rawToken string() {
  while (peek() != '"' && !isAtEnd()) {
    advance();
  }

  if (isAtEnd())
    return end();

  // The closing quote.
  advance();
  return makeRawToken();
}

// scan a token
rawToken getToken() {
  if (!*scanner.current)
    return end();

  if (isAtEnd())
    return end();

  skipWhitespace();

  scanner.start = scanner.current;
  char c = advance();
  if (c == '"')
    return string();

  if (c == '\n')
    return newline();

  // return word
  if (isAlpha(c))
    return word();

  // return single digits
  if (isDigit(c)) {
    return number();
  }

  return makeRawToken();
}
