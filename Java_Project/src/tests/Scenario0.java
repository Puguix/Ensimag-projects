package tests;

import io.DonneesSimulation;
import robot.*;
import map.*;
import event.*;

/**
 * Le premier scénario suggéré par le sujet. Il crash car un robot tente de
 * sortir de la carte
 */
public class Scenario0 {

	public static void main(String args[]) throws Exception {
		Simulateur simu = Simulateur.main(args);
		DonneesSimulation donnees = simu.getDonnees();
		long date = 0;

		Drone drone = null;
		for (Robot robot : donnees.getRobots()) {
			if (robot instanceof Drone) {
				drone = (Drone) robot;

				Case src = drone.getPosition();
				Case voisin = donnees.getCarte().getVoisin(src, Direction.NORD);
				date += donnees.getCarte().getTailleCases() / drone.getVitesse();
				Evenement un = new BougerRobot(drone, voisin, date);
				simu.ajouteEvenement(un);

				src = voisin;
				voisin = donnees.getCarte().getVoisin(src, Direction.NORD);
				date += donnees.getCarte().getTailleCases() / drone.getVitesse();
				Evenement deux = new BougerRobot(drone, voisin, date);
				simu.ajouteEvenement(deux);

				src = voisin;
				voisin = donnees.getCarte().getVoisin(src, Direction.NORD);
				date += donnees.getCarte().getTailleCases() / drone.getVitesse();
				Evenement trois = new BougerRobot(drone, voisin, date);
				simu.ajouteEvenement(trois);

				src = voisin;
				voisin = donnees.getCarte().getVoisin(src, Direction.NORD);
				date += donnees.getCarte().getTailleCases() / drone.getVitesse();
				Evenement quatre = new BougerRobot(drone, voisin, date);
				simu.ajouteEvenement(quatre);

				break;
			}
		}
	}
}
