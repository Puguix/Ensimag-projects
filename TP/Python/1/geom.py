#!/usr/bin/env python3

from collections import namedtuple

def affiche_triangle(triangle):
    print("triangle = (" + str(triangle.p1.x) + "," + str(triangle.p1.y) + ") (" + str(triangle.p2.x) + "," + str(triangle.p2.y) + ") (" 
        + str(triangle.p3.x) + "," + str(triangle.p3.y) + ")")

Point = namedtuple("Point", "x y")
Triangle = namedtuple("Triangle", "p1 p2 p3")

point1 = Point(50, 0)
point2 = Point(0, 50)
point3 = Point(50, 50)

tri = Triangle(point1, point2, point3)
affiche_triangle(tri)