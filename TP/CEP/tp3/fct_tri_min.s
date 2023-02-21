/*
void tri_min(int32_t tab[], uint32_t taille)
{
    uint32_t i, j, ix_min;
    int32_t tmp;
    for (i = 0; i < taille - 1; i++) {
        for (ix_min = i, j = i + 1; j < taille; j++) {
            if (tab[j] < tab[ix_min]) {
                ix_min = j;
            }
        }
        tmp = tab[i];
        tab[i] = tab[ix_min];
        tab[ix_min] = tmp;
    }
}
#ENTREE 23
*/
    .text
    .globl tri_min
/* void tri_min(int32_t tab[], uint32_t taille) */
/* DEBUT DU CONTEXTE
fonction :
     tri_min  : feuille
contexte :
     tab      : registre a0
     taille      : registre a1
     i : registre t0
     j : registre t1
     ix_min : registre t2
     tmp : registre t3
     
 */
tri_min:
tri_min_fin_prologue:
    li t0, 0
gros_for:
    bge t0, a1, tri_min_debut_epilogue
    addi t2, t0, 0
    addi t1, t0, 1
petit_for:
    bge t1, a1, fin_gros_for
    slli t5, t1, 2
    add t5, a0 ,t5
    lw t5, 0(t5)
    slli t6, t2, 2
    add t6, a0, t6
    lw t6, 0(t6)
    blt t5, t6, if
    addi t1, t1, 1
    j petit_for
if:
    addi t2, t1, 0
    addi t1, t1, 1
    j petit_for
fin_gros_for:
    slli t5, t0, 2
    add t5, a0 ,t5
    lw t3, 0(t5)

    slli t6, t2, 2
    add t6, a0 ,t6
    lw t4, 0(t6)
    sw t4, 0(t5)

    sw t3, 0(t6)
    addi t0, t0, 1
    j gros_for
tri_min_debut_epilogue:
    ret

