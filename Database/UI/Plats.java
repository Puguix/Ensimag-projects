package UI;

import java.awt.event.*;
import javax.swing.*;
import java.sql.*;

public class Plats extends JFrame implements ActionListener {

    static JFrame frame;
    static Connection conn;
    static Plats obj;

    public static void main(Connection connection, String mail) {

        // initiation de la connection
        conn = connection;

        // créer un frame
        frame = new JFrame("Grenoble Eats");
        // créer un objet
        obj = new Plats();
        // créer un panneau
        JPanel panel = new JPanel();

        ResultSet res = null;
        // TODO executer la requete pour chopper la liste des plats du resto
        try {
            res = Requetes.affichedetailRestau(conn, mail);
        } catch (SQLException e1) {
            e1.printStackTrace();
        }

        // créer la liste des plats
        JLabel plat;
        try {
            while (res.next()) {
                plat = new JLabel(res.getString(3) + " : " +
                        res.getString(2));
                panel.add(plat);
            }
        } catch (SQLException e1) {
            e1.printStackTrace();
        }

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
    }
}
