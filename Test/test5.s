.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

read:
li $v0, 4
la $a0, _prompt
syscall
li $v0, 5
syscall
jr $ra

write:
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
move $v0, $0
jr $ra

fib:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
addi $fp, $sp, 8


addi $sp, $sp, -4
lw $t0, 0($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 4($fp)
sw $t0, 0($sp)
addi $sp, $sp, -12


lw $t0, -12($fp)
li $t1, 1
beq $t0, $t1, iamlabel0


j  iamlabel1


iamlabel0:


li $t0, 1
add $sp, 28
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


iamlabel1:


lw $t0, -16($fp)
addi $t0, $t0, 1
sw $t0, -16($fp)


lw $t0, -12($fp)
addi $t0, $t0, -1
sw $t0, -28($fp)


addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)

addi $sp, $sp, -4
lw $t0, -28($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fib
move $t0, $v0
sw $v0, -24($fp)
addi $sp, $sp, 8
lw $ra, -4($fp)


li $t0, 3 
lw $t1, -24($fp)
add $t0, $t0, $t1
sw $t0, -20($fp)


lw $t0, -20($fp)
add $sp, 28
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


main:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
addi $fp, $sp, 8


addi $sp, $sp, -12


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -12($fp)


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -16($fp)


addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)

addi $sp, $sp, -4
lw $t0, -12($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fib
move $t0, $v0
sw $v0, -20($fp)
addi $sp, $sp, 8
lw $ra, -4($fp)


lw $a0, -20($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


li $t0, 0
add $sp, 20
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


