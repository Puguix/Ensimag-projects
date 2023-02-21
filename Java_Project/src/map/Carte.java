package map;

import java.util.*;

/**
 * La case en (0, 0) est la case la plus au nord ouest.
 * La case en (n, m) est la case la plus au sud est
 *
 * @param map         la matrice des cases qui compose la carte
 * @param tailleCases la taille des cases en mètres
 *
 */
public class Carte {

	public Case[][] map;
	public int tailleCases;

	public Carte(int nbLignes, int nbColonnes, int taille) {
		map = new Case[nbLignes][nbColonnes];
		tailleCases = taille;
	}

	public void placerCase(Case lieu) {
		map[lieu.getLigne()][lieu.getColonne()] = lieu;
	}

	public int getNbLignes() {
		return map.length;
	}

	public int getNbColonnes() {
		return map[0].length;
	}

	public int getTailleCases() {
		return tailleCases;
	}

	public Case getCase(int ligne, int colonne) {
		return map[ligne][colonne];
	}

	public boolean voisinExiste(Case src, Direction dir) {
		switch (dir) {
			case NORD:
				if (src.getLigne() <= 0) {
					return false;
				}
				break;
			case SUD:
				if (src.getLigne() >= getNbLignes() - 1) {
					return false;
				}
				break;
			case EST:
				if (src.getColonne() >= getNbColonnes() - 1) {
					return false;
				}
				break;
			case OUEST:
				if (src.getColonne() <= 0) {
					return false;
				}
				break;
		}
		return true;
	}

	public Map<Direction, Case> getListeVoisin(Case src, Carte map) {
		Map<Direction, Case> Voisins = new HashMap<Direction, Case>();
		if (voisinExiste(src, Direction.NORD)) {
			Voisins.put(Direction.NORD, getVoisin(src, Direction.NORD));
		}
		if (voisinExiste(src, Direction.SUD)) {
			Voisins.put(Direction.SUD, getVoisin(src, Direction.SUD));
		}
		if (voisinExiste(src, Direction.EST)) {
			Voisins.put(Direction.EST, getVoisin(src, Direction.EST));
		}
		if (voisinExiste(src, Direction.OUEST)) {
			Voisins.put(Direction.OUEST, getVoisin(src, Direction.OUEST));
		}
		return Voisins;
	}

	public Case getVoisin(Case src, Direction dir) {
		if (!voisinExiste(src, dir)) {
			System.out.println("le voisin n'existe pas");
			return null;
		}
		switch (dir) {
			case NORD:
				Case snord = getCase(src.getLigne() - 1, src.getColonne());
				return snord;
			case SUD:
				Case ssud = getCase(src.getLigne() + 1, src.getColonne());
				return ssud;
			case EST:
				Case sest = getCase(src.getLigne(), src.getColonne() + 1);
				return sest;
			default:
				Case s = getCase(src.getLigne(), src.getColonne() - 1);
				return s;
		}
	}
}
