/*
bool palin(const char *ch)
{
    uint32_t inf, sup;
    inf = 0;
    sup = strlen(ch) - 1;
    while (inf < sup && ch[inf] == ch[sup]) {
        inf++;
        sup--;
    }
    return inf >= sup;
}
*/
    .text
    .globl palin
    /* bool palin(char *ch) */
/* DEBUT DU CONTEXTE
fonction :
     palin  : non feuille
contexte :
     ch      : registre a0; pile *(sp+4)
     inf : registre t0
     sup : registre t1
     ra               : pile *(sp+0)
 */
palin:
    addi sp, sp, -8
    sw ra, 0(sp)
    sw a0, 4(sp)
palin_fin_prologue:
    jal strlen
    addi t1, a0, -1
    li t0, 0
    lw a0, 4(sp)
while:
    bge t0, t1, palin_debut_epilogue
    add t2, t0, a0
    lw t2, 0(t2)
    add t3, t1, a0
    lw t3, 0(t3)
    beq t2, t3, palin_debut_epilogue
    addi t0, t0, 1
    addi t1, t1, -1
    j while
palin_debut_epilogue:
    li a0, 0
    bge t0, t1, cond_pas_verifiee
    addi a0, a0, 1
cond_pas_verifiee:
    lw ra, 0(sp)
    addi sp, sp, 8
    ret
