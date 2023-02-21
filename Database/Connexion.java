import java.sql.*;

public class Connexion {

    static final String CONN_URL = "jdbc:oracle:thin:@oracle1.ensimag.fr:1521:oracle1";
    static final String USER = "lim"; // A remplacer pour votre compte, sinon genere une exception
    static final String PASSWD = "lim";

    public static Connection openConnection() {

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

            return conn;

        } catch (SQLException e) {
            System.err.println("failed !");
            e.printStackTrace();
            return null;
        }

    }

    public static void closeConnection(Connection conn) {

        try {
            // Terminaison de la transaction
            conn.commit();

            // Fermetures
            conn.close();
        } catch (SQLException e) {
            System.err.println("failed !");
            e.printStackTrace();
        }
    }
}
