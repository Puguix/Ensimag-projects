#!/usr/bin/env python3

import os
import sys

def traite_nombre(suite, type_suite, nombre):
    """ Traite le nombre donné vis à vis de la suite donnée.

    Renvoie (True, nouveau_type_suite) si suite est toujours
    une suite monotone après ajout de nombre.
    Renvoie (False, nouveau_type_suite) si la suite à changer de sens
    """
    if type_suite=="croissante":
        if nombre<suite[-1]:
            return False, "decroissante"
        return True, "croissante"
    else:
        if nombre>suite[-1]:
            return False, "croissante"
        return True, "decroissante"

def plus_longue(liste):
    res = max(len(elem) for elem in liste)
    while type(res)==int:
        for ele in liste:
            if len(ele)==res:
                res=ele
    return res


def main():
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "fichier a lire")
        sys.exit(1)

    fichier = open(sys.argv[1],'r')
    texte=fichier.readlines()

    chiffres=[]
    for ligne in texte:
        for ele in ligne.split(" "):
            chiffres.append(int(ele))


    sous_suites=[[chiffres[0]],[chiffres[0]]]
    type_sous_suites=["croissante","decroissante"]
    toujours_valide=[True,True]
    for i in range(1,len(chiffres)):
        for k in range(len(sous_suites)):
            if toujours_valide[k]:
                bool, type = traite_nombre(sous_suites[k],type_sous_suites[k],chiffres[i])
                if bool:
                    sous_suites[k].append(chiffres[i])
                else:
                    sous_suites.append([sous_suites[k][-1]]+[chiffres[i]])
                    type_sous_suites.append(type)
                    toujours_valide.append(True)
                toujours_valide[k]=bool

    print(plus_longue(sous_suites))


    fichier.close()

if __name__ == "__main__":
    main()
