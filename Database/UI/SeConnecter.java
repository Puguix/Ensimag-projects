package UI;

import java.awt.event.*;
import javax.swing.*;
import java.sql.*;

public class SeConnecter extends JFrame implements ActionListener {

    static JFrame frame;
    static Connection conn;
    static SeConnecter obj;
    static JTextField user;
    static JTextField mdp;

    public static void main(Connection connection) {

        // initiation de la connection
        conn = connection;

        // créer un frame
        frame = new JFrame("Grenoble Eats");
        // créer un objet
        obj = new SeConnecter();
        // créer un panneau
        JPanel panel = new JPanel();

        // créer les champs pour se connecter
        user = new JTextField(20);
        mdp = new JTextField(20);
        JButton validate = new JButton("Valider");
        user.setText("Mail");
        mdp.setText("Mot de passe");
        panel.add(user);
        panel.add(mdp);
        validate.addActionListener(obj);
        panel.add(validate);

        // créer le bouton pour executer le droit à l'oubli
        JButton delBtn = new JButton("Supprimer mes données");
        delBtn.addActionListener(obj);
        panel.add(delBtn);

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

        if (s.equals("Valider")) {
            // TODO: executer la requete pour récupérer les données

            String mdpBdd;
            try {
                mdpBdd = Requetes.recupMotdepasse(conn, user.getText()).getString(1);

                // Créer une boîte de dialogue
                JDialog d = new JDialog(frame, "Confirmation");
                // Créer une étiquette
                JLabel l;
                if (mdp.getText().equals(mdpBdd)) {
                    l = new JLabel("Vous etes bien connecté!");
                } else {
                    l = new JLabel("Identifiant et/ou mot de passe invalide!");
                }

                d.add(l);
                d.setSize(200, 100);
                d.setVisible(true);
            } catch (SQLException e1) {
                e1.printStackTrace();
            }

        }

        else if (s.equals("Supprimer mes données")) {
            try {
                // TODO: executer la requete pour supprimer l'utilisateur
                Requetes.deleteuser(conn, user.getText());

                // Créer une boîte de dialogue
                JDialog d = new JDialog(frame, "Confirmation");
                // Créer une étiquette
                JLabel l = new JLabel("Votre compte a bien été supprimer");
                // Ajouter l'étiquette à la boîte de dialogue
                d.add(l);
                // Définir la taille de la boîte de dialogue
                d.setSize(200, 100);
                // Définir la visibilité de la boîte de dialogue
                d.setVisible(true);
            } catch (SQLException e1) {
                e1.printStackTrace();
            }
        }

        else if (s.equals("Quitter")) {
            // on ferme l'app
            frame.dispose();
        }
    }
}
