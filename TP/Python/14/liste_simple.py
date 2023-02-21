#!/usr/bin/env python3

"""Listes simplements chainees + quelques operations"""

import traceur

class Cellule:
    """Une cellule d'une liste."""
    def __init__(self,valeur,suivant):
            self.valeur=valeur
            self.suivant=suivant

class ListeSimplementChainee:
    """Une liste simplement chainee."""
    def __init__(self,tete,queue,taille):
            self.tete=tete
            self.queue=queue
            self.taille=taille

def ajoute_en_tete(liste_chainee, valeur):
    """Ajoute une cellule en tete"""
    liste_chainee.taille=liste_chainee.taille+1
    liste_chainee.tete=Cellule(valeur,liste_chainee.tete)

def ajoute_en_queue(liste_chainee, valeur):
    """Ajoute une cellule en queue."""
    liste_chainee.taille=liste_chainee.taille+1
    cellule_fin=Cellule(valeur,None)
    liste_chainee.queue=Cellule(liste_chainee.queue.valeur,cellule_fin)
    liste_chainee.queue=cellule_fin

def recupere_cellules(liste_chainee):
    """Renvoie un vecteur contenant toutes les cellules de la liste_chainee"""
    res=[liste_chainee.tete]
    cellule=liste_chainee.tete
    while cellule.suivant!=None:
        cellule=cellule.suivant
        res+=[cellule]
    return res

def recherche(liste_chainee, valeur):
    """Recherche uen valeur dans la liste_chainee donnée.

    Renvoie la premiere cellule contenant la valeur donnée ou
    None si la valeur n'est pas trouvée dans la liste_chainee.
    """
    cellule=liste_chainee.tete
    while cellule.valeur!=valeur:
        cellule=cellule.suivant
    return cellule if cellule.valeur==valeur else None

def supprime(liste_chainee, valeur):
    """Enleve la premiere cellule contenant la valeur donnée."""
    cellule=recherche(liste_chainee,valeur)
    if cellule==None:
        return "il ya un pbm"
    else:
        liste_chainee.taille-=1
        cell=liste_chainee.tete
        if cell==cellule:
            liste_chainee.tete=cell.suivant
        else:
            while cell!=cellule:
                cell_1=cell
                cell=cell.suivant
            cell_1.suivant=cell.suivant

def test_listes():
    """On teste les operations de base, dans differentes configurations."""
    liste_chainee = ListeSimplementChainee()
    traceur.display_instance(liste_chainee,
                             visualize=False,
                             image_name="liste_chainee_0")
    ajoute_en_tete(liste_chainee, 3)
    ajoute_en_tete(liste_chainee, 5)
    ajoute_en_tete(liste_chainee, 2)
    ajoute_en_tete(liste_chainee, 4)
    print("liste_chainee : ", liste_chainee)
    traceur.display_instance(liste_chainee,
                             visualize=False,
                             image_name="liste_chainee_1")
    print("recherche : ", recherche(liste_chainee, 3).valeur)
    supprime(liste_chainee, 5)
    print("apres suppression de 5 : ", liste_chainee)
    traceur.display_instance(liste_chainee,
                             visualize=False,
                             image_name="liste_chainee_2")
    supprime(liste_chainee, 4)
    print("apres suppression de 4 : ", liste_chainee)
    traceur.display_instance(liste_chainee,
                             visualize=False,
                             image_name="liste_chainee_3")

if __name__ == "__main__":
    test_listes()
