#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern uint32_t res;
extern void sommeMem(void);

int main(void)
{
   res = 0xdeadbeef;
   sommeMem();
   printf("SommeMem(1 .. 10)  = %" PRIu32 "\n", res);
   return 0;
}
