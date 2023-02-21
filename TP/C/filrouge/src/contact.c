#include <stdint.h>

// Structure de données contact: un nom, un num, le contact suivant si besoin
struct Contact
{
    char *nom;
    char *numero;
    struct Contact *suivant;
};
