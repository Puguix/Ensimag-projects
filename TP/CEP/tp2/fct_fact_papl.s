/*
uint32_t fact_papl(uint32_t n)
{
    if (n <= 1) {
        return 1;
    } else {
        uint64_t tmp = n*fact_papl(n-1);
        if ((tmp >> 32) > 0)
            erreur_fact(n);
        return (uint32_t)tmp;
    }
}
*/

    .text
    .globl fact_papl
    /* uint32_t fact_papl(uint32_t n) */
/* DEBUT DU CONTEXTE
fonction :
     fact_papl  : non feuille
contexte :
     n      : registre a0; pile *(sp+4)
     tmp      : registre t0/t1
     ra               : pile *(sp+0)
 */
fact_papl:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)
fact_papl_fin_prologue:
    addi t2, zero, 1
    bgt a0, t2, else
    addi a0, zero, 1
    j fact_papl_debut_epilogue

else:
    addi a0, a0, -1
    jal fact_papl
    lw t2, 0(sp)
    mul t0, t2, a0
    mulh t1, t2, a0
    bgt t1, zero, if
    mv a0, t0
    j fact_papl_debut_epilogue

if:
    mv a0, t2
    jal erreur_fact

fact_papl_debut_epilogue:
    lw ra, 4(sp)
    addi sp, sp, 8
    ret
