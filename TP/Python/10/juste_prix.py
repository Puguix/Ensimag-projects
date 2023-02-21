#!/usr/bin/env python3

import os
import sys


def main():
    if len(sys.argv) != 2 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
        print("utilisation:", sys.argv[0], "nombre")
        sys.exit(1)

    n=int(sys.argv[1])
    if n==42:
        print("C'est gagné")
    elif n<42:
        print("C'est plus")
    else:
        print("C'est moins")

if __name__ == "__main__":
    main()
