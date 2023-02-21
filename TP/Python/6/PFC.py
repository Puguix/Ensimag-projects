#!/usr/bin/env python3
"""Papier caillou ciseaux"""

import random

def main():
    """point d'entrée du programme"""

    random.seed()

    plays = ["paper", "rock", "scissors"]

    while True:

        player = input("paper, rock, scissors ?\n")
        computer = plays[random.randint(0, 2)]

        if player == computer:
            print("Égalité!")
        elif player == "rock":
            if computer == "paper":
                print("You lose!", computer, "covers", player)
            else:
                print("You win!", player, "smashes", computer)
        elif player == "paper":
            if computer == "scissors":
                print("You lose!", computer, "cut", player)
            else:
                print("You win!", player, "covers", computer)
        elif player == "scissors":
            if computer == "rock":
                print("You lose...", computer, "smashes", player)
            else:
                print("You win!", player, "cut", computer)
        else:
            print("Invalid play. Check your spelling please !")

main()
