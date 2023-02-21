#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Déclaration de la fonction mult définie dans fct_mult.s
extern uint32_t mult(uint32_t a, uint32_t x);
// Déclaration de la fonction affine définie dans fct_affine.s
extern uint32_t affine(uint32_t a, uint32_t b, uint32_t x);
static uint32_t acq(const char *nb)
{
   char tampon[16];
   printf("Fonction affine : Entrez le %s opérande\n", nb);
   fgets(tampon, 16, stdin);
   return strtoul(tampon, NULL, 0);
}

uint32_t affine_c(uint32_t a, uint32_t b, uint32_t x)
{
   return mult(x, a) + b;
}

int main()
{
   uint32_t a, b, x;
   a = acq("premier");
   b = acq("deuxième");
   x = acq("troisième");
   uint32_t res_as = affine(a, b, x);
   printf("affine(%" PRIu32 ",%" PRIu32 ",%" PRIu32 ") calculé en assembleur: %" PRIu32 " et en C: %" PRIu32 "\n", a, b, x, res_as, affine_c(a, b, x));
   return 0;
}
