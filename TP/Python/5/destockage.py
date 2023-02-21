#!/usr/bin/env python3

var1 = "123"
var2 = [1, 2, 3]
var3 = (1, 2, 3)
var4 = range(1, 4)
var5 = ["toto", range(3), ["t", "o", "t", "o"]]
var6 = ([1, 2, 3], [4, 5, 6])
var7 = [[[1, 2], [3, 4]], [[5, 6]]]

for car in var1:
    print(car)

for ele in var2:
    print(ele)

for ele in var3:
    print(ele)

for i in var4:
    print(i)

for ele in var5:
    for el in ele:
        print(el)

for ele in var6:
    for el in ele:
        print(el)

for ele in var7:
    for el in ele:
        for i in el:
            print(i)
