#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

uint32_t hash(const char *str)
{
    uint32_t res = 5381;
    int i = 0;
    while (str[i] != '\0')
    {
        res = res * 33 + str[i];
        i++;
    }
    return res;
}
