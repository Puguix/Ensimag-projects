#!/usr/bin/env python3

import random as rd
import time
import matplotlib.pyplot as plt
import math
from timeit import timeit
from sys import argv
from geo.point import Point

espace = None
largeur = None
nb_colonnes = None
nb_lignes = None
distance = None
list_sous_espace = []

def iter_lvl(lvl):
    """
    iterateur sur les sous-espaces alentours
    22222
    21112
    21012
    21112
    22222

    0 est le sous_espace_considéré
    1 couche de niveau 1
    2 couche de niveau 2
    """
    i = -lvl
    j = -lvl
    while i < lvl:
        yield (i, j)
        i += 1
    yield (i, j)
    j += 1
    while j < lvl:
        yield (i, j)
        j += 1
    yield (i, j)
    i -= 1
    while i > -lvl:
        yield(i, j)
        i -= 1
    yield(i, j)
    j -= 1
    while j > -lvl:
        yield(i, j)
        j -= 1

def load_instance(filename):
    """
    loads .mnt file. 
    returns list of points.
    """
    with open(filename, "r") as instance_file:
        points = [Point((float(p[0]), float(p[1]))) for p in (l.split(',') for l in instance_file)]

    return points


def print_solution(points):
    c, d = dist_non_recursive(points)
    print(f"{str(c[0])}; {str(c[1])}")

def clean():
    """
    remise à 0 des variables globales
    """
    global espace
    global largeur
    global nb_colonnes
    global nb_lignes
    global distance
    global list_sous_espace
    espace = None
    largeur = None
    nb_colonnes = None
    nb_lignes = None
    distance = None
    list_sous_espace = []

def calcul_min_naive(points):
    """
    calcul naif de la distance min
    """
    n = len(points)
    m = math.inf
    c = None
    for i in range(n):
        p = points[i]
        for j in range(i+1, n):
            dist = Point.distance_to(p, points[j])
            if dist < m:
                m = dist
                c = (p, points[j])
    return c, m

def calcul_min_naive_ext(p, points):
    """calcul naif entre un point et un ensemble de points"""
    m = math.inf #par defaut on prends la distance la plus grande (vu qu'on compare après)
    c = None
    for pt in points:
        #Si on trouve notre points on le skip
        if pt == p:
            continue
        dist = Point.distance_to(p, pt)
        if dist < m:
            m = dist
            c = (p, pt)
    return c, m

def calcul_pseudo_min(points, k):
    """
    calcul un pseudo min avec k couples de points selectionnés au hasard
    """
    m = math.inf
    n = len(points)
    for i in range(k):
        u = rd.randint(0, n-1)
        v = rd.randint(0, n-1)
        if u == v:
            continue
        dist = Point.distance_to(points[u], points[v])
        if dist < m:
            m = dist
    return m

def place_point(points):
    """
    place les points dans notre matrice d'espace selon les coordonées
    """
    #TODO traiter cas, x_min = x_max et y_min = y_max
    x_min, x_max = calcul_min_max(points, 0)
    y_min, y_max = calcul_min_max(points, 1)

    global largeur
    pseudo_dist_min = calcul_pseudo_min(points, len(points))
    largeur = min(pseudo_dist_min, (x_max-x_min)/math.sqrt(len(points)), (y_max-y_min)/math.sqrt(len(points)))

    global nb_colonnes
    nb_colonnes = int((x_max-x_min)/largeur)

    global nb_lignes
    nb_lignes = int((y_max-y_min)/largeur)

    global list_sous_espace
    list_sous_espace = []

    global espace
    espace = {}

    dico_espace = {}
    for pt in points:
        x, y = pt.coordinates
        p_x = int((x-x_min)/(x_max-x_min)*(nb_colonnes)) #transformation classique pour se ramenet dans la bonne plage de donnée
        p_y = int((y-y_min)/(y_max-y_min)*(nb_lignes))
        p_x = p_x - 1 if p_x == nb_colonnes else p_x
        p_y = p_y - 1 if p_y == nb_lignes else p_y
        if dico_espace.get((p_x, p_y), None) is None:
            dico_espace[(p_x, p_y)] = 1
            espace[(p_x, p_y)] = []
            list_sous_espace.append((p_x, p_y))

        espace[(p_x, p_y)].append(pt)
    
def dist_non_recursive(points):
    """
    calcule la distance min non récursive grâce à un quadrillage
    """
    place_point(points)

    global distance
    distance = math.inf

    c_point = None
    for coord in list_sous_espace:
        i, j = coord
        c0, d0 = calcul_min_naive(espace[(i, j)])
        c1, d1 = min_se_alentours(i, j, c0, d0)
        d = d0 if d0 < d1 else d1
        c = c0 if d0 < d1 else c1
        if d < distance:
            distance = d
            c_point = c
        if d == 0:
            return i, j
    return c_point, distance

def min_se_alentours(i, j, c0, d0):
    """
    calcule le min parmis les sous-espaces qui sont aux alentours
    """
    d = d0
    lvl = 1
    c_dist = c0
    
    lvl_max = max(nb_colonnes, nb_lignes)
    while lvl < lvl_max and d > (lvl-1)*largeur and distance > (lvl-1)*largeur:
        """
        i*largeur correspond a la distance d'arret
        """
        #on va parcourir les espaces alentour
        for c in iter_lvl(lvl):
            k, l = c
            # Si l'espace qu'on considère existe pas ou qu'il est vide on n'entre pas dedans
            se = espace.get((i+k, j+l), [])
            if len(se) != 0:
                for pts in espace[(i, j)]:
                    c_point, dist = calcul_min_naive_ext(pts, se)

                    if dist < d:
                        d = dist
                        c_dist = c_point
        lvl += 1
    return (c_dist, d)

def calcul_min_max(points, k):
    """
    calcul le min et le max en position de la coordonnée x ou y
        x : k = 0
        y : k = 1
    """
    m = M = points[0].coordinates[k]

    for pts in points:
        c = pts.coordinates[k]
        if c < m: m = c
        if c > M: M = c
    return m, M


def main():
    """
    ne pas modifier: on charge des instances donnees et affiches les solutions
    """
    for instance in argv[1:]:
        points = load_instance(instance)
        print_solution(points)


main()
