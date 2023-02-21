package event;

import robot.*;

/** RemplirRobot est une extansion de la classe Evenement */
public class RemplirRobot extends Evenement {

	private Robot robot;

	public RemplirRobot(Robot r, long d) {
		super(d);
		robot = r;
	}

	public Robot getRobot() {
		return robot;
	}

	@Override
	public void execute() {
		robot.remplirReservoir();
	}

}
