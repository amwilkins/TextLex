all: tokenizer

make: tokenizer
	gcc -o tokenizer tokenizer.c

clean:
	rm tokenizer
