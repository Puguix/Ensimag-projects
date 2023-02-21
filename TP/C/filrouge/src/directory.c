#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <contact.h>
#include <hash.h>

struct dir
{
    uint32_t taille;
    uint32_t nb_contact;
    struct Contact **tableau;
};

// test si 2 string sont egaux
bool sont_egaux(char *str1, const char *str2)
{
    bool booleen = true;
    for (size_t i = 0; i < strlen(str1); i++)
    {
        if (str1[i] != str2[i])
        {
            booleen = false;
            break;
        }
    }
    return booleen;
}

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir *dico = malloc(sizeof(struct dir *));
    struct Contact **tableau = malloc(len * sizeof(struct Contact *));
    // on initialise les valeurs du tableau a NULL
    for (uint32_t i = 0; i < len; i++)
    {
        tableau[i] = NULL;
    }
    dico->tableau = tableau;
    dico->taille = len;
    dico->nb_contact = 0;
    return dico;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    // on calcule la clef
    uint32_t clef = hash(name) % dir->taille;

    // on regarde si ya deja quelqu'un du meme nom
    struct Contact *current = dir->tableau[clef];
    while (current != NULL && !sont_egaux(current->nom, name) && (current->suivant) != NULL)
    {
        current = (current->suivant);
    }

    // si effectivement le nom est deja present
    if (current != NULL && sont_egaux(current->nom, name))
    {
        char *ancien_numero = current->numero;
        current->numero = num;
        return ancien_numero; // l'ancien num est un pointeur
    }

    // sinon (current est la derniere personne de la liste)
    else
    {
        // s'il faut rajouter de la capacite au dico
        if (dir->nb_contact + 1 > 0.75 * dir->taille)
        {
            // on créé un nouveau tableau
            struct Contact **tableau = malloc(dir->taille * 2 * sizeof(struct Contact *));
            struct Contact **tmp = dir->tableau;
            dir->tableau = tableau;
            uint32_t taille_tableau = dir->taille;
            dir->taille = taille_tableau * 2;
            dir->nb_contact = 0;
            for (uint32_t i = 0; i < taille_tableau; i++)
            {
                struct Contact *current = tmp[i];
                while (current != NULL)
                {
                    // on rajoute tous les anciens contacts
                    dir_insert(dir, current->nom, current->numero);
                    current = current->suivant;
                }
            }
            // on rajoute le nouveau contact
            dir_insert(dir, name, num);
            free(tmp);
        }
        struct Contact *new = malloc(sizeof(struct Contact));
        new->nom = name;
        new->numero = num;
        new->suivant = NULL;
        dir->nb_contact++;

        // s'il y a personne dans la liste
        if (current == NULL)
        {
            dir->tableau[clef] = new;
        }
        // s'il y a quelqu'un dans la liste
        else
        {
            current->suivant = new;
        }
        return NULL;
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    // on calcule la clef
    uint32_t clef = hash(name) % dir->taille;

    // on regarde si ya deja quelqu'un du meme nom
    struct Contact *current = dir->tableau[clef];
    while (current != NULL && !sont_egaux(current->nom, name) && (current->suivant) != NULL)
    {
        current = (current->suivant);
    }

    // si le nom est deja present, on renvoie son numero
    if (current != NULL && sont_egaux(current->nom, name))
    {
        return current->numero;
    }
    // sinon rien
    return NULL;
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    // on calcule la clef
    uint32_t clef = hash(name) % dir->taille;

    // on regarde si ya deja quelqu'un du meme nom
    struct Contact *current = dir->tableau[clef];
    struct Contact *current_avant = NULL;
    while (current != NULL && !sont_egaux(current->nom, name) && (current->suivant) != NULL)
    {
        current_avant = current;
        current = (current->suivant);
    }

    // si effectivement le nom est present
    if (current != NULL && sont_egaux(current->nom, name))
    {
        // si on peut et qu'il faut enlever de la capacite au dico
        if (dir->taille > 10 && dir->nb_contact - 1 < 0.15 * dir->taille)
        {
            // on créé un nouveau tableau
            uint32_t max = (dir->taille / 2 > 10) ? dir->taille / 2 : 10;
            struct Contact **tableau = malloc(max * sizeof(struct Contact *));
            struct Contact **tmp = dir->tableau;
            dir->tableau = tableau;
            uint32_t taille_tableau = dir->taille;
            dir->taille = max;
            dir->nb_contact = 0;
            for (uint32_t i = 0; i < taille_tableau; i++)
            {
                struct Contact *current = tmp[i];
                while (current != NULL)
                {
                    // on rajoute tous les anciens contacts
                    dir_insert(dir, current->nom, current->numero);
                    current = current->suivant;
                }
            }
            // on supprime le nouveau contact
            dir_delete(dir, name);
            free(tmp);
        }
        else
        {
            // si c'est la premiere personne dans le dico
            if (current_avant == NULL)
            {
                dir->tableau[clef] = current->suivant;
            }

            // sinon
            else
            {
                (current_avant->suivant) = (current->suivant);
            }
            dir->nb_contact--;
        }
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i = 0; i < dir->taille; i++)
    {
        struct Contact *current = dir->tableau[i];
        while (current != NULL)
        {
            // on parcourt tous les contacts et on les libere
            struct Contact *past = current;
            current = current->suivant;
            free(past);
        }
    }
    free(dir->tableau);
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    for (uint32_t i = 0; i < dir->taille; i++)
    {
        struct Contact *current = dir->tableau[i];
        while (current != NULL)
        {
            printf("Nom: %s, numéro: %s \n", current->nom, current->numero);
            current = current->suivant;
        }
    }
}