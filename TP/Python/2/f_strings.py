#!/usr/bin/env python3

"""Illustration simple des f-strings."""

def test_fstrings():
    """Utilisation de f-strings pour afficher un message."""
    prenom = "Alexia"
    age = 7
    message_a_afficher = f"{prenom} a {age} ans"
    print(message_a_afficher)

if __name__ == "__main__":
    test_fstrings()
