/*
uint32_t fact(uint32_t n)
{
    if (n <= 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}
*/

    .text
    .globl fact
    /* uint32_t fact(uint32_t n) */
/* DEBUT DU CONTEXTE
fonction :
     fact  : non feuille
contexte :
     n      : registre a0; pile *(sp+0)
     ra     : pile *(sp+4)
 */
fact:
/* A compléter */
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)
fact_fin_prologue:
    li t0, 1
    ble a0, t0, else
    sub a0, a0, t0
    jal fact
    lw a1, 0(sp)
    mul a0, a0, a1
    j fact_debut_epilogue
else:
    mv a0, t0
fact_debut_epilogue:
    lw ra, 4(sp)
    addi sp, sp, 8
    ret
