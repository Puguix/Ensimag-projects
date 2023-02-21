/*
void tri_nain(int32_t tab[], uint32_t taille)
{
    uint32_t i = 0;
    while(i < taille - 1) {
        if (tab[i] > tab[i+1]) {
            int32_t tmp = tab[i];
            tab[i] = tab[i+1];
            tab[i + 1] = tmp;
            if (i > 0) {
                i = i - 1;
            }
        } else {
            i = i + 1;
        }
    }
}
*/

    .text
    .globl tri_nain_opt
/* Version du tri optimisée sans respecter la contrainte de la traduction
 * systématique pour les accès mémoire (et le calcul de leurs adresses)
   Complétez le contexte ci-dessous en indiquant les registres qui contiendront
   des variables temporaires.  */
/* DEBUT DU CONTEXTE
fonction :
     tri_nain_opt  : feuille
contexte :
     tab      : registre a0
     taille      : registre a1
     i      : registre t1
     tmp    :  registre t3
 */
tri_nain_opt:
    li t1, 0
tri_nain_opt_fin_prologue:
    addi t0, a1, -1
    bge t1, t0, tri_nain_opt_debut_epilogue
    
    /* *tab[i+1] -> t2, tab[i] -> t5 tab[i+1] -> t6*/
    slli t2, t1, 2
    add t2, a0 ,t2
    lw t5, 0(t2)
    addi t2, t2, 4
    lw t6, 0(t2)

    ble t5, t6, else
    addi t3, t5, 0
    sw t6, 0(t0)
    sw t3, 0(t4)
    ble t1, zero, i_neg
    addi t1, t1, -1

i_neg:
    j tri_nain_opt_fin_prologue
    
else:
    addi t1, t1, 1
    j tri_nain_opt_fin_prologue
tri_nain_opt_debut_epilogue:
    ret
