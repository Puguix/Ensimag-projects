package robot;

import java.util.Map;
import java.util.NavigableMap;

import event.BougerRobot;
import event.VerserEau;
import io.DonneesSimulation;
import map.*;
import tests.Simulateur;

public class ChefElementaire {

    /**
     * 
     * @param simu le simulateur de la simulation
     */
    public static void main(Simulateur simu) {

        DonneesSimulation donnees = simu.getDonnees();

        for (Incendie feu : donnees.getIncedies()) {
            if (feu.estAffecte()) {
                continue;
            }

            for (Robot robot : donnees.getRobots()) {
                if (robot.estAffecte()) {
                    continue;
                }
                try {
                    NavigableMap<Double, Case> route = robot.plusCourtChemin(robot.getPosition(), feu.getPosition(),
                            donnees.getCarte(), simu.getDate()).chemin;
                    // System.out.println(route);
                    robot.switchState();
                    for (Map.Entry chemin : route.entrySet()) {
                        simu.ajouteEvenement(
                                new BougerRobot(robot, (Case) chemin.getValue(),
                                        ((Double) chemin.getKey()).intValue()));
                    }
                    int dateFin = route.lastKey().intValue();
                    simu.ajouteEvenement(
                            new VerserEau(robot, feu, robot.getNblitres(), dateFin + robot.getTempsVersement()));
                    break;
                } catch (Exception e) {
                    continue;
                }
            }
        }
    }
}
