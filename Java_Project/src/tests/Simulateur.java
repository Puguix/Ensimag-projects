package tests;

import java.awt.Color;
import java.util.*;

import gui.GUISimulator;
import gui.Rectangle;
import gui.ImageElement;
import gui.Simulable;
import gui.Text;

import io.*;
import map.*;
import robot.*;
import tests.*;
import event.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.zip.DataFormatException;

import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;
import javax.swing.ImageIcon;

/**
 * Un simulateur
 * cet objet est associé à une fenêtre graphique GUISimulator, dans laquelle
 * elle peut se dessiner.
 * De plus elle hérite de Simulable, donc elle définit deux méthodes next() et
 * restart() invoquées par la fenêtre graphique de simulation selon les
 * commandes entrées par l'utilisateur.
 * 
 * @param gui         l'interface graphique associée
 * @param donnees     les donnees de la simulation en cours
 * @param donneesBase les donnees de base (pour pouvoir recommencer)
 * @param date        la date de la simulation en cours
 * @param events      la liste des evenements qui vont se produire
 * @param eventsBase  la liste des evenements de base (dans la cas des scénarios
 *                    prédéfinis pour pouvoir recommencer)
 */
public class Simulateur implements Simulable {

    private GUISimulator gui;
    private DonneesSimulation donnees;
    private DonneesSimulation donneesBase;
    private long date;
    private ArrayList<Evenement> events;

    /**
     * Associe les données à la fenêtre graphique et la représente.
     * 
     * @param gui     l'interface graphique associée, dans laquelle se fera le
     *                dessin et qui enverra les messages via les méthodes héritées
     *                de
     *                Simulable.
     * @param donnees les données de la simulation
     */
    public Simulateur(GUISimulator gui, DonneesSimulation donnees) {
        this.gui = gui;
        gui.setSimulable(this); // association a la gui!
        this.donneesBase = donnees;
        this.donnees = donneesBase.clone();
        this.events = new ArrayList<>();
        this.date = 0;
        draw(this.donnees);
    }

    public DonneesSimulation getDonnees() {
        return donnees;
    }

    public long getDate() {
        return date;
    }

    public void ajouteEvenement(Evenement event) {
        events.add(event);
        events.sort(null);
    }

    /** on incrémente la date et réalise les evenements de cette date */
    private void incrementeDate() {
        this.date++;

        if (!events.isEmpty()) {
            int size = events.size();
            int i = 0;

            while (i < size && events.get(i).getDate() < date) {
                i++;
                continue;
            }
            while (i < size && events.get(i).getDate() == date) {
                events.get(i).execute();
                i++;
            }
        }
    }

    /** la simulation s'arrete quand il n'y a plus d'evenements à réaliser */
    private boolean simulationTerminee() {
        return events.get(events.size() - 1).getDate() < date;
    }

    @Override
    public void next() {
        if (!simulationTerminee()) {
            incrementeDate();
            draw(this.donnees);
        }
    }

    @Override
    public void restart() {
        this.date = 0;
        this.donnees.copy(donneesBase);
        draw(this.donnees);
    }

