/*
// Description en C de la fonction à traduire en langage d'assemblage
uint32_t pgcd(void)
{
    uint32_t i=a;
    uint32_t j=b;
    while (i != j) {
        if (i < j) {
            j = j - i;
        } else {
            i = i - j;
        }
    }
    return i;
}
*/
    .text
    .globl pgcd
/*
  On propose de mettre les variables i et j respectivement dans les
  registres t0 (soit x5) et t1 (soit x6)

  La valeur de retour devra être mise dans le registre a0.
*/

/* DEBUT DU CONTEXTE
  Fonction :
    pgcd : feuille
  Contexte :
    a  : mémoire, allouée par pgcd.c
    b  : mémoire, allouée par pgcd.c
    i  : registre t0
    j  : registre t1
*/

pgcd:
pgcd_fin_prologue:
    /* uint32_t i=a; */
    lw   t0, a
    /* uint32_t j=b; */
    lw   t1, b
    /* while (i != j) {  */
while:
    beq  t0, t1, fin /* Saut à fin si i == j */
    /* if (i < j) {  */
    sltu t2, t0, t1 /* Le registre t2 est utilisé pour stocker le résultat du test i < j */
    beqz t2, else /* pseudo-instruction, on aurait pu utiliser beq t2, zero, else */
    /* j = j - i;  */
    sub  t1, t1, t0
    j    fin_if
    /* } else {  */
else:
    /* i = i - j;  */
    sub  t0, t0, t1
    /*  }  */
fin_if:
    /*  }  */
    j    while
    /* return i; */
fin:
    /* Par convention, le registre a0 (soit x10) contient la valeur de retour.*/
    mv   a0, t0 /* pseudo-instruction équivalente à add a0, t0, zero ou addi a0, t0, 0, ... */
    /* Par convention encore, l'adresse de retour dans la fonction appelante est
     * stockée dans le registre ra (soit x1) */
pgcd_debut_epilogue:
    /* ret est une pseudo-instruction, on aurait pu utiliser jr ra */
    ret
