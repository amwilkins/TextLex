#include <stdio.h>

#include "common.h"
#include "parser.h"
#include "tokenizer.h"

tokenType getTokenType(rawToken token) {}

Token makeToken(rawToken rawToken) {
  Token token;
  token.start = rawToken.start;
  token.length = rawToken.length;
  token.type = getTokenType(rawToken);
  return token;
}

// interpret an array of characters
void parse(const char *source) {
  printf("Token length, mem position, and value\n");

  // destructively write an output file
  FILE *out;
  remove("output.txt");
  out = fopen("output.txt", "a");

  initScanner(source);
  for (;;) {
    rawToken rawToken = getToken();
    if (rawToken.isAtEnd)
      break;

    Token token = makeToken(rawToken);

    printf("Token: %2d, %.*s\n", rawToken.length, token.length, token.start);

    // append to output file
    fprintf(out, "%.*s\n", token.length, token.start);
  }
}
