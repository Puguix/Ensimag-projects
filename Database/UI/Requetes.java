package UI;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;

public class Requetes {

        public static ResultSet chercheIdClient(Connection conn, String emailC) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement("select idClient from Client where emailC == ?");
                pstmt.setString(1, emailC);
                ResultSet rset = pstmt.executeQuery();
                return rset;

        }

        /*
         * public ResultSet chercheRestaurantParDisponibilité(Connection conn, int
         * places, String date, String heure)
         * throws SQLException {
         * PreparedStatement pstmt = conn
         * .prepareStatement("select * from Restaurant where nbplaces > ? and Date == ? and Heure == ?"
         * );
         * pstmt.setString(2, date);
         * pstmt.setString(2, heure);
         * ResultSet rset = pstmt.executeQuery();
         * dumpResult(rset);
         * return rset;
         * }
         */

        public static void deleteuser(Connection conn, String emailC) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement("delete from client where emailC == ?");
                pstmt.setString(1, emailC);
        }

        /*
         * public ResultSet chercheNoteRestaurant(Connection conn, String emailR) throws
         * SQLException {
         * PreparedStatement pstmt = conn
         * .prepareStatement("select avg(note) from evaluation join commande where date.commande == date .evaluation and heure.commande == heure.evaluation join restaurant where restaurant.emailR == ? "
         * );
         * pstmt.setString(1, emailR);
         * ResultSet rset = pstmt.executeQuery();
         * dumpResult(rset);
         * return rset;
         * }
         */

        /*
         * public ResultSet chercheAlergenePlat(Connection conn, int numeroPlat) throws
         * SQLException{
         * PreparedStatement pstmt = conn
         * .prepareStatement("select allergene from Allergene join plat where numeroPlat == ?"
         * );
         * pstmt.setInt(1, numeroPlat);
         * ResultSet rset = pstmt.executeQuery();
         * dumpResult(rset);
         * return rset;
         * }
         */

        /*
         * public ResultSet afficheHoraireOuverture(Connection conn, String emailR,
         * String jourO) throws SQLException {
         * PreparedStatement pstmt = conn
         * .prepareStatement("select plat from Plat join Restaurant where emailR == ?");
         * pstmt.setString(1, emailR);
         * ResultSet rset = pstmt.executeQuery();
         * dumpResult(rset);
         * return rset;
         * }
         */

        public static ResultSet nbrePlaceResto(Connection conn, String emailR) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement("select nbrePlace from Restaurant where emailR == ? and jourO == ?");
                pstmt.setString(1, emailR);
                ResultSet rset = pstmt.executeQuery();
                dumpResult(rset);
                return rset;
        }

        public static ResultSet afficheRestaurant(Connection conn, String categorie) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement(
                                                "select nomR, AVG(note) From Restaurant join apourcategorie where Restaurant.emailR == apourcategorie.emailR where apourcategorie.categorie == ? join Commande where Commande.emailR == Restaurant.emailR join join EvaluationC where Commande.date == Evaluation.date order by avg(note) desc");
                pstmt.setString(1, categorie);
                ResultSet rset = pstmt.executeQuery();
                dumpResult(rset);
                return rset;
        }

        public static ResultSet chercheRestaurantHoraire(Connection conn, String categorie, String jourO, int heureO)
                        throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement(
                                                "select nomR, AVG(note) From Restaurant join apourcategorie where Restaurant.emailR == apourcategorie.emailR where apourcategorie.categorie == ? join Commande where Commande.emailR == Restaurant.emailR join join EvaluationC where Commande.date == Evaluation.date join estouvertle where estouvertle.emailR == Restaurant.emailR where estouvertle.jourouverture == ? and estouvertle.heureouverture == ? order by avg(note) desc");
                pstmt.setString(1, categorie);
                pstmt.setString(2, jourO);
                pstmt.setInt(3, heureO);
                ResultSet rset = pstmt.executeQuery();
                dumpResult(rset);
                return rset;
        }

        public static ResultSet affichedetailRestau(Connection conn, String emailR) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement("select * From Restaurant Join Plat where emailR = ?");
                pstmt.setString(1, emailR);
                ResultSet rset = pstmt.executeQuery();
                dumpResult(rset);
                return rset;
        }

        /* TODO : Les commandes sont irreversibles (pas possible de les annuler */
        public static void addComandeEmporter(Connection conn, int idPlat, String emailC, String emailR,
                        Timestamp dateC, int Qte, int prixTotal, String statut, String typeC) throws SQLException {

                int idClient = chercheIdClient(conn, emailC).getInt(1);
                PreparedStatement pstmt = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', )");
                pstmt.setInt(1, idPlat);
                pstmt.setString(2, emailR);
                pstmt.setInt(3, idClient);
                pstmt.setTimestamp(4, dateC);
                pstmt.setInt(6, Qte);
                pstmt.executeQuery();
                PreparedStatement pstmt2 = conn
                                .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', )");
                pstmt2.setString(1, emailR);
                pstmt2.setInt(2, idClient);
                pstmt2.setTimestamp(3, dateC);
                pstmt2.setInt(4, prixTotal);
                pstmt2.setString(5, statut);
                pstmt2.setString(6, typeC);
                pstmt2.executeQuery();
        }

        public static void addComandeLivraison(Connection conn, int idPlat, String emailC, String emailR,
                        Timestamp dateC,
                        int Qte,
                        int prixTotal, String statut, String typeC, String adresseLivraison, Timestamp heureLivraison)
                        throws SQLException {

                int idClient = chercheIdClient(conn, emailC).getInt(1);
                PreparedStatement pstmt = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', )");
                pstmt.setInt(1, idPlat);
                pstmt.setString(2, emailR);
                pstmt.setInt(3, idClient);
                pstmt.setTimestamp(4, dateC);
                pstmt.setInt(6, Qte);
                pstmt.executeQuery();
                PreparedStatement pstmt2 = conn
                                .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', )");
                pstmt2.setString(1, emailR);
                pstmt2.setInt(2, idClient);
                pstmt2.setTimestamp(3, dateC);
                pstmt2.setInt(4, prixTotal);
                pstmt2.setString(5, statut);
                pstmt2.setString(6, typeC);
                pstmt2.executeQuery();

                PreparedStatement pstmt3 = conn
                                .prepareStatement("INSERT INTO Commandelivraison VALUES ('?', '?', '?', '?', )");
                pstmt3.setString(1, emailR);
                pstmt.setInt(2, idClient);
                pstmt3.setTimestamp(3, dateC);
                pstmt3.setInt(4, prixTotal);
                pstmt3.setString(5, statut);
                pstmt3.setString(6, typeC);
                pstmt3.setString(7, adresseLivraison);
                pstmt3.setTimestamp(8, heureLivraison);
        }

        public static void addComandeSurPlace(Connection conn, int idPlat, String emailC, String emailR,
                        Timestamp dateC,
                        int Qte,
                        int prixTotal, String statut, String typeC, int nbpersonnes, Timestamp heureArrivee)
                        throws SQLException {
                int idClient = chercheIdClient(conn, emailC).getInt(1);
                PreparedStatement pstmt = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', )");
                pstmt.setInt(1, idPlat);
                pstmt.setString(2, emailR);
                pstmt.setInt(3, idClient);
                pstmt.setTimestamp(4, dateC);
                pstmt.setInt(6, Qte);
                pstmt.executeQuery();
                PreparedStatement pstmt2 = conn
                                .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', )");
                pstmt2.setString(1, emailR);
                pstmt2.setInt(2, idClient);
                pstmt2.setTimestamp(3, dateC);
                pstmt2.setInt(4, prixTotal);
                pstmt2.setString(5, statut);
                pstmt2.setString(6, typeC);
                pstmt2.executeQuery();

                PreparedStatement pstmt3 = conn
                                .prepareStatement("INSERT INTO Commandesurplace VALUES ('?', '?', '?', '?', )");
                pstmt3.setString(1, emailR);
                pstmt3.setInt(2, idClient);
                pstmt3.setTimestamp(3, dateC);
                pstmt3.setInt(4, prixTotal);
                pstmt3.setString(5, statut);
                pstmt3.setString(6, typeC);
                pstmt3.setInt(7, nbpersonnes);
                pstmt3.setTimestamp(8, heureArrivee);

                int nbrePlaceRestante = nbrePlaceResto(conn, emailR).getInt(1) - nbpersonnes;
                PreparedStatement pstmt4 = conn
                                .prepareStatement("UPDATE Restaurant SET nbPlace = '?'' WHERE emailR == '?'");
                pstmt4.setInt(1, nbrePlaceRestante);
                pstmt4.setString(2, emailR);
        }


        /* TODO : Check nombre personnes */

        /**
         * L'heure de commande est l'heure systeme
         * @param conn
         * @param plats
         * @param emailC
         * @param emailR
         * @throws SQLException
         */
        public static void addCommandeSurPlace2(Connection conn, HashMap<Integer, Integer> plats, String emailC, String emailR)
                throws SQLException {
                Timestamp timestamp = new Timestamp(System.currentTimeMillis());
                /* Recupere les infos client */
                int idClient = chercheIdClient(conn, emailC).getInt(1);
                /* Debut transaction */
                conn.setAutoCommit(false);

//                conn.setSavepoint("savepoint0");

                /* Insertion sur Commande*/
                PreparedStatement insertCommande = conn
                        .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', '?', '?',)");
                insertCommande.setString(1, emailR);
                insertCommande.setInt(2, idClient);
                /* TODO : recuperer dateC */
                insertCommande.setTimestamp(3, timestamp);
                insertCommande.setInt(4, 0);
                insertCommande.setString(5, "attente de confirmation");
                insertCommande.setString(6, "sur place");


                /* Insertion sur commandesurplace */

                PreparedStatement insertCommandeSurPlace = conn
                        .prepareStatement("INSERT INTO Commandesurplace VALUES ('?', '?', '?', '?', '?', '?', '?','?',)");
                insertCommandeSurPlace.setString(1, emailR);
                insertCommandeSurPlace.setInt(2, idClient);
                insertCommandeSurPlace.setTimestamp(3, timestamp);
                insertCommandeSurPlace.setInt(4, 0);
                insertCommandeSurPlace.setString(5, "attente de confirmation");
                insertCommandeSurPlace.setString(6, "sur place");
                /* TODO : recuperer nbpersonnes et heureArrivee */
                insertCommandeSurPlace.setInt(7, nbpersonnes);
                insertCommandeSurPlace.setTimestamp(8, heureArrivee);


                insertCommande.executeQuery();
                insertCommandeSurPlace.executeQuery();

                int index = 0;
                int prixTotal = 0;
                conn.setSavepoint("savepoint"+index);

                /* Ajout des plats */
                for (Map.Entry<Integer, Integer> entry : plats.entrySet()){
                        int idPlat = entry.getKey();
                        int qte = entry.getValue();
                        PreparedStatement aCommande = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', '?',)");
                        aCommande.setInt(1, idPlat);
                        aCommande.setString(2, emailR);
                        aCommande.setInt(3, idClient);
                        aCommande.setTimestamp(4, timestamp);
                        aCommande.setInt(5, qte);
                        aCommande.executeQuery();
                        /* TODO : get prix plat */
                        prixTotal += qte * getPrixPlat(idPlat, emailR);
                        index += 1; //fluff
                }

                /* Validation de la commande */
                PreparedStatement updateCommande = conn.prepareStatement(
                        "UPDATE Commande SET (prixTotal = ?, statut = 'validee' WHERE emailR = ?, idClient = ?, dateC = ?");
                updateCommande.setInt(1, prixTotal);
                updateCommande.setString(2, emailR);
                updateCommande.setInt(3, idClient);
                updateCommande.setTimestamp(4, timestamp);
                updateCommande.executeQuery();

                PreparedStatement updateCommandeSurPlace = conn.prepareStatement(
                        "UPDATE CommandeSurPlace SET (prixTotal = ?, statut = 'validee'WHERE emailR = ?, idClient = ?, dateC = ?");
                updateCommandeSurPlace.setInt(1, prixTotal);
                updateCommandeSurPlace.setString(2, emailR);
                updateCommandeSurPlace.setInt(3, idClient);
                updateCommandeSurPlace.setTimestamp(4, timestamp);
                updateCommandeSurPlace.executeQuery();

                conn.commit();
                conn.setAutoCommit(true);
        }

        /**
         * L'heure de commande est l'heure systeme
         * @param conn
         * @param plats
         * @param emailC
         * @param emailR
         * @throws SQLException
         */
        public static void addCommandeAEmporter2(Connection conn, HashMap<Integer, Integer> plats, String emailC, String emailR)
                throws SQLException {
                Timestamp timestamp = new Timestamp(System.currentTimeMillis());
                /* Recupere les infos client */
                int idClient = chercheIdClient(conn, emailC).getInt(1);
                /* Debut transaction */
                conn.setAutoCommit(false);

//                conn.setSavepoint("savepoint0");

                /* Insertion sur Commande*/
                PreparedStatement insertCommande = conn
                        .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', '?', '?',)");
                insertCommande.setString(1, emailR);
                insertCommande.setInt(2, idClient);
                /* TODO : recuperer dateC */
                insertCommande.setTimestamp(3, timestamp);
                insertCommande.setInt(4, 0);
                insertCommande.setString(5, "attente de confirmation");
                insertCommande.setString(6, "a emporter");

                insertCommande.executeQuery();

                int index = 0;
                int prixTotal = 0;
                conn.setSavepoint("savepoint"+index);

                /* Ajout des plats */
                for (Map.Entry<Integer, Integer> entry : plats.entrySet()){
                        int idPlat = entry.getKey();
                        int qte = entry.getValue();
                        PreparedStatement aCommande = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', '?',)");
                        aCommande.setInt(1, idPlat);
                        aCommande.setString(2, emailR);
                        aCommande.setInt(3, idClient);
                        aCommande.setTimestamp(4, timestamp);
                        aCommande.setInt(5, qte);
                        aCommande.executeQuery();
                        /* TODO : get prix plat */
                        prixTotal += qte * getPrixPlat(idPlat, emailR);
                        index += 1; //fluff
                }

                /* Validation de la commande */
                PreparedStatement updateCommande = conn.prepareStatement(
                        "UPDATE Commande SET (prixTotal = ?, statut = 'validee' WHERE emailR = ?, idClient = ?, dateC = ?");
                updateCommande.setInt(1, prixTotal);
                updateCommande.setString(2, emailR);
                updateCommande.setInt(3, idClient);
                updateCommande.setTimestamp(4, timestamp);
                updateCommande.executeQuery();

                conn.commit();
        }

        /**
         * L'heure de commande est l'heure systeme
         * @param conn
         * @param plats
         * @param emailC
         * @param emailR
         * @throws SQLException
         */
        public static void addCommandeLivraison2(Connection conn, HashMap<Integer, Integer> plats, String emailC, String emailR)
                throws SQLException {
                Timestamp timestamp = new Timestamp(System.currentTimeMillis());
                /* Recupere les infos client */
                int idClient = chercheIdClient(conn, emailC).getInt(1);
                /* Debut transaction */
                conn.setAutoCommit(false);

//                conn.setSavepoint("savepoint0");

                /* Insertion sur Commande*/
                PreparedStatement insertCommande = conn
                        .prepareStatement("INSERT INTO commande VALUES ('?', '?', '?', '?', '?', '?',)");
                insertCommande.setString(1, emailR);
                insertCommande.setInt(2, idClient);
                /* TODO : recuperer dateC */
                insertCommande.setTimestamp(3, timestamp);
                insertCommande.setInt(4, 0);
                insertCommande.setString(5, "attente de confirmation");
                insertCommande.setString(6, "livraison");


                /* Insertion sur commandelivraison */

                PreparedStatement insertCommandeLivraison = conn
                        .prepareStatement("INSERT INTO Commandelivraison VALUES ('?', '?', '?', '?', '?', '?', '?','?',)");
                insertCommandeLivraison.setString(1, emailR);
                insertCommandeLivraison.setInt(2, idClient);
                insertCommandeLivraison.setTimestamp(3, timestamp);
                insertCommandeLivraison.setInt(4, 0);
                insertCommandeLivraison.setString(5, "attente de confirmation");
                insertCommandeLivraison.setString(6, "livraison");
                /* TODO : recuperer adresseLivraison */
                insertCommandeLivraison.setString(7, adresseLivraison);
                insertCommandeLivraison.setTimestamp(8, new Timestamp(0));

                /* Insertion sur Texte Livraison */
                PreparedStatement insertMessageLivraison = conn.prepareStatement("INSERT INTO TexteLivraison VALUES ('?', )");
                /* TODO : recuperer message Livraison */
                insertMessageLivraison.setString(1, messageLivraison);

                /* Insertion sur ContientMessage */
                PreparedStatement insertContientMsg = conn.prepareStatement("INSERT INTO contientmsg VALUES ('?', '?', '?', '?',)");
                insertContientMsg.setString(1, emailR);
                insertContientMsg.setInt(2, idClient);
                insertContientMsg.setTimestamp(3, timestamp);
                insertContientMsg.setTimestamp(4, messageLivraison);



                insertCommande.executeQuery();
                insertCommandeLivraison.executeQuery();
                insertMessageLivraison.executeQuery();
                insertContientMsg.executeQuery();


                int index = 0;
                int prixTotal = 0;
                conn.setSavepoint("savepoint"+index);

                /* Ajout des plats */
                for (Map.Entry<Integer, Integer> entry : plats.entrySet()){
                        int idPlat = entry.getKey();
                        int qte = entry.getValue();
                        PreparedStatement aCommande = conn
                                .prepareStatement("INSERT INTO acommande VALUES ('?', '?', '?', '?', '?',)");
                        aCommande.setInt(1, idPlat);
                        aCommande.setString(2, emailR);
                        aCommande.setInt(3, idClient);
                        aCommande.setTimestamp(4, timestamp);
                        aCommande.setInt(5, qte);
                        aCommande.executeQuery();
                        /* TODO : get prix plat */
                        prixTotal += qte * getPrixPlat(idPlat, emailR);
                        index += 1; //fluff
                }

                /* Validation de la commande */
                PreparedStatement updateCommande = conn.prepareStatement(
                        "UPDATE Commande SET (prixTotal = ?, statut = 'validee' WHERE emailR = ?, idClient = ?, dateC = ?");
                updateCommande.setInt(1, prixTotal);
                updateCommande.setString(2, emailR);
                updateCommande.setInt(3, idClient);
                updateCommande.setTimestamp(4, timestamp);
                updateCommande.executeQuery();

                PreparedStatement updateCommandeLivraison = conn.prepareStatement(
                        "UPDATE CommandeSurPlace SET (prixTotal = ?, statut = 'validee'WHERE emailR = ?, idClient = ?, dateC = ?");
                updateCommandeLivraison.setInt(1, prixTotal);
                updateCommandeLivraison.setString(2, emailR);
                updateCommandeLivraison.setInt(3, idClient);
                updateCommandeLivraison.setTimestamp(4, timestamp);
                updateCommandeLivraison.executeQuery();

                conn.commit();
                conn.setAutoCommit(true);
        }
        public static ResultSet recupMotdepasse(Connection conn, String emailC) throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement("select mdp from Client where emailC == ?");
                pstmt.setString(1, emailC);
                ResultSet rset = pstmt.executeQuery();
                return rset;
        }

        public static ResultSet trouveRestoSemblable(Connection conn, String emailR, int nbpersonnes)
                        throws SQLException {
                PreparedStatement pstmt = conn
                                .prepareStatement(
                                                "select nomR from Restaurant where nbPlaces >= '?' and where emailR in (Select emailR from apourcategorie where apourcategorie.emailR == '?' or where apourcategorie.categorie in (select categorie from Estfilsde join apourcategorie where Estfilsde.categorie == apourcategorie.categorie where emailR == '?'))");
                pstmt.setInt(1, nbpersonnes);
                pstmt.setString(2, emailR);
                pstmt.setString(3, emailR);
                ResultSet rset = pstmt.executeQuery();
                return rset;
        }

        static void dumpResult(ResultSet r) throws SQLException {
                while (r.next()) {
                        System.out.println(
                                        "Cinema: " + r.getString(1) +
                                                        "- Salle: " + r.getString(2) +
                                                        " - " + r.getInt(3) + " places.");
                }
        }
}
