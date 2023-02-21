#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t fact(uint32_t);

int main()
{
   char tampon[16];
   printf("Entrez l'entier non signé à utiliser en entrée de fact \n");
   fgets(tampon, 16, stdin);
   uint32_t n = strtoul(tampon, NULL, 0);
   printf("Fact(%" PRIu32 ") = %" PRIu32 "\n", n, fact(n));
   return 0;
}
