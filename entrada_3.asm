add x2, x0, x1
sll x1, x2, x2
or x2, x2, x1
andi x2, x1, 16
addi x3, x2, -243
add x2, x0, x1
add x6, x0, x2
sub x3, x6, x2
xor x4, x2, x3
srl x0, x2, x2
lw x1, 8(x2)
sw x2, 6(x3)
beq x2, x1, 16