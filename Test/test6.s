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

main:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
addi $fp, $sp, 8


addi $sp, $sp, -40


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -12($fp)


lw $a0, -12($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


lw $t0, -12($fp)
addi $t0, $t0, 1
sw $t0, -12($fp)


lw $a0, -12($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


lw $t0, -12($fp)
li $t1, 2
mul $t0, $t0, $t1
sw $t0, -12($fp)


lw $a0, -12($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


li $t2, 3
lw $t1, -12($fp)
div $t1, $t2
mflo $t0
sw $t0, -12($fp)


lw $a0, -12($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


lw $t0, -32($fp)
sw $t0, -28($fp)


lw $t0, -16($fp)
sw $t0, -44($fp)


li $t0, 1
sw $t0, -48($fp)


lw $t0, -48($fp)
li $t1, 4
mul $t0, $t0, $t1
sw $t0, -48($fp)


lw $t0, -44($fp)
lw $t1, -48($fp)
add $t0, $t0, $t1
sw $t0, -44($fp)


lw $t1, -44($fp)
lw $t0, 0($t1)
sw $t0, -24($fp)


lw $a0, -24($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


li $t0, 0
add $sp, 48
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


