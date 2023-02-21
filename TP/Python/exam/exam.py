#!/usr/bin/env python3

"""Un programme qui ne sert à pas grand chose."""

import sys

def teste():
    """Teste les fonctions :
        - `recupere_combinaisons_2`
        - `recupere_combinaisons`
        - `recupere_parametres`

    Ces trois fonctions testées seront écrites plus tard, mais c'est
    souvent une bonne chose de commencer par les tests, donc allons-y.
    En plus, écrire ce test vous obligera à réfléchir à l'algorithme
    général à appliquer pour générer les combinaisons, sur des séquences
    simples.

    Les spécifications du travail à réaliser sont données en commentaire
    dans le corps de la fonction ci-dessous.
    Vous devez rajouter une ou plusieurs lignes de code à chaque fois qu'il
    y a un TODO suivi de trois points.
    Merci de respecter les spécifications À LA LETTRE pour que la correction
    automatique soit possible.

    Pour rappel, en python une séquence `seq` est un objet sur lequel on peut :
      - utiliser la fonction `len(seq)` pour connaître sa taille. Cette opération
        s'effectue en temps constant ;
      - utiliser dans une boucle for pour parcourir tous les éléments de la
        séquence ;
      - accéder au ième élément avec `seq[i]`.
    """
    # affiche sur la sortie standard une ligne contenant EXACTEMENT
    # la chaîne de caractère suivante :
    #   Résultats calculés dans ma tête pour la séquence "ABCD" et k=2
    print("Résultats calculés dans ma tête pour la séquence 'ABCD' et k=2")

    # affiche sur la sortie standard ces combinaisons calculées dans notre tête
    # (c'est à dire pour la séquence "ABCD" et k=2), avec une seule combinaison
    # par ligne, sous forme de chaine de caractères par exemple AC
    print("AB")
    print("CB")
    print("DB")
    print("AC")
    print("AD")
    print("CD")

    # affiche sur la sortie standard une ligne contenant EXACTEMENT
    # la chaîne de caractère suivante :
    #   Résultats calculés par recupere_combinaisons_2("ABCD")
    print('Résultats calculés par recupere_combinaisons_2("ABCD")')

    # effectue l'appel à recupere_combinaisons_2('ABCD'), puis affiche sur la
    # sortie standard les combinaisons renvoyées par cet appel, avec une
    # seule combinaison par ligne. Une combinaison étant un tuple, on vous
    # demande pour l'affichage de passer directement ce tuple à la fonction
    # print, c'est à dire de ne faire aucun formatage. La combinaison AC sera
    # donc affichée de la façon suivante : ('A', 'C')
    combinaisons=recupere_combinaisons_2("ABCD")
    for ele in combinaisons:
        print(ele)

    # affiche sur la sortie standard une ligne vide
    print("")

    # affiche sur la sortie standard une ligne contenant EXACTEMENT
    # la chaîne de caractère suivante :
    #   Résultats calculés dans ma tête pour la séquence [0, 1, 2, 3, 4] et k=3
    print("Résultats calculés dans ma tête pour la séquence [0, 1, 2, 3, 4] et k=3")

    # affiche sur la sortie standard ces combinaisons calculées dans notre tête
    # (c'est à dire pour la séquence [0, 1, 2, 3, 4] et k=3), avec une seule
    # combinaison par ligne, sous forme de chaine de caractères (par exemple 014)
    print("012")
    print("013")
    print("014")
    print("023")
    print("024")
    print("034")
    print("123")
    print("124")
    print("134")
    print("234")

    # affiche sur la sortie standard une ligne contenant EXACTEMENT
    # la chaîne de caractère suivante :
    #   Resultats calculés par recupere_combinaisons([0, 1, 2, 3, 4], 3)
    print("Resultats calculés par recupere_combinaisons([0, 1, 2, 3, 4], 3)")

    # effectue l'appel à recupere_combinaisons([0, 1, 2, 3, 4], 3), puis affiche
    # sur la sortie standard les combinaisons renvoyées par cet appel, avec
    # une seule combinaison par ligne. Une combinaison étant un tuple, on vous
    # demande pour l'affichage de passer directement ce tuple à la fonction print,
    # c'est à dire de ne faire aucun formatage. La combinaison 014 sera donc affichée
    # de la façon suivante : (0, 1, 4)
    combinaisons=recupere_combinaisons([O,1,2,3,4],3)

    # affiche sur la sortie standard une ligne vide
    for ele in combinaisons:
        print(ele)

    # effectue l'appel recupere_parametres(x) avec x récupéré en tant que premier
    # argument de la ligne de commande.
    parametres=recupere_parametres(sys.argv[1])

    # affiche sur la sortie standard une ligne contenant EXACTEMENT
    # la chaîne de caractère suivante :
    #   Résultats calculés par recupere_combinaisons sur les paramètres dans le ficher
    print("Résultats calculés par recupere_combinaisons sur les paramètres dans le ficher")

    # effectue l'appel à recupere_combinaisons en utilisant les paramètres
    # renvoyés par l'appel à recupere_parametres(x), puis affiche sur la sortie
    # standard les combinaisons renvoyées par cet appel, avec une seule combinaison par
    # ligne. Une combinaison étant un tuple, on vous demande pour l'affichage
    # de passer directement ce tuple à la fonction print, c'est à dire de ne
    # faire aucun formatage. La combinaison AC sera donc affichée de la façon
    # suivante : ('A', 'C')
    combinaisons=recupere_combinaisons(parametres[0],parametres[1])
    for ele in combinaisons:
        print(ele)

