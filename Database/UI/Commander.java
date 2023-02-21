package UI;

import java.awt.event.*;
import javax.swing.*;
import java.sql.*;
import java.util.HashMap;

public class Commander extends JFrame implements ActionListener {

    static JFrame frame;
    static JPanel panel;
    static Connection conn;
    static Commander obj;
    static JTextField user;
    static JTextField mail;
    static JTextField places;
    static JTextField plat;
    static HashMap<Integer, Integer> plats;

    public static void main(Connection connection) {

        // initiation de la connection
        conn = connection;

        // créer un frame
        frame = new JFrame("Grenoble Eats");
        // créer un objet
        obj = new Commander();
        // créer un panneau
        panel = new JPanel();

        // créer les champs pour passer une commande
        user = new JTextField(20);
        mail = new JTextField(20);
        places = new JTextField(6);
        plat = new JTextField(20);
        JButton add = new JButton("Ajouter");
        user.setText("Mail client");
        mail.setText("Mail resto");
        places.setText("Places");
        plat.setText("Numéro plat");
        panel.add(user);
        panel.add(mail);
        panel.add(mail);
        panel.add(plat);
        add.addActionListener(obj);
        panel.add(add);
        JButton surPlace = new JButton("Commander sur place");
        surPlace.addActionListener(obj);
        panel.add(surPlace);
        JButton aEmporter = new JButton("Commander à emporter");
        aEmporter.addActionListener(obj);
        panel.add(aEmporter);
        JButton livraison = new JButton("Commander en livraison");
        livraison.addActionListener(obj);
        panel.add(livraison);

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

        if (s.equals("Ajouter")) {
            int id = Integer.parseInt(plat.getText());
            // on ajoute le plat à la liste des plats
            if (plats.containsKey(id)) {
                plats.put(id, plats.get(id) + 1);
            } else {
                plats.put(id, 1);
            }
        }

        else if (s.equals("Quitter")) {
            // on ferme l'app
            frame.dispose();
        }

        else {
            // Créer une boîte de dialogue
            JDialog d = new JDialog(frame, "Confirmation");

            // TODO: executer la requete pour commander
            try {
                if (s.equals("Commander sur place")) {
                    //Requetes.addComandeSurPlace(conn, plats, user, mail);
                    int nbPlacesDispo = Requetes.nbrePlaceResto(conn, mail.getText()).getInt(1);
                    if (nbPlacesDispo < Integer.parseInt(places.getText())) {
                        JLabel l = new JLabel("Il n'y a pas assez de places!");
                        d.add(l);
                        d.setSize(200, 100);
                        d.setVisible(true);
                        return;
                    }
                } else if (s.equals("Commander à emporter")) {
                    //Requetes.addComandeEmporter(conn, plats, user, mail);
                } else {
                    //Requetes.addComandeLivraison(conn, plats, user, mail);
                }
            } catch (SQLException e1) {
                e1.printStackTrace();
            }

            // Créer une étiquette
            JLabel l;
            l = new JLabel("La commande est en cours de préparation!");

            d.add(l);
            d.setSize(200, 100);
            d.setVisible(true);
        }
    }
}
