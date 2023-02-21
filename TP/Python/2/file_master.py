#!/usr/bin/env python3

toto = open("toto.txt", 'w')
toto.write('test \n')
print("woaw", file=toto)
toto.close()