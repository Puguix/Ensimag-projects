    .text
/*
uint32_t x, y, res;

uint32_t mult_simple(void)
{
    res = 0;
    while (y != 0) {
        res = res + x;
        y--;
    }
    return res;
}
*/
    .globl mult_simple
/* DEBUT DU CONTEXTE
fonction :
     mult_simple  : feuille
contexte :
     x      : mémoire allouée par mult_simple.c
     y      : mémoire allouée par mult_simple.c
     res    : mémoire allouée par mult_simple.c
 */
mult_simple:
mult_simple_fin_prologue:
/* A compléter */
    lw t0, x
    li a0, 0x0
    lw t1, y
while:
    beqz t1, mult_simple_debut_epilogue
    add a0, a0, t0
    addi t1, t1, 0xffffffff
    j while
mult_simple_debut_epilogue:
    ret


    .data
.comm res, 4
.comm x, 4
.comm y, 4
/* uint32_t res; */
