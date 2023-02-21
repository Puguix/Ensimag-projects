#include "cep_platform.h"
.section .text.excp,"ax",@progbits
    .align 2
.globl mon_vecteur

mon_vecteur:
    # Save registers.
    addi  sp, sp, -16 * 4
    sw    ra,  0*4(sp)
    sw    a0,  1*4(sp)
    sw    a1,  2*4(sp)
    sw    a2,  3*4(sp)
    sw    a3,  4*4(sp)
    sw    a4,  5*4(sp)
    sw    a5,  6*4(sp)
    sw    a6,  7*4(sp)
    sw    a7,  8*4(sp)
    sw    t0,  9*4(sp)
    sw    t1, 10*4(sp)
    sw    t2, 11*4(sp)
    sw    t3, 12*4(sp)
    sw    t4, 13*4(sp)
    sw    t5, 14*4(sp)
    sw    t6, 15*4(sp)

    # Invoke the handler.
    csrr    a0, mcause
    li      t1, 0x80000000
    and     t0, a0, t1   # MSB à 1 => interruption
    beqz    t0, pas_interruption
    jal     gestion_interruptions
    j       restaure_registres
 pas_interruption:
    la      a0, message_erreur
    jal     printf
    li      a0, 1
    jal     exit

restaure_registres:
    # Restore registers.
    lw    ra,  0*4(sp)
    lw    a0,  1*4(sp)
    lw    a1,  2*4(sp)
    lw    a2,  3*4(sp)
    lw    a3,  4*4(sp)
    lw    a4,  5*4(sp)
    lw    a5,  6*4(sp)
    lw    a6,  7*4(sp)
    lw    a7,  8*4(sp)
    lw    t0,  9*4(sp)
    lw    t1, 10*4(sp)
    lw    t2, 11*4(sp)
    lw    t3, 12*4(sp)
    lw    t4, 13*4(sp)
    lw    t5, 14*4(sp)
    lw    t6, 15*4(sp)
    addi sp, sp, 16 * 4
    mret

    .data
message_erreur: .string "Exception non gérée, bonjour chez vous!\n"
