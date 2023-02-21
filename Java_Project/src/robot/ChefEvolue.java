package robot;

import java.util.Map;
import java.util.NavigableMap;

import javax.swing.text.Style;

import event.ArriverRobot;
import event.BougerRobot;
import event.ExecutionStrategieChef;
import event.RemplirRobot;
import event.VerserEauIntelligent;
import io.DonneesSimulation;
import map.*;
import tests.Simulateur;

public class ChefEvolue {

    private static Simulateur simu;
    private static int interval;

    /**
     * 
     * @param simu le simulateur de la simulation
     */

    public static void main(Simulateur sim, int n) {
        simu = sim;
        interval = n;
        run();
    }

    public static void run() {

        // System.out.println("run");

        DonneesSimulation donnees = simu.getDonnees();

        // test si les robots ont besoin d'aller se remplir et le cas échéant trouve la
        // case où ils peuvent se remplir la plus rapide d'accès et les y envoie
        for (Robot robot : donnees.getRobots()) {
            if (robot.getNblitres() == 0 && !robot.estAffecte()) {
                if (robot instanceof RobotARoue) {
                }
                robot.switchState();
                if (robot instanceof RobotTerrestre) {
                    boolean peutSeRemplir = false;
                    // System.out.println(robot.getPosition());
                    for (Map.Entry c : donnees.getCarte().getListeVoisin(robot.getPosition(), donnees.getCarte())
                            .entrySet()) {
                        // System.out.println((Case) c.getValue());
                        if (((Case) c.getValue()).getNature() == NatureTerrain.EAU) {
                            simu.ajouteEvenement(new RemplirRobot(robot, simu.getDate() + robot.getTempsRemplissage()));
                            simu.ajouteEvenement(new ArriverRobot(robot, simu.getDate() + robot.getTempsRemplissage()));
                            peutSeRemplir = true;
                            // System.out.println("on est dans le if");
                            break;
                        }
                    }
                    if (peutSeRemplir) {
                        continue;
                    }
                }
                NavigableMap<Double, Case> route = (robot.eauProche(donnees.getCarte(), simu.getDate())).chemin;
                // System.out.println("route a prendre:" + route);
                for (Map.Entry chemin : route.entrySet()) {
                    simu.ajouteEvenement(
                            new BougerRobot(robot, (Case) chemin.getValue(),
                                    ((Double) chemin.getKey()).intValue()));
                }
                simu.ajouteEvenement(
                        new RemplirRobot(robot, route.lastKey().intValue() + robot.getTempsRemplissage()));
                simu.ajouteEvenement(
                        new ArriverRobot(robot, route.lastKey().intValue() + robot.getTempsRemplissage()));
            }

        }

        for (Incendie feu : donnees.getIncedies()) {
            // System.out.println("feu");

            if (feu.getNbLitres() == 0) {
                continue;
            }

            int dateMin = 86400 * 24; // plus l'infini (ici un jour)
            Robot chosenRobot = null;

            for (Robot robot : donnees.getRobots()) {
                if (robot.estAffecte()) {
                    // System.out.println("robot affecté");
                    continue;
                }
                try {
                    // System.out.println("robot pas affecté");
                    NavigableMap<Double, Case> route = robot.plusCourtChemin(robot.getPosition(), feu.getPosition(),
                            donnees.getCarte(), simu.getDate()).chemin;
                    if (route.lastKey() < dateMin) {
                        dateMin = route.lastKey().intValue();
                        chosenRobot = robot;
                    }
                } catch (Exception e) {
                    continue;
                }
            }

            if (chosenRobot != null) {
                chosenRobot.switchState();
                NavigableMap<Double, Case> route = chosenRobot.plusCourtChemin(chosenRobot.getPosition(),
                        feu.getPosition(),
                        donnees.getCarte(), (double) simu.getDate()).chemin;
                // if (chosenRobot instanceof RobotARoue) {
                // System.out.println(route);
                // }
                for (Map.Entry chemin : route.entrySet()) {
                    // System.out.println(
                    // ((Case) chemin.getValue()).getLigne() + ", " + ((Case)
                    // chemin.getValue()).getColonne());
                    simu.ajouteEvenement(
                            new BougerRobot(chosenRobot, (Case) chemin.getValue(),
                                    ((Double) chemin.getKey()).intValue()));
                }
                int dateFin = route.lastKey().intValue();
                simu.ajouteEvenement(new VerserEauIntelligent(chosenRobot, feu, chosenRobot.getNblitres(),
                        dateFin + chosenRobot.getTempsVersement()));
                simu.ajouteEvenement(new ArriverRobot(chosenRobot, dateFin + chosenRobot.getTempsVersement()));
            }
        }

        // si les incendies sont pas tous éteinds, on refait la stratégie un interval
        // plus tard
        boolean fini = true;

        for (Incendie feu : donnees.getIncedies()) {
            if (feu.getNbLitres() != 0) {
                fini = false;
                break;
            }
        }
        if (!fini) {
            simu.ajouteEvenement(new ExecutionStrategieChef(simu.getDate() + interval));
        }
    }
}
