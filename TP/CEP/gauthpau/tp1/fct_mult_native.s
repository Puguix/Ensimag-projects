    .text
/*
uint32_t x, y;

uint32_t mult_native(void)
{
    return x*y;
}
*/
    .globl mult_native
/* DEBUT DU CONTEXTE
fonction :
     mult_native  : feuille
contexte :
     x      : mémoire allouée par mult_native.c
     y      : mémoire allouée par mult_native.c
 */
mult_native:
mult_native_fin_prologue:
/* A compléter */
    lw t0, x
    lw t1, y
    mul a0, t1, t0
mult_native_debut_epilogue:
    ret

    .data
.comm x, 4
.comm y, 4
    
