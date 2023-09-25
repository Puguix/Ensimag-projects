# Projet couverture de produits dérivés

_Groupe 1: Nils Depuille, Guilhem Stevant, Hicham Al Jaabari, Paul GAUTHIER_

Dans **src/** se trouvent nos fichiers .cpp et .hpp, notamment:

-   BlackSholesModel, contenant les méthodes asset(), shift_asset(), et simul_market()
-   MonteCarlo, contenant les méthodes price(), delta(), et profit_loss()
-   Option, classe virtuelle dont lesquelles vont dériver les différents types d'option
-   Basket, classe fille de Option pour l'option de type basket
-   Asian, classe fille de Option pour l'option asiatique
-   Performance, classe fille de Option pour l'option de performance
-   test_en_0.cpp, fichier de test des prix et des deltas en t=0
-   test_hedge.cpp, fichier de test de la couverture
