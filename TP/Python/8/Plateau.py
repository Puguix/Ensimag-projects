#!/usr/bin/env python3

import sys
from svg import Point,genere_balise_debut_groupe,genere_balise_debut_image,genere_balise_fin_groupe,genere_balise_fin_image,genere_segment

def genere_image(largeur, hauteur):
    """
    Affiche le SVG correspondant sur la sortie standard.
    """
    print(genere_balise_debut_image(largeur, hauteur))
    print(genere_balise_debut_groupe())

    coordonnees=[Point(0,hauteur)]
    sens='droite'
    compteur_blocage=0

    def avance(p,sens,compteur_blocage):
        if sens=='droite':
            if p.x+80<=largeur:
                return (Point(p.x+40,p.y),'droite',0)
            elif p.y-80>=0:
                if compteur_blocage==0:
                    return (Point(p.x,p.y-40),'droite',1)
                else:
                    return (Point(p.x,p.y-40),'gauche',0)
            else:
                return ("bloqué",0,0)
        else:
            if p.x-80>=0:
                    return (Point(p.x-40,p.y),'gauche',0)
            elif p.y-80>=0:
                if compteur_blocage==0:
                    return (Point(p.x,p.y-40),'gauche',1)
                else:
                    return (Point(p.x,p.y-40),'droite',0)
            else:
                return ("bloqué",0,0)

    while coordonnees[-1]!="bloqué":
        res=avance(coordonnees[-1],sens,compteur_blocage)
        coordonnees.append(res[0])
        sens=res[1]
        compteur_blocage=res[2]
    
    for i in range(len(coordonnees)-1):
        # on génère la case dont p est le point en bas a gauche
        p=coordonnees[i]
        print(genere_segment(p,Point(p.x+40,p.y)))
        print(genere_segment(p,Point(p.x,p.y-40)))
        print(genere_segment(Point(p.x+40,p.y),Point(p.x+40,p.y-40)))
        print(genere_segment(Point(p.x,p.y-40),Point(p.x+40,p.y-40)))

        
    print(genere_balise_fin_groupe())
    print(genere_balise_fin_image())


def main():
    """On génère un SVG a partir de la taille"""
    if len(sys.argv) != 3 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "largeur hauteur > image.svg")
        sys.exit(1)

    largeur = int(sys.argv[1])
    hauteur = int(sys.argv[2])
    genere_image(largeur,hauteur)


if __name__ == "__main__":
    main()
