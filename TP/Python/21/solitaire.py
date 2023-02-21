#!/usr/bin/env python3

"""Jeu du solitaire."""

import subprocess
import sys
import plateau

def calcule_solution(plat):
    """Renvoie la suite des coups à jouer **à l'envers** pour gagner.

    Renvoie None si on ne peut pas gagner.
    """
    coups_possibles = iter(plateau.recupere_coups(plat))
    coup = next(coups_possibles, None)
    while coup is not None:
        nouveau_plat = plateau.joue_coup(plat, coup)
        if plateau.est_gagnant(nouveau_plat):
            return coup
        else:
            return coup, calcule_solution(nouveau_plat)
        coup= next(coups_possibles, None)
    

def demande_coup(plat):
    """Demande quel coup jouer à l'utilisateur."""
    try:

        # Demande la case à jouer
        print("tapez ^C pour arrêter et lancer la résolution")
        depart = int(input("ou alors \n  donnez une case de départ: "))
        if plat.cases[depart] == plateau.VIDE:
            print("  case de départ invalide")
            raise ValueError

        # Demande la case d'arrivée
        arrivee = int(input("  donnez une case d'arrivée: "))
        if plat.cases[arrivee] == plateau.PION:
            print("  case d'arrivée invalide")
            raise ValueError

        # On vérifie que le mouvement est valide, c'est à dire
        # qu'il y a un pion entre le départ et l'arrivée.
        # Le FAMEUX "for else" de Python : c'est QUOi CE TRUC ??
        for direction, milieu in enumerate(plateau.VOISINS[depart]):
            if milieu is not None:
                apres_milieu = plateau.VOISINS[milieu][direction]
                if apres_milieu is not None and apres_milieu == arrivee:
                    break
        else:
            print("  mouvement invalide")
            raise ValueError
        # Nous (mais pas pylint) savons qu'ici milieu est défini
        # pylint: disable=undefined-loop-variable
        if plat.cases[milieu] == plateau.VIDE:
            print("  mouvement invalide")
            raise ValueError
        return depart, milieu, arrivee

    # Ici on fait suivre l'exception
    except KeyboardInterrupt:
        raise

    # Ici on redemande à l'utilisateur car il
    # a joué un coup invalide.
    # pylint, laisse nous tranquille, on gère !
    except: # pylint: disable=bare-except
        return demande_coup(plat)

def main():
    """Lance une partie de solitaire."""

    # On determine si on est dans terminology ou non
    # pour savoir comment afficher le plateau :
    #  SVG ou textuel ?
    process = subprocess.Popen(["tycat"], stdout=subprocess.PIPE)
    process.communicate()
    exit_code = process.wait()
    in_terminology = exit_code == 0

    # On joue tant que ^C n'est pas tapé ou qu'on a pas gagné
    plat = plateau.Plateau()
    while not plateau.est_gagnant(plat):
        plateau.affiche(plat, in_terminology)
        try:
            coup = demande_coup(plat)
        except KeyboardInterrupt: # sur ^C
            break
        print(f"on joue de {coup[0]} a {coup[2]}")
        plateau.joue_coup(plat, coup)

    # Si le joueur humain a gagné, on s'arrête
    if plateau.est_gagnant(plat):
        print("Gagné !!!")
        sys.exit(0)

    # Sinon on demande la solution pour finir à notre
    # intelligence artificielle (fallait le placer ce
    # terme dans le cours BPI quand même !)
    suite = calcule_solution(plat)
    print()
    if suite:
        print("suite de coups possible pour terminer :")
        for debut, _, arrivee in reversed(suite):
            print("(", debut, ", ", arrivee, ")", sep="", end=" ")
        sys.exit(0)
    else:
        print("pas moyen d'aller plus loin !!!")
        sys.exit(1)

if __name__ == "__main__":
    main()
