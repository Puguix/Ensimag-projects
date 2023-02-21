#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#define TAILLE 10000
#define STR_M(s) #s
#define STR(s) STR_M(s)

int32_t tab[TAILLE];
int32_t ref[TAILLE];

void tri_nain(int32_t[], uint32_t);
void tri_nain_opt(int32_t[], uint32_t);
void tri_nain_superopt(int32_t[], uint32_t);

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

/* Adresse contenant une horloge temps-réel (rtc) */
#define CLINT_TIMER   0x0200bff8
static uint64_t maintenant(void)
{
   return *(volatile uint64_t *)CLINT_TIMER;
}


int main(void)
{
   printf("Test de performance sur un tableau de grande taille (" STR(TAILLE) ")\n");
   uint64_t qt, dt, odt, sdt; /* qsort time, dwarf sort time, optimized dt */

   uint32_t taille = TAILLE;
   srandom(0xbaffe);
   init_tabs(tab, ref, taille);
   // Nain de base
   dt = maintenant();
   tri_nain(tab, taille);
   dt = maintenant() - dt;
   // Nain optimisé
   memcpy(tab, ref, sizeof(int32_t) * taille);
   odt = maintenant();
   tri_nain_opt(tab, taille);
   odt = maintenant() - odt;
   // Nain super-optimisé
   memcpy(tab, ref, sizeof(int32_t) * taille);
   sdt = maintenant();
   tri_nain_superopt(tab, taille);
   sdt = maintenant() - sdt;
   // Tri de référence (quicksort)
   qt = maintenant();
   qsort(ref, taille, sizeof(int32_t), comp);
   qt = maintenant() - qt;
   if (memcmp(ref, tab, sizeof(int32_t) * taille) != 0) {
      printf("Erreur : le super-nain a mal trié un tableau (sale bête !)\n");
      exit(1);
   }
   printf("Tri de reference :              %" PRIu32 " nsec.\n", (uint32_t)qt);
   printf("Tri par le nain :               %" PRIu32 " nsec.\n", (uint32_t)dt);
   printf("Tri par le nain optimisé:       %" PRIu32 " nsec.\n", (uint32_t)odt);
   printf("Tri par le nain super-optimisé: %" PRIu32 " nsec.\n", (uint32_t)sdt);
   return 0;
}
