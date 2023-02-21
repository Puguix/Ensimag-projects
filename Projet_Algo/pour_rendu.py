#!/usr/bin/env python3

import random as rd
import time
import statistics

import main as prog
import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as sci
import tracemalloc
import math
from geo.point import Point

etalement_y = 1000
pour_afficher1 = None
pour_afficher2 = None
def generation_uniform(n):
    """
    generation de point uniforme
    """
    points = [Point((rd.random()*1000, rd.random()*etalement_y)) for _ in range(n)]
    return points

def generation_gaussienne(n, mu=0, s=1):
    """
    generation suivant une gaussienne
    """
    points = [Point((rd.gauss(mu, s)*1000, rd.gauss(mu, s)*etalement_y)) for _ in range(n)]
    global pour_afficher1
    pour_afficher1 = points
    return points

def generation_gaussienne2(n, mu=0, s=1):
    """
    generation suivant une gaussienne
    """
    points = [Point((rd.gauss(mu, s)*1000, rd.gauss(mu, s)*1000)) for _ in range(n//2)] + [Point((rd.gauss(2200, 25), rd.gauss(2200, 25))) for _ in range(n//2)]
    global pour_afficher2
    pour_afficher2 = points
    return points

def generation_gaussienne3(n, mu=0, s=1):
    """
    generation suivant une gaussienne
    """
    points = [Point((rd.gauss(mu, s)*1000, rd.gauss(mu, s)*1000)) for _ in range(n//2)] + [Point((rd.gauss(2200, 25), rd.gauss(2200, 25))) for _ in range(n//2)]
    rd.shuffle(points)
    global pour_afficher2
    pour_afficher2 = points
    return points

def mesure_perf_temps(N, m, fonction_gen, fonction_solve):
    mes = []
    for n in N:
        temps = []
        for _ in range(m):
            points = fonction_gen(n)
            t0 = time.perf_counter()
            fonction_solve(points)
            t1 = time.perf_counter()
            prog.clean()
            temps.append(t1-t0)
        mes.append(temps)
    return mes

def mesure_perf_mem(N, m, fonction_gen, fonction_solve):
    mes = []
    for n in N:
        mem = []
        for _ in range(m):
            points = fonction_gen(n)
            tracemalloc.start()
            fonction_solve(points)
            f_size, f_peak = tracemalloc.get_traced_memory()
            tracemalloc.stop()
            prog.clean()
            mem.append(f_peak)
        mes.append(mem)
    return mes


def afficheur(N, T0, title, legend, color="lightsteelblue", ecolor="royalblue", new_fig=False, y_lab="T (s)"):
    t0 = [statistics.mean(t) for t in T0]
    err_lower0 = [min(t) for t in T0]
    err_upper0 = [max(t) for t in T0]
    err = [err_lower0, err_upper0]


    if new_fig:
        plt.figure()
    plt.errorbar(N, t0, yerr=err, color=color, ls="dashed", marker='x',
                 ecolor=ecolor, elinewidth=2, uplims=True, lolims=True,
                 label=legend)
    plt.grid(True, which="both", linestyle="--")
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel("N")
    plt.ylabel(y_lab)
    plt.title(title)

def mesure_temps():
    N = [i*10**k for k in range(2, 4) for i in range(1, 10)]
    #N = [500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000]
    #N = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000]
    T2 = mesure_perf_temps(N, 10, generation_gaussienne2, prog.distance_non_rec_mieux)
    T1 = mesure_perf_temps(N, 10, generation_gaussienne3, prog.distance_non_rec_mieux)


    afficheur(N, T2, "gauss", "Deux nuage trié", new_fig=True)
    afficheur(N, T1, "gauss", "Deux nuage non trié", color="lightcoral", ecolor="brown")
    plt.legend(loc="upper left")



    TM = [statistics.mean(t) for t in T2]
    LN = [math.log(n) for n in N]
    LT = [math.log(t) for t in TM]
    plt.plot(LN, LT)
    a, b, r, p_value, std_err = sci.linregress(LN, LT)
    #a=0.9681909687665758, b=-11.065936290773635, r=0.9963108574174353, p_value=1.7051154197151474e-18, std_err=0.020848891899410166
    #a=1.0034854245524214, b=-11.431600114450163, r=0.9990096768773973, p_value=4.636770492685073e-23, std_err=0.011173192736173641
    print(f"a={a}, b={b}, r={r}, p_value={p_value}, std_err={std_err}")
    plt.show()

def mesure_mem():
    N = [i*10**k for k in range(2, 3) for i in range(1, 10)]
    M0 = mesure_perf_mem(N, 10, generation_uniform, prog.distance_non_rec_mieux)
    print("1")
    M1 = mesure_perf_mem(N, 10, generation_uniform, prog.calcul_min_naive)
    print("2")
    M2 = mesure_perf_mem(N, 10, generation_gaussienne, prog.distance_non_rec_mieux)

    afficheur(N, M0, "uniform", "Optimisé", new_fig=True, y_lab="mem (o)")
    afficheur(N, M1, "uniform", "Naif", color="lightcoral", ecolor="brown", y_lab="mem (o)")
    plt.legend(loc="upper left")

    afficheur(N, M0, "Optimisé", "Uniforme", new_fig=True, y_lab="mem (o)")
    afficheur(N, M2, "Optimisé", "Gaussien", color="lightcoral", ecolor="brown", y_lab="mem (o)")
    plt.legend(loc="upper left")

    plt.show()
def main():
    mesure_temps()

main()
