#!/usr/bin/env python3

class Cellule:

    def __init__(self,valeur,suivant):
            self.valeur=valeur
            self.suivant=suivant

    def __str__(self):
        return "cellule_"+str(self.valeur)