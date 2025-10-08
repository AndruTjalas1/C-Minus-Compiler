#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "symtab.h"

/* Forward declarations */
void genExprMips(ASTNode* node, FILE* out);
void genStmtMips(ASTNode* node, FILE* out);
Symbol* lookupSymbol(const char* name);
void genConditionMips(ASTNode* condition, FILE* out, const char* jumpLabel);
void collectStringLiterals(ASTNode* node, FILE* out);

/* String literal counter for generating unique labels */
static int stringLiteralCounter = 0;
static int currentStringLiteralIndex = 0;

/* Current function name for return statements */
static const char* currentFunctionName = NULL;

/* Lookup helper */
Symbol* lookupSymbol(const char* name) {
    return getSymbol(name);
}

/* Collect and generate string literals */
void collectStringLiterals(ASTNode* node, FILE* out) {
    if (!node) return;
    
    if (strcmp(node->type, "string_literal") == 0) {
        fprintf(out, "str_lit_%d: .asciiz \"%s\"\n", stringLiteralCounter, node->name);
        stringLiteralCounter++;
    }
    
    // Recursively traverse the AST
    if (node->left) collectStringLiterals(node->left, out);
    if (node->right) collectStringLiterals(node->right, out);
    if (node->next) collectStringLiterals(node->next, out);
    if (node->condition) collectStringLiterals(node->condition, out);
    if (node->ifBlock) collectStringLiterals(node->ifBlock, out);
    if (node->elseifList) collectStringLiterals(node->elseifList, out);
    if (node->elseBlock) collectStringLiterals(node->elseBlock, out);
    if (node->loopInit) collectStringLiterals(node->loopInit, out);
    if (node->loopUpdate) collectStringLiterals(node->loopUpdate, out);
    if (node->loopBody) collectStringLiterals(node->loopBody, out);
}

/* Helper to find string literal index */
int getStringLiteralIndex(ASTNode* root, ASTNode* target) {
    static int searchIndex;
    if (root == NULL) return -1;
    
    // Reset search on new traversal
    if (root->type && strcmp(root->type, "string_literal") == 0) {
        if (root == target) {
            return searchIndex++;
        }
        searchIndex++;
    }
    
    int result = -1;
    if (root->left && (result = getStringLiteralIndex(root->left, target)) >= 0) return result;
    if (root->right && (result = getStringLiteralIndex(root->right, target)) >= 0) return result;
    if (root->next && (result = getStringLiteralIndex(root->next, target)) >= 0) return result;
    if (root->condition && (result = getStringLiteralIndex(root->condition, target)) >= 0) return result;
    if (root->ifBlock && (result = getStringLiteralIndex(root->ifBlock, target)) >= 0) return result;
    if (root->elseifList && (result = getStringLiteralIndex(root->elseifList, target)) >= 0) return result;
    if (root->elseBlock && (result = getStringLiteralIndex(root->elseBlock, target)) >= 0) return result;
    if (root->loopInit && (result = getStringLiteralIndex(root->loopInit, target)) >= 0) return result;
    if (root->loopUpdate && (result = getStringLiteralIndex(root->loopUpdate, target)) >= 0) return result;
    if (root->loopBody && (result = getStringLiteralIndex(root->loopBody, target)) >= 0) return result;
    
    return -1;
}

