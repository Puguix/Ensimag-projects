#!/usr/bin/env python3

import sys
from random import random as rd
from collections import namedtuple

Point=namedtuple('Point', 'x y')

def result(n):
    list_points=[]
    compteur_point_interieur=0
    for _ in range(n):
        p = Point(2*rd()-1,2*rd()-1)
        est_p_dans_cercle = (p.x**2+p.y**2)**(1/2)<=1
        if est_p_dans_cercle:
            compteur_point_interieur+=1
        list_points.append((p, est_p_dans_cercle))
    return list_points,compteur_point_interieur/n *4

def main():
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "nombre de points")
        sys.exit(1)

    print(result(int(sys.argv[1]))[1])

if __name__ == "__main__":
    main()
