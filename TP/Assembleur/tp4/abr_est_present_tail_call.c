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
// renvoie vrai ssi la valeur est présente dans l'arbre
bool abr_est_present_tail_call(uint32_t, struct noeud_t *);

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

// teste la presence de valeurs dans l'arbre
void test_presence(struct noeud_t *abr)
{
   for (uint32_t i = 0; i < 15; i++) {
      printf("abr_est_present_tail_call(%" PRIu32 ", abr) ? : %s\n", i, abr_est_present_tail_call(i, abr) ? "oui" : "non");
   }
   puts("");
}


int main(void)
{
   // deux arbres, un vide et un plein
   struct noeud_t *abr_vide, *abr_ex;

   //  cree l'arbre de l'enonce
   abr_ex = abr_enonce();
   // teste la presence de valeur dans cet arbre
   printf("Test pour l'arbre de l'énoncé:");
   test_presence(abr_ex);

   // cree un arbre vide
   abr_vide = NULL;
   // teste la presence de valeurs dans cet arbre
   printf("Test pour l'arbre vide:");
   test_presence(abr_vide);

   return 0;
}
