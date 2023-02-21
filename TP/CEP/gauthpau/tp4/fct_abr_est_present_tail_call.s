/*
bool abr_est_present_tail_call(uint32_t val, struct noeud_t *abr)
{
   if (abr == NULL) {
       return false;
   } else if (val == abr->val) {
       return true;
   } else if (val < abr->val) {
       return abr_est_present_tail_call(val, abr->fg);
   } else {
       return abr_est_present_tail_call(val, abr->fd);
   }
}
*/
    .text
    .globl abr_est_present_tail_call
/* DEBUT DU CONTEXTE
fonction :
     abr_est_present_tail_call  : feuille
contexte :
     val      : registre a0
     abr      : registre a1
 */
abr_est_present_tail_call:
abr_est_present_tail_call_fin_prologue:
    beqz a1, abr_est_null 
    lw t0, 0(a1)
    beq t0, a0, val_egal_abr_val
    blt a0, t0, val_inf_abr_val
    j val_sup_abr_val

abr_est_null:
    li a0, 0
    j abr_est_present_tail_call_debut_epilogue

val_egal_abr_val:
    li a0, 1
    j abr_est_present_tail_call_debut_epilogue

val_inf_abr_val:
    lw a1, 4(a1)
    j abr_est_present_tail_call

val_sup_abr_val:
    lw a1, 8(a1)
    j abr_est_present_tail_call
abr_est_present_tail_call_debut_epilogue:
    ret
