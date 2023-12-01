/*
uint32_t age(uint32_t annee_naissance)
{
    uint32_t age;
    age = 2022 - annee_naissance;
    return age;
}
*/

    .text
    .globl age
    /* uint32_t age(uint32_t annee_naissance) */
/* DEBUT DU CONTEXTE
  Fonction :
    age : feuille
  Contexte imposé :
    annee_naissance  : registre a0
    uint32_t age     : pile *(sp+0)
*/
age:
/* A compléter */
  addi sp, sp, -4
age_fin_prologue:
  li t0, 2022
  sub t0, t0, a0
  sw t0, 0(sp)
  mv a0, t0
age_debut_epilogue:
  addi sp, sp, 4
    ret
