#!/usr/bin/env python3

"""Un programme pour comprendre la notion de point d'entrée en python"""

def fait_un_bidule():
    """Affiche un message de bienvenue"""
    print("ترحيب  en BPI")

message = "bienvenue"

def fait_un_truc():
    """Affiche un message de bienvenue"""
    print(message + " à l'Ensimag")

print("on vous souhaite la " + message)

def fait_un_autre_truc():
    """Affiche un autre message de bienvenue"""
    print(message + "à Grenoble, la plus belle ville du monde")

def main():
    """LA fonction principale"""
    print("Je suis le MAIN, et j'appelle ... fait_un_autre_truc")
    fait_un_autre_truc()

message = "welcome"

fait_un_bidule()

fait_un_truc()
