ensimag-shell
=============

Squelette pour le TP shell

Tous les fichiers sont sous licence GPLv3+

Introduction
----------

Ces fichiers servent de base à un TP sur le shell de commande à la Unix.

Spécificités de ce squelette:
- plusieurs variantes (libre choix par les étudiants)
- jeux de tests fournis aux étudiants
- utilisation de Gnu Readline
- Scheme (interpréteur Guile; Javascript possible)

Compilation et lancement des tests
----------

cd ensimag-shell
cd build
cmake ..
make
make test



Autres
------

Les premières versions imposaient la variante par un modulo sur le
sha512 sur de la liste triée des logins des étudiants. Cela peut être
réalisé complètement en CMake (>= 2.8).
