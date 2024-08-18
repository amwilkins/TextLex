#include <stdio.h>

#include "dArray.h"
#include "parser.h"
#include "scanner.h"

// init parser to keep our place
Parser parser;

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

  if (rawToken.isAtEnd) {
    return makeToken(rawToken, TOKEN_EOF);
  }

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
  rawToken prev_token;
  Token token;

  parser.previous = parser.current;
  for (;;) {
    rawToken rawToken = getToken();

    parser.current = processToken(rawToken);
    token = parser.current;

    if (token.type == TOKEN_EOF)
      break;
    /// if (token.type == TOKEN_NEWLINE)
    ///   break;

    // just for testing
    printf("Token: %2d, %.*s\n", token.type, token.length, token.start);
  }
}

// interpret an array of characters
bool parse(char *source, DArray *token_bag) {
  initScanner(source);
  advance();
  return 1;
}
