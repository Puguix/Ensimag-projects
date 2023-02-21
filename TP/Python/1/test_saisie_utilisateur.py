#!/usr/bin/env python3

import saisie_utilisateur as su

prenom = su.demande_chaine()
age = su.demande_entier()
print("bonjour " + prenom +", " + str(age) + " ans")