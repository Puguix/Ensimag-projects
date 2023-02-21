package map;

/**
 * La classe Incendie implémente Cloneable qui sert à faire des copies profondes
 * et donc pouvoir duppliquer des données afin de pouvoir recommencer une
 * simulation
 *
 * @param position          le lieu de l'incendie
 * @param litrePourEteindre le nombre de litres d'eau nécessaire pour l'éteindre
 * @param estAffecte        indique si un robot est affecté à éteindre ce feu
 */
public class Incendie implements Cloneable {

	private Case position;
	private int litrePourEteindre;
	private boolean estAffecte;

	public Incendie(Case lieu, int eauPourEteindre) {
		position = lieu;
		litrePourEteindre = eauPourEteindre;
	}

	public Case getPosition() {
		return position;
	}

	public int getNbLitres() {
		return litrePourEteindre;
	}

	public boolean estAffecte() {
		return estAffecte;
	}

	public void eteindre(int litres) {
		litrePourEteindre -= litres;
		if (litrePourEteindre < 0) {
			litrePourEteindre = 0;
		}
	}

	/**
	 * Renvoie une copie profonde de l'incendie
	 */
	public Incendie clone() {
		return new Incendie(position, litrePourEteindre);
	}

	/**
	 * Modifie les paramètres de l'incendie en fonction de celui passé en paramètre
	 */
	public void copy(Incendie incendie) {
		litrePourEteindre = incendie.getNbLitres();
		estAffecte = incendie.estAffecte();
	}

}
