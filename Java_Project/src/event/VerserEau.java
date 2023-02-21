package event;

import map.*;
import robot.*;

/** VerserEau est une extansion de la classe Evenement */
public class VerserEau extends Evenement {

	private Robot robot;
	private int quantite;
	private Incendie feu;

	public VerserEau(Robot r, Incendie incendie, int litres, long date) {
		super(date);
		robot = r;
		quantite = litres;
		feu = incendie;
	}

	public Robot getRobot() {
		return robot;
	}

	public int getQuantite() {
		return quantite;
	}

	public Incendie getIncendie() {
		return feu;
	}

	@Override
	public void execute() {
		robot.deverserEau(quantite);
		feu.eteindre(quantite);
	}

}
