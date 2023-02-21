package modeles;

import java.sql.*;

public class ReqParam {
    static final String CONN_URL = "jdbc:oracle:thin:@oracle1.ensimag.fr:1521:oracle1";
    static final String USER = "scott"; // A remplacer pour votre compte
    static final String PASSWD = "tiger";

    public ReqParam() {
        try {
            // Enregistrement du driver Oracle
            System.out.print("Loading Oracle driver... ");
            DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
            System.out.println("loaded");
            // Etablissement de la connection
            System.out.print("Connecting to the database... ");
            Connection conn = DriverManager.getConnection(CONN_URL, USER, PASSWD);
            System.out.println("connected");
            // Creation de la requete
            PreparedStatement stmt = conn
                    .prepareStatement("select * from cinesalles where NBPLACES >? and NOMCINE like ?");

            stmt.setInt(1, 200); // 1er parametre
            stmt.setString(2, "L%"); // 2eme parametre
            ResultSet rset = stmt.executeQuery();
            while (rset.next()) {
                System.out.println("Cinema : " + rset.getString(1) + " - Salle : " + rset.getString(2) + "-"
                        + rset.getString(3) + " places");
            }

            // Fermeture
            rset.close();
            stmt.close();
            conn.close();
        } catch (SQLException e) {
            System.err.println("failed");
            e.printStackTrace(System.err);
        }
    }

    public static void main(String args[]) {
        new ReqParam();
    }
}
