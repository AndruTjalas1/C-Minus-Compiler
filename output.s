.data
x: .word 10
y: .word 0
sum: .word 0
apple: .byte 66
arr: .space 20
arr2: .space 12
carr: .space 3
matrix: .space 24
cmatrix: .space 4
.text
.globl main
main:
    li $t0, 10
    sw $t0, x
    li $t0, 66
    sb $t0, apple
    lb $t0, apple
    move $a0, $t0
    li $v0, 11
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 5
    sw $t0, x
    li $t0, 10
    sw $t0, y
    lw $t0, y
    move $t1, $t0
    lw $t0, x
    add $t0, $t1, $t0
    sw $t0, sum
    lw $t0, sum
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 100
    move $t9, $t0
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 200
    move $t9, $t0
    li $t0, 1
    sll $t0, $t0, 2
    la $t1, arr
    add $t1, $t1, $t0
    sw $t9, 0($t1)
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
    li $t0, 300
    move $t9, $t0
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr2
    add $t1, $t1, $t0
    sw $t9, 0($t1)
    li $t0, 0
    sll $t0, $t0, 2
    la $t1, arr2
    add $t1, $t1, $t0
    lw $t0, 0($t1)
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, 10
    li $v0, 11
    syscall
    li $t0, 88
    move $t9, $t0
    li $t0, 0
    la $t1, carr
    add $t1, $t1, $t0
    sb $t9, 0($t1)
    li $t0, 89
    move $t9, $t0
    li $t0, 1
    la $t1, carr
    add $t1, $t1, $t0
    sb $t9, 0($t1)
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
