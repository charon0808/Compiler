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
li $t0, 0
bgt $t0, $t1, iamlabel0
 

lw $t1, -8($fp)
li $t0, 0
blt $t0, $t1, iamlabel3


li $a0, 0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

j  iamlabel5


iamlabel3:


li $t0, 0
addi $t0, $t0, -1
sw $t0, -12($fp)


lw $a0, -12($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

iamlabel5:


j  iamlabel2


iamlabel0:


li $a0, 1
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4

iamlabel2:


li $t0, 0
move $v0, $t0
jr $ra


