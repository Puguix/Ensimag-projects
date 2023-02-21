package UI;

import java.awt.event.*;
import javax.swing.*;
import java.sql.*;

public class Restaurants extends JFrame implements ActionListener {

    static JFrame frame;
    static Connection conn;
    static Restaurants obj;

    public static void main(Connection connection, String categorie, String date, int heure) {

        // initiation de la connection
        conn = connection;

        // créer un frame
        frame = new JFrame("Grenoble Eats");
        // créer un objet
        obj = new Restaurants();
        // créer un panneau
        JPanel panel = new JPanel();

        // TODO executer la requete pour chopper la liste des restos
        ResultSet res = null;
        try {
            if (date.equals("date")) {
                if (categorie.equals("categorie")) {
                    res = Requetes.afficheRestaurant(conn, "cuisine");
                } else {
                    res = Requetes.afficheRestaurant(conn, categorie);
                }
            } else {
                if (categorie.equals("categorie")) {
                    res = Requetes.chercheRestaurantHoraire(conn, "cuisine", date,
                            heure);
                } else {
                    res = Requetes.chercheRestaurantHoraire(conn, categorie, date,
                            heure);
                }
            }
        } catch (SQLException e1) {
            e1.printStackTrace();
        }

        // créer la liste des restos
        // TODO trier par recommandation
        try {
            JLabel resto;
            while (res.next()) {
                resto = new JLabel(res.getString(1));
                panel.add(resto);
            }

        } catch (SQLException e1) {
            e1.printStackTrace();
        }

        // créer le champ pour récupérer les plats d'un resto
        JTextField mail = new JTextField(30);
        mail.setText("Mail resto");
        mail.addActionListener(obj);
        panel.add(mail);

        // créer le bouton pour quitter l'app et fermer la connection
        JButton leaveBtn = new JButton("Quitter");
        leaveBtn.addActionListener(obj);
        panel.add(leaveBtn);

        frame.add(panel);
        frame.setSize(800, 800);
        frame.show();
    }

    public void actionPerformed(ActionEvent e) {
        String s = e.getActionCommand();

        if (s.equals("Quitter")) {
            // on ferme l'app
            frame.dispose();
        }

        // on a choisit un resto
        else {
            Plats.main(conn, s);
        }
    }
}
