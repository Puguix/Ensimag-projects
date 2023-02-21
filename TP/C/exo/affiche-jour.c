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

    /* Convertit l'argument passé par l'utilisateur en entier. */
    int32_t nombre = atoi(argv[1]);

    switch (nombre)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        printf("Le nombre correspond a un jour de la semaine");
        break;

    case 6:
    case 7:
        printf("Le nombre correspond a un jour du week end");
        break;

    default:
        printf("Le nombre doit etre entre 1 et 7");
        break;
    }

    return EXIT_SUCCESS;
}
