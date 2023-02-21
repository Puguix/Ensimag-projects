/*
  Test du module directory.

  Recherche dans un directory à trois contacts.
 */

#include <stdlib.h>
#include <stdio.h>

#include <directory.h>

int main(void)
{
    struct dir *dir = dir_create(10);
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    dir_insert(dir, "Caporal Ketchup", "0678346533");
    dir_insert(dir, "Sergent Mayo", "06723236533");
    dir_print(dir);

    const char *names[4] = {
        "Colonel Moutarde",
        "Caporal Ketchup",
        "Sergent Mayo",
        "Tartempion"};

    for (size_t id = 0; id < 4; id++)
    {
        const char *num = dir_lookup_num(dir, names[id]);
        if (num == NULL)
        {
            printf("%s ne figure pas dans l'directory!\n", names[id]);
        }
        else
        {
            printf("Le numéro de %s est %s.\n", names[id], num);
        }
    }

    dir_free(dir);

    return EXIT_SUCCESS;
}
