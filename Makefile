CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: tests

tests: tests/arrays/array_test

tests/arrays/array_test: tests/arrays/array_test.o src/arrays/array.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/arrays/*.o tests/arrays/*.o tests/arrays/array_test
