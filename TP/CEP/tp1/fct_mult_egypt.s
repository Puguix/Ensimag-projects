    .text
/*
uina02_t x, y;

uina02_t mult_egypt(void)
{
    uina02_t res = 0;
    while (y != 0) {
        if (y % 2 == 1) {
            res = res + x;
        }
        x = x << 1;
        y = y >> 1;
    }
    return res;
}
*/
    .globl mult_egypt
/* Attention, res est une variable locale que l'on mettra dans a0 */
/* DEBUT DU CONTEXTE
fonction :
     mult_egypt  : feuille
contexte :
     x      : mémoire allouée par mult_egypt.c
     y      : mémoire allouée par mult_egypt.c
     res    : registre a0
 */
mult_egypt:
mult_egypt_fin_prologue:
/* A compléter */
    lw t3, x
    li a0, 0
    lw t1, y
while:
    beqz t1, mult_egypt_debut_epilogue
    andi t2, t1, 0x001
    bnez t2, if
    j fin_while
if:
    add a0, a0, t3
    j fin_while
fin_while:
    srli t1, t1, 1
    slli t3, t3, 1
    j while
mult_egypt_debut_epilogue:
    ret
    
    .data
.comm x, 4
.comm y, 4