#!/usr/bin/env python3

from svg import *

print(genere_balise_debut_image(640,480))
print(genere_balise_debut_groupe("red","red",1))

for _ in range(1000):
    x = int(input())
    y = int(input())
    print(genere_cercle(Point(x,y),4))

print(genere_balise_fin_groupe())
print(genere_balise_fin_image())