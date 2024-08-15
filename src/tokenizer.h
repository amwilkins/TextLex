#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
  const char *start;
  int length;
  bool isAtEnd;
} rawToken;

void initScanner(const char *source);
rawToken getToken();
bool isAtEnd();

#endif
