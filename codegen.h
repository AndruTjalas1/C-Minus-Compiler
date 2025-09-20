#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"

/* Generate MIPS assembly code from AST and write to output file */
void generateMIPS(ASTNode* root, const char* filename);

#endif
