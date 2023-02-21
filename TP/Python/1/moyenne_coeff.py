#!/usr/bin/env python3

maths = (17, 9)
physique = (15, 6)
histoire = (4, 1)

def moyenne(t1, t2, t3):
    return (t1[0]*t1[1] + t2[0]*t2[1] + t3[0]*t3[1])/ (t1[1] + t2[1] + t3[1])

print(moyenne(maths, physique, histoire))