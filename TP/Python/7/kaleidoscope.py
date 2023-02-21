#!/usr/bin/env python3
"""Kaleidoscope.

Exercice graphique, quelques boucles, deux modules à écrire.
"""

import sys
from math import pi
from random import random
import dessin
import svg
from triangle import triangle_aleatoire, tourne_triangle_autour

def genere_image(nombre_triangles):
    """Génère le nombre de triangles demandé aléatoirement, les tourne.

    Affiche le SVG correspondant sur la sortie standard.
    """
    largeur, hauteur = 800.0, 600.0
    print(svg.genere_balise_debut_image(largeur, hauteur))
    centre = svg.Point(largeur / 2, hauteur / 2)

    for _ in range(nombre_triangles):
        # on génère un triangle à l'intérieur du quart en bas
        # à droite de l'image.
        triangle = triangle_aleatoire(
            largeur / 2, largeur,
            hauteur / 2, hauteur
        )
        couleur = dessin.couleur_aleatoire()
        print(svg.genere_balise_debut_groupe('red',couleur,0,random()))
        # on tourne et on affiche 8 fois le triangle
        for tour in range(8):
            angle = pi / 4 * tour
            triangle_tourne = tourne_triangle_autour(triangle, centre, angle)
            dessin.affiche_triangle(triangle_tourne, couleur)
        print(svg.genere_balise_fin_groupe())

    print(svg.genere_balise_fin_image())


def main():
    """On génère un SVG kaléidoscopique à partir d'un nombre de triangles"""
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "nombre_triangles > image.svg")
        sys.exit(1)

    nombre_triangles = int(sys.argv[1])
    genere_image(nombre_triangles)


if __name__ == "__main__":
    main()
