#!/usr/bin/env python3

"""Module tortue logo.

Ce module implémente les primitives graphiques basiques
d'une tortue logo.
"""

from svg import Point, genere_segment
from numpy import sin,cos,pi

def avance(abscisse, ordonnee, direction, crayon_en_bas, distance):
    """Fait avancer la tortue.

    Fait avancer la tortue dans la direction donnée et de la distance donnée.
    Affiche le segment SVG correspondant sur la sortie standard
    si le crayon est en bas.

    Renvoie la nouvelle position de la tortue sous la forme
    d'un Point (défini dans notre module svg).
    """
    
    abscisse_fin=abscisse+distance*cos(direction*pi/30)
    ordonnee_fin=ordonnee+distance*sin(direction*pi/30)
    point_fin=Point(abscisse_fin,ordonnee_fin)
    if crayon_en_bas:
        genere_segment(Point(abscisse,ordonnee),point_fin)
    return point_fin

def tourne_droite(direction, angle):
    """
    Fait tourner la tortue à droite.

    Fait tourner la tortue à partir de direction en tournant
    à droite de l'angle donné (en degrés).

    Renvoie la nouvelle direction.
    """
    return (direction+angle)%360

def tourne_gauche(direction, angle):
    """
    Fait tourner la tortue à droite.

    Fait tourner la tortue à partir de direction en tournant
    à droite de l'angle donné (en degrés).

    Renvoie la nouvelle direction.
    """
    return (direction-angle)%360
