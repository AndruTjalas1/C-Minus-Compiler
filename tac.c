#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"
#include "AST.h"

static int tempCount = 0;
static int labelCount = 0;

/* Generate a new temporary variable name */
char* newTemp() {
    char* buf = malloc(16);
    sprintf(buf, "t%d", tempCount++);
    return buf;
}

/* Generate a new label name */
char* newLabel() {
    char* buf = malloc(16);
    sprintf(buf, "L%d", labelCount++);
    return buf;
}

/* Make TAC instruction */
TAC* makeTAC(TACOp op, char* res, char* arg1, char* arg2) {
    TAC* tac = malloc(sizeof(TAC));
    tac->op = op;
    tac->res = res ? strdup(res) : NULL;
    tac->arg1 = arg1 ? strdup(arg1) : NULL;
    tac->arg2 = arg2 ? strdup(arg2) : NULL;
    tac->next = NULL;
    return tac;
}

/* Concatenate two TAC lists */
TAC* concat(TAC* code1, TAC* code2) {
    if (!code1) return code2;
    TAC* cur = code1;
    while (cur->next) cur = cur->next;
    cur->next = code2;
    return code1;
}

/* Generate TAC for conditions (handles logical operators) */
TAC* genConditionTac(ASTNode* node, char* trueLabel, char* falseLabel) {
    if (!node) return NULL;
    
    char* op = node->name;
    
    /* Handle logical AND */
    if (strcmp(op, "&&") == 0) {
        char* midLabel = newLabel();
        TAC* leftCode = genConditionTac(node->left, midLabel, falseLabel);
        TAC* labelCode = makeTAC(TAC_LABEL, midLabel, NULL, NULL);
        TAC* rightCode = genConditionTac(node->right, trueLabel, falseLabel);
        return concat(concat(leftCode, labelCode), rightCode);
    }
    
    /* Handle logical OR */
    if (strcmp(op, "||") == 0) {
        char* midLabel = newLabel();
        TAC* leftCode = genConditionTac(node->left, trueLabel, midLabel);
        TAC* labelCode = makeTAC(TAC_LABEL, midLabel, NULL, NULL);
        TAC* rightCode = genConditionTac(node->right, trueLabel, falseLabel);
        return concat(concat(leftCode, labelCode), rightCode);
    }
    
    /* Handle logical NOT */
    if (strcmp(op, "!") == 0) {
        /* Swap true and false labels */
        return genConditionTac(node->left, falseLabel, trueLabel);
    }
    
    /* Handle logical XOR */
    if (strcmp(op, "xor") == 0) {
        /* XOR: (A && !B) || (!A && B) */
        char* label1 = newLabel();
        char* label2 = newLabel();
        
        /* Check if left is true and right is false */
        TAC* leftTrue1 = genConditionTac(node->left, label1, label2);
        TAC* label1Code = makeTAC(TAC_LABEL, label1, NULL, NULL);
        TAC* rightFalse1 = genConditionTac(node->right, falseLabel, trueLabel);
        
        /* Check if left is false and right is true */
        TAC* label2Code = makeTAC(TAC_LABEL, label2, NULL, NULL);
        TAC* rightTrue2 = genConditionTac(node->right, trueLabel, falseLabel);
        
        return concat(concat(concat(concat(
            leftTrue1, label1Code), rightFalse1), label2Code), rightTrue2);
    }
    
    /* Handle basic comparison operators */
    char* leftPlace = NULL;
    char* rightPlace = NULL;
    TAC* leftCode = genExprTac(node->left, &leftPlace);
    TAC* rightCode = genExprTac(node->right, &rightPlace);
    
    if (!leftPlace || !rightPlace) {
        return NULL;
    }
    
    /* Generate jump to trueLabel if condition is TRUE */
    TACOp condOp;
    if (strcmp(op, "==") == 0) condOp = TAC_IF_EQ;
    else if (strcmp(op, "!=") == 0) condOp = TAC_IF_NEQ;
    else if (strcmp(op, "<") == 0) condOp = TAC_IF_LT;
    else if (strcmp(op, "<=") == 0) condOp = TAC_IF_LE;
    else if (strcmp(op, ">") == 0) condOp = TAC_IF_GT;
    else condOp = TAC_IF_GE;
    
    TAC* trueJump = makeTAC(condOp, trueLabel, leftPlace, rightPlace);
    TAC* falseJump = makeTAC(TAC_GOTO, falseLabel, NULL, NULL);
    
    return concat(concat(concat(leftCode, rightCode), trueJump), falseJump);
}

