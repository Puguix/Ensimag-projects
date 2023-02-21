#!/usr/bin/env python3

from os import EX_PROTOCOL, setgid
from random import lognormvariate
import subprocess
import sys
import approximate_pi as approx

def generate_ppm_file(taille, n, precision):
    
    pi=0
    tableau_fond=[["0 0 0 " for _ in range(taille)] for _ in range(taille)]

    chiffres={'0':[1,2,3,5,6,7],'1':[6,7],'2':[2,3,4,5,6],'3':[3,4,5,6,7],'4':[1,4,6,7],'5':[1,3,4,5,7],'6':[1,2,3,4,5,7],'7':[3,6,7],'8':[k for k in range(1,8)],'9':[1,3,4,5,6,7]}
    milieu=taille//2
    longueur=taille//20
    epaisseur=taille//100
    debut_x=int(milieu-(precision/2 *(longueur+epaisseur)))
    debut_y=int(milieu-longueur)
    segments={
        1:[0,epaisseur,0,longueur],
        2:[0,epaisseur,longueur-epaisseur,longueur],
        3:[0,longueur,0,epaisseur],
        4:[0,longueur,longueur-epaisseur,epaisseur],
        5:[0,longueur,2*longueur-epaisseur,epaisseur],
        6:[longueur-epaisseur,epaisseur,0,longueur],
        7:[longueur-epaisseur,epaisseur,longueur-epaisseur,longueur]
        }

    for k in range(1,11):

        liste_points,res=approx.result(n//10)
        pi= (pi*(k-1)+res) /k
        decimale= int((pi-3)*pow(10,precision))

        img=open(f"{k}_3-{decimale}.ppm","w")

        print("P3",file=img)
        print(f"{taille} {taille}",file=img)
        print("255",file=img)


        for (p, dedans) in liste_points:
            tableau_fond[ int((p.x+1)*taille/2)][ int((p.y+1)*taille/2)]= "255 0 255 " if dedans else "255 255 0 "

        tableau=[]
        for ele in tableau_fond:
            tableau.append(list(ele))

        for seg in chiffres['3']:   
            for i in range(segments[seg][1]):
                for j in range(segments[seg][3]):
                    tableau[debut_y+segments[seg][2]+j][debut_x+segments[seg][0]+i]="255 255 0 "
        for i in range(epaisseur):
            for j in range(epaisseur):
                tableau[debut_y+2*longueur-epaisseur+j][debut_x+longueur+epaisseur+i]="255 255 0 "
        compteur=1
        for car in str(decimale):
            for seg in chiffres[car]:   
                for i in range(segments[seg][1]):
                    for j in range(segments[seg][3]):
                        tableau[debut_y+segments[seg][2]+j][debut_x+segments[seg][0]+compteur*longueur+(2+compteur)*epaisseur+i]="255 255 0 "
            compteur+=1


        for ele in tableau:
            ligne=""
            for txt in ele:
                ligne+=txt
            print(ligne,file=img)
        
        img.close()

    subprocess.run(['convert', '-delay', '700', '*.ppm', '-loop', '0', 'animation.gif'])


def main():
    if len(sys.argv) != 4 or sys.argv[1] == "-h" or sys.argv[1] == "--help" or not (0<int(sys.argv[3])<6):
        print("utilisation:", sys.argv[0], "taille image, nombre de points, précision (entre 1 et 5")
        sys.exit(1)

    generate_ppm_file( int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]) )


if __name__ == "__main__":
    main()
