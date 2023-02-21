#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
exemple d'utilisation du module geo
"""
from math import cos, sin, pi
from itertools import islice, cycle

from geo.point import Point
from geo.tycat import tycat
from geo.segment import Segment


def main():
    """
    petit exemple sur l'utilisation de tycat
    """
    print("lancez moi dans terminology")
    print("tycat permet d'afficher des points et des segments")
    print("chaque argument doit etre un iterable sur des points \
et/ou segments (ou juste un point/segment)")
    print("chaque argument est affiche d'une couleur differente")

    # un point
    origine = Point([0.0, 0.0])
    # un vecteur de points
    cercle = [Point([cos(c*pi/10), sin(c*pi/10)]) for c in range(20)]
    seg = Segment([Point([1.0, 0.0]), Point([0.0, 1.0])])
    tycat(seg)
    # un iterateur sur des segments (crees a la volee)
    segments = (
        Segment([p1, p2])
        for p1, p2 in zip(cercle, islice(cycle(cercle), 1, None))
        )
    tycat(origine, cercle, segments)


main()
