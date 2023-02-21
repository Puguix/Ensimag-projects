/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

void *
emalloc_small(unsigned long size)
{
    /* on test si la liste est vide */
    if (arena.chunkpool != NULL)
    {
        void *ptr = arena.chunkpool;
        arena.chunkpool = *(void**)ptr;
        return mark_memarea_and_get_user_ptr(ptr, CHUNKSIZE, SMALL_KIND);
    }

    /* si la liste est vide, on crée les chunks et on rappelle la fonction */
    unsigned long blockSize = mem_realloc_small();
    void **ptr = arena.chunkpool;
    for (int i = 0; i < blockSize / CHUNKSIZE; i++)
    {
        *ptr = (void*)ptr + CHUNKSIZE;
        ptr = *ptr;
    }

    return emalloc_small(size);
}

void efree_small(Alloc a)
{
    /* on récup la tete de liste et la place à la suite de a, qui passe en tete de liste */
    void *head = arena.chunkpool;
    void **ptrNextChunk = a.ptr;
    *ptrNextChunk = head;
    arena.chunkpool = a.ptr;
}
