#!/usr/bin/env python3

import os
import sys


def affiche(tab):
    alphabet=[]
    ligne1=" "
    ligne2=" +"
    for k in range(len(tab[0])):
        ligne1+="  "+str(k)+"  "
        ligne2+=5*"-"
    print(ligne1+" ")
    print(ligne2+"+")
    for i in range(len(tab)):
        ligne=chr(k+65)+"|"
        for j in range(len(tab[0])):
            if tab[i][j]==".":
                ligne+="\u25A1"
            else:
                ligne+="\u25A0"
        ligne+="|"
        print(ligne)
    print(ligne2)
    print("   ")
    print("Choisissez une case à jouer:")

def est_fini(tab):
    for ele in tab:
        for el in ele:
            if el=="_":
                return False

def change(g,i,j):
    if g[i][j]==".":
        return "_"
    return "."

def modifie(case,graphe):
    car=["_","."]
    i=ord(case[0])-65
    j=int(case[1])-1
    #faire les cas angles, bord, milieu et modifier _ . 
    graphe[i][j]=change(graphe,i,j)
    if i==0 and j==0:
        graphe[1][0]=change(graphe,1,0)
        graphe[0][1]=change(graphe, 0, 1)
    elif i==0 and j==len(graphe[0])-1:
        graphe[1][j]=change(graphe,1,j)
        graphe[0][j-1]=change(graphe, 0 , j-1)
    elif i==len(graphe)-1 and j==0:
        graphe[i][1]=change(graphe,i,1)
        graphe[i-1][0]=change(graphe,i-1,0)
    elif i==len(graphe)-1 and j==len(graphe[0])-1:
        graphe[i][j-1]=change(graphe,i,j-1)
        graphe[i-1][j]=change(graphe,i-1,j)
    elif i==(0 or len(graphe)-1):
        graphe[i][j-1]=change(graphe,i,j-1)
        graphe[i][j+1]=change(graphe,i,j+1)
        if i==0:
            graphe[1][j]=change(graphe,1,j)
        else:
            graphe[i-1][j]=change(graphe,i-1,j)
    elif j==(0 or len(graphe[0])-1):
        graphe[i-1][j]=change(graphe,i-1,j)
        graphe[i+1][j]=change(graphe,i+1,j)
        if j==0:
            graphe[i][1]=change(graphe,i,1)
        else:
            graphe[i][j-1]=change(graphe,i,j-1)
    else:
        graphe[i-1][j]=change(graphe,i-1,j)
        graphe[i+1][j]=change(graphe,i+1,j)
        graphe[i][j-1]=change(graphe,i,j-1)
        graphe[i][j+1]=change(graphe,i,j+1)
    return graphe


def main():
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "nombre")
        sys.exit(1)

    fichier = open(sys.argv[1],'r')
    texte=fichier.readlines()

    bool=True
    
    finit=est_fini(texte)

    while not finit:

        affiche(texte)

        case=input()

        #fct modifie case
        texte = modifie(case,texte)



    fichier.close()

if __name__ == "__main__":
    main()
