#!/usr/bin/env python3
"""Un exemple d'utilisation d'une boucle while"""

def demande_prix():
    """Demande un prix à l'utilisateur"""
    print("Quel est votre proposition ?")
    return int(input())

prix_propose = demande_prix()

# Tant que (== while en anglais, ça tombe bien)
# l'utilisateur n'a pas trouvé le juste prix
while prix_propose != 42:

    #si prix négatif on sort
    if prix_propose<0:
        continue

    # On lui indique de quel côté il
    # se situe
    if prix_propose > 42:
        print("c'est moins !")
    else:
        print("c'est plus !")

    # On lui demande de faire une
    # nouvelle proposition
    prix_propose = demande_prix()

print("Comment? Vous me pensez assez tordu pour proposer un nombre négatif?")

# Quand on arrive ici, l'utilisateur
# a trouvé
if prix_propose==42:
    print("c'est trouvé !")
