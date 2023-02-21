package event;

import robot.ChefEvolue;

public class ExecutionStrategieChef extends Evenement {

    public ExecutionStrategieChef(long d) {
        super(d);
    }

    @Override
    public void execute() {
        ChefEvolue.run();
    }

}
