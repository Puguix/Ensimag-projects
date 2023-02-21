#!/usr/bin/env python3
"""Un exemple d'utilisation d'une boucle while avec continue"""

def demande_prix():
    """Demande à l'utilisateur un prix"""
    print("Quel est votre proposition ?")
    return int(input())

prix_propose = demande_prix()
n=1

# Tant que (== while en anglais, ça tombe bien)
# l'utilisateur n'a pas trouvé le juste prix
while prix_propose != 42:

    if n==4:
        break

    # Traitement spécial si le prix proposé est négatif
    if prix_propose < 0:
        print("Comment ? Vous me pensez assez tordu pour avoir choisi un prix négatif ???")
        prix_propose = demande_prix()
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
    n+=1

# Quand on arrive ici, l'utilisateur
# a trouvé
print("c'est trouvé !")
