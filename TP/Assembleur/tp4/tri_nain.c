#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#define TAILLE 2500
#define STR_M(s) #s
#define STR(s) STR_M(s)

int32_t tab[TAILLE];
int32_t ref[TAILLE];

void tri_nain(int32_t[], uint32_t);

static void afficher_tab(int32_t tab[], uint32_t taille)
{
   for (uint32_t i = 0; i < taille; i++) {
      printf("%" PRId32 " ", tab[i]);
   }
   printf("\n");
}

static void init_tabs(int32_t tab[], int32_t ref[], uint32_t taille)
{
   for (uint32_t i = 0; i < taille; i++) {
      tab[i] = (random() % 19) - 9;
   }
   memcpy(ref, tab, sizeof(int32_t) * taille);
}

int comp(const void *a, const void *b)
{
   return (int)(*(int32_t *)a - *(int32_t *)b);
}

static uint32_t acq()
{
   char tampon[16];
   printf("Fonction tri_nain : Entrez la taille du tableau (max = " STR(TAILLE) ")\n");
   fgets(tampon, 16, stdin);
   return strtoul(tampon, NULL, 0);
}


int main(void)
{
   uint32_t taille = acq();
   if (taille > TAILLE) {
      printf("La taille est trop grande, test annulé.\n");
      exit(1);
   }
   printf("Test sur un tableau de taille %" PRIu32 "\n", taille);

   srandom(0xbaffe);
   init_tabs(tab, ref, taille);

   tri_nain(tab, taille);

   if (taille < 26) {
      printf("Tableau initial : ");
      afficher_tab(ref, taille);
      printf("Tableau trie par le nain : ");
      afficher_tab(tab, taille);
   } else {
      printf("Le tableau a une taille > 25, il ne sera pas affiché.\n");
   }

   qsort(ref, taille, sizeof(int32_t), comp);

   if (memcmp(ref, tab, sizeof(int32_t) * taille) != 0) {
      printf("Erreur : le nain a mal trie un tableau (sale bete !)\n");
      exit(1);
   }
   printf("Le tableau est trié, le nain a bien fait son travail.\n");
   return 0;
}
