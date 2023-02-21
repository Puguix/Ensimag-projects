package robot;

import map.*;
import java.util.*;

/**
 * La classe RobotAChenille est une extansion de la classe RobotTerrestre
 */
public class RobotAChenille extends RobotTerrestre {

	/** constructeur de base */
	public RobotAChenille(Case emplacement) {
		super(emplacement, 60, 2000, 300, 8);
	}

	/** constructeur si on veut spécifier la vitesse */
	public RobotAChenille(Case emplacement, double vitesse) {
		super(emplacement, vitesse, 2000, 300, 8);
		if (vitesse > 80)
			vitesseMax = 80;
	}

	@Override
	public void setPosition(Case lieu) {
		if (!peutEtre(lieu)) {
			System.out.print("ne peut pas être sur cette case\n");
		} else {
			position = lieu;
		}
	}

	@Override
	public double getVitesse() {
		return position.getNature() == NatureTerrain.FORET ? vitesseMax / 2 : vitesseMax;
	}

	@Override
	public double getVitesse_case(Case c) {
		return c.getNature() == NatureTerrain.FORET ? vitesseMax / 2 : vitesseMax;
	}

	@Override
	public void deverserEau(int vol) {
		vol = ((vol / 100) + 1) * 100;
		if (!(nbLitres >= vol)) {
			nbLitres = 0;
		} else {
			nbLitres -= vol;
		}
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
			Case case_suiv = voisins.get(suiv);
			if (case_suiv.getNature() == NatureTerrain.EAU || case_suiv.getNature() == NatureTerrain.ROCHE) {
				v.remove(suiv);
			}
		}
		return v;
	}

	@Override
	public boolean peutEtre(Case s) {
		return !(s.getNature() == NatureTerrain.EAU || s.getNature() == NatureTerrain.ROCHE);
	}

	@Override
	public Robot clone() {
		return new RobotAChenille(position, vitesseMax);
	}

}
