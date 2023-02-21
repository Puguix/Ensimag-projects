package tests;

import robot.*;
import map.*;
import event.*;
import io.DonneesSimulation;
import java.util.*;

public class Scenario2 {

	public static void main(String[] args) throws Exception {
		Simulateur simu = Simulateur.main(args);
		DonneesSimulation donnees = simu.getDonnees();
		long date = 0;

		for (Robot r : donnees.getRobots()) {
			if (r instanceof RobotARoue) {
				RobotARoue robot = (RobotARoue) r;

				Case src = robot.getPosition();
				Case arrivee = donnees.getCarte().getCase(2, 2);

				arrivee.successeurs = robot.successeursPossibles(arrivee, donnees.getCarte());
				src.successeurs = robot.successeursPossibles(src, donnees.getCarte());

				Chemin ch = robot.plusCourtChemin(src, arrivee, donnees.getCarte(), 0.0);

				NavigableMap<Double, Case> che = ch.chemin;
				Collection<Double> date_it = che.keySet();
				Iterator<Double> it = date_it.iterator();
				while (it.hasNext()) {
					Double d = it.next();
					Case voisin = che.get(d);
					System.out.print(voisin);
					date = date + 1;
					Evenement i = new BougerRobot(robot, voisin, date);
					simu.ajouteEvenement(i);
					robot.setPosition(voisin);
				}
			}
		}
	}
}
