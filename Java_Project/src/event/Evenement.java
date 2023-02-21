package event;

/**
 * Evenement est la classe abstraite définissant tout type d'évenement
 * Elle implémente Comparable afin de pouvoir trier les évenements par ordre
 * d'apparition dans une liste
 *
 * @param date la date à laquelle se produit l'évenement
 */
abstract public class Evenement implements Comparable<Evenement> {

	public long date;

	public Evenement(long d) {
		date = d;
	}

	public long getDate() {
		return date;
	}

	abstract public void execute();

	/** Permet de tester si un evenement se produit avant un autre */
	@Override
	public int compareTo(Evenement event) {
		long dt = this.date - event.date;
		if (dt > 0)
			return 1;
		else if (dt < 0)
			return -1;
		else
			return 0;
	}

	/** Permet de tester si deux évenements se déroulent en même temps */
	@Override
	public boolean equals(Object o) {
		if (o instanceof Evenement == false) {
			return false;
		}
		Evenement e = (Evenement) o;
		return this.date == e.date;
	}
}
