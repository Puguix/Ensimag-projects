package robot;

import map.*;
import java.util.*;

/**
 * La classe RobotAPatte est une extansion de la classe RobotTerrestre.
 * Le réservoir est infini, on le définit à 0.
 * Pas besoin de remplir le réservoir donc dureeRemplissage = 0
 */
public class RobotAPatte extends RobotTerrestre {

	/** constructeur de base */
	public RobotAPatte(Case emplacement) {
		super(emplacement, 30, 1, 0, 1);
	}

	/** constructeur si on veut préciser la vitesse */
	public RobotAPatte(Case emplacement, double vitesse) {
		super(emplacement, vitesse, 1, 0, 1);
	}

	@Override
	public void setPosition(Case lieu) {
		if (lieu.getNature() != NatureTerrain.EAU) {
			position = lieu;
		} else {
			System.out.println("ne peut pas être sur cette case\n");
		}
	}

	@Override
	public double getVitesse() {
		if (position.getNature() == NatureTerrain.ROCHE) {
			return 30;
		}
		return vitesseMax;
	}

	@Override
	public double getVitesse_case(Case c) {
		if (c.getNature() == NatureTerrain.ROCHE) {
			return 30;
		}
		return vitesseMax;
	}

	@Override
	public void deverserEau(int vol) {
	}

	@Override
	public Robot clone() {
		return new RobotAPatte(position, vitesseMax);
	}

	@Override
	public Map<Direction, Case> successeursPossibles(Case c, Carte map) {
		Map<Direction, Case> voisins = map.getListeVoisin(c, map);
		Map<Direction, Case> v = new HashMap<Direction, Case>();
		v.putAll(voisins);
		Collection<Direction> dir = voisins.keySet();
		Iterator<Direction> it = dir.iterator();
		while (it.hasNext()) { // on enlève les voisins qui ont un terrain non praticable pour le robot
			Direction suiv = it.next();
			Case case_suiv = v.get(suiv);
			if (case_suiv.getNature() == NatureTerrain.EAU) {
				v.remove(suiv);
			}
		}
		return v;
	}

	@Override
	public boolean peutEtre(Case s) {
		return !(s.getNature() == NatureTerrain.EAU);
	}
}
