#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern uint8_t res8;
extern uint8_t somme8(void);

int main(void)
{
   res8 = 0xfa;
   printf("Somme8(1 .. 24)  = %" PRIu8 "\n", somme8());
   return 0;
}
