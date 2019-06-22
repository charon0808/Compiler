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

fact:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
addi $fp, $sp, 8


addi $sp, $sp, -4
lw $t0, 0($fp)
sw $t0, 0($sp)
addi $sp, $sp, -24


lw $t0, -12($fp)
li $t1, 1
beq $t0, $t1, iamlabel0


lw $t0, -12($fp)
addi $t0, $t0, -1
sw $t0, -24($fp)


addi $sp, $sp, -4
lw $t0, -24($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fact
move $t0, $v0
sw $v0, -20($fp)
addi $sp, $sp, 4
lw $ra, -4($fp)


lw $t0, -12($fp)
lw $t1, -20($fp)
mul $t0, $t0, $t1
sw $t0, -16($fp)


lw $t0, -16($fp)
add $sp, 36
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


j  iamlabel2


iamlabel0:


lw $t0, -12($fp)
add $sp, 36
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


iamlabel2:


lw $t0, -12($fp)
add $sp, 36
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


lw $t0, -12($fp)
addi $t0, $t0, -1
sw $t0, -36($fp)


addi $sp, $sp, -4
lw $t0, -36($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fact
move $t0, $v0
sw $v0, -32($fp)
addi $sp, $sp, 4
lw $ra, -4($fp)


lw $t0, -12($fp)
lw $t1, -32($fp)
mul $t0, $t0, $t1
sw $t0, -28($fp)


lw $t0, -28($fp)
add $sp, 36
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


addi $sp, $sp, -8


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -12($fp)


lw $t0, -12($fp)
li $t1, 1
bgt $t0, $t1, iamlabel3


li $t0, 1
sw $t0, -16($fp)


j  iamlabel5


iamlabel3:


addi $sp, $sp, -4
lw $t0, -12($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fact
move $t0, $v0
sw $v0, -16($fp)
addi $sp, $sp, 4
lw $ra, -4($fp)


iamlabel5:


lw $a0, -16($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


li $t0, 0
add $sp, 16
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


addi $sp, $sp, -4
lw $t0, -12($fp)
sw $t0, 0($sp)

sw $ra, -4($fp)
jal fact
move $t0, $v0
sw $v0, -16($fp)
addi $sp, $sp, 4
lw $ra, -4($fp)


