#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

extern void inverse_chaine(char *, uint32_t);

uint32_t taille_chaine(const char *chaine)
{
    uint32_t taille=0;
    while (chaine[taille] != '\0'){
        taille++;
    }
    return taille;
}

int main(void)
{
   char *chaines[] = { "Ensimag", "", "a", "ab", "abc", "abcd", "abcde", NULL };
   for (int32_t i = 0; chaines[i]; i++) {
      printf("Chaine : \"%s\"\n", chaines[i]);
      uint32_t taille = taille_chaine(chaines[i]);
      char *inv_chaine = malloc(taille + 1);
      strcpy(inv_chaine, chaines[i]);
      inverse_chaine(inv_chaine, taille);
      printf("Chaine inversee : \"%s\"\n", inv_chaine);
      puts("");
   }
   return 0;
}
