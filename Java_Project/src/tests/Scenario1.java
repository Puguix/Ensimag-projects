package tests;

import robot.*;
import map.*;
import event.*;
import io.DonneesSimulation;

/**
 * Le second scénario suggéré par le sujet
 */
public class Scenario1 {

    public static void main(String[] args) {
        Simulateur simu = Simulateur.main(args);
        DonneesSimulation donnees = simu.getDonnees();
        long date = 0;

        RobotARoue robot = null;
        for (Robot r : donnees.getRobots()) {
            if (r instanceof RobotARoue) {
                robot = (RobotARoue) r;

                Case src = robot.getPosition();
                Case voisin = donnees.getCarte().getVoisin(src, Direction.NORD);
                date += donnees.getCarte().getTailleCases() / robot.getVitesse();
                Evenement un = new BougerRobot(robot, voisin, date);
                simu.ajouteEvenement(un);

                Incendie feu = null;
                for (Incendie i : donnees.getIncedies()) {
                    if (i.getPosition() == voisin) {
                        feu = i;

                        date += robot.getTempsVersement() * robot.getNblitres() / 100;
                        Evenement deux = new VerserEau(robot, feu, robot.getNblitres(), 10);
                        simu.ajouteEvenement(deux);

                        src = voisin;
                        voisin = donnees.getCarte().getVoisin(src, Direction.OUEST);
                        date += donnees.getCarte().getTailleCases() / robot.getVitesse();
                        Evenement trois = new BougerRobot(robot, voisin, date);
                        simu.ajouteEvenement(trois);

                        src = voisin;
                        voisin = donnees.getCarte().getVoisin(src, Direction.OUEST);
                        date += donnees.getCarte().getTailleCases() / robot.getVitesse();
                        Evenement quatre = new BougerRobot(robot, voisin, date);
                        simu.ajouteEvenement(quatre);

                        date += robot.getTempsRemplissage();
                        Evenement cinq = new RemplirRobot(robot, date);
                        simu.ajouteEvenement(cinq);

                        src = voisin;
                        voisin = donnees.getCarte().getVoisin(src, Direction.EST);
                        date += donnees.getCarte().getTailleCases() / robot.getVitesse();
                        Evenement six = new BougerRobot(robot, voisin, date);
                        simu.ajouteEvenement(six);

                        src = voisin;
                        voisin = donnees.getCarte().getVoisin(src, Direction.EST);
                        date += donnees.getCarte().getTailleCases() / robot.getVitesse();
                        Evenement sept = new BougerRobot(robot, voisin, date);
                        simu.ajouteEvenement(sept);

                        date += robot.getTempsVersement() * robot.getNblitres() / 100;
                        Evenement huit = new VerserEau(robot, feu, robot.getNblitres(), date);
                        simu.ajouteEvenement(huit);
                        break;
                    }
                }

                break;
            }
        }
    }
}