/* Generate TAC for expressions */
TAC* genExprTac(ASTNode* node, char** place) {
    if (!node) return NULL;

    if (strcmp(node->type, "num") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);
        *place = newTemp();
        return makeTAC(TAC_NUM, *place, buf, NULL);
    }
    else if (strcmp(node->type, "array_decl_init") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);
        return makeTAC(TAC_ARRAY_DECL_INIT, node->name, buf, NULL);
    }
    else if (strcmp(node->type, "char") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);  // Store as ASCII value
        *place = newTemp();
        return makeTAC(TAC_CHAR, *place, buf, NULL);
    }
    else if (strcmp(node->type, "bool") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);  // Store as 0 or 1
        *place = newTemp();
        return makeTAC(TAC_NUM, *place, buf, NULL);
    }
    else if (strcmp(node->type, "string_literal") == 0) {
        // For string literals, use the string itself as the place
        *place = strdup(node->name);
        return NULL;
    }
    else if (strcmp(node->type, "var") == 0) {
        *place = strdup(node->name);
        return NULL;
    }
    else if (strcmp(node->type, "array_access") == 0) {
        char* indexPlace;
        TAC* indexCode = genExprTac(node->left, &indexPlace);
        *place = newTemp();
        TAC* accessCode = makeTAC(TAC_ARRAY_ACCESS, *place, node->name, indexPlace);
        return concat(indexCode, accessCode);
    }
    else if (strcmp(node->type, "array2d_access") == 0) {
        char* index1Place, *index2Place;
        TAC* index1Code = genExprTac(node->left, &index1Place);
        TAC* index2Code = genExprTac(node->right, &index2Place);
        *place = newTemp();
        
        // For 2D access, we need both indices - we'll use a special format
        char indexBuf[64];
        sprintf(indexBuf, "%s,%s", index1Place, index2Place);
        TAC* accessCode = makeTAC(TAC_ARRAY2D_ACCESS, *place, node->name, indexBuf);
        return concat(concat(index1Code, index2Code), accessCode);
    }
    else if (strcmp(node->type, "binop") == 0) {
        char* t1; char* t2;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* c2 = genExprTac(node->right, &t2);
        *place = newTemp();
        TACOp op;
        switch (node->op) {
            case '+': op = TAC_ADD; break;
            case '-': op = TAC_SUB; break;
            case '*': op = TAC_MUL; break;
            case '/': op = TAC_DIV; break;
            default: op = TAC_ADD; break;
        }
        return concat(concat(c1, c2), makeTAC(op, *place, t1, t2));
    }
    else if (strcmp(node->type, "function_call") == 0) {
        // Generate code for arguments
        TAC* argCode = NULL;
        ASTNode* arg = node->args;
        while (arg) {
            char* argPlace;
            TAC* argExpr = genExprTac(arg, &argPlace);
            TAC* argTac = makeTAC(TAC_ARG, argPlace, NULL, NULL);
            argCode = concat(argCode, argExpr);
            argCode = concat(argCode, argTac);
            arg = arg->next;
        }
        
        // Generate the call itself
        *place = newTemp();
        TAC* call = makeTAC(TAC_CALL, *place, node->name, NULL);
        return concat(argCode, call);
    }

    return NULL;
}

