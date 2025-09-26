# Compiler and tools
CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g -Wall

# Target executable
TARGET = Compiler
OBJS = lex.yy.o parser.tab.o main.o ast.o symtab.o codegen.o tac.o

# Default rule
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

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

main.o: main.c ast.h codegen.h tac.h symtab.h
	$(CC) $(CFLAGS) -c main.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

codegen.o: codegen.c codegen.h ast.h symtab.h
	$(CC) $(CFLAGS) -c codegen.c

tac.o: tac.c tac.h ast.h
	$(CC) $(CFLAGS) -c tac.c

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.s

# Test rule: compile and run a test source file
test: $(TARGET)
	./$(TARGET) test.c test.s
	@echo "\n=== Generated MIPS Code ==="
	@cat test.s

.PHONY: all clean test
