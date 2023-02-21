#!/usr/bin/env python3

from svg import *

p1=Point(5,6)
p2=Point(6,7)
points=[p1,p2]
def test(pa,pb):
    res=""
    points=[pa,pb]
    for p in points:
        res+=str(p.x),',',str(p.x)," "
    return res

print(test(p1,p2))