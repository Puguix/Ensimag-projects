#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern uint32_t somme(void);

int main(void)
{
   printf("Somme(1 .. 10)  = %" PRIu32 "\n", somme());
   return 0;
}
