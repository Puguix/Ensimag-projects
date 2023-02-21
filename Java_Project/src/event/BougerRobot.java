package event;

import robot.*;
import map.*;

/**
 * La classe BougerRobot permet de déplacer un robot au cours de la simulation.
 * C'est une extansion de la classe Evenement
 */
public class BougerRobot extends Evenement {

	private Robot robot;
	private Case position;

	public BougerRobot(Robot r, Case lieu, long date) {
		super(date);
		robot = r;
		position = lieu;
	}

	public Robot getRobot() {
		return robot;
	}

	public Case getPosition() {
		return position;
	}

	@Override
	public void execute() {
		robot.setPosition(position);
	}
}
