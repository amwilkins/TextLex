#include <stdio.h>

#include "common.h"
#include "parser.h"
#include "tokenizer.h"

static bool string() { return true; }

bool isInt(char c) { return c >= '0' && c <= '9'; }

Token makeToken(rawToken rawToken, tokenType type) {
  Token token;
  token.start = rawToken.start;
  token.length = rawToken.length;
  token.type = type;
  return token;
}

Token processToken(rawToken rawToken) {
  Token token;
  char c = rawToken.start[0];
  char next_c = rawToken.start[1];
  tokenType type;
  type = TOKEN_UNKNOWN;

  if (isInt(c)) {
    return makeToken(rawToken, TOKEN_NUMBER);
  }

  switch (c) {
  case '\n':
    return makeToken(rawToken, TOKEN_NEWLINE);
  case '(':
    return makeToken(rawToken, TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(rawToken, TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(rawToken, TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(rawToken, TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(rawToken, TOKEN_SEMICOLON);
  case ',':
    return makeToken(rawToken, TOKEN_COMMA);
  case '.':
    return makeToken(rawToken, TOKEN_DOT);
  case '-':
    return makeToken(rawToken, TOKEN_MINUS);
  case '+':
    return makeToken(rawToken, TOKEN_PLUS);
  case '/':
    return makeToken(rawToken, TOKEN_SLASH);
  case '*':
    return makeToken(rawToken, TOKEN_STAR);
  case '!':
    if (next_c == '=') {
      rawToken.length++;
      getToken();
      return makeToken(rawToken, TOKEN_BANG_EQUAL);
    } else {
      return makeToken(rawToken, TOKEN_BANG);
    }
  case '=':
    if (next_c == '=') {
      rawToken.length++;
      getToken();
      return makeToken(rawToken, TOKEN_EQUAL_EQUAL);

    } else {
      return makeToken(rawToken, TOKEN_EQUAL);
    }
  case '<':
    if (next_c == '=') {
      rawToken.length++;
      getToken();
      return makeToken(rawToken, TOKEN_LESS_EQUAL);

    } else {
      return makeToken(rawToken, TOKEN_LESS);
    }
  case '>':
    if (next_c == '=') {
      rawToken.length++;
      getToken();
      return makeToken(rawToken, TOKEN_GREATER_EQUAL);

    } else {
      return makeToken(rawToken, TOKEN_GREATER);
    }
  case '"':
    return makeToken(rawToken, TOKEN_STRING);

  default:
    return makeToken(rawToken, TOKEN_UNKNOWN);
  }
}

// advance to the next token
static void advance() {
  FILE *out;
  remove("output.txt");
  out = fopen("output.txt", "a");
  rawToken prev_token;
  Token token;

  printf("Token type and value\n");
  for (;;) {
    rawToken rawToken = getToken();
    if (rawToken.isAtEnd)
      break;

    token = processToken(rawToken);

    // just for testing
    printf("Token: %2d, %.*s\n", token.type, token.length, token.start);

    // append to output file
    fprintf(out, "%d %.*s\n", token.type, token.length, token.start);
  }
}

// interpret an array of characters
void parse(const char *source) {

  initScanner(source);
  advance();
}
