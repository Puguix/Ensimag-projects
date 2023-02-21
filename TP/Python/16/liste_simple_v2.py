#!/usr/bin/env python3

"""Listes simplements chainees + quelques operations"""

import traceur

class Cellule:
    """Une cellule d'une liste."""
    def __init__(self,valeur,suivant=None):
            self.valeur=valeur
            self.suivant=suivant

class ListeSimplementChainee:
    """Une liste simplement chainee."""
    def __init__(self,iterable):
            self.tete=None
            self.queue=None
            self.taille=0
            valeurs=iter(iterable)
            val=next(iter,None)

            if val is not None:
                cell=Cellule(val)
                self.tete=cell
                self.queue=cell

                for ele in valeurs:
                    cell=Cellule(ele)
                    self.queue.suivant=cell
                    self.queue=cell
                    self.taille+=1

def recupere_cellules(liste):
    cell=liste.tete
    while cell is not None:
        cell=cell.suivant
        yield cell

def remplace_valeurs(liste,transforme):
    for cell in recupere_cellules(liste):
        cell.valeur=transforme(cell.valeur)

def filtre_cellules(liste,filtre):
    cell=liste.tete
    while cell is not None:
        f=filtre(cell.valeur)
        if not isinstance(f,bool):
            raise TypeError
        if f:
            cell=cell.suivant
            yield cell
        else:
            cell=cell.suivant

def supprime_cellules(liste,filtre):
    filtré=filtre_cellules(liste,filtre)
    val=next(filtré,None)
    
    if val is not None:
        while liste.tete.valeur!=val:
            liste.tete=liste.tete.suivant
        cell0=liste.tete
        cell=cell0.suivant
        val=next(filtré,None)
        while val is not None:
            while cell!=val:
                cell0.suivant=cell.suivant
                cell=cell0.suivant
            cell0=cell
            cell=cell.suivant
            val=next(filtré,None)
        cell0.suivant=None
        liste.queue=cell0

def concatene(l1,l2):
    valeurs=recupere_cellules(l2)
    cell=l1.queue
    val=next(valeurs,None)
    if val is not None:
        cell.suivant=val
        l1.queue=l2.queue
        supprime_cellules(l2,lambda x:False)
    
def decoupe(liste,fonction):
    valeurs=recupere_cellules(liste)
    cell=next(valeurs,None)
    while val is not None:
        if fonction(cell.valeur):
            concatene
            
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
