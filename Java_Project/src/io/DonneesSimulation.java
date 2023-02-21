package io;

import robot.*;
import java.util.ArrayList;
import map.*;

/**
 * La classe regroupant toutes les données d'une simulation:
 * 
 * @param carte     la carte du monde
 * @param robots    une liste des robots présents
 * @param incendies une liste des incendies présents
 */
public class DonneesSimulation implements Cloneable {

    private Carte carte;
    private ArrayList<Robot> robots;
    private ArrayList<Incendie> incendies;

    /**
     * Le constructeur de base
     */
    public DonneesSimulation(Carte map) {
        carte = map;
        robots = new ArrayList<Robot>();
        incendies = new ArrayList<Incendie>();
    }

    /**
     * Le constructeur servant à recréer une instance à partir d'une autre
     */
    private DonneesSimulation(Carte map, ArrayList<Robot> r, ArrayList<Incendie> i) {
        carte = map;
        robots = r;
        incendies = i;
    }

    public void ajouterRobot(Robot robot) {
        robots.add(robot);
    }

    public void ajouterIncendie(Incendie incendie) {
        incendies.add(incendie);
    }

    public Carte getCarte() {
        return carte;
    }

    public ArrayList<Robot> getRobots() {
        return robots;
    }

    public ArrayList<Incendie> getIncedies() {
        return incendies;
    }

    /** Renvoie une copie profonde des données */
    public DonneesSimulation clone() {
        return new DonneesSimulation(carte, cloneRobots(robots), cloneIncendies(incendies));
    }

    /**
     * Modifie les donnees pour qu'elle soit identique à celle passée en argument
     */
    public void copy(DonneesSimulation donnees) {
        for (int i = 0; i < robots.size(); i++) {
            robots.get(i).copy(donnees.getRobots().get(i));
        }
        for (int i = 0; i < incendies.size(); i++) {
            incendies.get(i).copy(donnees.getIncedies().get(i));
        }
    }

    /** Renvoie une copie profonde de la liste des robots */
    public static ArrayList<Robot> cloneRobots(ArrayList<Robot> list) {
        ArrayList<Robot> clone = new ArrayList<Robot>(list.size());
        for (Robot item : list)
            clone.add(item.clone());
        return clone;
    }

    /** Renvoie une copie profonde de la liste des incendies */
    public static ArrayList<Incendie> cloneIncendies(ArrayList<Incendie> list) {
        ArrayList<Incendie> clone = new ArrayList<Incendie>(list.size());
        for (Incendie item : list)
            clone.add(item.clone());
        return clone;
    }
}
