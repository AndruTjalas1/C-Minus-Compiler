.data
.align 2
var_sum: .word 0
var_a: .word 0
var_b: .word 0
var_n: .word 0
var_x: .word 0
var_y: .word 0
var_constant: .word 0
var_fact: .word 0
var_result: .word 0
var_product: .word 0
var_prev: .word 0
var_prevFact: .word 0
.text
.globl main

# Function: add
func_add:
    # Function prologue
    addi $sp, $sp, -8
    sw $fp, 4($sp)
    sw $ra, 0($sp)
    move $fp, $sp
    lw $t0, 8($fp)
    sw $t0, var_a
    lw $t0, 12($fp)
    sw $t0, var_b
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, var_a
    move $s0, $t0
    lw $t0, var_b
    add $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    sw $t0, var_result
    lw $t0, var_result
    move $v0, $t0
    j func_add_exit
    # Function epilogue
func_add_exit:
    move $sp, $fp
    lw $ra, 0($sp)
    lw $fp, 4($sp)
    addi $sp, $sp, 8
    jr $ra

# Function: multiply
func_multiply:
    # Function prologue
    addi $sp, $sp, -8
    sw $fp, 4($sp)
    sw $ra, 0($sp)
    move $fp, $sp
    lw $t0, 8($fp)
    sw $t0, var_x
    lw $t0, 12($fp)
    sw $t0, var_y
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, var_x
    move $s0, $t0
    lw $t0, var_y
    mul $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    move $v0, $t0
    j func_multiply_exit
    # Function epilogue
func_multiply_exit:
    move $sp, $fp
    lw $ra, 0($sp)
    lw $fp, 4($sp)
    addi $sp, $sp, 8
    jr $ra

# Function: factorial
func_factorial:
    # Function prologue
    addi $sp, $sp, -8
    sw $fp, 4($sp)
    sw $ra, 0($sp)
    move $fp, $sp
    lw $t0, 8($fp)
    sw $t0, var_n
    lw $t0, var_n
    move $t8, $t0
    li $t0, 1
    move $t9, $t0
    slt $t7, $t9, $t8
    bne $t7, $zero, endif_0
    li $t0, 1
    move $v0, $t0
    j func_factorial_exit
    j endif_0
endif_0:
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, var_n
    move $s0, $t0
    li $t0, 1
    sub $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    sw $t0, var_prev
    # Function call: factorial
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    addi $sp, $sp, -4
    lw $t0, var_prev
    sw $t0, 0($sp)
    jal func_factorial
    addi $sp, $sp, 4
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, var_prevFact
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, var_n
    move $s0, $t0
    lw $t0, var_prevFact
    mul $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    move $v0, $t0
    j func_factorial_exit
    # Function epilogue
func_factorial_exit:
    move $sp, $fp
    lw $ra, 0($sp)
    lw $fp, 4($sp)
    addi $sp, $sp, 8
    jr $ra

# Function: getConstant
func_getConstant:
    # Function prologue
    addi $sp, $sp, -8
    sw $fp, 4($sp)
    sw $ra, 0($sp)
    move $fp, $sp
    li $t0, 42
    move $v0, $t0
    j func_getConstant_exit
    # Function epilogue
func_getConstant_exit:
    move $sp, $fp
    lw $ra, 0($sp)
    lw $fp, 4($sp)
    addi $sp, $sp, 8
    jr $ra

main:
    li $t0, 5
    sw $t0, var_a
    li $t0, 3
    sw $t0, var_b
    # Function call: add
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    addi $sp, $sp, -8
    lw $t0, var_a
    sw $t0, 0($sp)
    lw $t0, var_b
    sw $t0, 4($sp)
    jal func_add
    addi $sp, $sp, 8
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, var_sum
    lw $t0, var_sum
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    # Function call: multiply
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    addi $sp, $sp, -8
    lw $t0, var_a
    sw $t0, 0($sp)
    lw $t0, var_b
    sw $t0, 4($sp)
    jal func_multiply
    addi $sp, $sp, 8
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, var_product
    lw $t0, var_product
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    # Function call: factorial
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    addi $sp, $sp, -4
    li $t0, 5
    sw $t0, 0($sp)
    jal func_factorial
    addi $sp, $sp, 4
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, var_fact
    lw $t0, var_fact
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    # Function call: getConstant
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal func_getConstant
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, var_constant
    lw $t0, var_constant
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $v0, 10
    syscall
