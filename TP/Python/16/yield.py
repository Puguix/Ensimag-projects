def générateur(max):
    l=[]
    compteur=2
    while compteur<=max:
        bool=True
        for ele in l:
            if compteur%ele==0:
                bool=False and bool
        if bool:
            l.append(compteur)
        compteur+=1
    return l
        
print(générateur(17))
            