/* Generate TAC for statements */
TAC* genStmtTac(ASTNode* node) {
    if (!node) return NULL;

    if (strcmp(node->type, "assign") == 0) {
        char* t1;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* assign = makeTAC(TAC_ASSIGN, node->name, t1, NULL);
        return concat(c1, assign);
    }
    else if (strcmp(node->type, "array_assign") == 0) {
        ASTNode* arrayAccess = node->left;
        char* valuePlace;
        TAC* valueCode = genExprTac(node->right, &valuePlace);
        
        if (strcmp(arrayAccess->type, "array_access") == 0) {
            char* indexPlace;
            TAC* indexCode = genExprTac(arrayAccess->left, &indexPlace);
            TAC* assignCode = makeTAC(TAC_ARRAY_ASSIGN, arrayAccess->name, indexPlace, valuePlace);
            return concat(concat(indexCode, valueCode), assignCode);
        }
        else if (strcmp(arrayAccess->type, "array2d_access") == 0) {
            char* index1Place, *index2Place;
            TAC* index1Code = genExprTac(arrayAccess->left, &index1Place);
            TAC* index2Code = genExprTac(arrayAccess->right, &index2Place);
            
            char indexBuf[64];
            sprintf(indexBuf, "%s,%s", index1Place, index2Place);
            TAC* assignCode = makeTAC(TAC_ARRAY2D_ASSIGN, arrayAccess->name, indexBuf, valuePlace);
            return concat(concat(concat(index1Code, index2Code), valueCode), assignCode);
        }
    }
    else if (strcmp(node->type, "print") == 0) {
        char* t1;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* p = makeTAC(TAC_PRINT, NULL, t1, NULL);
        return concat(c1, p);
    }
    else if (strcmp(node->type, "decl") == 0) {
        return makeTAC(TAC_VAR, node->name, NULL, NULL);
    }
    else if (strcmp(node->type, "string_decl") == 0) {
        // Handle string declaration with initialization
        // string msg = "Hello World"
        char* valuePlace;
        TAC* valueCode = genExprTac(node->left, &valuePlace);
        TAC* declCode = makeTAC(TAC_VAR, node->name, NULL, NULL);
        TAC* assignCode = makeTAC(TAC_ASSIGN, node->name, valuePlace, NULL);
        return concat(concat(declCode, valueCode), assignCode);
    }
    else if (strcmp(node->type, "array_decl") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);
        return makeTAC(TAC_ARRAY_DECL, node->name, buf, NULL);
    }
    else if (strcmp(node->type, "array2d_decl") == 0) {
        char buf1[16], buf2[16];
        sprintf(buf1, "%d", node->left->value);
        sprintf(buf2, "%d", node->right->value);
        return makeTAC(TAC_ARRAY2D_DECL, node->name, buf1, buf2);
    }
    else if (strcmp(node->type, "array2d_decl_init") == 0) {
        char buf1[16], buf2[16];
        sprintf(buf1, "%d", node->left->value);
        sprintf(buf2, "%d", node->right->value);
        return makeTAC(TAC_ARRAY2D_DECL_INIT, node->name, buf1, buf2);
    }
    else if (strcmp(node->type, "if") == 0) {
        // printf("DEBUG: Processing if statement\n");
        
        /* Safety check */
        if (!node->condition) {
            fprintf(stderr, "Error: if statement has no condition\n");
            return NULL;
        }
        
        // printf("DEBUG: If condition exists, type=%s\n", node->condition->type ? node->condition->type : "NULL");
        
        /* Generate labels */
        char* elseLabel = newLabel();
        char* endLabel = newLabel();
        char* ifBodyLabel = newLabel();
        
        /* Determine where to jump when condition is false */
        char* falseLabel = (node->elseifList || node->elseBlock) ? elseLabel : endLabel;
        
        /* Generate condition code using new function that handles logical operators */
        TAC* condCode = genConditionTac(node->condition, ifBodyLabel, falseLabel);
        
        if (!condCode) {
            fprintf(stderr, "Error: failed to generate condition code\n");
            return NULL;
        }
        
        /* Generate if block code */
        TAC* ifBodyLabelCode = makeTAC(TAC_LABEL, ifBodyLabel, NULL, NULL);
        TAC* ifCode = genTAC(node->ifBlock);
        
        /* Jump to end after if block */
        TAC* gotoEnd = makeTAC(TAC_GOTO, endLabel, NULL, NULL);
        
        /* Start building the complete TAC */
        TAC* result = concat(condCode, ifBodyLabelCode);
        result = concat(result, ifCode);
        result = concat(result, gotoEnd);
        
        /* Handle elseif chain */
        if (node->elseifList) {
            result = concat(result, makeTAC(TAC_LABEL, elseLabel, NULL, NULL));
            
            ASTNode* elseif = node->elseifList;
            while (elseif) {
                /* Safety check */
                if (!elseif->condition) {
                    fprintf(stderr, "Error: elseif has no condition\n");
                    break;
                }
                
                char* elseifBodyLabel = newLabel();
                char* nextLabel = (elseif->next || node->elseBlock) ? newLabel() : endLabel;
                
                /* Generate elseif condition */
                TAC* elseifCondCode = genConditionTac(elseif->condition, elseifBodyLabel, nextLabel);
                
                if (!elseifCondCode) {
                    fprintf(stderr, "Error: failed to generate elseif condition\n");
                    break;
                }
                
                TAC* elseifBodyLabelCode = makeTAC(TAC_LABEL, elseifBodyLabel, NULL, NULL);
                TAC* elseifBlock = genTAC(elseif->ifBlock);
                TAC* elseifGoto = makeTAC(TAC_GOTO, endLabel, NULL, NULL);
                
                result = concat(result, elseifCondCode);
                result = concat(result, elseifBodyLabelCode);
                result = concat(result, elseifBlock);
                result = concat(result, elseifGoto);
                
                if (elseif->next || node->elseBlock) {
                    result = concat(result, makeTAC(TAC_LABEL, nextLabel, NULL, NULL));
                }
                
                elseif = elseif->next;
            }
        }
        
        /* Handle else block */
        if (node->elseBlock) {
            if (!node->elseifList) {
                result = concat(result, makeTAC(TAC_LABEL, elseLabel, NULL, NULL));
            }
            TAC* elseCode = genTAC(node->elseBlock);
            result = concat(result, elseCode);
        }
        
        /* Add end label */
        result = concat(result, makeTAC(TAC_LABEL, endLabel, NULL, NULL));
        
        return result;
    }
    else if (strcmp(node->type, "function_decl") == 0) {
        // Generate function begin marker
        TAC* funcBegin = makeTAC(TAC_FUNCTION_BEGIN, node->name, node->returnType, NULL);
        
        // Generate parameter declarations
        TAC* paramCode = NULL;
        ASTNode* param = node->params;
        while (param) {
            TAC* paramTac = makeTAC(TAC_PARAM, param->name, param->returnType, NULL);
            paramCode = concat(paramCode, paramTac);
            param = param->next;
        }
        
        // Generate function body
        TAC* bodyCode = genTAC(node->body);
        
        // Generate function end marker
        TAC* funcEnd = makeTAC(TAC_FUNCTION_END, node->name, NULL, NULL);
        
        // Concatenate all parts
        TAC* result = concat(funcBegin, paramCode);
        result = concat(result, bodyCode);
        result = concat(result, funcEnd);
        
        return result;
    }
    else if (strcmp(node->type, "function_call") == 0) {
        // Generate code for arguments
        TAC* argCode = NULL;
        ASTNode* arg = node->args;
        while (arg) {
            char* argPlace;
            TAC* argExpr = genExprTac(arg, &argPlace);
            TAC* argTac = makeTAC(TAC_ARG, argPlace, NULL, NULL);
            argCode = concat(argCode, argExpr);
            argCode = concat(argCode, argTac);
            arg = arg->next;
        }
        
        // Generate the call itself
        char* resultTemp = newTemp();
        TAC* call = makeTAC(TAC_CALL, resultTemp, node->name, NULL);
        return concat(argCode, call);
    }
    else if (strcmp(node->type, "return") == 0) {
        if (node->left) {
            // Return with value
            char* returnPlace;
            TAC* exprCode = genExprTac(node->left, &returnPlace);
            TAC* returnTac = makeTAC(TAC_RETURN, returnPlace, NULL, NULL);
            return concat(exprCode, returnTac);
        } else {
            // Return without value
            return makeTAC(TAC_RETURN, NULL, NULL, NULL);
        }
    }
    else if (strcmp(node->type, "break") == 0) {
        // Break in TAC is just represented as a note - actual jump is in MIPS
        return makeTAC(TAC_BREAK, NULL, NULL, NULL);
    }
    else if (strcmp(node->type, "continue") == 0) {
        // Continue in TAC is just represented as a note - actual jump is in MIPS
        return makeTAC(TAC_CONTINUE, NULL, NULL, NULL);
    }

    return NULL;
}