    /**
     * Dessine les données sur l'interface graphique.
     */
    private void draw(DonneesSimulation donnees) {
        gui.reset(); // clear the window
        // System.out.println("Temps écoulé: " + date / 60 + "min " + date % 60 + "s");

        /**
         * On crée un dico pour pouvoir dessiner plusieurs robots du meme type sur la
         * meme case:
         * le chiffre des unités donne le nombre de drone;
         * le chiffre des dizaines le nombre de robot à roues;
         * le chiffre des centaines le nombre de robot à chenilles;
         * le chiffre des milliers le nombre de robot à pattes
         */
        Map<Case, Integer> dico = new HashMap<Case, Integer>();
        for (int i = 0; i < donnees.getCarte().getNbLignes(); i++) {
            for (int j = 0; j < donnees.getCarte().getNbColonnes(); j++) {
                dico.put(donnees.getCarte().getCase(i, j), 0);
            }
        }

        Carte carte = donnees.getCarte();
        int hauteur = gui.getHeight();
        int largeur = gui.getWidth();
        int dy = hauteur / carte.getNbLignes();
        int dx = largeur / carte.getNbColonnes();
        int x = 0;
        int y = 0;

        // dessine chaque case de la carte
        for (int i = 0; i < carte.getNbLignes(); i++) {
            for (int j = 0; j < carte.getNbColonnes(); j++) {
                switch (carte.getCase(i, j).getNature()) {
                    case EAU:
                        gui.addGraphicalElement(new ImageElement(x, y, "src/tests/eau.jpeg", dx, dy, null));
                        break;
                    case FORET:
                        gui.addGraphicalElement(new ImageElement(x, y, "src/tests/foret.jpeg", dx, dy, null));
                        break;
                    case ROCHE:
                        gui.addGraphicalElement(new ImageElement(x, y, "src/tests/roche.jpeg", dx, dy, null));
                        break;
                    case HABITAT:
                        gui.addGraphicalElement(new ImageElement(x, y, "src/tests/habitat.jpeg", dx, dy, null));
                        break;
                    default://Terrain Libre
                        gui.addGraphicalElement(new ImageElement(x, y, "src/tests/terrainlibre.jpeg", dx, dy, null));
                        break;
                }
                x += dx;
            }
            x = 0;
            y += dy;
        }

        // dessine les incendies
        for (Incendie feu : donnees.getIncedies()) {

            // sauf ceux éteinds
            if (feu.getNbLitres() <= 0)
                continue;

            x = dx / 4 + feu.getPosition().getColonne() * dx;
            y = dy / 4 + feu.getPosition().getLigne() * dy;
            gui.addGraphicalElement( new ImageElement(x, y, "src/tests/feu.png", dx/2, dy/2, null));
        }

        // couleurs des robots
        Color couleurDroneInt = Color.decode("#000000"); // noir
        Color couleurDroneExt = Color.decode("#ff0000"); // rouge
        Color couleurRoueInt = Color.decode("#ffffff"); // blanc
        Color couleurRoueExt = Color.decode("#f2d14b"); // or
        Color couleurChenilleInt = Color.decode("#563013"); // marron
        Color couleurChenilleExt = Color.decode("#5ef379"); // vert
        Color couleurPatteInt = Color.decode("#bd11e0"); // rose
        Color couleurPatteExt = Color.decode("#e8f903"); // jaune
        Color couleurInt;
        Color couleurExt;

        /**
         * coordonnées du robot
         * les drones sont en haut à gauche de la case
         * les robots à roue en haut à droite
         * les robots à chenille en bas à droite
         * les robots à pattes en bas à gauche
         */
        int robotX;
        int robotY;
        String filename;

        for (Robot robot : donnees.getRobots()) {
            Case pos = robot.getPosition();
            x = dx / 4 + pos.getColonne() * dx;
            y = dy / 4 + pos.getLigne() * dy;

            if (robot instanceof RobotARoue) {
                filename = "src/tests/robotaroue.jpeg";
                robotX = x - dx / 4;
                robotY = y + dy / 2;
                dico.replace(pos, dico.get(pos) + 10);
            } else if (robot instanceof Drone) {
                filename = "src/tests/drone.png";
                robotX = x - dx / 4;
                robotY = y - dy / 4;
                dico.replace(pos, dico.get(pos) + 1);
            } else if (robot instanceof RobotAChenille) {
                filename = "src/tests/robotachenille.png";
                robotX = x + dx / 2;
                robotY = y - dy / 4;
                dico.replace(pos, dico.get(pos) + 100);
            } else {
                filename = "src/tests/robotapattes.png";
                robotX = x + dx / 2;
                robotY = y + dy / 2;
                dico.replace(pos, dico.get(pos) + 1000);
            }

            gui.addGraphicalElement( new ImageElement(robotX, robotY, filename, dx / 4, dy / 4, null));

        }
    }

    public static Simulateur main(String[] args) {
        // crée la fenêtre graphique dans laquelle dessiner
        GUISimulator gui = new GUISimulator(800, 800, Color.BLACK);

        if (args.length < 1) {
            System.out.println("Syntaxe: java TestLecteurDonnees <nomDeFichier>");
            System.exit(1);
        }

        try {
            // crée les donnees, en l'associant à la fenêtre graphique précédente
            System.out.println(args[0] + " dans simulateur\n");
            DonneesSimulation donnees = CreateurDonnees.creerDonnees(args[0]);
            Simulateur simu = new Simulateur(gui, donnees);
            return simu;
        } catch (FileNotFoundException e) {
            System.out.println("fichier " + args[0] + " inconnu ou illisible");
        } catch (DataFormatException e) {
            System.out.println("\n\t**format du fichier " + args[0] + " invalide: " + e.getMessage());
        }
        return null;
    }
}