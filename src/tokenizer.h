#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
  const char *start;
  int length;
  bool isAtEnd;
} rawToken;

void parse(const char *source);
void initScanner(const char *source);
rawToken getToken();

#endif
