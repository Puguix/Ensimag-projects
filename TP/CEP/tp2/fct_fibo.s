/*
uint32_t fibo(uint32_t n);
{
    uint32_t fibo_temp;
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
	fibo_temp = fibo(n - 1);
        return fibo_temp + fibo(n - 2);
    }
}
*/
    .text
    /* uint32_t fibo(uint32_t n) */
    .globl fibo
/*
  fibo : fonction non feuille
  => besoin de sauvegarder :
   - la place pour les paramètres des fonctions appelées si supérieur à 8 [notation np du cours, np=0]
   - la variable locale fibo_temp [notation nv du cours, nv=1]
   - le registre ra et le paramètre que l'on doit retrouver au retour [notation nr du cours, nr=2]

   => La fonction doit réserver dans la pile (np+nv+nr)*4 octets
   => Pile + 12
    PILE:
    sp+8 : place de l'adresse de retour (ra) dans la pile
    sp+4 : place pour le registre a0 (paramètre n)
    sp+0 : place pour la variable locale fibo_temp

DEBUT DU CONTEXTE
  Fonction :
    fibo : non feuille
  Contexte :
    ra         : pile *(sp+8)
    n          : registre a0; pile *(sp+4)
    fibo_temp  : pile *(sp+0)
*/

fibo:
    /* on reserve la place nécessaire dans la pile */
    addi sp, sp, -12
    /* on y sauvegarde l'adresse de retour */
    sw   ra, 8(sp)
    /* Et le paramètre n */
    sw   a0, 4(sp)
fibo_fin_prologue:
    /* if (n == 0) */
    bnez a0, elsif
    /* return 0; */
    j    fibo_debut_epilogue
elsif:
    /* else if (n == 1) */
    li   t0, 1
    bne  a0, t0, else
    /* return 1; */
    j    fibo_debut_epilogue
else:
    /* fibo_temp = fibo(n - 1)
       on place n-1 dans a0
    */
    addi a0, a0, -1
    jal  fibo
    /* stocke la valeur retournée dans fibo_temp */
    sw   a0, 0(sp)

    /* restauration du parametre n initial (a0 pu être modifié dans la fonction appelée)*/
    lw   a0, 4(sp)
    /* on appelle maintenant fibo(n - 2) */
    addi a0, a0, -2
    jal  fibo
    /* et on calcule la somme finale en mettant fibo_temp dans t0 */
    lw   t0, 0(sp)
    add  a0, a0, t0
fibo_debut_epilogue:
    lw   ra, 8(sp)  /* on recharge ra avec l'adresse de retour de la pile */
    addi sp, sp, 12 /* on libère la pile */
    ret
