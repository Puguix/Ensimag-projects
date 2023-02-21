package event;

import map.*;

import java.util.*;

/**
 * La classe Chemin permet de créer un Chemin qu ele robot suivra
 */
public class Chemin {
	// Double pour la date
	public NavigableMap<Double, Case> chemin;

	public Chemin() {
		NavigableMap<Double, Case> chemin = new TreeMap<Double, Case>();
		this.chemin = chemin;
	}

	public NavigableMap<Double, Case> getChemin() {
		return this.chemin;
	}

	public void ajoutChemin(Case s, double temps) {
		NavigableMap<Double, Case> ch = getChemin();
		ch.put(temps, s);
	}

	public NavigableMap<Double, Case> reverseChemin() {
		NavigableMap<Double, Case> chemin = this.getChemin();
		return chemin.descendingMap();
	}

	@Override
	public String toString() {
		NavigableMap<Double, Case> chemin = this.chemin;
		Collection<Double> temps = chemin.keySet();
		Iterator<Double> it = temps.iterator();
		String res = "";
		while (it.hasNext()) {
			Double t = it.next();
			res += "case : " + chemin.get(t) + "temps : " + t + " ";
		}
		return res;
	}
}
