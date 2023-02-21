#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{

    int lettre;
    do
    {
        lettre = getc(stdin);
    } while (isupper(lettre) == 0);

    return EXIT_SUCCESS;
}
