package event;

import robot.*;

/**
 * La classe ArriverRobot est une extansion de la classe evenement. Elle change
 * l'état du robot
 */
public class ArriverRobot extends Evenement {

	private Robot robot;

	public ArriverRobot(Robot r, long date) {
		super(date);
		robot = r;
	}

	public Robot getRobot() {
		return robot;
	}

	@Override
	public void execute() {
		robot.switchState();
	}
}
