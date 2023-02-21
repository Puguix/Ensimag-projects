#!/usr/bin/env python3

from random import randint

hauteur,largeur=1000,1000 #devrait etre une entrée utilisateur

print("P2")
print(hauteur," ",largeur)
print("255")

m=min(largeur,hauteur)/2
r1,r2=randint(0,m),randint(0,m)
x1,x2,y1,y2=randint(0,largeur),randint(0,largeur),randint(0,hauteur),randint(0,hauteur)
while x1+r1 > largeur or x1-r1 < 0:
    x1=randint(0,largeur)
while x2+r2 > largeur or x2-r2 < 0:
    x2=randint(0,largeur)
while y1+r1 > largeur or y1-r1 < 0:
    y1=randint(0,hauteur)
while y2+r2 > largeur or y2-r2 < 0:
    y2=randint(0,hauteur)

def in_circle(x,y):
    return ((x-x1)**2+(y-y1)**2)**(1/2)<r1 or ((x-x2)**2+(y-y2)**2)**(1/2)<r2
    

for y in range(hauteur):
    l=""
    for x in range(largeur):
        if in_circle(x,y):
            l+=str(randint(0,255))+" "
        else:
            l+="255 "
    print(l)
