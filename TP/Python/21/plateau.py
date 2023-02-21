"""Le module avec ce qu'il faut pour représenter le plateau."""

from itertools import islice
import os

# pylint: disable = too-few-public-methods
class Plateau:
    """Un plateau est representé par ses pions.

    On utilise un tableau dynamique de 15 cases.
    Initialement il y a un pion dans toutes les
    cases sauf dans la case numéro 12.
    """
    def __init__(self):
        self.cases = [PION for _ in range(15)]
        self.cases[12] = VIDE
        self.numero_affichage = 0

# Pour rendre le code plus lisible
VIDE = 0
PION = 1

INDICES_TO_UNICODE_VIDE = ["\u24FF"] + \
    [chr(ord("\u278A") + i) for i in range(10)] + \
    [chr(ord("\u24EB") + i) for i in range(5)]

INDICES_TO_UNICODE_PION = ["\u24EA"] + \
    [chr(ord("\u2460") + i) for i in range(15)]

# On stocke une fois pour toutes les
# voisins de chacune des 15 cases du
# plateau.
VOISINS = [
    [1, 2, None, None, None, None],
    [3, 4, 2, 0, None, None],
    [4, 5, None, None, 0, 1],
    [6, 7, 4, 1, None, None],
    [7, 8, 5, 2, 1, 3],
    [8, 9, None, None, 2, 4],
    [10, 11, 7, 3, None, None],
    [11, 12, 8, 4, 3, 6],
    [12, 13, 9, 5, 4, 7],
    [13, 14, None, None, 5, 8],
    [None, None, 11, 6, None, None],
    [None, None, 12, 7, 6, 10],
    [None, None, 13, 8, 7, 11],
    [None, None, 14, 9, 8, 12],
    [None, None, None, None, 9, 13],
]

def affiche(plateau, in_terminology):
    """Affiche le plateau en texte ou dans terminology."""
    os.system("clear")

    if in_terminology:
        nom_fichier = f"/tmp/plateau-{plateau.numero_affichage}.svg"
        plateau.numero_affichage += 1
        with open(nom_fichier, "w") as svg:
            print("<svg width='600' height='600'>", file=svg)
            print("<rect width='600' height='600' fill='white'/>", file=svg)
            cases = iter(plateau.cases)
            for ligne in range(5):
                for colonne, contenu in enumerate(islice(cases, ligne+1)):
                    _affiche_pion_terminology(svg, ligne, colonne, contenu)
            print("</svg>", file=svg)
        os.system(f"tycat {nom_fichier}")

    else:
        cases = iter(plateau.cases)
        for ligne in range(5):
            nb_empty_cases = (4 - ligne)
            print(" " * nb_empty_cases, end="")
            for colonne, contenu in enumerate(islice(cases, ligne+1)):
                _affiche_pion_texte(ligne, colonne, contenu)
            print()

def _affiche_pion_texte(ligne, colonne, contenu):
    indice = ligne*(ligne+1)//2 + colonne
    charac = INDICES_TO_UNICODE_VIDE[indice] if contenu == VIDE \
        else INDICES_TO_UNICODE_PION[indice]
    print(charac, end=" ")

def _affiche_pion_terminology(fichier, ligne, colonne, contenu):
    """Affiche le pion ligne/colonne dans le fichier svg donné.

    On affiche en noir un emplacement vide et en blanc un pion.
    """
    # pylint: disable=invalid-name
    y = 100 + ligne*100
    x = 300 + (colonne - ligne/2)*100
    fond, trait = ("white", "black") if contenu else ("black", "white")
    indice = ligne*(ligne+1)//2 + colonne
    print(f"<circle cx='{x}' cy='{y-10}' fill='{fond}' stroke='black' r='20'/>",
          file=fichier)
    print(f"<text x='{x}' y='{y}' fill='{trait}' text-anchor='middle' "
          f"font-size='30'>{indice}</text>",
          file=fichier)

def est_gagnant(plateau):
    """Renvoie True si le plateau ne contient qu'un pion et False sinon."""
    compte = 0
    for case in plateau.cases:
        if case == PION:
            compte += 1
            if compte == 2:
                return False
    return True

def joue_coup(plateau, coup):
    """Joue le coup valide donné en modifiant le plateau donné.

    Un coup est un triplet départ, milieu, arrivée.
    """
    depart, milieu, arrivee = coup
    plateau.cases[depart] = VIDE
    plateau.cases[milieu] = VIDE
    plateau.cases[arrivee] = PION


def recupere_coups(plateau):
    """Renvoie un itérateur sur tous les coups possibles."""
    for depart, _ in filter(lambda c: c[1] == PION, enumerate(plateau.cases)):
        for direction, milieu in enumerate(VOISINS[depart]):
            if milieu is not None and plateau.cases[milieu] == PION:
                arrivee = VOISINS[milieu][direction]
                if arrivee is not None and plateau.cases[arrivee] == VIDE:
                    yield depart, milieu, arrivee
