/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <stdint.h>
#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

unsigned int puiss2(unsigned long size)
{
    unsigned int p = 0;
    size = size - 1; // allocation start in 0
    while (size)
    { // get the largest bit
        p++;
        size >>= 1;
    }
    if (size > (1 << p))
        p++;
    return p;
}

void *
emalloc_medium(unsigned long size)
{
    assert(size < LARGEALLOC);
    assert(size > SMALLALLOC);

    unsigned int indice_taille = puiss2(size + 32);

    /* cas où un bloc est disponible */
    if (arena.TZL[indice_taille] != NULL)
    {
        /*On recupère le bloc et on met son suivant à sa place*/
        void *ptrChunk = arena.TZL[indice_taille];
        arena.TZL[indice_taille] = *(void**)ptrChunk;
        
        return mark_memarea_and_get_user_ptr(ptrChunk, 1 << indice_taille, MEDIUM_KIND);
    }

    /* cas où faut découper un bloc plus gros */

    /*  On cherche le plus petit bloc disponible 
        S'il n'y en a pas on realloc
    */
    unsigned int indice = indice_taille;
    while (arena.TZL[indice] == NULL)
    {
        indice++;
        if (indice == (FIRST_ALLOC_MEDIUM_EXPOSANT + arena.medium_next_exponant))
        {
            mem_realloc_medium();
            break;
        }
    }
    void **bloc = arena.TZL[indice];
    //on retire bloc de la liste (car bloc va etre découpé!)
    arena.TZL[indice] = *bloc;
    void **buddy = NULL;
    /* on découpe le bloc et son compagnon jusqu'à ce qu'il ait la bonne taille*/
    while (indice-- > indice_taille)
    {
        /* Calcul du buddy avec le xor puis on fait pointé buddy vers 0x0*/
        buddy = (void**) ((unsigned long)bloc ^ (1 << indice));
        *buddy = NULL;
        arena.TZL[indice] = (void *)buddy;
    }

    return mark_memarea_and_get_user_ptr((void *)bloc, 1 << indice_taille, MEDIUM_KIND);
}

void efree_medium(Alloc a)
{   
    /*
    Au moment du free les deux sont forcéments dans la même liste

    C'est au moment de la fusion qu'ils peuvent être ailleurs
    */
    /*Il est super dangereux d'utiliser un pointeur ici. Comme ça on force le type casting plus loin
    
    En effet, c'est possible que le buddy soit en cours d'utilisation
    */
    uint64_t buddy_adr = ((unsigned long)(a.ptr) ^ a.size);

    unsigned long indice = puiss2(a.size);

    /* Recherche dans la liste chainée du buddy */
    void **arenaPtr = arena.TZL[indice];
    void **current = (void**) &arenaPtr;

    while(current != NULL && *current != (void**) buddy_adr) {
        current = *current;
    }
    if(current != NULL) {
        if(arena.TZL[indice] == (void*) buddy_adr) {
            arena.TZL[indice] = *(void**)buddy_adr;
        }
        else {
            *current = (void**)*((void**)*current);
        }
        a.size *= 2;
        /* on garde le pointeur du bloc de gauche pour être aligné n*/
        a.ptr = a.ptr < (void*) buddy_adr ? a.ptr: (void*) buddy_adr;
        efree_medium(a);
    }
    else {
        void **ptr = (void**) a.ptr;
        *ptr = arena.TZL[indice];
        arena.TZL[indice] = ptr;
    }    
    /* Le buddy n'est pas dans la liste c'est qu'il est déjà utilisé

    La propriété de l'algo est de toujours avoir le buddy dans la liste de la taille de ce qu'on cherche a merge
    */
}
