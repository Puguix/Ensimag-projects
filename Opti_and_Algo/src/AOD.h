#ifndef _AOD_
#define _AOD_

#include "stdlib.h"
#include <inttypes.h>

typedef struct context {
    char *X;
    char *Y;
    size_t M;
    size_t N;
} context;

long edit_distance_NW_iteratif_direct(char *A, size_t lengthA, char *B, size_t lengthB);

long edit_distance_NW_cache_aware(char *A, size_t lengthA, char *B, size_t lengthB, size_t Z);

//long NW_cache_oblivious_rec(int64_t seuil, int64_t begin_i, int64_t end_i, int64_t begin_j, int64_t end_j);

long edit_distance_NW_cache_oblivious(uint16_t seuil, char *A, size_t lengthA, char *B, size_t lengthB);

//return une matrice de long
static inline long** alloc_tab(size_t dimA, size_t dimB) {
    long** phi = malloc((dimA + 1)* sizeof(long));
    for(uint64_t i = 0; i < dimA + 1; i++) {
        phi[i] = malloc((dimB + 1)* sizeof(long));
    }
    return phi;
}

static inline void free_tab(long** tab, size_t dimA) {
    for(uint64_t i = 0; i < dimA + 1; i++) {
        free(tab[i]);
    }
    free(tab);
}

#endif