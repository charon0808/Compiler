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

a:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
addi $fp, $sp, 8


addi $sp, $sp, -8


li $t0, 3
li $t1, 4
mul $t0, $t0, $t1
sw $t0, -16($fp)


lw $t0, -16($fp)
addi $t0, $t0, 12
sw $t0, -12($fp)


lw $t0, -12($fp)
add $sp, 16
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


bb:
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
addi $sp, $sp, -4
lw $t0, 8($fp)
sw $t0, 0($sp)
addi $sp, $sp, -20


sw $ra, -4($fp)
jal a
move $t0, $v0
sw $v0, -36($fp)
lw $ra, -4($fp)


lw $t0, -16($fp)
lw $t1, -20($fp)
mul $t0, $t0, $t1
sw $t0, -40($fp)


lw $t0, -36($fp)
lw $t1, -40($fp)
add $t0, $t0, $t1
sw $t0, -28($fp)


sw $ra, -4($fp)
jal a
move $t0, $v0
sw $v0, -32($fp)
lw $ra, -4($fp)


lw $t0, -28($fp)
lw $t1, -32($fp)
add $t0, $t0, $t1
sw $t0, -24($fp)


lw $t0, -24($fp)
add $sp, 40
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


addi $sp, $sp, -16


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -16($fp)


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -20($fp)


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -24($fp)


lw $t0, -24($fp)
li $t1, 3
bgt $t0, $t1, iamlabel0


j  iamlabel1


iamlabel0:


addi $sp, $sp, -4
lw $t0, -24($fp)
sw $t0, 0($sp)

addi $sp, $sp, -4
lw $t0, -20($fp)
sw $t0, 0($sp)

addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal bb
move $t0, $v0
sw $v0, -12($fp)
addi $sp, $sp, 12
lw $ra, -4($fp)


iamlabel1:


lw $a0, -12($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


li $t0, 1
add $sp, 24
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


