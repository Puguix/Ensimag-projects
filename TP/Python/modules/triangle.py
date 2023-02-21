#!/usr/bin/env python3

from random import randint as rd
from math import sin,cos
from svg import Point

def triangle_aleatoire(x1,x2,y1,y2):
    l=[]
    for _ in range(3):
        l.append(rd(x1,x2))
        l.append(rd(y1,y2))
    return ( Point(l[0],l[1]), Point(l[2],l[3]), Point(l[4],l[5]) )

def tourne_triangle_autour(triangle,pc,a):
    lp=[]
    for p in triangle:
        lp.append( Point( (p.x-pc.x)*cos(a) - (p.y-pc.y)*sin(a) + pc.x , (p.x-pc.x)*sin(a) - (p.y-pc.y)*cos(a) + pc.y ) )
    return (lp[0],lp[1],lp[2])

