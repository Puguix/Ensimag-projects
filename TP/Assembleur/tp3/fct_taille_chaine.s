/*
uint32_t taille_chaine(const char *chaine)
{
    uint32_t taille = 0;
    while (chaine[taille] != '\0') {
        taille++;
    }
    return taille;
}
*/
    .text
    .globl taille_chaine
/* uint32_t taille_chaine(const char *chaine) */
/* DEBUT DU CONTEXTE
fonction :
     taille_chaine  : feuille
contexte :
     taille      : registre t0
     chaine : registre a0
 */

taille_chaine:
taille_chaine_fin_prologue:
    li t0, 0
    lbu t1, 0(a0)
while:
    beqz t1, taille_chaine_debut_epilogue
    addi t0, t0, 1
    add t2, a0, t0
    lbu t1, 0(t2)
    j while
taille_chaine_debut_epilogue:
    mv a0, t0
    ret
