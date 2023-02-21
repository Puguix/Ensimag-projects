#!/usr/bin/env python3

from svg import *

image=open("image_svg.svg",'w')
print(genere_balise_debut_image(360,360),genere_balise_debut_groupe("blue","red",3),genere_cercle(Point(180,180),20),genere_balise_fin_groupe(),genere_balise_fin_image(),file=image)
image.close()