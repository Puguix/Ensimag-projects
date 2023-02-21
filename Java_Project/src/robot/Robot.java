package robot;

import map.*;
import java.util.*;
import event.*;

/**
 * La classe abstraite Robot.
 * On implémente la fonctionalité Cloneable qui permet de faire des copies
 * profondes (pour copier les données de base de la simulation afin de pouvoir
 * la recommencer du début)
 */
abstract public class Robot implements Cloneable {

	protected Case position;
	// la case ou se trouve le robot
	protected double vitesseMax;
	// la vitesse max du robot
	protected int tailleReservoir;
	// la taille du r � �servoir
	protected int nbLitres;
	// le nombre de litre d 'eau dans le réservoir
	protected int tempsRemplissage;
	// le temps pour remplir le r � �servoir
	protected int tempsVersement;
	// le temps pour d � �verser l 'eau
	protected boolean estAffecte;
	// le robot a une mission

	/** constructeur de base de tous les robots */
	public Robot(Case emplacement, double vitesse, int reservoir, int dureeRemplissage, int dureeVersement) {
		position = emplacement;
		vitesseMax = vitesse;
		tailleReservoir = reservoir;
		nbLitres = reservoir;
		tempsRemplissage = dureeRemplissage;
		tempsVersement = dureeVersement;
		estAffecte = false;
	}

	public Case getPosition() {
		return position;
	}

	public int getTailleReservoir() {
		return tailleReservoir;
	}

	public int getNblitres() {
		return nbLitres;
	}

	public int getTempsRemplissage() {
		return tempsRemplissage;
	}

	public int getTempsVersement() {
		return tempsVersement;
	}

	public boolean estAffecte() {
		return estAffecte;
	}

	public void switchState() {
		estAffecte = !estAffecte;
	}

	/*
	 * trouve la case qui a le poids(ici le temps de trajet jusqu'à la prochaine
	 * case) minimum dans le graphe
	 */
	public Case trouve_min(Map<Case, Double> q, Map<Case, Double> graphe) {
		double min = 1000000002;
		Case s = new Case(-1, -1, NatureTerrain.TERRAIN_LIBRE); // case aberrante
		Collection<Case> case_it = q.keySet();
		Iterator<Case> it = case_it.iterator();
		while (it.hasNext()) {
			Case courant = it.next();
			if (graphe.get(courant) <= min) {
				min = graphe.get(courant);
				s = courant;
			}
		}
		return s;
	}

	abstract public void setPosition(Case lieu);

	abstract public double getVitesse();

	abstract public double getVitesse_case(Case c);

	abstract public void deverserEau(int vol);

	abstract public void remplirReservoir();

	/**
	 * Créer une copie profonde du robot
	 */
	abstract public Robot clone();

	/*
	 * Renvoie un dictionnaire des cases suivantes possibles d'une case pour un
	 * robot
	 */
	abstract public Map<Direction, Case> successeursPossibles(Case c, Carte map);

	/* renvoie le temps de trajet entre deux cases adjacentes pour un robot */
	abstract public double tempsDeTrajetDirect(Carte map, Case s1, Case s2);

	// renvoie le graphe orienté associé àla map (les arcs relient deux cases
	// adjacentes entre lesquelles le robot peut se déplacer)
	public GrapheSuccesseurs createGraphe(Carte carte) {
		int lig = carte.getNbLignes();
		int col = carte.getNbColonnes();
		Map<Case, Double> Cases = new HashMap<Case, Double>();
		GrapheSuccesseurs g = new GrapheSuccesseurs(Cases);
		for (int i = 0; i < lig; i++) {
			for (int j = 0; j < col; j++) {
				Case c = carte.map[i][j];
				Map<Direction, Case> succ = successeursPossibles(c, carte); // on récupère les prochaines cases
																			// possibles d'accès
				c.successeurs = succ;
				g.ajouteCase(c, 1000000000.0);
			}
		}
		return g;
	}

	public Map<Case, Case> Dijkstra(Carte map, Case debut, GrapheSuccesseurs graphe_0, double temps) {
		Map<Case, Double> graphe = graphe_0.getGraphe();
		Map<Case, Double> q = new HashMap<Case, Double>();
		q.putAll(graphe);
		// liste des cases non exploréees
		graphe.replace(debut, temps); // initialisation
		Map<Case, Case> predecesseur = new HashMap<Case, Case>();
		while (!q.isEmpty()) {
			Case s1 = trouve_min(q, graphe); // trouve le sommet qui a le poids le plus faible parmis ceux non traités
			s1.successeurs = successeursPossibles(s1, map);
			q.remove(s1); // on enlève cette case et on la traite
			Map<Direction, Case> succ = successeursPossibles(s1, map);
			Collection<Case> case_it = succ.values();
			Iterator<Case> it = case_it.iterator();
			while (it.hasNext()) {
				maj_distances(map, predecesseur, s1, it.next(), graphe); // on met à jour la plus la case avec le poids
																			// minimum et on ajoute la prochaines case
																			// au chemin
			}

		}
		return predecesseur;
	}

