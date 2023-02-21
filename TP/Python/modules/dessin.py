#!/usr/bin/env python3

from random import randint as rd
from svg import *

def couleur_aleatoire():
    return f"rgb({rd(0,255)},{rd(0,255)},{rd(0,255)})"

def affiche_triangle(triangle,couleur):
    print(genere_polygone(triangle))