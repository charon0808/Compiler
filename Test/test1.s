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


addi $sp, $sp, -8


sw $ra, -4($fp)
jal read
lw $ra, -4($fp)
sw $v0, -12($fp)


lw $t0, -12($fp)
li $t1, 0
bgt $t0, $t1, iamlabel0


lw $t0, -12($fp)
li $t1, 0
blt $t0, $t1, iamlabel3


li $a0, 0
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


j  iamlabel5


iamlabel3:


li $t0, 0
addi $t0, $t0, -1
sw $t0, -16($fp)


lw $a0, -16($fp)
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


iamlabel5:


j  iamlabel2


iamlabel0:


li $a0, 1
sw $ra, -4($fp)
jal write
lw $ra, -4($fp)


iamlabel2:


li $t0, 0
add $sp, 16
lw $ra, -4($sp)
lw $fp, -8($sp)
move $v0, $t0
jr $ra


