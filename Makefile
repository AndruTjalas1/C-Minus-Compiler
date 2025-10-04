# Compiler and tools
CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g -Wall

# Windows-specific settings
ifeq ($(OS),Windows_NT)
    # For Windows with MinGW/Cygwin
    LDFLAGS = -lpsapi
    RM = del /Q
else
    # Unix-like systems
    LDFLAGS =
    RM = rm -f
endif

# Target executable
TARGET = Compiler
OBJS = lex.yy.o parser.tab.o main.o AST.o symtab.o codegen.o tac.o benchmark.o stringpool.o error.o

# Default rule
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Generate lexer code
lex.yy.c: lexer.l parser.tab.h
	$(LEX) lexer.l

# Generate parser code
parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

# Compile object files
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

main.o: main.c AST.h codegen.h tac.h symtab.h benchmark.h stringpool.h
	$(CC) $(CFLAGS) -c main.c

AST.o: AST.c AST.h stringpool.h
	$(CC) $(CFLAGS) -c AST.c

symtab.o: symtab.c symtab.h stringpool.h
	$(CC) $(CFLAGS) -c symtab.c

codegen.o: codegen.c codegen.h AST.h symtab.h
	$(CC) $(CFLAGS) -c codegen.c

tac.o: tac.c tac.h AST.h
	$(CC) $(CFLAGS) -c tac.c

benchmark.o: benchmark.c benchmark.h
	$(CC) $(CFLAGS) -c benchmark.c

stringpool.o: stringpool.c stringpool.h
	$(CC) $(CFLAGS) -c stringpool.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	$(RM) $(TARGET).exe $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.s tac.txt tac_unoptimized.txt 2>nul || true
else
	$(RM) $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.s tac.txt tac_unoptimized.txt test_large.c test_medium.c test_small.c test_xlarge.C
endif

# Test rule: compile and run a test source file
test: $(TARGET)
	./$(TARGET) test.c test.s
	@echo "\n=== Generated MIPS Code ==="
	@cat test.s

.PHONY: all clean test
