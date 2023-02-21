#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern uint32_t mult_egypt(void);
static uint32_t mult_c(void);

uint32_t x, y;

static uint32_t mult_c(void)
{
   return x * y;
}

static void test(uint32_t xi, uint32_t yi)
{
   printf("Multiplication de %" PRIu32 " par %" PRIu32 ":\n", xi, yi);
   x = xi;
   y = yi;
   printf("Résultat attendu : %" PRIu32 "\n", mult_c());
   x = xi;
   y = yi;
   printf("Résultat de mult_egypt: %" PRIu32 "\n\n", mult_egypt());
}

static uint32_t acq(const char *nb)
{
   /* On réserve 16 caractères pour les saisies de chaines.
    * Même si on pourrait descendre à 11, car un nombre de 32bits
    * tient même sur 10 symboles décimaux + \0 */
   char tampon[16];

   printf("Multiplication non-signée : Entrez le %s opérande\n", nb);
   fgets(tampon, 16, stdin);
   return strtoul(tampon, NULL, 0);
}

int main(void)
{
   printf("Test interactif\n");
   uint32_t xi, yi;
   xi = acq("premier");
   yi = acq("deuxième");
   test(xi, yi);

   printf("Tests supplémentaires\n");
   test(5, 16);
   test(20, 54);

   return 0;
}
