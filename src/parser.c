#include <stdio.h>

#include "common.h"
#include "parser.h"
#include "tokenizer.h"

static bool string() { return true; }

Token processToken(rawToken rawToken) {
  Token token;
  char c = rawToken.start[0];
  char next_c = rawToken.start[1];
  tokenType type;
  type = TOKEN_UNKNOWN;

  switch (c) {
  case '(':
    type = TOKEN_LEFT_PAREN;
    break;
  case ')':
    type = TOKEN_RIGHT_PAREN;
    break;
  case '{':
    type = TOKEN_LEFT_BRACE;
    break;
  case '}':
    type = TOKEN_RIGHT_BRACE;
    break;
  case ';':
    type = TOKEN_SEMICOLON;
    break;
  case ',':
    type = TOKEN_COMMA;
    break;
  case '.':
    type = TOKEN_DOT;
    break;
  case '-':
    type = TOKEN_MINUS;
    break;
  case '+':
    type = TOKEN_PLUS;
    break;
  case '/':
    type = TOKEN_SLASH;
    break;
  case '*':
    type = TOKEN_STAR;
    break;
  case '!':
    if (next_c == '=') {
      type = TOKEN_BANG_EQUAL;
      rawToken.length++;
      getToken();
      break;
    } else {
      type = TOKEN_BANG;
      break;
    }
  case '=':
    if (next_c == '=') {
      type = TOKEN_EQUAL_EQUAL;
      rawToken.length++;
      getToken();
      break;
    } else {
      type = TOKEN_EQUAL;
      break;
    }
  case '<':
    if (next_c == '=') {
      type = TOKEN_LESS_EQUAL;
      rawToken.length++;
      getToken();
      break;
    } else {
      type = TOKEN_LESS;
      break;
    }
  case '>':
    if (next_c == '=') {
      type = TOKEN_GREATER_EQUAL;
      rawToken.length++;
      getToken();
      break;
    } else {
      type = TOKEN_GREATER;
      break;
    }
  case '"':
    type = TOKEN_STRING;
    break;
  default:
    type = TOKEN_UNKNOWN;
  }

  token.type = type;
  token.start = rawToken.start;
  token.length = rawToken.length;
  return token;
}

// advance to the next token
static void advance() {
  FILE *out;
  remove("output.txt");
  out = fopen("output.txt", "a");
  rawToken prev_token;

  printf("Token type and value\n");
  for (;;) {
    rawToken rawToken = getToken();
    if (rawToken.isAtEnd)
      break;

    Token token = processToken(rawToken);

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
