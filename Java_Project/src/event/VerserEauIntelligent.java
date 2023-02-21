package event;

import map.*;
import robot.*;

/**
 * VerserEauIntelligent est une extansion de la classe Evenement. La différence
 * avec la version normale VerserEau est que le robot vérifie si l'incendie
 * n'est pas déjà éteind avant de verser l'eau
 */
public class VerserEauIntelligent extends Evenement {

    private Robot robot;
    private int quantite;
    private Incendie feu;

    public VerserEauIntelligent(Robot r, Incendie incendie, int litres, long date) {
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
        if (feu.getNbLitres() != 0) {
            robot.deverserEau(quantite);
            feu.eteindre(quantite);
        }
    }

}
