package robot;

import map.*;

import java.util.*;
import event.Chemin;

/**
 * La classe Drone est une extension de la classe Robot
 */
public class Drone extends Robot {

	/** constructeur de base */
	public Drone(Case emplacement) {
		super(emplacement, 100, 10000, 1800, 30);
	}

	/** constructeur si on veut une certaine vitesse */
	public Drone(Case emplacement, double vitesse) {
		super(emplacement, vitesse, 10000, 1800, 30);
		if (vitesse > 150)
			vitesseMax = 150;
	}

	@Override
	public void setPosition(Case lieu) {
		position = lieu;
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
		nbLitres = 0;
	}

	@Override
	public void remplirReservoir() {
		if (!(position.getNature() == NatureTerrain.EAU)) {
			System.out.println("ne peux pas remplir si la case n'est pas de l'eau");
		} else {
			nbLitres = tailleReservoir;
		}
	}

	@Override
	public Robot clone() {
		return new Drone(position, vitesseMax);
	}

	@Override
	public double tempsDeTrajetDirect(Carte map, Case s1, Case s2) {
		double temps = (double) (map.tailleCases / ((getVitesse() * 1000) / 3600)); // en secondes
		return temps;
	}

	@Override
	public Map<Direction, Case> successeursPossibles(Case c, Carte map) {
		return map.getListeVoisin(c, map);
	}

	@Override
	public boolean peutEtre(Case s) {
		return true;
	}

	@Override
	public Chemin eauProche(Carte map, double temps) {
		Chemin res = this.plusCourtChemin(this.getPosition(), map.getCase(1, 1), map, temps);
		int tempsMin = 1000000;
		for (int i = 0; i < map.getNbLignes(); i++) {
			for (int j = 0; j < map.getNbColonnes(); j++) {
				Case lieu = map.getCase(i, j);
				if (lieu.getNature() == NatureTerrain.EAU) {
					Chemin ch = this.plusCourtChemin(this.getPosition(), lieu, map, temps);
					// System.out.println("Chemin calculé=" + ch);
					if (ch.chemin.lastKey() < tempsMin) {
						tempsMin = ch.chemin.lastKey().intValue();
						res = ch;
					}
				}
			}
		}
		// System.out.println(res);
		return res;
	}
}
