#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include "codegen.h"
#include "tac.h"
#include "symtab.h"

/* External declarations from Bison/Flex */
extern FILE* yyin;
extern int yyparse();
extern ASTNode* root;

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source.c> <output.s>\n", argv[0]);
        return 1;
    }

    const char* srcFile = argv[1];
    const char* outFile = argv[2];

    /* Open source file */
    yyin = fopen(srcFile, "r");
    if (!yyin) {
        perror(srcFile);
        return 1;
    }

    /* Parse input and build AST */
    printf("Parsing %s...\n", srcFile);
    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed due to syntax errors.\n");
        fclose(yyin);
        return 1;
    }
    fclose(yyin);

    /* Print AST for debugging */
    //printf("\n=== Abstract Syntax Tree ===\n");
    //printAST(root, 0);

    /* Optional: Generate Three-Address Code (TAC) */
    printf("\nGenerating TAC...\n");
    generateTAC(root, "tac.txt");  // implement in tac.c/h

    /* Generate MIPS assembly */
    printf("Generating MIPS assembly: %s\n", outFile);
    generateMIPS(root, outFile);

    printf("Compilation finished successfully.\n");
    return 0;
}