/* Generate TAC recursively for AST */
TAC* genTAC(ASTNode* root) {
    if (!root) return NULL;
    
    // Debug output
    // if (root->type) {
    //     printf("Generating TAC for: %s\n", root->type);
    // }
    
    TAC* code = genStmtTac(root);
    if (root->next) {
        code = concat(code, genTAC(root->next));
    }
    
    return code;
}

/* ========== TAC OPTIMIZATION FUNCTIONS ========== */

/* Check if a string represents a constant */
int isConstant(const char* operand) {
    if (!operand) return 0;
    if (operand[0] == '-' || isdigit(operand[0])) {
        for (int i = 1; operand[i]; i++) {
            if (!isdigit(operand[i])) return 0;
        }
        return 1;
    }
    return 0;
}

/* Get the integer value of a constant */
int getConstantValue(const char* operand) {
    return atoi(operand);
}

/* Create a string representation of a constant */
char* makeConstant(int value) {
    char* result = malloc(16);
    sprintf(result, "%d", value);
    return result;
}

/* Count TAC instructions */
int countTACInstructions(TAC* code) {
    int count = 0;
    TAC* cur = code;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* Print optimization statistics */
void printOptimizationStats(int originalCount, int optimizedCount) {
    int saved = originalCount - optimizedCount;
    double percentage = originalCount > 0 ? ((double)saved / originalCount) * 100.0 : 0.0;
    printf("TAC Optimization Results:\n");
    printf("  Original instructions: %d\n", originalCount);
    printf("  Optimized instructions: %d\n", optimizedCount);
    printf("  Instructions saved: %d (%.1f%%)\n", saved, percentage);
}

/* Constant folding optimization */
TAC* constantFolding(TAC* code) {
    TAC* cur = code;
    int changes = 0;
    
    while (cur) {
        if ((cur->op == TAC_ADD || cur->op == TAC_SUB || 
             cur->op == TAC_MUL || cur->op == TAC_DIV) &&
            isConstant(cur->arg1) && isConstant(cur->arg2)) {
            
            int val1 = getConstantValue(cur->arg1);
            int val2 = getConstantValue(cur->arg2);
            int result;
            
            switch (cur->op) {
                case TAC_ADD: result = val1 + val2; break;
                case TAC_SUB: result = val1 - val2; break;
                case TAC_MUL: result = val1 * val2; break;
                case TAC_DIV: 
                    if (val2 != 0) result = val1 / val2; 
                    else { cur = cur->next; continue; }
                    break;
                default: cur = cur->next; continue;
            }
            
            // Replace with constant assignment
            cur->op = TAC_NUM;
            free(cur->arg1);
            free(cur->arg2);
            cur->arg1 = makeConstant(result);
            cur->arg2 = NULL;
            changes++;
        }
        cur = cur->next;
    }
    
    if (changes > 0) {
        printf("  Constant folding: %d operations simplified\n", changes);
    }
    return code;
}

/* Algebraic simplification */
TAC* algebraicSimplification(TAC* code) {
    TAC* cur = code;
    int changes = 0;
    
    while (cur) {
        if (cur->op == TAC_ADD) {
            // x + 0 = x, 0 + x = x
            if (isConstant(cur->arg1) && getConstantValue(cur->arg1) == 0) {
                cur->op = TAC_ASSIGN;
                free(cur->arg1);
                cur->arg1 = cur->arg2;
                cur->arg2 = NULL;
                changes++;
            } else if (isConstant(cur->arg2) && getConstantValue(cur->arg2) == 0) {
                cur->op = TAC_ASSIGN;
                free(cur->arg2);
                cur->arg2 = NULL;
                changes++;
            }
        }
        else if (cur->op == TAC_SUB) {
            // x - 0 = x
            if (isConstant(cur->arg2) && getConstantValue(cur->arg2) == 0) {
                cur->op = TAC_ASSIGN;
                free(cur->arg2);
                cur->arg2 = NULL;
                changes++;
            }
        }
        else if (cur->op == TAC_MUL) {
            // x * 0 = 0, 0 * x = 0
            if ((isConstant(cur->arg1) && getConstantValue(cur->arg1) == 0) ||
                (isConstant(cur->arg2) && getConstantValue(cur->arg2) == 0)) {
                cur->op = TAC_NUM;
                free(cur->arg1);
                free(cur->arg2);
                cur->arg1 = makeConstant(0);
                cur->arg2 = NULL;
                changes++;
            }
            // x * 1 = x, 1 * x = x
            else if (isConstant(cur->arg1) && getConstantValue(cur->arg1) == 1) {
                cur->op = TAC_ASSIGN;
                free(cur->arg1);
                cur->arg1 = cur->arg2;
                cur->arg2 = NULL;
                changes++;
            } else if (isConstant(cur->arg2) && getConstantValue(cur->arg2) == 1) {
                cur->op = TAC_ASSIGN;
                free(cur->arg2);
                cur->arg2 = NULL;
                changes++;
            }
        }
        else if (cur->op == TAC_DIV) {
            // x / 1 = x
            if (isConstant(cur->arg2) && getConstantValue(cur->arg2) == 1) {
                cur->op = TAC_ASSIGN;
                free(cur->arg2);
                cur->arg2 = NULL;
                changes++;
            }
        }
        cur = cur->next;
    }
    
    if (changes > 0) {
        printf("  Algebraic simplification: %d operations simplified\n", changes);
    }
    return code;
}

/* Helper function to check if a string looks like a string literal (has spaces or special chars) */
int isStringLiteral(const char* str) {
    if (!str) return 0;
    // Check if it contains spaces or looks like a sentence
    while (*str) {
        if (*str == ' ' || *str == ',' || *str == '!' || *str == '?') {
            return 1;
        }
        str++;
    }
    return 0;
}

/* Copy propagation optimization */
TAC* copyPropagation(TAC* code) {
    TAC* cur = code;
    int changes = 0;
    
    // Simple copy propagation: if we have t1 = t2, replace uses of t1 with t2
    while (cur) {
        if (cur->op == TAC_ASSIGN && cur->arg1 && !isConstant(cur->arg1)) {
            char* target = cur->res;
            char* source = cur->arg1;
            
            // Don't propagate string literals - keep them as variable references
            if (isStringLiteral(source)) {
                cur = cur->next;
                continue;
            }
            
            // Look ahead and replace uses of target with source
            TAC* next = cur->next;
            while (next) {
                // Replace in arg1
                if (next->arg1 && strcmp(next->arg1, target) == 0) {
                    free(next->arg1);
                    next->arg1 = strdup(source);
                    changes++;
                }
                // Replace in arg2
                if (next->arg2 && strcmp(next->arg2, target) == 0) {
                    free(next->arg2);
                    next->arg2 = strdup(source);
                    changes++;
                }
                
                // Stop if target is redefined
                if (next->res && strcmp(next->res, target) == 0) {
                    break;
                }
                // Stop if source is redefined
                if (next->res && strcmp(next->res, source) == 0) {
                    break;
                }
                
                next = next->next;
            }
        }
        cur = cur->next;
    }
    
    if (changes > 0) {
        printf("  Copy propagation: %d references updated\n", changes);
    }
    return code;
}

/* Dead code elimination */
TAC* deadCodeElimination(TAC* code) {
    if (!code) return NULL;
    
    TAC* cur = code;
    TAC* prev = NULL;
    int changes = 0;
    
    while (cur) {
        int isDead = 0;
        
        // Check if this instruction defines a variable that's never used
        if (cur->res && (cur->op == TAC_NUM || cur->op == TAC_CHAR || 
                         cur->op == TAC_ADD || cur->op == TAC_SUB ||
                         cur->op == TAC_MUL || cur->op == TAC_DIV ||
                         cur->op == TAC_ASSIGN)) {
            
            // Check if this result is used anywhere later
            int isUsed = 0;
            TAC* check = cur->next;
            while (check) {
                if ((check->arg1 && strcmp(check->arg1, cur->res) == 0) ||
                    (check->arg2 && strcmp(check->arg2, cur->res) == 0)) {
                    isUsed = 1;
                    break;
                }
                // If the variable is redefined, stop looking
                if (check->res && strcmp(check->res, cur->res) == 0) {
                    break;
                }
                check = check->next;
            }
            
            // If it's a temporary variable (starts with 't') and not used, it's dead
            if (!isUsed && cur->res[0] == 't' && isdigit(cur->res[1])) {
                isDead = 1;
            }
        }
        
        if (isDead) {
            if (prev) {
                prev->next = cur->next;
            } else {
                code = cur->next;
            }
            TAC* toFree = cur;
            cur = cur->next;
            free(toFree->res);
            free(toFree->arg1);
            free(toFree->arg2);
            free(toFree);
            changes++;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    
    if (changes > 0) {
        printf("  Dead code elimination: %d instructions removed\n", changes);
    }
    return code;
}

/* Main optimization function */
TAC* optimizeTAC(TAC* code) {
    if (!code) return NULL;
    
    int originalCount = countTACInstructions(code);
    printf("\nOptimizing TAC...\n");
    
    // Apply optimizations multiple times until no more changes
    int totalPasses = 0;
    int changed;
    
    do {
        totalPasses++;
        printf("  Pass %d:\n", totalPasses);
        changed = 0;
        
        int beforeCount = countTACInstructions(code);
        
        code = constantFolding(code);
        code = algebraicSimplification(code);
        code = copyPropagation(code);
        code = deadCodeElimination(code);
        
        int afterCount = countTACInstructions(code);
        if (afterCount < beforeCount) {
            changed = 1;
        }
        
    } while (changed && totalPasses < 5); // Limit to 5 passes to avoid infinite loops
    
    int optimizedCount = countTACInstructions(code);
    printOptimizationStats(originalCount, optimizedCount);
    
    return code;
}

/* Output TAC to file */
void generateTAC(ASTNode* root, const char* filename) {
    TAC* code = genTAC(root);
    
    // Generate unoptimized TAC file
    FILE* unoptFile = fopen("tac_unoptimized.txt", "w");
    if (unoptFile) {
        fprintf(unoptFile, "# Unoptimized Three Address Code\n\n");
        TAC* cur = code;
        while (cur) {
            switch (cur->op) {
                case TAC_ADD: fprintf(unoptFile, "%s = %s + %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_SUB: fprintf(unoptFile, "%s = %s - %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_MUL: fprintf(unoptFile, "%s = %s * %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_DIV: fprintf(unoptFile, "%s = %s / %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ASSIGN: fprintf(unoptFile, "%s = %s\n", cur->res, cur->arg1); break;
                case TAC_VAR: fprintf(unoptFile, "declare %s\n", cur->res); break;
                case TAC_NUM: fprintf(unoptFile, "%s = %s\n", cur->res, cur->arg1); break;
                case TAC_CHAR: fprintf(unoptFile, "%s = '%c'  // ASCII %s\n", cur->res, atoi(cur->arg1), cur->arg1); break;
                case TAC_PRINT: fprintf(unoptFile, "print %s\n", cur->arg1); break;
                case TAC_ARRAY_DECL: fprintf(unoptFile, "declare %s[%s]\n", cur->res, cur->arg1); break;
                case TAC_ARRAY_DECL_INIT: fprintf(unoptFile, "declare %s[%s] with init\n", cur->res, cur->arg1); break;
                case TAC_ARRAY2D_DECL: fprintf(unoptFile, "declare %s[%s][%s]\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ARRAY2D_DECL_INIT: fprintf(unoptFile, "declare %s[%s][%s] with init\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ARRAY_ACCESS: fprintf(unoptFile, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ARRAY2D_ACCESS: fprintf(unoptFile, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ARRAY_ASSIGN: fprintf(unoptFile, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_ARRAY2D_ASSIGN: fprintf(unoptFile, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2); break;
                case TAC_LABEL: fprintf(unoptFile, "%s:\n", cur->res); break;
                case TAC_GOTO: fprintf(unoptFile, "goto %s\n", cur->res); break;
                case TAC_IF_EQ: fprintf(unoptFile, "if %s == %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_IF_NEQ: fprintf(unoptFile, "if %s != %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_IF_LT: fprintf(unoptFile, "if %s < %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_IF_LE: fprintf(unoptFile, "if %s <= %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_IF_GT: fprintf(unoptFile, "if %s > %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_IF_GE: fprintf(unoptFile, "if %s >= %s goto %s\n", cur->arg1, cur->arg2, cur->res); break;
                case TAC_FUNCTION_BEGIN: fprintf(unoptFile, "\nfunction %s(%s):\n", cur->res, cur->arg1 ? cur->arg1 : "void"); break;
                case TAC_FUNCTION_END: fprintf(unoptFile, "end function %s\n\n", cur->res); break;
                case TAC_PARAM: fprintf(unoptFile, "param %s %s\n", cur->arg1, cur->res); break;
                case TAC_CALL: fprintf(unoptFile, "%s = call %s\n", cur->res, cur->arg1); break;
                case TAC_RETURN: fprintf(unoptFile, "return %s\n", cur->res ? cur->res : ""); break;
                case TAC_ARG: fprintf(unoptFile, "arg %s\n", cur->res); break;
                case TAC_BREAK: fprintf(unoptFile, "break\n"); break;
                case TAC_CONTINUE: fprintf(unoptFile, "continue\n"); break;
            }
            cur = cur->next;
        }
        fclose(unoptFile);
    }
    
    // Optimize the TAC
    code = optimizeTAC(code);
    
    // Generate optimized TAC file
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        return;
    }

    fprintf(out, "# Optimized Three Address Code\n");
    fprintf(out, "# Generated from AST\n\n");

    TAC* cur = code;
    while (cur) {
        switch (cur->op) {
            case TAC_ADD: 
                fprintf(out, "%s = %s + %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_SUB: 
                fprintf(out, "%s = %s - %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_MUL: 
                fprintf(out, "%s = %s * %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_DIV: 
                fprintf(out, "%s = %s / %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_ASSIGN: 
                fprintf(out, "%s = %s\n", cur->res, cur->arg1); 
                break;
            case TAC_VAR: 
                fprintf(out, "declare %s\n", cur->res); 
                break;
            case TAC_NUM: 
                fprintf(out, "%s = %s\n", cur->res, cur->arg1); 
                break;
            case TAC_CHAR: 
                fprintf(out, "%s = '%c'  // ASCII %s\n", cur->res, atoi(cur->arg1), cur->arg1); 
                break;
            case TAC_PRINT: 
                fprintf(out, "print %s\n", cur->arg1); 
                break;
            case TAC_ARRAY_DECL: 
                fprintf(out, "declare %s[%s]\n", cur->res, cur->arg1); 
                break;
            case TAC_ARRAY_DECL_INIT: 
                fprintf(out, "declare %s[%s] with init\n", cur->res, cur->arg1); 
                break;
            case TAC_ARRAY2D_DECL: 
                fprintf(out, "declare %s[%s][%s]\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_ARRAY2D_DECL_INIT: 
                fprintf(out, "declare %s[%s][%s] with init\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_ARRAY_ACCESS:
                fprintf(out, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY2D_ACCESS:
                fprintf(out, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY_ASSIGN:
                fprintf(out, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY2D_ASSIGN:
                fprintf(out, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_LABEL:
                fprintf(out, "%s:\n", cur->res);
                break;
            case TAC_GOTO:
                fprintf(out, "goto %s\n", cur->res);
                break;
            case TAC_IF_EQ:
                fprintf(out, "if %s == %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_IF_NEQ:
                fprintf(out, "if %s != %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_IF_LT:
                fprintf(out, "if %s < %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_IF_LE:
                fprintf(out, "if %s <= %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_IF_GT:
                fprintf(out, "if %s > %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_IF_GE:
                fprintf(out, "if %s >= %s goto %s\n", cur->arg1, cur->arg2, cur->res);
                break;
            case TAC_FUNCTION_BEGIN:
                fprintf(out, "\nfunction %s(%s):\n", cur->res, cur->arg1 ? cur->arg1 : "void");
                break;
            case TAC_FUNCTION_END:
                fprintf(out, "end function %s\n\n", cur->res);
                break;
            case TAC_PARAM:
                fprintf(out, "param %s %s\n", cur->arg1, cur->res);
                break;
            case TAC_CALL:
                fprintf(out, "%s = call %s\n", cur->res, cur->arg1);
                break;
            case TAC_RETURN:
                fprintf(out, "return %s\n", cur->res ? cur->res : "");
                break;
            case TAC_ARG:
                fprintf(out, "arg %s\n", cur->res);
                break;
            case TAC_BREAK:
                fprintf(out, "break\n");
                break;
            case TAC_CONTINUE:
                fprintf(out, "continue\n");
                break;
        }
        cur = cur->next;
    }

    fclose(out);
    printf("TAC generated successfully: %s\n", filename);
}