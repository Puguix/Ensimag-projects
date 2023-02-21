package map;

import java.util.*;

/**
 * Une case est représentée par:
 *
 * @param ligne       sa ligne
 * @param colonne     sa colonne
 * @param nature      la nature du terrain
 * @param successeurs Dictionnaire des cases suivantes
 */
public class Case {

	private int ligne;
	private int colonne;
	private NatureTerrain nature;
	public Map<Direction, Case> successeurs;

	public Case(int x, int y, NatureTerrain terrain) {
		this.ligne = x;
		this.colonne = y;
		this.nature = terrain;
		Map<Direction, Case> successeurs = new HashMap<Direction, Case>();
		this.successeurs = successeurs;

	}

	public int getLigne() {
		return this.ligne;
	}

	public int getColonne() {
		return this.colonne;
	}

	public NatureTerrain getNature() {
		return this.nature;
	}

	public Map<Direction, Case> getSuccesseurs() {
		return this.successeurs;
	}

	@Override
	public String toString() {
		return this.ligne + ", " + this.colonne;
	}

}
