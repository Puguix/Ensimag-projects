package robot;

import map.*;
import java.util.*;

/**
 * La classe RobotARoue est une extansion de la classe RobotTerrestre
 */
public class RobotARoue extends RobotTerrestre {

	/** constructeur de base */
	public RobotARoue(Case emplacement) {
		super(emplacement, 80, 5000, 600, 5);
	}

	/** constructeur si on veut préciser la vitesse */
	public RobotARoue(Case emplacement, double vitesse) {
		super(emplacement, vitesse, 5000, 600, 5);
	}

	@Override
	public void setPosition(Case lieu) {
		if (peutEtre(lieu)) {
			position = lieu;
		} else {
			System.out.print(" ne peut pas être sur cette case\n");
		}
	}

	@Override
	public double getVitesse() {
		return vitesseMax;
	}

	@Override
	public double getVitesse_case(Case c) {
		return vitesseMax;
	}

	@Override
	public void deverserEau(int vol) {
		vol = ((vol / 100) + 1) * 100;
		if (nbLitres >= vol) {
			nbLitres -= vol;
		} else {
			nbLitres = 0;
		}
	}

	@Override
	public Robot clone() {
		return new RobotARoue(position, vitesseMax);
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
			if (case_suiv.getNature() == NatureTerrain.EAU || case_suiv.getNature() == NatureTerrain.ROCHE
					|| case_suiv.getNature() == NatureTerrain.FORET) {
				v.remove(suiv);
			}
		}
		return v;
	}

	@Override
	public boolean peutEtre(Case s) {
		return !(s.getNature() == NatureTerrain.EAU || s.getNature() == NatureTerrain.ROCHE
				|| s.getNature() == NatureTerrain.FORET);
	}

}
