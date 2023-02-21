#!/usr/bin/env python3

"""Un petit programme pour tester le module traceur.py"""

from traceur import trace

class Cellule:
    """Une cellule d'une liste chaînée"""

    def __init__(self, valeur, suivant):
        self.valeur = valeur
        self.suivant = suivant

    def __str__(self):
        return "cellule_" + str(self.valeur)

@trace(visualize=False)
def ajoute_valeurs_cellules(cell1, cell2):
    """Renvoie la valeur de la cellule + valeur du suivant"""
    return cell1.valeur + cell2.valeur

def main():
    """Test simple du module de traçage"""
    cell42 = Cellule(42, None)
    cell41 = Cellule(41, cell42)

    somme = ajoute_valeurs_cellules(cell41, cell42)
    print("Somme des deux cellules =", somme)

if __name__ == "__main__":
    main()
