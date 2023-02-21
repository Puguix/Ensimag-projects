#include "AOD.h"

#include <math.h>
#include <stdio.h>

#include "characters_to_base.h"
#include "inttypes.h"

#define min(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define max_num ~(0)

long edit_distance_NW_iteratif_direct(char *A, size_t lengthA, char *B,
                                      size_t lengthB) {
    fprintf(stderr, "Iteratif\n");
    _init_base_match();
    char *X;
    char *Y;
    size_t M;
    size_t N;
    if (lengthA >= lengthB) {
        X = A;
        M = lengthA;
        Y = B;
        N = lengthB;
    } else {
        X = B;
        M = lengthB;
        Y = A;
        N = lengthA;
    }
    long **phi = alloc_tab(M, N);

    for (uint64_t j = N - 1; j != max_num; j--) {
        phi[M][j] = 2 * isBase(Y[j]) + phi[M][j + 1];
    }

    for (uint64_t i = M - 1; i != max_num; i--) {
        phi[i][N] = 2 * isBase(X[i]) + phi[i + 1][N];

        for (uint64_t j = N - 1; j != max_num; j--) {

            if (!isBase(X[i]) || !isBase(Y[j])) {
                uint64_t m1 = !isBase(X[i]) ? phi[i + 1][j] : max_num;
                uint64_t m2 = !isBase(Y[j]) ? phi[i][j + 1] : max_num;
                phi[i][j] = m1 < m2 ? m1 : m2;
            } else {
                uint64_t a = ((isUnknownBase(X[i])) || (CharToBase(X[i]) != CharToBase(Y[j])) ? 1 : 0) + phi[i + 1][j + 1];
                uint64_t b = 2 + phi[i + 1][j];
                uint64_t c = 2 + phi[i][j + 1];

                uint64_t m3 = min(a, b, c);

                phi[i][j] = m3;
            }
        }
    }

    long res = phi[0][0];
    free_tab(phi, M);

    return res;
}
// Demander par mail si L peut intervenir dans un algo cache aware
long edit_distance_NW_cache_aware(char *A, size_t lengthA, char *B, size_t lengthB, size_t Z) {
    _init_base_match();

    char *X;
    char *Y;
    size_t M;
    size_t N;

    if (lengthA >= lengthB) {
        X = A;
        M = lengthA;
        Y = B;
        N = lengthB;
    } else {
        X = B;
        M = lengthB;
        Y = A;
        N = lengthA;
    }
    long **phi = alloc_tab(M, N);

    int64_t K = sqrt(Z);
    fprintf(stderr, "Cache Aware K = %ld\n", K);

    for (int64_t I = M; I >= 0; I -= K) {
        int64_t i_end = I - K >= 0 ? I - K : 0;

        for (int64_t J = N; J >= 0; J -= K) {
            int64_t j_end = J - K >= 0 ? J - K : 0;

            for (int64_t i = I; i >= i_end; --i) {
                for (int64_t j = J; j >= j_end; --j) {
                    if (i == M) {
                        if (j == N) {
                            phi[i][j] = 0;
                        } else {
                            phi[i][j] = 2 * isBase(Y[j]) + phi[i][j + 1];
                        }
                    } else if (j == N) {
                        phi[i][j] = 2 * isBase(X[i]) + phi[i + 1][j];
                    } else if (!isBase(X[i]) || !isBase(Y[j])) {
                        uint64_t m1 = !isBase(X[i]) ? phi[i + 1][j] : max_num;
                        uint64_t m2 = !isBase(Y[j]) ? phi[i][j + 1] : max_num;
                        phi[i][j] = m1 < m2 ? m1 : m2;
                    } else {
                        uint64_t a = ((isUnknownBase(X[i])) || (CharToBase(X[i]) != CharToBase(Y[j])) ? 1 : 0) + phi[i + 1][j + 1];
                        uint64_t b = 2 + phi[i + 1][j];
                        uint64_t c = 2 + phi[i][j + 1];

                        uint64_t m3 = min(a, b, c);

                        phi[i][j] = m3;
                    }
                }
            }
        }
    }

    long res = phi[0][0];
    free_tab(phi, M);

    return res;
}

void NW_cache_oblivious_rec(context *ctx, long **phi, int16_t seuil, int64_t begin_i, int64_t end_i, int64_t begin_j, int64_t end_j) {
    int64_t n_i = begin_i - end_i;
    int64_t n_j = begin_j - end_j;
    if (n_i <= seuil && n_j <= seuil) {
        // fprintf(stderr, "ni = %ld, nj = %ld", n_i, n_j);
        for (int64_t i = begin_i; i >= end_i; i--) {
            for (int64_t j = begin_j; j >= end_j; j--) {
                // bords
                if (i == ctx->M) {
                    if (j == ctx->N) {
                        phi[i][j] = 0;
                    } else {
                        phi[i][j] = 2 * isBase(ctx->Y[j]) + phi[i][j + 1];
                    }
                } else if (j == ctx->N) {
                    phi[i][j] = 2 * isBase(ctx->X[i]) + phi[i + 1][j];
                } else {
                    if (!isBase(ctx->X[i]) || !isBase(ctx->Y[j])) {
                        uint64_t m1 = !isBase(ctx->X[i]) ? phi[i + 1][j] : max_num;
                        uint64_t m2 = !isBase(ctx->Y[j]) ? phi[i][j + 1] : max_num;
                        phi[i][j] = m1 < m2 ? m1 : m2;
                    } else {
                        uint64_t a = ((isUnknownBase(ctx->X[i])) || (CharToBase(ctx->X[i]) != CharToBase(ctx->Y[j])) ? 1 : 0) + phi[i + 1][j + 1];
                        uint64_t b = 2 + phi[i + 1][j];
                        uint64_t c = 2 + phi[i][j + 1];

                        uint64_t m3 = min(a, b, c);

                        phi[i][j] = m3;
                    }
                }
            }
        }
    } else {
        int64_t mid_i = (begin_i + end_i) / 2;
        int64_t mid_j = (begin_j + end_j) / 2;
        NW_cache_oblivious_rec(ctx, phi, seuil, begin_i, mid_i, begin_j, mid_j);
        NW_cache_oblivious_rec(ctx, phi, seuil, mid_i + 1, end_i, begin_j, mid_j);
        NW_cache_oblivious_rec(ctx, phi, seuil, begin_i, mid_i, mid_j + 1, end_j);
        NW_cache_oblivious_rec(ctx, phi, seuil, mid_i + 1, end_i, mid_j + 1, end_j);
    }
}

long edit_distance_NW_cache_oblivious(uint16_t seuil, char *A, size_t lengthA,
                                      char *B, size_t lengthB) {
    fprintf(stderr, "CO ===========================\n");
    _init_base_match();
    context ctx;
    if (lengthA >= lengthB) {
        ctx.X = A;
        ctx.M = lengthA;
        ctx.Y = B;
        ctx.N = lengthB;
    } else {
        ctx.X = B;
        ctx.M = lengthB;
        ctx.Y = A;
        ctx.N = lengthA;
    }
    long **phi = alloc_tab(ctx.M, ctx.N);

    NW_cache_oblivious_rec(&ctx, phi, seuil, ctx.M, 0, ctx.N, 0);

    long res = phi[0][0];
    free_tab(phi, ctx.M);

    return res;
}