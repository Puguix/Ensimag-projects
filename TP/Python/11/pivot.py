#!/usr/bin/env python3

def pivote(tab, i):
    tab1,tab2=[],[]
    for ele in tab[:i]+tab[i+1:]:
        if ele>tab[i]:
            tab2.append(ele)
        else:
            tab1.append(ele)
    return tab1,tab2

def pivot(tab, i):
    tab[i],tab[0]=tab[0],tab[i]
    i=0
    compteur_fin=0
    for k in range(1,len(tab)):
        if tab[k-compteur_fin]<=tab[i]:
            tab[k-compteur_fin],tab[i]=tab[i],tab[k-compteur_fin]
            i+=1
        else:
            tab[k-compteur_fin],tab[-1-compteur_fin]=tab[-1-compteur_fin],tab[k-compteur_fin]
            compteur_fin+=1
    
l=[3,0,10,1,6,9,5,3,9,0,5,8,9,8,4,2,0,9,6,2]
pivot(l,0)
print(l)
