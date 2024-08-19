#ifndef PARSER_H
#define PARSER_H

#include "dArray.h"
#include "vm.h"

// types of tokens allowed
typedef enum {
  // Single-character tokens.
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_MINUS,
  TOKEN_PLUS,
  TOKEN_SEMICOLON,
  TOKEN_SLASH,
  TOKEN_STAR,
  TOKEN_BANG,
  TOKEN_BANG_EQUAL, // One or two character tokens.
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,
  TOKEN_IDENTIFIER, // Literals.
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_AND, // Keywords.
  TOKEN_CLASS,
  TOKEN_ELSE,
  TOKEN_FALSE,
  TOKEN_FOR,
  TOKEN_FUN,
  TOKEN_IF,
  TOKEN_NIL,
  TOKEN_OR,
  TOKEN_PRINT,
  TOKEN_RETURN,
  TOKEN_SUPER,
  TOKEN_THIS,
  TOKEN_TRUE,
  TOKEN_VAR,
  TOKEN_WHILE,
  TOKEN_NEWLINE,
  TOKEN_ERROR,
  TOKEN_EOF,
  TOKEN_UNKNOWN
} tokenType;

typedef struct {
  const char *start;
  int length;
  tokenType type;
} Token;

typedef struct {
  Token current;
  Token previous;
} Parser;

bool parse(char *source, VM *vm);

#endif
