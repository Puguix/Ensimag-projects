#!/usr/bin/env python3

"""Listes simplement chaînées avec partages de suffixes."""

import traceur

class Cellule:
    """Une cellule d'une liste simplement chaînée.

    Contient une référence vers la valeur, une référence vers la cellule
    suivante et une référence vers un compteur comptabilisant combien
    de cellules pointent dessus.
    """
    def __init__(self, valeur, suivant=None):
        self.valeur = valeur
        self.suivant = suivant
        self.utilisation = 1

    def __str__(self):
        return str(self.valeur) + " , " + str(self.utilisation)

class ListeSimplementChainee:
    """Liste simplement chainée avec partage de cellule.

    Des listes simplement chainées différentes peuvent partager
    des cellules communes.
    """
    def __init__(self, mot):
        """Construit une liste simplement chaînée à partir d'un mot.

        La liste simplement chaînée construite ne partage aucune cellule
        pour le moment.
        """
        premiere_cellule = None
        self.taille = 0
        for lettre in reversed(mot):
            premiere_cellule = Cellule(lettre, premiere_cellule)
            self.taille += 1
        self.tete = premiere_cellule

    def __str__(self):
        """Renvoie la chaîne de cractères "val1 --> val2 --> val3 ..." """
        return "-->".join(str(cell.valeur) for cell in recupere_cellules(self))


def recupere_cellules(liste_chainee):
    """Générateur renvoyant un itérateur sur toutes les cellules."""
    cell=liste_chainee.tete
    while cell is not None:
        yield cell
        cell=cell.suivant

def ajoute_suffixe(liste_chainee, autre):
    """Ajoute la liste chaînée `autre` à la fin de `liste_chainee`.

    Toutes les cellules de autre sont partagées.
    Si la fin de `liste_chainee` était déjà partagée avec quelqu'un, alors
    il faut dédoubler toute la partie partagée avant l'ajout pour ne pas changer
    les autres listes chaînées utilisant cette fin.
    """
    cell=liste_chainee.tete
    if cell is not None:
        while cell.suivant is not None and cell.utilisation==1:
            cell=cell.suivant
        if cell.utilisation==1:
            cell.suivant=autre.tete
            cellules=recupere_cellules(autre)
            cells=next(cellules,None)
            while cells is not None:
                cells.utilisation+=1
                cells=next(cellules,None)
        else:
            cell_copy=Cellule(cell.suivant.valeur,None,1)
            cell_copy0=cell_copy
            cell_changement=cell
            while cell.suivant is not None:
                cell=cell.suivant
                cell_suivante=Cellule(cell.suivant.valeur,None,1)
                cell_copy.suivant=cell_suivante
                cell_copy=cell_suivante
            cell_changement.suivant=cell_copy0
            cell_copy.suivant=autre.tete
            cells=next(cellules,None)
            while cells is not None:
                cells.utilisation+=1
                cells=next(cellules,None)
    

def teste_listes():
    """On teste toutes les operations dans différentes configurations."""

    print("on crée une list, c'est à dire un tableau dynamique, de 4 listes simplement chainées")
    listes_chainees = [ListeSimplementChainee(mot) for mot in
                       ("SE", "PAS", "DE", "DEVIS")]
    print(*listes_chainees, sep="\n")

    # On temporise
    _ = input("tapez sur une touche pour continuer")
    print()

    print("on ajoute", listes_chainees[0], "apres", listes_chainees[1])
    ajoute_suffixe(listes_chainees[1], listes_chainees[0])
    print(*listes_chainees, sep="\n")

    # On temporise
    _ = input("tapez sur une touche pour continuer")
    print()

    print("on ajoute une liste vide après", listes_chainees[1])
    ajoute_suffixe(listes_chainees[1], ListeSimplementChainee(""))
    print(*listes_chainees, sep="\n")

    # On temporise
    _ = input("tapez sur une touche pour continuer")
    print()

    print("on ajoute", listes_chainees[1], "apres", listes_chainees[2], "et",
          listes_chainees[0], "apres", listes_chainees[3])
    ajoute_suffixe(listes_chainees[2], listes_chainees[1])
    ajoute_suffixe(listes_chainees[3], listes_chainees[0])
    print(*listes_chainees, sep="\n")
    traceur.display_vars(traceur.Variable('listes', listes_chainees), deeply=False,
                         visualize=False, image_name="4_listes")

    # On temporise
    _ = input("tapez sur une touche pour continuer")
    print()

    liste_chainee_nt = ListeSimplementChainee("NT")
    print("on ajoute 'NT' apres 'PASSE'")
    ajoute_suffixe(listes_chainees[1], liste_chainee_nt)
    print(*listes_chainees, liste_chainee_nt, sep="\n")

    # On temporise
    _ = input("tapez sur une touche pour continuer")
    print()

    print("on ajoute 'SE' apres elle-meme")
    ajoute_suffixe(listes_chainees[0], listes_chainees[0])
    print(*listes_chainees, sep="\n")
    traceur.display_vars(traceur.Variable('listes', listes_chainees),
                         traceur.Variable('liste_chainee_nt', liste_chainee_nt),
                         deeply=False,
                         visualize=False, image_name="5_listes")

if __name__ == "__main__":
    teste_listes()
