/*
  Test du module directory.

  Crée un annuaire et le libère.
 */

#include <stdlib.h>

#include <directory.h>

int main(void)
{
  struct dir *dir = dir_create(5);
  dir_free(dir);

  return EXIT_SUCCESS;
}
