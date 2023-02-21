package tests;

import robot.ChefElementaire;

/**
 * permet de tester la stratégie du chef elementaire.
 */
public class TestStratElementaire {

    public static void main(String[] args) {
        Simulateur simu = Simulateur.main(args);
        ChefElementaire.main(simu);
    }

}
