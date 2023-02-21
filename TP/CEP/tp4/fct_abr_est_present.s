/*
bool abr_est_present(uint32_t val, struct noeud_t *abr)
{
   if (abr == NULL) {
       return false;
   } else if (val == abr->val) {
       return true;
   } else if (val < abr->val) {
       return abr_est_present(val, abr->fg);
   } else {
       return abr_est_present(val, abr->fd);
   }
}
*/

    .text
    .globl abr_est_present
/* DEBUT DU CONTEXTE
fonction :
     abr_est_present  : non feuille
contexte :
     val      : registre a0; pile *(sp+4)
     abr      : registre a1 pile *(sp+8)
     ra       : pile *(sp+0)
 */
abr_est_present:
    addi sp, sp, -12
    sw ra, 0(sp)
    sw a0, 4(sp)
    sw a1, 8(sp)

abr_est_present_fin_prologue:
    beqz a1, abr_est_null 
    lw t0, 0(a1)
    beq t0, a0, val_egal_abr_val
    blt a0, t0, val_inf_abr_val
    j val_sup_abr_val

abr_est_null:
    li a0, 0
    j abr_est_present_debut_epilogue

val_egal_abr_val:
    li a0, 1
    j abr_est_present_debut_epilogue

val_inf_abr_val:
    lw a1, 4(a1)
    jal abr_est_present
    j abr_est_present_debut_epilogue

val_sup_abr_val:
    lw a1, 8(a1)
    jal abr_est_present
    j abr_est_present_debut_epilogue

abr_est_present_debut_epilogue:
    lw ra, 0(sp)
    addi sp, sp, 12
    ret
