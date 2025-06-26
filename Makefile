#c compiler
CC=gcc
CFLAGS= -Wall -Wextra -std=c23 -g -Iinc

#dirs
SRCDIR=src
EXAMPLEDIR=examples
LEETCODEDIR=leetcode
TESTDIR=tests
BINDIR=bin
OBJDIR=obj

$(shell mkdir -p $(BINDIR) $(OBJDIR))

UTILS_SRC=$(SRCDIR)/common.c

UTILS_OBJ=$(SRCDIR)/common.o

all: tests examples leetcode

debug: CFLAGS += -DDEBUG -O0
debug: all

release: CFLAGS += -O2 -DNDEBUG
release: all

clean:
	@echo "Cleaning up..."
	rm -rf $(BINDIR)/* $(OBJDIR)/*

rebuild: clean all

help:
	@echo "C DSA Project Makefile"
	@echo "======================"
	@echo ""
	@echo "Main targets:"
	@echo "  all        - Build tests, examples, and leetcode problems"
	@echo "  tests      - Build all test executables"
	@echo "  examples   - Build all demo programs"
	@echo "  problems   - Build practice problems"
	@echo ""
	@echo "Test targets:"
	@echo "  test           - Run all tests"
	@echo ""
	@echo "Demo targets:"
	@echo "  demo           - Run all demos"
	@echo ""
	@echo "Build variants:"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build optimized version"
	@echo ""
	@echo "Utility:"
	@echo "  clean      - Remove all generated files"
	@echo "  rebuild    - Clean and build everything"
	@echo "  help       - Show this help message"

.PHONY: all tests examples problems test demo clean rebuild help debug release
