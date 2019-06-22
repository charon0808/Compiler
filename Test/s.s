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


addi $sp, $sp, -28


li $t0, 0
sw $t0, -12($fp)


li $t0, 1
sw $t0, -16($fp)


li $t0, 0
sw $t0, -20($fp)


addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
sw $v0, -24($fp)


iamlabel0:


lw $t0, -20($fp)
lw $t1, -24($fp)
blt $t0, $t1, iamlabel1


j  iamlabel2


iamlabel1:


lw $t0, -12($fp)
lw $t1, -16($fp)
add $t0, $t0, $t1
sw $t0, -32($fp)


lw $t0, -32($fp)
sw $t0, -28($fp)


lw $a0, -16($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

lw $t0, -16($fp)
sw $t0, -12($fp)


lw $t0, -28($fp)
sw $t0, -16($fp)


lw $t0, -20($fp)
addi $t0, $t0, 1
sw $t0, -20($fp)


j  iamlabel0


iamlabel2:


li $t0, 0
add $sp, 36
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


lw $t0, -12($fp)
lw $t1, -16($fp)
add $t0, $t0, $t1
sw $t0, -36($fp)


lw $t0, -36($fp)
sw $t0, -28($fp)


lw $a0, -16($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

lw $t0, -16($fp)
sw $t0, -12($fp)


lw $t0, -28($fp)
sw $t0, -16($fp)


lw $t0, -20($fp)
addi $t0, $t0, 1
sw $t0, -20($fp)


