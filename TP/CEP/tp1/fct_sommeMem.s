/*
uint32_t res;

uint32_t sommeMem(void)
{
    uint32_t i;
    res = 0;
    for (i = 1; i <= 10; i++) {
        res = res + i;
    }
    return res;
}
*/

    .globl sommeMem
/* DEBUT DU CONTEXTE
fonction :
     sommeMem  : feuille
contexte :
     i      : registre t0
     res    : mémoire allouée par registre.c
 */
sommeMem:
sommeMem_fin_prologue:
/* A compléter */
    li t0, 0x1
    li a0, 0x0
    li t2, 0xA
    sw a0, res, t1
for:
    bgt t0, t2, sommeMem_debut_epilogue
    lw a0, res
    add a0, a0, t0
    addi t0, t0, 1
    sw a0, res, t1
    j for
sommeMem_debut_epilogue:
    ret

    .data
.comm res, 4
/* uint32_t res;
 la variable globale res étant définie dans ce fichier, il est nécessaire de
 la définir dans la section .data du programme assembleur : par exemple, avec
 la directive .comm vu qu'elle n'est pas initialisée
*/
