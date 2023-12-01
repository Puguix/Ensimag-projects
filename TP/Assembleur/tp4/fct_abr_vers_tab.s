/*
void abr_vers_tab(struct noeud_t *abr)
{
    if (abr != NULL) {
        abr_vers_tab(abr->fg);
        *ptr = abr->val;
        ptr++;
        struct noeud_t *fd = abr->fd;
        free(abr);
        abr_vers_tab(fd);
    }
}
*/

    .text
    .globl abr_vers_tab
/* DEBUT DU CONTEXTE
fonction :
     abr_vers_tab  : non feuille
contexte :
     abr      : registre a0; pile *(sp+4)
     ra         : pile *(sp+0)
     ptr        : memoire allouée par le fichier .s
     fd         : registre t0
 */
abr_vers_tab:
    addi sp, sp, -8
    sw ra, 0(sp)
    sw a0, 4(sp)
abr_vers_tab_fin_prologue:
    beqz a0, abr_vers_tab_debut_epilogue
    lw a0, 4(a0)
    jal abr_vers_tab
    lw a0, 4(sp)
    lw t1, 0(a0)
    lw t2, ptr
    sw t1, 0(t2)
    addi t2, t2, 4
    sw t2, ptr, t3
    lw t0, 8(a0)
    jal free
    mv a0, t0
    jal abr_vers_tab
    j abr_vers_tab_fin_prologue

abr_vers_tab_debut_epilogue:
    lw ra, 0(sp)
    addi sp, sp, 8
    ret

.data
.comm ptr, 4
