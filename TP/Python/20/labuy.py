#!/usr/bin/env python3

"""Dessin d'un labyrinthe récursif."""

# étudiant
from random import randint
import sys
import svg

ECHELLE = 20
MARGE = 10

def genere_segment_avec_zoom(debut_x, debut_y, arrivee_x, arrivee_y):
    """Genere un ségement SVG en zoomant. selon ECHELLE et MARGE."""
    return svg.genere_segment(svg.Point(debut_x*ECHELLE + MARGE/2, debut_y*ECHELLE + MARGE/2),
                              svg.Point(arrivee_x*ECHELLE + MARGE/2, arrivee_y*ECHELLE + MARGE/2))

def dessine_murs(coordonnees, chemin):
    """Dessine recursivement des murs aleatoires.

    coordonnees est un quadruplet : pos_x, pos_y, largeur, hauteur
    chemin vaut soit la liste vide si le rectangle à traiter n’est pas sur le chemin
    soit une liste à deux éléments : coordonnées de l’entrée et de la sortie.
    Renvoie la liste des points par où passer.
    """
    pos_x, pos_y, largeur, hauteur = coordonnees
    if largeur <= 1 or hauteur <= 1:
        return chemin

    # coordonnées des deux sous-rectangles pour les appels récursifs
    coord_rect = [None, None]
    # coordonnées juste avant la porte et juste après la porte
    porte_av, porte_ap = None, None
    c_mur = None # coordonnée (x ou y) du mur
    x_ou_y = 0 # 0 pour x, 1 pour y

    if largeur > hauteur:
        # on coupe verticalement
        c_mur = pos_x + randint(1, largeur-1)
        c_porte = pos_y + randint(1, hauteur)
        print(genere_segment_avec_zoom(c_mur, pos_y, c_mur, c_porte-1))
        print(genere_segment_avec_zoom(c_mur, c_porte, c_mur, pos_y+hauteur))

        porte_av = (c_mur-0.5, c_porte-0.5)
        porte_ap = (c_mur+0.5, c_porte-0.5)
        coord_rect[0] = (pos_x, pos_y, c_mur-pos_x, hauteur)
        coord_rect[1] = (c_mur, pos_y, largeur-(c_mur-pos_x), hauteur)
    else:
        # ou coupe horizontalement
        x_ou_y = 1
        c_mur = pos_y + randint(1, hauteur-1)
        c_porte = pos_x + randint(1, largeur)
        print(genere_segment_avec_zoom(pos_x, c_mur, c_porte-1, c_mur))
        print(genere_segment_avec_zoom(c_porte, c_mur, pos_x+largeur, c_mur))

        porte_av = (c_porte-0.5, c_mur-0.5)
        porte_ap = (c_porte-0.5, c_mur+0.5)
        coord_rect[0] = (pos_x, pos_y, largeur, c_mur-pos_y)
        coord_rect[1] = (pos_x, c_mur, largeur, hauteur-(c_mur-pos_y))

    # calcul du chemin à suivre
    chem_premier_rect, chem_second_rect = [], []
    ordre = 0 # numéro du rectangle par lequel on passe en premier
    if chemin != []:
        if chemin[0][x_ou_y] < c_mur:
            if chemin[1][x_ou_y] < c_mur: # on ne passe que par le rectangle 0
                chem_premier_rect = chemin
            else: # on passe par le 0 puis par le 1
                chem_premier_rect = [chemin[0], porte_av]
                chem_second_rect = [porte_ap, chemin[1]]
        elif chemin[1][x_ou_y] < c_mur: # on passe par le 1 puis par le 0
            ordre = 1 # on inverse l’ordre des deux rectangles
            chem_premier_rect = [chemin[0], porte_ap]
            chem_second_rect = [porte_av, chemin[1]]
        else: # on ne passe que par le 1
            chem_second_rect = chemin

    # appels récursifs
    chem1 = dessine_murs(coord_rect[ordre], chem_premier_rect)
    chem2 = dessine_murs(coord_rect[1-ordre], chem_second_rect)
    return chem1 + chem2

def dessine_contours(largeur, hauteur):
    """Dessine les contours du labyrinthe. """
    print(svg.genere_balise_debut_groupe("white", "white", 0))
    print(svg.genere_rectangle(svg.Point(0, 0), largeur*ECHELLE + MARGE, hauteur*ECHELLE + MARGE))
    print(svg.genere_balise_fin_groupe())
    print(svg.genere_balise_debut_groupe("black", "none", ECHELLE/8))
    print(genere_segment_avec_zoom(0, 0, 0, hauteur))
    print(genere_segment_avec_zoom(largeur, 0, largeur, hauteur))
    print(genere_segment_avec_zoom(1, 0, largeur, 0))
    print(genere_segment_avec_zoom(0, hauteur, largeur-1, hauteur))
    print(svg.genere_balise_fin_groupe())

def dessine_chemin(chemin):
    """Dessin du chemin pour sortir."""
    print(svg.genere_balise_debut_groupe("blue", "none", ECHELLE/4))
    for i in range(len(chemin)-1):
        print(genere_segment_avec_zoom(chemin[i][0], chemin[i][1],
                                       chemin[i+1][0], chemin[i+1][1]))
    print(svg.genere_balise_fin_groupe())

def dessine_labyrinthe():
    """Génère un labyrinthe au format SVG de la taille donnée sur la sortie standard."""
    if len(sys.argv) != 3:
        print("utilisez laby.py largeur hauteur")
        sys.exit()
    largeur, hauteur = int(sys.argv[1]), int(sys.argv[2])

    print(svg.genere_balise_debut_image(largeur*ECHELLE + MARGE, hauteur*ECHELLE + MARGE))
    dessine_contours(largeur, hauteur)
    print(svg.genere_balise_debut_groupe("black", "none", ECHELLE/4))
    chemin = dessine_murs((0, 0, largeur, hauteur),
                          [(0.5, 0.5), (largeur-0.5, hauteur-0.5)])
    print(svg.genere_balise_fin_groupe())
    dessine_chemin([(0.5, -1)] + chemin + [(largeur-0.5, hauteur+1)])
    print(svg.genere_balise_fin_image())

if __name__ == "__main__":
    dessine_labyrinthe()
