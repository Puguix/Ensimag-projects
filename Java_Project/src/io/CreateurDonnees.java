package io;

import robot.*;

import java.io.*;
import java.util.*;
import java.util.zip.DataFormatException;

import map.*;

/**
 * Lit toutes les infos d'un fichier et en créer une instance de
 * DonneesSimulation
 */
public class CreateurDonnees {

    /** Crée et renvoie un objet contenant toutes les données de la simulation */
    public static DonneesSimulation creerDonnees(String fichierDonnees)
            throws FileNotFoundException, DataFormatException {
        System.out.println("\n == Analyse du fichier" + fichierDonnees);
        CreateurDonnees createur = new CreateurDonnees(fichierDonnees);
        Carte map = createur.creerCarte();
        DonneesSimulation donnees = new DonneesSimulation(map);
        createur.mettreIncendies(donnees);
        createur.mettreRobots(donnees);
        scanner.close();
        System.out.println("\n == Analyse terminee");
        return donnees;
    }

    // Tout le reste de la classe est prive!

    private static Scanner scanner;

    /**
     * Constructeur prive; impossible d'instancier la classe depuis l'exterieur
     * 
     * @param fichierDonnees nom du fichier a lire
     */
    private CreateurDonnees(String fichierDonnees)
            throws FileNotFoundException {
        scanner = new Scanner(new File(fichierDonnees));
        scanner.useLocale(Locale.US);
    }

    private Carte creerCarte() throws DataFormatException {
        ignorerCommentaires();
        try {
            int nbLignes = scanner.nextInt();
            int nbColonnes = scanner.nextInt();
            int tailleCases = scanner.nextInt(); // en m
            Carte map = new Carte(nbLignes, nbColonnes, tailleCases);

            for (int lig = 0; lig < nbLignes; lig++) {
                for (int col = 0; col < nbColonnes; col++) {
                    map.placerCase(creerCase(lig, col));
                }
            }
            return map;

        } catch (NoSuchElementException e) {
            throw new DataFormatException("Format invalide. "
                    + "Attendu: nbLignes nbColonnes tailleCases");
        }
        // une ExceptionFormat levee depuis lireCase est remontee telle quelle
    }

    private Case creerCase(int lig, int col) throws DataFormatException {
        ignorerCommentaires();
        String chaineNature = new String(); // NatureTerrain nature;

        try {
            chaineNature = scanner.next();
            NatureTerrain nature = NatureTerrain.valueOf(chaineNature);

            verifieLigneTerminee();

            return new Case(lig, col, nature);

        } catch (NoSuchElementException e) {
            throw new DataFormatException("format de case invalide. "
                    + "Attendu: nature altitude [valeur_specifique]");
        }
    }

    private void mettreIncendies(DonneesSimulation donnees) throws DataFormatException {
        ignorerCommentaires();
        try {
            int nbIncendies = scanner.nextInt();
            for (int i = 0; i < nbIncendies; i++) {
                donnees.ajouterIncendie(creerIncendie(i, donnees));
            }

        } catch (NoSuchElementException e) {
            throw new DataFormatException("Format invalide. "
                    + "Attendu: nbIncendies");
        }
    }

    private Incendie creerIncendie(int i, DonneesSimulation donnees) throws DataFormatException {
        ignorerCommentaires();
        try {
            int lig = scanner.nextInt();
            int col = scanner.nextInt();
            int intensite = scanner.nextInt();
            if (intensite <= 0) {
                throw new DataFormatException("incendie " + i
                        + "nb litres pour eteindre doit etre > 0");
            }
            verifieLigneTerminee();

            return new Incendie(donnees.getCarte().getCase(lig, col), intensite);

        } catch (NoSuchElementException e) {
            throw new DataFormatException("format d'incendie invalide. "
                    + "Attendu: ligne colonne intensite");
        }
    }

    private void mettreRobots(DonneesSimulation donnees) throws DataFormatException {
        ignorerCommentaires();
        try {
            int nbRobots = scanner.nextInt();
            for (int i = 0; i < nbRobots; i++) {
                donnees.ajouterRobot(creerRobot(i, donnees));
            }

        } catch (NoSuchElementException e) {
            throw new DataFormatException("Format invalide. "
                    + "Attendu: nbRobots");
        }
    }

    private Robot creerRobot(int i, DonneesSimulation donnees) throws DataFormatException {
        ignorerCommentaires();
        try {
            int lig = scanner.nextInt();
            int col = scanner.nextInt();
            String type = scanner.next();

            // lecture eventuelle d'une vitesse du robot (entier)
            String s = scanner.findInLine("(\\d+)");
            int vitesse = 0;
            if (s != null) {
                vitesse = Integer.parseInt(s);
            }

            Robot robot;

            switch (type) {
                case "ROUES":
                    vitesse = vitesse != 0 ? vitesse : 80;
                    robot = new RobotARoue(donnees.getCarte().getCase(lig, col), vitesse);
                    break;
                case "CHENILLES":
                    vitesse = vitesse != 0 ? vitesse : 60;
                    robot = new RobotAChenille(donnees.getCarte().getCase(lig, col), vitesse);
                    break;
                case "PATTES":
                    vitesse = 30;
                    robot = new RobotAPatte(donnees.getCarte().getCase(lig, col), vitesse);
                    break;
                default:
                    vitesse = vitesse != 0 ? vitesse : 100;
                    robot = new Drone(donnees.getCarte().getCase(lig, col), vitesse);
                    break;
            }

            verifieLigneTerminee();

            return robot;

        } catch (NoSuchElementException e) {
            throw new DataFormatException("format de robot invalide. "
                    + "Attendu: ligne colonne type [valeur_specifique]");
        }
    }

    /** Ignore toute (fin de) ligne commencant par '#' */
    private void ignorerCommentaires() {
        while (scanner.hasNext("#.*")) {
            scanner.nextLine();
        }
    }

    /**
     * Verifie qu'il n'y a plus rien a lire sur cette ligne (int ou float).
     * 
     * @throws ExceptionFormatDonnees
     */
    private void verifieLigneTerminee() throws DataFormatException {
        if (scanner.findInLine("(\\d+)") != null) {
            throw new DataFormatException("format invalide, donnees en trop.");
        }
    }
}
