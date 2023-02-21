package robot;

import java.util.Map;

import event.Chemin;
import map.*;

/**
 * La classe RobotTerrestre est une extansion de la classe Robot
 */
public abstract class RobotTerrestre extends Robot {

	/** constructeur de base */
	public RobotTerrestre(Case emplacement, double vitesse, int reservoir, int dureeRemplissage, int dureeVersement) {
		super(emplacement, vitesse, reservoir, dureeRemplissage, dureeVersement);
	}

	public double tempsDeTrajetDirect(Carte map, Case s1, Case s2) {
		double vitesse_s1 = getVitesse_case(s1);
		double vitesse_s2 = getVitesse_case(s2);
		double vitesse = (vitesse_s1 + vitesse_s2) / 2;
		double temps = (double) (map.tailleCases / ((vitesse * 1000) / 3600)); // en secondes
		return temps;
	}

	public void remplirReservoir() {
		nbLitres = tailleReservoir;
	}

	@Override
	public Chemin eauProche(Carte map, double temps) {
		Chemin res = this.plusCourtChemin(this.getPosition(), map.getCase(1, 1), map, temps);
		int tempsMin = 1000000;
		for (int i = 0; i < map.getNbLignes(); i++) {
			for (int j = 0; j < map.getNbColonnes(); j++) {
				Case lieu = map.getCase(i, j);
				Map<Direction, Case> dicoVoisins = map.getListeVoisin(lieu, map);
				for (Map.Entry voisins : dicoVoisins.entrySet()) {
					if (((Case) voisins.getValue()).getNature() == NatureTerrain.EAU
							&& lieu.getNature() != NatureTerrain.EAU) {
						Chemin ch = this.plusCourtChemin(this.getPosition(), lieu, map, temps);
						if (ch.chemin.lastKey() < tempsMin) {
							tempsMin = ch.chemin.lastKey().intValue();
							res = ch;
						}
					}
				}
			}
		}
		return res;
	}
}
