#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier unsigned. */
    int32_t au_cas_ou = atoi(argv[1]);
    if (au_cas_ou < 1)
    {
        fprintf(stderr, " on a dit \"strictement positif\", le nombre! Pas %d...\n", au_cas_ou);
        exit(EXIT_FAILURE);
        /* Tiens et si ca tient pas sur 32 bits? A voir... */
    }
    uint32_t nombre = (uint32_t)au_cas_ou;

    for (uint32_t i = 1; i < au_cas_ou; i++)
    {
        if (au_cas_ou % i == 0)
        {
            printf("%i est un diviseur de %i \n", i, au_cas_ou);
        };
    }

    return EXIT_SUCCESS;
}
