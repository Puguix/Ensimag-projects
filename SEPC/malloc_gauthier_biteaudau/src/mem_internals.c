/******************************************************
 * Copyright Grégory Mounié 2018-2022                 *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <sys/mman.h>
#include <assert.h>
#include <stdint.h>
#include "mem.h"
#include "mem_internals.h"

unsigned long knuth_mmix_one_round(unsigned long in)
{
    return in * 6364136223846793005UL % 1442695040888963407UL;
}

void *mark_memarea_and_get_user_ptr(void *ptr, unsigned long size, MemKind k)
{
    /* ecriture sur les octets la taille */
    unsigned long long *p = ptr;
    *p++ = size;

    /* ecriture sur les octets du chiffre magique */
    unsigned long magicNumber = knuth_mmix_one_round((unsigned long)ptr);
    magicNumber &= ~(0b11UL);
    magicNumber |= k;

    *p = magicNumber;
    //TODO checker les trucs qui vont bien
    p = (void*)(ptr + size - 16);
    *p++ = magicNumber;

    *p = size;
    
    /* on renvoie l'adresse de la zone utilisable */
    return (void *)(ptr + 16);
}

Alloc mark_check_and_get_alloc(void *ptr)
{
    /* on a un gros bug :( les tailles sont des puissances de deux !*/
    /* on récupère le type de taille */
    unsigned long long *p = (unsigned long long*)ptr - 1;
    unsigned long magicNumberStart = *p;
    MemKind k = magicNumberStart & 0b11;
    /* on récupère la taille */
    p--;
    unsigned long size = *p;
    Alloc a = {
        ptr - 16,
        k,
        size};

    /* on vérifie si le nombre magique correspond*/
    unsigned long magicNumber = knuth_mmix_one_round((unsigned long)(ptr-16));


    assert((magicNumber & ~(0b11UL)) == (magicNumberStart & ~(0b11UL)));

    /* on vérifie le chiffre magique */
    p = (void*)(ptr + size - 32);
    unsigned long magicNumberEnd = *p;
    assert(magicNumberStart == magicNumberEnd);
    
    return a;
}

unsigned long
mem_realloc_small()
{
    assert(arena.chunkpool == 0);
    unsigned long size = (FIRST_ALLOC_SMALL << arena.small_next_exponant);
    arena.chunkpool = mmap(0,
                           size,
                           PROT_READ | PROT_WRITE | PROT_EXEC,
                           MAP_PRIVATE | MAP_ANONYMOUS,
                           -1,
                           0);
    if (arena.chunkpool == MAP_FAILED)
        handle_fatalError("small realloc");
    arena.small_next_exponant++;
    return size;
}

unsigned long
mem_realloc_medium()
{
    uint32_t indice = FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant;
    assert(arena.TZL[indice] == 0);
    unsigned long size = (FIRST_ALLOC_MEDIUM << arena.medium_next_exponant);
    assert(size == (1UL << indice));
    arena.TZL[indice] = mmap(0,
                             size * 2, // twice the size to allign
                             PROT_READ | PROT_WRITE | PROT_EXEC,
                             MAP_PRIVATE | MAP_ANONYMOUS,
                             -1,
                             0);
    if (arena.TZL[indice] == MAP_FAILED)
        handle_fatalError("medium realloc");
    // align allocation to a multiple of the size
    // for buddy algo
    arena.TZL[indice] += (size - (((intptr_t)arena.TZL[indice]) % size));
    arena.medium_next_exponant++;
    return size; // lie on allocation size, but never free
}

// used for test in buddy algo
unsigned int
nb_TZL_entries()
{
    int nb = 0;

    for (int i = 0; i < TZL_SIZE; i++)
        if (arena.TZL[i])
            nb++;

    return nb;
}
