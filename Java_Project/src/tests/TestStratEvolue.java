package tests;

import robot.ChefEvolue;

/**
 * permet de tester la stratégie du chef evolue. n ci-dessous représente
 * l'intervalle auquel le chef exécute sa stratégie
 */
public class TestStratEvolue {

    private static int n = 60;

    public static void main(String[] args) {
        Simulateur simu = Simulateur.main(args);
        ChefEvolue.main(simu, n);
    }

}