/* Generate MIPS for expressions */
void genExprMips(ASTNode* node, FILE* out) {
    if (!node) return;

    if (strcmp(node->type, "num") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);
    }
    else if (strcmp(node->type, "char") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);
    }
    else if (strcmp(node->type, "bool") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);  // 0 for false, 1 for true
    }
    else if (strcmp(node->type, "string_literal") == 0) {
        fprintf(out, "    la $t0, str_lit_%d\n", currentStringLiteralIndex++);
    } 
    else if (strcmp(node->type, "var") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared variable '%s'\n", node->name);
            return;
        }
        // Check if it's a string variable
        if (sym->stringValue) {
            fprintf(out, "    la $t0, var_%s\n", sym->name);  // load string address
        }
        else if (sym->type == 'c') {
            fprintf(out, "    lb $t0, var_%s\n", sym->name);
        }
        else {
            fprintf(out, "    lw $t0, var_%s\n", sym->name);
        }
    }
    else if (strcmp(node->type, "array_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        genExprMips(node->left, out);
        
        if (sym->type == 'c') {
            fprintf(out, "    la $t1, var_%s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lb $t0, 0($t1)\n");
        } else {
            fprintf(out, "    sll $t0, $t0, 2\n");
            fprintf(out, "    la $t1, var_%s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lw $t0, 0($t1)\n");
        }
    }
    else if (strcmp(node->type, "array2d_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        genExprMips(node->left, out);
        fprintf(out, "    move $t2, $t0\n");
        fprintf(out, "    li $t3, %d\n", sym->dim2);
        fprintf(out, "    mul $t2, $t2, $t3\n");
        
        genExprMips(node->right, out);
        fprintf(out, "    add $t0, $t2, $t0\n");
        
        if (sym->type == 'c') {
            fprintf(out, "    la $t1, var_%s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lb $t0, 0($t1)\n");
        } else {
            fprintf(out, "    sll $t0, $t0, 2\n");
            fprintf(out, "    la $t1, var_%s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lw $t0, 0($t1)\n");
        }
    }
    else if (strcmp(node->type, "function_call") == 0) {
        // Save $ra and any needed registers
        fprintf(out, "    # Function call: %s\n", node->name);
        fprintf(out, "    addi $sp, $sp, -4\n");
        fprintf(out, "    sw $ra, 0($sp)\n");
        
        // Push arguments onto stack (in reverse order for correct ordering)
        int argCount = 0;
        ASTNode* arg = node->args;
        while (arg) {
            argCount++;
            arg = arg->next;
        }
        
        // Allocate space for arguments
        if (argCount > 0) {
            fprintf(out, "    addi $sp, $sp, -%d\n", argCount * 4);
        }
        
        // Evaluate and store arguments
        arg = node->args;
        int offset = 0;
        while (arg) {
            genExprMips(arg, out);
            fprintf(out, "    sw $t0, %d($sp)\n", offset);
            offset += 4;
            arg = arg->next;
        }
        
        // Call the function
        fprintf(out, "    jal func_%s\n", node->name);
        
        // Clean up arguments from stack
        if (argCount > 0) {
            fprintf(out, "    addi $sp, $sp, %d\n", argCount * 4);
        }
        
        // Restore $ra
        fprintf(out, "    lw $ra, 0($sp)\n");
        fprintf(out, "    addi $sp, $sp, 4\n");
        
        // Result is in $v0, move to $t0
        fprintf(out, "    move $t0, $v0\n");
    }
    else if (strcmp(node->type, "binop") == 0) {
        fprintf(out, "    sw $s0, -4($sp)\n");
        fprintf(out, "    addiu $sp, $sp, -4\n");

        genExprMips(node->left, out);
        fprintf(out, "    move $s0, $t0\n");
        genExprMips(node->right, out);
        switch (node->op) {
            case '+': fprintf(out, "    add $t0, $s0, $t0\n"); break;
            case '-': fprintf(out, "    sub $t0, $s0, $t0\n"); break;
            case '*': fprintf(out, "    mul $t0, $s0, $t0\n"); break;
            case '/': fprintf(out, "    div $s0, $t0\n    mflo $t0\n"); break;
            case '%': fprintf(out, "    div $s0, $t0\n    mfhi $t0\n"); break;
        }

        fprintf(out, "    addiu $sp, $sp, 4\n");
        fprintf(out, "    lw $s0, -4($sp)\n");
    }
}

/* Generate MIPS for conditions with logical operators */
void genConditionMips(ASTNode* condition, FILE* out, const char* jumpLabel) {
    if (!condition) return;
    
    char* condOp = condition->name;
    
    // Handle logical NOT
    if (strcmp(condOp, "!") == 0) {
        static int notCounter = 0;
        char trueLabel[32];
        sprintf(trueLabel, "not_true_%d", notCounter++);
        
        genConditionMips(condition->left, out, trueLabel);
        fprintf(out, "    j %s\n", jumpLabel);
        fprintf(out, "%s:\n", trueLabel);
        return;
    }
    
    // Handle logical AND
    if (strcmp(condOp, "&&") == 0) {
        genConditionMips(condition->left, out, jumpLabel);
        genConditionMips(condition->right, out, jumpLabel);
        return;
    }
    
    // Handle logical OR
    if (strcmp(condOp, "||") == 0) {
        static int orCounter = 0;
        char trueLabel[32];
        sprintf(trueLabel, "or_true_%d", orCounter++);
        
        genConditionMips(condition->left, out, trueLabel);
        genConditionMips(condition->right, out, jumpLabel);
        fprintf(out, "%s:\n", trueLabel);
        return;
    }
    
    // Handle logical XOR
    if (strcmp(condOp, "^") == 0) {
        // Evaluate left condition
        genExprMips(condition->left->left, out);
        fprintf(out, "    move $t8, $t0\n");
        genExprMips(condition->left->right, out);
        fprintf(out, "    move $t9, $t0\n");
        
        char* leftOp = condition->left->name;
        fprintf(out, "    # Evaluate left XOR condition\n");
        if (strcmp(leftOp, "==") == 0) {
            fprintf(out, "    seq $t6, $t8, $t9\n");
        } else if (strcmp(leftOp, "!=") == 0) {
            fprintf(out, "    sne $t6, $t8, $t9\n");
        } else if (strcmp(leftOp, "<") == 0) {
            fprintf(out, "    slt $t6, $t8, $t9\n");
        } else if (strcmp(leftOp, "<=") == 0) {
            fprintf(out, "    slt $t7, $t9, $t8\n");
            fprintf(out, "    xori $t6, $t7, 1\n");
        } else if (strcmp(leftOp, ">") == 0) {
            fprintf(out, "    slt $t6, $t9, $t8\n");
        } else if (strcmp(leftOp, ">=") == 0) {
            fprintf(out, "    slt $t7, $t8, $t9\n");
            fprintf(out, "    xori $t6, $t7, 1\n");
        }
        
        // Evaluate right condition
        genExprMips(condition->right->left, out);
        fprintf(out, "    move $t8, $t0\n");
        genExprMips(condition->right->right, out);
        fprintf(out, "    move $t9, $t0\n");
        
        char* rightOp = condition->right->name;
        fprintf(out, "    # Evaluate right XOR condition\n");
        if (strcmp(rightOp, "==") == 0) {
            fprintf(out, "    seq $t7, $t8, $t9\n");
        } else if (strcmp(rightOp, "!=") == 0) {
            fprintf(out, "    sne $t7, $t8, $t9\n");
        } else if (strcmp(rightOp, "<") == 0) {
            fprintf(out, "    slt $t7, $t8, $t9\n");
        } else if (strcmp(rightOp, "<=") == 0) {
            fprintf(out, "    slt $t5, $t9, $t8\n");
            fprintf(out, "    xori $t7, $t5, 1\n");
        } else if (strcmp(rightOp, ">") == 0) {
            fprintf(out, "    slt $t7, $t9, $t8\n");
        } else if (strcmp(rightOp, ">=") == 0) {
            fprintf(out, "    slt $t5, $t8, $t9\n");
            fprintf(out, "    xori $t7, $t5, 1\n");
        }
        
        // XOR the two boolean results
        fprintf(out, "    xor $t6, $t6, $t7\n");
        fprintf(out, "    beq $t6, $zero, %s\n", jumpLabel);
        return;
    }
    
    // Handle basic comparison operators
    genExprMips(condition->left, out);
    fprintf(out, "    move $t8, $t0\n");
    genExprMips(condition->right, out);
    fprintf(out, "    move $t9, $t0\n");
    
    if (strcmp(condOp, "==") == 0) {
        fprintf(out, "    bne $t8, $t9, %s\n", jumpLabel);
    } else if (strcmp(condOp, "!=") == 0) {
        fprintf(out, "    beq $t8, $t9, %s\n", jumpLabel);
    } else if (strcmp(condOp, "<") == 0) {
        fprintf(out, "    slt $t7, $t8, $t9\n");
        fprintf(out, "    beq $t7, $zero, %s\n", jumpLabel);
    } else if (strcmp(condOp, "<=") == 0) {
        fprintf(out, "    slt $t7, $t9, $t8\n");
        fprintf(out, "    bne $t7, $zero, %s\n", jumpLabel);
    } else if (strcmp(condOp, ">") == 0) {
        fprintf(out, "    slt $t7, $t9, $t8\n");
        fprintf(out, "    beq $t7, $zero, %s\n", jumpLabel);
    } else if (strcmp(condOp, ">=") == 0) {
        fprintf(out, "    slt $t7, $t8, $t9\n");
        fprintf(out, "    bne $t7, $zero, %s\n", jumpLabel);
    }
}

/* Generate MIPS for statements */
void genStmtMips(ASTNode* node, FILE* out) {
    ASTNode* p = node;
    while (p) {
        if (strcmp(p->type, "assign") == 0) {
            genExprMips(p->left, out);
            Symbol* sym = lookupSymbol(p->name);
            if (!sym) {
                fprintf(stderr, "Error: undeclared variable '%s'\n", p->name);
                return;
            }
            if (sym->type == 'c')
                fprintf(out, "    sb $t0, var_%s\n", sym->name);
            else
                fprintf(out, "    sw $t0, var_%s\n", sym->name);
        }
        else if (strcmp(p->type, "string_decl") == 0) {
            // Strings initialized in data section
        }
        else if (strcmp(p->type, "array_decl_init") == 0) {
            Symbol* sym = lookupSymbol(p->name);
            if (!sym || !sym->initValues) {
                p = p->next;
                continue;
            }
            
            for (int i = 0; i < sym->initCount && i < sym->dim1; i++) {
                fprintf(out, "    li $t0, %d\n", sym->initValues[i]);
                fprintf(out, "    li $t1, %d\n", i);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t2, var_%s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sb $t0, 0($t2)\n");
                } else {
                    fprintf(out, "    sll $t1, $t1, 2\n");
                    fprintf(out, "    la $t2, var_%s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sw $t0, 0($t2)\n");
                }
            }
        }
        else if (strcmp(p->type, "array2d_decl_init") == 0) {
            Symbol* sym = lookupSymbol(p->name);
            if (!sym || !sym->initValues) {
                p = p->next;
                continue;
            }
            
            // Initialize 2D array elements in row-major order
            for (int i = 0; i < sym->initCount && i < (sym->dim1 * sym->dim2); i++) {
                fprintf(out, "    li $t0, %d\n", sym->initValues[i]);
                fprintf(out, "    li $t1, %d\n", i);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t2, var_%s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sb $t0, 0($t2)\n");
                } else {
                    fprintf(out, "    sll $t1, $t1, 2\n");
                    fprintf(out, "    la $t2, var_%s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sw $t0, 0($t2)\n");
                }
            }
        }
        else if (strcmp(p->type, "array_assign") == 0) {
            genExprMips(p->right, out);
            fprintf(out, "    move $t9, $t0\n");
            
            ASTNode* arrayAccess = p->left;
            Symbol* sym = lookupSymbol(arrayAccess->name);
            if (!sym) {
                fprintf(stderr, "Error: undeclared array '%s'\n", arrayAccess->name);
                return;
            }
            
            if (strcmp(arrayAccess->type, "array_access") == 0) {
                genExprMips(arrayAccess->left, out);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, var_%s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sb $t9, 0($t1)\n");
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");
                    fprintf(out, "    la $t1, var_%s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sw $t9, 0($t1)\n");
                }
            }
            else if (strcmp(arrayAccess->type, "array2d_access") == 0) {
                genExprMips(arrayAccess->left, out);
                fprintf(out, "    move $t2, $t0\n");
                fprintf(out, "    li $t3, %d\n", sym->dim2);
                fprintf(out, "    mul $t2, $t2, $t3\n");
                
                genExprMips(arrayAccess->right, out);
                fprintf(out, "    add $t0, $t2, $t0\n");
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, var_%s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sb $t9, 0($t1)\n");
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");
                    fprintf(out, "    la $t1, var_%s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sw $t9, 0($t1)\n");
                }
            }
        }
        else if (strcmp(p->type, "print") == 0) {
            // Check if printing a string literal
            if (p->left && strcmp(p->left->type, "string_literal") == 0) {
                genExprMips(p->left, out);
                fprintf(out, "    move $a0, $t0\n");
                fprintf(out, "    li $v0, 4\n    syscall\n");
                fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
                p = p->next;
                continue;
            }
            // Check if printing a string variable
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->stringValue) {
                    fprintf(out, "    la $a0, var_%s\n", sym->name);
                    fprintf(out, "    li $v0, 4\n    syscall\n");
                    fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
                    p = p->next;
                    continue;
                }
            }
            
            genExprMips(p->left, out);
            
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
                }
            }
            else if (p->left && strcmp(p->left->type, "char") == 0) {
                fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
            }
            else if (p->left && (strcmp(p->left->type, "array_access") == 0 || strcmp(p->left->type, "array2d_access") == 0)) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
                }
            }
            else {
                fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
            }
            
            fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
        }
        else if (strcmp(p->type, "if") == 0) {
            // Generate unique labels
            static int labelCounter = 0;
            char elseLabel[32], endLabel[32];
            sprintf(elseLabel, "else_%d", labelCounter);
            sprintf(endLabel, "endif_%d", labelCounter);
            labelCounter++;
            
            // Use new condition generation function
            genConditionMips(p->condition, out, (p->elseifList || p->elseBlock) ? elseLabel : endLabel);
            
            // Generate if block
            genStmtMips(p->ifBlock, out);
            fprintf(out, "    j %s\n", endLabel);
            
            // Handle elseif chain
            if (p->elseifList) {
                fprintf(out, "%s:\n", elseLabel);
                ASTNode* elseif = p->elseifList;
                int elseifCounter = 0;
                
                while (elseif) {
                    char nextLabel[32];
                    if (elseif->next || p->elseBlock) {
                        sprintf(nextLabel, "elseif_%d_%d", labelCounter-1, elseifCounter++);
                    } else {
                        strcpy(nextLabel, endLabel);
                    }
                    
                    // Evaluate elseif condition using new function
                    genConditionMips(elseif->condition, out, nextLabel);
                    
                    // Generate elseif block
                    genStmtMips(elseif->ifBlock, out);
                    fprintf(out, "    j %s\n", endLabel);
                    
                    if (elseif->next || p->elseBlock) {
                        fprintf(out, "%s:\n", nextLabel);
                    }
                    
                    elseif = elseif->next;
                }
            }
            
            // Handle else block
            if (p->elseBlock) {
                if (!p->elseifList) {
                    fprintf(out, "%s:\n", elseLabel);
                }
                genStmtMips(p->elseBlock, out);
            }
            
            // End label
            fprintf(out, "%s:\n", endLabel);
        }
        else if (strcmp(p->type, "for") == 0) {
            // Generate unique labels for the for loop
            static int forCounter = 0;
            char startLabel[32], condLabel[32], updateLabel[32], endLabel[32];
            sprintf(startLabel, "for_start_%d", forCounter);
            sprintf(condLabel, "for_cond_%d", forCounter);
            sprintf(updateLabel, "for_update_%d", forCounter);
            sprintf(endLabel, "for_end_%d", forCounter);
            forCounter++;
            
            // Generate initialization code
            if (p->loopInit) {
                genStmtMips(p->loopInit, out);
            }
            
            // Condition label and check
            fprintf(out, "%s:\n", condLabel);
            if (p->condition) {
                genConditionMips(p->condition, out, endLabel);
            }
            
            // Loop body
            genStmtMips(p->loopBody, out);
            
            // Update expression
            fprintf(out, "%s:\n", updateLabel);
            if (p->loopUpdate) {
                genStmtMips(p->loopUpdate, out);
            }
            
            // Jump back to condition
            fprintf(out, "    j %s\n", condLabel);
            
            // End label
            fprintf(out, "%s:\n", endLabel);
        }
        else if (strcmp(p->type, "while") == 0) {
            // Generate unique labels for the while loop
            static int whileCounter = 0;
            char condLabel[32], endLabel[32];
            sprintf(condLabel, "while_cond_%d", whileCounter);
            sprintf(endLabel, "while_end_%d", whileCounter);
            whileCounter++;
            
            // Condition label and check
            fprintf(out, "%s:\n", condLabel);
            if (p->condition) {
                genConditionMips(p->condition, out, endLabel);
            }
            
            // Loop body
            genStmtMips(p->loopBody, out);
            
            // Jump back to condition
            fprintf(out, "    j %s\n", condLabel);
            
            // End label
            fprintf(out, "%s:\n", endLabel);
        }
        else if (strcmp(p->type, "do_while") == 0) {
            // Generate unique labels for the do-while loop
            static int doWhileCounter = 0;
            char startLabel[32], condLabel[32];
            sprintf(startLabel, "do_start_%d", doWhileCounter);
            sprintf(condLabel, "do_cond_%d", doWhileCounter);
            doWhileCounter++;
            
            // Start label - body executes at least once
            fprintf(out, "%s:\n", startLabel);
            
            // Loop body
            genStmtMips(p->loopBody, out);
            
            // Condition check - if true, continue loop
            fprintf(out, "%s:\n", condLabel);
            if (p->condition) {
                // For do-while, we want to jump back to start if condition is TRUE
                // So we need to invert the jump logic by creating a temp label
                static int doEndCounter = 0;
                char endLabel[32];
                sprintf(endLabel, "do_end_%d", doEndCounter++);
                
                // Evaluate condition and jump to end if FALSE
                genConditionMips(p->condition, out, endLabel);
                
                // If we get here, condition was true, so loop again
                fprintf(out, "    j %s\n", startLabel);
                
                // End label
                fprintf(out, "%s:\n", endLabel);
            } else {
                // No condition means infinite loop
                fprintf(out, "    j %s\n", startLabel);
            }
        }
        else if (strcmp(p->type, "function_decl") == 0) {
            // Generate function label
            fprintf(out, "\n# Function: %s\n", p->name);
            fprintf(out, "func_%s:\n", p->name);
            
            // Set current function name for return statements
            currentFunctionName = p->name;
            
            // Function prologue - save frame pointer and return address
            fprintf(out, "    # Function prologue\n");
            fprintf(out, "    addi $sp, $sp, -8\n");
            fprintf(out, "    sw $fp, 4($sp)\n");
            fprintf(out, "    sw $ra, 0($sp)\n");
            fprintf(out, "    move $fp, $sp\n");
            
            // Load parameters from stack into local variables
            // Parameters are at $fp + 8 onwards (after saved $ra and $fp)
            int paramOffset = 8;
            ASTNode* param = p->params;
            while (param) {
                fprintf(out, "    lw $t0, %d($fp)\n", paramOffset);
                fprintf(out, "    sw $t0, var_%s\n", param->name);
                paramOffset += 4;
                param = param->next;
            }
            
            // Generate function body
            genStmtMips(p->body, out);
            
            // Function epilogue (in case no explicit return)
            fprintf(out, "    # Function epilogue\n");
            fprintf(out, "func_%s_exit:\n", p->name);
            fprintf(out, "    move $sp, $fp\n");
            fprintf(out, "    lw $ra, 0($sp)\n");
            fprintf(out, "    lw $fp, 4($sp)\n");
            fprintf(out, "    addi $sp, $sp, 8\n");
            fprintf(out, "    jr $ra\n");
            
            // Reset current function name
            currentFunctionName = NULL;
        }
        else if (strcmp(p->type, "function_call") == 0) {
            // Function call as statement (not expression)
            genExprMips(p, out);
        }
        else if (strcmp(p->type, "return") == 0) {
            if (p->left) {
                // Return with value
                genExprMips(p->left, out);
                fprintf(out, "    move $v0, $t0\n");
            }
            // Jump to function exit using current function name
            if (currentFunctionName) {
                fprintf(out, "    j func_%s_exit\n", currentFunctionName);
            }
        }
        p = p->next;
    }
}

