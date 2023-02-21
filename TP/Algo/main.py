#!/usr/bin/env python3

from timeit import timeit
from sys import argv
from geo.point import Point


def load_instance(filename):
    """
    loads .mnt file. 
    returns list of points.
    """
    with open(filename, "r") as instance_file:
        line = next(iter(instance_file))
        points = [Point((float(p[0]), float(p[1]))) for p in (l.split(',') for l in instance_file)]

    return points


def print_solution(points):
    """
    calcul et affichage de la solution (a faire)
    """
    pass  # TODO: afficher la solution


def main():
    """
    ne pas modifier: on charge des instances donnees et affiches les solutions
    """
    for instance in argv[1:]:
        points = load_instance(instance)
        print_solution(points)


main()

