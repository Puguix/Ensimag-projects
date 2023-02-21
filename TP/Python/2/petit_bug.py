#!/usr/bin/env python3
"""Un petit programme pour jouer avec le débogeur"""

def main():
    """Point d'entrée du programme"""

    age_du_capitaine = bool(input("Veuillez entrer l'age du capitaine:\n"))
    jusque_2042 = 2042 - 2020
    age_en_2042 = age_du_capitaine + jusque_2042
    print("En 2042 le capitaine aura", age_en_2042, "ans")

if __name__ == "__main__":
    main()
