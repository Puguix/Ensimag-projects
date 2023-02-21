package modeles;

import java.sql.*;

public class Transaction {

    static final String CONN_URL = "jdbc:oracle:thin:@oracle1.ensimag.fr:1521:oracle1";
    static final String USER = "scott"; // A remplacer pour votre compte, sinon genere une exception
    static final String PASSWD = "tiger";

    public Transaction() {
        try {
            // Enregistrement du driver Oracle
            System.out.println("Loading Oracle thin driver...");
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
            System.out.println("loaded.");

            // Etablissement de la connexion
            System.out.println("Connecting to the database...");
            Connection conn = DriverManager.getConnection(CONN_URL, USER, PASSWD);
            System.out.println("connected.");

            // Demarrage de la transaction (implicite dans notre cas)
            conn.setAutoCommit(false);
            conn.setTransactionIsolation(conn.TRANSACTION_SERIALIZABLE);

            // Execution des requetes
            PreparedStatement pstmt = conn
                    .prepareStatement("select * from Restaurant where nbplaces > ? and Date == ? and Heure == ?");

            System.out.println("Restaurant de plus de 5 places disponibles le 10/12/2022 à 11h15");
            pstmt.setInt(1, 5);
            pstmt.setString(2, "10-12-22");

            ResultSet rset = pstmt.executeQuery();
            dumpResult(rset);
            rset.close();

            System.out.println("Salles de plus de 300 places des cinemas UGC : ");
            pstmt.setInt(1, 300);
            pstmt.setString(2, "UGC%");

            rset = pstmt.executeQuery();

            dumpResult(rset);
            rset.close();

            // Terminaison de la transaction
            conn.commit();

            // Fermetures
            pstmt.close();
            conn.close();
        } catch (SQLException e) {
            System.err.println("failed !");
            e.printStackTrace();
        }
    }

    void dumpResult(ResultSet r) throws SQLException {
        while (r.next()) {
            System.out.println(
                    "Cinema: " + r.getString(1) +
                            "- Salle: " + r.getString(2) +
                            " - " + r.getInt(3) + " places.");
        }
    }

    public static void main(String args[]) {
        new Transaction();
    }
}
