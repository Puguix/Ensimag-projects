import java.awt.event.*;
import javax.swing.*;
import java.sql.*;

import UI.*;

public class Main extends JFrame implements ActionListener {

    static JFrame frame;
    static Connection conn;
    static Main obj;
    static JTextField categorie;
    static JTextField date;
    static JTextField heure;

    public static void main(String[] args) {

        // initiation de la connection
        conn = Connexion.openConnection();

        // créer un frame
        frame = new JFrame("Grenoble Eats");
        // créer un objet
        obj = new Main();
        // créer un panneau
        JPanel panel = new JPanel();

        // créer le bouton pour se connecter
        JButton connectBtn = new JButton("Me connecter");
        connectBtn.addActionListener(obj);
        panel.add(connectBtn);

        // créer de quoi faire la recherche pour voir la liste des restos
        categorie = new JTextField(20);
        categorie.setText("categorie");
        panel.add(categorie);
        date = new JTextField(8);
        date.setText("date");
        panel.add(date);
        heure = new JTextField(8);
        heure.setText("heure");
        panel.add(heure);
        JButton restoBtn = new JButton("Liste des restaurants");
        restoBtn.addActionListener(obj);
        panel.add(restoBtn);

        // créer le bouton pour passer commande
        JButton commandeBtn = new JButton("Passer une commande");
        commandeBtn.addActionListener(obj);
        panel.add(commandeBtn);

        // créer le bouton pour le droit à l'oubli
        JButton btn = new JButton("Supprimer mes données");
        btn.addActionListener(obj);
        panel.add(btn);

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

        if (s.equals("Me connecter") || s.equals("Supprimer mes données")) {
            SeConnecter.main(conn);
        }

        else if (s.equals("Liste des restaurants")) {
            Restaurants.main(conn, categorie.getText(), date.getText(), Integer.parseInt(heure.getText()));
        }

        else if (s.equals("Passer une commande")) {
            Commander.main(conn);
        }

        else if (s.equals("Quitter")) {
            // on ferme la connection
            Connexion.closeConnection(conn);

            // on ferme l'app
            frame.dispose();
        }
    }
}