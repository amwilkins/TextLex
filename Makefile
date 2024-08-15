CC ?= gcc
BIN := tokenize

all:
	$(CC) -g -o $(BIN) $(wildcard src/*.c)

run: all
	./$(BIN)

clean:
	rm $(BIN) | true
