/*
  Test du module directory.

  Suppression dans un directory.
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
        "Tartempion",
        "Caporal Ketchup",
        "Sergent Mayo"
    };

    for (size_t id = 0; id < 4; id++) {
        dir_delete(dir, names[id]);
        dir_print(dir);
    }

    dir_free(dir);

    return EXIT_SUCCESS;
}
