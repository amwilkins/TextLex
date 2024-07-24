CC ?= gcc
BIN := tokenize

all:
	$(CC) -o $(BIN) $(wildcard src/*.c)

run: all
	./$(BIN)

clean:
	rm $(BIN) | true