	/*
	 * met à jour le poids des cases dans le graphe et ajoute la prochaine case au
	 * sommet
	 */
	public void maj_distances(Carte map, Map<Case, Case> predecesseur, Case s1, Case s2, Map<Case, Double> g) {
		double new_d = g.get(s1) + tempsDeTrajetDirect(map, s1, s2);
		if (g.get(s2) > new_d) {
			g.replace(s2, new_d);
			predecesseur.put(s2, s1);
		}
	}

	/* vérifie si le robot peut être sur cette case */
	abstract public boolean peutEtre(Case s);

	/* calcule du plus court chemin entre deux cases pour un robot */
	public Chemin plusCourtChemin(Case debut, Case fin, Carte map, double tempsInit) {
		if (!peutEtre(fin)) {
			System.out.println("ne peut pas être sur la dernière case\n");
		}
		GrapheSuccesseurs graphe_0 = createGraphe(map);
		Map<Case, Case> predecesseur = Dijkstra(map, debut, graphe_0, tempsInit);
		Chemin chemin = new Chemin();
		Deque<Case> cheminMiroir = new LinkedList<Case>();
		Case courant = fin;
		while (courant != debut && courant != null) { // on créer une pile du chemin mais à l'envers
			cheminMiroir.add(courant);
			courant = predecesseur.get(courant);
		}
		cheminMiroir.add(debut);

		double temps = tempsInit;
		Iterator<Case> it = cheminMiroir.iterator();
		Case current = it.next();
		if (it.hasNext()) {
			Case suivant = it.next();
			while (it.hasNext()) { // on remplit la structure de donnée chemin (toujours à l'envers)
				chemin.ajoutChemin(current, temps);
				temps += tempsDeTrajetDirect(map, current, suivant);
				current = suivant;
				suivant = it.next();
			}
		}
		chemin.ajoutChemin(current, temps);

		NavigableMap<Double, Case> cheminReverse = chemin.reverseChemin(); // on remet le chemin à l'endroit
		chemin.chemin = cheminReverse;

		Collection<Case> c = cheminReverse.values();
		Iterator<Case> it_temps = c.iterator();
		Case current_temps = it_temps.next();

		NavigableMap<Double, Case> nmap_chemin = new TreeMap<Double, Case>();
		Chemin cheminfinal = new Chemin();
		cheminfinal.chemin = nmap_chemin;

		temps = tempsInit;
		cheminfinal.ajoutChemin(current_temps, temps);
		if (it_temps.hasNext()) { // on met à jour le temps d'arrivée en chaque case dans le chemin à l'endroit
			Case suivant_temps = it_temps.next();
			temps += tempsDeTrajetDirect(map, current_temps, suivant_temps);
			while (it_temps.hasNext()) {
				cheminfinal.ajoutChemin(current_temps, temps);
				temps += tempsDeTrajetDirect(map, current_temps, suivant_temps);
				current_temps = suivant_temps;
				suivant_temps = it_temps.next();
			}
			cheminfinal.ajoutChemin(current_temps, temps);
			temps += tempsDeTrajetDirect(map, current_temps, suivant_temps);
			cheminfinal.ajoutChemin(suivant_temps, temps);
			return cheminfinal;
		} else {
			// si il y a une seul case dans cheminMiroir
			cheminfinal.ajoutChemin(current, temps);
			return cheminfinal;
		}
	}

	/**
	 *
	 * @param map
	 * @return le chemin qui permet de s'approvisionner en eau le plus rapidement
	 *
	 */
	public abstract Chemin eauProche(Carte map, double temps);

	/**
	 * Modifie le robot de façon à ce qu'il est les mêmes propriétés que celui passé
	 * en argument
	 */
	public void copy(Robot robot) {
		position = robot.getPosition();
		vitesseMax = robot.getVitesse();
		tailleReservoir = robot.getTailleReservoir();
		nbLitres = robot.getNblitres();
		tempsRemplissage = robot.getTempsRemplissage();
		tempsVersement = robot.getTempsVersement();
		estAffecte = robot.estAffecte();
	}
}
