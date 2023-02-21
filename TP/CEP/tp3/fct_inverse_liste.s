/*
void inverse_liste(struct cellule_t **l)
{
   struct cellule_t *res, *suiv;
   res = NULL;
   while (*l != NULL) {
       suiv = (*l)->suiv;
       (*l)->suiv = res;
       res = *l;
       *l = suiv;
   }
   *l = res;
}
*/
    .text
    .globl inverse_liste
/* void inverse_liste(struct cellule_t **l) */
/* DEBUT DU CONTEXTE
fonction :
     inverse_liste  : feuille
contexte :
     l      : registre a0
     res    : registre t0
     suiv   : registre t1
 */

 inverse_liste:
    li t0, 0 
inverse_liste_fin_prologue:
    lw t2, 0(a0)
    beqz t2, fin
    lw t3, 0(a0)
    lw t1, 4(t3)
    sw t0, 4(t3)
    lw t0, 0(a0)
    sw t1, 0(a0)
    j inverse_liste_fin_prologue
fin:
    sw t0, 0(a0)
inverse_liste_debut_epilogue:
    ret
