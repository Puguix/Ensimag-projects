#!/usr/bin/env python3

import os
import sys


def main():
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "fichier a lire")
        sys.exit(1)

    fichier = open(sys.argv[1],'r')
    texte=fichier.readlines()
    for ligne in texte:
        print(ligne)
    fichier.close()

if __name__ == "__main__":
    main()
