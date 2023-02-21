#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

// nombre d'elements dans l'arbre
#define NBR_ELEM 9

// le type d'un noeud de l'arbre
struct noeud_t {
   uint32_t val;                // valeur du noeud
   struct noeud_t *fg;          // fils gauche
   struct noeud_t *fd;          // fils droite
};

// fonction implantée dans le fichier assembleur
// copie les valeurs des noeuds de l'arbre dans un tableau
void abr_vers_tab(struct noeud_t *);

// cree un noeud en allouant l'espace mémoire et en
//   initialisant les champs de la structure
struct noeud_t *cree_noeud(uint32_t val, struct noeud_t *fg, struct noeud_t *fd)
{
   struct noeud_t *res = malloc(sizeof(struct noeud_t));
   res->val = val;
   res->fg = fg;
   res->fd = fd;
   return res;
}

// cree l'ABR donne dans l'enonce
struct noeud_t *abr_enonce(void)
{
   return cree_noeud(8,
                     cree_noeud(3,
                                cree_noeud(1, NULL, NULL),
                                cree_noeud(6,
                                           cree_noeud(4, NULL, NULL),
                                           cree_noeud(7, NULL, NULL))),
                     cree_noeud(10, NULL, cree_noeud(14, cree_noeud(13, NULL, NULL), NULL)));
}

// une fonction d'affichage du tableau
void affiche_tab(uint32_t tab[])
{
   printf("Contenu du tableau : ");
   for (uint8_t i = 0; i < NBR_ELEM; i++) {
      printf("%" PRIu32 " ", tab[i]);
   }
   puts("");
}

// Le mot cle "extern" veut dire que cette variable globale est visible
//   dans le fichier .c, mais qu'elle est allouée « ailleurs ».
// Vous devez l'allouer dans la zone .data du fichier assembleur.
extern uint32_t *ptr;

int main(void)
{
   // deux arbres, un vide et un plein
   struct noeud_t *abr_ex;

   //  cree l'arbre de l'enonce
   abr_ex = abr_enonce();

   // cree un tableau
   uint32_t tab[NBR_ELEM];
   // initialise le ptr sur la premiere case du tableau
   ptr = tab;
   // copie les elements de l'arbre dans le tableau
   abr_vers_tab(abr_ex);
   // affiche le tableau
   affiche_tab(tab);

   return 0;
}
