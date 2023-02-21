/*
struct rect_t double_rect(struct rect_t r)
{
    return (struct rect_t){r.x, r.y, r.dx * 2, r.dy * 2};
}
*/
    .text
    .globl double_rect
/*
    Fonction feuille : rien à faire sur la pile, ra non modifié
    Agrégat > 64 en valeur de retour
      => appelante a réservé une place dans sa pile
         et a0 (paramètre implicite) pointe dessus
    Agrégat > 64 en paramètre
      => appelante a réservé une place dans sa pile
         et a1 (et non a0 car réservé pour la valeur de retour) pointe dessus

DEBUT DU CONTEXTE
  Fonction :
    double_rect : feuille
  Contexte :
    r         : pile *(a1)
    résultat  : pile *(a0)
*/
double_rect:
double_rect_fin_prologue:
    lhu  t0, 10(a1)
    lhu  t1,  8(a1)
    lw   t2,  4(a1)
    lw   t3,  0(a1)
    slli t0, t0, 1
    slli t1, t1, 1
    sh   t0, 10(a0)
    sh   t1,  8(a0)
    sw   t2,  4(a0)
    sw   t3,  0(a0)
double_rect_debut_epilogue:
    ret