def recupere_parametres(filename):
    """Renvoie un tuple à deux entrées contenant la séquence et le paramètre k,
    DANS CET ORDRE lus à partir du fichier passé en paramètre.

    Spécifications PRÉCISES (pensons aux tests automatiques) sur le format du fichier :
       - la première ligne contient le nombre k
       - la seconde contient le nombre d'éléments dans la séquence
         qui suit, ce nombre est forcément un nombre pair et on le note nb_elems
       - nb_elems/2 lignes, contenant chacune deux chaînes de caractères
         séparées par une virgule
    """
    k=readline(filename)
    k.strip("\n")
    nb_elems=readline(filename)
    nb_elems.strip("\n")
    return (k,nb_elems)

def recupere_combinaisons_2(sequence):
    """"Renvoie toutes les combinaisons de taille 2 de la séquence donnée.

    Spécifications PRÉCISES (pensons aux tests automatiques) :
       - les combinaisons renvoyées sont représentées par une `list` de `tuple`.
    """
    res=[]
    for i in range(len(sequence)-1):
        for j in range(i+1,len(sequence)):
            res.append((sequence[i],sequence[j]))
    return res


def renverse(sequence):
    """Renvoie une nouvelle séquence qui est la séquence donnée à l'envers."""
    newSequence=[]
    for i in range(0,len(sequence),-1):
        newSequence.append(sequence[i])
    return res

def recupere_combinaisons(sequence, k):

    """"Renvoie toutes les combinaisons de taille k de la sequence donnée.

    Attention, cette fonction est difficile à implémenter.
    Il est vivement conseillé de réfléchir à votre algorithme sur le papier
    avant de se lancer dans le code.
    La fonction `renverse` sera normalement utilisée.

    Spécifications PRÉCISES (pensons aux tests automatiques) :
       - les combinaisons renvoyées sont représentées par une `list` de `tuple`.
    """
    if k==2:
        return recupere_combinaisons(sequence)
    else:
        combinaisons_avant=recupere_combinaisons(sequence,k-1)
        res=[]
        for ele in sequence:
            for comb in combinaisons_avant:
                if not ele in comb:
                    new=comb+[(comb[-1][1],ele)]
                    if not new in res:
                        res.append(new)
        return new  

def affiche_nombre_combinaisons(n,k):
    """Affiche le nombre de k-combinaisons du séquence de taille n.

    Faire un peu de dénombrement, ça fait toujours plaisir non ?

    Spécifications PRÉCISES (pensons aux tests automatiques) :
       - l'affichage se fera en fonction de n, la taille de la séquence,
         et du paramètre k
       - utiliser UNIQUEMENT des caractères du pavé numérique de votre
         clavier, les lettres `n` et `k` et des caractères de ponctuation
         si besoin.
    """
    res=1
    compteur=0
    while k-compteur!=0:
        res*=n-compteur
    return res

# APPELER ICI la fonction teste() dans le cas ou le programme
# est invoqué comme programme principal.
if __name__ == "__main__":
    teste()