package map;

import java.util.*;

public class GrapheSuccesseurs {
	public Map<Case, Double> Cases;

	public GrapheSuccesseurs(Map<Case, Double> Cases) {
		this.Cases = Cases;
	}

	public Map<Case, Double> getGraphe() {
		return this.Cases;
	}

	public void ajouteCase(Case c, Double temps) {
		Map<Case, Double> g = this.getGraphe();
		g.put(c, temps);
	}

	@Override
	public String toString() {
		Map<Case, Double> chemin = this.Cases;
		Set<Case> cases = chemin.keySet();
		Iterator<Case> it = cases.iterator();
		String res = "";
		while (it.hasNext()) {
			res += it.next().toString() + " | ";
		}
		return res;
	}
}