/* Entry point */
void generateMIPS(ASTNode* root, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        return;
    }

    // Reset counters for new compilation
    stringLiteralCounter = 0;
    currentStringLiteralIndex = 0;

    fprintf(out, ".data\n");
    
    // Collect and generate string literals
    collectStringLiterals(root, out);

    // Iterate through hash table buckets for string and char declarations
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol* s = symtab.buckets[i];
        while (s) {
            if (s->stringValue) {
                fprintf(out, "var_%s: .asciiz \"%s\"\n", s->name, s->stringValue);
            }
            else if (s->type == 'c') {
                if (s->dimensions == 0) {
                    fprintf(out, "var_%s: .byte %d\n", s->name, s->initial_value);
                } else {
                    fprintf(out, "var_%s: .space %d\n", s->name, s->size);
                }
            }
            s = s->next;
        }
    }
    
    fprintf(out, ".align 2\n");
    
    // Iterate through hash table buckets for int and bool declarations
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol* s = symtab.buckets[i];
        while (s) {
            if (s->type == 'i' || s->type == 'b') {
                if (s->dimensions == 0) {
                    fprintf(out, "var_%s: .word %d\n", s->name, s->initial_value);
                } else {
                    fprintf(out, "var_%s: .space %d\n", s->name, s->size * 4);
                }
            }
            s = s->next;
        }
    }

    fprintf(out, ".text\n.globl main\n");
    
    // First pass: Generate all function definitions
    ASTNode* p = root;
    while (p) {
        if (strcmp(p->type, "function_decl") == 0) {
            // Generate function code (single node, not recursive)
            ASTNode temp = *p;
            temp.next = NULL;
            genStmtMips(&temp, out);
        }
        p = p->next;
    }
    
    // Generate main program code
    fprintf(out, "\nmain:\n");
    p = root;
    while (p) {
        if (strcmp(p->type, "function_decl") != 0) {
            // Create a temporary node list for just this statement
            ASTNode temp = *p;
            temp.next = NULL;
            genStmtMips(&temp, out);
        }
        p = p->next;
    }
    
    fprintf(out, "    li $v0, 10\n    syscall\n");
    fclose(out);
}
