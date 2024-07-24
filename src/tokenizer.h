#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
  const char *start;
  int length;
} Token;

typedef struct {
  const char *start;
  const char *current;
} Scanner;

void parseString(const char *source);

#endif
