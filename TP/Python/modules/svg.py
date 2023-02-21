#!/usr/bin/env python3

"""
Un module pour générer des images au format SVG.

Ce module fournit diverses fonctions pour générer des éléments SVG
sous forme de chaînes de caractères.
Ces chaînes DOIVENT être écrites dans un fichier en respectant la
structure SVG pour obtenir une image valide.
"""

from collections import namedtuple

# Definition de la structure Point composée de deux attributs x et y
Point = namedtuple('Point', 'x y')

def genere_balise_debut_image(largeur, hauteur):
    """
    Retourne la chaine de caractères correspondant à la balise ouvrante pour
    décrire une image SVG de dimensions largeur x hauteur pixels. Les paramètres
    sont des entiers.

    Remarque : l’origine est en haut à gauche et l’axe des Y est orienté vers le
    bas.
    """
    return f"<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='{largeur}' height='{hauteur}'>"

def genere_balise_fin_image():
    """
    Retourne la chaine de caractères correspondant à la balise svg fermante.
    Cette balise doit être placée après tous les éléments de description de
    l’image, juste avant la fin du fichier.
    """
    return f"</svg>"

def genere_balise_debut_groupe(couleur_ligne="black", couleur_remplissage="white", epaisseur_ligne=2, opacite=1):
    """
    Retourne la chaine de caractères correspondant à une balise ouvrante
    définissant un groupe d’éléments avec un style particulier. Chaque groupe
    ouvert doit être refermé individuellement et avant la fermeture de l’image.

    Les paramètres de couleur sont des chaînes de caractères et peuvent avoir
    les valeurs :
    -- un nom de couleur reconnu, par exemple "red" ou "black" ;
    -- "none" qui signifie aucun remplissage (attention ici on parle de la chaîne
        de caractère "none" qui est différente de l'objet None).

    Le paramètre d’épaisseur est un nombre positif ou nul, représentant la
    largeur du tracé d'une ligne en pixels.
    """
    return f"     <g stroke='{couleur_ligne}' stroke-width='{epaisseur_ligne}' fill='{couleur_remplissage}' style='fill-opacity: {opacite}'>"

def genere_balise_fin_groupe():
    """
    Retourne la chaine de caractères correspondant à la balise fermante pour un
    groupe d’éléments.
    """
    return f"     </g>"

def genere_cercle(centre, rayon):
    """
    Retourne la chaine de caractères correspondant à un élément SVG représentant
    un cercle (ou un disque, cela dépend de la couleur de remplissage du groupe
    dans lequel on se trouve).

    centre est une structure de données de type Point, et rayon un nombre de
    pixels indiquant le rayon du cercle.
    """
    return f"        <circle cx='{centre.x}' cy='{centre.y}' r='{rayon}'/>"

def genere_segment(dep, arr):
    """
    Retourne la chaine de caractères correspondant à un élément SVG représentant
    un segment. Ce segment relie les points dep et arr.
    """
    return f"       <line x1='{dep.x}' y1='{dep.y}' x2='{arr.x}' y2='{arr.y}'/>"

def genere_polygone(points):
    coordonnees_points=""
    for p in points:
        coordonnees_points+= f"{p.x},{p.y} "
    return f"       <polygon points='{coordonnees_points}'/>"

