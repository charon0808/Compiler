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
move $fp, $sp
addi $sp, $sp, -4
sw $ra, 0($sp)


addi $sp, $sp, -4
lw $t0, 0($fp)
sw $t0, 0($sp)
addi $sp, $sp, -12


addi $sp, $sp, -8


lw $t1, -8($fp)
li $t0, 1
beq $t1, $t0, iamlabel0


lw $t0, -8($fp)
addi $t0, $t0, -1
sw $t0, -20($fp)


addi $sp, $sp, -4
lw $t0, -20($fp)
sw $t0, 0($sp)

jal fact


lw $t0, -8($fp)
lw $t1, -16($fp)
mul $t0, $t0, $t1
sw $t0, -12($fp)


lw $t0, -12($fp)
move $v0, $t0
jr $ra


j  iamlabel2


iamlabel0:


lw $t0, -8($fp)
move $v0, $t0
jr $ra


iamlabel2:


main:
move $fp, $sp
addi $sp, $sp, -4
sw $ra, 0($sp)


addi $sp, $sp, -8


addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
sw $v0, -8($fp)


lw $t1, -8($fp)
li $t0, 1
bgt $t1, $t0, iamlabel3


li $t0, 1
sw $t0, -12($fp)


j  iamlabel5


iamlabel3:


addi $sp, $sp, -4
lw $t0, -8($fp)
sw $t0, 0($sp)

jal fact


iamlabel5:


lw $a0, -12($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

li $t0, 0
move $v0, $t0
jr $ra


