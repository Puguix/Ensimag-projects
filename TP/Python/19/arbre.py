#!/usr/bin/env python3

"""Fractales : arbres, un exo sympa pour la recursion."""

# étudiant
from random import random, randint, choice
from math import pi, cos, sin, sqrt

import svg

def sub(point1, point2):
    """Renvoie un nouveau point égale à point1 - point2."""
    return svg.Point(point1.x - point2.x,
                     point1.y - point2.y)

def add(point1, point2):
    """Renvoie un nouveau point égale à point1 + point2."""
    return svg.Point(point1.x + point2.x,
                     point1.y + point2.y)

def mul(point, scalaire):
    """Renvoie un nouveau point égale à point * scalaire."""
    return svg.Point(point.x * scalaire,
                     point.y * scalaire)

def distance_a(point1, point2):
    """Renvoie la distance entre point1 et point2"""
    x_diff = (point1.x - point2.x)
    y_diff = (point1.y - point2.y)
    return sqrt(x_diff * x_diff + y_diff * y_diff)

def rotation(point, angle):
    """Tourne point autour de l'origine de l'angle donné en radians."""
    cosinus, sinus = cos(angle), sin(angle)
    return svg.Point(cosinus*point.x - sinus*point.y,
                     sinus*point.x + cosinus*point.y)

def dessine_branche(points, limite):
    """Dessine la branche entre les deux points donnés.

    Cette fonction S'appelle récursivement jusqu'à ce que
    la taille de la branche soit inférieure à la limite.
    """

    # On s'arrête quand la branche est en dessous de la
    # taille limite
    taille_branche = distance_a(points[0], points[1])
    if taille_branche < limite:
        return

    # On dessine la branche
    print(svg.genere_segment(points[0], points[1]))

    # On tire entre 2 et 4 sous branches au hasard
    for _ in range(randint(2, 4)):

        cote = choice((1, -1)) # à gauche ou à droite ?
        alpha = random()/3 # dans le tiers du haut
        nouveau_depart = add(mul(points[0], alpha), mul(points[1], (1-alpha)))
        taille = random() # taille quelconque mais <= 1 * taille courante
        nouvelle_arrivee = add(nouveau_depart,
                               rotation(mul(sub(points[1], points[0]), taille),
                                        cote*pi/4*random()))

        dessine_branche((nouveau_depart, nouvelle_arrivee), limite)

def dessine_arbre():
    """Génère un arbre au format SVG sur la sortie standard."""
    print(svg.genere_balise_debut_image(800, 600))
    print(svg.genere_balise_debut_groupe("black", "black", 1))
    print(svg.genere_rectangle(svg.Point(0, 0), 800, 600))
    print(svg.genere_balise_fin_groupe())
    print(svg.genere_balise_debut_groupe("white", "none", 1))
    dessine_branche((svg.Point(400, 550), svg.Point(400, 350)), 5)
    print(svg.genere_balise_fin_groupe())
    print(svg.genere_balise_fin_image())

if __name__ == "__main__":
    dessine_arbre()
