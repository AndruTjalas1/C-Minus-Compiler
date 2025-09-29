.data
apple: .byte 66
carr: .space 3
cmatrix: .space 4
.align 2
x: .word 10
y: .word 0
sum: .word 0
arr1: .space 12
arr: .space 20
matrix: .space 24
.text
.globl main
main:
    li $t0, 10
    sw $t0, x
    li $t0, 66
    sb $t0, apple
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lb $t0, apple
    move $s0, $t0
    li $t0, 67
    add $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 5
    sw $t0, x
    li $t0, 10
    sw $t0, y
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, y
    move $s0, $t0
    lw $t0, x
    add $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    sw $t0, sum
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    lw $t0, sum
    move $s0, $t0
    li $t0, 5
    add $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    move $t9, $t0
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 2
    move $t9, $t0
    li $t0, 1
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    sw $s0, -4($sp)
    addiu $sp, $sp, -4
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $s0, $t0
    li $t0, 1
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    add $t0, $s0, $t0
    addiu $sp, $sp, 4
    lw $s0, -4($sp)
    move $t9, $t0
    li $t0, 2
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 2
    sll $t0, $t0, 2
    la $t1, arr1
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 10
    li $t1, 0
    sll $t1, $t1, 2
    la $t2, arr
    add $t2, $t2, $t1
    sw $t0, 0($t2)
    li $t0, 20
    li $t1, 1
    sll $t1, $t1, 2
    la $t2, arr
    add $t2, $t2, $t1
    sw $t0, 0($t2)
    li $t0, 30
    li $t1, 2
    sll $t1, $t1, 2
    la $t2, arr
    add $t2, $t2, $t1
    sw $t0, 0($t2)
    li $t0, 40
    li $t1, 3
    sll $t1, $t1, 2
    la $t2, arr
    add $t2, $t2, $t1
    sw $t0, 0($t2)
    li $t0, 50
    li $t1, 4
    sll $t1, $t1, 2
    la $t2, arr
    add $t2, $t2, $t1
    sw $t0, 0($t2)
    li $t0, 65
    li $t1, 0
    la $t2, carr
    add $t2, $t2, $t1
    sb $t0, 0($t2)
    li $t0, 66
    li $t1, 1
    la $t2, carr
    add $t2, $t2, $t1
    sb $t0, 0($t2)
    li $t0, 67
    li $t1, 2
    la $t2, carr
    add $t2, $t2, $t1
    sb $t0, 0($t2)
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    sll $t0, $t0, 2
    la $t1, arr
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 0
    la $t1, carr
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    la $t1, carr
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 0
    la $t1, carr
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    la $t1, carr
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    move $t9, $t0
    li $t0, 0
    move $t2, $t0
    li $t3, 3
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    sll $t0, $t0, 2
    la $t1, matrix
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 2
    move $t9, $t0
    li $t0, 0
    move $t2, $t0
    li $t3, 3
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    sll $t0, $t0, 2
    la $t1, matrix
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 0
    move $t2, $t0
    li $t3, 3
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    sll $t0, $t0, 2
    la $t1, matrix
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 0
    move $t2, $t0
    li $t3, 3
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    sll $t0, $t0, 2
    la $t1, matrix
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 77
    move $t9, $t0
    li $t0, 0
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    sb $t9, 0($t1)
    li $t0, 78
    move $t9, $t0
    li $t0, 0
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    sb $t9, 0($t1)
    li $t0, 79
    move $t9, $t0
    li $t0, 1
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    sb $t9, 0($t1)
    li $t0, 80
    move $t9, $t0
    li $t0, 1
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    sb $t9, 0($t1)
    li $t0, 0
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 0
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 0
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 1
    move $t2, $t0
    li $t3, 2
    mul $t2, $t2, $t3
    li $t0, 1
    add $t0, $t2, $t0
    la $t1, cmatrix
    add $t1, $t1, $t0
    lb $t0, 0($t1)
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $v0, 10
    syscall
