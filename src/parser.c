#include "parser.h"
#include "dArray.h"
#include "scanner.h"

// init parser to keep our place
Parser parser;
VM *vm;

static bool string() { return true; }

bool isInt(char c) { return c >= '0' && c <= '9'; }

static void emitByte(DArray *token_bag, uint8_t byte) {
  writeDArray(token_bag, &byte);
}

static void emitBytes(DArray *array, uint8_t byte1, uint8_t byte2) {
  writeDArray(array, &byte1);
  writeDArray(array, &byte2);
}

static void emitNumber(DArray *constants, Token token) {
  double value = strtod(token.start, NULL);
  writeDArray(constants, &value);
}

static void unary() {
  tokenType operatorType = parser.previous.type;
  switch (operatorType) {
  case TOKEN_MINUS:
    emitByte(vm->token_bag, OP_NEGATE);
    break;
  default:
    return;
  }
}

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
static void advance(VM *vm) {
  rawToken prev_token;
  Token token;

  parser.previous = parser.current;
  for (;;) {
    rawToken rawToken = getToken();

    parser.current = processToken(rawToken);
    token = parser.current;

    emitByte(vm->token_bag, token.type);

    if (token.type == TOKEN_NUMBER)
      emitNumber(vm->constants, token);

    if (token.type == TOKEN_EOF)
      break;
  }
}

// interpret an array of characters
bool parse(char *source, VM *vm) {
  vm = vm;

  initScanner(source);
  advance(vm);

  emitByte(vm->token_bag, TOKEN_RETURN);

  return 1;
}
