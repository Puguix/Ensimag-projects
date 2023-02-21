/*
uint32_t somme(void)
{
    uint32_t i;
    uint32_t res = 0;
    for (i = 1; i <= 10; i++) {
        res = res + i;
    }
    return res;
}
*/
    .text
    .globl somme
/* DEBUT DU CONTEXTE
fonction :
     somme  : feuille
contexte :
     i : registre t0
     res : registre a0
 */
somme:
somme_fin_prologue:
/* A compléter */
    li t0, 0x1
    li a0, 0x0
    li t2, 0xA
for:
    bgt t0, t2, somme_debut_epilogue 
    add a0, a0, t0
    addi t0, t0, 1
    j for
somme_debut_epilogue:
    ret
