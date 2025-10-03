#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include "codegen.h"
#include "tac.h"
#include "symtab.h"
#include "benchmark.h"
#include "stringpool.h"

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

    /* Initialize optimization systems */
    printf("Initializing compiler with optimizations...\n");
    BenchmarkResult* total_bench = start_benchmark();
    
    init_string_pool();
    init_ast_memory();
    initSymTab();

    /* Open source file */
    yyin = fopen(srcFile, "r");
    if (!yyin) {
        perror(srcFile);
        return 1;
    }

    /* Parse input and build AST */
    printf("\nParsing %s...\n", srcFile);
    BenchmarkResult* parse_bench = start_benchmark();
    
    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed due to syntax errors.\n");
        fclose(yyin);
        return 1;
    }
    fclose(yyin);
    
    end_benchmark(parse_bench, "Parsing");
    free(parse_bench);

    /* Optional: Generate Three-Address Code (TAC) */
    printf("\nGenerating TAC...\n");
    BenchmarkResult* tac_bench = start_benchmark();
    
    generateTAC(root, "tac.txt");
    
    end_benchmark(tac_bench, "TAC Generation & Optimization");
    free(tac_bench);

    /* Generate MIPS assembly */
    printf("\nGenerating MIPS assembly: %s\n", outFile);
    BenchmarkResult* codegen_bench = start_benchmark();
    
    generateMIPS(root, outFile);
    
    end_benchmark(codegen_bench, "Code Generation");
    free(codegen_bench);

    /* Print optimization statistics */
    print_ast_memory_stats();
    print_string_stats();
    print_symtab_stats();

    /* Total time */
    end_benchmark(total_bench, "Total Compilation");
    free(total_bench);

    /* Cleanup */
    free_ast_memory();
    free_string_pool();

    printf("\n✓ Compilation finished successfully.\n");
    return 0;
}
